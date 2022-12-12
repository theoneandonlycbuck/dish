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
#include <cassert>
#include <cstdio>

#include "atomics.h"
#include "exception.h"
#include "langerr.h"

/******************************************************************************

    dish global variable definitions

 ******************************************************************************/
 
const bool dish::UNLOCKED(false);
const bool dish::LOCKED(true);

const bool dish::REFERENCE_PARAMETER(true);
const bool dish::VALUE_PARAMETER(false);

/******************************************************************************

    dish::iAtomic class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::iAtomic::memberBytes() const
{
    std::stringstream message;
    message << "The member 'bytes' is not valid for values of this type: ";
    message << TypeToString(Type());
    message << ".";

    throw NoSuchMemberException(message.str());
}

std::shared_ptr< dish::iAtomic > dish::iAtomic::memberMinimum() const
{
    std::stringstream message;
    message << "The member 'minimum' is not valid for values of this type: ";
    message << TypeToString(Type());
    message << ".";

    throw NoSuchMemberException(message.str());
}

std::shared_ptr< dish::iAtomic > dish::iAtomic::memberMaximum() const
{
    std::stringstream message;
    message << "The member 'maximum' is not valid for values of this type: ";
    message << TypeToString(Type());
    message << ".";

    throw NoSuchMemberException(message.str());
}

std::shared_ptr< dish::iAtomic > dish::iAtomic::memberEps() const
{
    std::stringstream message;
    message << "The member 'eps' is not valid for values of this type: ";
    message << TypeToString(Type());
    message << ".";

    throw NoSuchMemberException(message.str());
}

std::shared_ptr< dish::iAtomic > dish::iAtomic::Clone() const
{
    std::shared_ptr< iAtomic > clone(Copy());
    
    if(IsLocked())
    {
        clone->Lock();
    }
    
    return clone;
}

const bool &dish::iAtomic::IsLocked() const throw()
{
    return mLocked;
}

void dish::iAtomic::Lock() throw()
{
    mLocked = true;
}
 
dish::BooleanT dish::iAtomic::AsBoolean() const
{
    std::stringstream message;
    message << "Cannot cast right-hand value to 'boolean' (";
    message << TypeToString(Type());
    message << ").";

    throw IllegalCastException(message.str());
}

dish::IntegerT dish::iAtomic::AsInteger() const
{
    std::stringstream message;
    message << "Cannot cast right-hand value to 'integer' (";
    message << TypeToString(Type());
    message << ").";

    throw IllegalCastException(message.str());
}

dish::RealT dish::iAtomic::AsReal() const
{
    std::stringstream message;
    message << "Cannot cast right-hand value to 'real' (";
    message << TypeToString(Type());
    message << ").";

    throw IllegalCastException(message.str());
}

dish::StringT dish::iAtomic::AsString() const
{
    std::stringstream message;
    message << "Cannot cast right-hand value to 'string' (";
    message << TypeToString(Type());
    message << ").";

    throw IllegalCastException(message.str());
}

void dish::iAtomic::Assign(std::shared_ptr< iAtomic > rhs)
{
    Assign(*rhs);
}

void dish::iAtomic::Assign(const iValueAtomic &rhs)
{
    std::stringstream message;
    message << "Value cannot be assigned to ";
    message << TypeToString(Type());
    message << ".";

    throw ValueNotLeftHandSideException(message.str());
}

void dish::iAtomic::Assign(const dish::BooleanT &rhs)
{
    Assign(*BooleanValue::MakeLockedValue(rhs));
}

void dish::iAtomic::Assign(const dish::IntegerT &rhs)
{
    Assign(*IntegerValue::MakeValue(rhs));
}

void dish::iAtomic::Assign(const dish::RealT &rhs)
{
    Assign(*RealValue::MakeValue(rhs));
}

void dish::iAtomic::Assign(const dish::StringT &rhs)
{
    Assign(*StringValue::MakeValue(rhs));
}

dish::IntegerT dish::iAtomic::Members(dish::iStructureAtomic::MemberNameSetT &members) const
{
    return 0;
}

std::shared_ptr< dish::iAtomic > dish::iAtomic::Member(const std::string &member) const
{
    if(IsEqual(member, "bytes", CASE_INSENSITIVE))
    {
        return memberBytes();
    }
    
    else if(IsEqual(member, "eps", CASE_INSENSITIVE))
    {
        return memberEps();
    }
    
    else if(IsEqual(member, "maximum", CASE_INSENSITIVE))
    {
        return memberMaximum();
    }
    
    else if(IsEqual(member, "minimum", CASE_INSENSITIVE))
    {
        return memberMinimum();
    }

    std::stringstream message;
    message << "The member '";
    message << member;
    message << "' is not valid for values of this type: ";
    message << TypeToString(Type());
    message << ".";

    throw NoSuchMemberException(message.str());
}

dish::IntegerT dish::iAtomic::Add(std::shared_ptr< dish::iAtomic > element)
{
    std::stringstream message;
    message << "Cannot add elements to values of this type: ";
    message << TypeToString(Type());
    message << ".";

    throw IllegalTypeException(message.str());
}

dish::IntegerT dish::iAtomic::Add(std::shared_ptr< dish::iAtomic > element, const IntegerT &index)
{
    std::stringstream message;
    message << "Cannot add elements to values of this type: ";
    message << TypeToString(Type());
    message << ".";

    throw IllegalTypeException(message.str());
}

std::shared_ptr< dish::iAtomic > dish::iAtomic::Element(const dish::IntegerT &index) const
{
    std::stringstream message;
    message << "The index ";
    message << index;
    message << " is not valid for this value: ";
    message << TypeToString(Type());
    message << ".";

    throw IllegalIndexException(message.str());
}

void dish::iAtomic::Swap(const dish::IntegerT &a, const dish::IntegerT &b)
{
    std::stringstream message;
    message << "Cannot swap elements of this type: ";
    message << TypeToString(Type());
    message << ".";

    throw IllegalTypeException(message.str());
}

dish::IntegerT dish::iAtomic::Add(std::shared_ptr< dish::iAtomic > key, std::shared_ptr< dish::iAtomic > value)
{
    std::stringstream message;
    message << "Cannot add <key, value>-pairs to values of this type: ";
    message << TypeToString(Type());
    message << ".";

    throw IllegalTypeException(message.str());
}

std::shared_ptr< dish::iAtomic > dish::iAtomic::Keys() const
{
    std::stringstream message;
    message << "Cannot retrieve keys from type: ";
    message << TypeToString(Type());
    message << ".";

    throw IllegalTypeException(message.str());
}

std::shared_ptr< dish::iAtomic > dish::iAtomic::Lookup(const dish::StringT &key) const
{
    std::stringstream message;
    message << "Cannot lookup '";
    message << key;
    message << "' in this type: ";
    message << TypeToString(Type());
    message << ".";

    throw IllegalTypeException(message.str());
}

std::shared_ptr< dish::iAtomic > dish::iAtomic::Declare() const
{
    std::stringstream message;
    message << "Cannot declare values of this type: ";
    message << TypeToString(Type());
    message << ".";

    throw IllegalTypeException(message.str());
}

std::shared_ptr< dish::iAtomic > dish::iAtomic::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::stringstream message;
    message << "Values of this type are not executable: ";
    message << TypeToString(Type());
    message << ".";

    throw NotExecutableException(message.str());
}

const dish::iAtomic::ParamListT &dish::iAtomic::ParameterList() const
{
    std::stringstream message;
    message << "This value is not executable; there is no parameter list: ";
    message << TypeToString(Type());
    message << ".";

    throw NotExecutableException(message.str());
}

dish::IntegerT dish::iAtomic::NumParameters() const
{
    std::stringstream message;
    message << "This value is not executable; there is no parameter list: ";
    message << TypeToString(Type());
    message << ".";

    throw NotExecutableException(message.str());
}
 
void dish::iAtomic::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << AsString();
}

/******************************************************************************

    dish::iAtomic-function definitions

 ******************************************************************************/

void dish::AssertIs(std::shared_ptr< dish::iAtomic > atomic, const dish::iAtomic::TypeT &type)
{
    if(type != atomic->Type())
    {
        std::stringstream message;
        message << "Expecting a ";
        message << type;
        message << " but found a ";
        message << atomic->Type();
        message << ".";
    
        throw IllegalTypeException(message.str());
    }
}

std::ostream &dish::operator<<(std::ostream &out, const dish::iAtomic::TypeT &type)
{
    switch(type)
    {
        case iAtomic::typeNull:
        {
            out << "NullT";
        } break;
            
        case iAtomic::typeType:
        {
            out << "TypeT";
        } break;
            
        case iAtomic::typeBoolean:
        {
            out << "BooleanT";
        } break;
            
        case iAtomic::typeInteger:
        {
            out << "IntegerT";
        } break;
            
        case iAtomic::typeReal:
        {
            out << "RealT";
        } break;
            
        case iAtomic::typeString:
        {
            out << "StringT";
        } break;
            
        case iAtomic::typeArray:
        {
            out << "ArrayT";
        } break;
            
        case iAtomic::typeDictionary:
        {
            out << "DictionaryT";
        } break;
            
        case iAtomic::typeStructure:
        {
            out << "StructureT";
        } break;
            
        case iAtomic::typeExecutable:
        {
            out << "FunctionT";
        } break;
            
        default:
        {
            out << "<unknonwn>T";
        }
         
    }
    
    return out;
}
 
/******************************************************************************

    dish::TypeAtomic class definitions

 ******************************************************************************/
 
dish::TypeAtomic::TypeT dish::TypeAtomic::Type() const throw()
{
    return typeType;
}
 
std::shared_ptr< dish::iAtomic > dish::TypeAtomic::Member(const std::string &member) const
{
    if(IsEqual(member, "instances", CASE_INSENSITIVE))
    {
        return IntegerValue::MakeValue(mNumInstances);
    }
    
    return iAtomic::Member(member);
}

/******************************************************************************

    dish::BooleanTypeAtomic class definitions

 ******************************************************************************/

dish::IntegerT dish::BooleanTypeAtomic::Count(0);
 
std::shared_ptr< dish::iAtomic > dish::BooleanTypeAtomic::Copy() const
{
    return BooleanTypeAtomic::MakeValue(mInitialValue);
}
 
std::shared_ptr< dish::iAtomic > dish::BooleanTypeAtomic::Declare() const
{
    declare();
    
    return BooleanValue::MakeUnlockedValue(mInitialValue);
}

void dish::BooleanTypeAtomic::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << "boolean";
}

/******************************************************************************

    dish::IntegerTypeAtomic class definitions

 ******************************************************************************/

dish::IntegerT dish::IntegerTypeAtomic::Count(0);
 
std::shared_ptr< dish::iAtomic > dish::IntegerTypeAtomic::Copy() const
{
    return std::shared_ptr< iAtomic >(new IntegerTypeAtomic(mInitialValue));
}
 
std::shared_ptr< dish::iAtomic > dish::IntegerTypeAtomic::Declare() const
{
    declare();
    
    return IntegerValue::MakeValue(mInitialValue);
}

void dish::IntegerTypeAtomic::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << "integer";
}

/******************************************************************************

    dish::RangedIntegerTypeAtomic class definitions

 ******************************************************************************/

dish::IntegerT dish::RangedIntegerTypeAtomic::Count(0);
 
std::shared_ptr< dish::iAtomic > dish::RangedIntegerTypeAtomic::Copy() const
{
    return std::shared_ptr< iAtomic >(new RangedIntegerTypeAtomic(mMinimumRange, mMaximumRange, mRangeBoundary, mInitialValue));
}
 
std::shared_ptr< dish::iAtomic > dish::RangedIntegerTypeAtomic::Declare() const
{
    declare();
    
    return RangedIntegerValue::MakeValue(mMinimumRange, mMaximumRange, mRangeBoundary, mInitialValue);
}

void dish::RangedIntegerTypeAtomic::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << "integer(";
    out << mMinimumRange;
    out << ", ";
    out << mMaximumRange;
    out << ", ";
    switch(mRangeBoundary)
    {
        case rngbndCap:
        {
            out << "CAP";
        } break;
        
        case rngbndRollover:
        {
            out << "ROLLOVER";
        } break;
        
        case rngbndError:
        default:
        {
            out << "ERROR";
        } break;
        
    }
    out << ")";
}

/******************************************************************************

    dish::RealTypeAtomic class definitions

 ******************************************************************************/

dish::IntegerT dish::RealTypeAtomic::Count(0);
 
std::shared_ptr< dish::iAtomic > dish::RealTypeAtomic::Copy() const
{
    return std::shared_ptr< iAtomic >(new RealTypeAtomic());
}
 
std::shared_ptr< dish::iAtomic > dish::RealTypeAtomic::Declare() const
{
    declare();
    
    return RealValue::MakeValue(mInitialValue);
}

void dish::RealTypeAtomic::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << "real";
}

/******************************************************************************

    dish::RangedRealTypeAtomic class definitions

 ******************************************************************************/

dish::IntegerT dish::RangedRealTypeAtomic::Count(0);
 
std::shared_ptr< dish::iAtomic > dish::RangedRealTypeAtomic::Copy() const
{
    return std::shared_ptr< iAtomic >(new RangedRealTypeAtomic(mMinimumRange, mMaximumRange, mRangeBoundary, mInitialValue));
}
 
std::shared_ptr< dish::iAtomic > dish::RangedRealTypeAtomic::Declare() const
{
    declare();
    
    return RangedRealValue::MakeValue(mMinimumRange, mMaximumRange, mRangeBoundary, mInitialValue);
}

void dish::RangedRealTypeAtomic::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << "real(";
    out << mMinimumRange;
    out << ", ";
    out << mMaximumRange;
    out << ", ";
    switch(mRangeBoundary)
    {
        case rngbndCap:
        {
            out << "CAP";
        } break;
        
        case rngbndRollover:
        {
            out << "ROLLOVER";
        } break;
        
        case rngbndError:
        default:
        {
            out << "ERROR";
        } break;
        
    }
    out << ")";
}

/******************************************************************************

    dish::StringTypeAtomic class definitions

 ******************************************************************************/

dish::IntegerT dish::StringTypeAtomic::Count(0);
 
std::shared_ptr< dish::iAtomic > dish::StringTypeAtomic::Copy() const
{
    return std::shared_ptr< iAtomic >(new StringTypeAtomic());
}
 
std::shared_ptr< dish::iAtomic > dish::StringTypeAtomic::Declare() const
{
    declare();
    
    return StringValue::MakeValue(mInitialValue);
}

void dish::StringTypeAtomic::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << "string";
}

/******************************************************************************

    dish::ArrayTypeAtomic class definitions

 ******************************************************************************/

dish::IntegerT dish::ArrayTypeAtomic::Count(0);
 
dish::ArrayTypeAtomic::ArrayTypeAtomic(const dish::IntegerT &min, const dish::IntegerT &max, std::shared_ptr< dish::iAtomic > type) : dish::TypeAtomic(),
    mMinimumIndex(min),
    mMaximumIndex(max),
    
    mType(type)
{
    assert(mMinimumIndex <= mMaximumIndex);
    assert(mType);
    
    ++Count; 
}
 
std::shared_ptr< dish::iAtomic > dish::ArrayTypeAtomic::Copy() const
{
    return std::shared_ptr< iAtomic >(new ArrayTypeAtomic(mMinimumIndex, mMaximumIndex, mType->Copy()));
}

std::shared_ptr< dish::iAtomic > dish::ArrayTypeAtomic::Declare() const
{
    declare();
    
    return (0 != mType.get()) ? ArrayValue::MakeValue(mMinimumIndex, mMaximumIndex - mMinimumIndex + 1, mType) : ArrayValue::MakeValue(mMinimumIndex);
}

void dish::ArrayTypeAtomic::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    
    out << "array[";
    out << mMinimumIndex;
    out << " to ";
    out << mMaximumIndex;
    out << "] of ";
    mType->Print(out, 0);
}

/******************************************************************************

    dish::DictionaryTypeAtomic class definitions

 ******************************************************************************/

dish::IntegerT dish::DictionaryTypeAtomic::Count(0);
 
std::shared_ptr< dish::iAtomic > dish::DictionaryTypeAtomic::Copy() const
{
    return DictionaryTypeAtomic::MakeValue();
}

std::shared_ptr< dish::iAtomic > dish::DictionaryTypeAtomic::Declare() const
{
    declare();
    
    return DictionaryValue::MakeValue();
}

void dish::DictionaryTypeAtomic::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    
    out << "dictionary";
}

/******************************************************************************

    dish::StructureTypeAtomic class definitions

 ******************************************************************************/

dish::IntegerT dish::StructureTypeAtomic::Count(0);
 
void dish::StructureTypeAtomic::Add(const std::string &id, std::shared_ptr< dish::iAtomic > type)
{
    assert(0 != type.get());

    switch(mMemberList.size())
    {
        case 0:
        {
            //  Empty.
        } break;
        
        case 1:
        {
            if(id == mMemberList.front().first)
            {
                std::stringstream message;
                message << "Duplicate structure member id: '";
                message << id;
                message << "'.";
                
                throw DuplicateSymbolException(message.str());
            }
        } break;
        
        case 2:
        {
            if((id == mMemberList.front().first) || (id == mMemberList.back().first))
            {
                std::stringstream message;
                message << "Duplicate structure member id: '";
                message << id;
                message << "'.";
                
                throw DuplicateSymbolException(message.str());
            }
        } break;
        
        default:
        {
            std::for_each(
                mMemberList.begin(), mMemberList.end(),
                [&](const MemberListT::value_type &elem)
                {
                    if(id == elem.first)
                    {
                        std::stringstream message;
                        message << "Duplicate structure member id: '";
                        message << id;
                        message << "'.";
                        
                        throw DuplicateSymbolException(message.str());
                    }
                }
            );
        }
        
    }

    mMemberList.push_back(std::make_pair(id, type));
}
 
std::shared_ptr< dish::iAtomic > dish::StructureTypeAtomic::Copy() const
{
    std::shared_ptr< StructureTypeAtomic > value(StructureTypeAtomic::MakeValue());
    
    std::for_each(
        mMemberList.begin(), mMemberList.end(),
        [&](const MemberListT::value_type &elem)
        {
            value->Add(elem.first, elem.second->Copy());
        }
    );
    
    return value;
}

std::shared_ptr< dish::iAtomic > dish::StructureTypeAtomic::Declare() const
{
    std::shared_ptr< StructureValue > structure(StructureValue::MakeValue());
    
    std::for_each(
        mMemberList.begin(), mMemberList.end(),
        [&](const MemberListT::value_type &elem)
        {
            structure->Add(elem.first, elem.second->Declare());
        }
    );
    
    return structure;
}

void dish::StructureTypeAtomic::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << "structure" << std::endl;
    
    std::for_each(
        mMemberList.begin(), mMemberList.end(),
        [&](const MemberListT::value_type &value)
        {
            printIndent(out, indent + INDENT);
            out << "declare ";
            value.second->Print(out, 0);
            out << value.first;
            out << std::endl;
        }
    );
    
    printIndent(out, indent);
    out << "end" << std::endl;
}

/******************************************************************************

    dish::NullValue class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::NullValue > dish::NullValue::Value(new NullValue());
 
dish::IntegerT dish::NullValue::Count(0);
 
dish::TypeAtomic::TypeT dish::NullValue::Type() const throw()
{
    return typeNull;
}
 
std::shared_ptr< dish::iAtomic > dish::NullValue::Copy() const
{
    return MakeValue();
}
 
dish::StringT dish::NullValue::AsString() const
{
    return "<null>";
}

/******************************************************************************

    dish::ExecutableAtomic class definitions

 ******************************************************************************/

dish::IntegerT dish::ExecutableAtomic::Count(0);

void dish::ExecutableAtomic::AddParam(const std::string &param, const bool &ref)
{
    switch(mParamList.size())
    {
        case 0:
        {
            //  Empty.
        } break;
        
        case 1:
        {
            //  Make sure the param-name is not already in the list...
            if(param == mParamList.front().first)
            {
                std::stringstream message;
                message << "Duplicate function parameter id: '";
                message << param;
                message << "'.";
                
                throw DuplicateSymbolException(message.str());
            }
        } break;
        
        case 2:
        {
            //  Make sure the param-name is not already in the list...
            if((param == mParamList.front().first) || (param == mParamList.back().first))
            {
                std::stringstream message;
                message << "Duplicate function parameter id: '";
                message << param;
                message << "'.";
                
                throw DuplicateSymbolException(message.str());
            }
        } break;
        
        default:
        {
            //  Ensure the parameter is unique in the list.
            std::for_each(
                mParamList.begin(), mParamList.end(),
                [&](const ParamListT::value_type &elem)
                {
                    if(param == elem.first)
                    {
                        std::stringstream message;
                        message << "Duplicate function parameter id: '";
                        message << param;
                        message << "'.";
                        
                        throw DuplicateSymbolException(message.str());
                    }
                }
            );
        }
        
    }

    //  Add the parameter to the function's parameter list.
    addParam(param, ref);
}

void dish::ExecutableAtomic::AddParam(const iExecutableAtomic::ParamListT &params)
{
#ifdef LANG_FORMAL_PARAM_LIST_TYPE_VECTOR
    mParamList.reserve(mParamList.size() + params.size());
#endif

    std::for_each(
        params.begin(), params.end(),
        [&](const ParamListT::value_type &elem)
        {
            AddParam(elem.first, elem.second);
        }
    );
}
 
dish::TypeAtomic::TypeT dish::ExecutableAtomic::Type() const throw()
{
    return typeExecutable;
}

std::shared_ptr< dish::iAtomic > dish::ExecutableAtomic::Copy() const
{
    throw IllegalCastException("Cannot copy an ExecutableAtomic.");
}

std::shared_ptr< dish::iAtomic > dish::ExecutableAtomic::Clone() const
{
    throw IllegalCastException("Cannot clone an ExecutableAtomic.");
}

dish::StringT dish::ExecutableAtomic::AsString() const
{
    std::stringstream str;
    
    Print(str);
    
    return str.str();
}

const dish::iAtomic::iExecutableAtomic::ParamListT &dish::ExecutableAtomic::ParameterList() const
{
    return mParamList;
}

dish::IntegerT dish::ExecutableAtomic::NumParameters() const
{
    return static_cast< IntegerT >(mParamList.size());
}

void dish::ExecutableAtomic::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << "<native function>";
}

/******************************************************************************

    dish::ReferenceValue class definitions

 ******************************************************************************/

dish::IntegerT dish::ReferenceValue::Count(0);
 
void dish::ReferenceValue::Lock() throw()
{
    mValue->Lock();
    iAtomic::Lock();
}
 
dish::TypeAtomic::TypeT dish::ReferenceValue::Type() const throw()
{
    return mValue->Type();
}
 
std::shared_ptr< dish::iAtomic > dish::ReferenceValue::Copy() const
{
    return mValue->Copy();
}
 
std::shared_ptr< dish::iAtomic > dish::ReferenceValue::Clone() const
{
    return mValue->Clone();
}

dish::BooleanT dish::ReferenceValue::AsBoolean() const
{
    return mValue->AsBoolean();
}

dish::IntegerT dish::ReferenceValue::AsInteger() const
{
    return mValue->AsInteger();
}

dish::RealT dish::ReferenceValue::AsReal() const
{
    return mValue->AsReal();
}

dish::StringT dish::ReferenceValue::AsString() const
{
    return mValue->AsString();
}

void dish::ReferenceValue::Assign(std::shared_ptr< dish::iAtomic > rhs)
{
    mValue->Assign(rhs);
}

void dish::ReferenceValue::Assign(const dish::iValueAtomic &rhs)
{
    mValue->Assign(rhs);
}

void dish::ReferenceValue::Assign(const dish::BooleanT &rhs)
{
    mValue->Assign(rhs);
}

void dish::ReferenceValue::Assign(const dish::IntegerT &rhs)
{
    mValue->Assign(rhs);
}

void dish::ReferenceValue::Assign(const dish::RealT &rhs)
{
    mValue->Assign(rhs);
}

void dish::ReferenceValue::Assign(const dish::StringT &rhs)
{
    mValue->Assign(rhs);
}

std::shared_ptr< dish::iAtomic > dish::ReferenceValue::Member(const std::string &member) const
{
    return mValue->Member(member);
}

dish::IntegerT dish::ReferenceValue::Add(std::shared_ptr< dish::iAtomic > element)
{
    return mValue->Add(element);
}

dish::IntegerT dish::ReferenceValue::Add(std::shared_ptr< dish::iAtomic > element, const IntegerT &index)
{
    return mValue->Add(element, index);
}

std::shared_ptr< dish::iAtomic > dish::ReferenceValue::Element(const dish::IntegerT &index) const
{
    return mValue->Element(index);
}

dish::IntegerT dish::ReferenceValue::Add(std::shared_ptr< dish::iAtomic > key, std::shared_ptr< dish::iAtomic > value)
{
    return mValue->Add(key, value);
}

std::shared_ptr< dish::iAtomic > dish::ReferenceValue::Keys() const
{
    return mValue->Keys();
}

std::shared_ptr< dish::iAtomic > dish::ReferenceValue::Lookup(const dish::StringT &key) const
{
    return mValue->Lookup(key);
}

std::shared_ptr< dish::iAtomic > dish::ReferenceValue::Declare() const
{
    return mValue->Declare();
}

std::shared_ptr< dish::iAtomic > dish::ReferenceValue::Execute(dish::LanguageSymbolTable &symtab) const
{
    return mValue->Execute(symtab);
}

const dish::iExecutableAtomic::ParamListT &dish::ReferenceValue::ParameterList() const
{
    return mValue->ParameterList();
}

dish::IntegerT dish::ReferenceValue::NumParameters() const
{
    return mValue->NumParameters();
}

void dish::ReferenceValue::Print(std::ostream &out, const std::string::size_type &indent) const
{
    mValue->Print(out, indent);
}

/******************************************************************************

    dish::BooleanValueBase class definitions

 ******************************************************************************/
 
dish::IntegerT dish::BooleanValueBase::Count(0);
 
std::shared_ptr< dish::iAtomic > dish::BooleanValueBase::memberBytes() const
{
    static std::shared_ptr< dish::iAtomic > BooleanBytes(dish::IntegerValue::MakeValue(BOOLEAN_NBYTES, dish::LOCKED));
    
    return BooleanBytes;
}

std::shared_ptr< dish::iAtomic > dish::BooleanValueBase::memberMinimum() const
{
    return BooleanValue::MakeValue(BOOLEAN_MIN, LOCKED);
}

std::shared_ptr< dish::iAtomic > dish::BooleanValueBase::memberMaximum() const
{
    return BooleanValue::MakeValue(BOOLEAN_MAX, LOCKED);
}
 
dish::TypeAtomic::TypeT dish::BooleanValueBase::Type() const throw()
{
    return typeBoolean;
}
 
dish::BooleanT dish::BooleanValueBase::AsBoolean() const
{
    return value();
}

dish::IntegerT dish::BooleanValueBase::AsInteger() const
{
    static const IntegerT Values[2] = { 0, 1 };

    return Values[static_cast< int >(value())];
}

dish::StringT dish::BooleanValueBase::AsString() const
{
    static const StringT Values[2] = { "False", "True" };

    return Values[static_cast< int >(value())];
}

void dish::BooleanValueBase::Assign(std::shared_ptr< dish::iAtomic > rhs)
{
    if(!IsLocked())
    {
        value() = rhs->AsBoolean();
    }
    else
    {
        throw ValueLockedException("Cannot modify a locked value.");
    }
}

void dish::BooleanValueBase::Assign(const dish::iValueAtomic &rhs)
{
    if(!IsLocked())
    {
        value() = rhs.AsBoolean();
    }
    else
    {
        throw ValueLockedException("Cannot modify a locked value.");
    }
}

void dish::BooleanValueBase::Assign(const dish::BooleanT &rhs)
{
    if(!IsLocked())
    {
        value() = rhs;
    }
    else
    {
        throw ValueLockedException("Cannot modify a locked value.");
    }
}

void dish::BooleanValueBase::Assign(const dish::IntegerT &rhs)
{
    if(!IsLocked())
    {
        value() = (0 != rhs);
    }
    else
    {
        throw ValueLockedException("Cannot modify a locked value.");
    }
}

/******************************************************************************

    dish::BooleanValue class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::BooleanValue > dish::BooleanValue::Values[2] = 
{
    std::shared_ptr< dish::BooleanValue >(new BooleanValue(false, dish::LOCKED)),
    std::shared_ptr< dish::BooleanValue >(new BooleanValue(true, dish::LOCKED))
};

#ifdef RECYCLE_PRIMITIVES

dish::BufferStack< void * > dish::BooleanValue::ObjectCache;

void *dish::BooleanValue::operator new(const std::size_t size)
{
    if(size == sizeof(BooleanValue))
    {
        if(!ObjectCache.IsEmpty())
        {
            return ObjectCache.Next();
        }
    }
    
    return ::operator new(size);
}

void dish::BooleanValue::operator delete(void * const ptr, const std::size_t size) throw()
{
    if(0 != ptr)
    {
        if(size == sizeof(BooleanValue))
        {
            if(ObjectCache.Insert(ptr))
            {
                return;
            }
        }
        
        ::operator delete(ptr);
    }
}

void dish::BooleanValue::Destroy() throw()
{
    while(!ObjectCache.IsEmpty())
    {
        ::operator delete(ObjectCache.Next());
    }
}

#endif
 
std::shared_ptr< dish::iAtomic > dish::BooleanValue::Copy() const
{
    return BooleanValue::MakeValue(mValue, UNLOCKED);
}
 
std::shared_ptr< dish::iAtomic > dish::BooleanValue::Clone() const
{
    return BooleanValue::MakeValue(mValue, IsLocked());
}

/******************************************************************************

    dish::IntegerValueBase class definitions

 ******************************************************************************/

dish::IntegerT dish::IntegerValueBase::Count(0);
 
std::shared_ptr< dish::iAtomic > dish::IntegerValueBase::memberBytes() const
{ 
    static std::shared_ptr< dish::iAtomic > IntegerBytes(dish::IntegerValue::MakeValue(INTEGER_NBYTES, dish::LOCKED));
    
    return IntegerBytes;
}

std::shared_ptr< dish::iAtomic > dish::IntegerValueBase::memberMinimum() const
{
    static std::shared_ptr< dish::iAtomic > IntegerMin(dish::IntegerValue::MakeValue(INTEGER_MIN, dish::LOCKED));
    
    return IntegerMin;
}

std::shared_ptr< dish::iAtomic > dish::IntegerValueBase::memberMaximum() const
{
    static std::shared_ptr< dish::iAtomic > IntegerMax(dish::IntegerValue::MakeValue(INTEGER_MAX, dish::LOCKED));
    
    return IntegerMax;
}

std::shared_ptr< dish::iAtomic > dish::IntegerValueBase::memberEps() const
{
    static std::shared_ptr< dish::iAtomic > IntegerEps(dish::IntegerValue::MakeValue(INTEGER_EPS, dish::LOCKED));
    
    return IntegerEps;
}
 
dish::TypeAtomic::TypeT dish::IntegerValueBase::Type() const throw()
{
    return typeInteger;
}
 
dish::BooleanT dish::IntegerValueBase::AsBoolean() const
{
    return (0 != value());
}

dish::IntegerT dish::IntegerValueBase::AsInteger() const
{
    return value();
}

dish::RealT dish::IntegerValueBase::AsReal() const
{
    return static_cast< RealT >(value());
}

dish::StringT dish::IntegerValueBase::AsString() const
{
    std::stringstream str;
    str << value();
    
    return str.str();
}

void dish::IntegerValueBase::Assign(std::shared_ptr< dish::iAtomic > rhs)
{
    if(!IsLocked())
    {
        value() = rhs->AsInteger();
    }
    else
    {
        throw ValueLockedException("Cannot modify a locked value.");
    }
}

void dish::IntegerValueBase::Assign(const dish::iValueAtomic &rhs)
{
    if(!IsLocked())
    {
        value() = rhs.AsInteger();
    }
    else
    {
        throw ValueLockedException("Cannot modify a locked value.");
    }
}

void dish::IntegerValueBase::Assign(const dish::BooleanT &rhs)
{
    if(!IsLocked())
    {
        value() = (rhs ? 1 : 0);
    }
    else
    {
        throw ValueLockedException("Cannot modify a locked value.");
    }
}

void dish::IntegerValueBase::Assign(const dish::IntegerT &rhs)
{
    if(!IsLocked())
    {
        value() = rhs;
    }
    else
    {
        throw ValueLockedException("Cannot modify a locked value.");
    }
}

/******************************************************************************

    dish::IntegerValue class definitions

 ******************************************************************************/

const dish::IntegerT dish::IntegerValue::CONSTANT_INTEGER_VALUES_MIN_INDEX(-1);
const dish::IntegerT dish::IntegerValue::CONSTANT_INTEGER_VALUES_MAX_INDEX(100);

static_assert(
    (dish::IntegerValue::CONSTANT_INTEGER_VALUES_MAX_INDEX > dish::IntegerValue::CONSTANT_INTEGER_VALUES_MIN_INDEX),
    "Range out of compliance: dish::IntegerValue::CONSTANT_INTEGER_VALUES_MAX_INDEX >= dish::IntegerValue::CONSTANT_INTEGER_VALUES_MIN_INDEX."
);

dish::IntegerValue::ValueTableT dish::IntegerValue::ValueTable(
    static_cast< dish::IntegerValue::ValueTableT::size_type >(CONSTANT_INTEGER_VALUES_MAX_INDEX - CONSTANT_INTEGER_VALUES_MIN_INDEX + 1)
);

std::shared_ptr< dish::IntegerValue > dish::IntegerValue::MakeValue(const dish::IntegerT &value, const bool &locked)
{
    if(locked && (CONSTANT_INTEGER_VALUES_MIN_INDEX <= value) && (value <= CONSTANT_INTEGER_VALUES_MAX_INDEX))
    {
        ValueTableT::value_type &elem(
            ValueTable[static_cast< ValueTableT::size_type >(value - CONSTANT_INTEGER_VALUES_MIN_INDEX)]
        );
        
        if(0 != elem.second.get())
        {
            ++elem.first;
        }
        else
        {
            elem.first = 1;
            elem.second.reset(new IntegerValue(value, LOCKED));
        }
        
        return elem.second;
    }
    
    return std::shared_ptr< IntegerValue >(new IntegerValue(value, locked));
}

void dish::IntegerValue::PrintTableStatistics(std::ostream &out)
{
    //  Count the number of allocated integers in the pool.
    IntegerT allocated(0);

    //  Bucket-counts for the number of integers or each value.
    BucketCounts bucketcounts(7);
    bucketcounts.AddBucket(0, 1);
    bucketcounts.AddBucket(1, 2);
    bucketcounts.AddBucket(2, 10);
    bucketcounts.AddBucket(10, 100);
    bucketcounts.AddBucket(100, 500);
    bucketcounts.AddBucket(500, 1000);
    bucketcounts.AddBucket(1000, 10000);
    
    //  Print out the number of each integer values created.
    IntegerT value(CONSTANT_INTEGER_VALUES_MIN_INDEX);
    for(ValueTableT::const_iterator i(ValueTable.begin()), last_i(ValueTable.end()); i != last_i; ++i, ++value)
    {
        IntegerT index(0);
    
        if(0 != i->second.get())
        {
            ++allocated;
            
            index = i->first;
        
            out << "";
            out << value;
            out << " : ";
            out << i->first;
            out << std::endl;
        }
        
        ++bucketcounts[index];
    }
    
    out << std::endl;
    
    //  Print out summary information.
    out << "Constant integers between [" << CONSTANT_INTEGER_VALUES_MIN_INDEX << ", " << CONSTANT_INTEGER_VALUES_MAX_INDEX << "]:" << std::endl;
    out << "        Allocated: " << allocated << std::endl;
    out << "              [0]: " << bucketcounts[0] << std::endl;
    out << "              [1]: " << bucketcounts[1] << std::endl;
    out << "          [2, 10): " << bucketcounts[2] << std::endl;
    out << "        [10, 100): " << bucketcounts[10] << std::endl;
    out << "       [100, 500): " << bucketcounts[100] << std::endl;
    out << "      [500, 1000): " << bucketcounts[500] << std::endl;
    out << "    [1000, 10000): " << bucketcounts[1000] << std::endl;
    out << "                 : " << bucketcounts[-1] << std::endl;
}

#ifdef RECYCLE_PRIMITIVES

    dish::BufferStack< void * > dish::IntegerValue::ObjectCache;

    void *dish::IntegerValue::operator new(const std::size_t size)
    {
        if(size == sizeof(IntegerValue))
        {
            if(!ObjectCache.IsEmpty())
            {
                return ObjectCache.Next();
            }
        }
        
        return ::operator new(size);
    }

    void dish::IntegerValue::operator delete(void * const ptr, const std::size_t size) throw()
    {
        if(0 != ptr)
        {
            if(size == sizeof(IntegerValue))
            {
                if(ObjectCache.Insert(ptr))
                {
                    return;
                }
            }
            
            ::operator delete(ptr);
        }
    }

    void dish::IntegerValue::Destroy() throw()
    {
        while(!ObjectCache.IsEmpty())
        {
            ::operator delete(ObjectCache.Next());
        }
    }

#endif
 
std::shared_ptr< dish::iAtomic > dish::IntegerValue::Copy() const
{
    return IntegerValue::MakeValue(mValue, UNLOCKED);
}
 
std::shared_ptr< dish::iAtomic > dish::IntegerValue::Clone() const
{
    return IntegerValue::MakeValue(mValue, IsLocked());
}

/******************************************************************************

    dish::RangedIntegerValue class definitions

 ******************************************************************************/

void dish::RangedIntegerValue::checkValue()
{
    switch(mRangeBounds)
    {
        case rngbndError:
        {
            if((mValue < mMinimumValue) || (mValue > mMaximumValue))
            {
                std::stringstream message;
                message << "The value assigned, ";
                message << mValue;
                message << ", does not fall within the allowable range [";
                message << mMinimumValue;
                message << ", ";
                message << mMaximumValue;
                message << "].";
                
                throw IllegalValueException(message.str());
            }
        } break;
                
        case rngbndCap:
        {
            if(mValue < mMinimumValue)
            {
                mValue = mMinimumValue;
            }
            
            else if(mValue > mMaximumValue)
            {
                mValue = mMaximumValue;
            }
            
            else
            {
                //  Empty
            }
        } break;
        
        case rngbndRollover:
        {
            const RealT delta(mMaximumValue - mMinimumValue);
        
            while(mValue < mMinimumValue)
            {
                mValue += delta;
            }
            
            while(mValue > mMaximumValue)
            {
                mValue -= delta;
            }
        } break;
        
        default:
        {
            assert(false);
        }
        
    }
}
 
std::shared_ptr< dish::iAtomic > dish::RangedIntegerValue::Copy() const
{
    return RangedIntegerValue::MakeValue(mMinimumValue, mMaximumValue, mRangeBounds, mValue, UNLOCKED);
}

std::shared_ptr< dish::iAtomic > dish::RangedIntegerValue::Clone() const
{
    return RangedIntegerValue::MakeValue(mMinimumValue, mMaximumValue, mRangeBounds, mValue, UNLOCKED);
}

void dish::RangedIntegerValue::Assign(std::shared_ptr< dish::iAtomic > rhs)
{
    IntegerValueBase::Assign(rhs);
    checkValue();
}

void dish::RangedIntegerValue::Assign(const dish::iValueAtomic &rhs)
{
    IntegerValueBase::Assign(rhs);
    checkValue();
}

void dish::RangedIntegerValue::Assign(const dish::BooleanT &rhs)
{
    IntegerValueBase::Assign(rhs);
    checkValue();
}

void dish::RangedIntegerValue::Assign(const dish::IntegerT &rhs)
{
    IntegerValueBase::Assign(rhs);
    checkValue();
}

/******************************************************************************

    dish::RealValueBase class definitions

 ******************************************************************************/

dish::IntegerT dish::RealValueBase::Count(0);
 
std::shared_ptr< dish::iAtomic > dish::RealValueBase::memberBytes() const
{
    static std::shared_ptr< dish::iAtomic > RealBytes(dish::IntegerValue::MakeValue(REAL_NBYTES, dish::LOCKED));

    return RealBytes;
}

std::shared_ptr< dish::iAtomic > dish::RealValueBase::memberMinimum() const
{
    static std::shared_ptr< dish::iAtomic > RealMin(dish::RealValue::MakeValue(REAL_MIN, dish::LOCKED));
    
    return RealMin;
}

std::shared_ptr< dish::iAtomic > dish::RealValueBase::memberMaximum() const
{
    static std::shared_ptr< dish::iAtomic > RealMax(dish::RealValue::MakeValue(REAL_MAX, dish::LOCKED));
    
    return RealMax;
}

std::shared_ptr< dish::iAtomic > dish::RealValueBase::memberEps() const
{
    static std::shared_ptr< dish::iAtomic > RealEps(dish::RealValue::MakeValue(REAL_EPS, dish::LOCKED));
    
    return RealEps;
}
 
dish::TypeAtomic::TypeT dish::RealValueBase::Type() const throw()
{
    return typeReal;
}
 
dish::BooleanT dish::RealValueBase::AsBoolean() const
{
    return (0.0 != value());
}

dish::IntegerT dish::RealValueBase::AsInteger() const
{
    return static_cast< IntegerT >(value());
}

dish::RealT dish::RealValueBase::AsReal() const
{
    return value();
}

dish::StringT dish::RealValueBase::AsString() const
{
    std::stringstream str;
    str.precision(15);
    
    str << value();
    
    return str.str();
}

void dish::RealValueBase::Assign(std::shared_ptr< dish::iAtomic > rhs)
{
    if(!IsLocked())
    {
        value() = rhs->AsReal();
    }
    else
    {
        throw ValueLockedException("Cannot modify a locked value.");
    }
}

void dish::RealValueBase::Assign(const dish::iValueAtomic &rhs)
{
    if(!IsLocked())
    {
        value() = rhs.AsReal();
    }
    else
    {
        throw ValueLockedException("Cannot modify a locked value.");
    }
}

void dish::RealValueBase::Assign(const dish::IntegerT &rhs)
{
    if(!IsLocked())
    {
        value() = rhs;
    }
    else
    {
        throw ValueLockedException("Cannot modify a locked value.");
    }
}

void dish::RealValueBase::Assign(const dish::RealT &rhs)
{
    if(!IsLocked())
    {
        value() = rhs;
    }
    else
    {
        throw ValueLockedException("Cannot modify a locked value.");
    }
}

/******************************************************************************

    dish::RealValue class definitions

 ******************************************************************************/
 
#ifdef RECYCLE_PRIMITIVES
 
    dish::BufferStack< void * > dish::RealValue::ObjectCache;

    void *dish::RealValue::operator new(const std::size_t size)
    {
        if(size == sizeof(RealValue))
        {
            if(!ObjectCache.IsEmpty())
            {
                return ObjectCache.Next();
            }
        }
        
        return ::operator new(size);
    }

    void dish::RealValue::operator delete(void * const ptr, const std::size_t size) throw()
    {
        if(0 != ptr)
        {
            if(size == sizeof(RealValue))
            {
                if(ObjectCache.Insert(ptr))
                {
                    return;
                }
            }
            
            ::operator delete(ptr);
        }
    }

    void dish::RealValue::Destroy() throw()
    {
        while(!ObjectCache.IsEmpty())
        {
            ::operator delete(ObjectCache.Next());
        }
    }

#endif
 
std::shared_ptr< dish::iAtomic > dish::RealValue::Copy() const
{
    return RealValue::MakeValue(mValue, UNLOCKED);
}
 
std::shared_ptr< dish::iAtomic > dish::RealValue::Clone() const
{
    return RealValue::MakeValue(mValue, IsLocked());
}

/******************************************************************************

    dish::RangedRealValue class definitions

 ******************************************************************************/

void dish::RangedRealValue::checkValue()
{
    switch(mRangeBounds)
    {
        case rngbndError:
        {
            if((mValue < mMinimumValue) || (mValue > mMaximumValue))
            {
                std::stringstream message;
                message << "The value assigned, ";
                message << mValue;
                message << ", does not fall within the allowable range [";
                message << mMinimumValue;
                message << ", ";
                message << mMaximumValue;
                message << "].";
                
                throw IllegalValueException(message.str());
            }
        } break;
                
        case rngbndCap:
        {
            if(mValue < mMinimumValue)
            {
                mValue = mMinimumValue;
            }
            
            else if(mValue > mMaximumValue)
            {
                mValue = mMaximumValue;
            }
            
            else
            {
                //  Empty
            }
        } break;
        
        case rngbndRollover:
        {
            const RealT delta(mMaximumValue - mMinimumValue);
        
            while(mValue < mMinimumValue)
            {
                mValue += delta;
            }
            
            while(mValue > mMaximumValue)
            {
                mValue -= delta;
            }
        } break;
        
        default:
        {
            assert(false);
        }
        
    }
}
 
std::shared_ptr< dish::iAtomic > dish::RangedRealValue::Copy() const
{
    return RangedRealValue::MakeValue(mMinimumValue, mMaximumValue, mRangeBounds, mValue, UNLOCKED);
}

std::shared_ptr< dish::iAtomic > dish::RangedRealValue::Clone() const
{
    return RangedRealValue::MakeValue(mMinimumValue, mMaximumValue, mRangeBounds, mValue, UNLOCKED);
}

void dish::RangedRealValue::Assign(std::shared_ptr< dish::iAtomic > rhs)
{
    RangedRealValue::Assign(rhs);
    checkValue();
}

void dish::RangedRealValue::Assign(const dish::iValueAtomic &rhs)
{
    RangedRealValue::Assign(rhs);
    checkValue();
}

void dish::RangedRealValue::Assign(const dish::BooleanT &rhs)
{
    RangedRealValue::Assign(rhs);
    checkValue();
}

void dish::RangedRealValue::Assign(const dish::IntegerT &rhs)
{
    RangedRealValue::Assign(rhs);
    checkValue();
}

/******************************************************************************

    dish::StringValueBase class definitions

 ******************************************************************************/

dish::IntegerT dish::StringValueBase::Count(0);
 
dish::TypeAtomic::TypeT dish::StringValueBase::Type() const throw()
{
    return typeString;
}
 
dish::BooleanT dish::StringValueBase::AsBoolean() const
{
    if(IsEqual(value(), "false", CASE_INSENSITIVE))
    {
        return false;
    }
    
    else if(IsEqual(value(), "true", CASE_INSENSITIVE))
    {
        return true;
    }
    
    std::stringstream message;
    message << "Cannot convert the string '";
    message << value();
    message << "' to a boolean.";
    
    throw IllegalCastException(message.str());
}

dish::IntegerT dish::StringValueBase::AsInteger() const
{
    std::stringstream in(value());
    
    IntegerT val;
    in >> val;
    
    if(!in.fail())
    {
        return val;
    }
    
    std::stringstream message;
    message << "Cannot parse an integer value from the string \"";
    message << value();
    message << "\".";
    
    throw IllegalCastException(message.str());
}

dish::RealT dish::StringValueBase::AsReal() const
{
    std::stringstream in(value());
    
    RealT val;
    in >> val;
    
    if(!in.fail())
    {
        return val;
    }
    
    std::stringstream message;
    message << "Cannot parse a real value from the string \"";
    message << value();
    message << "\".";
    
    throw IllegalCastException(message.str());
}

dish::StringT dish::StringValueBase::AsString() const
{
    return value();
}

void dish::StringValueBase::Assign(std::shared_ptr< dish::iAtomic > rhs)
{
    if(!IsLocked())
    {
        invalidate();
    
        value() = rhs->AsString();
    }
    else
    {
        throw ValueLockedException("Cannot modify a locked value.");
    }
}

void dish::StringValueBase::Assign(const dish::iValueAtomic &rhs)
{
    if(!IsLocked())
    {
        invalidate();
    
        value() = rhs.AsString();
    }
    else
    {
        throw ValueLockedException("Cannot modify a locked value.");
    }
}

void dish::StringValueBase::Assign(const dish::StringT &rhs)
{
    if(!IsLocked())
    {
        invalidate();
    
        value() = rhs;
    }
    else
    {
        throw ValueLockedException("Cannot modify a locked value.");
    }
}

std::shared_ptr< dish::iAtomic > dish::StringValueBase::Member(const std::string &member) const
{
    if(IsEqual(member, "finish", CASE_INSENSITIVE))
    {
        if(0 == mFinishV.get())
        {
            mFinishV = IntegerValue::MakeValue(value().length() - 1, LOCKED);
        }
    
        return mFinishV;
    }
    
    else if(IsEqual(member, "length", CASE_INSENSITIVE))
    {
        if(0 == mLengthV.get())
        {
            mLengthV = IntegerValue::MakeValue(value().length(), LOCKED);
        }
    
        return mLengthV;
    }
    
    else if(IsEqual(member, "start", CASE_INSENSITIVE))
    {
        static std::shared_ptr< iAtomic > start(IntegerValue::MakeValue(0, LOCKED));
    
        return start;
    }
    
    return iAtomic::Member(member);
}

std::shared_ptr< dish::iAtomic > dish::StringValueBase::Element(const dish::IntegerT &index) const
{
    if((index >= 0) && (index < static_cast< IntegerT >(value().size())))
    {
        return IntegerValue::MakeValue(value()[index], LOCKED);
    }

    std::stringstream message;
    message << "The specified index, ";
    message << index;
    message << ", does not fall within [0, ";
    message << value().size();
    message << ").";
    
    throw IllegalIndexException(message.str());
}

void dish::StringValueBase::Swap(const IntegerT &a, const IntegerT &b)
{
    if(!IsLocked())
    {
        const IntegerT length(static_cast< IntegerT >(value().size()));

        if((a >= 0) && (a < length) && (b >= 0) && (b < length))
        {
            if(a != b)
            {
                invalidate();
                
                std::swap(value()[a], value()[b]);
            }
        }
        else
        {
            std::stringstream message;
            message << "The specified index, ";
            message << (((a < 0) && (a >= length)) ? a : b);
            message << ", does not fall within [0, ";
            message << length;
            message << ").";
        
            throw IllegalIndexException(message.str());
        }
    }
    else
    {
        throw ValueLockedException("Cannot modify a locked value.");
    }
}

void dish::StringValueBase::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << "\"";
    out << value();
    out << "\"";
}

/******************************************************************************

    dish::StringValue class definitions

 ******************************************************************************/

#ifdef RECYCLE_PRIMITIVES

    dish::BufferStack< void * > dish::StringValue::ObjectCache;

    void *dish::StringValue::operator new(const std::size_t size)
    {
        if(size == sizeof(StringValue))
        {
            if(!ObjectCache.IsEmpty())
            {
                return ObjectCache.Next();
            }
        }
        
        return ::operator new(size);
    }

    void dish::StringValue::operator delete(void * const ptr, const std::size_t size) throw()
    {
        if(0 != ptr)
        {
            if(size == sizeof(StringValue))
            {
                if(ObjectCache.Insert(ptr))
                {
                    return;
                }
            }
            
            ::operator delete(ptr);
        }
    }

    void dish::StringValue::Destroy() throw()
    {
        while(!ObjectCache.IsEmpty())
        {
            ::operator delete(ObjectCache.Next());
        }
    }

#endif
 
std::shared_ptr< dish::iAtomic > dish::StringValue::Copy() const
{
    return StringValue::MakeValue(mValue, UNLOCKED);
}
 
std::shared_ptr< dish::iAtomic > dish::StringValue::Clone() const
{
    return StringValue::MakeValue(mValue, IsLocked());
}

/******************************************************************************

    dish::ArrayValue class definitions

 ******************************************************************************/
 
dish::IntegerT dish::ArrayValue::Count(0);

dish::ArrayValue::ArrayValue(const dish::IntegerT &mini, const dish::IntegerT &nelem, std::shared_ptr< dish::iAtomic > type) : dish::iAtomic(),
    mValue(),
    mIndexOffset(-mini),
    
    mInitialized(false),
    mFinishV(),
    mLengthV(),
    mStartV()
{
    assert(nelem >= 0);
    assert(type);

    mValue.resize(nelem);
    
    std::for_each(
        mValue.begin(), mValue.end(),
        [&](ArrayT::value_type &element)
        {
            element = type->Declare();
        }
    );
    
    ++Count;
}

void dish::ArrayValue::Lock() throw()
{
    std::for_each(
        mValue.begin(), mValue.end(),
        [&](ArrayT::value_type &element)
        {
            element->Lock();
        }
    );
    
    iAtomic::Lock();
}
 
dish::TypeAtomic::TypeT dish::ArrayValue::Type() const throw()
{
    return typeArray;
}
 
std::shared_ptr< dish::iAtomic > dish::ArrayValue::Copy() const
{
    std::shared_ptr< ArrayValue > value(new ArrayValue(-mIndexOffset, mValue.size()));
    
    ArrayT::const_iterator i(mValue.begin());
    
    std::for_each(
        value->mValue.begin(), value->mValue.end(),
        [&](ArrayT::value_type &element)
        {
            element = (*i++)->Clone();
        }
    );
    
    return value;
}

dish::StringT dish::ArrayValue::AsString() const
{
    std::stringstream str;
    
    str << "Array [";
    str << -mIndexOffset;
    str << ", ";
    str << (static_cast< IntegerT >(mValue.size()) - mIndexOffset - 1);
    str << "]{ ";
    
    std::for_each(
        mValue.begin(), mValue.end(),
        [&](const ArrayT::value_type &value)
        {
            str << value->AsString();
            str << ", ";
        }
    );
    
    str << " }";
    
    return str.str();
}

void dish::ArrayValue::Assign(std::shared_ptr< iAtomic > rhs)
{
    if(Member("length")->AsInteger() == rhs->Member("length")->AsInteger())
    {
        IntegerT lhs_i(Member("start")->AsInteger());
        const IntegerT lhs_last_i(Member("finish")->AsInteger());
        
        IntegerT rhs_i(rhs->Member("start")->AsInteger());

        while(lhs_i <= lhs_last_i)
        {
            Element(lhs_i++)->Assign(rhs->Element(rhs_i++));
        }
    }
    else
    {
        throw MatrixDimensionErrorException("The matrix boundaries of the left- and right- sides of the assignment do not match.");
    }
}

std::shared_ptr< dish::iAtomic > dish::ArrayValue::Member(const std::string &member) const
{
    if(IsEqual("start", member, CASE_INSENSITIVE))
    {
        if(0 == mStartV.get())
        {
            mStartV = IntegerValue::MakeValue(-mIndexOffset, LOCKED);
        }
        
        return mStartV;
    }
    
    else if(IsEqual("finish", member, CASE_INSENSITIVE))
    {
        if(0 == mFinishV.get())
        {
            mFinishV = IntegerValue::MakeValue(static_cast< IntegerT >(mValue.size()) - mIndexOffset - 1, LOCKED);
        }
        
        return mFinishV;
    }
    
    else if(IsEqual("length", member, CASE_INSENSITIVE))
    {
        if(0 == mLengthV.get())
        {
            mLengthV = IntegerValue::MakeValue(static_cast< IntegerT >(mValue.size()), LOCKED);
        }
        
        return mLengthV;
    }
    
    else if(IsEqual("empty", member, CASE_INSENSITIVE))
    {
        return BooleanValue::MakeLockedValue(mValue.empty());
    }

    return iAtomic::Member(member);
}

dish::IntegerT dish::ArrayValue::Add(std::shared_ptr< dish::iAtomic > element)
{
    assert(element);
    
    if(!IsLocked())
    {
        invalidate();
        
        IntegerT ret(mIndexOffset);
        
        if(mInitialized)
        {
            ret += static_cast< IntegerT >(mValue.size());
            mValue.push_back(element);
        }
        else
        {
            mValue.front() = element;
            mInitialized = true;
        }
        
        return ret;
    }
    
    throw ValueLockedException("Cannot modify a locked value.");
}

dish::IntegerT dish::ArrayValue::Add(std::shared_ptr< dish::iAtomic > element, const IntegerT &index)
{
    assert(element);
    
    if(!IsLocked())
    {
        invalidate();
    
        const IntegerT array_size(static_cast< IntegerT >(mValue.size()));
        
        if(mInitialized)
        {
            const IntegerT adj_index(index + mIndexOffset);
            
            if(adj_index <= 0)
            {
                mValue.insert(mValue.begin(), element);
            }
            
            else if(adj_index >= array_size)
            {
                mValue.insert(mValue.end(), element);
            }
            
            else
            {
                mValue.insert(mValue.begin() + adj_index, element);
            }
        }
        else
        {
            mValue.front() = element;
            mInitialized = true;
        }
        
        return (array_size + mIndexOffset + 1);
    }
    
    throw ValueLockedException("Cannot modify a locked value.");
}

std::shared_ptr< dish::iAtomic > dish::ArrayValue::Element(const dish::IntegerT &index) const
{
    const ArrayT::size_type adj_index(
        static_cast< ArrayT::size_type >(index + mIndexOffset)
    );
    
    if(adj_index < mValue.size())
    {
        return mValue[adj_index];
    }

    std::stringstream message;
    message << "The specified index, ";
    message << index;
    message << ", does not fall within [";
    message << -mIndexOffset;
    message << ", ";
    message << (static_cast< IntegerT >(mValue.size()) - mIndexOffset - 1);
    message << "].";
    
    throw IllegalIndexException(message.str());
}

void dish::ArrayValue::Swap(const dish::IntegerT &a, const dish::IntegerT &b)
{
    if(!IsLocked())
    {
        invalidate();
    
        const ArrayT::size_type length(mValue.size());

        const ArrayT::size_type aindex(
            static_cast< ArrayT::size_type >(a + mIndexOffset)
        );
        
        const ArrayT::size_type bindex(
            static_cast< ArrayT::size_type >(b + mIndexOffset)
        );
        
        if((aindex >= 0) && (aindex < length) && (bindex >= 0) && (bindex < length))
        {
            if(aindex != bindex)
            {
                std::swap(mValue[aindex], mValue[bindex]);
            }
        }
        else
        {
            std::stringstream message;
            message << "The specified index, ";
            message << (((aindex < 0) || (aindex >= length)) ? a : b);
            message << ", does not fall within [";
            message << -mIndexOffset;
            message << ", ";
            message << (static_cast< IntegerT >(mValue.size()) - mIndexOffset - 1);
            message << "].";
            
            throw IllegalIndexException(message.str());
        }
    }
    else
    {
        throw ValueLockedException("Cannot modify a locked value.");
    }
}

void dish::ArrayValue::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);

    out << "[";
    out << (-mIndexOffset);
    out << ", ";
    out << (static_cast< IntegerT >(mValue.size()) + mIndexOffset - 1);
    out << "]: ";
    
    out << "{ ";

    std::for_each(
        mValue.begin(), mValue.end(),
        [&](const ArrayT::value_type &element)
        {
            element->Print(out, indent + 8);
            out << ", ";
        }
    );
    
    out << " }";
}

/******************************************************************************

    dish::DictionaryValue::ContainsMethod class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::DictionaryValue::ContainsMethod::Execute(dish::LanguageSymbolTable &symtab) const
{
    const auto &thisval(thisValue().mValue);

    return BooleanValue::MakeLockedValue(thisval.end() != thisval.find(getParam(symtab, "str")->AsString()));
}

/******************************************************************************

    dish::DictionaryValue::ValueHolder class definitions

 ******************************************************************************/

void dish::DictionaryValue::ValueHolder::Lock() throw()
{
    mHeldValue->Lock();
    
    iAtomic::Lock();
}

dish::iAtomic::TypeT dish::DictionaryValue::ValueHolder::Type() const throw()
{
    return mHeldValue->Type();
}

std::shared_ptr< dish::iAtomic > dish::DictionaryValue::ValueHolder::Copy() const
{
    //  Note, this is not a complete copy of the ValueHolder, just a copy of
    //  the held value. To copy the ValueHolder completely we would need to know
    //  theDictionary the value will be held by.
    return mHeldValue->Copy();
}

std::shared_ptr< dish::iAtomic > dish::DictionaryValue::ValueHolder::Clone() const
{
    //  Note, this is not a complete clone of the ValueHolder, just a clone of
    //  the held value. To clone to ValueHolder completely we would need to know
    //  the Dictionary the value will be held by.
    return mHeldValue->Clone();
}

dish::BooleanT dish::DictionaryValue::ValueHolder::AsBoolean() const
{
    return mHeldValue->AsBoolean();
}

dish::IntegerT dish::DictionaryValue::ValueHolder::AsInteger() const
{
    return mHeldValue->AsInteger();
}

dish::RealT dish::DictionaryValue::ValueHolder::AsReal() const
{
    return mHeldValue->AsReal();
}

dish::StringT dish::DictionaryValue::ValueHolder::AsString() const
{
    return mHeldValue->AsString();
}

void dish::DictionaryValue::ValueHolder::Assign(std::shared_ptr< dish::iAtomic > rhs)
{
    assert(rhs);
    
    if(!IsLocked())
    {
        mDictionary.invalidate();
    
        mHeldValue = rhs->Clone();
    }
    else
    {
        throw ValueLockedException("Cannot modify a locked value.");
    }
}

std::shared_ptr< dish::iAtomic > dish::DictionaryValue::ValueHolder::Member(const std::string &member) const
{
    return mHeldValue->Member(member);
}

dish::IntegerT dish::DictionaryValue::ValueHolder::Add(std::shared_ptr< dish::iAtomic > element)
{
    mDictionary.invalidate();

    return mHeldValue->Add(element);
}

dish::IntegerT dish::DictionaryValue::ValueHolder::Add(std::shared_ptr< dish::iAtomic > element, const dish::IntegerT &index)
{
    mDictionary.invalidate();
    
    return mHeldValue->Add(element, index);
}

std::shared_ptr< dish::iAtomic > dish::DictionaryValue::ValueHolder::Element(const dish::IntegerT &index) const
{
    mDictionary.invalidate();
    
    return mHeldValue->Element(index);
}

dish::IntegerT dish::DictionaryValue::ValueHolder::Add(std::shared_ptr< dish::iAtomic > key, std::shared_ptr< dish::iAtomic > value)
{
    mDictionary.invalidate();
    
    return mHeldValue->Add(key, value);
}

std::shared_ptr< dish::iAtomic > dish::DictionaryValue::ValueHolder::Keys() const
{
    return mHeldValue->Keys();
}

std::shared_ptr< dish::iAtomic > dish::DictionaryValue::ValueHolder::Lookup(const dish::StringT &key) const
{
    mDictionary.invalidate();
    
    return mHeldValue->Lookup(key);
}

std::shared_ptr< dish::iAtomic > dish::DictionaryValue::ValueHolder::Declare() const
{
    return mHeldValue->Declare();
}

std::shared_ptr< dish::iAtomic > dish::DictionaryValue::ValueHolder::Execute(dish::LanguageSymbolTable &symtab) const
{
    return mHeldValue->Execute(symtab);
}

const dish::iExecutableAtomic::ParamListT &dish::DictionaryValue::ValueHolder::ParameterList() const
{
    return mHeldValue->ParameterList();
}

dish::IntegerT dish::DictionaryValue::ValueHolder::NumParameters() const
{
    return mHeldValue->NumParameters();
}

/******************************************************************************

    dish::DictionaryValue class definitions

 ******************************************************************************/
 
dish::IntegerT dish::DictionaryValue::Count(0);

void dish::DictionaryValue::Lock() throw()
{
    std::for_each(
        mValue.begin(), mValue.end(),
        [](DictionaryT::value_type &value)
        {
            value.second->Lock();
        }
    );
    
    iAtomic::Lock();
}

dish::iAtomic::TypeT dish::DictionaryValue::Type() const throw()
{
    return typeDictionary;
}

std::shared_ptr< dish::iAtomic > dish::DictionaryValue::Copy() const
{
    std::shared_ptr< DictionaryValue > dictionary(new DictionaryValue());
    
    std::for_each(
        mValue.begin(), mValue.end(),
        [&](const DictionaryT::value_type &value)
        {
            dictionary->Add(StringValue::MakeValue(value.first), value.second->Copy());
        }
    );
    
    return dictionary;
}

dish::StringT dish::DictionaryValue::AsString() const
{
    std::stringstream out;
    bool first(true);
    
    out << "Dictionary { ";
    
    std::for_each(
        mValue.begin(), mValue.end(),
        [&](const DictionaryT::value_type &value)
        {
            if(!first)
            {
                out << ", ";
            }
        
            out << value.first;
            out << " : ";
            out << value.second->AsString();
            
            first = false;
        }
    );
    
    out << " }";
    
    return out.str();
}

void dish::DictionaryValue::Assign(std::shared_ptr< dish::iAtomic > rhs)
{
    if(!IsLocked())
    {
        if(typeDictionary == rhs->Type())
        {
            std::shared_ptr< iAtomic > keys(rhs->Keys());
        
            invalidate();
            mValue.clear();
            
            for(IntegerT i(keys->Member("start")->AsInteger()), last_i(keys->Member("finish")->AsInteger()); i <= last_i; ++i)
            {
                std::shared_ptr< iAtomic > key(keys->Element(i));
            
                Add(key, rhs->Lookup(key->AsString())->Clone());
            }
        }
        else
        {
            throw IllegalCastException("Cannot cast right-hand value to 'dictionary'.");
        }
    }
    else
    {
        throw ValueLockedException("Cannot modify a locked value.");
    }
}

std::shared_ptr< dish::iAtomic > dish::DictionaryValue::Member(const std::string &member) const
{
    if(IsEqual("contains", member, CASE_INSENSITIVE))
    {
        if(0 == mContainsF.get())
        {
            mContainsF = ContainsMethod::MakeValue(*this);
        }
        
        return mContainsF;
    }
    
    else if(IsEqual("count", member, CASE_INSENSITIVE))
    {
        if(0 == mCountV.get())
        {
            mCountV = IntegerValue::MakeValue(mValue.size(), LOCKED);
        }
        
        return mCountV;
    }
    
    else if(IsEqual("empty", member, CASE_INSENSITIVE))
    {
        if(0 == mEmptyV.get())
        {
            mEmptyV = BooleanValue::MakeLockedValue(mValue.empty());
        }
        
        return mEmptyV;
    }
    
    else if(IsEqual("keys", member, CASE_INSENSITIVE))
    {
        if(0 == mKeysV.get())
        {
            mKeysV = Keys();
            mKeysV->Lock();
        }
        
        return mKeysV;
    }

    return iAtomic::Member(member);
}

dish::IntegerT dish::DictionaryValue::Add(std::shared_ptr< dish::iAtomic > key, std::shared_ptr< dish::iAtomic > value)
{
    assert(value);

    invalidate();

    const auto element(
        mValue.insert(
            std::make_pair(
                key->AsString(), 
                ValueHolder::MakeValue(*this, value)
            )
        )
    );
    
    if(!element.second)
    {
        element.first->second->Assign(value);
    }
    
    return static_cast< IntegerT >(mValue.size());
}

std::shared_ptr< dish::iAtomic > dish::DictionaryValue::Keys() const
{
    std::shared_ptr< ArrayValue > keys(ArrayValue::MakeValue(0));
    
    std::for_each(
        mValue.begin(), mValue.end(),
        [&](const DictionaryT::value_type &value)
        {
            keys->Add(StringValue::MakeValue(value.first, LOCKED));
        }
    );
    
    return keys;
}

std::shared_ptr< dish::iAtomic > dish::DictionaryValue::Lookup(const dish::StringT &key) const
{
    const auto element(mValue.find(key));
    
    if(mValue.end() != element)
    {
        return element->second;
    }
    
    else if(!IsLocked())
    {
        invalidate();
    
        std::shared_ptr< iAtomic > value(ValueHolder::MakeValue(*this, NullValue::MakeValue()));
        mValue[key] = value;
    
        return value;
    }
    
    else
    {
        //  Empty
    }
    
    throw ValueLockedException("Cannot modify a locked value.");
}

void dish::DictionaryValue::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << "dictionary" << std::endl;
    
    std::for_each(
        mValue.begin(), mValue.end(),
        [&](const DictionaryT::value_type &value)
        {
            printIndent(out, indent + INDENT);
            out << value.first;
            out << ": ";
            value.second->Print(out, 0);
            out << std::endl;
        }
    );
    
    printIndent(out, indent);
    out << "end";
}

/******************************************************************************

    dish::StructureValue class definitions

 ******************************************************************************/
 
dish::IntegerT dish::StructureValue::Count(0);
 
void dish::StructureValue::generateStructureMemberExistsError(const std::string &id)
{
    std::stringstream message;
    message << "The member '";
    message << id;
    message << "' already exists.";
    
    throw DuplicateSymbolException(message.str());
}

void dish::StructureValue::Lock() throw()
{
    std::for_each(
        mMemberSet.begin(), mMemberSet.end(),
        [&](MemberSetT::value_type &value)
        {
            value.second->Lock();
        }
    );
    
    iAtomic::Lock();
}

dish::iAtomic::TypeT dish::StructureValue::Type() const throw()
{
    return typeStructure;
}
 
std::shared_ptr< dish::iAtomic > dish::StructureValue::Copy() const
{
    std::shared_ptr< StructureValue > value(new StructureValue());
    
    std::for_each(
        mMemberSet.begin(), mMemberSet.end(),
        [&](const MemberSetT::value_type &element)
        {
            value->Add(element.first, element.second->Clone());
        }
    );
    
    return value;
}

dish::StringT dish::StructureValue::AsString() const
{
    std::stringstream out;
    bool first(true);
    
    std::for_each(
        mMemberSet.begin(), mMemberSet.end(),
        [&](const MemberSetT::value_type &element)
        {
            if(!first)
            {
                out << ", ";
            }
        
            out << element.first;
            out << ": ";
            out << element.second->AsString();
            
            first = false;
        }
    );
    
    return out.str();
}

dish::IntegerT dish::StructureValue::Members(dish::StructureValue::MemberNameSetT &members) const
{
    std::for_each(
        mMemberSet.begin(), mMemberSet.end(),
        [&](const dish::StructureValue::MemberSetT::value_type &member)
        {
            members.push_back(member.first);
        }
    );
    
    return static_cast< IntegerT >(mMemberSet.size());
}

std::shared_ptr< dish::iAtomic > dish::StructureValue::Member(const std::string &member) const
{
    const MemberSetT::const_iterator elem(mMemberSet.find(member));
    
    if(mMemberSet.end() != elem)
    {
        return elem->second;
    }
    
    return iAtomic::Member(member);
}

void dish::StructureValue::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << "structure" << std::endl;
    
    std::for_each(
        mMemberSet.begin(), mMemberSet.end(),
        [&](const MemberSetT::value_type &value)
        {
            printIndent(out, indent + INDENT);
            out << value.first;
            out << ": ";
            value.second->Print(out, 0);
            out << std::endl;
        }
    );
    
    printIndent(out, indent);
    out << "end";
}

