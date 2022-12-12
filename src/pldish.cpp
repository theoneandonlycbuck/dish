/*
    This file is part of the DISH programming language, Copyright 2014, 2015,
    2016 by Chris Buck.
    
    DISH is free software: you can redistribute it and/or modify it provided
    
    
        (1) The following Copyright notice is displayed at runtime:
    
            DISH programming language copyright (c) 2014, 2015, 2016 by Chris Buck.
        
        (2) All source files duplicate this copyright statement in full.

    DISH is distributed in the hope that it will be useful, but WITHOUT ANY 
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS 
    FOR A PARTICULAR PURPOSE.
*/

#include <stdint.h>

#include <algorithm>
#include <cassert>
#include <cstring>
#include <sstream>

#include "exception.h"
#include "pldish.h"

/******************************************************************************

    dish::BooleanCppReferenceType class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::BooleanCppReferenceType::Declare(void * const ptr, const bool &locked) const
{
    return BooleanCppReferenceValue::MakeValue(ptr, locked);
}

void dish::BooleanCppReferenceType::Swap(void * const val1, void * const val2) const
{
    assert(nullptr != val1);
    assert(nullptr != val2);
    
    std::swap(*reinterpret_cast< BooleanT * >(val1), *reinterpret_cast< BooleanT * >(val2));
}

/******************************************************************************

    dish::IntegerCppReferenceType class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::IntegerCppReferenceType::Declare(void * const ptr, const bool &locked) const
{
    return IntegerCppReferenceValue::MakeValue(ptr, locked);
}

void dish::IntegerCppReferenceType::Swap(void * const val1, void * const val2) const
{
    assert(nullptr != val1);
    assert(nullptr != val2);
    
    std::swap(*reinterpret_cast< IntegerT * >(val1), *reinterpret_cast< IntegerT * >(val2));
}

/******************************************************************************

    dish::RealCppReferenceType class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::RealCppReferenceType::Declare(void * const ptr, const bool &locked) const
{
    return RealCppReferenceValue::MakeValue(ptr, locked);
}

void dish::RealCppReferenceType::Swap(void * const val1, void * const val2) const
{
    assert(nullptr != val1);
    assert(nullptr != val2);
    
    std::swap(*reinterpret_cast< RealT * >(val1), *reinterpret_cast< RealT * >(val2));
}

/******************************************************************************

    dish::StringCppReferenceType class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::StringCppReferenceType::Declare(void * const ptr, const bool &locked) const
{
    return StringCppReferenceValue::MakeValue(ptr, locked);
}

void dish::StringCppReferenceType::Swap(void * const val1, void * const val2) const
{
    assert(nullptr != val1);
    assert(nullptr != val2);
    
    std::swap(*reinterpret_cast< StringT * >(val1), *reinterpret_cast< StringT * >(val2));
}

/******************************************************************************

    dish::ArrayCppReferenceType class definitions

 ******************************************************************************/
 
dish::ArrayCppReferenceType::ArrayCppReferenceType(const IntegerT &n, std::shared_ptr< iCppReferenceType > type) : iCppReferenceType(),
    mNumElements(n),
    mType(type)
{
    assert(mNumElements > 0);
    assert(mType);
}

std::shared_ptr< dish::iAtomic > dish::ArrayCppReferenceType::Declare(void * const ptr, const bool &locked) const
{
    return ArrayCppReferenceValue::MakeValue(mNumElements, ptr, mType, locked);
}

void dish::ArrayCppReferenceType::Swap(void * const val1, void * const val2) const
{
    assert(nullptr != val1);
    assert(nullptr != val2);
    
    const IntegerT size(mNumElements * mType->Size());
    
    uint8_t buffer[size];
        
    std::memcpy(buffer, val1, size);
    std::memcpy(val1, val2, size);
    std::memcpy(val2, buffer, size);
}

/******************************************************************************

    dish::StructureCppReferenceType class definitions

 ******************************************************************************/

dish::StructureCppReferenceType::StructureCppReferenceType(const dish::IntegerT size) : iCppReferenceType(),
    mStructureSize(size),
    
    mMembers()
{
    assert(mStructureSize > 0);
}

void dish::StructureCppReferenceType::AddMember(const std::string &member, std::shared_ptr< iCppReferenceType > type, const size_t &offset)
{
    std::for_each(
        mMembers.begin(), mMembers.end(),
        [&](const MemberSetT::value_type &elem)
        {
            if(member == elem.first)
            {
                std::stringstream message;
                message << "Duplicate structure member id: '";
                message << member;
                message << "'.";
                
                throw DuplicateSymbolException(message.str());
            }
            
            else if(offset == elem.second.second)
            {
                std::stringstream message;
                message << "Duplicate structure member offset: ";
                message << elem.first;
                message << " and ";
                message << member;
                message << " share the same offset (";
                message << offset;
                message << ").";
                
                throw DuplicateSymbolException(message.str());
            }
            
            else
            {
                //  Empty
            }
        }
    );

    mMembers.push_back(std::make_pair(member, std::make_pair(type, offset)));
}

std::shared_ptr< dish::iAtomic > dish::StructureCppReferenceType::Declare(void * const ptr, const bool &locked) const
{
    assert(nullptr != ptr);
    
    std::shared_ptr< StructureCppReferenceValue > value(new StructureCppReferenceValue(ptr));
    
    std::for_each(
        mMembers.begin(), mMembers.end(),
        [&](const MemberSetT::value_type &member)
        {
            value->AddMember(member.first, member.second.first->Declare(reinterpret_cast< uint8_t * >(ptr) + member.second.second));
        }
    );
    
    if(locked)
    {
        value->Lock();
    }
    
    return value;
}

void dish::StructureCppReferenceType::Swap(void * const val1, void * const val2) const
{
    assert(nullptr != val1);
    assert(nullptr != val2);
    
    const size_t size(Size());
    
    uint8_t buffer[size];
        
    std::memcpy(buffer, val1, size);
    std::memcpy(val1, val2, size);
    std::memcpy(val2, buffer, size);
}

/******************************************************************************

    dish::BooleanCppReferenceValue class definitions

 ******************************************************************************/
 
dish::BooleanCppReferenceValue::BooleanCppReferenceValue(void * const value, const bool &locked) : dish::BooleanValueBase(locked),
    mValue(value)
{
    assert(nullptr != mValue);
}

dish::BooleanCppReferenceValue::BooleanCppReferenceValue(dish::BooleanT &value, const bool &locked) : dish::BooleanValueBase(locked),
    mValue(&value)
{
    assert(nullptr != mValue);
}

std::shared_ptr< dish::iAtomic > dish::BooleanCppReferenceValue::Copy() const
{
    throw IllegalOperationException("Cannot clone a reference to a CPP object.");
}

/******************************************************************************

    dish::IntegerCppReferenceValue class definitions

 ******************************************************************************/
 
dish::IntegerCppReferenceValue::IntegerCppReferenceValue(void * const value, const bool &locked) : dish::IntegerValueBase(locked),
    mValue(value)
{
    assert(nullptr != mValue);
}

dish::IntegerCppReferenceValue::IntegerCppReferenceValue(dish::IntegerT &value, const bool &locked) : dish::IntegerValueBase(locked),
    mValue(&value)
{
    assert(nullptr != mValue);
}

std::shared_ptr< dish::iAtomic > dish::IntegerCppReferenceValue::Copy() const
{
    throw IllegalOperationException("Cannot clone a reference to a CPP object.");
}

/******************************************************************************

    dish::RealCppReferenceValue class definitions

 ******************************************************************************/
 
dish::RealCppReferenceValue::RealCppReferenceValue(void * const value, const bool &locked) : dish::RealValueBase(locked),
    mValue(value)
{
    assert(nullptr != mValue);
}

dish::RealCppReferenceValue::RealCppReferenceValue(dish::RealT &value, const bool &locked) : dish::RealValueBase(locked),
    mValue(&value)
{
    assert(nullptr != mValue);
}

std::shared_ptr< dish::iAtomic > dish::RealCppReferenceValue::Copy() const
{
    throw IllegalOperationException("Cannot clone a reference to a CPP object.");
}

/******************************************************************************

    dish::StringCppReferenceValue class definitions

 ******************************************************************************/
 
dish::StringCppReferenceValue::StringCppReferenceValue(void * const value, const bool &locked) : dish::StringValueBase(locked),
    mValue(value)
{
    assert(nullptr != mValue);
}

dish::StringCppReferenceValue::StringCppReferenceValue(dish::StringT &value, const bool &locked) : dish::StringValueBase(locked),
    mValue(&value)
{
    assert(nullptr != mValue);
}

std::shared_ptr< dish::iAtomic > dish::StringCppReferenceValue::Copy() const
{
    throw IllegalOperationException("Cannot clone a reference to a CPP object.");
}

/******************************************************************************

    dish::ArrayCppReferenceValue class definitions

 ******************************************************************************/

dish::ArrayCppReferenceValue::ArrayCppReferenceValue(const IntegerT n, void * const values, std::shared_ptr< iCppReferenceType > type, const bool &locked) : iAtomic(locked),
    mNumElements(n),
    mValues(values),
    mType(type)
{
    assert(mNumElements > 0);
    assert(nullptr != mValues);
    assert(mType);
}

dish::iAtomic::TypeT dish::ArrayCppReferenceValue::Type() const throw()
{
    return iAtomic::typeArray;
}

std::shared_ptr< dish::iAtomic > dish::ArrayCppReferenceValue::Copy() const
{
    throw IllegalOperationException("Cannot copy a reference to a CPP object.");
}

std::shared_ptr< dish::iAtomic > dish::ArrayCppReferenceValue::Member(const std::string &member) const
{
    if(IsEqual(member, "length", CASE_INSENSITIVE))
    {
        return IntegerValue::MakeValue(mNumElements);
    }
    
    else if(IsEqual(member, "start", CASE_INSENSITIVE))
    {
        return IntegerValue::MakeValue(0, true);
    }
    
    else if(IsEqual(member, "finish", CASE_INSENSITIVE))
    {
        return IntegerValue::MakeValue(mNumElements - 1);
    }
    
    else if(IsEqual(member, "size", CASE_INSENSITIVE))
    {
        IntegerT tmp(0);
        
        for(IntegerT i(0); i < mNumElements; ++i)
        {
            tmp += Element(i)->Member(member)->AsInteger();
        }
        
        return IntegerValue::MakeValue(tmp);
    }
    
    else if(IsEqual(member, "bytes", CASE_INSENSITIVE))
    {
        IntegerT tmp(0);
        
        for(IntegerT i(0); i < mNumElements; ++i)
        {
            tmp += Element(i)->Member(member)->AsInteger();
        }
    
        return IntegerValue::MakeValue(tmp);
    }
    
    else
    {
        return iAtomic::Member(member);
    }
}

dish::IntegerT dish::ArrayCppReferenceValue::Add(std::shared_ptr< dish::iAtomic > element)
{
    throw IllegalOperationException("Cannot add a value to a reference to a CPP array.");
}

dish::IntegerT dish::ArrayCppReferenceValue::Add(std::shared_ptr< dish::iAtomic > element, const dish::IntegerT &index)
{
    throw IllegalOperationException("Cannot add a value to a reference to a CPP array.");
}

std::shared_ptr< dish::iAtomic > dish::ArrayCppReferenceValue::Element(const dish::IntegerT &index) const
{
    if(index < mNumElements)
    {
        return mType->Declare(reinterpret_cast< uint8_t * >(mValues) + (index * mType->Size()), IsLocked());
    }
    
    std::stringstream message;
    message << "Index out of bounds (";
    message << index;
    message << " >= ";
    message << mNumElements;
    message << ").";
    
    throw IllegalIndexException(message.str());
}

void dish::ArrayCppReferenceValue::Swap(const dish::IntegerT &a, const dish::IntegerT &b)
{
    if(!IsLocked())
    {
        if((a < mNumElements) && (b < mNumElements))
        {
            const IntegerT size(mType->Size());
        
            mType->Swap(
                reinterpret_cast< uint8_t * >(mValues) + (a * size), 
                reinterpret_cast< uint8_t * >(mValues) + (b * size)
            );
        }
        else
        {
            std::stringstream message;
            message << "Index out of bounds (";
            message << ((a < mNumElements) ? b : a);
            message << " >= ";
            message << mNumElements;
            message << ").";
            
            throw IllegalIndexException(message.str());
        }
    }
    else
    {
        throw ValueLockedException("Cannot modify a locked value.");
    }
}

void dish::ArrayCppReferenceValue::Print(std::ostream &out, const std::string::size_type &indent) const
{
    const std::string indentation(indent, static_cast< char >(' '));

    out << indentation;
    out << "[0, ";
    out << mNumElements;
    out << "): ";
    out << std::endl;
    
    out << indentation;
    out << "{";
    out << std::endl;

    bool first(true);
    for(IntegerT i(0); i < mNumElements; ++i)
    {
        Element(i)->Print(out, indent + 4);
        
        if(!first)
        {
            out << ",";
            out << std::endl;
        }
        else
        {
            first = false;
        }
    }
    
    out << indentation;
    out << "}";
}

/******************************************************************************

    dish::IntegerVectorCppReferenceValue class definitions

 ******************************************************************************/

dish::iAtomic::TypeT dish::IntegerVectorCppReferenceValue::Type() const throw()
{
    return iAtomic::typeArray;
}

std::shared_ptr< dish::iAtomic > dish::IntegerVectorCppReferenceValue::Copy() const
{
    throw IllegalOperationException("Cannot copy a reference to a CPP object.");
}

std::shared_ptr< dish::iAtomic > dish::IntegerVectorCppReferenceValue::Member(const std::string &member) const
{
    if(IsEqual(member, "length", CASE_INSENSITIVE))
    {
        return IntegerValue::MakeValue(mValues.size());
    }
    
    else if(IsEqual(member, "start", CASE_INSENSITIVE))
    {
        return IntegerValue::MakeValue(0, true);
    }
    
    else if(IsEqual(member, "finish", CASE_INSENSITIVE))
    {
        return IntegerValue::MakeValue(static_cast< IntegerT >(mValues.size()) - 1);
    }
    
    else if(IsEqual(member, "size", CASE_INSENSITIVE))
    {
        return IntegerValue::MakeValue(mValues.size());
    }
    
    else if(IsEqual(member, "bytes", CASE_INSENSITIVE))
    {
        return IntegerValue::MakeValue(sizeof(VectorT) + (mValues.size() * sizeof(IntegerT)));
    }
    
    else
    {
        return iAtomic::Member(member);
    }
}

dish::IntegerT dish::IntegerVectorCppReferenceValue::Add(std::shared_ptr< dish::iAtomic > element)
{
    assert(element);
    
    const IntegerT size(static_cast< IntegerT >(mValues.size()));
    
    mValues.push_back(element->AsInteger());
    
    return size;
}

dish::IntegerT dish::IntegerVectorCppReferenceValue::Add(std::shared_ptr< dish::iAtomic > element, const dish::IntegerT &index)
{
    assert(element);
    
    const IntegerT size(static_cast< IntegerT >(mValues.size()));
    
    if(index < size)
    {
        mValues.insert(mValues.begin() + index, element->AsInteger());
    }
    else
    {
        mValues.push_back(element->AsInteger());
    }
    
    return size;
}

std::shared_ptr< dish::iAtomic > dish::IntegerVectorCppReferenceValue::Element(const dish::IntegerT &index) const
{
    if(index < static_cast< IntegerT >(mValues.size()))
    {
        return IntegerCppReferenceValue::MakeValue(mValues[index], IsLocked());
    }

    std::stringstream message;
    message << "The specified index, ";
    message << index;
    message << ", does not fall within [0, ";
    message << static_cast< IntegerT >(mValues.size());
    message << ").";
    
    throw IllegalIndexException(message.str());
}

void dish::IntegerVectorCppReferenceValue::Swap(const dish::IntegerT &a, const dish::IntegerT &b)
{
    if(!IsLocked())
    {
        const IntegerT length(static_cast< IntegerT >(mValues.size()));

        if((a >= 0) && (a < length) && (b >= 0) && (b < length))
        {
            if(a != b)
            {
                std::swap(mValues[a], mValues[b]);
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

void dish::IntegerVectorCppReferenceValue::Print(std::ostream &out, const std::string::size_type &indent) const
{
    const std::string indentation(indent, static_cast< char >(' '));

    out << indentation;
    out << "[0, ";
    out << mValues.size();
    out << "): ";
    out << std::endl;
    
    out << indentation;
    out << "{";
    out << std::endl;

    bool first(true);
    std::for_each(
        mValues.begin(), mValues.end(),
        [&](const VectorT::value_type &element)
        {
            out << indent;
            out << "    ";
            out << element;
            
            if(!first)
            {
                out << ",";
                out << std::endl;
            }
            else
            {
                first = false;
            }
        }
    );
    
    out << indentation;
    out << "}";
}

/******************************************************************************

    dish::RealVectorCppReferenceValue class definitions

 ******************************************************************************/

dish::iAtomic::TypeT dish::RealVectorCppReferenceValue::Type() const throw()
{
    return iAtomic::typeArray;
}

std::shared_ptr< dish::iAtomic > dish::RealVectorCppReferenceValue::Copy() const
{
    throw IllegalOperationException("Cannot copy a reference to a CPP object.");
}

std::shared_ptr< dish::iAtomic > dish::RealVectorCppReferenceValue::Member(const std::string &member) const
{
    if(IsEqual(member, "length", CASE_INSENSITIVE))
    {
        return IntegerValue::MakeValue(mValues.size());
    }
    
    else if(IsEqual(member, "start", CASE_INSENSITIVE))
    {
        return IntegerValue::MakeValue(0, true);
    }
    
    else if(IsEqual(member, "finish", CASE_INSENSITIVE))
    {
        return IntegerValue::MakeValue(static_cast< RealT >(mValues.size()) - 1);
    }
    
    else if(IsEqual(member, "size", CASE_INSENSITIVE))
    {
        return IntegerValue::MakeValue(mValues.size());
    }
    
    else if(IsEqual(member, "bytes", CASE_INSENSITIVE))
    {
        return IntegerValue::MakeValue(sizeof(VectorT) + (mValues.size() * sizeof(RealT)));
    }
    
    else
    {
        return iAtomic::Member(member);
    }
}

dish::IntegerT dish::RealVectorCppReferenceValue::Add(std::shared_ptr< dish::iAtomic > element)
{
    assert(element);
    
    const IntegerT size(static_cast< IntegerT >(mValues.size()));
    
    mValues.push_back(element->AsReal());
    
    return size;
}

dish::IntegerT dish::RealVectorCppReferenceValue::Add(std::shared_ptr< dish::iAtomic > element, const dish::IntegerT &index)
{
    assert(element);
    
    const IntegerT size(static_cast< IntegerT >(mValues.size()));
    
    if(index < size)
    {
        mValues.insert(mValues.begin() + index, element->AsReal());
    }
    else
    {
        mValues.push_back(element->AsReal());
    }
    
    return size;
}

std::shared_ptr< dish::iAtomic > dish::RealVectorCppReferenceValue::Element(const dish::IntegerT &index) const
{
    if(index < static_cast< IntegerT >(mValues.size()))
    {
        return RealCppReferenceValue::MakeValue(mValues[index], IsLocked());
    }

    std::stringstream message;
    message << "The specified index, ";
    message << index;
    message << ", does not fall within [0, ";
    message << static_cast< IntegerT >(mValues.size());
    message << ").";
    
    throw IllegalIndexException(message.str());
}

void dish::RealVectorCppReferenceValue::Swap(const dish::IntegerT &a, const dish::IntegerT &b)
{
    if(!IsLocked())
    {
        const IntegerT length(static_cast< IntegerT >(mValues.size()));

        if((a >= 0) && (a < length) && (b >= 0) && (b < length))
        {
            if(a != b)
            {
                std::swap(mValues[a], mValues[b]);
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

void dish::RealVectorCppReferenceValue::Print(std::ostream &out, const std::string::size_type &indent) const
{
    const std::string indentation(indent, static_cast< char >(' '));

    out << indentation;
    out << "[0, ";
    out << mValues.size();
    out << "): ";
    out << std::endl;
    
    out << indentation;
    out << "{";
    out << std::endl;

    bool first(true);
    std::for_each(
        mValues.begin(), mValues.end(),
        [&](const VectorT::value_type &element)
        {
            out << indent;
            out << "    ";
            out << element;
            
            if(!first)
            {
                out << ",";
                out << std::endl;
            }
            else
            {
                first = false;
            }
        }
    );
    
    out << indentation;
    out << "}";
}

/******************************************************************************

    dish::StringVectorCppReferenceValue class definitions

 ******************************************************************************/

dish::iAtomic::TypeT dish::StringVectorCppReferenceValue::Type() const throw()
{
    return iAtomic::typeArray;
}

std::shared_ptr< dish::iAtomic > dish::StringVectorCppReferenceValue::Copy() const
{
    throw IllegalOperationException("Cannot copy a reference to a CPP object.");
}

std::shared_ptr< dish::iAtomic > dish::StringVectorCppReferenceValue::Member(const std::string &member) const
{
    if(IsEqual(member, "length", CASE_INSENSITIVE))
    {
        return IntegerValue::MakeValue(mValues.size());
    }
    
    else if(IsEqual(member, "start", CASE_INSENSITIVE))
    {
        return IntegerValue::MakeValue(0, true);
    }
    
    else if(IsEqual(member, "finish", CASE_INSENSITIVE))
    {
        return IntegerValue::MakeValue(static_cast< RealT >(mValues.size()) - 1);
    }
    
    else if(IsEqual(member, "size", CASE_INSENSITIVE))
    {
        return IntegerValue::MakeValue(mValues.size());
    }
    
    else if(IsEqual(member, "bytes", CASE_INSENSITIVE))
    {
        IntegerT tmp(sizeof(VectorT) + (mValues.size() * sizeof(StringT)));
        
        std::for_each(
            mValues.begin(), mValues.end(),
            [&](const VectorT::value_type &value)
            {
                tmp += (value.length() * sizeof(StringT::value_type));
            }
        );
        
        return IntegerValue::MakeValue(tmp);
    }
    
    else
    {
        return iAtomic::Member(member);
    }
}

dish::IntegerT dish::StringVectorCppReferenceValue::Add(std::shared_ptr< dish::iAtomic > element)
{
    assert(element);
    
    const IntegerT size(static_cast< IntegerT >(mValues.size()));
    
    mValues.push_back(element->AsString());
    
    return size;
}

dish::IntegerT dish::StringVectorCppReferenceValue::Add(std::shared_ptr< dish::iAtomic > element, const dish::IntegerT &index)
{
    assert(element);
    
    const IntegerT size(static_cast< IntegerT >(mValues.size()));
    
    if(index < size)
    {
        mValues.insert(mValues.begin() + index, element->AsString());
    }
    else
    {
        mValues.push_back(element->AsString());
    }
    
    return size;
}

std::shared_ptr< dish::iAtomic > dish::StringVectorCppReferenceValue::Element(const dish::IntegerT &index) const
{
    if(index < static_cast< IntegerT >(mValues.size()))
    {
        return StringCppReferenceValue::MakeValue(mValues[index], IsLocked());
    }

    std::stringstream message;
    message << "The specified index, ";
    message << index;
    message << ", does not fall within [0, ";
    message << static_cast< IntegerT >(mValues.size());
    message << ").";
    
    throw IllegalIndexException(message.str());
}

void dish::StringVectorCppReferenceValue::Swap(const dish::IntegerT &a, const dish::IntegerT &b)
{
    if(!IsLocked())
    {
        const IntegerT length(static_cast< IntegerT >(mValues.size()));

        if((a >= 0) && (a < length) && (b >= 0) && (b < length))
        {
            if(a != b)
            {
                std::swap(mValues[a], mValues[b]);
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

void dish::StringVectorCppReferenceValue::Print(std::ostream &out, const std::string::size_type &indent) const
{
    const std::string indentation(indent, static_cast< char >(' '));

    out << indentation;
    out << "[0, ";
    out << mValues.size();
    out << "): ";
    out << std::endl;
    
    out << indentation;
    out << "{";
    out << std::endl;

    bool first(true);
    std::for_each(
        mValues.begin(), mValues.end(),
        [&](const VectorT::value_type &element)
        {
            out << indent;
            out << "    ";
            out << element;
            
            if(!first)
            {
                out << ",";
                out << std::endl;
            }
            else
            {
                first = false;
            }
        }
    );
    
    out << indentation;
    out << "}";
}

/******************************************************************************

    dish::StructureCppReferenceValue class definitions

 ******************************************************************************/
 
dish::StructureCppReferenceValue::StructureCppReferenceValue(void * const ptr, const bool &locked) : iAtomic(locked),
    mValue(ptr),
    
    mMembers()
{
    assert(nullptr != mValue);
}

void dish::StructureCppReferenceValue::AddMember(const std::string &member, std::shared_ptr< dish::iAtomic > value)
{
    assert(value);
    
    if(mMembers.insert(std::make_pair(member, value)).second)
    {
        return;
    }
    
    std::stringstream message;
    message << "The member '";
    message << member;
    message << "' already exists.";
    
    throw DuplicateSymbolException(message.str());
}

void dish::StructureCppReferenceValue::Lock() throw()
{
    std::for_each(
        mMembers.begin(), mMembers.end(),
        [](MemberSetT::value_type &value)
        {
            value.second->Lock();
        }
    );

    iAtomic::Lock();
}

dish::iAtomic::TypeT dish::StructureCppReferenceValue::Type() const throw()
{
    return iAtomic::typeStructure;
}

std::shared_ptr< dish::iAtomic > dish::StructureCppReferenceValue::Copy() const
{
    throw IllegalOperationException("Cannot copy a reference to a CPP object.");
}

std::shared_ptr< dish::iAtomic > dish::StructureCppReferenceValue::Member(const std::string &member) const
{
    const MemberSetT::const_iterator elem(mMembers.find(member));
    
    if(mMembers.end() != elem)
    {
        return elem->second;
    }
    
    return iAtomic::Member(member);
}

/******************************************************************************

    dish::ExecutableCppValue class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::ExecutableCppValue::call(dish::LanguageSymbolTable &symtab, const std::string &fid, const ArgumentListT &args) const
{
    std::stringstream id;
    id << fid;
    id << "_";
    id << args.size();
    
    std::shared_ptr< dish::iAtomic > function(symtab.Lookup(id.str()));
    const ParamListT &paramlist(function->ParameterList());
    
    if(!args.empty())
    {
        ScopedScope scope(symtab);
    
        auto args_i(args.begin());
        const auto last_args_i(args.end());
    
        auto params_i(paramlist.begin());
        const auto last_params_i(paramlist.end());
    
        while((args_i != last_args_i) && (params_i != last_params_i))
        {
            symtab.Insert(params_i->first, params_i->second ? *args_i : (*args_i)->Clone());
        
            ++args_i;
            ++params_i;
        }
        
        assert(args_i == last_args_i);
        assert(params_i == last_params_i);
        
        return function->Execute(symtab);
    }
    
    return function->Execute(symtab);
}

/******************************************************************************

    dish::DishMachine class definitions

 ******************************************************************************/
 
dish::DishMachine::DishMachine(std::shared_ptr< dish::LanguageSymbolTable > symtab) :
    mSymbolTable(symtab)
{
    assert(mSymbolTable);
}

std::shared_ptr< dish::iAtomic > dish::DishMachine::Call(const std::string &fid, const ArgumentListT &args) const
{
    std::stringstream id;
    id << fid;
    id << "_";
    id << args.size();
    
    std::shared_ptr< dish::iAtomic > function(mSymbolTable->Lookup(id.str()));
    const ExecutableAtomic::ParamListT &paramlist(function->ParameterList());
    
    if(args.size() > 0)
    {
        ScopedScope scope(*mSymbolTable);
    
        auto args_i(args.begin());
        const auto last_args_i(args.end());
    
        auto params_i(paramlist.begin());
        const auto last_params_i(paramlist.end());
    
        while((args_i != last_args_i) && (params_i != last_params_i))
        {
            mSymbolTable->Insert(params_i->first, params_i->second ? *args_i : (*args_i)->Clone());
        
            ++args_i;
            ++params_i;
        }
        
        assert(args_i == last_args_i);
        assert(params_i == last_params_i);
        
        return function->Execute(*mSymbolTable);
    }
    
    return function->Execute(*mSymbolTable);
}

