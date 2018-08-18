/*
 * Metadata parser base.
 *
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <tuple>
#include <set>

#include <yactfr/metadata/internal/tsdl-parser-base.hpp>
#include <yactfr/metadata/metadata-text-location.hpp>
#include <yactfr/metadata/array-type.hpp>
#include <yactfr/metadata/text-array-type.hpp>
#include <yactfr/metadata/sequence-type.hpp>
#include <yactfr/metadata/text-sequence-type.hpp>
#include <yactfr/metadata/struct-type.hpp>
#include <yactfr/metadata/variant-type.hpp>
#include <yactfr/metadata/metadata-parse-error.hpp>
#include <yactfr/internal/utils.hpp>

namespace yactfr {
namespace internal {

const char * const TsdlParserBase::_MODEL_EMF_URI_ATTR = "model.emf.uri";

struct TimestampFieldQuirkProcessor
{
    TimestampFieldQuirkProcessor(const std::vector<std::string>& fieldNames,
                                 PseudoTraceType& pseudoTraceType,
                                 PseudoDataType& rootDataType) :
        _fieldNames {&fieldNames},
        _pseudoTraceType {&pseudoTraceType}
    {
        this->_process(rootDataType);
    }

private:
    void _process(PseudoDataType& dataType)
    {
        switch (dataType.kind()) {
        case PseudoDataType::Kind::SCALAR_WRAPPER:
            return this->_process(static_cast<PseudoScalarTypeWrapper&>(dataType));

        case PseudoDataType::Kind::ARRAY:
            return this->_process(static_cast<PseudoArrayType&>(dataType));

        case PseudoDataType::Kind::SEQUENCE:
            return this->_process(static_cast<PseudoSequenceType&>(dataType));

        case PseudoDataType::Kind::STRUCT:
            return this->_process(static_cast<PseudoStructType&>(dataType));

        case PseudoDataType::Kind::VARIANT:
            return this->_process(static_cast<PseudoVariantType&>(dataType));

        default:
            abort();
        }
    }

    void _process(PseudoScalarTypeWrapper& dataType)
    {
        if (!_curFieldName) {
            // non-struct or non-variant root?
            return;
        }

        bool process = false;

        for (const auto& fieldName : *_fieldNames) {
            if (fieldName == *_curFieldName) {
                process = true;
                break;
            }

            // also check the display name
            if (!_curFieldName->empty() && (*_curFieldName)[0] == '_' &&
                    _curFieldName->compare(1, _curFieldName->size() - 1, fieldName) == 0) {
                process = true;
                break;
            }
        }

        if (!process) {
            return;
        }

        if (!dataType.type->isUnsignedIntType()) {
            return;
        }

        auto intType = dataType.type->asIntType();

        if (intType->mappedClockTypeName()) {
            return;
        }

        if (_pseudoTraceType->clockTypes.empty()) {
            // create implicit 1 GHz clock type
            auto clockType = std::make_unique<const ClockType>("default",
                                                               1000000000,
                                                               boost::none,
                                                               boost::none, 0,
                                                               ClockTypeOffset {0, 0},
                                                               true);

            _pseudoTraceType->clockTypes.insert(std::move(clockType));
        }

        if (_pseudoTraceType->clockTypes.size() != 1) {
            // we don't know which clock type to choose, leave it unmapped
            return;
        }

        auto& clockTypeUp = *std::begin(_pseudoTraceType->clockTypes);
        auto uintType = std::make_unique<const UnsignedIntType>(intType->alignment(),
                                                                intType->size(),
                                                                intType->byteOrder(),
                                                                intType->displayBase(),
                                                                intType->encoding(),
                                                                clockTypeUp->name());

        // finally, replace the original type
        dataType.type = std::move(uintType);
    }

    void _process(PseudoArrayType& dataType) {
        this->_process(*dataType.elementType);
    }

    void _process(PseudoSequenceType& dataType) {
        this->_process(*dataType.elementType);
    }

    void _process(PseudoStructType& dataType) {
        for (auto& field : dataType.fields) {
            _curFieldName = &field->name;
            this->_process(*field->type);
        }
    }

    void _process(PseudoVariantType& dataType) {
        for (auto& option : dataType.options) {
            _curFieldName = &option->name;
            this->_process(*option->type);
        }
    }

private:
    const std::vector<std::string> *_fieldNames;
    PseudoTraceType *_pseudoTraceType;
    std::string *_curFieldName = nullptr;

};

void TsdlParserBase::_applyQuirks()
{
    /*
     * For all the timestamp fields in event record type headers and
     * packet context types, if it's not mapped to a clock type:
     *
     * * If there's exactly one clock type, map it to this clock type.
     *
     * * If there's no clock type, create a default 1 GHz clock type and
     *   map it to this one.
     *
     * * If there's more than one clock type, leave it as is (unmapped).
     */
    for (auto& idPseudoDstPair : _pseudoTraceType.dataStreamTypes) {
        auto& pseudoDst = idPseudoDstPair.second;

        if (pseudoDst->eventHeaderType) {
            TimestampFieldQuirkProcessor {
                {"timestamp"}, _pseudoTraceType, *pseudoDst->eventHeaderType
            };
        }

        if (pseudoDst->packetContextType) {
            TimestampFieldQuirkProcessor {
                {"timestamp_begin", "timestamp_end"},
                _pseudoTraceType, *pseudoDst->packetContextType
            };
        }
    }
}

void TsdlParserBase::_createTraceType()
{
    if (_pseudoTraceType.majorVersion == 0) {
        throw MetadataParseError {"Missing `trace` block."};
    }

    DataStreamTypeSet dstSet;

    for (auto& idPseudoDstPair : _pseudoTraceType.dataStreamTypes) {
        auto dst = TsdlParserBase::_dataStreamTypeFromPseudoDataStreamType(*idPseudoDstPair.second);

        dstSet.insert(std::move(dst));
    }

    DataType::UP packetHeaderType;

    if (_pseudoTraceType.packetHeaderType) {
        packetHeaderType = TsdlParserBase::_dataTypeFromPseudoDataType(*_pseudoTraceType.packetHeaderType,
                                                                       Scope::PACKET_HEADER);
    }

    try {
        _traceType = std::make_shared<const TraceType>(_pseudoTraceType.majorVersion,
                                                       _pseudoTraceType.minorVersion,
                                                       _pseudoTraceType.uuid,
                                                       std::move(packetHeaderType),
                                                       std::move(_pseudoTraceType.env),
                                                       std::move(_pseudoTraceType.clockTypes),
                                                       std::move(dstSet));
    } catch (const InvalidMetadata& ex) {
        MetadataParseError error {ex.what()};
        std::ostringstream ss;

        ss << "When creating trace type:";
        error._appendErrorMessage(ss.str(), MetadataTextLocation {0, 0});
        throw error;
    }
}

void TsdlParserBase::_checkDupNamedDataType(const PseudoNamedDataTypes& entries,
                                            const MetadataTextLocation& location)
{
    std::set<std::string> entryNames;

    for (const auto& entry : entries) {
        if (entryNames.find(entry->name) != std::end(entryNames)) {
            std::ostringstream ss;

            ss << "Duplicate field/option `" << entry->name << "`.";
            throw MetadataParseError {ss.str(), location};
        }

        entryNames.insert(entry->name);
    }
}

bool TsdlParserBase::_isVariantTypeUntaggedRec(const PseudoDataType& type)
{
    if (type.kind() == PseudoDataType::Kind::ARRAY) {
        auto& arrayType = static_cast<const PseudoArrayType&>(type);
        return TsdlParserBase::_isVariantTypeUntaggedRec(*arrayType.elementType);
    }

    if (type.kind() == PseudoDataType::Kind::SEQUENCE) {
        auto& sequenceType = static_cast<const PseudoSequenceType&>(type);
        return TsdlParserBase::_isVariantTypeUntaggedRec(*sequenceType.elementType);
    }

    if (type.kind() != PseudoDataType::Kind::VARIANT) {
        return false;
    }

    auto& pseudoVariantType = static_cast<const PseudoVariantType&>(type);
    return pseudoVariantType.tagFieldRef.pathElements.empty();
}

int TsdlParserBase::_Attribute::_toByteOrder() const
{
    if (strValue == "be" || strValue == "network") {
        return static_cast<int>(ByteOrder::BIG);
    } else if (strValue == "le") {
        return static_cast<int>(ByteOrder::LITTLE);
    } else if (strValue == "native") {
        return -1;
    }

    std::ostringstream ss;

    ss << "Invalid byte order `" << strValue << "`.";
    throw MetadataParseError {ss.str(), this->valueTextLocation()};
}

Encoding TsdlParserBase::_Attribute::_toEncoding() const
{
    if (strValue == "NONE" || strValue == "none") {
        return Encoding::NONE;
    } else if (strValue == "UTF8" || strValue == "utf8") {
        return Encoding::UTF8;
    } else if (strValue == "ASCII" || strValue == "ascii") {
        // ASCII is UTF-8 anyway
        return Encoding::UTF8;
    }

    std::ostringstream ss;

    ss << "Invalid encoding `" << strValue << "`.";
    throw MetadataParseError {ss.str(), this->valueTextLocation()};
}

DisplayBase TsdlParserBase::_Attribute::displayBase() const
{
    int dispBase = 0;

    if (kind != Kind::UINT && kind != Kind::IDENTIFIER) {
        std::ostringstream ss;

        ss << "Attribute `" << name <<
              "`: expecting constant unsigned integer or identifier.";
        throw MetadataParseError {ss.str(), this->valueTextLocation()};
    }

    if (kind == Kind::UINT) {
        if (uintValue != 2 && uintValue != 8 && uintValue != 10 && uintValue != 16) {
            std::ostringstream ss;

            ss << "Invalid `base` attribute: " << uintValue << ".";
            throw MetadataParseError {ss.str(), this->valueTextLocation()};
        }

        dispBase = uintValue;
    }

    if (strValue == "decimal" || strValue == "dec" || strValue == "d" ||
            strValue == "i" || strValue == "u") {
        dispBase = 10;
    } else if (strValue == "hexadecimal" || strValue == "hex" ||
            strValue == "x" || strValue == "X" || strValue == "p") {
        dispBase = 16;
    } else if (strValue == "octal" || strValue == "oct" || strValue == "o") {
        dispBase = 8;
    } else if (strValue == "binary" || strValue == "bin" || strValue == "b") {
        dispBase = 2;
    }

    if (dispBase == 0) {
        std::ostringstream ss;

        ss << "Invalid `base` attribute: `" << strValue << "`.";
        throw MetadataParseError {ss.str(), this->valueTextLocation()};
    }

    return static_cast<DisplayBase>(dispBase);
}

void TsdlParserBase::_Attribute::checkKind(const Kind expectedKind) const
{
    if (kind != expectedKind) {
        std::ostringstream ss;

        ss << "Attribute `" << name << "`: expecting ";

        switch (expectedKind) {
        case _Attribute::Kind::STRING:
            ss << "literal string";
            break;

        case _Attribute::Kind::UINT:
            ss << "constant unsigned integer.";
            break;

        case _Attribute::Kind::INT:
            ss << "constant signed integer.";
            break;

        case _Attribute::Kind::IDENTIFIER:
            ss << "identifier.";
            break;

        case _Attribute::Kind::CLOCK_NAME_VALUE:
            ss << "`clock.NAME.value`.";
            break;

        default:
            abort();
        }

        throw MetadataParseError {ss.str(), this->valueTextLocation()};
    }
}

void TsdlParserBase::_Attribute::throwUnknown() const
{
    std::ostringstream ss;

    ss << "Unknown attribute `" << name << "`.";
    throw MetadataParseError {ss.str(), this->nameTextLocation()};
}

unsigned int TsdlParserBase::_Attribute::alignment() const
{
    this->checkKind(Kind::UINT);

    if (!internal::ispow2(uintValue)) {
        std::ostringstream ss;

        ss << "Invalid `align` attribute (must be a power of two): " <<
              uintValue << ".";
        throw MetadataParseError {ss.str(), this->valueTextLocation()};
    }

    return uintValue;
}

int TsdlParserBase::_Attribute::byteOrder() const
{
    this->checkKind(Kind::IDENTIFIER);
    return this->_toByteOrder();
}

Encoding TsdlParserBase::_Attribute::encoding() const
{
    this->checkKind(Kind::IDENTIFIER);
    return this->_toEncoding();
}

/*
 * Returns the equivalent boolean value of this attribute,
 * throwing an error if it cannot.
 */
bool TsdlParserBase::_Attribute::boolEquiv() const
{
    switch (kind) {
    case Kind::UINT:
        if (uintValue == 1) {
            return true;
        } else if (uintValue == 0) {
            return false;
        }
        break;

    case Kind::IDENTIFIER:
        if (strValue == "true" || strValue == "TRUE") {
            return true;
        } else if (strValue == "false" || strValue == "FALSE") {
            return false;
        }

    default:
        break;
    }

    std::ostringstream ss;

    ss << "Expecting `0`, `false`, `FALSE`, `1`, `true`, or `TRUE` for `" <<
          name << "` attribute.";
    throw MetadataParseError {ss.str(), this->valueTextLocation()};
}

void TsdlParserBase::_checkDupAttribute(const _Attributes& attrs)
{
    std::set<std::string> attrSet;

    for (const auto& attr : attrs) {
        if (attrSet.find(attr.name) != std::end(attrSet)) {
            std::ostringstream ss;

            ss << "Duplicate attribute `" << attr.name << "`.";
            throw MetadataParseError {ss.str(), attr.nameTextLocation()};
        }

        attrSet.insert(attr.name);
    }
}

void TsdlParserBase::_throwMissingAttribute(const std::string& name,
                                            const MetadataTextLocation& location)
{
    std::ostringstream ss;

    ss << "Missing attribute `" << name << "`.";
    throw MetadataParseError {ss.str(), location};
}

boost::uuids::uuid TsdlParserBase::_uuidFromString(const std::string& str)
{
    const boost::uuids::nil_generator nilGen;

    try {
        return boost::uuids::string_generator {}(str);
    } catch (...) {
        return nilGen();
    }
}

bool TsdlParserBase::_pseudoFieldRefFromAbsoluteAllPathElements(const VofS& allPathElements,
                                                                const MetadataTextLocation& location,
                                                                PseudoFieldRef& pseudoFieldRef,
                                                                const bool expect)
{
    auto restPos = std::begin(allPathElements);

    if (allPathElements.size() >= 3) {
        if (allPathElements[0] == "trace") {
            if (allPathElements[1] == "packet") {
                if (allPathElements[2] == "header") {
                    pseudoFieldRef.scope = Scope::PACKET_HEADER;
                    pseudoFieldRef.isAbsolute = true;
                }
            }

            if (!pseudoFieldRef.isAbsolute) {
                if (expect) {
                    throw MetadataParseError {
                        "Expecting `packet.header` after `trace.`.",
                        location
                    };
                } else {
                    return false;
                }
            }
        } else if (allPathElements[0] == "stream") {
            if (allPathElements[1] == "packet") {
                if (allPathElements[2] == "context") {
                    pseudoFieldRef.scope = Scope::PACKET_CONTEXT;
                    pseudoFieldRef.isAbsolute = true;
                }
            } else if (allPathElements[1] == "event") {
                if (allPathElements[2] == "header") {
                    pseudoFieldRef.scope = Scope::EVENT_RECORD_HEADER;
                    pseudoFieldRef.isAbsolute = true;
                } else if (allPathElements[2] == "context") {
                    pseudoFieldRef.scope = Scope::EVENT_RECORD_FIRST_CONTEXT;
                    pseudoFieldRef.isAbsolute = true;
                }
            }

            if (!pseudoFieldRef.isAbsolute) {
                if (expect) {
                    throw MetadataParseError {
                        "Expecting `packet.context`, `event.header`, or "
                        "`event.context` after `stream.`.",
                        location
                    };
                } else {
                    return false;
                }
            }
        }

        if (pseudoFieldRef.isAbsolute) {
            restPos = std::begin(allPathElements) + 3;
        }
    }

    if (!pseudoFieldRef.isAbsolute && allPathElements.size() >= 2) {
        if (allPathElements[0] == "event") {
            if (allPathElements[1] == "context") {
                pseudoFieldRef.scope = Scope::EVENT_RECORD_SECOND_CONTEXT;
                pseudoFieldRef.isAbsolute = true;
            } else if (allPathElements[1] == "fields") {
                pseudoFieldRef.scope = Scope::EVENT_RECORD_PAYLOAD;
                pseudoFieldRef.isAbsolute = true;
            }

            if (!pseudoFieldRef.isAbsolute) {
                if (expect) {
                    throw MetadataParseError {
                        "Expecting `context` or `fields` after `event.`.",
                        location
                    };
                } else {
                    return false;
                }
            }
        }

        if (pseudoFieldRef.isAbsolute) {
            restPos = std::begin(allPathElements) + 2;
        }
    }

    if (!pseudoFieldRef.isAbsolute && allPathElements.size() >= 1) {
        if (allPathElements[0] == "env") {
            pseudoFieldRef.isAbsolute = true;
            pseudoFieldRef.isEnv = true;
            restPos = std::begin(allPathElements) + 1;
        }
    }

    if (!pseudoFieldRef.isAbsolute) {
        return false;
    }

    /*
     * Field reference is already absolute: skip the root scope part (or
     * `env`) to create the path elements.
     */
    std::copy(restPos, std::end(allPathElements),
              std::back_inserter(pseudoFieldRef.pathElements));
    return true;
}

bool TsdlParserBase::_pseudoFieldRefFromRelativeAllPathElements(const VofS& allPathElements,
                                                                const MetadataTextLocation& location,
                                                                PseudoFieldRef& pseudoFieldRef,
                                                                const bool expect)
{
    /*
     * In this method, we only want to make sure that the relative field
     * reference does not target a field which is outside the topmost
     * type alias scope, if any, in the current stack.
     *
     * For example, this is okay:
     *
     *     typealias struct {
     *         int a;
     *         struct {
     *             string seq[a];
     *         } b;
     *     } := some_name;
     *
     * This is not (it _should_, in fact, but it's not supported as of
     * this version of yactfr):
     *
     *     typealias struct {
     *         my_int a;
     *
     *         typealias struct {
     *             string seq[a];
     *         } := my_struct;
     *
     *         struct {
     *             int a;
     *             my_struct b;
     *         };
     *     } := some_name;
     *
     * In this last example, the length type's position for the sequence
     * type `seq[a]` contained in `my_struct b` is NOT `int a`
     * immediately before, but rather `my_int a`. In practice, this
     * trick of using a field type which is external to a type alias for
     * sequence length or variant tag is rarely, if ever used.
     *
     * So this is easy to detect, because each time this parser "enters"
     * a type alias (with the `typealias` keyword or with a named
     * structure/variant type), it pushes a type alias frame on the
     * stack. We just need to check if we can find the first path
     * element within the field names of the stack frames, from top to
     * bottom, until we reach a type alias or the root frame (both lead
     * to an exception).
     */

    assert(!_stack.empty());
    assert(!allPathElements.empty());

    // find position of first path element in stack from top to bottom
    auto stackIt = _stack.cend() - 1;
    const auto& pathElem = allPathElements.front();

    while (true) {
        if (stackIt->kind == _StackFrame::Kind::TYPE_ALIAS) {
            if (expect) {
                std::ostringstream ss;

                ss << "First field name of field reference, `" <<
                      pathElem << "`, refers to a field which crosses a "
                      "type alias (or named structure/variant type) boundary. "
                      "CTF 1.8 allows this, but this version of yactfr does not "
                      "support it.";
                throw MetadataParseError {ss.str(), location};
            } else {
                return false;
            }
        }

        const auto& frameFieldNames = stackIt->fieldNames;

        if (std::find(std::begin(frameFieldNames), std::end(frameFieldNames), pathElem) != std::end(frameFieldNames)) {
            // field found in this frame: win!
            pseudoFieldRef.isAbsolute = false;
            pseudoFieldRef.isEnv = false;
            pseudoFieldRef.pathElements = allPathElements;
            return true;
        }

        // field is not in this frame: try next (lower) stack frame
        if (stackIt == _stack.cbegin()) {
            if (expect) {
                // no more frames: not found
                std::ostringstream ss;

                ss << "Relative field reference `";

                for (auto it = std::begin(allPathElements); it != std::end(allPathElements); ++it) {
                    ss << *it;

                    if (it != std::end(allPathElements) - 1) {
                        ss << ".";
                    }
                }

                ss << "` does not target an existing field.";
                throw MetadataParseError {ss.str(), location};
            } else {
                return false;
            }
        }

        --stackIt;
    }

    return false;
}

bool TsdlParserBase::_pseudoFieldRefFromAllPathElements(const VofS& allPathElements,
                                                        const MetadataTextLocation& location,
                                                        PseudoFieldRef& pseudoFieldRef,
                                                        const bool expect)
{
    assert(!allPathElements.empty());

    if (this->_pseudoFieldRefFromAbsoluteAllPathElements(allPathElements, location, pseudoFieldRef, expect)) {
        return true;
    }

    if (this->_pseudoFieldRefFromRelativeAllPathElements(allPathElements, location, pseudoFieldRef, expect)) {
        return true;
    }

    if (expect) {
        throw MetadataParseError {"Invalid field reference.", location};
    }

    return false;
}

void TsdlParserBase::_addTypeAlias(const std::string& name,
                                   const PseudoDataType& type,
                                   const MetadataTextLocation& curLocation,
                                   _StackFrame& frame)
{
    assert(!name.empty());

    /*
     * Check for existing alias with this name. We only check in the
     * top frame of the lexical scope stack because a type alias with
     * a given name can shadow a deeper one with the same name in TSDL.
     */
    if (frame.typeAliases.find(name) != std::end(frame.typeAliases)) {
        std::ostringstream ss;

        ss << "Duplicate type alias: `" << name << "`.";
        throw MetadataParseError {ss.str(), curLocation};
    }

    // add alias
    frame.typeAliases[name] = type.clone();
}

void TsdlParserBase::_addTypeAlias(const std::string& name,
                                   const PseudoDataType& type,
                                   const MetadataTextLocation& curLocation)
{
    this->_addTypeAlias(name, type, curLocation, this->_stackTop());
}

PseudoDataType::UP TsdlParserBase::_getAliasedType(const std::string& name) const
{
    for (auto it = _stack.crbegin(); it != _stack.crend(); ++it) {
        const auto& frame = *it;
        const auto findIt = frame.typeAliases.find(name);

        if (findIt == std::end(frame.typeAliases)) {
            continue;
        }

        /*
         * The shallow clone is needed because a variant type
         * alias may not contain any tag yet.
         */
        return findIt->second->clone();
    }

    return nullptr;
}

DataType::UP TsdlParserBase::_dataTypeFromPseudoDataType(const PseudoDataType& pseudoDataType,
                                                         const Scope scope)
{
    _ResolvingStack stack;

    return TsdlParserBase::_dataTypeFromPseudoDataType(pseudoDataType, scope,
                                                       "", stack);
}

DataType::UP TsdlParserBase::_dataTypeFromPseudoDataType(const PseudoDataType& pseudoDataType,
                                                         const Scope scope,
                                                         const std::string &name,
                                                         _ResolvingStack& stack)
{
    switch (pseudoDataType.kind()) {
    case PseudoDataType::Kind::SCALAR_WRAPPER:
        return TsdlParserBase::_dataTypeFromPseudoScalarTypeWrapper(pseudoDataType, scope, stack);

    case PseudoDataType::Kind::ARRAY:
        return TsdlParserBase::_dataTypeFromPseudoArrayType(pseudoDataType, scope, name, stack);

    case PseudoDataType::Kind::SEQUENCE:
        return TsdlParserBase::_dataTypeFromPseudoSequenceType(pseudoDataType, scope, name, stack);

    case PseudoDataType::Kind::STRUCT:
        return TsdlParserBase::_dataTypeFromPseudoStructType(pseudoDataType, scope, name, stack);

    case PseudoDataType::Kind::VARIANT:
        return TsdlParserBase::_dataTypeFromPseudoVariantType(pseudoDataType, scope, name, stack);

    default:
        abort();
    }
}

FieldRef TsdlParserBase::_fieldRefFromPseudoFieldRef(const PseudoFieldRef& pseudoFieldRef,
                                                     const Scope scope,
                                                     _ResolvingStack& stack)
{
    assert(!pseudoFieldRef.isEnv);

    // if the pseudo field reference is already absolute, use it as is
    if (pseudoFieldRef.isAbsolute) {
        return FieldRef {pseudoFieldRef.scope, pseudoFieldRef.pathElements};
    }

    /*
     * Find the first path element in the field names of the resolving
     * stack, from top to bottom, and keep this iterator.
     */
    auto firstPathElemStackIt = std::cend(stack) - 1;
    const auto& pathElem = pseudoFieldRef.pathElements.front();

    while (true) {
        auto& frameFieldNames = firstPathElemStackIt->fieldNames;

        if (std::find(std::begin(frameFieldNames), std::end(frameFieldNames), pathElem) != std::end(frameFieldNames)) {
            // found it
            break;
        }

        /*
         * We can assert this because at this point the target field
         * must exist. This is checked by
         * _pseudoFieldRefFromRelativeAllPathElements() when also making
         * sure that the target does not cross a type alias boundary.
         */
        assert(firstPathElemStackIt != std::cbegin(stack));
        --firstPathElemStackIt;
    }

    /*
     * Now we go back from the stack's lowest frame and append the frame
     * names until we reach `firstPathElemStackIt` (including its name
     * because it is the container of the first path element).
     */
    VofS absPathElements;

    for (auto stackIt = std::cbegin(stack) + 1; stackIt != (firstPathElemStackIt + 1); ++stackIt) {
        assert(!stackIt->name.empty());
        absPathElements.push_back(stackIt->name);
    }

    // append remaining, relative path elements
    std::copy(std::begin(pseudoFieldRef.pathElements),
              std::end(pseudoFieldRef.pathElements),
              std::back_inserter(absPathElements));
    return FieldRef {scope, absPathElements};
}

DataType::UP TsdlParserBase::_dataTypeFromPseudoScalarTypeWrapper(const PseudoDataType& pseudoDataType,
                                                                  const Scope scope,
                                                                  _ResolvingStack& stack)
{
    auto& scalarType = static_cast<const PseudoScalarTypeWrapper&>(pseudoDataType);
    return scalarType.type->clone();
}


template <typename StdTypeT, typename TextTypeT, typename LengthT>
static DataType::UP dataTypeFromPseudoArrayOrSequenceType(DataType::UP elemType,
                                                          const LengthT& length)
{
    if (elemType->isIntType()) {
        auto intType = elemType->asIntType();

        if (intType->encoding() != Encoding::NONE &&
                intType->alignment() == 8 && intType->size() == 8) {
            return std::make_unique<const TextTypeT>(8, intType->encoding(), length);
        }
    }

    return std::make_unique<const StdTypeT>(1, std::move(elemType), length);
}

DataType::UP TsdlParserBase::_dataTypeFromPseudoArrayType(const PseudoDataType& pseudoDataType,
                                                          const Scope scope,
                                                          const std::string &name,
                                                          _ResolvingStack& stack)
{
    auto& arrayType = static_cast<const PseudoArrayType&>(pseudoDataType);
    auto elemType = TsdlParserBase::_dataTypeFromPseudoDataType(*arrayType.elementType,
                                                                scope, name, stack);
    return dataTypeFromPseudoArrayOrSequenceType<ArrayType, TextArrayType>(std::move(elemType), arrayType.length);
}

DataType::UP TsdlParserBase::_dataTypeFromPseudoSequenceType(const PseudoDataType& pseudoDataType,
                                                             const Scope scope,
                                                             const std::string &name,
                                                             _ResolvingStack& stack)
{
    auto& seqType = static_cast<const PseudoSequenceType&>(pseudoDataType);
    auto elemType = TsdlParserBase::_dataTypeFromPseudoDataType(*seqType.elementType,
                                                                scope, name, stack);
    auto fieldRef = TsdlParserBase::_fieldRefFromPseudoFieldRef(seqType.lengthFieldRef,
                                                                scope, stack);
    return dataTypeFromPseudoArrayOrSequenceType<SequenceType, TextSequenceType>(std::move(elemType), fieldRef);
}

DataType::UP TsdlParserBase::_dataTypeFromPseudoStructType(const PseudoDataType& pseudoDataType,
                                                           const Scope scope,
                                                           const std::string &name,
                                                           _ResolvingStack& stack)
{
    stack.push_back({name});

    StructTypeFields fields;
    auto& pseudoStructType = static_cast<const PseudoStructType&>(pseudoDataType);

    for (const auto& namedDataType : pseudoStructType.fields) {
        auto fieldType = TsdlParserBase::_dataTypeFromPseudoDataType(*namedDataType->type,
                                                                     scope, namedDataType->name,
                                                                     stack);
        fields.push_back(std::make_unique<const StructTypeField>(namedDataType->name,
                                                                 std::move(fieldType)));
        stack.back().fieldNames.push_back(namedDataType->name);
    }

    auto structType = std::make_unique<const StructType>(pseudoStructType.minAlignment, std::move(fields));

    stack.pop_back();
    return structType;
}

DataType::UP TsdlParserBase::_dataTypeFromPseudoVariantType(const PseudoDataType& pseudoDataType,
                                                            const Scope scope,
                                                            const std::string &name,
                                                            _ResolvingStack& stack)
{
    auto& pseudoVariantType = static_cast<const PseudoVariantType&>(pseudoDataType);
    auto tagFieldRef = TsdlParserBase::_fieldRefFromPseudoFieldRef(pseudoVariantType.tagFieldRef,
                                                                   scope, stack);

    stack.push_back({name});

    VariantTypeOptions options;

    for (const auto& namedDataType : pseudoVariantType.options) {
        auto optionType = TsdlParserBase::_dataTypeFromPseudoDataType(*namedDataType->type,
                                                                      scope, namedDataType->name,
                                                                      stack);
        options.push_back(std::make_unique<const VariantTypeOption>(namedDataType->name,
                                                                    std::move(optionType)));
        stack.back().fieldNames.push_back(namedDataType->name);
    }

    auto varType = std::make_unique<const VariantType>(1, std::move(options),
                                                       tagFieldRef);

    stack.pop_back();
    return varType;
}

std::unique_ptr<const DataStreamType> TsdlParserBase::_dataStreamTypeFromPseudoDataStreamType(const PseudoDataStreamType& pseudoDst)
{
    EventRecordTypeSet ertSet;

    for (const auto& idPseudoErtPair : pseudoDst.eventRecordTypes) {
        auto ert = TsdlParserBase::_eventRecordTypeFromPseudoEventRecordType(*idPseudoErtPair.second);

        ertSet.insert(std::move(ert));
    }

    DataType::UP packetContextType;
    DataType::UP eventRecordHeaderType;
    DataType::UP eventRecordContextType;

    if (pseudoDst.packetContextType) {
        packetContextType = TsdlParserBase::_dataTypeFromPseudoDataType(*pseudoDst.packetContextType,
                                                                        Scope::PACKET_CONTEXT);
    }

    if (pseudoDst.eventHeaderType) {
        eventRecordHeaderType = TsdlParserBase::_dataTypeFromPseudoDataType(*pseudoDst.eventHeaderType,
                                                                            Scope::EVENT_RECORD_HEADER);
    }

    if (pseudoDst.eventContextType) {
        eventRecordContextType = TsdlParserBase::_dataTypeFromPseudoDataType(*pseudoDst.eventContextType,
                                                                            Scope::EVENT_RECORD_FIRST_CONTEXT);
    }

    std::unique_ptr<const DataStreamType> dst;

    try {
        dst = std::make_unique<const DataStreamType>(pseudoDst.id,
                                                     std::move(ertSet),
                                                     std::move(packetContextType),
                                                     std::move(eventRecordHeaderType),
                                                     std::move(eventRecordContextType));
    } catch (const InvalidMetadata& ex) {
        MetadataParseError error {ex.what()};
        std::ostringstream ss;

        ss << "Invalid data stream type with ID " << pseudoDst.id << ":";
        error._appendErrorMessage(ss.str(), MetadataTextLocation {0, 0});
        throw error;
    }

    return dst;
}

std::unique_ptr<const EventRecordType> TsdlParserBase::_eventRecordTypeFromPseudoEventRecordType(const PseudoEventRecordType& pseudoErt)
{
    DataType::UP contextType;
    DataType::UP payloadType;

    if (pseudoErt.contextType) {
        contextType = TsdlParserBase::_dataTypeFromPseudoDataType(*pseudoErt.contextType,
                                                                  Scope::EVENT_RECORD_SECOND_CONTEXT);
    }

    if (pseudoErt.payloadType) {
        payloadType = TsdlParserBase::_dataTypeFromPseudoDataType(*pseudoErt.payloadType,
                                                                  Scope::EVENT_RECORD_PAYLOAD);
    }

    std::unique_ptr<const EventRecordType> ert;

    try {
        ert = std::make_unique<const EventRecordType>(pseudoErt.id, pseudoErt.name,
                                                      pseudoErt.logLevel,
                                                      pseudoErt.modelEmfUri,
                                                      std::move(contextType),
                                                      std::move(payloadType));
    } catch (const InvalidMetadata& ex) {
        MetadataParseError error {ex.what()};
        std::ostringstream ss;

        ss << "Invalid event record type with ID " << pseudoErt.id << ":";
        error._appendErrorMessage(ss.str(), MetadataTextLocation {0, 0});
        throw error;
    }

    return ert;
}

void PseudoTraceType::clear()
{
    majorVersion = 0;
    minorVersion = 0;
    defaultByteOrder = -1;
    uuid = boost::uuids::nil_generator {}();
    packetHeaderType = nullptr;
    env = nullptr;
    clockTypes.clear();
    dataStreamTypes.clear();
}

} // namespace internal
} // namespace yactfr
