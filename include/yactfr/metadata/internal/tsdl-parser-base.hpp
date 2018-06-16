/*
 * A non-predictive recursive descent CTF 1.8 TSDL parser.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_INTERNAL_TSDL_PARSER_BASE_HPP
#define _YACTFR_METADATA_INTERNAL_TSDL_PARSER_BASE_HPP

#include <cstdlib>
#include <memory>
#include <vector>
#include <cstring>
#include <cassert>
#include <unordered_map>
#include <boost/utility.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/nil_generator.hpp>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <yactfr/aliases.hpp>
#include <yactfr/metadata/trace-type.hpp>
#include <yactfr/metadata/trace-type-env.hpp>
#include <yactfr/metadata/data-stream-type.hpp>
#include <yactfr/metadata/event-record-type.hpp>
#include <yactfr/metadata/enum-type.hpp>
#include <yactfr/metadata/aliases.hpp>

#include "string-scanner.hpp"

namespace yactfr {

template <typename ParserCharIt>
TraceType::SP traceTypeFromMetadataText(ParserCharIt, ParserCharIt,
                                        const boost::optional<boost::uuids::uuid>& = boost::none);

namespace internal {

using VofS = std::vector<std::string>;

/*
 * All the "pseudo" stuff below exists because the yactfr metadata
 * objects are immutable and we need to modify them sometimes during
 * the parsing process, mostly because of type aliases containing
 * relative field references (they need to be converted to absolute
 * field references because this is what the yactfr model asks for).
 */

/*
 * A pseudo field reference is the result of parsing a TSDL field
 * reference, possibly not yet converted to an absolute field
 * reference.
 *
 * If `isEnv`, then the parsed field reference was `env.SOMETHING`,
 * where `SOMETHING` should be an existing environment key (for
 * array types). The first element of `pathElements` is `SOMETHING`
 * in this case.
 *
 * If `isAbsolute` is false, then do not consider `scope`. If
 * `isAbsolute` is true, then `scope` indicates the root scope,
 * and `pathElements` contain everything else
 * (`stream.packet.context` and so forth are stripped).
 */
struct PseudoFieldRef {
    bool isEnv = false;
    bool isAbsolute = false;
    Scope scope;
    VofS pathElements;
};

/*
 * Base pseudo data type.
 */
struct PseudoDataType {
    using UP = std::unique_ptr<PseudoDataType>;

    enum class Kind {
        SCALAR_WRAPPER,
        ARRAY,
        SEQUENCE,
        STRUCT,
        VARIANT,
    };

    virtual ~PseudoDataType()
    {
    }

    virtual bool isIntType() const
    {
        return false;
    }

    virtual Kind kind() const = 0;
    virtual PseudoDataType::UP clone() const = 0;
};

/*
 * This is a wrapper for any scalar type. Scalar types are final and
 * do not need to be modified during the parsing process, so we can
 * simply create them directly, wrap them with this so they have the
 * common pseudo data type base, and move them later without
 * unnecessary allocations.
 */
struct PseudoScalarTypeWrapper : public PseudoDataType {
    explicit PseudoScalarTypeWrapper(DataType::UP type) :
        type {std::move(type)}
    {
    }

    bool isIntType() const override
    {
        return type->isIntType();
    }

    PseudoDataType::Kind kind() const override
    {
        return PseudoDataType::Kind::SCALAR_WRAPPER;
    }

    PseudoDataType::UP clone() const override
    {
        return std::make_unique<PseudoScalarTypeWrapper>(type->clone());
    }

    DataType::UP type;
};

/*
 * Pseudo array type. Its element type can contain (eventually)
 * sequence or variant types with relative field references.
 */
struct PseudoArrayType : public PseudoDataType {
    explicit PseudoArrayType(const Size length,
                             PseudoDataType::UP elementType) :
        length {length},
        elementType {std::move(elementType)}
    {
    }

    PseudoDataType::Kind kind() const override
    {
        return PseudoDataType::Kind::ARRAY;
    }

    PseudoDataType::UP clone() const override
    {
        return std::make_unique<PseudoArrayType>(length,
                                                 elementType->clone());
    }

    Size length;
    PseudoDataType::UP elementType;
};

/*
 * Pseudo sequence type. `lengthFieldRef` can be a relative field
 * reference. Its element type can contain (eventually) sequence or
 * variant types with relative field references.
 */
struct PseudoSequenceType : public PseudoDataType {
    explicit PseudoSequenceType(const PseudoFieldRef& lengthFieldRef,
                                PseudoDataType::UP elementType) :
        lengthFieldRef {lengthFieldRef},
        elementType {std::move(elementType)}
    {
    }

    PseudoDataType::Kind kind() const override
    {
        return PseudoDataType::Kind::SEQUENCE;
    }

    PseudoDataType::UP clone() const override
    {
        return std::make_unique<PseudoSequenceType>(lengthFieldRef,
                                                   elementType->clone());
    }

    PseudoFieldRef lengthFieldRef;
    PseudoDataType::UP elementType;
};

/*
 * Pseudo named data type. `type` can contain (eventually)
 * sequence or variant types with relative field references.
 */
struct PseudoNamedDataType {
    using UP = std::unique_ptr<PseudoNamedDataType>;

    PseudoNamedDataType()
    {
    }

    explicit PseudoNamedDataType(const std::string& name,
                                 PseudoDataType::UP type) :
        name {name},
        type {std::move(type)}
    {
    }

    std::string name;
    PseudoDataType::UP type;
};

using PseudoNamedDataTypes = std::vector<PseudoNamedDataType::UP>;

/*
 * Pseudo structure type. `fields` can contain (eventually)
 * sequence or variant types with relative field references.
 */
struct PseudoStructType : public PseudoDataType {
    explicit PseudoStructType(const unsigned long long minAlignment,
                              PseudoNamedDataTypes&& fields) :
        minAlignment {minAlignment},
        fields {std::move(fields)}
    {
    }

    PseudoDataType::Kind kind() const override
    {
        return PseudoDataType::Kind::STRUCT;
    }

    PseudoDataType::UP clone() const override
    {
        PseudoNamedDataTypes newFields;

        for (const auto& field : fields) {
            auto newField = std::make_unique<PseudoNamedDataType>(field->name, field->type->clone());
            newFields.push_back(std::move(newField));
        }

        return std::make_unique<PseudoStructType>(minAlignment,
                                                  std::move(newFields));
    }

    unsigned long long minAlignment;
    PseudoNamedDataTypes fields;
};

/*
 * Pseudo variant type. `tagFieldRef` can be a relative field
 * reference. `choices` can contain (eventually) sequence or variant
 * types with relative field references.
 */
struct PseudoVariantType : public PseudoDataType {
    explicit PseudoVariantType(const PseudoFieldRef& tagFieldRef,
                               PseudoNamedDataTypes&& choices) :
        tagFieldRef {tagFieldRef},
        choices {std::move(choices)}
    {
    }

    PseudoDataType::Kind kind() const override
    {
        return PseudoDataType::Kind::VARIANT;
    }

    PseudoDataType::UP clone() const override
    {
        PseudoNamedDataTypes newChoices;

        for (const auto& choice : choices) {
            auto newChoice = std::make_unique<PseudoNamedDataType>(choice->name, choice->type->clone());
            newChoices.push_back(std::move(newChoice));
        }

        return std::make_unique<PseudoVariantType>(tagFieldRef,
                                                   std::move(newChoices));
    }

    PseudoFieldRef tagFieldRef;
    PseudoNamedDataTypes choices;
};

// a pseudo data stream type: a mutable event record type
struct PseudoEventRecordType {
    TypeId id = 0;
    boost::optional<std::string> name = boost::none;
    boost::optional<LogLevel> logLevel = boost::none;
    boost::optional<std::string> modelEmfUri = boost::none;
    PseudoDataType::UP contextType;
    PseudoDataType::UP payloadType;
};

// a pseudo data stream type: a mutable data stream type
struct PseudoDataStreamType {
    TypeId id = 0;
    std::unordered_map<TypeId, std::unique_ptr<PseudoEventRecordType>> eventRecordTypes;
    PseudoDataType::UP packetContextType;
    PseudoDataType::UP eventHeaderType;
    PseudoDataType::UP eventContextType;
};

// a pseudo trace type: a mutable trace type
struct PseudoTraceType {
    unsigned int majorVersion = 0;
    unsigned int minorVersion = 0;
    int defaultByteOrder = -1;
    boost::uuids::uuid uuid;
    PseudoDataType::UP packetHeaderType;
    std::unique_ptr<const TraceTypeEnv> env;
    ClockTypeSet clockTypes;
    std::unordered_map<TypeId, std::unique_ptr<PseudoDataStreamType>> dataStreamTypes;

    void clear();
};

struct PseudoSignedEnumTypeMember {
    std::set<SignedEnumType::Range> ranges;
};

struct PseudoUnsignedEnumTypeMember {
    std::set<UnsignedEnumType::Range> ranges;
};

struct MutableMetadataTextLocation {
    explicit MutableMetadataTextLocation(const MetadataTextLocation& location) :
        _lineNumber {location.lineNumber()},
        _colNumber {location.colNumber()}
    {
    }

    MutableMetadataTextLocation& operator=(const MetadataTextLocation& location)
    {
        _lineNumber = location.lineNumber();
        _colNumber = location.colNumber();
        return *this;
    }

    MetadataTextLocation location() const
    {
        return MetadataTextLocation {_lineNumber, _colNumber};
    }

private:
    Index _lineNumber, _colNumber;
};

/*
 * CTF metadata parser base. Everything in this base class does not
 * depend on the type of the iterator used in the templated
 * yactfr::internal::TsdlParser class, but is still accessible by any
 * version of the concrete parser.
 */
class TsdlParserBase :
    private boost::noncopyable
{
    template <typename ParserCharIt>
    friend TraceType::SP yactfr::traceTypeFromMetadataText(ParserCharIt, ParserCharIt,
                                                           const boost::optional<boost::uuids::uuid>&);

public:
    /*
     * Returns the parsed trace type.
     */
    TraceType::SP traceType() const
    {
        return _traceType;
    }

protected:
    TsdlParserBase()
    {
    }

    /*
     * One frame of the parser's context stack. Each frame has:
     *
     * * A kind, which indicates what kind of frame/scope this
     *   represents.
     * * A map of type alias name to full pseudo data type, local to
     *   the frame. Frames which are higher in the stack have access
     *   to the aliased types of the frames below them.
     * * A vector of the current field names, when this frame's kind is
     *   `STRUCT_TYPE` or `VARIANT_TYPE`. This is used to ensure that a
     *   relative field reference does not target a field which is
     *   located outside the topmost type alias frame. Even if CTF 1.8
     *   officially supports this feature, we don't.
     *
     * You can use _stackPush() and _stackPop() manually, but it is
     * recommended to use an RAII _LexicalScope instead to automatically
     * push and pop scopes and avoid errors.
     */
    struct _StackFrame {
        enum class Kind {
            ROOT,
            TRACE,
            PACKET_HEADER_TYPE,
            STREAM,
            STREAM_PACKET_CONTEXT_TYPE,
            STREAM_EVENT_HEADER_TYPE,
            STREAM_EVENT_CONTEXT_TYPE,
            EVENT,
            EVENT_CONTEXT_TYPE,
            EVENT_PAYLOAD_TYPE,
            TYPE_ALIAS,
            STRUCT_TYPE,
            VARIANT_TYPE,
        };

        _StackFrame(const Kind kind) :
            kind {kind}
        {
        }

        const Kind kind;
        std::unordered_map<std::string, PseudoDataType::UP> typeAliases;
        VofS fieldNames;
    };

    /*
     * This special stack frame is used only during
     * _dataTypeFromPseudoDataType() to resolve relative pseudo field
     * references to absolute field references.
     */
    struct _ResolvingStackFrame {
        _ResolvingStackFrame(const std::string& name) :
            name {name}
        {
        }

        const std::string name;
        VofS fieldNames;
    };

    using _ResolvingStack = std::vector<_ResolvingStackFrame>;

    /*
     * An attribute, the result of parsing something like this:
     *
     *     size = 32;
     *     byte_order = be;
     *     map = clock.monotonic.value;
     *     custom_stuff = "hello there";
     */
    class _Attribute {
    public:
        enum class Kind {
            UNSET,
            STRING,
            INT,
            UINT,
            IDENTIFIER,
            CLOCK_NAME_VALUE,
        };

    public:
        /*
         * String attribute to display base. Throws if the string is an
         * unknown base.
         */
        DisplayBase displayBase() const;

        /*
         * Ensures that the attribute's kind is `expectedKind`, throwing an
         * error if it's not the case.
         */
        void checkKind(const Kind expectedKind) const;

        /*
         * Throws that the attribute is an unknown attribute.
         */
        void throwUnknown() const;

        /*
         * Throws that the attribute should be a boolean attribute.
         */
        void throwExpectingBool() const;

        /*
         * Returns an alignment from the attribute, throwing an error
         * if it's a wrong alignment or if the attribute's kind is not
         * the expected one.
         */
        unsigned int alignment() const;

        /*
         * Returns a byte order from attribute the attribute, throwing
         * an error if it cannot.
         */
        int byteOrder() const;

        /*
         * Returns an encoding from the attribute, throwing an error if
         * it cannot.
         */
        Encoding encoding() const;

        /*
         * Returns the equivalent boolean value of this attribute,
         * throwing an error if it cannot.
         */
        bool boolEquiv() const;

        const MetadataTextLocation nameTextLocation() const
        {
            return nameLocation.location();
        }

        const MetadataTextLocation valueTextLocation() const
        {
            return valueLocation.location();
        }

    public:
        // kind of attribute
        Kind kind = Kind::UNSET;

        // attribute's name
        std::string name;

        // string value (for `STRING`, `IDENTIFIER`, and `CLOCK_NAME_VALUE` kinds)
        std::string strValue;

        // unsignefd integer value (for `UINT` kind)
        unsigned long long uintValue = -1ULL;

        // signed integer value (for `INT` kind)
        long long intValue = -1LL;

        // source location of the beginning of the parsed attribute's name
        MutableMetadataTextLocation nameLocation {MetadataTextLocation {0, 0}};

        // source location of the beginning of the parsed attribute's value
        MutableMetadataTextLocation valueLocation {MetadataTextLocation {0, 0}};

        // true if this attribute can represent a boolean value
        bool hasEquivBool = false;

        // attribute's equivalent boolean value if `hasEquivBool` is true
        bool equivBool = false;

    private:
        /*
         * String attribute to byte order. Throws if the string is an
         * unknown byte order.
         */
        int _toByteOrder() const;

        /*
         * String attribute to encoding. Throws if the string is an
         * unknown encoding.
         */
        Encoding _toEncoding() const;
    };

    class _LexicalScope :
        private boost::noncopyable
    {
    public:
        _LexicalScope() noexcept :
            _mp {nullptr},
            _kind {_StackFrame::Kind::ROOT}
        {
        }

        explicit _LexicalScope(TsdlParserBase& mp,
                              const _StackFrame::Kind kind) :
            _mp {&mp},
            _kind {kind}
        {
            _mp->_stackPush(kind);
        }

        ~_LexicalScope()
        {
            this->exit();
        }

        void operator=(const _LexicalScope& lexicalScope)
        {
            this->exit();
            _mp = lexicalScope._mp;
            _kind = lexicalScope._kind;
            _mp->_stackPush(_kind);
        }

        void exit()
        {
            if (_mp) {
                _mp->_stackPop();
            }

            _mp = nullptr;
        }

    private:
        TsdlParserBase *_mp;
        TsdlParserBase::_StackFrame::Kind _kind;
    };

    using _Attributes = std::vector<_Attribute>;

protected:
    // creates the trace type
    void _createTraceType();

    // applies various metadata quirks
    void _applyQuirks();

    // pushes the lexical scope stack
    void _stackPush(const _StackFrame::Kind kind)
    {
        _stack.push_back(_StackFrame {kind});
    }

    // pops the lexical scope stack
    void _stackPop()
    {
        assert(!_stack.empty());
        _stack.pop_back();
    }

    // returns the top frame of the lexical scope stack
    _StackFrame& _stackTop()
    {
        assert(!_stack.empty());
        return _stack.back();
    }

    bool _pseudoFieldRefFromAbsoluteAllPathElements(const VofS& allPathElements,
                                                    const MetadataTextLocation& location,
                                                    PseudoFieldRef& pseudoFieldRef,
                                                    bool expect);
    bool _pseudoFieldRefFromRelativeAllPathElements(const VofS& allPathElements,
                                                    const MetadataTextLocation& location,
                                                    PseudoFieldRef& pseudoFieldRef,
                                                    bool expect);
    bool _pseudoFieldRefFromAllPathElements(const VofS& allPathElements,
                                            const MetadataTextLocation& location,
                                            PseudoFieldRef& pseudoFieldRef,
                                            bool expect);

    /*
     * Returns whether or not a pseudo data stream type currently exists
     * with the ID `id`.
     */
    bool _pseudoDataStreamTypeExists(const TypeId id) const
    {
        return _pseudoTraceType.dataStreamTypes.find(id) !=
               std::end(_pseudoTraceType.dataStreamTypes);
    }

    /*
     * Returns a cloned pseudo data type corresponding to an alias name
     * within the context of the current frame.
     */
    PseudoDataType::UP _getAliasedType(const std::string& name) const;

    /*
     * Adds a type alias to the current stack frame's register. `type`
     * is cloned and associated to `name`.
     */
    void _addTypeAlias(const std::string& name, const PseudoDataType& type,
                       const MetadataTextLocation& curLocation);

    void _addTypeAlias(const std::string& name, const PseudoDataType& type,
                       const MetadataTextLocation& curLocation, _StackFrame& frame);

protected:
    /*
     * Checks for duplicate named data types in `entries` (by name),
     * throwing an error if one is found.
     */
    static void _checkDupNamedDataType(const PseudoNamedDataTypes& entries,
                                       const MetadataTextLocation& location);

    /*
     * Returns whether or not `type` is recursively a variant type
     * (passing through array and sequence types).
     */
    static bool _isVariantTypeUntaggedRec(const PseudoDataType& type);

    /*
     * Throws that the attribute named `name` is missing at location
     * `location`.
     */
    static void _throwMissingAttribute(const std::string& name,
                                       const MetadataTextLocation& location);

    /*
     * Checks for duplicate attributes in `attrs`, throwing an error if
     * any is found.
     */
    static void _checkDupAttribute(const _Attributes& attrs);

    /*
     * Returns a UUID object from the canonical textual representation
     * `str`. Returns a nil UUID if the conversion fails.
     */
    static boost::uuids::uuid _uuidFromString(const std::string& str);

    /*
     * Converts a pseudo event record type to a concrete event record
     * type.
     */
    static std::unique_ptr<const DataStreamType> _dataStreamTypeFromPseudoDataStreamType(const PseudoDataStreamType& pseudoDataStreamType);

    /*
     * Converts a pseudo event record type to a concrete event record
     * type.
     */
    static std::unique_ptr<const EventRecordType> _eventRecordTypeFromPseudoEventRecordType(const PseudoEventRecordType& pseudoEventRecordType);

    /*
     * Converts a pseudo data type to a concrete data type, recursively
     * resolving all the relative pseudo field references to concrete
     * absolute field references for sequence and variant types, and
     * throwing if any error occurs.
     *
     * `scope` is the scope of which `pseudoDataType` is the root type.
     */
    static DataType::UP _dataTypeFromPseudoDataType(const PseudoDataType& pseudoDataType,
                                                    Scope scope);

    static DataType::UP _dataTypeFromPseudoDataType(const PseudoDataType& pseudoDataType,
                                                    Scope scope,
                                                    const std::string &name,
                                                    _ResolvingStack& stack);
    static FieldRef _fieldRefFromPseudoFieldRef(const PseudoFieldRef& pseudoFieldRef,
                                                Scope scope,
                                                _ResolvingStack& stack);
    static DataType::UP _dataTypeFromPseudoScalarTypeWrapper(const PseudoDataType& pseudoDataType,
                                                             Scope scope,
                                                             _ResolvingStack& stack);
    static DataType::UP _dataTypeFromPseudoArrayType(const PseudoDataType& pseudoDataType,
                                                     Scope scope,
                                                     const std::string &name,
                                                     _ResolvingStack& stack);
    static DataType::UP _dataTypeFromPseudoSequenceType(const PseudoDataType& pseudoDataType,
                                                        Scope scope,
                                                        const std::string &name,
                                                        _ResolvingStack& stack);
    static DataType::UP _dataTypeFromPseudoStructType(const PseudoDataType& pseudoDataType,
                                                      Scope scope,
                                                      const std::string &name,
                                                      _ResolvingStack& stack);
    static DataType::UP _dataTypeFromPseudoVariantType(const PseudoDataType& pseudoDataType,
                                                       Scope scope,
                                                       const std::string &name,
                                                       _ResolvingStack& stack);

protected:
    static const char * const _MODEL_EMF_URI_ATTR;
    static constexpr Size _MAX_FAST_INT_FT_STRING_SIZE = 256;

protected:
    // final trace type
    TraceType::SP _traceType;

    // current trace type data
    PseudoTraceType _pseudoTraceType;

    // lexical scope stack
    std::vector<_StackFrame> _stack;
};

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_METADATA_INTERNAL_TSDL_PARSER_BASE_HPP
