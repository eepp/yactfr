/*
 * Field resolver.
 *
 * This used to resolve relative paths within the metadata tree too, but
 * on 16 August 2017, after several hours of discussion with myself, the
 * decision was made to support only absolute paths within the model so
 * simplify the whole thing and hope to have a working yactfr library
 * before I die. This explains the name of this file,
 *
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_FIELD_RESOLVER_HPP
#define _YACTFR_METADATA_FIELD_RESOLVER_HPP

#include <utility>
#include <vector>
#include <functional>
#include <boost/utility.hpp>

#include <yactfr/aliases.hpp>
#include <yactfr/metadata/aliases.hpp>
#include <yactfr/metadata/fwd.hpp>
#include <yactfr/metadata/field-ref.hpp>
#include <yactfr/metadata/named-data-type.hpp>

namespace yactfr {
namespace internal {

/*
 * Field resolver.
 *
 * This resolver can find the path to a field from another field within
 * a metadata tree.
 */
class FieldResolver :
    private boost::noncopyable
{
public:
    struct Entry {
        const DataType *type = nullptr;
        const std::string *name = nullptr;
    };

    struct Result {
        Result() :
            ref {FieldRef {Scope::PACKET_HEADER, {}}}
        {
        }

        Result(const FieldRef& fieldRef, const DataType *type) :
            ref {fieldRef},
            type {type}
        {
        }

        FieldRef ref;
        const DataType *type = nullptr;
    };

public:
    using Position = std::vector<Index>;
    using Positions = std::vector<Position>;
    using GetEntryAtFn = std::function<Entry (const Scope, const Position&)>;

public:
    /*
     * Builds a field resolver.
     *
     * The `getEntryAtFn` function must return a field resolver entry
     * (field type and name) when called with a specific scope and
     * position. If the position parameter is empty, the entry to return
     * is the scope itself. The "current element" of arrays and
     * sequences is considered at index -1 of its container.
     */
    explicit FieldResolver(const GetEntryAtFn& getEntryAtFn) noexcept;

    /*
     * Resolves a field.
     *
     * `sourceScope` is the scope of the source, typically the sequence
     * or variant type which needs to find its length/tag position
     * (called the target).
     *
     * `sourcePos` is the exact, absolute position of the source from
     * the root of the source scope. If `sourcePos` is empty, the source
     * is the scope itself. The "current element" of arrays and
     * sequences is considered at index -1 of its container.
     *
     * `tgtFieldRef` is the field reference of the target to resolve.
     *
     * Returns a validated field reference and (target) data type. The
     * data type is \c nullptr if the field cannot be resolved for any
     * reason. In the returned field reference, arrays and sequences
     * must be skipped (their element is not named).
     *
     * It is guaranteed that the target can, at least in one specific
     * configuration, be reached from its source during the decoding
     * process. The real availability of a target depends on the current
     * variant selections (if any) during the decoding process.
     */
    Result resolve(const Scope sourceScope, const Position& sourcePos,
                   const FieldRef& tgtFieldRef) const;

private:
    enum class Order {
        BEFORE,
        SAME,
        AFTER,
    };

private:
    Result _resolveAbsolute(const Scope sourceScope,
                            const Position& sourcePos,
                            const FieldRef& tgtFieldRef) const;
    Result _resultFromAbsPos(const Scope scope, const Position& pos) const;
    Order _posOrder(const Scope baseScope, const Position& basePos,
                    const Scope scope, const Position& pos) const;
    Scope _scopeFromPrefix(const std::string& prefix) const;
    Position _lcaPos(const Position& pos1, const Position& pos2) const;
    bool _validateAbsolutePos(const Scope sourceScope, const Position& sourcePos,
                              const Scope tgtScope, const Position& tgtPos) const;
    bool _forwardSearchRec(const Scope scope, const Position& parentPos,
                           const std::vector<std::string>& pathElements,
                           Position& result) const;
    bool _forwardSearch(const Scope scope, const Position& parentPos,
                        const std::vector<std::string>& pathElements,
                        Position& result) const;

private:
    const GetEntryAtFn _getEntryAtFn;
};

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_METADATA_FIELD_RESOLVER_HPP
