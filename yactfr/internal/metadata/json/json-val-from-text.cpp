/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cstdlib>
#include <cassert>
#include <string>
#include <vector>

#include "json-parser.hpp"
#include "json-val-from-text.hpp"

namespace yactfr {
namespace internal {

/*
 * Listener for the listener version of parseJson() which iteratively
 * builds a "root" JSON value.
 */
class JsonValBuilder final
{
public:
    explicit JsonValBuilder(const Size baseOffset) :
        _baseOffset {baseOffset}
    {
    }

    void onNull(const TextLocation& loc)
    {
        this->_handleVal(loc);
    }

    template <typename ValT>
    void onScalarVal(const ValT& val, const TextLocation& loc)
    {
        this->_handleVal(loc, val);
    }

    void onArrayBegin(const TextLocation&)
    {
        _stack.push_back(_tStackFrame {_tState::InArray});
    }

    void onArrayEnd(const TextLocation& loc)
    {
        auto arrayValCont = std::move(this->_stackTop().arrayValCont);

        _stack.pop_back();
        this->_handleVal(loc, std::move(arrayValCont));
    }

    void onObjBegin(const TextLocation&)
    {
        _stack.push_back(_tStackFrame {_tState::InObj});
    }

    void onObjKey(const std::string& key, const TextLocation&)
    {
        this->_stackTop().lastObjKey = key;
    }

    void onObjEnd(const TextLocation& loc)
    {
        auto objValCont = std::move(this->_stackTop().objValCont);

        _stack.pop_back();
        this->_handleVal(loc, std::move(objValCont));
    }

    JsonVal::Up releaseVal() noexcept
    {
        return std::move(_jsonVal);
    }

private:
    enum class _tState
    {
        InArray,
        InObj,
    };

    struct _tStackFrame
    {
        explicit _tStackFrame(const _tState stateParam) :
            state {stateParam}
        {
        }

        _tState state;
        JsonArrayVal::Container arrayValCont;
        JsonObjVal::Container objValCont;
        std::string lastObjKey;
    };

private:
    _tStackFrame& _stackTop() noexcept
    {
        return _stack.back();
    }

    template <typename... ArgTs>
    void _handleVal(const TextLocation& loc, ArgTs&&... args)
    {
        auto jsonVal = createJsonVal(std::forward<ArgTs>(args)..., TextLocation {
            loc.offset() + _baseOffset, loc.lineNumber(), loc.columnNumber()
        });

        if (_stack.empty()) {
            _jsonVal = std::move(jsonVal);
            return;
        }

        switch (_stack.back().state) {
        case _tState::InArray:
            this->_stackTop().arrayValCont.push_back(std::move(jsonVal));
            break;

        case _tState::InObj:
             // safe to move `lastObjKey`: only used once
            this->_stackTop().objValCont.insert(std::make_pair(std::move(this->_stackTop().lastObjKey),
                                                               std::move(jsonVal)));
            break;

        default:
            std::abort();
        }
    }

private:
    Size _baseOffset;
    std::vector<_tStackFrame> _stack;
    JsonVal::Up _jsonVal;
};

JsonVal::Up parseJson(const char * const begin, const char * const end, const Size baseOffset)
{
    JsonValBuilder builder {baseOffset};

    try {
        parseJson(begin, end, builder);
    } catch (const TextParseError& exc) {
        // parseJson() only throws single-message text parse errors
        assert(exc.messages().size() == 1);

        auto& firstMsg = exc.messages().front();

        throwTextParseError(firstMsg.message(), TextLocation {
            firstMsg.location().offset() + baseOffset,
            firstMsg.location().lineNumber(),
            firstMsg.location().columnNumber()
        });
    }

    return builder.releaseVal();
}

} // namespace internal
} // namespace yactfr
