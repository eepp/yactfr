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
    @param[in] type
        Data type of data stream structure members described by
        this type.
    */
    explicit StructureMemberType(std::string name, DataType::UP type);

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
    const DataType& type() const noexcept
    {
        return *_dt;
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
};

} // namespace yactfr

#endif // _YACTFR_METADATA_STRUCT_MEMBER_TYPE_HPP
