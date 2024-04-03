/*
 * Copyright (C) 2015-2023 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_METADATA_CLK_TYPE_HPP
#define YACTFR_METADATA_CLK_TYPE_HPP

#include <string>
#include <memory>
#include <utility>
#include <boost/core/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/uuid/uuid.hpp>

#include "aliases.hpp"
#include "clk-offset.hpp"
#include "clk-orig.hpp"
#include "clk-value-interval.hpp"
#include "item.hpp"

namespace yactfr {

/*!
@brief
    Clock type.

@ingroup metadata

A clock type describes data stream clocks.
*/
class ClockType final :
    boost::noncopyable
{
public:
    /// Unique pointer to constant clock type.
    using Up = std::unique_ptr<const ClockType>;

public:
    /*!
    @brief
        Builds a clock type.

    @param[in] internalId
        ID internal to the trace type containing this type.
    @param[in] nameSpace
        Namespace of data stream clocks described by this type.
    @param[in] name
        Name of data stream clocks described by this type.
    @param[in] uid
        Unique ID of data stream clocks described by this type.
    @param[in] originalUuid
        @parblock
        Original UUID of data stream clocks described by this type.

        This is only relevant when the TraceType::majorVersion() method
        for the trace type which will contain this clock type
        will return&nbsp;1.
        @endparblock
    @param[in] frequency
        Frequency (Hz) of data stream clocks described by this type.
    @param[in] description
        Description.
    @param[in] origin
        Origin of data stream clocks described by this type, or
        \c boost::none if the origin is unknown.
    @param[in] precision
        Precision (cycles) of data stream clocks described by this type,
        or \c boost::none if the precision is unknown.
    @param[in] accuracy
        Accuracy (cycles) of data stream clocks described by this type,
        or \c boost::none if the accuracy is unknown.
    @param[in] offsetFromOrigin
        Offset from origin of data stream clocks described by this type.
    @param[in] attributes
        @parblock
        Attributes of data stream clocks described by this type.

        If set, each key of \p *attributes is a namespace.
        @endparblock

    @pre
        \p frequency is greater than 0.
    @pre
        <code>offset.cycles()</code> is less than \p frequency.
    */
    explicit ClockType(boost::optional<std::string> internalId,
                       boost::optional<std::string> nameSpace,
                       boost::optional<std::string> name,
                       boost::optional<std::string> uid,
                       boost::optional<boost::uuids::uuid> originalUuid,
                       unsigned long long frequency, boost::optional<std::string> description,
                       boost::optional<ClockOrigin> origin, boost::optional<Cycles> precision,
                       boost::optional<Cycles> accuracy, const ClockOffset& offsetFromOrigin,
                       MapItem::Up attributes = nullptr);

    /*!
    @brief
        Creates a constant clock type unique pointer, forwarding \p args
        to the constructor.

    @param[in] args
        Arguments to forward to the clock type constructor.

    @returns
        Created constant clock type unique pointer.

    @pre
        See the preconditions of the constructor.
    */
    template <typename... ArgTs>
    static Up create(ArgTs&&... args)
    {
        return std::make_unique<Up::element_type>(std::forward<ArgTs>(args)...);
    }

    /// ID internal to the trace type containing this type.
    const boost::optional<std::string>& internalId() const noexcept
    {
        return _id;
    }

    /// Namespace of data stream clocks described by this type.
    const boost::optional<std::string>& nameSpace() const noexcept
    {
        return _ns;
    }

    /// Name of data stream clocks described by this type.
    const boost::optional<std::string>& name() const noexcept
    {
        return _name;
    }

    /// Unique ID of data stream clocks described by this type.
    const boost::optional<std::string>& uid() const noexcept
    {
        return _uid;
    }

    /*!
    @brief
        Original UUID of data stream clocks described by this type.

    This is only relevant when the TraceType::majorVersion() method for
    the trace type containing this clock type returns&nbsp;1.
    */
    const boost::optional<boost::uuids::uuid>& originalUuid() const noexcept
    {
        return _origUuid;
    }

    /// Frequency (Hz) of data stream clocks described by this type.
    unsigned long long frequency() const noexcept
    {
        return _freq;
    }

    /*!
    @brief
        Origin of data stream clocks described by this type, or
        \c boost::none if the origin is unknown.
    */
    const boost::optional<ClockOrigin>& origin() const noexcept
    {
        return _orig;
    }

    /// Description.
    const boost::optional<std::string>& description() const noexcept
    {
        return _descr;
    }

    /*!
    @brief
        Precision (cycles) of data stream clocks described by this type
        (\c boost::none means unknown).
    */
    const boost::optional<Cycles>& precision() const noexcept
    {
        return _prec;
    }

    /*!
    @brief
        Accuracy (cycles) of data stream clocks described by this type
        (\c boost::none means unknown).
    */
    const boost::optional<Cycles>& accuracy() const noexcept
    {
        return _accuracy;
    }

    /// Offset from origin of data stream clocks described by this type.
    const ClockOffset& offsetFromOrigin() const noexcept
    {
        return _offsetFromOrig;
    }

    /*!
    @brief
        Returns the interval of possible \em true data stream clock
        values for a given value \p cycles considering the precision
        (precision()) and accuracy (accuracy()) of data stream clocks
        described by this type.

    @param[in] value
        Data stream clock value for which to get the interval of
        possible true values considering the precision and accuracy
        of this clock type.

    @returns
        Interval of possible values for \p cycles considering the
        precision of this clock type.

    @pre
        Both the precision() and accuracy() methods for this clock type
        return a value.
    */
    ClockValueInterval clockValueInterval(Cycles value) const noexcept;

    /*!
    @brief
        Returns \c true if the clock type \p other has the same identity
        as this clock type.

    @param[in] other
        Other clock type to compare to.

    @returns
        \c true if \p other has the same identity as this clock type.
    */
    bool hasSameIdentity(const ClockType& other) const noexcept
    {
        if (_ns != other._ns) {
            return false;
        }

        if (_name && other._name && *_name != *other._name) {
            return false;
        }

        if (_uid && other._uid && *_uid != *other._uid) {
            return false;
        }

        return true;
    }

    /*!
    @brief
        Attributes.

    If set, each key of the returned map item is a namespace.

    @note
        Even if the return value isn't \c nullptr, the returned map
        item may still be empty (which also means no attributes).
    */
    const MapItem *attributes() const noexcept
    {
        return _attrs.get();
    }

private:
    const boost::optional<std::string> _id;
    const boost::optional<std::string> _ns;
    const boost::optional<std::string> _name;
    const boost::optional<std::string> _uid;
    boost::optional<boost::uuids::uuid> _origUuid;
    const unsigned long long _freq;
    const boost::optional<std::string> _descr;
    const boost::optional<ClockOrigin> _orig;
    const boost::optional<Cycles> _prec;
    const boost::optional<Cycles> _accuracy;
    const ClockOffset _offsetFromOrig;
    const MapItem::Up _attrs;
};

} // namespace yactfr

#endif // YACTFR_METADATA_CLK_TYPE_HPP
