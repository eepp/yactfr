/*
 * Decoding error.
 *
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Packet sequence iterator.

@ingroup packet_seq
*/

#ifndef _YACTFR_DECODING_ERROR_HPP
#define _YACTFR_DECODING_ERROR_HPP

// for std::runtime_error
#include <stdexcept>

// for std::string
#include <string>

// for Index
#include "aliases.hpp"

namespace yactfr {
namespace internal {

    class Vm;

} // namespace internal

/*!
@brief  Decoding error.

This is thrown when there's an error in the decoding process of a packet
sequence (PacketSequenceIterator::operator++()).
*/
class DecodingError final :
    public std::runtime_error
{
public:
    explicit DecodingError(const std::string& reason, Index offset);

    /// Reason of the error.
    const std::string& reason() const noexcept
    {
        return _reason;
    }

    /*!
    @brief  Offset (bits) from the beginning of the packet sequence
            which created this iterator.
    */
    Index offset() const noexcept
    {
        return _offset;
    }

private:
    std::string _reason;
    Index _offset;
};

} // namespace yactfr

#endif // _YACTFR_DECODING_ERROR_HPP
