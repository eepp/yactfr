/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_TRACE_ENV_STREAM_DECODER_HPP
#define _YACTFR_TRACE_ENV_STREAM_DECODER_HPP

#include <boost/optional.hpp>
#include <string>
#include <stdexcept>

#include "trace-env.hpp"
#include "elem-seq.hpp"
#include "elem.hpp"
#include "aliases.hpp"
#include "metadata/nt-str-type.hpp"
#include "metadata/sl-str-type.hpp"
#include "metadata/dl-str-type.hpp"

namespace yactfr {

class DataSourceFactory;
class TraceType;
class TraceEnvironmentStreamDecoder;

/*!
@brief
    Invalid trace environment stream.

@ingroup trace
*/
class InvalidTraceEnvironmentStream final :
    public std::runtime_error
{
    friend class TraceEnvironmentStreamDecoder;

public:
    explicit InvalidTraceEnvironmentStream(std::string msg, Index offset);

    /// Offset (bits) from the beginning of the trace environment data
    /// stream.
    Index offset() const noexcept
    {
        return _offset;
    }

private:
    Index _offset;
};

/*!
@brief
    Trace environment stream decoder (CTF&nbsp;2).

@ingroup trace

A trace environment stream decoder decodes a CTF&nbsp;2 trace
environment data stream to produce a TraceEnvironment object.

Just like an \link ElementSequence element sequence\endlink (which it
uses behind the scenes), a trace environment stream decoder needs both
a \link TraceType trace type\endlink and a
\link DataSourceFactory data source factory\endlink.

Once you have built a trace environment stream decoder, call its
decode() method which returns a TraceEnvironment object on success, or
throws otherwise.
*/
class TraceEnvironmentStreamDecoder final
{
public:
    /*!
    @brief
        Builds a trace environment stream decoder to decode a trace
        environment data stream described by a \link DataStreamType data
        stream type\endlink in \p traceType and which creates a data
        source with \p dataSourceFactory.

    \p traceType and \p dataSourceFactory must exist as long as this
    trace environment stream decoder exists.

    @param[in] traceType
        Trace type which contains the data stream type describing the
        trace environment data stream to decode.
    @param[in] dataSourceFactory
        Factory of data sources used by the decoder to obtain the trace
        environment data stream bytes.
    */
    explicit TraceEnvironmentStreamDecoder(const TraceType& traceType, DataSourceFactory& dataSourceFactory);

    /*!
    @brief
        Decodes the whole data stream provided by a data source
        of the factory provided at construction time and returns the
        corresponding trace environment object.

    This method may throw a DataNotAvailable instance. In that case,
    this trace environment stream decoder retains the current data
    stream decoding state so that it's safe to call this method again,
    until it finally returns.

    @returns
        Trace environment object corresponding to the contents of the
        decoded trace environment data stream.

    @throws ?
        Any exception which ElementSequence::begin() can throw.
    @throws ?
        Any exception which ElementSequenceIterator::operator++() can
        throw.
    @throws InvalidTraceEnvironmentStream
        Invalid trace environment stream.
    */
    TraceEnvironment decode();

private:
    enum class _State
    {
        INIT,
        EXPECT_KEY
    };

private:
    /*
     * Validates that there's no current value, throwing
     * `InvalidTraceEnvironmentStream` otherwise.
     */
    void _validateNoCurVal() const;

    /*
     * Returns whether or not the data type `dt` has the standard user
     * attribute flag `flagName` set.
     */
    static bool _dtStdUserAttrsHasFlag(const DataType& dt, const char *flagName) noexcept;

    /*
     * Returns whether or not the data type of `elem` has the standard
     * "is value" user attribute flag set.
     */
    template <typename ElemT>
    static bool _dtIsVal(const ElemT& elem) noexcept
    {
        return TraceEnvironmentStreamDecoder::_dtStdUserAttrsHasFlag(elem.type(), "is-value");
    }

    /*
     * Returns whether or not the data type of `elem` has the standard
     * "is key" user attribute flag set.
     */
    template <typename ElemT>
    static bool _dtIsKey(const ElemT& elem) noexcept
    {
        return TraceEnvironmentStreamDecoder::_dtStdUserAttrsHasFlag(elem.type(), "is-key");
    }

    /*
     * Returns the `long long` value of the unsigned integer element
     * `elem`, throwing `InvalidTraceEnvironmentStream` on overflow.
     */
    template <typename ElemT>
    long long _uIntElemVal(const ElemT& elem) const
    {
        constexpr auto llMaxAsUll = static_cast<unsigned long long>(std::numeric_limits<long long>::max());

        if (elem.value() > llMaxAsUll) {
            std::ostringstream ss;

            ss << "Value " << elem.value() << " overflows the signed 64-bit range.";
            throw InvalidTraceEnvironmentStream {ss.str(), _it.offset()};
        }

        return static_cast<long long>(elem.value());
    }

    /*
     * Returns the value of the signed integer element `elem`.
     */
    template <typename ElemT>
    static long long _sIntElemVal(const ElemT& elem) noexcept
    {
        return elem.value();
    }

    long long _intElemVal(const FixedLengthUnsignedIntegerElement& elem) const
    {
        return this->_uIntElemVal(elem);
    }

    long long _intElemVal(const FixedLengthSignedIntegerElement& elem) const noexcept
    {
        return this->_sIntElemVal(elem);
    }

    long long _intElemVal(const VariableLengthUnsignedIntegerElement& elem) const
    {
        return this->_uIntElemVal(elem);
    }

    long long _intElemVal(const VariableLengthSignedIntegerElement& elem) const noexcept
    {
        return this->_sIntElemVal(elem);
    }

    /*
     * Tries to set the current integer value from the element of `_it`,
     * throwing `InvalidTraceEnvironmentStream` on error.
     */
    template <typename ElemT>
    void _trySetCurIntVal()
    {
        auto& elem = static_cast<const ElemT &>(*_it);

        if (!this->_dtIsVal(elem)) {
            return;
        }

        this->_validateNoCurVal();
        _curIntVal = this->_intElemVal(elem);
    }

    /*
     * Tries to initialize the current key and/or string value from the
     * string beginning element of `_it`.
     */
    template <typename ElemT>
    void _tryInitCurKeyAndStrVal() noexcept
    {
        auto& elem = static_cast<const ElemT&>(*_it);

        if (this->_dtIsKey(elem)) {
            // initialize current key
            _fillingCurKey = true;
            _curKey = std::string {};
        }

        if (this->_dtIsVal(elem)) {
            // initialize current string value
            _fillingCurStrVal = true;
            _curStrVal = std::string {};
        }
    }

private:
    const TraceType *_traceType;
    ElementSequence _elemSeq;
    ElementSequenceIterator _it;
    boost::optional<std::string> _curKey;
    bool _fillingCurKey = false;
    boost::optional<std::string> _curStrVal;
    bool _fillingCurStrVal = false;
    boost::optional<long long> _curIntVal;
    TraceEnvironment::Entries _curEntries;
    boost::optional<TraceEnvironment> _traceEnv;
};

} // namespace yactfr

#endif // _YACTFR_TRACE_ENV_STREAM_DECODER_HPP
