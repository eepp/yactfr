/*
 * Copyright (C) 2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_TESTS_ELEMENT_COLLECTOR_HPP
#define _YACTFR_TESTS_ELEMENT_COLLECTOR_HPP

#include <cstdint>
#include <cstdlib>
#include <memory>
#include <vector>

#include <yactfr/elem-visitor.hpp>
#include <yactfr/elem.hpp>

class ElementCollector :
    public yactfr::ElementVisitor
{
private:
    void visit(const yactfr::PacketBeginningElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::PacketEndElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::ScopeBeginningElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::ScopeEndElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::PacketContentBeginningElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::PacketContentEndElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::EventRecordBeginningElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::EventRecordEndElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::DataStreamIdElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::PacketOriginIndexElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::ExpectedPacketTotalLengthElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::ExpectedPacketContentLengthElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::PacketMagicNumberElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::TraceTypeUuidElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::ClockValueElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::PacketEndClockValueElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::DataStreamTypeElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::EventRecordTypeElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::SignedIntegerElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::UnsignedIntegerElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::SignedEnumerationElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::UnsignedEnumerationElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::RealElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::StringBeginningElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::StringEndElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::SubstringElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::StaticArrayBeginningElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::StaticArrayEndElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::StaticTextArrayBeginningElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::StaticTextArrayEndElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::DynamicArrayBeginningElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::DynamicArrayEndElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::DynamicTextArrayBeginningElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::DynamicTextArrayEndElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::StructureBeginningElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::StructureEndElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::VariantWithSignedSelectorBeginningElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::VariantWithUnsignedSelectorBeginningElement& elem)
    {
        this->_appendElement(elem);
    }

    void visit(const yactfr::VariantEndElement& elem)
    {
        this->_appendElement(elem);
    }

private:
    template <typename ElemT>
    void _appendElement(const ElemT& elem)
    {
        _elements.push_back(std::make_unique<const ElemT>(elem));
    }

private:
    std::vector<std::unique_ptr<const yactfr::Element>> _elements;
};

#endif // _YACTFR_TESTS_ELEMENT_COLLECTOR_HPP
