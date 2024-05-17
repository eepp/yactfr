/*
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/elem-seq-it.hpp>

#include "internal/vm.hpp"
#include "internal/metadata/trace-type-impl.hpp"

namespace yactfr {

constexpr Index ElementSequenceIterator::_endOffset = static_cast<Index>(~0ULL);

ElementSequenceIterator::ElementSequenceIterator(DataSourceFactory& dataSrcFactory,
                                                 const TraceType& traceType, const bool end) :
    _dataSrcFactory {&dataSrcFactory},
    _traceType {&traceType}
{
    if (end) {
        _offset = _endOffset;
    } else {
        _vm = std::make_unique<internal::Vm>(*_dataSrcFactory, traceType._pimpl->pktProc(), *this);
        _vm->nextElem();
    }
}

void ElementSequenceIterator::_resetOther(ElementSequenceIterator& other)
{
    other._mark = 0;
    other._offset = _endOffset;
    other._curElem = nullptr;
}

ElementSequenceIterator::ElementSequenceIterator(const ElementSequenceIterator& other) :
    _dataSrcFactory {other._dataSrcFactory},
    _traceType {other._traceType},
    _offset {other._offset},
    _mark {other._mark}
{
    if (!other._vm) {
        return;
    }

    _vm = std::make_unique<internal::Vm>(*other._vm, *this);
    _vm->updateItElemFromOtherPos(other._vm->pos(), other._curElem);
}

/*
 * Copy (do not move) data source factory and trace types so that the
 * source iterator can still create a new VM in the future if needed
 * (in ElementSequenceIterator::restorePosition()).
 */
ElementSequenceIterator::ElementSequenceIterator(ElementSequenceIterator&& other) :
    _dataSrcFactory {other._dataSrcFactory},
    _traceType {other._traceType},
    _offset {other._offset},
    _mark {other._mark}
{
    if (!other._vm) {
        this->_resetOther(other);
        return;
    }

    auto& otherPos = other._vm->pos();

    _vm = std::move(other._vm);
    _vm->it(*this);
    _vm->updateItElemFromOtherPos(otherPos, other._curElem);
    this->_resetOther(other);
}

ElementSequenceIterator::~ElementSequenceIterator()
{
}

ElementSequenceIterator& ElementSequenceIterator::operator=(const ElementSequenceIterator& other)
{
    /*
     * Data source factory and trace type should already be the same
     * because we're in the same element sequence.
     */
    assert(_dataSrcFactory == other._dataSrcFactory);
    assert(_traceType == other._traceType);
    _offset = other._offset;
    _mark = other._mark;

    if (!other._vm) {
        _curElem = nullptr;
        return *this;
    }

    if (_vm) {
        _vm->setFromOther(*other._vm, *this);
    } else {
        _vm = std::make_unique<internal::Vm>(*other._vm, *this);
    }

    _vm->updateItElemFromOtherPos(other._vm->pos(), other._curElem);
    return *this;
}

ElementSequenceIterator& ElementSequenceIterator::operator=(ElementSequenceIterator&& other)
{
    /*
     * Data source factory and trace type should already be the same
     * because we're in the same element sequence.
     */
    assert(_dataSrcFactory == other._dataSrcFactory);
    assert(_traceType == other._traceType);
    _offset = other._offset;
    _mark = other._mark;

    if (!other._vm) {
        _curElem = nullptr;
        this->_resetOther(other);
        return *this;
    }

    auto& otherPos = other._vm->pos();

    _vm = std::move(other._vm);
    _vm->it(*this);
    _vm->updateItElemFromOtherPos(otherPos, other._curElem);
    this->_resetOther(other);
    return *this;
}

ElementSequenceIterator& ElementSequenceIterator::operator++()
{
    assert(_offset != _endOffset);
    assert(_vm);
    _vm->nextElem();
    return *this;
}

void ElementSequenceIterator::seekPacket(const Index offset)
{
    assert(_vm);
    _vm->seekPkt(offset);
}

void ElementSequenceIterator::savePosition(ElementSequenceIteratorPosition& pos) const
{
    assert(_vm);
    _vm->savePos(pos);
}

void ElementSequenceIterator::restorePosition(const ElementSequenceIteratorPosition& pos)
{
    if (!_vm) {
        /*
         * This iterator is at the end of the element sequence and has
         * no VM. Create a new VM before restoring the VM's position.
         */
        _vm = std::make_unique<internal::Vm>(*_dataSrcFactory, _traceType->_pimpl->pktProc(),
                                             *this);
    }

    _vm->restorePos(pos);
}

} // namespace yactfr
