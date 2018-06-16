/*
 * Choice of a CTF variant type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Choice of a CTF variant type.

@ingroup metadata_dt
*/

#ifndef _YACTFR_METADATA_VARIANT_TYPE_CHOICE_HPP
#define _YACTFR_METADATA_VARIANT_TYPE_CHOICE_HPP

// for std::string
#include <string>

// for std::vector
#include <vector>

// for std::unique_ptr
#include <memory>

// for NamedDataType
#include "named-data-type.hpp"

// for DataType
#include "data-type.hpp"

namespace yactfr {

/*!
@brief  Choice of a variant type (VariantType).

@ingroup metadata_dt
*/
class VariantTypeChoice final :
    public NamedDataType
{
public:
    /*!
    Builds a variant type's choice.

    @param name Choice's name.
    @param type Choice's data type.

    @throws InvalidMetadata The variant type's choice is invalid.
    */
    explicit VariantTypeChoice(const std::string& name, DataType::UP type);

    /*!
    Returns a clone, a deep copy of this variant type's choice.

    @returns    Clone of this variant type's choice.
    */
    std::unique_ptr<const VariantTypeChoice> clone() const;

    /*!
    @brief  Equality operator.

    @param otherChoice  Other variant type's choice to compare with.
    @returns            \c true if \p otherChoice is equal to this
                        variant type's choice.
    */
    bool operator==(const VariantTypeChoice& otherChoice) const
    {
        return NamedDataType::operator==(otherChoice);
    }

    /*!
    @brief  Non-equality operator.

    @param otherChoice   Other variant type's choice to compare with.
    @returns            \c true if \p otherChoice is not equal to this
                        variant type's choice.
    */
    bool operator!=(const VariantTypeChoice& otherChoice) const
    {
        return !(*this == otherChoice);
    }
};

/*!
@brief  Vector of variant type's choices.

@ingroup metadata_dt
*/
using VariantTypeChoices = std::vector<std::unique_ptr<const VariantTypeChoice>>;

} // namespace yactfr

#endif // _YACTFR_METADATA_VARIANT_TYPE_CHOICE_HPP
