/*
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cstring>
#include <string>
#include <sstream>
#include <boost/optional.hpp>

#include <yactfr/trace-env-stream-decoder.hpp>
#include <yactfr/trace-env.hpp>
#include <yactfr/metadata/trace-type.hpp>
#include <yactfr/metadata/dst.hpp>
#include <yactfr/elem-seq-it.hpp>
#include <yactfr/elem.hpp>

namespace yactfr {

InvalidTraceEnvironmentStream::InvalidTraceEnvironmentStream(std::string msg, const Index offset) :
    std::runtime_error {std::move(msg)},
    _offset {offset}
{
}

TraceEnvironmentStreamDecoder::TraceEnvironmentStreamDecoder(const TraceType& traceType,
                                                             DataSourceFactory& dataSrcFactory) :
    _traceType {&traceType},
    _elemSeq {traceType, dataSrcFactory},
    _it {_elemSeq.end()}
{
}

constexpr const char *stdNsStr = "std";
constexpr const char *envKeyStr = "environment";

/*
 * Depending on `doThrow`:
 *
 * False:
 *     Returns whether or not the data stream type of `elem` exists and
 *     has the namespace `std` and the name `environment`.
 *
 * True:
 *     Throws `InvalidTraceEnvironmentStream` if the data stream type of
 *     `elem` is missing or doesn't have the namespace `std` and the
 *     name `environment`.
 */
static bool dsInfoSuggestsTraceEnv(const DataStreamInfoElement& elem, const Index offset,
                                   const bool doThrow)
{
    if (!elem.type()) {
        if (doThrow) {
            throw InvalidTraceEnvironmentStream {"No data stream type available.", offset};
        } else {
            return false;
        }
    }

    auto& dst = *elem.type();

    if (!dst.nameSpace()) {
        if (doThrow) {
            std::ostringstream ss;

            ss << "Data stream type has no namespace (expecting `" << stdNsStr << "`).";
            throw InvalidTraceEnvironmentStream {ss.str(), offset};
        } else {
            return false;
        }
    }

    if (*dst.nameSpace() != stdNsStr) {
        if (doThrow) {
            std::ostringstream ss;

            ss << "Unexpected data stream type namespace `" << *dst.nameSpace() << "`; " <<
                  "expecting `" << stdNsStr << "`.";
            throw InvalidTraceEnvironmentStream {ss.str(), offset};
        } else {
            return false;
        }
    }

    if (!dst.name()) {
        if (doThrow) {
            std::ostringstream ss;

            ss << "Data stream type has no name (expecting `" << envKeyStr << "`).";
            throw InvalidTraceEnvironmentStream {ss.str(), offset};
        } else {
            return false;
        }
    }

    if (*dst.name() != envKeyStr) {
        if (doThrow) {
            std::ostringstream ss;

            ss << "Unexpected data stream type name `" << *dst.name() << "`; " <<
                  "expecting `" << envKeyStr << "`.";
            throw InvalidTraceEnvironmentStream {ss.str(), offset};
        } else {
            return false;
        }
    }

    return true;
}

bool TraceEnvironmentStreamDecoder::_dtStdUserAttrsHasFlag(const DataType& dt, const char * const flagName) noexcept
{
    if (!dt.userAttributes()) {
        return false;
    }

    if (!dt.userAttributes()->hasItem(stdNsStr)) {
        return false;
    }

    auto& stdItem = *(*dt.userAttributes())[stdNsStr];

    if (!stdItem.isMap()) {
        return false;
    }

    if (!stdItem.asMap().hasItem(flagName)) {
        return false;
    }

    auto& isValItem = *stdItem.asMap()[flagName];

    if (!isValItem.isBoolean()) {
        return false;
    }

    return *isValItem.asBoolean();
}

void TraceEnvironmentStreamDecoder::_validateNoCurVal() const
{
    if (_curStrVal || _curIntVal) {
        throw InvalidTraceEnvironmentStream {
            "Value is already set for the current environment entry.",
            _it.offset()
        };
    }
}

void TraceEnvironmentStreamDecoder::_validateNoCurKey() const
{
    if (_curKey) {
        throw InvalidTraceEnvironmentStream {
            "Key is already set for the current environment entry.",
            _it.offset()
        };
    }
}

TraceEnvironment TraceEnvironmentStreamDecoder::decode()
{
    if (_traceEnv) {
        // already decoded
        return *_traceEnv;
    }

    if (_it == _elemSeq.end()) {
        // initialize iterator
        _it = _elemSeq.begin();
    }

    while (_it != _elemSeq.end()) {
        switch (_it->kind()) {
        case Element::Kind::DATA_STREAM_INFO:
        {
            dsInfoSuggestsTraceEnv(_it->asDataStreamInfoElement(), _it.offset(), true);
            break;
        }

        case Element::Kind::EVENT_RECORD_BEGINNING:
        {
            // reset current key and values
            _curKey = boost::none;
            _curStrVal = boost::none;
            _curIntVal = boost::none;
            break;
        }

        case Element::Kind::FIXED_LENGTH_UNSIGNED_INTEGER:
        case Element::Kind::FIXED_LENGTH_UNSIGNED_ENUMERATION:
            this->_trySetCurIntVal<FixedLengthUnsignedIntegerElement>();
            break;

        case Element::Kind::FIXED_LENGTH_SIGNED_INTEGER:
        case Element::Kind::FIXED_LENGTH_SIGNED_ENUMERATION:
            this->_trySetCurIntVal<FixedLengthSignedIntegerElement>();
            break;

        case Element::Kind::VARIABLE_LENGTH_UNSIGNED_INTEGER:
        case Element::Kind::VARIABLE_LENGTH_UNSIGNED_ENUMERATION:
            this->_trySetCurIntVal<VariableLengthUnsignedIntegerElement>();
            break;

        case Element::Kind::VARIABLE_LENGTH_SIGNED_INTEGER:
        case Element::Kind::VARIABLE_LENGTH_SIGNED_ENUMERATION:
            this->_trySetCurIntVal<VariableLengthSignedIntegerElement>();
            break;

        case Element::Kind::NULL_TERMINATED_STRING_BEGINNING:
            this->_tryInitCurKeyAndStrVal<NullTerminatedStringBeginningElement>();
            break;

        case Element::Kind::STATIC_LENGTH_STRING_BEGINNING:
            this->_tryInitCurKeyAndStrVal<StaticLengthStringBeginningElement>();
            break;

        case Element::Kind::DYNAMIC_LENGTH_STRING_BEGINNING:
            this->_tryInitCurKeyAndStrVal<DynamicLengthStringBeginningElement>();
            break;

        case Element::Kind::SUBSTRING:
        {
            auto& elem = _it->asSubstringElement();

            if (_fillingCurKey) {
                // append to current key
                _curKey->append(elem.string());
            }

            if (_fillingCurStrVal) {
                // append to current string value
                _curStrVal->append(elem.string());
            }

            break;
        }

        case Element::Kind::NULL_TERMINATED_STRING_END:
        case Element::Kind::STATIC_LENGTH_STRING_END:
        case Element::Kind::DYNAMIC_LENGTH_STRING_END:
        {
            _fillingCurKey = false;
            _fillingCurStrVal = false;
            break;
        }

        case Element::Kind::EVENT_RECORD_END:
        {
            if (!_curKey) {
                throw InvalidTraceEnvironmentStream {
                    "Missing environment entry key.",
                    _it.offset()
                };
            }

            if (!_curStrVal && !_curIntVal) {
                throw InvalidTraceEnvironmentStream {
                    "Missing environment entry value.",
                    _it.offset()
                };
            }

            if (_curEntries.find(*_curKey) != _curEntries.end()) {
                std::ostringstream ss;

                ss << "Duplicate environment entry with key `" << *_curKey << "`.";
                throw InvalidTraceEnvironmentStream {ss.str(), _it.offset()};
            }

            if (_curStrVal) {
                // string value
                _curEntries.emplace(std::make_pair(std::move(*_curKey), std::move(*_curStrVal)));
            } else {
                // integer value
                assert(_curIntVal);
                _curEntries.emplace(std::make_pair(std::move(*_curKey), *_curIntVal));
            }

            break;
        }

        default:
            break;
        }

        ++_it;
    }

    // create corresponding trace environment
    _traceEnv = TraceEnvironment {std::move(_curEntries)};
    return *_traceEnv;
}

bool TraceEnvironmentStreamDecoder::isTraceEnvironmentStream()
{
    auto res = false;

    if (_it == _elemSeq.end()) {
        // initialize iterator
        _it = _elemSeq.begin();
    }

    while (_it != _elemSeq.end()) {
        switch (_it->kind()) {
        case Element::Kind::DATA_STREAM_INFO:
        {
            res = dsInfoSuggestsTraceEnv(_it->asDataStreamInfoElement(), _it.offset(), false);

            _it = _elemSeq.end();
            break;
        }

        default:
            ++_it;
            break;
        };
    };

    return res;
}

} // namespace yactfr
