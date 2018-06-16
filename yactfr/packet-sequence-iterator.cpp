/*
 * Packet sequence iterator.
 *
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/packet-sequence-iterator.hpp>

#include "vm.hpp"
#include "metadata/trace-type-impl.hpp"

/*
 * It is possible that a packet sequence iterator has no VM instance,
 * but it must be able to create a new VM at any time because of
 * PacketSequenceIterator::restorePosition(), so even an "end" packet
 * sequence iterator must keep:
 *
 * * Its data source factory.
 * * Its trace type.
 */

namespace yactfr {

PacketSequenceIterator::PacketSequenceIterator(std::shared_ptr<DataSourceFactory> dataSourceFactory,
                                               TraceType::SP traceType,
                                               const bool end) :
    _dataSourceFactory {dataSourceFactory},
    _traceType {traceType}
{
    if (end) {
        _offset = _END_OFFSET;
    } else {
        _vm = std::make_unique<internal::Vm>(_dataSourceFactory.get(),
                                             traceType->_pimpl->packetProc(),
                                             *this);
        _vm->nextElement();
    }
}

void PacketSequenceIterator::_resetOther(PacketSequenceIterator& other)
{
    other._mark = 0;
    other._offset = _END_OFFSET;
    other._curElement = nullptr;
}

PacketSequenceIterator::PacketSequenceIterator(const PacketSequenceIterator& other) :
    _dataSourceFactory {other._dataSourceFactory},
    _traceType {other._traceType},
    _offset {other._offset},
    _mark {other._mark}
{
    if (!other._vm) {
        return;
    }

    if (_vm) {
        *_vm = *other._vm;
        _vm->iter(*this);
    } else {
        _vm = std::make_unique<internal::Vm>(*other._vm, *this);
    }

    _vm->updateIterElementFromOtherPos(other._vm->pos(), other._curElement);
}

/*
 * Copy (do not move) data source factory and trace types so that the
 * source iterator can still create a new VM in the future if needed (in
 * PacketSequenceIterator::restorePosition()).
 */
PacketSequenceIterator::PacketSequenceIterator(PacketSequenceIterator&& other) :
    _dataSourceFactory {other._dataSourceFactory},
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
    _vm->iter(*this);
    _vm->updateIterElementFromOtherPos(otherPos, other._curElement);
    this->_resetOther(other);
}

PacketSequenceIterator::~PacketSequenceIterator()
{
}

PacketSequenceIterator& PacketSequenceIterator::operator=(const PacketSequenceIterator& other)
{
    /*
     * Data source factory and trace type should already be the same
     * because we're in the same packet sequence.
     */
    assert(_dataSourceFactory == other._dataSourceFactory);
    assert(_traceType == other._traceType);
    _offset = other._offset;
    _mark = other._mark;

    if (!other._vm) {
        _curElement = nullptr;
        return *this;
    }

    if (_vm) {
        *_vm = *other._vm;
        _vm->iter(*this);
    } else {
        _vm = std::make_unique<internal::Vm>(*other._vm, *this);
    }

    _vm->updateIterElementFromOtherPos(other._vm->pos(), other._curElement);
    return *this;
}

PacketSequenceIterator& PacketSequenceIterator::operator=(PacketSequenceIterator&& other)
{
    /*
     * Data source factory and trace type should already be the same
     * because we're in the same packet sequence.
     */
    assert(_dataSourceFactory == other._dataSourceFactory);
    assert(_traceType == other._traceType);
    _offset = other._offset;
    _mark = other._mark;

    if (!other._vm) {
        _curElement = nullptr;
        this->_resetOther(other);
        return *this;
    }

    auto& otherPos = other._vm->pos();

    _vm = std::move(other._vm);
    _vm->iter(*this);
    _vm->updateIterElementFromOtherPos(otherPos, other._curElement);
    this->_resetOther(other);
    return *this;
}

PacketSequenceIterator& PacketSequenceIterator::operator++()
{
    assert(_offset != _END_OFFSET);
    assert(_vm);
    _vm->nextElement();
    return *this;
}

void PacketSequenceIterator::seekPacket(const Index offset)
{
    assert(_vm);
    _vm->seekPacket(offset);
}

void PacketSequenceIterator::savePosition(PacketSequenceIteratorPosition& pos) const
{
    assert(_vm);
    _vm->savePosition(pos);
}

void PacketSequenceIterator::restorePosition(const PacketSequenceIteratorPosition& pos)
{
    if (!_vm) {
        /*
         * This iterator is at the end of the packet sequence and has
         * no VM. Create a new VM before restoring the VM's position.
         */
        _vm = std::make_unique<internal::Vm>(_dataSourceFactory.get(),
                                             _traceType->_pimpl->packetProc(),
                                             *this);
    }

    _vm->restorePosition(pos);
}

} // namespace yactfr
