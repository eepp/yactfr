/*
 * Field of a CTF structure type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Field of a CTF structure type.

@ingroup metadata_dt
*/

#ifndef _YACTFR_METADATA_STRUCT_TYPE_FIELD_HPP
#define _YACTFR_METADATA_STRUCT_TYPE_FIELD_HPP

#include <string>
#include <vector>

#include "named-data-type.hpp"
#include "fwd.hpp"

namespace yactfr {

/*!
@brief  Field of a structure type (StructType).

@ingroup metadata_dt
*/
class StructTypeField final :
    public NamedDataType
{
public:
    /*!
    Builds a structure type's field.

    @param name Field's name.
    @param type Field's data type.

    @throws InvalidMetadata The structure type's field is invalid.
    */
    explicit StructTypeField(const std::string& name, DataType::UP type);

    /*!
    Returns a clone, a deep copy of this structure type's field.

    @returns    Clone of this structure type's field.
    */
    std::unique_ptr<const StructTypeField> clone() const;

    /*!
    @brief  Equality operator.

    @param otherField   Other structure type's field to compare with.
    @returns            \c true if \p otherField is equal to this
                        structure type's field.
    */
    bool operator==(const StructTypeField& otherField) const
    {
        return NamedDataType::operator==(otherField);
    }

    /*!
    @brief  Non-equality operator.

    @param otherField   Other structure type's field to compare with.
    @returns            \c true if \p otherField is not equal to this
                        structure type's field.
    */
    bool operator!=(const StructTypeField& otherField) const
    {
        return !(*this == otherField);
    }
};

/*!
@brief  Vector of structure type's fields.

@ingroup metadata_dt
*/
using StructTypeFields = std::vector<std::unique_ptr<const StructTypeField>>;

} // namespace yactfr

#endif // _YACTFR_METADATA_STRUCT_TYPE_FIELD_HPP
