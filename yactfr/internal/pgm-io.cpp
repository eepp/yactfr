/*
 * Copyright (C) 2016-2025 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <sstream>
#include <boost/algorithm/string/predicate.hpp>

#include <yactfr/metadata/ert.hpp>
#include <yactfr/metadata/dst.hpp>
#include <yactfr/metadata/trace-type.hpp>

#include "vendor/wise-enum/wise_enum.h"
#include "utils.hpp"
#include "pgm.hpp"
#include "pgm-io.hpp"

namespace yactfr {
namespace internal {
namespace {

class Writer final
{
public:
    explicit Writer(std::ostream& os, const PktPgm& pktPgm) :
        _os {&os}
    {
        this->_write(pktPgm);
    }

private:
    void _writePgmName(const std::string& name)
    {
        this->_writeColoredName("❰", name, "❱", 4);
    }

    void _writePgm(const std::string& name, const Size pgmLen)
    {
        this->_writeLine([&] {
            this->_writePgmName(name);
            this->_writeProp("len", pgmLen);
        });

        this->_writeIndented([&] {
            const auto beginNucleo = _nucleo;

            while (_nucleo < beginNucleo + pgmLen) {
                this->_writeCurInstr();
            }
        });
    }

    void _writeIndentedPgm(const std::string& name, const Size pgmLen)
    {
        this->_writeIndented([&] {
            this->_writePgm(name, pgmLen);
        });
    }

    void _writePgm(const std::string& name, const InstrBase::Opcode endOpcode)
    {
        this->_writeLine([&] {
            this->_writePgmName(name);
        });

        this->_writeIndented([&] {
            while (InstrBase::fromNucleo(_nucleo).opcode() != endOpcode) {
                this->_writeCurInstr();
            }
        });
    }

    void _writeIndentedPgm(const std::string& name, const InstrBase::Opcode endOpcode)
    {
        this->_writeIndented([&] {
            this->_writePgm(name, endOpcode);
        });
    }

    void _writeIndentedPgm(const std::string& name, const PgmView pgm, const Size pgmLen)
    {
        _nucleo = pgm.begin();

        this->_writeIndentedPgm(name, pgmLen);
    }

    void _writeIndentedRootPgm(const std::string& name, const PgmView pgm, const Size pgmLen)
    {
        _curPgm = pgm;
        this->_writeIndentedPgm(name, pgm, pgmLen);
    }

    template <typename FuncT>
    void _writeIndented(FuncT&& func, const Size indentIncr = 1)
    {
        _indent += indentIncr;
        func();
        _indent -= indentIncr;
    }

    void _writeNl()
    {
        *_os << '\n';
    }

    template <typename FuncT>
    void _writeLine(FuncT&& func)
    {
        this->_writeIndent();
        func();
        this->_writeNl();
    }

    void _writeIndent()
    {
        for (Index i = 0; i < _indent; ++i) {
            *_os << "  ";
        }
    }

    void _writeTermBold()
    {
        *_os << "\033[1m";
    }

    void _writeTermFgColor(const Index id)
    {
        this->_writeTermBold();
        *_os << "\033[" << (30 + id) << 'm';
    }

    void _writeTermReset()
    {
        *_os << "\033[0m";
    }

    template <typename FuncT>
    void _writeColored(const Index colorId, FuncT&& func)
    {
        this->_writeTermFgColor(colorId);
        func();
        this->_writeTermReset();
    }

    void _writeColoredName(const std::string& prefix, const std::string& name,
                           const std::string& suffix, const Index colorId)
    {
        *_os << prefix;
        this->_writeColored(colorId, [&] {
            *_os << name;
        });
        *_os << suffix;
    }

    void _writeSectionName(const std::string& name)
    {
        *_os << '<';
        this->_writeTermBold();
        *_os << name;
        this->_writeTermReset();
        *_os << '>';
    }

    void _writeTopName(const std::string& name)
    {
        this->_writeColoredName("{", name, "}", 5);
    }

    template <typename ValT>
    void _writePropVal(ValT&& val)
    {
        *_os << val;
    }

    void _writePropVal(const std::string& val)
    {
        *_os << '`' << val << '`';
    }

    void _writePropVal(const Scope scope)
    {
        this->_writeColored(3, [&] {
            *_os << [scope] {
                switch (scope) {
                case Scope::PacketHeader:
                    return "PH";

                case Scope::PacketContext:
                    return "PC";

                case Scope::EventRecordHeader:
                    return "ERH";

                case Scope::EventRecordCommonContext:
                    return "ERCC";

                case Scope::EventRecordSpecificContext:
                    return "ERSC";

                case Scope::EventRecordPayload:
                    return "ERP";

                default:
                    std::abort();
                }
            }();
        });
    }

    template <typename ValT>
    void _writeProp(const std::string& prop, ValT&& val)
    {
        *_os << ' ';
        this->_writeTermBold();
        *_os << prop;
        this->_writeTermReset();
        *_os << '=';
        this->_writePropVal(std::forward<ValT>(val));
    }

    template <typename ObjT>
    void _writeObjIdProp(const ObjT& val)
    {
        if (!val.nameSpace() && !val.name() && !val.uid()) {
            return;
        }

        this->_writeProp("obj-id",
                         static_cast<const std::string &>(call([&val] {
            std::ostringstream idSs;

            if (val.nameSpace()) {
                idSs << *val.nameSpace();

                if (val.name() || val.uid()) {
                    idSs << ':';
                }
            }

            if (val.name()) {
                idSs << *val.name();

                if (val.uid()) {
                    idSs << ':';
                }
            }

            if (val.uid()) {
                idSs << *val.uid();
            }

            return idSs.str();
        })));
    }

    void _write(const PktPgm& pktPgm)
    {
        this->_writeLine([&] {
            this->_writeTopName("pkt pgm");
            this->_writeProp("saved-vals-count", pktPgm.savedValsCount());
        });

        this->_writeIndentedRootPgm("pkt preamble pgm", pktPgm.preamblePgm(),
                                    pktPgm.preamblePgmLen());

        if (pktPgm.dsPktPgmsCount() > 0) {
            this->_writeIndented([&] {
                this->_writeLine([&] {
                    this->_writeSectionName("DS pkt pgms");
                });

                this->_writeIndented([&] {
                    pktPgm.forEachDsPktPgm([&](auto& dsPktPgm) {
                        this->_write(dsPktPgm);
                    });
                });
            });
        }
    }

    void _write(const DsPktPgm& dsPktPgm)
    {
        this->_writeLine([&] {
            this->_writeTopName("DS pkt pgm");
            this->_writeProp("dst-id", dsPktPgm.dst().id());
            this->_writeObjIdProp(dsPktPgm.dst());
        });

        this->_writeIndentedRootPgm("pkt preamble pgm", dsPktPgm.pktPreamblePgm(),
                                    dsPktPgm.pktPreamblePgmLen());
        this->_writeIndentedRootPgm("ER preamble pgm", dsPktPgm.erPreamblePgm(),
                                    dsPktPgm.erPreamblePgmLen());

        if (dsPktPgm.erPgmsCount() > 0) {
            this->_writeIndented([&] {
                this->_writeLine([&] {
                    this->_writeSectionName("ER pgms");
                });

                this->_writeIndented([&] {
                    dsPktPgm.forEachErPgm([&](auto& erPgm) {
                        this->_write(erPgm);
                    });
                });
            });
        }
    }

    void _write(const ErPgm& erPgm)
    {
        this->_writeLine([&] {
            this->_writeTopName("ER pgm");
            this->_writeProp("ert-id", erPgm.ert().id());
            this->_writeObjIdProp(erPgm.ert());
        });

        this->_writeIndentedRootPgm("pgm", erPgm.pgm(), erPgm.pgmLen());
    }

    template <typename SelT>
    static std::string _rangeStr(const PgmIntRange<SelT> range)
    {
        std::ostringstream ss;

        ss << '[' << range.lower() << ", " << range.upper() << ']';
        return ss.str();
    }

    template <typename SelT>
    void _writeSelRangesProp(const PgmIntRangeSetView<SelT> ranges)
    {
        this->_writeProp("sel-ranges", call([&] {
            if (ranges.count() == 1) {
                return this->_rangeStr(ranges[0]);
            }

            std::ostringstream rangesSs;

            rangesSs << '{';

            char comma[] = {'\0', ' ', '\0'};

            for (auto& range : ranges) {
                rangesSs << comma << this->_rangeStr(range);
                comma[0] = ',';
            }

            rangesSs << '}';
            return rangesSs.str();
        }));
    }

    void _write(const InstrBase::Opcode opcode)
    {
        namespace balg = boost::algorithm;

        const auto opcodeStr = wise_enum::to_string(opcode);

        this->_writeColoredName("[", opcodeStr, "]", [opcodeStr] {
            if (balg::starts_with(opcodeStr, "Read")) {
                return 6;
            } else if (balg::starts_with(opcodeStr, "End")) {
                return 1;
            } else if (balg::starts_with(opcodeStr, "Set") ||
                       balg::starts_with(opcodeStr, "Update") ||
                       balg::starts_with(opcodeStr, "Save")) {
                return 3;
            } else {
                return 0;
            }
        }());
    }

    template <typename InstrT>
    void _writeInstrBaseProps(const InstrT& instr)
    {
        this->_writeProp("static-instr-len", instr.staticLen());
    }

    template <typename InstrT>
    void _writeReadDataInstrProps(const InstrT& instr)
    {
        this->_writeInstrBaseProps(instr);
        this->_writeProp("align", instr.align());

        if (instr.memberType() && instr.memberType()->displayName()) {
            this->_writeProp("member-type-name", *instr.memberType()->displayName());
        }
    }

    template <typename InstrT>
    void _writeReadSlDataInstrProps(const InstrT& instr)
    {
        this->_writeReadDataInstrProps(instr);
        this->_writeProp("elem-count", instr.elemCount());
    }

    template <typename InstrT>
    void _writeReadDlDataInstrProps(const InstrT& instr)
    {
        this->_writeReadDataInstrProps(instr);
        this->_writeProp("saved-elem-count-pos", instr.savedElemCountPos());
    }

    template <typename InstrT>
    void _writeReadArrayElemPgm(const InstrT& instr)
    {
        if (instr.elemPgmLen() > 0) {
            this->_writeIndentedPgm("elem pgm", instr.elemPgm(), instr.elemPgmLen());
        }
    }

    template <typename InstrT>
    void _writeReadOptInstrProps(const InstrT& instr)
    {
        this->_writeReadDataInstrProps(instr);
        this->_writeProp("saved-sel-pos", instr.savedSelPos());
    }

    template <typename InstrT>
    void _writeReadOptWithIntSelInstrFull(const InstrT& instr)
    {
        this->_writeReadOptInstrProps(instr);
        this->_writeProp("sel-ranges-count", instr.selRangeSet().count());
        this->_writeSelRangesProp(instr.selRangeSet());
        this->_writeNl();
        this->_writeIndentedPgm("pgm", instr.pgm(), instr.pgmLen());
    }

    template <typename VarTypeT>
    void _writeVarTypeOptName(const VarTypeT& varType, const Index optIndex)
    {
        auto& opt = varType[optIndex];

        if (opt.displayName()) {
            this->_writeProp("opt-name", *opt.displayName());
        }
    }

    template <typename InstrT>
    void _writeReadVarWithIntSelInstrFull(const InstrT& instr)
    {
        this->_writeReadDataInstrProps(instr);
        this->_writeProp("instr-len", instr.len());
        this->_writeProp("saved-sel-pos", instr.savedSelPos());
        this->_writeProp("opt-count", instr.optCount());
        this->_writeNl();
        this->_writeIndented([&] {
            for (Index i = 0; i < instr.optCount(); ++i) {
                auto& opt = instr[i];

                this->_writeLine([&] {
                    {
                        std::ostringstream ss;

                        ss << "opt #" << (i + 1);
                        this->_writeSectionName(ss.str());
                    }

                    if (instr.opcode() == InstrBase::Opcode::ReadVarWithUIntSel) {
                        this->_writeVarTypeOptName(instr.dt().asVariantWithUnsignedIntegerSelectorType(), i);
                    } else {
                        assert(instr.opcode() == InstrBase::Opcode::ReadVarWithSIntSel);
                        this->_writeVarTypeOptName(instr.dt().asVariantWithSignedIntegerSelectorType(), i);
                    }

                    this->_writeProp("instr-len", opt.len());
                    this->_writeProp("sel-ranges-count", opt.selRangeSet().count());
                    this->_writeSelRangesProp(opt.selRangeSet());
                });

                this->_writeIndentedPgm("pgm", opt.pgm(), opt.pgmLen());
            }
        });
    }

    void _writeCurInstr()
    {
        auto& instr = InstrBase::fromNucleo(_nucleo);
        const auto instrBeginNucleo = _nucleo;

        this->_writeIndent();
        this->_write(instr.opcode());
        *_os << " (";
        this->_writeColored(2, [&] {
            *_os << (_nucleo - _curPgm.begin());
        });
        *_os << ")";

        switch (instr.opcode()) {
        case InstrBase::Opcode::ReadFlBitArrayA16Be:
        case InstrBase::Opcode::ReadFlBitArrayA16BeRev:
        case InstrBase::Opcode::ReadFlBitArrayA16Le:
        case InstrBase::Opcode::ReadFlBitArrayA16LeRev:
        case InstrBase::Opcode::ReadFlBitArrayA32Be:
        case InstrBase::Opcode::ReadFlBitArrayA32BeRev:
        case InstrBase::Opcode::ReadFlBitArrayA32Le:
        case InstrBase::Opcode::ReadFlBitArrayA32LeRev:
        case InstrBase::Opcode::ReadFlBitArrayA64Be:
        case InstrBase::Opcode::ReadFlBitArrayA64BeRev:
        case InstrBase::Opcode::ReadFlBitArrayA64Le:
        case InstrBase::Opcode::ReadFlBitArrayA64LeRev:
        case InstrBase::Opcode::ReadFlBitArrayA8:
        case InstrBase::Opcode::ReadFlBitArrayA8Rev:
        case InstrBase::Opcode::ReadFlBitMapA16Be:
        case InstrBase::Opcode::ReadFlBitMapA16BeRev:
        case InstrBase::Opcode::ReadFlBitMapA16Le:
        case InstrBase::Opcode::ReadFlBitMapA16LeRev:
        case InstrBase::Opcode::ReadFlBitMapA32Be:
        case InstrBase::Opcode::ReadFlBitMapA32BeRev:
        case InstrBase::Opcode::ReadFlBitMapA32Le:
        case InstrBase::Opcode::ReadFlBitMapA32LeRev:
        case InstrBase::Opcode::ReadFlBitMapA64Be:
        case InstrBase::Opcode::ReadFlBitMapA64BeRev:
        case InstrBase::Opcode::ReadFlBitMapA64Le:
        case InstrBase::Opcode::ReadFlBitMapA64LeRev:
        case InstrBase::Opcode::ReadFlBitMapA8:
        case InstrBase::Opcode::ReadFlBitMapA8Rev:
        case InstrBase::Opcode::ReadFlBoolA16Be:
        case InstrBase::Opcode::ReadFlBoolA16BeRev:
        case InstrBase::Opcode::ReadFlBoolA16Le:
        case InstrBase::Opcode::ReadFlBoolA16LeRev:
        case InstrBase::Opcode::ReadFlBoolA32Be:
        case InstrBase::Opcode::ReadFlBoolA32BeRev:
        case InstrBase::Opcode::ReadFlBoolA32Le:
        case InstrBase::Opcode::ReadFlBoolA32LeRev:
        case InstrBase::Opcode::ReadFlBoolA64Be:
        case InstrBase::Opcode::ReadFlBoolA64BeRev:
        case InstrBase::Opcode::ReadFlBoolA64Le:
        case InstrBase::Opcode::ReadFlBoolA64LeRev:
        case InstrBase::Opcode::ReadFlBoolA8:
        case InstrBase::Opcode::ReadFlBoolA8Rev:
        case InstrBase::Opcode::ReadFlFloatA32Be:
        case InstrBase::Opcode::ReadFlFloatA32BeRev:
        case InstrBase::Opcode::ReadFlFloatA32Le:
        case InstrBase::Opcode::ReadFlFloatA32LeRev:
        case InstrBase::Opcode::ReadFlFloatA64Be:
        case InstrBase::Opcode::ReadFlFloatA64BeRev:
        case InstrBase::Opcode::ReadFlFloatA64Le:
        case InstrBase::Opcode::ReadFlFloatA64LeRev:
        case InstrBase::Opcode::ReadFlSIntA16Be:
        case InstrBase::Opcode::ReadFlSIntA16BeRev:
        case InstrBase::Opcode::ReadFlSIntA16Le:
        case InstrBase::Opcode::ReadFlSIntA16LeRev:
        case InstrBase::Opcode::ReadFlSIntA32Be:
        case InstrBase::Opcode::ReadFlSIntA32BeRev:
        case InstrBase::Opcode::ReadFlSIntA32Le:
        case InstrBase::Opcode::ReadFlSIntA32LeRev:
        case InstrBase::Opcode::ReadFlSIntA64Be:
        case InstrBase::Opcode::ReadFlSIntA64BeRev:
        case InstrBase::Opcode::ReadFlSIntA64Le:
        case InstrBase::Opcode::ReadFlSIntA64LeRev:
        case InstrBase::Opcode::ReadFlSIntA8:
        case InstrBase::Opcode::ReadFlSIntA8Rev:
        case InstrBase::Opcode::ReadFlUIntA16Be:
        case InstrBase::Opcode::ReadFlUIntA16BeRev:
        case InstrBase::Opcode::ReadFlUIntA16Le:
        case InstrBase::Opcode::ReadFlUIntA16LeRev:
        case InstrBase::Opcode::ReadFlUIntA32Be:
        case InstrBase::Opcode::ReadFlUIntA32BeRev:
        case InstrBase::Opcode::ReadFlUIntA32Le:
        case InstrBase::Opcode::ReadFlUIntA32LeRev:
        case InstrBase::Opcode::ReadFlUIntA64Be:
        case InstrBase::Opcode::ReadFlUIntA64BeRev:
        case InstrBase::Opcode::ReadFlUIntA64Le:
        case InstrBase::Opcode::ReadFlUIntA64LeRev:
        case InstrBase::Opcode::ReadFlUIntA8:
        case InstrBase::Opcode::ReadFlUIntA8Rev:
        case InstrBase::Opcode::ReadNtStrUtf16:
        case InstrBase::Opcode::ReadNtStrUtf32:
        case InstrBase::Opcode::ReadNtStrUtf8:
        case InstrBase::Opcode::ReadVlSInt:
        case InstrBase::Opcode::ReadVlUInt:
            this->_writeReadDataInstrProps(instr.asReadData());
            this->_writeNl();
            _nucleo = instrBeginNucleo + instr.asReadData().staticLen();
            break;

        case InstrBase::Opcode::ReadFlBitArrayBe:
        case InstrBase::Opcode::ReadFlBitArrayBeRev:
        case InstrBase::Opcode::ReadFlBitArrayLe:
        case InstrBase::Opcode::ReadFlBitArrayLeRev:
        case InstrBase::Opcode::ReadFlBitMapBe:
        case InstrBase::Opcode::ReadFlBitMapBeRev:
        case InstrBase::Opcode::ReadFlBitMapLe:
        case InstrBase::Opcode::ReadFlBitMapLeRev:
        case InstrBase::Opcode::ReadFlBoolBe:
        case InstrBase::Opcode::ReadFlBoolBeRev:
        case InstrBase::Opcode::ReadFlBoolLe:
        case InstrBase::Opcode::ReadFlBoolLeRev:
        case InstrBase::Opcode::ReadFlFloat32Be:
        case InstrBase::Opcode::ReadFlFloat32BeRev:
        case InstrBase::Opcode::ReadFlFloat32Le:
        case InstrBase::Opcode::ReadFlFloat32LeRev:
        case InstrBase::Opcode::ReadFlFloat64Be:
        case InstrBase::Opcode::ReadFlFloat64BeRev:
        case InstrBase::Opcode::ReadFlFloat64Le:
        case InstrBase::Opcode::ReadFlFloat64LeRev:
        case InstrBase::Opcode::ReadFlSIntBe:
        case InstrBase::Opcode::ReadFlSIntBeRev:
        case InstrBase::Opcode::ReadFlSIntLe:
        case InstrBase::Opcode::ReadFlSIntLeRev:
        case InstrBase::Opcode::ReadFlUIntBe:
        case InstrBase::Opcode::ReadFlUIntBeRev:
        case InstrBase::Opcode::ReadFlUIntLe:
        case InstrBase::Opcode::ReadFlUIntLeRev:
            this->_writeReadDataInstrProps(instr.asReadOddFlBitArray());
            this->_writeProp("data-len", instr.asReadOddFlBitArray().dataLen());
            this->_writeNl();
            _nucleo = instrBeginNucleo + instr.asReadOddFlBitArray().staticLen();
            break;

        case InstrBase::Opcode::ReadSlBlob:
        case InstrBase::Opcode::ReadSlStr:
        case InstrBase::Opcode::ReadSlUuidBlob:
            this->_writeReadSlDataInstrProps(instr.asReadSlData());
            this->_writeNl();
            _nucleo = instrBeginNucleo + instr.asReadSlData().staticLen();
            break;

        case InstrBase::Opcode::ReadSlArray:
        case InstrBase::Opcode::ReadSlUuidArray:
            this->_writeReadSlDataInstrProps(instr.asReadSlArray());
            this->_writeNl();
            this->_writeReadArrayElemPgm(instr.asReadSlArray());
            _nucleo = instrBeginNucleo + instr.asReadSlArray().len();
            break;

        case InstrBase::Opcode::ReadDlBlob:
        case InstrBase::Opcode::ReadDlStr:
            this->_writeReadDlDataInstrProps(instr.asReadDlData());
            this->_writeNl();
            _nucleo = instrBeginNucleo + instr.asReadDlData().staticLen();
            break;

        case InstrBase::Opcode::ReadDlArray:
            this->_writeReadDlDataInstrProps(instr.asReadDlArray());
            this->_writeNl();
            this->_writeReadArrayElemPgm(instr.asReadDlArray());
            _nucleo = instrBeginNucleo + instr.asReadDlArray().len();
            break;

        case InstrBase::Opcode::ReadStruct:
            this->_writeReadDataInstrProps(instr.asReadStruct());
            this->_writeProp("member-count",
                             instr.asReadData().dt().asStructureType().memberTypes().size());
            this->_writeNl();
            _nucleo = instr.asReadStruct().membersPgm().begin();
            this->_writeIndentedPgm("members pgm", InstrBase::Opcode::EndReadStruct);
            assert(InstrBase::fromNucleo(_nucleo).opcode() == InstrBase::Opcode::EndReadStruct);
            this->_writeCurInstr();
            break;

        case InstrBase::Opcode::ReadOptWithBoolSel:
            this->_writeReadOptInstrProps(instr.asReadOptWithBoolSel());
            this->_writeNl();
            this->_writeIndentedPgm("pgm", instr.asReadOptWithBoolSel().pgm(),
                                    instr.asReadOptWithBoolSel().pgmLen());
            _nucleo = instrBeginNucleo + instr.asReadOptWithBoolSel().len();
            break;

        case InstrBase::Opcode::ReadOptWithUIntSel:
            this->_writeReadOptWithIntSelInstrFull(instr.asReadOptWithUIntSel());
            _nucleo = instrBeginNucleo + instr.asReadOptWithUIntSel().len();
            break;

        case InstrBase::Opcode::ReadOptWithSIntSel:
            this->_writeReadOptWithIntSelInstrFull(instr.asReadOptWithSIntSel());
            _nucleo = instrBeginNucleo + instr.asReadOptWithSIntSel().len();
            break;

        case InstrBase::Opcode::ReadVarWithUIntSel:
            this->_writeReadVarWithIntSelInstrFull(instr.asReadVarWithUIntSel());
            _nucleo = instrBeginNucleo + instr.asReadVarWithUIntSel().len();
            break;

        case InstrBase::Opcode::ReadVarWithSIntSel:
            this->_writeReadVarWithIntSelInstrFull(instr.asReadVarWithSIntSel());
            _nucleo = instrBeginNucleo + instr.asReadVarWithSIntSel().len();
            break;

        case InstrBase::Opcode::ReadScope:
            this->_writeInstrBaseProps(instr.asReadScope());
            this->_writeProp("scope", instr.asReadScope().scope());
            this->_writeNl();
            _nucleo = instr.asReadScope().pgm().begin();
            this->_writeIndentedPgm("scope pgm", InstrBase::Opcode::EndReadScope);
            assert(InstrBase::fromNucleo(_nucleo).opcode() == InstrBase::Opcode::EndReadScope);
            this->_writeCurInstr();
            break;

        case InstrBase::Opcode::SaveCurInt:
            this->_writeInstrBaseProps(instr.asSaveCurInt());
            this->_writeProp("pos", instr.asSaveCurInt().pos());
            this->_writeNl();
            _nucleo = instrBeginNucleo + instr.asSaveCurInt().staticLen();
            break;

        case InstrBase::Opcode::UpdateDefClkValFlFromCurInt:
            this->_writeInstrBaseProps(instr.asUpdateDefClkValFlFromCurInt());
            this->_writeProp("cur-int-len", instr.asUpdateDefClkValFlFromCurInt().curIntLen());
            this->_writeNl();
            _nucleo = instrBeginNucleo + instr.asUpdateDefClkValFlFromCurInt().staticLen();
            break;

        case InstrBase::Opcode::EndReadArrayElem:
        case InstrBase::Opcode::EndReadDlArray:
        case InstrBase::Opcode::EndReadDlBlob:
        case InstrBase::Opcode::EndReadDlStr:
        case InstrBase::Opcode::EndReadDsErPreamble:
        case InstrBase::Opcode::EndReadDsPktPreamble:
        case InstrBase::Opcode::EndReadEr:
        case InstrBase::Opcode::EndReadOptWithBoolSel:
        case InstrBase::Opcode::EndReadOptWithSIntSel:
        case InstrBase::Opcode::EndReadOptWithUIntSel:
        case InstrBase::Opcode::EndReadPktPreamble:
        case InstrBase::Opcode::EndReadScope:
        case InstrBase::Opcode::EndReadSlArray:
        case InstrBase::Opcode::EndReadSlUuidArray:
        case InstrBase::Opcode::EndReadSlBlob:
        case InstrBase::Opcode::EndReadSlStr:
        case InstrBase::Opcode::EndReadSlUuidBlob:
        case InstrBase::Opcode::EndReadStruct:
        case InstrBase::Opcode::EndReadVarOpt:
        case InstrBase::Opcode::EndReadVarWithSIntSel:
        case InstrBase::Opcode::EndReadVarWithUIntSel:
        case InstrBase::Opcode::SetCurTypeIdFromCurInt:
        case InstrBase::Opcode::SetDsIdFromCurInt:
        case InstrBase::Opcode::SetDsInfo:
        case InstrBase::Opcode::SetDstFromCurTypeId:
        case InstrBase::Opcode::SetDstFromUnique:
        case InstrBase::Opcode::SetErInfo:
        case InstrBase::Opcode::SetErtFromCurTypeId:
        case InstrBase::Opcode::SetErtFromUnique:
        case InstrBase::Opcode::SetPktContentLenFromCurInt:
        case InstrBase::Opcode::SetPktDiscErCounterSnapFromCurInt:
        case InstrBase::Opcode::SetPktEndDefClkValFromCurInt:
        case InstrBase::Opcode::SetPktInfo:
        case InstrBase::Opcode::SetPktMagicNumberFromCurInt:
        case InstrBase::Opcode::SetPktSeqNumFromCurInt:
        case InstrBase::Opcode::SetPktTotalLenFromCurInt:
        case InstrBase::Opcode::UpdateDefClkValVlFromCurInt:
            this->_writeInstrBaseProps(instr);
            this->_writeNl();
            _nucleo = instrBeginNucleo + instr.staticLen();
            break;

        default:
            std::abort();
        }
    }

private:
    std::ostream *_os;
    Size _indent = 0;
    PgmView _curPgm {nullptr};
    const PgmNucleo *_nucleo;
};

} // namespace

std::ostream& operator<<(std::ostream& os, const PktPgm& pktPgm)
{
    Writer writer {os, pktPgm};

    return os;
}

} // namespace internal
} // namespace yactfr
