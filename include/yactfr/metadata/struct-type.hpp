/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_STRUCT_TYPE_HPP
#define _YACTFR_METADATA_STRUCT_TYPE_HPP

#include <cassert>
#include <string>
#include <vector>
#include <unordered_map>

#include "compound-dt.hpp"
#include "struct-member-type.hpp"
#include "dt.hpp"
#include "dt-visitor.hpp"
#include "../aliases.hpp"

namespace yactfr {

/*!
@brief
    Structure type.

@ingroup metadata_dt

A structure type describes data stream structures.
*/
class StructureType final :
    public CompoundDataType
{
public:
    /// Unique pointer to constant structure type.
    using UP = std::unique_ptr<const StructureType>;

    /// Map of member names to member types.
    using NamesToMemberTypes = std::unordered_map<std::string, const StructureMemberType *>;

    /// Member types.
    using MemberTypes = std::vector<std::unique_ptr<const StructureMemberType>>;

public:
    /*!
    @brief
        Builds a structure type.

    @param[in] minimumAlignment
        Minimum alignment of data stream structures described by this
        type.
    @param[in] memberTypes
        Member types of the structure type (moved to this type).
    @param[in] userAttributes
        @parblock
        User attributes of data stream structures described by this
        type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock

    @pre
        \p minimumAlignment > 0.
    @pre
        \p minimumAlignment is a power of two.
    */
    explicit StructureType(unsigned int minimumAlignment, MemberTypes&& memberTypes,
                           MapItem::UP userAttributes = nullptr);

    /*!
    @brief
        Builds a structure type having a default minimum alignment
        property (1).

    @param[in] memberTypes
        Member types of the structure type (moved to this type).
    @param[in] userAttributes
        @parblock
        User attributes of data stream structures described by this
        type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock
    */
    explicit StructureType(MemberTypes&& memberTypes, MapItem::UP userAttributes = nullptr);

    /// Member types contained in this structure type.
    const MemberTypes& memberTypes() const noexcept
    {
        return _memberTypes;
    }

    /// Member type iterator set at the first member type of this type.
    MemberTypes::const_iterator begin() const noexcept
    {
        return _memberTypes.begin();
    }

    /// Member type iterator set \em after the last member type of
    /// this type.
    MemberTypes::const_iterator end() const noexcept
    {
        return _memberTypes.end();
    }

    /// Number of member types this type has.
    Size size() const noexcept
    {
        return _memberTypes.size();
    }

    /*!
    @brief
        Returns the member type at the index \p index.

    @param[in] index
        Index of the member type to return.

    @returns
        Member type at the index \p index.

    @pre
        \p index < <code>size()</code>
    */
    const StructureMemberType& operator[](const Index index) const noexcept
    {
        assert(index < _memberTypes.size());
        return *_memberTypes[index];
    }

    /*!
    @brief
        Returns the member type named \p name, or \c nullptr if not
        found.

    @param[in] name
        Name of the member type to find.

    @returns
        Member type named \p name, or \c nullptr if not found.
    */
    const StructureMemberType *operator[](const std::string& name) const noexcept;

    /*!
    @brief
        Returns the member type having the display name \p displayName,
        or \c nullptr if not found.

    @param[in] displayName
        Display name of the member type to find.

    @returns
        Member type having the display name \p displayName,
        or \c nullptr if not found.
    */
    const StructureMemberType *memberTypeByDisplayName(const std::string& displayName) const noexcept;

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    bool _isEqual(const DataType& other) const noexcept override;
    void _initNamesToMemberTypes();

private:
    const MemberTypes _memberTypes;
    NamesToMemberTypes _namesToMemberTypes;
    NamesToMemberTypes _dispNamesToMemberTypes;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_STRUCT_TYPE_HPP
