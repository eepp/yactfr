/*
 * Copyright (C) 2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_TESTS_ELEMENT_PRINTER_HPP
#define _YACTFR_TESTS_ELEMENT_PRINTER_HPP

#include <cstdint>
#include <cstdlib>
#include <memory>
#include <vector>
#include <iomanip>
#include <ostream>

#include <yactfr/element-visitor.hpp>
#include <yactfr/element.hpp>

class ElementPrinter :
    public yactfr::ElementVisitor
{
public:
    ElementPrinter(std::ostream& os, const unsigned long indentWidth = 2) :
        _os {&os},
        _indentWidth {indentWidth}
    {
    }

    void visit(const yactfr::PacketBeginningElement& elem)
    {
        this->_indent();
        *_os << "PB\n";
        ++_indentLevel;
    }

    void visit(const yactfr::PacketEndElement& elem)
    {
        --_indentLevel;
        this->_indent();
        *_os << "PE\n";
    }

    void visit(const yactfr::ScopeBeginningElement& elem)
    {
        this->_indent();
        *_os << "SCB:" << static_cast<int>(elem.scope()) << '\n';
        ++_indentLevel;
    }

    void visit(const yactfr::ScopeEndElement& elem)
    {
        --_indentLevel;
        this->_indent();
        *_os << "SCE\n";
    }

    void visit(const yactfr::PacketContentBeginningElement& elem)
    {
        this->_indent();
        *_os << "PCB\n";
        ++_indentLevel;
    }

    void visit(const yactfr::PacketContentEndElement& elem)
    {
        --_indentLevel;
        this->_indent();
        *_os << "PCE\n";
    }

    void visit(const yactfr::EventRecordBeginningElement& elem)
    {
        this->_indent();
        *_os << "ERB\n";
        ++_indentLevel;
    }

    void visit(const yactfr::EventRecordEndElement& elem)
    {
        --_indentLevel;
        this->_indent();
        *_os << "ERE\n";
    }

    void visit(const yactfr::DataStreamIdElement& elem)
    {
        this->_indent();
        *_os << "DSID:" << elem.id() << '\n';
    }

    void visit(const yactfr::PacketOriginIndexElement& elem)
    {
        this->_indent();
        *_os << "POI:" << elem.index() << '\n';
    }

    void visit(const yactfr::ExpectedPacketTotalSizeElement& elem)
    {
        this->_indent();
        *_os << "EPTS:" << elem.expectedSize() << '\n';
    }

    void visit(const yactfr::ExpectedPacketContentSizeElement& elem)
    {
        this->_indent();
        *_os << "EPCS:" << elem.expectedSize() << '\n';
    }

    void visit(const yactfr::PacketMagicNumberElement& elem)
    {
        this->_indent();
        *_os << "PM:" << elem.value() << '\n';
    }

    void visit(const yactfr::PacketUuidElement& elem)
    {
        this->_indent();
        *_os << "PU:" << elem.uuid() << '\n';
    }

    void visit(const yactfr::ClockValueElement& elem)
    {
        this->_indent();
        *_os << "CV:" << elem.clockType().name() << ":" <<
                     elem.cycles() << '\n';
    }

    void visit(const yactfr::PacketEndClockValueElement& elem)
    {
        this->_indent();
        *_os << "PECV:" << elem.clockType().name() << ":" <<
                     elem.cycles() << '\n';
    }

    void visit(const yactfr::DataStreamTypeElement& elem)
    {
        this->_indent();
        *_os << "DST:" << elem.dataStreamType().id() << '\n';
    }

    void visit(const yactfr::EventRecordTypeElement& elem)
    {
        this->_indent();
        *_os << "ERT:" << elem.eventRecordType().id();

        if (elem.eventRecordType().name()) {
            *_os << ":" << *elem.eventRecordType().name();
        }

        *_os << '\n';
    }

    void visit(const yactfr::SignedIntElement& elem)
    {
        this->_indent();
        *_os << "I:" << *elem.displayName() << ":" <<
                     elem.value() << '\n';
    }

    void visit(const yactfr::UnsignedIntElement& elem)
    {
        this->_indent();
        *_os << "U:" << *elem.displayName() << ":" <<
                     elem.value() << '\n';
    }

    void visit(const yactfr::SignedEnumElement& elem)
    {
        this->_indent();
        *_os << "SE:" << *elem.displayName() << ":" <<
                     elem.value() << '\n';
    }

    void visit(const yactfr::UnsignedEnumElement& elem)
    {
        this->_indent();
        *_os << "UE:" << *elem.displayName() << ":" <<
                     elem.value() << '\n';
    }

    void visit(const yactfr::FloatElement& elem)
    {
        this->_indent();
        *_os << "F:" << *elem.displayName() << ":" <<
                     std::setprecision(6) << elem.value() << '\n';
    }

    void visit(const yactfr::StringBeginningElement& elem)
    {
        this->_indent();
        *_os << "STRB:" << *elem.displayName() << '\n';
        ++_indentLevel;
    }

    void visit(const yactfr::StringEndElement& elem)
    {
        --_indentLevel;
        this->_indent();
        *_os << "STRE\n";
    }

    void visit(const yactfr::SubstringElement& elem)
    {
        this->_indent();
        *_os << "SUB:" << elem.size() << ":";

        for (auto ch = elem.begin(); *ch != '\0' && ch != elem.end(); ++ch) {
            *_os << *ch;
        }

        *_os << '\n';
    }

    void visit(const yactfr::ArrayBeginningElement& elem)
    {
        this->_indent();
        *_os << "AB:" << *elem.displayName() << '\n';
        ++_indentLevel;
    }

    void visit(const yactfr::ArrayEndElement& elem)
    {
        --_indentLevel;
        this->_indent();
        *_os << "AE\n";
    }

    void visit(const yactfr::TextArrayBeginningElement& elem)
    {
        this->_indent();
        *_os << "TAB:" << *elem.displayName() << '\n';
        ++_indentLevel;
    }

    void visit(const yactfr::TextArrayEndElement& elem)
    {
        --_indentLevel;
        this->_indent();
        *_os << "TAE\n";
    }

    void visit(const yactfr::SequenceBeginningElement& elem)
    {
        this->_indent();
        *_os << "SQB:" << *elem.displayName() << '\n';
        ++_indentLevel;
    }

    void visit(const yactfr::SequenceEndElement& elem)
    {
        --_indentLevel;
        this->_indent();
        *_os << "SQE\n";
    }

    void visit(const yactfr::TextSequenceBeginningElement& elem)
    {
        this->_indent();
        *_os << "TSQB:" << *elem.displayName() << '\n';
        ++_indentLevel;
    }

    void visit(const yactfr::TextSequenceEndElement& elem)
    {
        --_indentLevel;
        this->_indent();
        *_os << "TSQE\n";
    }

    void visit(const yactfr::StructBeginningElement& elem)
    {
        this->_indent();
        *_os << "STB";

        if (elem.displayName()) {
            *_os << ":" << *elem.displayName();
        }

        *_os << '\n';
        ++_indentLevel;
    }

    void visit(const yactfr::StructEndElement& elem)
    {
        --_indentLevel;
        this->_indent();
        *_os << "STE\n";
    }

    void visit(const yactfr::VariantBeginningSignedTagElement& elem)
    {
        this->_indent();
        *_os << "VSB:" << *elem.displayName() << ":" << elem.tag() << '\n';
        ++_indentLevel;
    }

    void visit(const yactfr::VariantBeginningUnsignedTagElement& elem)
    {
        this->_indent();
        *_os << "VUB:" << *elem.displayName() << ":" << elem.tag() << '\n';
        ++_indentLevel;
    }

    void visit(const yactfr::VariantEndElement& elem)
    {
        --_indentLevel;
        this->_indent();
        *_os << "VE\n";
    }

private:
    void _indent()
    {
        if (_indentWidth == 0) {
            return;
        }

        for (unsigned long i = 0; i < _indentLevel; ++i) {
            for (unsigned long x = 0; x < _indentWidth; ++x) {
                *_os << ' ';
            }
        }
    }

private:
    std::ostream * const _os;
    const unsigned long _indentWidth;
    unsigned long _indentLevel = 0;
};

#endif // _YACTFR_TESTS_ELEMENT_PRINTER_HPP
