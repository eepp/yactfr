/*
 * Copyright (C) 2018-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_TESTS_ELEM_PRINTER_HPP
#define _YACTFR_TESTS_ELEM_PRINTER_HPP

#include <cstdint>
#include <cstdlib>
#include <memory>
#include <vector>
#include <string>
#include <iomanip>
#include <ostream>
#include <boost/uuid/uuid_io.hpp>

#include <yactfr/elem-visitor.hpp>
#include <yactfr/elem.hpp>

class ElemPrinter :
    public yactfr::ElementVisitor
{
public:
    explicit ElemPrinter(std::ostream& os, const unsigned long indentWidth = 2) :
        _os {&os},
        _indentWidth {indentWidth}
    {
    }

    void visit(const yactfr::PacketBeginningElement&) override
    {
        this->_indent();
        *_os << "P {\n";
        ++_indentLevel;
    }

    void visit(const yactfr::ScopeBeginningElement& elem) override
    {
        this->_indent();
        *_os << "SC:" << static_cast<int>(elem.scope()) << " {\n";
        ++_indentLevel;
    }

    void visit(const yactfr::PacketContentBeginningElement&) override
    {
        this->_indent();
        *_os << "PC {\n";
        ++_indentLevel;
    }

    void visit(const yactfr::EventRecordBeginningElement&) override
    {
        this->_indent();
        *_os << "ER {\n";
        ++_indentLevel;
    }

    void visit(const yactfr::PacketMagicNumberElement& elem) override
    {
        this->_indent();
        *_os << "PMN:" << elem.value() << '\n';
    }

    void visit(const yactfr::MetadataStreamUuidElement& elem) override
    {
        this->_indent();
        *_os << "MSU:" << elem.uuid() << '\n';
    }

    void visit(const yactfr::DefaultClockValueElement& elem) override
    {
        this->_indent();
        *_os << "DCV:" << elem.cycles() << '\n';
    }

    void visit(const yactfr::DataStreamInfoElement& elem) override
    {
        this->_indent();
        *_os << "DSI";

        if (elem.type()) {
            *_os << ":T" << elem.type()->id();
        }

        this->_tryAppendVal('I', elem.id());
        *_os << '\n';
    }

    void visit(const yactfr::EventRecordInfoElement& elem) override
    {
        this->_indent();
        *_os << "ERI";

        if (elem.type()) {
            *_os << ":T" << elem.type()->id();
            this->_tryAppendVal('#', elem.type()->name());
        }

        *_os << '\n';
    }

    void visit(const yactfr::PacketInfoElement& elem) override
    {
        this->_indent();
        *_os << "PI";
        this->_tryAppendVal('T', elem.expectedTotalLength());
        this->_tryAppendVal('C', elem.expectedContentLength());
        this->_tryAppendVal('E', elem.endDefaultClockValue());
        this->_tryAppendVal('S', elem.sequenceNumber());
        this->_tryAppendVal('D', elem.discardedEventRecordCounterSnapshot());
        *_os << '\n';
    }

    void visit(const yactfr::FixedLengthBitArrayElement& elem) override
    {
        this->_visitDataElem(elem, "FLBA");
        *_os << ':' << elem.unsignedIntegerValue() << '\n';
    }

    void visit(const yactfr::FixedLengthBooleanElement& elem) override
    {
        this->_visitDataElem(elem, "FLB");
        *_os << ':' << (elem.value() ? "true" : "false") << '\n';
    }

    void visit(const yactfr::FixedLengthSignedIntegerElement& elem) override
    {
        this->_visitDataElem(elem, "FLSI");
        *_os << ':' << elem.value() << '\n';
    }

    void visit(const yactfr::FixedLengthUnsignedIntegerElement& elem) override
    {
        this->_visitDataElem(elem, "FLUI");
        *_os << ':' << elem.value() << '\n';
    }

    void visit(const yactfr::FixedLengthSignedEnumerationElement& elem) override
    {
        this->_visitDataElem(elem, "FLSE");
        *_os << ':' << elem.value() << '\n';
    }

    void visit(const yactfr::FixedLengthUnsignedEnumerationElement& elem) override
    {
        this->_visitDataElem(elem, "FLUE");
        *_os << ':' << elem.value() << '\n';
    }

    void visit(const yactfr::FixedLengthFloatingPointNumberElement& elem) override
    {
        this->_visitDataElem(elem, "FLFPN");
        *_os << ':' << std::setprecision(6) << elem.value() << '\n';
    }

    void visit(const yactfr::VariableLengthSignedIntegerElement& elem) override
    {
        this->_visitDataElem(elem, "VLSI");
        *_os << ':' << elem.value() << '\n';
    }

    void visit(const yactfr::VariableLengthUnsignedIntegerElement& elem) override
    {
        this->_visitDataElem(elem, "VLUI");
        *_os << ':' << elem.value() << '\n';
    }

    void visit(const yactfr::VariableLengthSignedEnumerationElement& elem) override
    {
        this->_visitDataElem(elem, "VLSE");
        *_os << ':' << elem.value() << '\n';
    }

    void visit(const yactfr::VariableLengthUnsignedEnumerationElement& elem) override
    {
        this->_visitDataElem(elem, "VLUE");
        *_os << ':' << elem.value() << '\n';
    }

    void visit(const yactfr::NullTerminatedStringBeginningElement& elem) override
    {
        this->_visitDataElem(elem, "NTS");
        *_os << " {\n";
        ++_indentLevel;
    }

    void visit(const yactfr::SubstringElement& elem) override
    {
        this->_indent();
        *_os << "SS:" << elem.size() << ":" << elem.string() << '\n';
    }

    void visit(const yactfr::BlobSectionElement& elem) override
    {
        this->_indent();
        *_os << "BS:" << elem.size() << ":";

        std::ios init {nullptr};

        init.copyfmt(*_os);
        *_os << std::hex << std::setfill('0');

        for (const auto byte : elem) {
            *_os << std::setw(2) << static_cast<unsigned int>(byte);
        }

        _os->copyfmt(init);
        *_os << '\n';
    }

    void visit(const yactfr::StaticLengthArrayBeginningElement& elem) override
    {
        this->_visitDataElem(elem, "SLA");
        *_os << " {\n";
        ++_indentLevel;
    }

    void visit(const yactfr::StaticLengthStringBeginningElement& elem) override
    {
        this->_visitDataElem(elem, "SLS");
        *_os << " {\n";
        ++_indentLevel;
    }

    void visit(const yactfr::StaticLengthBlobBeginningElement& elem) override
    {
        this->_visitDataElem(elem, "SLB");
        *_os << ':' << elem.type().mediaType() << " {\n";
        ++_indentLevel;
    }

    void visit(const yactfr::DynamicLengthArrayBeginningElement& elem) override
    {
        this->_visitDataElem(elem, "DLA");
        *_os << " {\n";
        ++_indentLevel;
    }

    void visit(const yactfr::DynamicLengthStringBeginningElement& elem) override
    {
        this->_visitDataElem(elem, "DLS");
        *_os << " {\n";
        ++_indentLevel;
    }

    void visit(const yactfr::DynamicLengthBlobBeginningElement& elem) override
    {
        this->_visitDataElem(elem, "DLB");
        *_os << ':' << elem.type().mediaType() << " {\n";
        ++_indentLevel;
    }

    void visit(const yactfr::StructureBeginningElement& elem) override
    {
        this->_visitDataElem(elem, "ST");
        *_os << " {\n";
        ++_indentLevel;
    }

    void visit(const yactfr::VariantWithSignedIntegerSelectorBeginningElement& elem) override
    {
        this->_visitVarBegElem(elem, "VS");
    }

    void visit(const yactfr::VariantWithUnsignedIntegerSelectorBeginningElement& elem) override
    {
        this->_visitVarBegElem(elem, "VU");
    }

    void visit(const yactfr::OptionalWithBooleanSelectorBeginningElement& elem) override
    {
        this->_visitOptBegElem(elem, "OB");
        *_os << " {\n";
        ++_indentLevel;
    }

    void visit(const yactfr::OptionalWithSignedIntegerSelectorBeginningElement& elem) override
    {
        this->_visitOptBegWithIntSelElem(elem, "OS");
    }

    void visit(const yactfr::OptionalWithUnsignedIntegerSelectorBeginningElement& elem) override
    {
        this->_visitOptBegWithIntSelElem(elem, "OU");
    }

    void visit(const yactfr::EndElement&) override
    {
        --_indentLevel;
        this->_indent();
        *_os << "}\n";
    }

private:
    template <typename OptValT>
    void _tryAppendVal(const char type, const OptValT& optVal) {
        if (optVal) {
            *_os << ':' << type << *optVal;
        }
    }

    template <typename VarBegElemT>
    void _visitVarBegElem(const VarBegElemT& elem, const char * const id)
    {
        this->_visitDataElem(elem, id);
        *_os << ':' << elem.selectorValue() << " {\n";
        ++_indentLevel;
    }

    void _visitOptBegElem(const yactfr::OptionalBeginningElement& elem, const char * const id)
    {
        this->_visitDataElem(elem, id);
        *_os << ':' << (elem.isEnabled() ? "enabled" : "disabled");
    }

    template <typename OptBegElemT>
    void _visitOptBegWithIntSelElem(const OptBegElemT& elem, const char * const id)
    {
        this->_visitOptBegElem(elem, id);
        *_os << ':' << elem.selectorValue() << " {\n";
        ++_indentLevel;
    }

    void _visitDataElem(const yactfr::DataElement& elem, const char * const id)
    {
        this->_indent();
        *_os << id;

        if (elem.structureMemberType()) {
            *_os << ':' << *elem.structureMemberType()->displayName();
        }
    }

    void _indent()
    {
        for (auto i = 0U; i < _indentLevel * _indentWidth; ++i) {
            *_os << ' ';
        }
    }

private:
    std::ostream * const _os;
    const unsigned long _indentWidth;
    unsigned long _indentLevel = 0;
};

#endif // _YACTFR_TESTS_ELEM_PRINTER_HPP
