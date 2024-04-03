/*
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_MMAP_FILE_VIEW_FACTORY_HPP
#define YACTFR_MMAP_FILE_VIEW_FACTORY_HPP

#include <memory>
#include <boost/noncopyable.hpp>
#include <string>

#include "data-src-factory.hpp"
#include "aliases.hpp"

namespace yactfr {
namespace internal {

class MmapFileViewFactoryImpl;

} // namespace internal

/*!
@brief
    Memory mapped file view factory.

@ingroup element_seq

This is a factory of memory mapped file views, which are valid data
sources for element sequences.

All the memory mapped file views that such a factory creates operate on
the same file handle/descriptor.
*/
class MemoryMappedFileViewFactory final :
    public DataSourceFactory,
    boost::noncopyable
{
public:
    /*!
    @brief
        Memory map access pattern.
    */
    enum class AccessPattern {
        /// No special treatment.
        Normal,

        /// Expect page references in sequential order (more read ahead).
        Sequential,

        /// Expect page references in random order (less read ahead).
        Random,
    };

public:
    /*!
    @brief
        Creates a memory mapped file view factory which can create
        memory mapped file views on the file located at \p path.

    \p preferredMmapSize is the preferred size, in bytes, of each
    individual memory map operations performed by the memory map file
    views which this factory creates. The actual memory map size can be
    larger than \p preferredMmapSize if the platform imposes a minimum
    size. The actual memory map size can also be smaller than
    \p preferredMmapSize.

    \p expectedAccessPattern controls how the memory maps which the
    data sources of this factory are optimized. Prefer
    AccessPattern::Sequential if you're going to iterate whole packets
    in order. Prefer AccessPattern::Random if you're going to skip many
    elements and seek packets.

    This factory can throw IOError on construction and when creating a
    data source. Its created data source can throw IOError when getting
    a new data block.

    @param[in] path
        Path of the file on which to create memory mapped file views.
    @param[in] preferredMmapSize
        Preferred maximum size (bytes) of each memory map operation, or
        \c boost::none to let the implementation decide.
    @param[in] expectedAccessPattern
        Expected access pattern of the memory mapped file views created
        by this factory.

    @throws IOError
        An I/O error occurred (file not found, permission denied, etc.).
    */
    explicit MemoryMappedFileViewFactory(std::string path,
                                         const boost::optional<Size>& preferredMmapSize = boost::none,
                                         AccessPattern expectedAccessPattern = AccessPattern::Normal);

    /// Current expected access pattern for future memory maps.
    AccessPattern expectedAccessPattern() const noexcept;

    /*!
    @brief
        Sets the current expected access pattern for future memory maps
        to \p expectedAccessPattern.

    Note that this setting only applies to memory map operations
    performed \em after this call, by any data source created by this
    factory.

    @param[in] expectedAccessPattern
        Expected access pattern of the memory mapped file views created
        by this factory.
    */
    void expectedAccessPattern(AccessPattern expectedAccessPattern) noexcept;

private:
    DataSource::Up _createDataSource() override;

private:
    /*
     * Shared because memory mapped file views also keep a reference to
     * keep the file descriptor opened.
     */
    std::shared_ptr<internal::MmapFileViewFactoryImpl> _pimpl;
};

} // namespace yactfr

#endif // YACTFR_MMAP_FILE_VIEW_FACTORY_HPP
