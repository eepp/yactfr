/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_DATA_LOC_HPP
#define _YACTFR_METADATA_DATA_LOC_HPP

#include <vector>
#include <string>

#include "../aliases.hpp"
#include "scope.hpp"

namespace yactfr {

/*!
@brief
    Data location.

@ingroup metadata

A data location is a scope and a sequence of structure member names to
follow to reach a specific datum within this scope. It is used to find
which datum in a given data stream indicates:

- The lengths of dynamic arrays
  (described by \link DynamicArrayType dynamic array types\endlink).

- The selectors of variants (described by
  \link VariantType variant types\endlink).

You can also use a data location for general data searching with
TraceType::findDataType(), DataStreamType::findDataType(), and
EventRecordType::findDataType().
*/
class DataLocation final
{
public:
    /// Vector of path elements.
    using PathElements = std::vector<std::string>;

public:
    /*!
    @brief
        Builds a data location, copying the path elements
        \p pathElements.

    @param[in] scope
        Scope.
    @param[in] pathElements
        Names of the structure members to follow from \p scope to reach
        the target (copied). If this is empty, then the scope itself is
        the target.
    */
    explicit DataLocation(Scope scope, const PathElements& pathElements);

    /*!
    @brief
        Builds a data location, moving the path elements
        \p pathElements.

    @param[in] scope
        Scope.
    @param[in] pathElements
        Names of the structure members to follow from \p scope to reach
        the target (moved). If this is empty, then the scope itself is
        the target.
    */
    explicit DataLocation(Scope scope, PathElements&& pathElements);

    /// Default copy constructor.
    DataLocation(const DataLocation&) = default;

    /// Default move constructor.
    DataLocation(DataLocation&&) = default;

    /// Default copy assignment operator.
    DataLocation& operator=(const DataLocation&) = default;

    /// Default move assignment operator.
    DataLocation& operator=(DataLocation&&) = default;

    /// Scope of this data location.
    Scope scope() const noexcept
    {
        return _scope;
    }

    /// Names of the structure members to follow from scope() to reach
    /// the target.
    const PathElements& pathElements() const noexcept
    {
        return _pathElems;
    }

    /// Path element iterator set at the first path element of this data
    /// location.
    PathElements::const_iterator begin() const noexcept
    {
        return _pathElems.begin();
    }

    /// Path element iterator set \em after the last path element of
    /// this data location.
    PathElements::const_iterator end() const noexcept
    {
        return _pathElems.end();
    }

    /// Number of path elements this data location has.
    Size size() const noexcept
    {
        return _pathElems.size();
    }

    /*!
    @brief
        Returns the path element at the index \p index.

    @param[in] index
        Index of the path element to return.

    @returns
        Path element at the index \p index.

    @pre
        \p index < <code>pathElements().size()</code>
    */
    const std::string& operator[](Index index) const
    {
        return _pathElems[index];
    }

    /*!
    @brief
        Equality operator.

    @param[in] other
        Other data location to compare to.

    @returns
        \c true if \p other is equal to this data location.
    */
    bool operator==(const DataLocation& other) const;

private:
    Scope _scope;
    PathElements _pathElems;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_DATA_LOC_HPP
