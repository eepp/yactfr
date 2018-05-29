/*
 * CTF structure type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Structure type.

@ingroup metadata_dt
*/

#ifndef _YACTFR_METADATA_STRUCT_TYPE_HPP
#define _YACTFR_METADATA_STRUCT_TYPE_HPP

#include <memory>
#include <algorithm>

#include <yactfr/aliases.hpp>

#include "struct-variant-type-base.hpp"
#include "struct-type-field.hpp"
#include "data-type-visitor.hpp"

namespace yactfr {

/*!
@brief  Structure type.

@ingroup metadata_dt

A structure type describes data stream structures.
*/
class StructType final :
    public StructVariantTypeBase<StructTypeField>
{
public:
    /*!
    @brief  Builds a structure type.

    @param minAlign Minimal alignment of data stream structures
                    described by this structure type (power of two,
                    greater than 0).
    @param fields   Fields of the structure type (moved to this
                    new structure type).

    @throws InvalidMetadata The string type is invalid.
    */
    explicit StructType(unsigned int minAlign, StructTypeFields&& fields);

    /// Fields contained in this structure type.
    const StructTypeFields& fields() const noexcept
    {
        return this->_entries();
    }

    /// Field iterator set at the first field of this structure type.
    StructTypeFields::const_iterator begin() const noexcept
    {
        return this->_begin();
    }

    /// Field iterator set \em after the last field of this structure type.
    StructTypeFields::const_iterator end() const noexcept
    {
        return this->_end();
    }

    /*!
    @brief  Checks whether or not this structure type has a field
            at index \p index.

    @param index    Index to check.
    @returns        \c true if this structure type has a field at
                    index \p index.
    */
    bool hasField(const Index index) const
    {
        return this->_hasEntry(index);
    }

    /*!
    @brief  Checks whether or not this structure type has a field
            named \p name.

    @param name Name to check.
    @returns    \c true if this structure type has a field named \p name.
    */
    bool hasField(const std::string& name) const
    {
        return this->_hasEntry(name);
    }

    /*!
    @brief  Finds a field by index.

    @param index    Index of field to find.
    @returns        Field at index \p index.

    @throws NoSuchIndex There's no field at index \p index.
    */
    const StructTypeField& operator[](Index index) const
    {
        return StructVariantTypeBase<StructTypeField>::operator[](index);
    }

    /*!
    @brief  Finds a field by name.

    @param name Name of field to find.
    @returns    Field named \p name.

    @throws NoSuchName There's no field named \p name.
    */
    const StructTypeField& operator[](const std::string& name) const
    {
        return StructVariantTypeBase<StructTypeField>::operator[](name);
    }

    /*!
    @brief  Finds a field by exact name and returns its type, returning
            \c nullptr if the field is not found not found.

    @param fieldName    Name of the field to find.
    @returns            Type of the field named \p name or nullptr if no
                        field was found.

    @sa findTypeByDisplayName(): Finds a field by display name and
                                 returns its type.
    */
    const DataType *findType(const std::string& fieldName) const
    {
        return this->_findEntryType(fieldName);
    }

    /*!
    @brief  Finds a field by display name and returns its type,
            returning \c nullptr if the field is not found not found.

    @param dispName     Display name of the field to find.
    @returns            Type of the field of which the display name is
                        \p name or nullptr if no field was found.

    @sa findType(): Finds a field by exact name and returns its type.
    */
    const DataType *findTypeByDisplayName(const std::string& dispName) const
    {
        return this->_findEntryTypeByDisplayName(dispName);
    }

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    bool _compare(const DataType& otherType) const override;
    void _setRealAlign();
};

} // namespace yactfr

#endif // _YACTFR_METADATA_STRUCT_TYPE_HPP
