/*
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_STRUCT_MEMBER_TYPE_HPP
#define _YACTFR_METADATA_STRUCT_MEMBER_TYPE_HPP

#include <string>
#include <boost/noncopyable.hpp>

#include "dt.hpp"
#include "item.hpp"

namespace yactfr {

/*!
@brief
    Structure member type.

A structure member type describes members of data stream structures (as
decribed by \link StructureType structure types\endlink).

@ingroup metadata_dt
*/
class StructureMemberType final :
    boost::noncopyable
{
public:
    /*!
    @brief
        Builds a structure member type.

    @param[in] name
        Name of data stream structure members described by this type.
    @param[in] dataType
        Data type of data stream structure members described by
        this type.
    @param[in] userAttributes
        @parblock
        User attributes of data stream structure members described by
        this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock

    @pre
        \p dataType is set.
    */
    explicit StructureMemberType(std::string name, DataType::UP dataType,
                                 MapItem::UP userAttributes = nullptr);

    /// Name of data stream structure members described by this type.
    const std::string& name() const noexcept
    {
        return _name;
    }

    /// Display name (name() with first underscore removed, if any)
    /// of data stream structure members described by this type.
    const std::string& displayName() const noexcept
    {
        return _dispName;
    }

    /// Data type of data stream structure members described by
    /// this type.
    const DataType& dataType() const noexcept
    {
        return *_dt;
    }

    /*!
    @brief
        User attributes.

    If set, each key of \p *userAttributes is a namespace.

    @note
        Even if the return value isn't \c nullptr, the returned map
        item may still be empty (which also means no user attributes).
    */
    const MapItem *userAttributes() const noexcept
    {
        return _userAttrs.get();
    }

    /*!
    @brief
        Clones this structure member type and returns it.

    @returns
        Clone of this structure member type.
    */
    std::unique_ptr<const StructureMemberType> clone() const;

    /*!
    @brief
        Equality operator.

    @param[in] other
        Other structure member type to compare to.

    @returns
        \c true if \p other is equal to this structure member type.
    */
    bool operator==(const StructureMemberType& other) const noexcept;

    /*!
    @brief
        Non-equality operator.

    @param[in] other
        Other structure member type to compare to.

    @returns
        \c true if \p other is not equal to this structure member type.
    */
    bool operator!=(const StructureMemberType& other) const noexcept
    {
        return !(*this == other);
    }

private:
    const std::string _dispName;
    const std::string _name;
    const DataType::UP _dt;
    const MapItem::UP _userAttrs;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_STRUCT_MEMBER_TYPE_HPP
