/*
 * CTF variant type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Variant type.

@ingroup metadata_dt
*/

#ifndef _YACTFR_METADATA_VARIANT_TYPE_HPP
#define _YACTFR_METADATA_VARIANT_TYPE_HPP

// for std::string
#include <string>

// for StructVariantTypeBase
#include "struct-variant-type-base.hpp"

// for FieldRef
#include "field-ref.hpp"

// for VariantTypeChoice
#include "variant-type-choice.hpp"

// for DataType
#include "data-type.hpp"

// for DataTypeVisitor
#include "data-type-visitor.hpp"

// for Index
#include "../aliases.hpp"

namespace yactfr {

/*!
@brief  Variant type.

@ingroup metadata_dt

A structure type describes data stream variants.
*/
class VariantType final :
    public StructVariantTypeBase<VariantTypeChoice>
{
public:
    /// Field reference of the tag of data stream variants described
    /// by this variant type.
    const FieldRef& tag() const noexcept
    {
        return _tag;
    }

    /// Choices offered by this variant type.
    const VariantTypeChoices& choices() const noexcept
    {
        return this->_entries();
    }

    /// Choice iterator set at the first choice of this variant type.
    VariantTypeChoices::const_iterator begin() const noexcept
    {
        return this->_begin();
    }

    /// Choice iterator set \em after the last choice of this
    /// variant type.
    VariantTypeChoices::const_iterator end() const noexcept
    {
        return this->_end();
    }

    /*!
    @brief  Checks whether or not this variant type has a choice
            at index \p index.

    @param index    Index to check.
    @returns        \c true if this variant type has a choice at
                    index \p index.
    */
    bool hasChoice(const Index index) const
    {
        return this->_hasEntry(index);
    }

    /*!
    @brief  Checks whether or not this variant type has a choice
            named \p name.

    @param name Name to check.
    @returns    \c true if this variant type has a choice named \p name.
    */
    bool hasChoice(const std::string& name) const
    {
        return this->_hasEntry(name);
    }

    /*!
    @brief  Finds a choice by index.

    @param index    Index of choice to find.
    @returns        Field at index \p index.

    @throws NoSuchIndex There's no choice at index \p index.
    */
    const VariantTypeChoice& operator[](const Index index) const
    {
        return StructVariantTypeBase<VariantTypeChoice>::operator[](index);
    }

    /*!
    @brief  Finds a choice by name.

    @param name Name of choice to find.
    @returns    Field named \p name.

    @throws NoSuchName There's no choice named \p name.
    */
    const VariantTypeChoice& operator[](const std::string& name) const
    {
        return StructVariantTypeBase<VariantTypeChoice>::operator[](name);
    }

    /*!
    @brief  Finds a choice by exact name and returns its type, returning
            \c nullptr if the choice is not found not found.

    @param choiceName   Name of the choice to find.
    @returns            Type of the choice named \p name or nullptr if no
                        choice was found.

    @sa findTypeByDisplayName() Finds a choice by display name and
                                returns its type.
    */
    const DataType *findType(const std::string& choiceName) const
    {
        return this->_findEntryType(choiceName);
    }

    /*!
    @brief  Finds a choice by display name and returns its type,
            returning \c nullptr if the choice is not found not found.

    @param dispName     Display name of the choice to find.
    @returns            Type of the choice of which the display name is
                        \p name or nullptr if no choice was found.

    @sa findType(): Finds a choice by exact name and returns its type.
    */
    const DataType *findTypeByDisplayName(const std::string& dispName) const
    {
        return this->_findEntryTypeByDisplayName(dispName);
    }

    // This is placed here because, for some reason, Doxygen doesn't
    // like this constructor at the top. Why? Goodness only knows.

    /*!
    @brief  Builds a variant type.

    @param align    Alignment of data stream variants described by this
                    variant type (power of two, greater than 0).
    @param choices  Variant type's choices (moved to this new variant type).
    @param tag      Tag field reference.

    @throws InvalidMetadata The variant type is invalid.
    */
    explicit VariantType(unsigned int align, VariantTypeChoices&& choices,
                         const FieldRef& tag);

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    bool _compare(const DataType& otherType) const override;

private:
    const FieldRef _tag;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_VARIANT_TYPE_HPP
