/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_INTERNAL_PSEUDO_TYPE_VISITOR_HPP
#define _YACTFR_METADATA_INTERNAL_PSEUDO_TYPE_VISITOR_HPP

#include "pseudo-types.hpp"

namespace yactfr {
namespace internal {

class PseudoDtVisitor
{
protected:
    explicit PseudoDtVisitor() = default;

public:
    virtual ~PseudoDtVisitor()
    {
    }

    virtual void visit(PseudoScalarDtWrapper&)
    {
    }

    virtual void visit(PseudoFlUIntType&)
    {
    }

    virtual void visit(PseudoFlUEnumType&)
    {
    }

    virtual void visit(PseudoSlArrayType&)
    {
    }

    virtual void visit(PseudoDlArrayType&)
    {
    }

    virtual void visit(PseudoSlBlobType&)
    {
    }

    virtual void visit(PseudoDlBlobType&)
    {
    }

    virtual void visit(PseudoStructType&)
    {
    }

    virtual void visit(PseudoVarType&)
    {
    }
};

class ConstPseudoDtVisitor
{
protected:
    explicit ConstPseudoDtVisitor() = default;

public:
    virtual ~ConstPseudoDtVisitor()
    {
    }

    virtual void visit(const PseudoScalarDtWrapper&)
    {
    }

    virtual void visit(const PseudoFlUIntType&)
    {
    }

    virtual void visit(const PseudoFlUEnumType&)
    {
    }

    virtual void visit(const PseudoSlArrayType&)
    {
    }

    virtual void visit(const PseudoDlArrayType&)
    {
    }

    virtual void visit(const PseudoSlBlobType&)
    {
    }

    virtual void visit(const PseudoDlBlobType&)
    {
    }

    virtual void visit(const PseudoStructType&)
    {
    }

    virtual void visit(const PseudoVarType&)
    {
    }
};

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_METADATA_INTERNAL_PSEUDO_TYPE_VISITOR_HPP