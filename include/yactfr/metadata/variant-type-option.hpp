/*
 * Option of a CTF variant type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Option of a CTF variant type.

@ingroup metadata_dt
*/

#ifndef _YACTFR_METADATA_VARIANT_TYPE_OPTION_HPP
#define _YACTFR_METADATA_VARIANT_TYPE_OPTION_HPP

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
@brief  Option of a variant type (VariantType).

@ingroup metadata_dt
*/
class VariantTypeOption final :
    public NamedDataType
{
public:
    /*!
    Builds a variant type's option.

    @param name Option's name.
    @param type Option's data type.

    @throws InvalidMetadata The variant type's option is invalid.
    */
    explicit VariantTypeOption(const std::string& name, DataType::UP type);

    /*!
    Returns a clone, a deep copy of this variant type's option.

    @returns    Clone of this variant type's option.
    */
    std::unique_ptr<const VariantTypeOption> clone() const;

    /*!
    @brief  Equality operator.

    @param otherOption  Other variant type's option to compare with.
    @returns            \c true if \p otherOption is equal to this
                        variant type's option.
    */
    bool operator==(const VariantTypeOption& otherOption) const
    {
        return NamedDataType::operator==(otherOption);
    }

    /*!
    @brief  Non-equality operator.

    @param otherOption   Other variant type's option to compare with.
    @returns            \c true if \p otherOption is not equal to this
                        variant type's option.
    */
    bool operator!=(const VariantTypeOption& otherOption) const
    {
        return !(*this == otherOption);
    }
};

/*!
@brief  Vector of variant type's options.

@ingroup metadata_dt
*/
using VariantTypeOptions = std::vector<std::unique_ptr<const VariantTypeOption>>;

} // namespace yactfr

#endif // _YACTFR_METADATA_VARIANT_TYPE_OPTION_HPP
