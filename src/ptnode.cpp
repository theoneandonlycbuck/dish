/*
    This file is part of the DISH programming language, Copyright 2014-2017 by 
    Chris Buck.
    
    DISH is free software for non-commercial use; you can redistribute it and/or
    modify it provided
    
        (1) The following Copyright notice is displayed at runtime and in any
            accompanying documentation:
    
            DISH programming language copyright (c) 2014-2017 by Chris Buck.
        
        (2) All source files duplicate this copyright statement in full.
        
    Commercial licenses can be negotiated by contacting Chris Buck at
    chrisbuck1220@hotmail.com.

    DISH is distributed in the hope that it will be useful, but WITHOUT ANY 
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS 
    FOR A PARTICULAR PURPOSE.
*/

#include <algorithm>
#include <sstream>

#include "exception.h"
#include "log.h"
#include "ptnode.h"
#include "utility.h"

/******************************************************************************

    dish::ParseTreeNode class definitions

 ******************************************************************************/
 
bool dish::ParseTreeNode::isEqual(const dish::NullParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::ReferenceParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::LiteralParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::LiteralArrayParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::IdentifierParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::LockParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::BooleanTypeParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::IntegerTypeParseTreeNode &ptn) const
{
    return false;
}

bool dish::ParseTreeNode::isEqual(const dish::RangedIntegerTypeParseTreeNode &ptn) const
{
    return false;
}            
 
bool dish::ParseTreeNode::isEqual(const dish::RealTypeParseTreeNode &ptn) const
{
    return false;
}

bool dish::ParseTreeNode::isEqual(const dish::RangedRealTypeParseTreeNode &ptn) const
{
    return false;
} 
 
bool dish::ParseTreeNode::isEqual(const dish::StringTypeParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::ArrayTypeParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::DictionaryTypeParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::StructureTypeParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::DeclareParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::DeclareTypeParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::DeclareFunctionParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::DeclareReferenceParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::AssignmentParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::IndexParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::MemberParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::FunctionCallParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::ReturnParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::NegateOpParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::AddOpChainParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::SubOpParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::MulOpChainParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::DivOpParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::ModOpParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::PowOpParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::NotOpParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::AndOpChainParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::OrOpChainParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::XorOpChainParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::LessThanOpParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::LessThanEqualOpParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::EqualOpParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::NotEqualOpParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::GreaterThanEqualOpParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::GreaterThanOpParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::StatementBlockParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::IfStatementParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::SwitchStatementParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::ForLoopParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::ForEachLoopParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::WhileLoopParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::RepeatUntilLoopParseTreeNode &ptn) const
{
    return false;
}
 
bool dish::ParseTreeNode::isEqual(const dish::AssertParseTreeNode &ptn) const
{
    return false;
}
 
const std::string &dish::ParseTreeNode::LocationString() const
{
    return mLocationString;
}
 
bool dish::ParseTreeNode::IsLiteral() const
{
    return false;
}

std::shared_ptr< dish::iAtomic > dish::ParseTreeNode::Execute()
{
    std::stringstream message;
    message << LocationString() << " : ";
    message << "Evaluating this parse-tree node, <";
    Print(message);
    message << ">, requires context (i.e. a symbol table).";

    throw NonLiteralExpressionException(LocationString(), message.str());
}

void dish::ParseTreeNode::Validate(LanguageSymbolTable &symtab) const
{
    //  Empty
}

bool dish::ParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return false;
}

const std::string &dish::ParseTreeNode::ToString() const
{
    static const std::string StringRep("(empty)");
    
    return StringRep;
}

void dish::ParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << "<ERROR>";
}

/******************************************************************************

    dish::NullParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::NullParseTreeNode::Count(0);
dish::IntegerT dish::NullParseTreeNode::Instances(0);

bool dish::NullParseTreeNode::isEqual(const dish::NullParseTreeNode &ptn) const
{
    return true;
}

std::shared_ptr< dish::NullParseTreeNode > dish::NullParseTreeNode::MakeValue()
{
    static std::shared_ptr< NullParseTreeNode > node(new NullParseTreeNode());
    
    return node;
}
 
std::shared_ptr< dish::iAtomic > dish::NullParseTreeNode::Execute(LanguageSymbolTable &symtab)
{
    return NullValue::MakeValue();
}

bool dish::NullParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::NullParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << "PTN: (null)";
}

/******************************************************************************

    dish::ReferenceParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::ReferenceParseTreeNode::Count(0);
dish::IntegerT dish::ReferenceParseTreeNode::Instances(0);

bool dish::ReferenceParseTreeNode::isEqual(const dish::ReferenceParseTreeNode &ptn) const
{
    const iAtomic::TypeT type(mReference->Type());

    if(type == ptn.mReference->Type())
    {
        switch(type)
        {
            case iAtomic::typeBoolean:
            {
                return dish::IsEqual(mReference->AsBoolean(), ptn.mReference->AsBoolean());
            }
            
            case iAtomic::typeInteger:
            {
                return dish::IsEqual(mReference->AsInteger(), ptn.mReference->AsInteger());
            }
            
            case iAtomic::typeReal:
            {
                return dish::IsEqual(mReference->AsReal(), ptn.mReference->AsReal());
            }
            
            case iAtomic::typeString:
            {
                return dish::IsEqual(mReference->AsString(), ptn.mReference->AsString(), CASE_SENSITIVE);
            }
            
            default:
            {
                //  All other literal values will be considered not to be equal.
                //  This is used for an optimization so 
            }
            
        }
    }
    
    return false;
}

bool dish::ReferenceParseTreeNode::IsLiteral() const
{
    //  We will treat a reference-parse-tree-node as a non-literal to prevent it
    //  from being turned into another reference itself. Basically, this is the
    //  base-case of a recursive simplification at parse-time.
    return false;
}

std::shared_ptr< dish::iAtomic > dish::ReferenceParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    return mReference;
}

bool dish::ReferenceParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::ReferenceParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{    
    printIndent(out, indent);
    
    out << "PTN: Ref(";
    mReference->Print(out);
    out << ")";
}

/******************************************************************************

    dish::LiteralParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::LiteralParseTreeNode::Count(0);
dish::IntegerT dish::LiteralParseTreeNode::Instances(0);

std::map< dish::IntegerT, std::shared_ptr< dish::LiteralParseTreeNode > > dish::LiteralParseTreeNode::CachedIntegerLiteralNodes;
std::map< dish::RealT, std::shared_ptr< dish::LiteralParseTreeNode > > dish::LiteralParseTreeNode::CachedRealLiteralNodes;
std::map< dish::StringT, std::shared_ptr< dish::LiteralParseTreeNode > > dish::LiteralParseTreeNode::CachedStringLiteralNodes;

bool dish::LiteralParseTreeNode::isEqual(const dish::LiteralParseTreeNode &ptn) const
{
    const iAtomic::TypeT type(mLiteral->Type());

    if(type == ptn.mLiteral->Type())
    {
        switch(type)
        {
            case iAtomic::typeBoolean:
            {
                return dish::IsEqual(mLiteral->AsBoolean(), ptn.mLiteral->AsBoolean());
            }
            
            case iAtomic::typeInteger:
            {
                return dish::IsEqual(mLiteral->AsInteger(), ptn.mLiteral->AsInteger());
            }
            
            case iAtomic::typeReal:
            {
                return dish::IsEqual(mLiteral->AsReal(), ptn.mLiteral->AsReal());
            }
            
            case iAtomic::typeString:
            {
                return dish::IsEqual(mLiteral->AsString(), ptn.mLiteral->AsString(), CASE_SENSITIVE);
            }
            
            default:
            {
                //  All other literal values will be considered not to be equal.
                //  This is used for an optimization so 
            }
            
        }
    }
    
    return false;
}

std::shared_ptr< dish::LiteralParseTreeNode > dish::LiteralParseTreeNode::MakeValue(const dish::BooleanT &value)
{
    if(value)
    {
        static std::shared_ptr< LiteralParseTreeNode > true_literal(new LiteralParseTreeNode(true));
        
        return true_literal;
    }
    else
    {
        static std::shared_ptr< LiteralParseTreeNode > false_literal(new LiteralParseTreeNode(false));
        
        return false_literal;
    }
    
    assert(false);
}

std::shared_ptr< dish::LiteralParseTreeNode > dish::LiteralParseTreeNode::MakeValue(const dish::IntegerT &value)
{
    const auto cached(CachedIntegerLiteralNodes.find(value));
    if(CachedIntegerLiteralNodes.end() != cached)
    {
        return cached->second;
    }
    
    std::shared_ptr< LiteralParseTreeNode > node(new LiteralParseTreeNode(value));
    CachedIntegerLiteralNodes[value] = node;
    
    return node;
}

std::shared_ptr< dish::LiteralParseTreeNode > dish::LiteralParseTreeNode::MakeValue(const dish::RealT &value)
{
    const auto cached(CachedRealLiteralNodes.find(value));
    if(CachedRealLiteralNodes.end() != cached)
    {
        return cached->second;
    }
    
    std::shared_ptr< LiteralParseTreeNode > node(new LiteralParseTreeNode(value));
    CachedRealLiteralNodes[value] = node;
    
    return node;
}

std::shared_ptr< dish::LiteralParseTreeNode > dish::LiteralParseTreeNode::MakeValue(const dish::StringT &value)
{
    const auto cached(CachedStringLiteralNodes.find(value));
    if(CachedStringLiteralNodes.end() != cached)
    {
        return cached->second;
    }
    
    std::shared_ptr< LiteralParseTreeNode > node(new LiteralParseTreeNode(value));
    CachedStringLiteralNodes[value] = node;
    
    return node;
}

bool dish::LiteralParseTreeNode::IsLiteral() const
{
    return true;
}

dish::IntegerT dish::LiteralParseTreeNode::ReleaseCachedParseTreeNodes()
{
    IntegerT numnodes(0);
    
    numnodes += NumCachedIntegerLiteralNodes();
    CachedIntegerLiteralNodes.clear();
    
    numnodes += NumCachedRealLiteralNodes();
    CachedRealLiteralNodes.clear();
    
    numnodes += NumCachedStringLiteralNodes();
    CachedStringLiteralNodes.clear();
    
    return numnodes;
}

std::shared_ptr< dish::iAtomic > dish::LiteralParseTreeNode::Execute()
{
    return mLiteral->Clone();
}

std::shared_ptr< dish::iAtomic > dish::LiteralParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    return mLiteral->Clone();
}

bool dish::LiteralParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::LiteralParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    
    out << "PTN: Lit(";
    mLiteral->Print(out, indent);
    out << ")";
}

/******************************************************************************

    dish::LiteralArrayParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::LiteralArrayParseTreeNode::Count(0);
dish::IntegerT dish::LiteralArrayParseTreeNode::Instances(0);
 
bool dish::LiteralArrayParseTreeNode::IsLiteral() const
{
    return false;
}

std::shared_ptr< dish::iAtomic > dish::LiteralArrayParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    std::shared_ptr< ArrayValue > array(ArrayValue::MakeValue(0));
    
    std::for_each(
        mElements.begin(), mElements.end(),
        [&](ElementT::value_type &elem)
        {
            array->Add(elem->Execute(symtab), array->mValue.size());
        }
    );
    
    return array;
}

void dish::LiteralArrayParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);

    out << "PTN: lit-array{";
    
    ElementT::const_iterator i(mElements.begin());
    const ElementT::const_iterator last_i(mElements.end());
    
    if(i != last_i)
    {
        out << " ";
        (*i)->Print(out, 0);
        
        std::for_each(
            ++i, last_i,
            [&](const ElementT::value_type &value)
            {
                out << ", ";
                value->Print(out, 0);
            }
        );
    }
    
    out << " }";
}

/******************************************************************************

    dish::IdentifierParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::IdentifierParseTreeNode::Count(0);
dish::IntegerT dish::IdentifierParseTreeNode::Instances(0);

std::map< std::string, std::shared_ptr< dish::IdentifierParseTreeNode > > dish::IdentifierParseTreeNode::CachedNodes;

bool dish::IdentifierParseTreeNode::isEqual(const dish::IdentifierParseTreeNode &ptn) const
{
    static const std::string prefix("`");
    
    if(!mBaseId)
    {
        if(!ptn.mBaseId)
        {
            return (mId == ptn.mId);
        }
        
        return (mId == (prefix + ptn.mId));
    }
    
    return ((prefix + mId) == (prefix + ptn.mId));
}

std::shared_ptr< dish::IdentifierParseTreeNode > dish::IdentifierParseTreeNode::MakeValue(const std::string &id)
{
    const auto cached(CachedNodes.find(id));
    if(CachedNodes.end() != cached)
    {
        return cached->second;
    }
    
    std::shared_ptr< dish::IdentifierParseTreeNode > node(new IdentifierParseTreeNode(id));
    CachedNodes[id] = node;
    
    return node;
}

dish::IntegerT dish::IdentifierParseTreeNode::ReleaseCachedParseTreeNodes()
{
    const IntegerT numnodes(NumCachedNodes());
    
    CachedNodes.clear();
    
    return numnodes;
}
 
std::shared_ptr< dish::iAtomic > dish::IdentifierParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    try
    {
        return (mBaseId ? symtab.LookupInBase(mId) : symtab.Lookup(mId));
    }
    
    catch(DishException &e)
    {
        if(!e.IsLocationSupplied())
        {
            e.AddLocation(LocationString());
        }
        
        throw;
    }
    
    assert(false);
}

void dish::IdentifierParseTreeNode::Validate(LanguageSymbolTable &symtab) const
{
    try
    {
        symtab.Lookup(mId);
    }
    
    catch(DishException &e)
    {
        if(!e.IsLocationSupplied())
        {
            e.AddLocation(LocationString());
        }
        
        throw;
    }
}

bool dish::IdentifierParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

const std::string &dish::IdentifierParseTreeNode::ToString() const
{
    return mId;
}

void dish::IdentifierParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    
    out << "PTN: ID(";
    out << mId;
    out << ")";
}

/******************************************************************************

    dish::LockParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::LockParseTreeNode::Count(0);
dish::IntegerT dish::LockParseTreeNode::Instances(0);

bool dish::LockParseTreeNode::isEqual(const dish::LockParseTreeNode &ptn) const
{
    return (mId == ptn.mId);
}
 
std::shared_ptr< dish::iAtomic > dish::LockParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    symtab.Lookup(mId)->Lock();
    
    return NullValue::MakeValue();
}

bool dish::LockParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::LockParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << "PTN: lock(";
    out << mId;
    out << ")";
}

/******************************************************************************

    dish::BooleanTypeParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::BooleanTypeParseTreeNode::Count(0);
dish::IntegerT dish::BooleanTypeParseTreeNode::Instances(0);

bool dish::BooleanTypeParseTreeNode::isEqual(const dish::BooleanTypeParseTreeNode &ptn) const
{
    return true;
}
 
std::shared_ptr< dish::iAtomic > dish::BooleanTypeParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    return BooleanTypeAtomic::MakeValue();
}

bool dish::BooleanTypeParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::BooleanTypeParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << "PTN: boolean-type";
}

/******************************************************************************

    dish::IntegerTypeParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::IntegerTypeParseTreeNode::Count(0);
dish::IntegerT dish::IntegerTypeParseTreeNode::Instances(0);

bool dish::IntegerTypeParseTreeNode::isEqual(const dish::IntegerTypeParseTreeNode &ptn) const
{
    return true;
}
 
std::shared_ptr< dish::iAtomic > dish::IntegerTypeParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    return IntegerTypeAtomic::MakeValue();
}

bool dish::IntegerTypeParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::IntegerTypeParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << "PTN: integer-type";
}

/******************************************************************************

    dish::RangedIntegerTypeParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::RangedIntegerTypeParseTreeNode::Count(0);
dish::IntegerT dish::RangedIntegerTypeParseTreeNode::Instances(0);

bool dish::RangedIntegerTypeParseTreeNode::isEqual(const dish::RangedIntegerTypeParseTreeNode &ptn) const
{
    return true;
}
 
std::shared_ptr< dish::iAtomic > dish::RangedIntegerTypeParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    iAtomic::RangeBoundsT bounds(iAtomic::rngbndError);
    switch(mBoundary->Execute(symtab)->AsInteger())
    {
        case static_cast< IntegerT >(iAtomic::rngbndError):
        {
            bounds = iAtomic::rngbndError;
        } break;
        
        case static_cast< IntegerT >(iAtomic::rngbndCap):
        {
            bounds = iAtomic::rngbndCap;
        } break;
        
        case static_cast< IntegerT >(iAtomic::rngbndRollover):
        {
            bounds = iAtomic::rngbndRollover;
        } break;
        
        default:
        {
            //  Empty
        }
        
    }

    return RangedIntegerTypeAtomic::MakeValue(
        mMinimum->Execute(symtab)->AsInteger(),
        mMaximum->Execute(symtab)->AsInteger(),
        bounds
    );
}

bool dish::RangedIntegerTypeParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::RangedIntegerTypeParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << "PTN: ranged-integer-type(";
    mMinimum->Print(out, 0);
    out << ", ";
    mMaximum->Print(out, 0);
    out << ", ";
    mBoundary->Print(out, 0);
    out << ")";
}

/******************************************************************************

    dish::RealTypeParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::RealTypeParseTreeNode::Count(0);
dish::IntegerT dish::RealTypeParseTreeNode::Instances(0);

bool dish::RealTypeParseTreeNode::isEqual(const dish::RealTypeParseTreeNode &ptn) const
{
    return true;
}
 
std::shared_ptr< dish::iAtomic > dish::RealTypeParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    return RealTypeAtomic::MakeValue();
}

bool dish::RealTypeParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::RealTypeParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << "PTN: real-type";
}

/******************************************************************************

    dish::RangedRealTypeParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::RangedRealTypeParseTreeNode::Count(0);
dish::IntegerT dish::RangedRealTypeParseTreeNode::Instances(0);

bool dish::RangedRealTypeParseTreeNode::isEqual(const dish::RangedRealTypeParseTreeNode &ptn) const
{
    return true;
}
 
std::shared_ptr< dish::iAtomic > dish::RangedRealTypeParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    iAtomic::RangeBoundsT bounds(iAtomic::rngbndError);
    switch(mBoundary->Execute(symtab)->AsInteger())
    {
        case static_cast< IntegerT >(iAtomic::rngbndError):
        {
            bounds = iAtomic::rngbndError;
        } break;
        
        case static_cast< IntegerT >(iAtomic::rngbndCap):
        {
            bounds = iAtomic::rngbndCap;
        } break;
        
        case static_cast< IntegerT >(iAtomic::rngbndRollover):
        {
            bounds = iAtomic::rngbndRollover;
        } break;
        
        default:
        {
            //  Empty
        }
        
    }

    return RangedRealTypeAtomic::MakeValue(
        mMinimum->Execute(symtab)->AsReal(),
        mMaximum->Execute(symtab)->AsReal(),
        bounds
    );
}

bool dish::RangedRealTypeParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::RangedRealTypeParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << "PTN: ranged-real-type(";
    mMinimum->Print(out, 0);
    out << ", ";
    mMaximum->Print(out, 0);
    out << ", ";
    mBoundary->Print(out, 0);
    out << ")";
}

/******************************************************************************

    dish::StringTypeParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::StringTypeParseTreeNode::Count(0);
dish::IntegerT dish::StringTypeParseTreeNode::Instances(0);

bool dish::StringTypeParseTreeNode::isEqual(const dish::StringTypeParseTreeNode &ptn) const
{
    return true;
}
 
std::shared_ptr< dish::iAtomic > dish::StringTypeParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    return StringTypeAtomic::MakeValue();
}

bool dish::StringTypeParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::StringTypeParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << "PTN: string-type";
}

/******************************************************************************

    dish::ArrayTypeParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::ArrayTypeParseTreeNode::Count(0);
dish::IntegerT dish::ArrayTypeParseTreeNode::Instances(0);

bool dish::ArrayTypeParseTreeNode::isEqual(const dish::ArrayTypeParseTreeNode &ptn) const
{
    return (
        mFromIndex->IsEqual(*(ptn.mFromIndex)) &&
        mToIndex->IsEqual(*(ptn.mToIndex)) &&
        mType->IsEqual(*(ptn.mType))
    );
}

std::shared_ptr< dish::iAtomic > dish::ArrayTypeParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    return ArrayTypeAtomic::MakeValue(
        mFromIndex->Execute(symtab)->AsInteger(), 
        mToIndex->Execute(symtab)->AsInteger(), 
        mType->Execute(symtab)
    );
}

void dish::ArrayTypeParseTreeNode::Validate(LanguageSymbolTable &symtab) const
{
    mFromIndex->Validate(symtab);
    mToIndex->Validate(symtab);
    mType->Validate(symtab);
}

bool dish::ArrayTypeParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::ArrayTypeParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    
    out << "PTN: array-type [";
    mFromIndex->Print(out, 0);
    out << " to ";
    mToIndex->Print(out, 0);
    out << "] of ";
    mType->Print(out, 0);
}

/******************************************************************************

    dish::DictionaryTypeParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::DictionaryTypeParseTreeNode::Count(0);
dish::IntegerT dish::DictionaryTypeParseTreeNode::Instances(0);

bool dish::DictionaryTypeParseTreeNode::isEqual(const dish::DictionaryTypeParseTreeNode &ptn) const
{
    return true;
}
 
std::shared_ptr< dish::iAtomic > dish::DictionaryTypeParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    return DictionaryTypeAtomic::MakeValue();
}

bool dish::DictionaryTypeParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::DictionaryTypeParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    
    out << "PTN: dictionary-type";
}

/******************************************************************************

    dish::StructureTypeParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::StructureTypeParseTreeNode::Count(0);
dish::IntegerT dish::StructureTypeParseTreeNode::Instances(0);
 
void dish::StructureTypeParseTreeNode::Add(const std::string &id, std::shared_ptr< dish::iParseTreeNode > type)
{
    assert(type);
    
    mStructureNode.reset();
    
    mMemberList.push_back(std::make_pair(id, type));
}
 
std::shared_ptr< dish::iAtomic > dish::StructureTypeParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    if(mStructureNode)
    {
        return mStructureNode;
    }

    mStructureNode = StructureTypeAtomic::MakeValue();
    
    std::for_each(
        mMemberList.begin(), mMemberList.end(),
        [&](const MemberListT::value_type &member)
        {
            mStructureNode->Add(member.first, member.second->Execute(symtab));
        }
    );
    
    return mStructureNode;
}

void dish::StructureTypeParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    
    out << "PTN: structure-type(" << std::endl;
    
    std::for_each(
        mMemberList.begin(), mMemberList.end(),
        [&](const MemberListT::value_type &member)
        {
            out << "  ";
            out << member.second;
            out << ": ";
            member.second->Print(out, 0);
        }
    );
    
    out << "  )";
}

/******************************************************************************

    dish::DeclareParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::DeclareParseTreeNode::Count(0);
dish::IntegerT dish::DeclareParseTreeNode::Instances(0);

bool dish::DeclareParseTreeNode::isEqual(const dish::DeclareParseTreeNode &ptn) const
{
    return (
        mType->IsEqual(*(ptn.mType)) &&
        (mId == ptn.mId)
    );
}

std::shared_ptr< dish::iAtomic > dish::DeclareParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    std::shared_ptr< dish::iAtomic > value(mType->Execute(symtab)->Declare());
    
    symtab.Insert(mId, value);
    
    return value;
}

void dish::DeclareParseTreeNode::Validate(LanguageSymbolTable &symtab) const
{
    mType->Validate(symtab);
    
    symtab.Insert(mId, NullValue::MakeValue());
}

bool dish::DeclareParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::DeclareParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    
    out << "PTN: declare ";
    mType->Print(out, 0);
    out << " as ";
    out << mId;
}

/******************************************************************************

    dish::DeclareTypeParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::DeclareTypeParseTreeNode::Count(0);
dish::IntegerT dish::DeclareTypeParseTreeNode::Instances(0);

bool dish::DeclareTypeParseTreeNode::isEqual(const dish::DeclareTypeParseTreeNode &ptn) const
{
    return (
        mType->IsEqual(*(ptn.mType)) &&
        (mId == ptn.mId)
    );
}

std::shared_ptr< dish::iAtomic > dish::DeclareTypeParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    std::shared_ptr< dish::iAtomic > value(mType->Execute(symtab));
    
    symtab.Insert(mId, value);
    
    return value;
}

void dish::DeclareTypeParseTreeNode::Validate(LanguageSymbolTable &symtab) const
{
    mType->Validate(symtab);
    
    symtab.Insert(mId, NullValue::MakeValue());
}

bool dish::DeclareTypeParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::DeclareTypeParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << "PTN: declare type ";
    mType->Print(out, 0);
    out << " as ";
    out << mId;
}

/******************************************************************************

    dish::FunctionParseTreeNode::FunctionValue class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::FunctionParseTreeNode::FunctionValue::Execute(dish::LanguageSymbolTable &symtab) const
{
    return mBody->Execute(symtab);
}

void dish::FunctionParseTreeNode::FunctionValue::Validate(LanguageSymbolTable &symtab) const
{
    mBody->Validate(symtab);
}

/******************************************************************************

    dish::DeclareFunctionParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::DeclareFunctionParseTreeNode::Count(0);
dish::IntegerT dish::DeclareFunctionParseTreeNode::Instances(0);

std::shared_ptr< dish::iAtomic > dish::DeclareFunctionParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    symtab.Insert(mId, FunctionValue::MakeValue(formalParameters(), body()));
    
    return NullValue::MakeValue();
}

void dish::DeclareFunctionParseTreeNode::Validate(LanguageSymbolTable &symtab) const
{
    //  First validate the function's body; this requires the formal parameters
    //  be added to the symbol table.
    {
        ScopedScope scope(symtab);
        
        std::for_each(
            formalParameters().begin(), formalParameters().end(),
            [&](const ParamListT::value_type &param)
            {
                symtab.Insert(param.first, NullValue::MakeValue());
            }
        );
        
        body()->Validate(symtab);
    }
    
    //  Add the Function ID.
    std::shared_ptr< iParseTreeNode > null(NullParseTreeNode::MakeValue(LocationString()));
    symtab.Insert(
        mId, 
        FunctionValue::MakeValue(formalParameters(), null)
    );
}

void dish::DeclareFunctionParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    
    out << "PTN: declare function ";
    out << mId;
    out << "(";
    
    {
        ParamListT::const_iterator first(formalParameters().begin());
        const ParamListT::const_iterator last(formalParameters().end());
        
        if(last != first)
        {
            if(first->second)
            {
                out << "&";
            }
            
            out << first->first;
        
            std::for_each(
                ++first, last,
                [&](const ParamListT::value_type &param)
                {
                    out << ", ";
                
                    if(param.second)
                    {
                        out << "&";
                    }
                    
                    out << param.first;
                }
            );
        }
    }
    
    out << ")";
    out << std::endl;
    
    body()->Print(out, indent + 4);
}

/******************************************************************************

    dish::LambdaFunctionParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::LambdaFunctionParseTreeNode::Count(0);
dish::IntegerT dish::LambdaFunctionParseTreeNode::Instances(0);

std::shared_ptr< dish::iAtomic > dish::LambdaFunctionParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    return DeclareFunctionParseTreeNode::FunctionValue::MakeValue(formalParameters(), body());
}

void dish::LambdaFunctionParseTreeNode::Validate(dish::LanguageSymbolTable &symtab) const
{
    //  Validate the function's body; this requires the formal parameters be
    //  added to the symbol table.
    ScopedScope scope(symtab);
    
    std::for_each(
        formalParameters().begin(), formalParameters().end(),
        [&](const ParamListT::value_type &param)
        {
            symtab.Insert(param.first, NullValue::MakeValue());
        }
    );
    
    body()->Validate(symtab);
}

void dish::LambdaFunctionParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    
    out << "PTN: lambda(";
    
    {
        ParamListT::const_iterator first(formalParameters().begin());
        const ParamListT::const_iterator last(formalParameters().end());
        
        if(last != first)
        {
            if(first->second)
            {
                out << "&";
            }
            
            out << first->first;
        
            std::for_each(
                ++first, last,
                [&](const ParamListT::value_type &param)
                {
                    out << ", ";
                
                    if(param.second)
                    {
                        out << "&";
                    }
                    
                    out << param.first;
                }
            );
        }
    }
    
    out << ")";
    out << std::endl;
    
    body()->Print(out, indent + 4);
}

/******************************************************************************

    dish::DeclareReferenceParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::DeclareReferenceParseTreeNode::Count(0);
dish::IntegerT dish::DeclareReferenceParseTreeNode::Instances(0);

std::shared_ptr< dish::iAtomic > dish::DeclareReferenceParseTreeNode::Execute(LanguageSymbolTable &symtab)
{
    std::shared_ptr< dish::iAtomic > value(ReferenceValue::MakeValue(mExpression->Execute(symtab)));

    symtab.Insert(mId, value);
    
    return value;
}

void dish::DeclareReferenceParseTreeNode::Validate(LanguageSymbolTable &symtab) const
{
    mExpression->Validate(symtab);

    symtab.Insert(mId, NullValue::MakeValue());
}

void dish::DeclareReferenceParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    
    out << "PTN: declare ";
    out << mId;
    out << " = ";
    mExpression->Print(out, 0);
}

/******************************************************************************

    dish::AssignmentParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::AssignmentParseTreeNode::Count(0);
dish::IntegerT dish::AssignmentParseTreeNode::Instances(0);

bool dish::AssignmentParseTreeNode::isEqual(const dish::AssignmentParseTreeNode &ptn) const
{
    return (
        mLeftHandSide->IsEqual(*(ptn.mLeftHandSide)) &&
        mRightHandSide->IsEqual(*(ptn.mRightHandSide))
    );
}

std::shared_ptr< dish::iAtomic > dish::AssignmentParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    try
    {
        std::shared_ptr< dish::iAtomic > lhs(mLeftHandSide->Execute(symtab));
        
        lhs->Assign(mRightHandSide->Execute(symtab));
        
        return lhs;
    }
    
    catch(DishException &e)
    {
        if(!e.IsLocationSupplied())
        {
            e.AddLocation(LocationString());
        }
        
        throw;
    }
}

void dish::AssignmentParseTreeNode::Validate(LanguageSymbolTable &symtab) const
{
    mLeftHandSide->Validate(symtab);
    mRightHandSide->Validate(symtab);
}

bool dish::AssignmentParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::AssignmentParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    
    out << "PTN: Assign(";
    mLeftHandSide->Print(out, 0);
    out << " = ";
    mRightHandSide->Print(out, 0);
    out << ")";
}

/******************************************************************************

    dish::IndexParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::IndexParseTreeNode::Count(0);
dish::IntegerT dish::IndexParseTreeNode::Instances(0);

bool dish::IndexParseTreeNode::isEqual(const dish::IndexParseTreeNode &ptn) const
{
    return (
        mBase->IsEqual(*(ptn.mBase)) &&
        mIndex->IsEqual(*(ptn.mIndex))
    );
}

std::shared_ptr< dish::iAtomic > dish::IndexParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    try
    {
        std::shared_ptr< dish::iAtomic > base(mBase->Execute(symtab));
        std::shared_ptr< dish::iAtomic > index(mIndex->Execute(symtab));
        
        if((iAtomic::typeInteger == index->Type()) && (iAtomic::typeDictionary != base->Type()))
        {
            return base->Element(index->AsInteger());
        }
        
        return base->Lookup(index->AsString());
    }
    
    catch(DishException &e)
    {
        if(!e.IsLocationSupplied())
        {
            e.AddLocation(LocationString());
        }
        
        throw;
    }
}

void dish::IndexParseTreeNode::Validate(LanguageSymbolTable &symtab) const
{
    mBase->Validate(symtab);
    mIndex->Validate(symtab);
}

bool dish::IndexParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::IndexParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    
    out << "PTN: Index(";
    mBase->Print(out, 0);
    out << "[";
    mIndex->Print(out, 0);
    out << "])";
}

/******************************************************************************

    dish::MemberParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::MemberParseTreeNode::Count(0);
dish::IntegerT dish::MemberParseTreeNode::Instances(0);

bool dish::MemberParseTreeNode::isEqual(const dish::MemberParseTreeNode &ptn) const
{
    return (
        (mMember == ptn.mMember) &&
        mBase->IsEqual(*(ptn.mBase))
    );
}

std::shared_ptr< dish::iAtomic > dish::MemberParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    try
    {
        return mBase->Execute(symtab)->Member(mMember);
    }
    
    catch(DishException &e)
    {
        if(!e.IsLocationSupplied())
        {
            e.AddLocation(LocationString());
        }
        
        throw;
    }
}

void dish::MemberParseTreeNode::Validate(LanguageSymbolTable &symtab) const
{
    mBase->Validate(symtab);
}

bool dish::MemberParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::MemberParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    
    out << "PTN: Member(";
    mBase->Print(out, 0);
    out << ".";
    out << mMember;
    out << ")";
}

/******************************************************************************

    dish::FunctionCallParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::FunctionCallParseTreeNode::Count(0);
dish::IntegerT dish::FunctionCallParseTreeNode::Instances(0);

bool dish::FunctionCallParseTreeNode::isEqual(const dish::FunctionCallParseTreeNode &ptn) const
{
    if(mFunction->IsEqual(*(ptn.mFunction)))
    {
        if(mParameterList.size() == ptn.mParameterList.size())
        {
            ParameterListT::const_iterator i(mParameterList.begin());
            const ParameterListT::const_iterator last_i(mParameterList.end());
            
            ParameterListT::const_iterator ptn_i(ptn.mParameterList.begin());
            const ParameterListT::const_iterator ptn_last_i(ptn.mParameterList.end());
            
            while((i != last_i) && (ptn_i != ptn_last_i))
            {
                if(!(*i)->IsEqual(**ptn_i))
                {
                    return false;
                }
                
                ++i;
                ++ptn_i;
            }
        
            assert(i == last_i);
            assert(ptn_i == ptn_last_i);
        
            return true;
        }
    }

    return false;
}

std::shared_ptr< dish::iAtomic > dish::FunctionCallParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    //  Get the function object.
    std::shared_ptr< dish::iAtomic > function(mFunction->Execute(symtab));
    
    //  Get the formal parameter list of the function.
    const iExecutableAtomic::ParamListT &formalparams(function->ParameterList());
    
    //  Make sure the number of actual parameters matches the number of formal
    //  parameters.
    if(mParameterList.size() == formalparams.size())
    {
        std::string fsignature;
        
        if(symtab.CollectExecutionProfile())
        {
            fsignature = mFunction->ToString();
            fsignature = fsignature.substr(0, fsignature.find_last_of('_'));
            fsignature += "(";
        }
    
        //  Does the function accept parameters?
        if(mParameterList.empty())
        {
            //  No, there are no parameters. Make the function call.
            try
            {
                std::shared_ptr< ExecutionProfile::AccumulateTime > profile;
                if(symtab.CollectExecutionProfile())
                {
                    fsignature += ")";
                    profile = symtab.ProfileInformation().ScopedProfileAccumulator(fsignature);
                }
            
                return function->Execute(symtab);
            }
            
            catch(ReturnParseTreeNode::ReturnValueT e)
            {
                return e;
            }
        }
        else
        {   
            //  Yes, there are parameters. Create a new symbol-table to store
            //  the actual parameters.
            std::shared_ptr< BasicSymbolTable > table(BasicSymbolTable::MakeValue());
            
            //  Loop through the formal- and actual-parameter lists and add them
            //  to the new table.
            ParameterListT::const_iterator ap_i(mParameterList.begin());
            const ParameterListT::const_iterator ap_last_i(mParameterList.end());
    
            iExecutableAtomic::ParamListT::const_iterator fp_i(formalparams.begin());
            const iExecutableAtomic::ParamListT::const_iterator fp_last_i(formalparams.end());
            
            if(!symtab.CollectExecutionProfile())
            {
                while((ap_i != ap_last_i) && (fp_i != fp_last_i))
                {
                    table->Insert(fp_i->first, fp_i->second ? (*ap_i)->Execute(symtab) : (*ap_i)->Execute(symtab)->Clone());
                    
                    ++ap_i;
                    ++fp_i;
                }
            }
            else
            {
                for(bool first(true); (ap_i != ap_last_i) && (fp_i != fp_last_i); ++ap_i, ++fp_i)
                {
                    if(!first)
                    {
                        fsignature += ", ";
                    }
                    else
                    {
                        first = false;
                    }
                    if(fp_i->second)
                    {
                        fsignature += "&";
                    }
                    fsignature += fp_i->first;
                
                    table->Insert(fp_i->first, fp_i->second ? (*ap_i)->Execute(symtab) : (*ap_i)->Execute(symtab)->Clone());
                }
            }
        
            assert(ap_last_i == ap_i);
            assert(fp_last_i == fp_i);
            
            //  Add a new scope with the parameters to the stack.
            ScopedScope scope(symtab, table);
        
            //  Make the function call.
            try
            {
                std::shared_ptr< ExecutionProfile::AccumulateTime > profile;
                if(symtab.CollectExecutionProfile())
                {
                    fsignature += ")";
                    profile = symtab.ProfileInformation().ScopedProfileAccumulator(fsignature);
                }
            
                return function->Execute(symtab);
            }
            
            catch(ReturnParseTreeNode::ReturnValueT e)
            {
                return e;
            }
        }
    }
    
    std::stringstream message;
    message << LocationString() << " : ";
    message << "Syntax error: Incorrect number of arguments in call to function '";
    mFunction->Print(message);
    message << "'.";
    
    throw SyntaxErrorException(LocationString(), message.str());
}

void dish::FunctionCallParseTreeNode::Validate(LanguageSymbolTable &symtab) const
{
    std::for_each(
        mParameterList.begin(), mParameterList.end(),
        [&](const ParameterListT::value_type &param)
        {
            param->Validate(symtab);
        }
    );
    
    mFunction->Validate(symtab);
}

bool dish::FunctionCallParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::FunctionCallParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    
    out << "PTN: function-call( ";
    mFunction->Print(out, 0);
    out << "(";
    
    bool first(true);
    std::for_each(
        mParameterList.begin(), mParameterList.end(),
        [&](const ParameterListT::value_type &param)
        {
            if(!first)
            {
                out << ", ";
            }
            else
            {
                first = false;
            }
            
            param->Print(out, 0);
        }
    );
    
    out << ") )";
}

/******************************************************************************

    dish::ReturnParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::ReturnParseTreeNode::Count(0);
dish::IntegerT dish::ReturnParseTreeNode::Instances(0);

bool dish::ReturnParseTreeNode::isEqual(const dish::ReturnParseTreeNode &ptn) const
{
    return mReturn->IsEqual(*(ptn.mReturn));
}
 
std::shared_ptr< dish::iAtomic > dish::ReturnParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    throw mReturn->Execute(symtab);
}

void dish::ReturnParseTreeNode::Validate(LanguageSymbolTable &symtab) const
{
    mReturn->Validate(symtab);
}

bool dish::ReturnParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::ReturnParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    
    out << "PTN: return ";
    mReturn->Print(out, 0);
}

/******************************************************************************

    dish::OneOprParseTreeNode class definitions

 ******************************************************************************/
 
bool dish::OneOprParseTreeNode::IsLiteral() const
{
    return mOpr->IsLiteral();
}

void dish::OneOprParseTreeNode::Validate(LanguageSymbolTable &symtab) const
{
    mOpr->Validate(symtab);
}

/******************************************************************************

    dish::TwoOprParseTreeNode class definitions

 ******************************************************************************/
 
bool dish::TwoOprParseTreeNode::IsLiteral() const
{
    return (mOpr1->IsLiteral() && mOpr2->IsLiteral());
}

void dish::TwoOprParseTreeNode::Validate(LanguageSymbolTable &symtab) const
{
    mOpr1->Validate(symtab);
    mOpr2->Validate(symtab);
}

/******************************************************************************

    dish::ChainedOprParseTreeNode class definitions

 ******************************************************************************/
 
bool dish::ChainedOprParseTreeNode::equal(const dish::ChainedOprParseTreeNode &ptn) const
{
    if(mOprList.size() == ptn.mOprList.size())
    {
        ChainedOprListT::const_iterator i(mOprList.begin());
        const ChainedOprListT::const_iterator last_i(mOprList.end());
        
        ChainedOprListT::const_iterator ptn_i(ptn.mOprList.begin());
        const ChainedOprListT::const_iterator ptn_last_i(ptn.mOprList.end());
        
        while((i != last_i) && (ptn_i != ptn_last_i))
        {
            if((*i)->IsEqual(**ptn_i))
            {
                ++i;
                ++ptn_i;
            }
            else
            {
                return false;
            }
        }
        
        assert(i == last_i);
        assert(ptn_i == ptn_last_i);

        return true;
    }
    
    return false;
}
 
void dish::ChainedOprParseTreeNode::AddOperand(std::shared_ptr< dish::iParseTreeNode > opr)
{
    assert(0 != opr.get());
    
    if((!mOprList.empty()) && opr->IsLiteral())
    {
        std::shared_ptr< iAtomic > opratomic(opr->Execute());
        const iAtomic::TypeT oprtype(opratomic->Type());
        
        if((iAtomic::typeBoolean == oprtype) || (iAtomic::typeInteger == oprtype) || (iAtomic::typeReal == oprtype))
        {
            std::shared_ptr< dish::iParseTreeNode > tmp(mOprList.front());
        
            if(tmp->IsLiteral())
            {
                mOprList.pop_front();
                
                std::shared_ptr< iAtomic > tmpatomic(tmp->Execute());
                tmpatomic = execute(opratomic, tmpatomic);
                opr = LiteralParseTreeNode::MakeValue(tmpatomic);
            }
            
            mOprList.push_front(opr);
        }
        else
        {
            mOprList.push_back(opr);
        }
    }
    else
    {
        mOprList.push_back(opr);
    }
}

bool dish::ChainedOprParseTreeNode::IsLiteral() const
{
    for(ChainedOprListT::const_iterator i(mOprList.begin()), last_i(mOprList.end()); i != last_i; ++i)
    {
        if(!(*i)->IsLiteral())
        {
            return false;
        }
    }
    
    return true;
}

/******************************************************************************

    dish::NegateOpParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::NegateOpParseTreeNode::Count(0);
dish::IntegerT dish::NegateOpParseTreeNode::Instances(0);

bool dish::NegateOpParseTreeNode::isEqual(const dish::NegateOpParseTreeNode &ptn) const
{
    return equal(ptn);
}

std::shared_ptr< dish::iAtomic > dish::NegateOpParseTreeNode::Execute()
{
    return -(mOpr->Execute());
}

std::shared_ptr< dish::iAtomic > dish::NegateOpParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    return -(mOpr->Execute(symtab));
}

bool dish::NegateOpParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::NegateOpParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    
    out << "PTN: -(";
    mOpr->Print(out, 0);
    out << ")";
}

/******************************************************************************

    dish::AddOpChainParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::AddOpChainParseTreeNode::Count(0);
dish::IntegerT dish::AddOpChainParseTreeNode::Instances(0);

bool dish::AddOpChainParseTreeNode::isEqual(const dish::AddOpChainParseTreeNode &ptn) const
{
    return equal(ptn);
}

std::shared_ptr< dish::iAtomic > dish::AddOpChainParseTreeNode::execute(std::shared_ptr< dish::iAtomic > opr1, std::shared_ptr< dish::iAtomic > opr2)
{
    return OpAdd(opr1, opr2);
}

std::string dish::AddOpChainParseTreeNode::oprString() const
{
    return " + ";
}

std::shared_ptr< dish::iAtomic > dish::AddOpChainParseTreeNode::Execute()
{
    assert(!mOprList.empty());

    ChainedOprListT::const_iterator i(mOprList.begin());
    const ChainedOprListT::const_iterator last_i(mOprList.end());
    
    std::shared_ptr< iAtomic > result((*i++)->Execute());
    
    while(i != last_i)
    {
        result = OpAdd(result, (*i++)->Execute());
    }
    
    return result;
}

std::shared_ptr< dish::iAtomic > dish::AddOpChainParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    assert(!mOprList.empty());

    ChainedOprListT::const_iterator i(mOprList.begin());
    const ChainedOprListT::const_iterator last_i(mOprList.end());
    
    std::shared_ptr< iAtomic > result((*i++)->Execute(symtab));
    
    while(i != last_i)
    {
        result = OpAdd(result, (*i++)->Execute(symtab));
    }
    
    return result;
}

bool dish::AddOpChainParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::AddOpChainParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);

    ChainedOprListT::const_iterator i(mOprList.begin());
    const ChainedOprListT::const_iterator last_i(mOprList.end());
    
    out << "PTN: AddChain(";
    
    for((*i++)->Print(out); i != last_i; ++i)
    {
        out << ", ";
        (*i)->Print(out);
    }
    
    out << ")";
}

/******************************************************************************

    dish::SubOpParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::SubOpParseTreeNode::Count(0);
dish::IntegerT dish::SubOpParseTreeNode::Instances(0);

bool dish::SubOpParseTreeNode::isEqual(const dish::SubOpParseTreeNode &ptn) const
{
    return equal(ptn);
}

std::shared_ptr< dish::iAtomic > dish::SubOpParseTreeNode::Execute()
{
    try
    {
        return OpSub(mOpr1->Execute(), mOpr2->Execute());
    }
    
    catch(DishException &e)
    {
        if(!e.IsLocationSupplied())
        {
            e.AddLocation(LocationString());
        }
        
        throw;
    }
}

std::shared_ptr< dish::iAtomic > dish::SubOpParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    try
    {
        return OpSub(mOpr1->Execute(symtab), mOpr2->Execute(symtab));
    }
    
    catch(DishException &e)
    {
        if(!e.IsLocationSupplied())
        {
            e.AddLocation(LocationString());
        }
        
        throw;
    }
}

bool dish::SubOpParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::SubOpParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    
    out << "PTN: Sub(";
    mOpr1->Print(out, 0);
    out << ", ";
    mOpr2->Print(out, 0);
    out << ")";
}

/******************************************************************************

    dish::MulOpChainParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::MulOpChainParseTreeNode::Count(0);
dish::IntegerT dish::MulOpChainParseTreeNode::Instances(0);

bool dish::MulOpChainParseTreeNode::isEqual(const dish::MulOpChainParseTreeNode &ptn) const
{
    return equal(ptn);
}

std::shared_ptr< dish::iAtomic > dish::MulOpChainParseTreeNode::execute(std::shared_ptr< dish::iAtomic > opr1, std::shared_ptr< dish::iAtomic > opr2)
{
    return OpMul(opr1, opr2);
}

std::string dish::MulOpChainParseTreeNode::oprString() const
{
    return " * ";
}

std::shared_ptr< dish::iAtomic > dish::MulOpChainParseTreeNode::Execute()
{
    assert(!mOprList.empty());

    ChainedOprListT::const_iterator i(mOprList.begin());
    const ChainedOprListT::const_iterator last_i(mOprList.end());
    
    std::shared_ptr< iAtomic > result((*i++)->Execute());
    
    while(i != last_i)
    {
        result = OpMul(result, (*i++)->Execute());
    }
    
    return result;
}

std::shared_ptr< dish::iAtomic > dish::MulOpChainParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    assert(!mOprList.empty());

    ChainedOprListT::const_iterator i(mOprList.begin());
    const ChainedOprListT::const_iterator last_i(mOprList.end());
    
    std::shared_ptr< iAtomic > result((*i++)->Execute(symtab));
    
    while(i != last_i)
    {
        result = OpMul(result, (*i++)->Execute(symtab));
    }
    
    return result;
}

bool dish::MulOpChainParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::MulOpChainParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);

    ChainedOprListT::const_iterator i(mOprList.begin());
    const ChainedOprListT::const_iterator last_i(mOprList.end());
    
    out << "PTN: MulChain(";
    
    for((*i++)->Print(out); i != last_i; ++i)
    {
        out << ", ";
        (*i)->Print(out);
    }
    
    out << ")";
}

/******************************************************************************

    dish::DivOpParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::DivOpParseTreeNode::Count(0);
dish::IntegerT dish::DivOpParseTreeNode::Instances(0);

bool dish::DivOpParseTreeNode::isEqual(const dish::DivOpParseTreeNode &ptn) const
{
    return equal(ptn);
}

std::shared_ptr< dish::iAtomic > dish::DivOpParseTreeNode::Execute()
{
    try
    {
        return OpDiv(mOpr1->Execute(), mOpr2->Execute());
    }
    
    catch(DishException &e)
    {
        if(!e.IsLocationSupplied())
        {
            e.AddLocation(LocationString());
        }
        
        throw;
    }
}

std::shared_ptr< dish::iAtomic > dish::DivOpParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    try
    {
        return OpDiv(mOpr1->Execute(symtab), mOpr2->Execute(symtab));
    }
    
    catch(DishException &e)
    {
        if(!e.IsLocationSupplied())
        {
            e.AddLocation(LocationString());
        }
        
        throw;
    }
}

bool dish::DivOpParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::DivOpParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    
    out << "PTN: Div(";
    mOpr1->Print(out, 0);
    out << ", ";
    mOpr2->Print(out, 0);
    out << ")";
}

/******************************************************************************

    dish::ModOpParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::ModOpParseTreeNode::Count(0);
dish::IntegerT dish::ModOpParseTreeNode::Instances(0);

bool dish::ModOpParseTreeNode::isEqual(const dish::ModOpParseTreeNode &ptn) const
{
    return equal(ptn);
}

std::shared_ptr< dish::iAtomic > dish::ModOpParseTreeNode::Execute()
{
    try
    {
        return OpMod(mOpr1->Execute(), mOpr2->Execute());
    }
    
    catch(DishException &e)
    {
        if(!e.IsLocationSupplied())
        {
            e.AddLocation(LocationString());
        }
        
        throw;
    }
}

std::shared_ptr< dish::iAtomic > dish::ModOpParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    try
    {
        return OpMod(mOpr1->Execute(symtab), mOpr2->Execute(symtab));
    }
    
    catch(DishException &e)
    {
        if(!e.IsLocationSupplied())
        {
            e.AddLocation(LocationString());
        }
        
        throw;
    }
}

bool dish::ModOpParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::ModOpParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    
    out << "PTN: Mod(";
    mOpr1->Print(out, 0);
    out << ", ";
    mOpr2->Print(out, 0);
    out << ")";
}

/******************************************************************************

    dish::PowOpParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::PowOpParseTreeNode::Count(0);
dish::IntegerT dish::PowOpParseTreeNode::Instances(0);

bool dish::PowOpParseTreeNode::isEqual(const dish::PowOpParseTreeNode &ptn) const
{
    return equal(ptn);
}

std::shared_ptr< dish::iAtomic > dish::PowOpParseTreeNode::Execute()
{
    try
    {
        return OpPow(mOpr1->Execute(), mOpr2->Execute());
    }
    
    catch(DishException &e)
    {
        if(!e.IsLocationSupplied())
        {
            e.AddLocation(LocationString());
        }
        
        throw;
    }
}

std::shared_ptr< dish::iAtomic > dish::PowOpParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    try
    {
        return OpPow(mOpr1->Execute(symtab), mOpr2->Execute(symtab));
    }
    
    catch(DishException &e)
    {
        if(!e.IsLocationSupplied())
        {
            e.AddLocation(LocationString());
        }
        
        throw;
    }
}

bool dish::PowOpParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::PowOpParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    
    out << "PTN: Pow(";
    mOpr1->Print(out, 0);
    out << ", ";
    mOpr2->Print(out, 0);
    out << ")";
}

/******************************************************************************

    dish::NotOpParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::NotOpParseTreeNode::Count(0);
dish::IntegerT dish::NotOpParseTreeNode::Instances(0);

bool dish::NotOpParseTreeNode::isEqual(const dish::NotOpParseTreeNode &ptn) const
{
    return equal(ptn);
}

std::shared_ptr< dish::iAtomic > dish::NotOpParseTreeNode::Execute()
{
    try
    {
        return !(mOpr->Execute());
    }
    
    catch(DishException &e)
    {
        if(!e.IsLocationSupplied())
        {
            e.AddLocation(LocationString());
        }
        
        throw;
    }
}

std::shared_ptr< dish::iAtomic > dish::NotOpParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    try
    {
        return !(mOpr->Execute(symtab));
    }
    
    catch(DishException &e)
    {
        if(!e.IsLocationSupplied())
        {
            e.AddLocation(LocationString());
        }
        
        throw;
    }
}

bool dish::NotOpParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::NotOpParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    
    out << "PTN: Not(";
    mOpr->Print(out, 0);
    out << ")";
}

/******************************************************************************

    dish::AndOpChainParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::AndOpChainParseTreeNode::Count(0);
dish::IntegerT dish::AndOpChainParseTreeNode::Instances(0);

bool dish::AndOpChainParseTreeNode::isEqual(const dish::AndOpChainParseTreeNode &ptn) const
{
    return equal(ptn);
}

std::shared_ptr< dish::iAtomic > dish::AndOpChainParseTreeNode::execute(std::shared_ptr< dish::iAtomic > opr1, std::shared_ptr< dish::iAtomic > opr2)
{
    return OpAnd(opr1, opr2);
}

std::string dish::AndOpChainParseTreeNode::oprString() const
{
    return " and ";
}

std::shared_ptr< dish::iAtomic > dish::AndOpChainParseTreeNode::Execute()
{
    assert(!mOprList.empty());

    ChainedOprListT::const_iterator i(mOprList.begin());
    const ChainedOprListT::const_iterator last_i(mOprList.end());
    
    std::shared_ptr< iAtomic > result((*i++)->Execute());
    
    while(i != last_i)
    {
        result = OpAnd(result, (*i++)->Execute());
    }
    
    return result;
}

std::shared_ptr< dish::iAtomic > dish::AndOpChainParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    assert(!mOprList.empty());

    ChainedOprListT::const_iterator i(mOprList.begin());
    const ChainedOprListT::const_iterator last_i(mOprList.end());
    
    std::shared_ptr< iAtomic > result((*i++)->Execute(symtab));
    
    while(i != last_i)
    {
        result = OpAnd(result, (*i++)->Execute(symtab));
    }
    
    return result;
}

bool dish::AndOpChainParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::AndOpChainParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);

    ChainedOprListT::const_iterator i(mOprList.begin());
    const ChainedOprListT::const_iterator last_i(mOprList.end());
    
    out << "PTN: AndChain(";
    
    for((*i++)->Print(out); i != last_i; ++i)
    {
        out << ", ";
        (*i)->Print(out);
    }
    
    out << ")";
}

/******************************************************************************

    dish::OrOpChainParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::OrOpChainParseTreeNode::Count(0);
dish::IntegerT dish::OrOpChainParseTreeNode::Instances(0);

bool dish::OrOpChainParseTreeNode::isEqual(const dish::OrOpChainParseTreeNode &ptn) const
{
    return equal(ptn);
}

std::shared_ptr< dish::iAtomic > dish::OrOpChainParseTreeNode::execute(std::shared_ptr< dish::iAtomic > opr1, std::shared_ptr< dish::iAtomic > opr2)
{
    return OpOr(opr1, opr2);
}

std::string dish::OrOpChainParseTreeNode::oprString() const
{
    return " or ";
}

std::shared_ptr< dish::iAtomic > dish::OrOpChainParseTreeNode::Execute()
{
    assert(!mOprList.empty());

    ChainedOprListT::const_iterator i(mOprList.begin());
    const ChainedOprListT::const_iterator last_i(mOprList.end());
    
    std::shared_ptr< iAtomic > result((*i++)->Execute());
    
    while(i != last_i)
    {
        result = OpOr(result, (*i++)->Execute());
    }
    
    return result;
}

std::shared_ptr< dish::iAtomic > dish::OrOpChainParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    assert(!mOprList.empty());

    ChainedOprListT::const_iterator i(mOprList.begin());
    const ChainedOprListT::const_iterator last_i(mOprList.end());
    
    std::shared_ptr< iAtomic > result((*i++)->Execute(symtab));
    
    while(i != last_i)
    {
        result = OpOr(result, (*i++)->Execute(symtab));
    }
    
    return result;
}

bool dish::OrOpChainParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::OrOpChainParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);

    ChainedOprListT::const_iterator i(mOprList.begin());
    const ChainedOprListT::const_iterator last_i(mOprList.end());
    
    out << "PTN: OrChain(";
    
    for((*i++)->Print(out); i != last_i; ++i)
    {
        out << ", ";
        (*i)->Print(out);
    }
    
    out << ")";
}

/******************************************************************************

    dish::XorOpChainParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::XorOpChainParseTreeNode::Count(0);
dish::IntegerT dish::XorOpChainParseTreeNode::Instances(0);

bool dish::XorOpChainParseTreeNode::isEqual(const dish::XorOpChainParseTreeNode &ptn) const
{
    return equal(ptn);
}

std::shared_ptr< dish::iAtomic > dish::XorOpChainParseTreeNode::execute(std::shared_ptr< dish::iAtomic > opr1, std::shared_ptr< dish::iAtomic > opr2)
{
    return OpXor(opr1, opr2);
}

std::string dish::XorOpChainParseTreeNode::oprString() const
{
    return " xor ";
}

std::shared_ptr< dish::iAtomic > dish::XorOpChainParseTreeNode::Execute()
{
    assert(!mOprList.empty());

    ChainedOprListT::const_iterator i(mOprList.begin());
    const ChainedOprListT::const_iterator last_i(mOprList.end());
    
    std::shared_ptr< iAtomic > result((*i++)->Execute());
    
    while(i != last_i)
    {
        result = OpXor(result, (*i++)->Execute());
    }
    
    return result;
}

std::shared_ptr< dish::iAtomic > dish::XorOpChainParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    assert(!mOprList.empty());

    ChainedOprListT::const_iterator i(mOprList.begin());
    const ChainedOprListT::const_iterator last_i(mOprList.end());
    
    std::shared_ptr< iAtomic > result((*i++)->Execute(symtab));
    
    while(i != last_i)
    {
        result = OpXor(result, (*i++)->Execute(symtab));
    }
    
    return result;
}

bool dish::XorOpChainParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::XorOpChainParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);

    ChainedOprListT::const_iterator i(mOprList.begin());
    const ChainedOprListT::const_iterator last_i(mOprList.end());
    
    out << "PTN: XorChain(";
    
    for((*i++)->Print(out); i != last_i; ++i)
    {
        out << ", ";
        (*i)->Print(out);
    }
    
    out << ")";
}

/******************************************************************************

    dish::LessThanOpParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::LessThanOpParseTreeNode::Count(0);
dish::IntegerT dish::LessThanOpParseTreeNode::Instances(0);

bool dish::LessThanOpParseTreeNode::isEqual(const dish::LessThanOpParseTreeNode &ptn) const
{
    return equal(ptn);
}

std::shared_ptr< dish::iAtomic > dish::LessThanOpParseTreeNode::Execute()
{
    try
    {
        return OpLessThan(mOpr1->Execute(), mOpr2->Execute());
    }
    
    catch(DishException &e)
    {
        if(!e.IsLocationSupplied())
        {
            e.AddLocation(LocationString());
        }
        
        throw;
    }
}

std::shared_ptr< dish::iAtomic > dish::LessThanOpParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    try
    {
        return OpLessThan(mOpr1->Execute(symtab), mOpr2->Execute(symtab));
    }
    
    catch(DishException &e)
    {
        if(!e.IsLocationSupplied())
        {
            e.AddLocation(LocationString());
        }
        
        throw;
    }
}

bool dish::LessThanOpParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::LessThanOpParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    
    out << "PTN: Less(";
    mOpr1->Print(out, 0);
    out << ", ";
    mOpr2->Print(out, 0);
    out << ")";
}

/******************************************************************************

    dish::LessThanEqualOpParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::LessThanEqualOpParseTreeNode::Count(0);
dish::IntegerT dish::LessThanEqualOpParseTreeNode::Instances(0);

bool dish::LessThanEqualOpParseTreeNode::isEqual(const dish::LessThanEqualOpParseTreeNode &ptn) const
{
    return equal(ptn);
}

std::shared_ptr< dish::iAtomic > dish::LessThanEqualOpParseTreeNode::Execute()
{
    try
    {
        return OpLessThanOrEqual(mOpr1->Execute(), mOpr2->Execute());
    }
    
    catch(DishException &e)
    {
        if(!e.IsLocationSupplied())
        {
            e.AddLocation(LocationString());
        }
        
        throw;
    }
}

std::shared_ptr< dish::iAtomic > dish::LessThanEqualOpParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    try
    {
        return OpLessThanOrEqual(mOpr1->Execute(symtab), mOpr2->Execute(symtab));
    }
    
    catch(DishException &e)
    {
        if(!e.IsLocationSupplied())
        {
            e.AddLocation(LocationString());
        }
        
        throw;
    }
}

bool dish::LessThanEqualOpParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::LessThanEqualOpParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    
    out << "PTN: LessEqual(";
    mOpr1->Print(out, 0);
    out << ", ";
    mOpr2->Print(out, 0);
    out << ")";
}

/******************************************************************************

    dish::EqualOpParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::EqualOpParseTreeNode::Count(0);
dish::IntegerT dish::EqualOpParseTreeNode::Instances(0);

bool dish::EqualOpParseTreeNode::isEqual(const dish::EqualOpParseTreeNode &ptn) const
{
    return equal(ptn);
}

std::shared_ptr< dish::iAtomic > dish::EqualOpParseTreeNode::Execute()
{
    try
    {
        return OpEqual(mOpr1->Execute(), mOpr2->Execute());
    }
    
    catch(DishException &e)
    {
        if(!e.IsLocationSupplied())
        {
            e.AddLocation(LocationString());
        }
        
        throw;
    }
}

std::shared_ptr< dish::iAtomic > dish::EqualOpParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    try
    {
        return OpEqual(mOpr1->Execute(symtab), mOpr2->Execute(symtab));
    }
    
    catch(DishException &e)
    {
        if(!e.IsLocationSupplied())
        {
            e.AddLocation(LocationString());
        }
        
        throw;
    }
}

bool dish::EqualOpParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::EqualOpParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    
    out << "PTN: Equal(";
    mOpr1->Print(out, 0);
    out << ", ";
    mOpr2->Print(out, 0);
    out << ")";
}

/******************************************************************************

    dish::NotEqualOpParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::NotEqualOpParseTreeNode::Count(0);
dish::IntegerT dish::NotEqualOpParseTreeNode::Instances(0);

bool dish::NotEqualOpParseTreeNode::isEqual(const dish::NotEqualOpParseTreeNode &ptn) const
{
    return equal(ptn);
}

std::shared_ptr< dish::iAtomic > dish::NotEqualOpParseTreeNode::Execute()
{
    try
    {
        return OpNotEqual(mOpr1->Execute(), mOpr2->Execute());
    }
    
    catch(DishException &e)
    {
        if(!e.IsLocationSupplied())
        {
            e.AddLocation(LocationString());
        }
        
        throw;
    }
}

std::shared_ptr< dish::iAtomic > dish::NotEqualOpParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    try
    {
        return OpNotEqual(mOpr1->Execute(symtab), mOpr2->Execute(symtab));
    }
    
    catch(DishException &e)
    {
        if(!e.IsLocationSupplied())
        {
            e.AddLocation(LocationString());
        }
        
        throw;
    }
}

bool dish::NotEqualOpParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::NotEqualOpParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    
    out << "PTN: NotEqual(";
    mOpr1->Print(out, 0);
    out << ", ";
    mOpr2->Print(out, 0);
    out << ")";
}

/******************************************************************************

    dish::GreaterThanEqualOpParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::GreaterThanEqualOpParseTreeNode::Count(0);
dish::IntegerT dish::GreaterThanEqualOpParseTreeNode::Instances(0);

bool dish::GreaterThanEqualOpParseTreeNode::isEqual(const dish::GreaterThanEqualOpParseTreeNode &ptn) const
{
    return equal(ptn);
}

std::shared_ptr< dish::iAtomic > dish::GreaterThanEqualOpParseTreeNode::Execute()
{
    try
    {
        return OpGreaterThanOrEqual(mOpr1->Execute(), mOpr2->Execute());
    }
    
    catch(DishException &e)
    {
        if(!e.IsLocationSupplied())
        {
            e.AddLocation(LocationString());
        }
        
        throw;
    }
}

std::shared_ptr< dish::iAtomic > dish::GreaterThanEqualOpParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    try
    {
        return OpGreaterThanOrEqual(mOpr1->Execute(symtab), mOpr2->Execute(symtab));
    }
    
    catch(DishException &e)
    {
        if(!e.IsLocationSupplied())
        {
            e.AddLocation(LocationString());
        }
        
        throw;
    }
}

bool dish::GreaterThanEqualOpParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::GreaterThanEqualOpParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    
    out << "PTN: GreaterEqual(";
    mOpr1->Print(out, 0);
    out << ", ";
    mOpr2->Print(out, 0);
    out << ")";
}

/******************************************************************************

    dish::GreaterThanOpParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::GreaterThanOpParseTreeNode::Count(0);
dish::IntegerT dish::GreaterThanOpParseTreeNode::Instances(0);

bool dish::GreaterThanOpParseTreeNode::isEqual(const dish::GreaterThanOpParseTreeNode &ptn) const
{
    return equal(ptn);
}

std::shared_ptr< dish::iAtomic > dish::GreaterThanOpParseTreeNode::Execute()
{
    try
    {
        return OpGreaterThan(mOpr1->Execute(), mOpr2->Execute());
    }
    
    catch(DishException &e)
    {
        if(!e.IsLocationSupplied())
        {
            e.AddLocation(LocationString());
        }
        
        throw;
    }
}

std::shared_ptr< dish::iAtomic > dish::GreaterThanOpParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    try
    {
        return OpGreaterThan(mOpr1->Execute(symtab), mOpr2->Execute(symtab));
    }
    
    catch(DishException &e)
    {
        if(!e.IsLocationSupplied())
        {
            e.AddLocation(LocationString());
        }
        
        throw;
    }
}

bool dish::GreaterThanOpParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::GreaterThanOpParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    
    out << "PTN: Greater(";
    mOpr1->Print(out, 0);
    out << ", ";
    mOpr2->Print(out, 0);
    out << ")";
}

/******************************************************************************

    dish::StatementBlockParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::StatementBlockParseTreeNode::Count(0);
dish::IntegerT dish::StatementBlockParseTreeNode::Instances(0);

bool dish::StatementBlockParseTreeNode::isEqual(const dish::StatementBlockParseTreeNode &ptn) const
{
    if(mBlock.size() == ptn.mBlock.size())
    {
        StatementBlockT::const_iterator i(mBlock.begin());
        const StatementBlockT::const_iterator last_i(mBlock.end());
    
        StatementBlockT::const_iterator ptn_i(ptn.mBlock.begin());
        const StatementBlockT::const_iterator ptn_last_i(ptn.mBlock.end());
        
        while((i != last_i) && (ptn_i != ptn_last_i))
        {
            if((*i)->IsEqual(**ptn_i))
            {
                ++i;
                ++ptn_i;
            }
            else
            {
                return false;
            }
        }
        
        assert(i == last_i);
        assert(ptn_i == ptn_last_i);
        
        return true;
    }
    
    return false;
}

std::shared_ptr< dish::iAtomic > dish::StatementBlockParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    ScopedScope scope(symtab);

    std::for_each(
        mBlock.begin(), mBlock.end(),
        [&](const StatementBlockT::value_type &statement)
        {
            statement->Execute(symtab);
        }
    );
    
    return NullValue::MakeValue();
}

void dish::StatementBlockParseTreeNode::Validate(LanguageSymbolTable &symtab) const
{
    ScopedScope scope(symtab);

    std::for_each(
        mBlock.begin(), mBlock.end(),
        [&](const StatementBlockT::value_type &statement)
        {
            statement->Validate(symtab);
        }
    );
}

bool dish::StatementBlockParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::StatementBlockParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << "PTN: block" << std::endl;
    
    std::for_each(
        mBlock.begin(), mBlock.end(),
        [&](const StatementBlockT::value_type &statement)
        {
            statement->Print(out, indent + 4);
            out << std::endl;
        }
    );
    
    printIndent(out, indent);
    out << "end";
}

/******************************************************************************

    dish::IfStatementParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::IfStatementParseTreeNode::Count(0);
dish::IntegerT dish::IfStatementParseTreeNode::Instances(0);

bool dish::IfStatementParseTreeNode::isEqual(const dish::IfStatementParseTreeNode &ptn) const
{
    if(mCondition->IsEqual(*(ptn.mCondition)) && mIfBlock->IsEqual(*(ptn.mIfBlock)))
    {
        const bool else_exists(0 != mElseBlock.get());
        const bool ptn_else_exists(0 != ptn.mElseBlock.get());
    
        if(else_exists == ptn_else_exists)
        {
            if(else_exists)
            {
                return mElseBlock->IsEqual(*(ptn.mElseBlock));
            }
        }
    }
    
    return false;
}

std::shared_ptr< dish::iAtomic > dish::IfStatementParseTreeNode::Execute(LanguageSymbolTable &symtab)
{
    if(mCondition->Execute(symtab)->AsBoolean())
    {
        return mIfBlock->Execute(symtab);
    }
    
    else if(0 != mElseBlock.get())
    {
        return mElseBlock->Execute(symtab);
    }
    
    return NullValue::MakeValue(); 
}

void dish::IfStatementParseTreeNode::Validate(LanguageSymbolTable &symtab) const
{
    mCondition->Validate(symtab);
    mIfBlock->Validate(symtab);
    
    if(mElseBlock)
    {
        mElseBlock->Validate(symtab);
    }
}

bool dish::IfStatementParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::IfStatementParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << "PTN: if (";
    mCondition->Print(out, 0);
    out << ") then";
    out << std::endl;
    
    mIfBlock->Print(out, indent + 8);
    out << std::endl;
    
    if(mElseBlock)
    {
        printIndent(out, indent + 4);
        out << "else";
        out << std::endl;
        
        mIfBlock->Print(out, indent + 8);
        out << std::endl;
    }
}

/******************************************************************************

    dish::SwitchStatementParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::SwitchStatementParseTreeNode::Count(0);
dish::IntegerT dish::SwitchStatementParseTreeNode::Instances(0);

bool dish::SwitchStatementParseTreeNode::isEqual(const dish::SwitchStatementParseTreeNode &ptn) const
{
    if(mSwitch.size() == ptn.mSwitch.size())
    {
        if(mExpression->IsEqual(*(ptn.mExpression)))
        {
            {
                SwitchStatementT::const_iterator i(mSwitch.begin());
                const SwitchStatementT::const_iterator last_i(mSwitch.end());
                
                SwitchStatementT::const_iterator ptn_i(ptn.mSwitch.begin());
                const SwitchStatementT::const_iterator ptn_last_i(ptn.mSwitch.end());
            
                while((i != last_i) && (ptn_i != ptn_last_i))
                {
                    if(i->first->IsEqual(*(ptn_i->first)) && i->second->IsEqual(*(ptn_i->second)))
                    {
                        ++i;
                        ++ptn_i;
                    }
                    else
                    {
                        return false;
                    }
                }
                
                assert(i == last_i);
                assert(ptn_i == ptn_last_i);
            }
            
            {
                const bool otherwise_exists(0 != mOtherwise.get());
                const bool ptn_otherwise_exists(0 != ptn.mOtherwise.get());
            
                if(otherwise_exists == ptn_otherwise_exists)
                {
                    if(otherwise_exists)
                    {
                        return mOtherwise->IsEqual(*(ptn.mOtherwise));
                    }
                }
            }
            
            return true;
        }
    }
    
    return false;
}

std::shared_ptr< dish::iAtomic > dish::SwitchStatementParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    std::shared_ptr< dish::iAtomic > value(mExpression->Execute(symtab));
    
    for(SwitchStatementT::const_iterator i(mSwitch.begin()), last_i(mSwitch.end()); i != last_i; ++i)
    {
        if((i->first->Execute(symtab) == value)->AsBoolean())
        {
            i->second->Execute(symtab);
            
            return NullValue::MakeValue();
        }
    }
    
    if(mOtherwise)
    {
        mOtherwise->Execute(symtab);
    }
    else
    {
        throw CaseNotHandledException(LocationString(), "Case not handled in switch-statement.");
    }
    
    return NullValue::MakeValue(); 
}

void dish::SwitchStatementParseTreeNode::Validate(LanguageSymbolTable &symtab) const
{
    mExpression->Validate(symtab);
    
    std::for_each(
        mSwitch.begin(), mSwitch.end(),
        [&](const SwitchStatementT::value_type &elem)
        {
            elem.first->Validate(symtab);
            elem.second->Validate(symtab);
        }
    );
    
    if(mOtherwise)
    {
        mOtherwise->Validate(symtab);
    }
}

bool dish::SwitchStatementParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::SwitchStatementParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << "PTN: switch(";
    mExpression->Print(out, 0);
    out << ")";
    out << std::endl;
    
    std::for_each(
        mSwitch.begin(), mSwitch.end(),
        [&](const SwitchStatementT::value_type &value)
        {
            value.first->Print(out, indent + 4);
            out << " :";
            out << std::endl;
            value.second->Print(out, indent + 8);
            out << std::endl;
            
            out << std::endl;
        }
    );
    
    if(mOtherwise)
    {
        printIndent(out, indent);
        out << "otherwise:";
        out << std::endl;
        mOtherwise->Print(out, indent + 4);
        out << std::endl;
    }
    
    printIndent(out, indent);
    out << "end";
}

/******************************************************************************

    dish::ForLoopParseTreeNode::StepF class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::ForLoopParseTreeNode::StepF::Execute(dish::LanguageSymbolTable &symtab)
{
    std::shared_ptr< iAtomic > lhs(mLeftHandSide->Execute(symtab));
    lhs->Assign(OpAdd(lhs, mStep->Execute(symtab)));
    
    return NullValue::MakeValue();
}

void dish::ForLoopParseTreeNode::StepF::Print(std::ostream &out, const int &indent) const
{
    printIndent(out, indent);
    out << "PTN: ForLoopParseTreeNode::StepF(";
    mLeftHandSide->Print(out, 0);
    out << ", ";
    mStep->Print(out, 0);
    out << ")";
}

/******************************************************************************

    dish::ForLoopParseTreeNode class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iParseTreeNode > dish::ForLoopParseTreeNode::OneLit(LiteralParseTreeNode::MakeValue(static_cast< IntegerT >(1)));
 
dish::IntegerT dish::ForLoopParseTreeNode::Count(0);
dish::IntegerT dish::ForLoopParseTreeNode::Instances(0);

bool dish::ForLoopParseTreeNode::isEqual(const dish::ForLoopParseTreeNode &ptn) const
{
    return (
        mAssign->IsEqual(*(ptn.mAssign)) &&
        mCondition->IsEqual(*(ptn.mCondition)) &&
        
        mIncrement->mLeftHandSide->IsEqual(*(ptn.mIncrement->mLeftHandSide)) &&
        mIncrement->mStep->IsEqual(*(ptn.mIncrement->mStep)) &&
        
        mBody->IsEqual(*(ptn.mBody))
    );
}

std::shared_ptr< dish::iAtomic > dish::ForLoopParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    for(mAssign->Execute(symtab); mCondition->Execute(symtab)->AsBoolean(); mIncrement->Execute(symtab))
    {
        mBody->Execute(symtab);
    }
    
    mBody->Execute(symtab);
    
    return NullValue::MakeValue(); 
}

void dish::ForLoopParseTreeNode::Validate(LanguageSymbolTable &symtab) const
{
    mAssign->Validate(symtab);
    mCondition->Validate(symtab);
    mIncrement->Validate(symtab);
    
    mBody->Validate(symtab);
}

bool dish::ForLoopParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::ForLoopParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << "PTN: for ";
    mAssign->Print(out, 0);
    out << ", while ";
    mCondition->Print(out, 0);
    out << ", ";
    mIncrement->Print(out, 0);
    out << std::endl;
    
    mBody->Print(out, indent + 4);
}

/******************************************************************************

    dish::ForEachLoopParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::ForEachLoopParseTreeNode::Count(0);
dish::IntegerT dish::ForEachLoopParseTreeNode::Instances(0);

bool dish::ForEachLoopParseTreeNode::isEqual(const dish::ForEachLoopParseTreeNode &ptn) const
{
    return (
        (mReference == ptn.mReference) &&
        (mId == ptn.mId) &&
        mCollection->IsEqual(*(ptn.mCollection)) &&
        mBody->IsEqual(*(ptn.mBody))
    );
}

std::shared_ptr< dish::iAtomic > dish::ForEachLoopParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    std::shared_ptr< iAtomic > collection(mCollection->Execute(symtab));

    switch(collection->Type())
    {
        case iAtomic::typeArray:
        {
            const IntegerT last_i(collection->Member("finish")->AsInteger());
            for(IntegerT i(collection->Member("start")->AsInteger()); i <= last_i; ++i)
            {
                std::shared_ptr< iAtomic > element(collection->Element(i));
                ScopedScope scope(symtab, SingleSymbolTable::MakeValue(mId, mReference ? element : element->Clone()));
                
                mBody->Execute(symtab);
            }
        } break;
        
        case iAtomic::typeDictionary:
        {
            std::shared_ptr< iAtomic > keys(collection->Keys());
            
            const IntegerT last_i(keys->Member("finish")->AsInteger());
            for(IntegerT i(keys->Member("start")->AsInteger()); i <= last_i; ++i)
            {
                std::shared_ptr< iAtomic > key(ReferenceValue::MakeValue(keys->Element(i)));
                std::shared_ptr< iAtomic > value(ReferenceValue::MakeValue(collection->Lookup(key->AsString())));
                
                std::shared_ptr< StructureValue > element(StructureValue::MakeValue());
                if(mReference)
                {
                    element->Add("key", key);
                    element->Add("value", value);
                }
                else
                {
                    element->Add("key", key->Clone());
                    element->Add("value", value->Clone());
                }
                
                ScopedScope scope(symtab, SingleSymbolTable::MakeValue(mId, element));
                
                mBody->Execute(symtab);
            }
        } break;
        
        default:
        {
            std::stringstream message;
            message << "Cannot iterate over values of type '";
            message << TypeToString(collection->Type());
            message << "'.";
            
            throw IllegalOperationException(message.str());
        }
        
    }
    
    return NullValue::MakeValue();
}

void dish::ForEachLoopParseTreeNode::Validate(dish::LanguageSymbolTable &symtab) const
{
    mCollection->Validate(symtab);
    mBody->Validate(symtab);
}

bool dish::ForEachLoopParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::ForEachLoopParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << "PTN: foreach ";
    if(mReference)
    {
        out << "&";
    }
    out << mId;
    out << " in ";
    mCollection->Print(out, 0);
    out << std::endl;
    mBody->Print(out, indent + 4);
}

/******************************************************************************

    dish::WhileLoopParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::WhileLoopParseTreeNode::Count(0);
dish::IntegerT dish::WhileLoopParseTreeNode::Instances(0);

bool dish::WhileLoopParseTreeNode::isEqual(const dish::WhileLoopParseTreeNode &ptn) const
{
    return (
        mCondition->IsEqual(*(ptn.mCondition)) &&
        mBody->IsEqual(*(ptn.mBody))
    );
}

std::shared_ptr< dish::iAtomic > dish::WhileLoopParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    while(mCondition->Execute(symtab)->AsBoolean())
    {
        mBody->Execute(symtab);
    }
    
    return NullValue::MakeValue(); 
}

void dish::WhileLoopParseTreeNode::Validate(LanguageSymbolTable &symtab) const
{
    mCondition->Validate(symtab);
    mBody->Validate(symtab);
}

bool dish::WhileLoopParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::WhileLoopParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << "PTN: while ";
    mCondition->Print(out, 0);
    out << " do";
    out << std::endl;
    
    mBody->Print(out, 4);
}

/******************************************************************************

    dish::RepeatUntilLoopParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::RepeatUntilLoopParseTreeNode::Count(0);
dish::IntegerT dish::RepeatUntilLoopParseTreeNode::Instances(0);

bool dish::RepeatUntilLoopParseTreeNode::isEqual(const dish::RepeatUntilLoopParseTreeNode &ptn) const
{
    if(mBody.size() == ptn.mBody.size())
    {
        if(mCondition->IsEqual(*(ptn.mCondition)))
        {
            BodyT::const_iterator i(mBody.begin());
            const BodyT::const_iterator last_i(mBody.end());
            
            BodyT::const_iterator ptn_i(ptn.mBody.begin());
            const BodyT::const_iterator ptn_last_i(ptn.mBody.end());
        
            while((i != last_i) && (ptn_i != ptn_last_i))
            {
                if((*i)->IsEqual(**ptn_i))
                {
                    ++i;
                    ++ptn_i;
                }
                else
                {
                    return false;
                }
            }
            
            assert(i == last_i);
            assert(ptn_i == ptn_last_i);
            
            return true;
        }
    }
    
    return false;
}

std::shared_ptr< dish::iAtomic > dish::RepeatUntilLoopParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    do
    {
        std::for_each(
            mBody.begin(), mBody.end(),
            [&](BodyT::value_type &line)
            {
                line->Execute(symtab);
            }
        );
    } while(!mCondition->Execute(symtab)->AsBoolean());
    
    return NullValue::MakeValue(); 
}

void dish::RepeatUntilLoopParseTreeNode::Validate(LanguageSymbolTable &symtab) const
{
    std::for_each(
        mBody.begin(), mBody.end(),
        [&](const BodyT::value_type &line)
        {
            line->Validate(symtab);
        }
    );

    mCondition->Validate(symtab);
}

bool dish::RepeatUntilLoopParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::RepeatUntilLoopParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << "PTN: repeat";
    out << std::endl;
    
    std::for_each(
        mBody.begin(), mBody.end(),
        [&](const BodyT::value_type &line)
        {
            line->Print(out, indent + 4);
            out << std::endl;
        }
    );
    
    printIndent(out, indent);
    out << "until ";
    mCondition->Print(out, 0);
}

/******************************************************************************

    dish::AssertParseTreeNode class definitions

 ******************************************************************************/
 
dish::IntegerT dish::AssertParseTreeNode::Count(0);
dish::IntegerT dish::AssertParseTreeNode::Instances(0);

bool dish::AssertParseTreeNode::isEqual(const dish::AssertParseTreeNode &ptn) const
{
    return mCondition->IsEqual(*(ptn.mCondition));
}

std::shared_ptr< dish::iAtomic > dish::AssertParseTreeNode::Execute(dish::LanguageSymbolTable &symtab)
{
    if(!mCondition->Execute(symtab)->AsBoolean())
    {
        std::stringstream message;
        message << "Assert failed: ";
        mCondition->Print(message, 0);
        message << ".";
    
        throw FailedAssertionException(LocationString(), message.str());
    }

    return NullValue::MakeValue(); 
}

void dish::AssertParseTreeNode::Validate(LanguageSymbolTable &symtab) const
{
    mCondition->Validate(symtab);
}

bool dish::AssertParseTreeNode::IsEqual(const dish::iParseTreeNode &ptn) const
{
    return ptn.isEqual(*this);
}

void dish::AssertParseTreeNode::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << "PTN: assert(";
    mCondition->Print(out, 0);
    out << ");";
}

/******************************************************************************

    Global function definitions

 ******************************************************************************/

void dish::PrintParseTreeStatistics(std::ostream &out)
{
    dish::IntegerT live_nodes(0);
    dish::IntegerT total_nodes(0);
    
    out << "               Null PTN: " << dish::NullParseTreeNode::NumLiveInstances() << " / " << dish::NullParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::NullParseTreeNode::NumLiveInstances();
    total_nodes += dish::NullParseTreeNode::NumInstances();
    
    out << "          Reference PTN: " << dish::ReferenceParseTreeNode::NumLiveInstances() << " / " << dish::ReferenceParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::ReferenceParseTreeNode::NumLiveInstances();
    total_nodes += dish::ReferenceParseTreeNode::NumInstances();
    
    out << std::endl;
    
    out << "            Literal PTN: " << dish::LiteralParseTreeNode::NumLiveInstances() << " / " << dish::LiteralParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::LiteralParseTreeNode::NumLiveInstances();
    total_nodes += dish::LiteralParseTreeNode::NumInstances();
    
    out << "      Literal Array PTN: " << dish::LiteralArrayParseTreeNode::NumLiveInstances() << " / " << dish::LiteralArrayParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::LiteralArrayParseTreeNode::NumLiveInstances();
    total_nodes += dish::LiteralArrayParseTreeNode::NumInstances();
    
    out << std::endl;
    
    out << "         Identifier PTN: " << dish::IdentifierParseTreeNode::NumLiveInstances() << " / " << dish::IdentifierParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::IdentifierParseTreeNode::NumLiveInstances();
    total_nodes += dish::IdentifierParseTreeNode::NumInstances();
    
    out << std::endl;
    
    out << "      Boolean Type PTN: " << dish::BooleanTypeParseTreeNode::NumLiveInstances() << " / " << dish::BooleanTypeParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::BooleanTypeParseTreeNode::NumLiveInstances();
    total_nodes += dish::BooleanTypeParseTreeNode::NumInstances();
    
    std::cout << "      Integer Type PTN: " << dish::IntegerTypeParseTreeNode::NumLiveInstances() << " / " << dish::IntegerTypeParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::IntegerTypeParseTreeNode::NumLiveInstances();
    total_nodes += dish::IntegerTypeParseTreeNode::NumInstances();
    
    out << "         Real Type PTN: " << dish::RealTypeParseTreeNode::NumLiveInstances() << " / " << dish::RealTypeParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::RealTypeParseTreeNode::NumLiveInstances();
    total_nodes += dish::RealTypeParseTreeNode::NumInstances();
    
    out << "       String Type PTN: " << dish::StringTypeParseTreeNode::NumLiveInstances() << " / " << dish::StringTypeParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::StringTypeParseTreeNode::NumLiveInstances();
    total_nodes += dish::StringTypeParseTreeNode::NumInstances();
    
    out << "        Array Type PTN: " << dish::ArrayTypeParseTreeNode::NumLiveInstances() << " / " << dish::ArrayTypeParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::ArrayTypeParseTreeNode::NumLiveInstances();
    total_nodes += dish::ArrayTypeParseTreeNode::NumInstances();
    
    out << "    Structure Type PTN: " << dish::StructureTypeParseTreeNode::NumLiveInstances() << " / " << dish::StructureTypeParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::StructureTypeParseTreeNode::NumLiveInstances();
    total_nodes += dish::StructureTypeParseTreeNode::NumInstances();
    
    out << "   Dictionary Type PTN: " << dish::DictionaryTypeParseTreeNode::NumLiveInstances() << " / " << dish::DictionaryTypeParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::DictionaryTypeParseTreeNode::NumLiveInstances();
    total_nodes += dish::DictionaryTypeParseTreeNode::NumInstances();
    
    out << std::endl;
    
    out << "           Declare PTN: " << dish::DeclareParseTreeNode::NumLiveInstances() << " / " << dish::DeclareParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::DeclareParseTreeNode::NumLiveInstances();
    total_nodes += dish::DeclareParseTreeNode::NumInstances();
    
    out << "      Declare Type PTN: " << dish::DeclareTypeParseTreeNode::NumLiveInstances() << " / " << dish::DeclareTypeParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::DeclareTypeParseTreeNode::NumLiveInstances();
    total_nodes += dish::DeclareTypeParseTreeNode::NumInstances();
    
    out << "  Declare Function PTN: " << dish::DeclareTypeParseTreeNode::NumLiveInstances() << " / " << dish::DeclareTypeParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::DeclareTypeParseTreeNode::NumLiveInstances();
    total_nodes += dish::DeclareTypeParseTreeNode::NumInstances();
    
    out << " Declare Reference PTN: " << dish::DeclareReferenceParseTreeNode::NumLiveInstances() << " / " << dish::DeclareReferenceParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::DeclareReferenceParseTreeNode::NumLiveInstances();
    total_nodes += dish::DeclareReferenceParseTreeNode::NumInstances();
    
    out << std::endl;
    
    out << "             Index PTN: " << dish::IndexParseTreeNode::NumLiveInstances() << " / " << dish::IndexParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::IndexParseTreeNode::NumLiveInstances();
    total_nodes += dish::IndexParseTreeNode::NumInstances();
    
    out << "            Member PTN: " << dish::MemberParseTreeNode::NumLiveInstances() << " / " << dish::MemberParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::MemberParseTreeNode::NumLiveInstances();
    total_nodes += dish::MemberParseTreeNode::NumInstances();
    
    out << std::endl;
    
    out << "     Function Call PTN: " << dish::FunctionCallParseTreeNode::NumLiveInstances() << " / " << dish::FunctionCallParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::FunctionCallParseTreeNode::NumLiveInstances();
    total_nodes += dish::FunctionCallParseTreeNode::NumInstances();
    
    out << "            Return PTN: " << dish::ReturnParseTreeNode::NumLiveInstances() << " / " << dish::ReturnParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::ReturnParseTreeNode::NumLiveInstances();
    total_nodes += dish::ReturnParseTreeNode::NumInstances();
    
    out << std::endl;
    
    out << "         Op Assign PTN: " << dish::AssignmentParseTreeNode::NumLiveInstances() << " / " << dish::AssignmentParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::AssignmentParseTreeNode::NumLiveInstances();
    total_nodes += dish::AssignmentParseTreeNode::NumInstances();
    
    out << "            Op Neg PTN: " << dish::NegateOpParseTreeNode::NumLiveInstances() << " / " << dish::NegateOpParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::NegateOpParseTreeNode::NumLiveInstances();
    total_nodes += dish::NegateOpParseTreeNode::NumInstances();
    
    out << "  Op Add (chained) PTN: " << dish::AddOpChainParseTreeNode::NumLiveInstances() << " / " << dish::AddOpChainParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::AddOpChainParseTreeNode::NumLiveInstances();
    total_nodes += dish::AddOpChainParseTreeNode::NumInstances();
    
    out << "            Op Sub PTN: " << dish::SubOpParseTreeNode::NumLiveInstances() << " / " << dish::SubOpParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::SubOpParseTreeNode::NumLiveInstances();
    total_nodes += dish::SubOpParseTreeNode::NumInstances();
    
    out << "  Op Mul (chained) PTN: " << dish::MulOpChainParseTreeNode::NumLiveInstances() << " / " << dish::MulOpChainParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::MulOpChainParseTreeNode::NumLiveInstances();
    total_nodes += dish::MulOpChainParseTreeNode::NumInstances();
    
    out << "            Op Div PTN: " << dish::DivOpParseTreeNode::NumLiveInstances() << " / " << dish::DivOpParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::DivOpParseTreeNode::NumLiveInstances();
    total_nodes += dish::DivOpParseTreeNode::NumInstances();
    
    out << "            Op Mod PTN: " << dish::ModOpParseTreeNode::NumLiveInstances() << " / " << dish::ModOpParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::ModOpParseTreeNode::NumLiveInstances();
    total_nodes += dish::ModOpParseTreeNode::NumInstances();
    
    out << "            Op Pow PTN: " << dish::PowOpParseTreeNode::NumLiveInstances() << " / " << dish::PowOpParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::PowOpParseTreeNode::NumLiveInstances();
    total_nodes += dish::PowOpParseTreeNode::NumInstances();
    
    out << std::endl;
    
    out << "            Op Not PTN: " << dish::NotOpParseTreeNode::NumLiveInstances() << " / " << dish::NotOpParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::NotOpParseTreeNode::NumLiveInstances();
    total_nodes += dish::NotOpParseTreeNode::NumInstances();
    
    out << "  Op And (chained) PTN: " << dish::AndOpChainParseTreeNode::NumLiveInstances() << " / " << dish::AndOpChainParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::AndOpChainParseTreeNode::NumLiveInstances();
    total_nodes += dish::AndOpChainParseTreeNode::NumInstances();
    
    out << "   Op Or (chained) PTN: " << dish::OrOpChainParseTreeNode::NumLiveInstances() << " / " << dish::OrOpChainParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::OrOpChainParseTreeNode::NumLiveInstances();
    total_nodes += dish::OrOpChainParseTreeNode::NumInstances();
    
    out << "  Op Xor (chained) PTN: " << dish::XorOpChainParseTreeNode::NumLiveInstances() << " / " << dish::XorOpChainParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::XorOpChainParseTreeNode::NumLiveInstances();
    total_nodes += dish::XorOpChainParseTreeNode::NumInstances();
    
    out << std::endl;
    
    out << "             Op <= PTN: " << dish::LessThanEqualOpParseTreeNode::NumLiveInstances() << " / " << dish::LessThanEqualOpParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::LessThanEqualOpParseTreeNode::NumLiveInstances();
    total_nodes += dish::LessThanEqualOpParseTreeNode::NumInstances();
    
    out << "              Op < PTN: " << dish::LessThanOpParseTreeNode::NumLiveInstances() << " / " << dish::LessThanOpParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::LessThanOpParseTreeNode::NumLiveInstances();
    total_nodes += dish::LessThanOpParseTreeNode::NumInstances();
    
    out << "             Op == PTN: " << dish::EqualOpParseTreeNode::NumLiveInstances() << " / " << dish::EqualOpParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::EqualOpParseTreeNode::NumLiveInstances();
    total_nodes += dish::EqualOpParseTreeNode::NumInstances();
    
    out << "             Op != PTN: " << dish::NotEqualOpParseTreeNode::NumLiveInstances() << " / " << dish::NotEqualOpParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::NotEqualOpParseTreeNode::NumLiveInstances();
    total_nodes += dish::NotEqualOpParseTreeNode::NumInstances();
    
    out << "             Op >= PTN: " << dish::GreaterThanEqualOpParseTreeNode::NumLiveInstances() << " / " << dish::GreaterThanEqualOpParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::GreaterThanEqualOpParseTreeNode::NumLiveInstances();
    total_nodes += dish::GreaterThanEqualOpParseTreeNode::NumInstances();
    
    out << "              Op > PTN: " << dish::GreaterThanOpParseTreeNode::NumLiveInstances() << " / " << dish::GreaterThanOpParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::GreaterThanOpParseTreeNode::NumLiveInstances();
    total_nodes += dish::GreaterThanOpParseTreeNode::NumInstances();
    
    std::cout << std::endl;
    
    out << "   Statement Block PTN: " << dish::StatementBlockParseTreeNode::NumLiveInstances() << " / " << dish::StatementBlockParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::StatementBlockParseTreeNode::NumLiveInstances();
    total_nodes += dish::StatementBlockParseTreeNode::NumInstances();
    
    out << std::endl;
    
    std::cout << "      If-Then-Else PTN: " << dish::IfStatementParseTreeNode::NumLiveInstances() << " / " << dish::IfStatementParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::IfStatementParseTreeNode::NumLiveInstances();
    total_nodes += dish::IfStatementParseTreeNode::NumInstances();
    
    out << "            Switch PTN: " << dish::SwitchStatementParseTreeNode::NumLiveInstances() << " / " << dish::SwitchStatementParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::SwitchStatementParseTreeNode::NumLiveInstances();
    total_nodes += dish::SwitchStatementParseTreeNode::NumInstances();
    
    out << std::endl;
    
    out << "          For-Loop PTN: " << dish::ForLoopParseTreeNode::NumLiveInstances() << " / " << dish::ForLoopParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::ForLoopParseTreeNode::NumLiveInstances();
    total_nodes += dish::ForLoopParseTreeNode::NumInstances();
    
    out << "      ForEach-Loop PTN: " << dish::ForEachLoopParseTreeNode::NumLiveInstances() << " / " << dish::ForEachLoopParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::ForEachLoopParseTreeNode::NumLiveInstances();
    total_nodes += dish::ForEachLoopParseTreeNode::NumInstances();
    
    out << "        While-Loop PTN: " << dish::WhileLoopParseTreeNode::NumLiveInstances() << " / " << dish::WhileLoopParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::WhileLoopParseTreeNode::NumLiveInstances();
    total_nodes += dish::WhileLoopParseTreeNode::NumInstances();
    
    out << " Repeat-Until-Loop PTN: " << dish::RepeatUntilLoopParseTreeNode::NumLiveInstances() << " / " << dish::RepeatUntilLoopParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::RepeatUntilLoopParseTreeNode::NumLiveInstances();
    total_nodes += dish::RepeatUntilLoopParseTreeNode::NumInstances();
    
    out << std::endl;
    
    out << "            Assert PTN: " << dish::AssertParseTreeNode::NumLiveInstances() << " / " << dish::AssertParseTreeNode::NumInstances() << std::endl;
    live_nodes += dish::AssertParseTreeNode::NumLiveInstances();
    total_nodes += dish::AssertParseTreeNode::NumInstances();
    
    out << std::endl;
    
    out << "                       ----------" << std::endl;
    out << "                  Live: " << live_nodes << std::endl;
    out << "                 Total: " << total_nodes << std::endl;
}

