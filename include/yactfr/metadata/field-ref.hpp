/*
 * CTF (absolute) field reference.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Field reference.

@ingroup metadata
*/

#ifndef _YACTFR_METADATA_FIELD_REF_HPP
#define _YACTFR_METADATA_FIELD_REF_HPP

#include <vector>
#include <memory>
#include <string>

#include "metadata-base.hpp"
#include "aliases.hpp"
#include "scope.hpp"

namespace yactfr {

/*!
@brief  Field reference.

@ingroup metadata

A field reference is a scope and a sequence of field names to follow to
reach a specific field within this scope. It is used to find which field
in the metadata tree indicates the length of sequences (described by
SequenceType) and variants (described by VariantType), and also for
general searching with TraceType::findDataType(),
DataStreamType::findDataType(), and EventRecordType::findDataType().
*/
class FieldRef final :
    public MetadataBase
{
public:
    /*!
    @brief  Builds a field reference.

    @param scope        Scope.
    @param pathElements Names of the fields to follow from \p scope
                        to reach the target. If this is empty, then the
                        root scope itself is the target.
    */
    explicit FieldRef(Scope scope,
                      const std::vector<std::string>& pathElements);

    /*!
    @brief  Builds a field reference, moving the passed path elements.

    @param scope        Scope.
    @param pathElements Names of the fields to follow from \p scope
                        to reach the target. If this is empty, then the
                        root scope itself is the target. This vector
                        is moved to the new field reference.
    */
    explicit FieldRef(Scope scope,
                      std::vector<std::string>&& pathElements);

    /*!
    @brief  Copy constructor.

    @param fieldRef Field reference to copy.
    */
    FieldRef(const FieldRef& fieldRef);

    /*!
    @brief  Move constructor.

    @param fieldRef Field reference to move.
    */
    FieldRef(FieldRef&& fieldRef);

    /// Scope of this field reference.
    Scope scope() const noexcept
    {
        return _scope;
    }

    /*!
    @brief  Names of the fields to follow from scope() to reach
            the target.
    */
    const std::vector<std::string>& pathElements() const noexcept
    {
        return _pathElements;
    }

    /*!
    @brief  Equality operator.

    @param otherFieldRef    Other field reference to compare with.
    @returns                \c true if \p otherFieldRef is equal to
                            this data type.
    */
    bool operator==(const FieldRef& otherFieldRef) const;

private:
    const Scope _scope;
    const std::vector<std::string> _pathElements;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_FIELD_REF_HPP
