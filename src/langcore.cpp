/*
    This file is part of the DISH programming language, Copyright 2014, 2015,
    2016 by Chris Buck.
    
    DISH is free software for non-commercial use: you can redistribute it and/or
    modify it provided
    
        (1) The following Copyright notice is displayed at runtime:
    
            DISH programming language copyright (c) 2014-2017 by Chris Buck.
        
        (2) All source files duplicate this copyright statement in full.
        
    Commercial licenses can be negotiated by contacting Chris Buck at
    chrisbuck1220@hotmail.com.

    DISH is distributed in the hope that it will be useful, but WITHOUT ANY 
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS 
    FOR A PARTICULAR PURPOSE.
*/

#include <unistd.h>

#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <memory>

#include "exception.h"
#include "langcore.h"
#include "language.h"
#include "parser.h"
#include "version.h"

/******************************************************************************

    dish::IsEntryPointFunction definitions

 ******************************************************************************/
 
//  This function is defined in main.cpp and queries the Parser to see if it is
//  processing the entry-point of the program.
extern bool IsInputEntryPoint();
 
std::shared_ptr< dish::iAtomic > dish::IsEntryPointFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return BooleanValue::MakeLockedValue(IsInputEntryPoint());
}

/******************************************************************************

    dish::ReleaseCachedParseTreeNodesFunction definitions

 ******************************************************************************/
 
//  This function is defined in main.cpp and releases any cached parse-tree-
//  nodes kept by the parser for reuse.
extern dish::IntegerT ReleaseCachedParseTreeNodes();
 
std::shared_ptr< dish::iAtomic > dish::ReleaseCachedParseTreeNodesFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return IntegerValue::MakeValue(ReleaseCachedParseTreeNodes(), LOCKED);
}

/******************************************************************************

    dish::Language-Version function definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::CreateVersionStructureType()
{
    static std::shared_ptr< StructureTypeAtomic > structure;
    
    if(0 == structure.get())
    {
        std::shared_ptr< IntegerTypeAtomic > integer_type(IntegerTypeAtomic::MakeValue());
        
        structure = StructureTypeAtomic::MakeValue();
        structure->Add("Major", integer_type);
        structure->Add("Minor", integer_type);
        structure->Add("Revision", integer_type);
    }

    return structure;
}

std::shared_ptr< dish::iAtomic > dish::CreateVersionStructure(const dish::IntegerT &major, const dish::IntegerT &minor, const dish::IntegerT &revision, const bool locked)
{
    std::shared_ptr< iAtomic > version(CreateVersionStructureType()->Declare());
    version->Member("Major")->Assign(major);
    version->Member("Minor")->Assign(minor);
    version->Member("Revision")->Assign(revision);
    
    if(locked)
    {
        version->Lock();
    }
    
    return version;
}

/******************************************************************************

    dish::MakeVersionFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::MakeVersionFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return CreateVersionStructure(
        getParam(symtab, "major")->AsInteger(),
        getParam(symtab, "minor")->AsInteger(),
        getParam(symtab, "revision")->AsInteger(),
        false
    );
}

/******************************************************************************

    dish::VersionLessThanFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::VersionLessThanFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > lhs(getParam(symtab, "lhs"));
    std::shared_ptr< iAtomic > rhs(getParam(symtab, "rhs"));
    
    IntegerT lhs_tmp(lhs->Member("Major")->AsInteger());
    IntegerT rhs_tmp(rhs->Member("Major")->AsInteger());
    
    if(lhs_tmp < rhs_tmp)
    {
        return BooleanValue::MakeLockedValue(true);
    }
    
    else if(lhs_tmp == rhs_tmp)
    {
        lhs_tmp = lhs->Member("Minor")->AsInteger();
        rhs_tmp = rhs->Member("Minor")->AsInteger();
        
        if(lhs_tmp < rhs_tmp)
        {
            return BooleanValue::MakeLockedValue(true);
        }
        
        else if(lhs_tmp == rhs_tmp)
        {
            lhs_tmp = lhs->Member("Revision")->AsInteger();
            rhs_tmp = rhs->Member("Revision")->AsInteger();
            
            if(lhs_tmp < rhs_tmp)
            {
                return BooleanValue::MakeLockedValue(true);
            }
        }
    }
    
    return BooleanValue::MakeLockedValue(false);
}

/******************************************************************************

    dish::VersionEqualFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::VersionEqualFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > lhs(getParam(symtab, "lhs"));
    std::shared_ptr< iAtomic > rhs(getParam(symtab, "rhs"));
    
    return BooleanValue::MakeLockedValue(
        (lhs->Member("Major")->AsInteger() == rhs->Member("Major")->AsInteger()) &&
        (lhs->Member("Minor")->AsInteger() == rhs->Member("Minor")->AsInteger()) &&
        (lhs->Member("Revision")->AsInteger() == rhs->Member("Revision")->AsInteger())
    );
}

/******************************************************************************

    dish::VersionAsStringFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::VersionAsStringFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > version(getParam(symtab, "version"));
    
    return StringValue::MakeValue(
        version->Member("Major")->AsString() + "." + 
        version->Member("Minor")->AsString() + "." +
        version->Member("Revision")->AsString(), LOCKED
    );
}

/******************************************************************************

    dish::GetEnvironmentVariableFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::GetEnvironmentVariableFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return dish::StringValue::MakeValue(std::getenv(getParam(symtab, "env")->AsString().c_str()), LOCKED);
}

/******************************************************************************

    dish::TerminateFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::TerminateFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    throw dish::TerminateExecutionException("Program termination.");
}

/******************************************************************************

    dish::SleepFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::SleepFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    dish::IntegerT usec(
        static_cast< dish::IntegerT >(1000000.0 * getParam(symtab, "amt")->AsReal() + 0.5)
    );
    
    while(usec > 0)
    {
        if(usec >= 500000)
        {
            usleep(500000);
            usec -= 500000;
        }
        else
        {
            usleep(usec);
            usec = 0;
        }
    }

    return dish::NullValue::MakeValue();
}

/******************************************************************************

    dish::SystemFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::SystemFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > cmdln(getParam(symtab, "cmdln"));
    
    if(iAtomic::typeArray != cmdln->Type())
    {
        //  If the argument is not an array, assume it is a string command-line.
        return IntegerValue::MakeValue(
            std::system(cmdln->AsString().c_str()), LOCKED
        );
    }
    else
    {
        //  The argument is an array; treat it like an array of command-lines to
        //  be executed and the return codes returned in an array of integers.
        //  First, get the index range of the argument.
        IntegerT start(cmdln->Member("start")->AsInteger());
        const IntegerT finish(cmdln->Member("finish")->AsInteger());
        
        //  Create the result-array.
        std::shared_ptr< dish::iAtomic > results(
            ArrayValue::MakeValue(
                start, finish, IntegerTypeAtomic::MakeValue()
            )
        );
        
        //  Execute each of the command-lines in the array passed as an 
        //  argument.
        for(; start <= finish; ++start)
        {
            //  Execute the command-line.
            results->Element(start)->Assign(
                dish::IntegerValue::MakeValue(
                    std::system(cmdln->Element(start)->AsString().c_str()), 
                    LOCKED
                )
            );
        }
        
        return results;
    }
}

/******************************************************************************

    dish::ExecuteFunction class definitions

 ******************************************************************************/
 
namespace
{

    INLINEC dish::StringT CollectOutputOfExecutedCommand(const dish::StringT &cndln)
    {
        //  Execute the command.
        std::FILE * const input(popen(cndln.c_str(), "r"));
        assert(NULL != input);
        
        //  Collect the output from the command.
        dish::StringT result;
        while(!std::feof(input))
        {
            //  Read the next block from the pipe.
            char buffer[4096] = { '\0' };
            const int nbytes(std::fread(buffer, sizeof(char), 4095, input));
            
            //  Append the block of bytes.
            if(nbytes > 0)
            {
                result.append(buffer, nbytes);
            }
        }
        
        //  Close the command.
        pclose(input);
        
        return result;
    }

}

std::shared_ptr< dish::iAtomic > dish::ExecuteFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > cmdln(getParam(symtab, "cmdln"));
    
    if(iAtomic::typeArray != cmdln->Type())
    {
        //  If the argument is not an array, assume it is a string command-line.
        return StringValue::MakeValue(
            CollectOutputOfExecutedCommand(cmdln->AsString())
        );
    }
    else
    {
        //  The argument is an array; treat it like an array of command-lines to
        //  be executed and the return codes returned in an array of integers.
        //  First, get the index range of the argument.
        IntegerT start(cmdln->Member("start")->AsInteger());
        const IntegerT finish(cmdln->Member("finish")->AsInteger());
        
        //  Create the result-array.
        std::shared_ptr< dish::iAtomic > results(
            ArrayValue::MakeValue(
                start, finish, StringTypeAtomic::MakeValue()
            )
        );
        
        //  Execute each of the command-lines in the array passed as an 
        //  argument.
        for(; start <= finish; ++start)
        {
            //  Execute the command-line.
            results->Element(start)->Assign(
                CollectOutputOfExecutedCommand(
                    cmdln->Element(start)->AsString()
                )
            );
        }
        
        return results;
    }
}

/******************************************************************************

    dish::CopyFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::CopyFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return getParam(symtab, "value")->Copy();
}

/******************************************************************************

    dish::CloneFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::CloneFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return getParam(symtab, "value")->Clone();
}

/******************************************************************************

    dish::AsBooleanFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::AsBooleanFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return dish::BooleanValue::MakeLockedValue(getParam(symtab, "value")->AsBoolean());
}

/******************************************************************************

    dish::AsIntegerFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::AsIntegerFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return dish::IntegerValue::MakeValue(getParam(symtab, "value")->AsInteger(), LOCKED);
}

/******************************************************************************

    dish::AsRealFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::AsRealFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return dish::RealValue::MakeValue(getParam(symtab, "value")->AsReal(), LOCKED);
}

/******************************************************************************

    dish::AsStringFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::AsStringFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return dish::StringValue::MakeValue(getParam(symtab, "value")->AsString(), LOCKED);
}

/******************************************************************************

    dish::AppendFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::AppendFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return dish::IntegerValue::MakeValue(getParam(symtab, "A")->Add(getParam(symtab, "elem")), LOCKED);
}

/******************************************************************************

    dish::InsertFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::InsertFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return dish::IntegerValue::MakeValue(
        getParam(symtab, "A")->Add(getParam(symtab, "elem"), getParam(symtab, "pos")->AsInteger()), LOCKED
    );
}

/******************************************************************************

    dish::CompareLessThanFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::CompareLessThanFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return dish::BooleanValue::MakeValue(*getParam(symtab, "arg1") < *getParam(symtab, "arg2"));
}

/******************************************************************************

    dish::CompareGreaterThanFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::CompareGreaterThanFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return dish::BooleanValue::MakeValue(*getParam(symtab, "arg1") > *getParam(symtab, "arg2"));
}

/******************************************************************************

    dish::CompareEqualFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::CompareEqualFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return dish::BooleanValue::MakeValue(*getParam(symtab, "arg1") == *getParam(symtab, "arg2"));
}

/******************************************************************************

    dish::SortFunction class definitions

 ******************************************************************************/
 
namespace
{

    bool CompareCall(dish::LanguageSymbolTable &symtab, std::shared_ptr< dish::iAtomic > compareF, std::shared_ptr< dish::iAtomic > arg1, std::shared_ptr< dish::iAtomic > arg2)
    {
        const dish::iExecutableAtomic::ParamListT &paramlist(compareF->ParameterList());
        
        auto params_i(paramlist.begin());
        const auto last_params_i(paramlist.end());
        
        {
            dish::ScopedScope scope(symtab);
            
            symtab.Insert(params_i->first, arg1);
            ++params_i;
            
            symtab.Insert(params_i->first, arg2);
            ++params_i;
            
            assert(params_i == last_params_i);
            
            return compareF->Execute(symtab)->AsBoolean();
        }
    }
    
    void quicksort(dish::LanguageSymbolTable &symtab, std::shared_ptr< dish::iAtomic > A, const dish::IntegerT lo, const dish::IntegerT hi, std::shared_ptr< dish::iAtomic > compareF)
    {
        dish::IntegerT i(lo);
        dish::IntegerT j(hi);
        std::shared_ptr< dish::iAtomic > pivot(A->Element((i + j) / 2));
    
        while(i <= j)
        {
            while(CompareCall(symtab, compareF, A->Element(i), pivot))
            {
                ++i;
            }
            
            while(CompareCall(symtab, compareF, pivot, A->Element(j)))
            {
                --j;
            }
            
            if(i <= j)
            {
                A->Swap(i, j);
                
                ++i;
                --j;
            }
        }
        
        if(lo < j)
        {
            quicksort(symtab, A, lo, j, compareF);
        }
        
        if(i <= hi)
        {
            quicksort(symtab, A, i, hi, compareF);
        }
    } 

}

std::shared_ptr< dish::iAtomic > dish::SortFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< dish::iAtomic > A(getParam(symtab, "A"));
    
    quicksort(
        symtab,
        A, 
        A->Member("start")->AsInteger(), 
        A->Member("finish")->AsInteger(),
        getParam(symtab, "compareF")
    );
    
    return dish::NullValue::MakeValue();
}

/******************************************************************************

    dish::SwapFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::SwapFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    getParam(symtab, "A")->Swap(
        getParam(symtab, "index1")->AsInteger(),
        getParam(symtab, "index2")->AsInteger()
    );
    
    return dish::NullValue::MakeValue();
}

/******************************************************************************

    dish::FindFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::FindFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< dish::iAtomic > A(getParam(symtab, "A"));
    std::shared_ptr< dish::iAtomic > elem(getParam(symtab, "elem"));
    std::shared_ptr< dish::iAtomic > compareF(getParam(symtab, "compareF"));
    
    const dish::IntegerT start(A->Member("start")->AsInteger());
    const dish::IntegerT finish(A->Member("finish")->AsInteger());
    
    for(dish::IntegerT i(start); i != finish; ++i)
    {
        if(!CompareCall(symtab, compareF, A->Element(i), elem) && !CompareCall(symtab, compareF, elem, A->Element(i)))
        {
            return dish::IntegerValue::MakeValue(i, LOCKED);
        }
    }
    
    if(!CompareCall(symtab, compareF, A->Element(finish), elem) && !CompareCall(symtab, compareF, elem, A->Element(finish)))
    {
        return dish::IntegerValue::MakeValue(finish, LOCKED);
    }
    
    return dish::IntegerValue::MakeValue(finish + 1, LOCKED);
}

/******************************************************************************

    dish::FindSortedFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::FindSortedFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< dish::iAtomic > A(getParam(symtab, "A"));
    std::shared_ptr< dish::iAtomic > elem(getParam(symtab, "elem"));
    std::shared_ptr< dish::iAtomic > compareF(getParam(symtab, "compareF"));
    
    dish::IntegerT start(A->Member("start")->AsInteger());
    dish::IntegerT finish(A->Member("finish")->AsInteger());
    
    while(start <= finish)
    {
        const dish::IntegerT mid((start + finish) / 2);
        std::shared_ptr< dish::iAtomic > element(A->Element(mid));
        
        if(CompareCall(symtab, compareF, element, elem))
        {
            start = mid + 1;
        }
        
        else if(CompareCall(symtab, compareF, elem, element))
        {
            finish = mid - 1;
        }
        
        else
        {
            return dish::IntegerValue::MakeValue(mid);
        }
    }
    
    return dish::IntegerValue::MakeValue(finish + 1, LOCKED);
}

/******************************************************************************

    dish::IsLockedFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::IsLockedFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return BooleanValue::MakeLockedValue(getParam(symtab, "arg")->IsLocked());
}

/******************************************************************************

    dish::IsNullFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::IsNullFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return BooleanValue::MakeLockedValue(iAtomic::typeNull == getParam(symtab, "value")->Type());
}

/******************************************************************************

    dish::IsTypeFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::IsTypeFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return BooleanValue::MakeLockedValue(iAtomic::typeType == getParam(symtab, "value")->Type());
}

/******************************************************************************

    dish::IsBooleanFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::IsBooleanFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return BooleanValue::MakeLockedValue(iAtomic::typeBoolean == getParam(symtab, "value")->Type());
}

/******************************************************************************

    dish::IsIntegerFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::IsIntegerFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return BooleanValue::MakeLockedValue(iAtomic::typeInteger == getParam(symtab, "value")->Type());
}

/******************************************************************************

    dish::IsRealFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::IsRealFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return BooleanValue::MakeLockedValue(iAtomic::typeReal == getParam(symtab, "value")->Type());
}

/******************************************************************************

    dish::IsStringFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::IsStringFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return BooleanValue::MakeLockedValue(iAtomic::typeString == getParam(symtab, "value")->Type());
}

/******************************************************************************

    dish::IsArrayFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::IsArrayFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return BooleanValue::MakeLockedValue(iAtomic::typeArray == getParam(symtab, "value")->Type());
}

/******************************************************************************

    dish::IsDictionaryFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::IsDictionaryFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return BooleanValue::MakeLockedValue(iAtomic::typeDictionary == getParam(symtab, "value")->Type());
}

/******************************************************************************

    dish::IsStructureFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::IsStructureFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return BooleanValue::MakeLockedValue(iAtomic::typeStructure == getParam(symtab, "value")->Type());
}

/******************************************************************************

    dish::IsFunctionFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::IsFunctionFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return BooleanValue::MakeLockedValue(iAtomic::typeExecutable == getParam(symtab, "value")->Type());
}

/******************************************************************************

    dish::StringAsNumericFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::StringAsNumericFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > strarg(getParam(symtab, "str"));
    const StringT str(strarg->AsString());
    
    StringT::const_iterator i(str.begin());
    const StringT::const_iterator last_i(str.end());
    
    if(i != last_i)
    {
        //  Consume any leading negative sign.
        if('-' == *i)
        {
            ++i;
        }
        
        //  Consume any leading digits
        while((i != last_i) && std::isdigit(*i))
        {
            ++i;
        }
        
        //  If the next character is a '.' we have a potential real-value, so
        //  return it, otherwise we should have an integer-value.
        if('.' == *i)
        {
            return RealValue::MakeValue(strarg->AsReal());
        }
        else
        {
            return IntegerValue::MakeValue(strarg->AsInteger());
        }
    }
    
    std::stringstream message;
    message << "Cannot convert \"";
    message << str;
    message << "\" to a numeric value.";
    
    throw IllegalCastException(message.str());
}

/******************************************************************************

    dish::TypeOfFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::TypeOfFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > expr(getParam(symtab, "expr"));
    const iAtomic::TypeT type(expr->Type());
    
    switch(type)
    {
        case iAtomic::typeNull:
        {
            return NullValue::MakeValue();
        }
        
        case iAtomic::typeType:
        {
            return expr;
        }
        
        case iAtomic::typeBoolean:
        {
            return BooleanTypeAtomic::MakeValue();
        }
        
        case iAtomic::typeInteger:
        {
            return IntegerTypeAtomic::MakeValue();
        }
        
        case iAtomic::typeReal:
        {
            return RealTypeAtomic::MakeValue();
        }
        
        case iAtomic::typeString:
        {
            return StringTypeAtomic::MakeValue();
        }
        
        case iAtomic::typeArray:
        {
            //  Empty - fall-through to the bottom of the method.
        } break;
        
        case iAtomic::typeDictionary:
        {
            return DictionaryTypeAtomic::MakeValue();
        }
        
        case iAtomic::typeStructure:
        {
            //  Empty - fall-through to the bottom of the method.
        } break;
        
        case iAtomic::typeExecutable:
        {
            //  Empty - fall-through to the bottom of the method.
        } break;
        
        default:
        {
            assert(false);
        }
        
    }
    
    std::stringstream message;
    message << "No accessible underlying type for '";
    message << TypeToString(type);
    message << "'.";
    
    throw IllegalTypeException(message.str());
}

/******************************************************************************

    dish::TypeIdFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::TypeIdFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return IntegerValue::MakeValue(
        static_cast< IntegerT >(getParam(symtab, "arg")->Type()), LOCKED
    );
}

/******************************************************************************

    dish::MinimumFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::MinimumFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > A(getParam(symtab, "A"));
    
    if(A->Member("length")->AsInteger() > 0)
    {
        IntegerT i(A->Member("start")->AsInteger());
        const IntegerT last_i(A->Member("finish")->AsInteger());
        
        std::shared_ptr< iAtomic > minimum(A->Element(i));
        for(++i; i <= last_i; ++i)
        {
            std::shared_ptr< iAtomic > tmp(A->Element(i));
            
            if(*tmp < *minimum)
            {
                minimum = tmp;
            }
        }
        
        return minimum;
    }

    return NullValue::MakeValue();
}

/******************************************************************************

    dish::Minimum2Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::Minimum2Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< dish::iAtomic > x(getParam(symtab, "x"));
    std::shared_ptr< dish::iAtomic > y(getParam(symtab, "y"));

    return ((*x <= *y) ? x : y);
}

/******************************************************************************

    dish::Minimum3Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::Minimum3Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< dish::iAtomic > x(getParam(symtab, "x"));
    std::shared_ptr< dish::iAtomic > y(getParam(symtab, "y"));
    std::shared_ptr< dish::iAtomic > z(getParam(symtab, "z"));

    return ((*x <= *y) ? ((*x <= *z) ? x : z) : ((*y <= *z) ? y : z));
}

/******************************************************************************

    dish::MaximumFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::MaximumFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > A(getParam(symtab, "A"));
    
    if(A->Member("length")->AsInteger() > 0)
    {
        IntegerT i(A->Member("start")->AsInteger());
        const IntegerT last_i(A->Member("finish")->AsInteger());
        
        std::shared_ptr< iAtomic > maximum(A->Element(i));
        for(++i; i <= last_i; ++i)
        {
            std::shared_ptr< iAtomic > tmp(A->Element(i));
            
            if(*tmp > *maximum)
            {
                maximum = tmp;
            }
        }
        
        return maximum;
    }

    return NullValue::MakeValue();
}

/******************************************************************************

    dish::Maximum2Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::Maximum2Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< dish::iAtomic > x(getParam(symtab, "x"));
    std::shared_ptr< dish::iAtomic > y(getParam(symtab, "y"));

    return ((*x >= *y) ? x : y);
}

/******************************************************************************

    dish::Maximum3Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::Maximum3Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< dish::iAtomic > x(getParam(symtab, "x"));
    std::shared_ptr< dish::iAtomic > y(getParam(symtab, "y"));
    std::shared_ptr< dish::iAtomic > z(getParam(symtab, "z"));

    return ((*x >= *y) ? ((*x >= *z) ? x : z) : ((*y >= *z) ? y : z));
}

/******************************************************************************

    dish::IncFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::IncFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > x(getParam(symtab, "x"));

    switch(x->Type())
    {
        case typeBoolean:
        case typeInteger:
        {
            const IntegerT value(x->AsInteger() + 1);
            x->Assign(value);
        } break;
        
        case typeReal:
        case typeString:
        {
            const RealT value(x->AsReal() + static_cast< RealT >(1.0));
            x->Assign(value);
        } break;
        
        case typeArray:
        {
            const IntegerT start(x->Member("start")->AsInteger());
            const IntegerT finish(x->Member("finish")->AsInteger());
            
            for(IntegerT i(start); i <= finish; ++i)
            {
                std::shared_ptr< iAtomic > arg(x->Element(i));
                
                switch(arg->Type())
                {
                    case typeBoolean:
                    case typeInteger:
                    {
                        arg->Assign(arg->AsInteger() + 1);
                    } break;
                    
                    case typeReal:
                    case typeString:
                    {
                        arg->Assign(arg->AsReal() + static_cast< RealT >(1.0));
                    } break;
                    
                    default:
                    {
                        throw IllegalCastException("Cannot cast to a numeric value for function call 'Inc'.");
                    }
                    
                }
            }
        } break;
        
        default:
        {
            throw IllegalCastException("Cannot cast to a numeric value for function call 'Inc'.");
        }
        
    }
    
    return x;
}

/******************************************************************************

    dish::Inc2Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Inc2Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > x(getParam(symtab, "x"));

    switch(x->Type())
    {
        case typeBoolean:
        case typeInteger:
        {
            x->Assign(x->AsInteger() + getParam(symtab, "amt")->AsInteger());
        } break;
        
        case typeReal:
        case typeString:
        {
            x->Assign(x->AsReal() + getParam(symtab, "amt")->AsReal());
        } break;
        
        case typeArray:
        {
            const IntegerT start(x->Member("start")->AsInteger());
            const IntegerT finish(x->Member("finish")->AsInteger());
            
            std::shared_ptr< iAtomic > amt(getParam(symtab, "amt"));
            const IntegerT intamt(amt->AsInteger());
            const RealT realamt(amt->AsReal());
            
            for(IntegerT i(start); i <= finish; ++i)
            {
                std::shared_ptr< iAtomic > arg(x->Element(i));
                
                switch(arg->Type())
                {
                    case typeBoolean:
                    case typeInteger:
                    {
                        arg->Assign(arg->AsInteger() + intamt);
                    } break;
                    
                    case typeReal:
                    case typeString:
                    {
                        arg->Assign(arg->AsReal() + realamt);
                    } break;
                    
                    default:
                    {
                        throw IllegalCastException("Cannot cast to a numeric value for function call 'Inc'.");
                    }
                    
                }
            }
        } break;
        
        default:
        {
            throw IllegalCastException("Cannot cast to a numeric value for function call 'Inc'.");
        }
        
    }
    
    return x;
}

/******************************************************************************

    dish::DecFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::DecFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > x(getParam(symtab, "x"));

    switch(x->Type())
    {
        case typeBoolean:
        case typeInteger:
        {
            const IntegerT value(x->AsInteger() - 1);
            x->Assign(value);
        } break;
        
        case typeReal:
        case typeString:
        {
            const RealT value(x->AsReal() - static_cast< RealT >(1.0));
            x->Assign(value);
        } break;
        
        case typeArray:
        {
            const IntegerT start(x->Member("start")->AsInteger());
            const IntegerT finish(x->Member("finish")->AsInteger());
            
            for(IntegerT i(start); i <= finish; ++i)
            {
                std::shared_ptr< iAtomic > arg(x->Element(i));
                
                switch(arg->Type())
                {
                    case typeBoolean:
                    case typeInteger:
                    {
                        arg->Assign(arg->AsInteger() - 1);
                    } break;
                    
                    case typeReal:
                    case typeString:
                    {
                        arg->Assign(arg->AsReal() - static_cast< RealT >(1.0));
                    } break;
                    
                    default:
                    {
                        throw IllegalCastException("Cannot cast to a numeric value for function call 'Dec'.");
                    }
                    
                }
            }
        } break;
        
        default:
        {
            throw IllegalCastException("Cannot cast to a numeric value for function call 'Dec'.");
        }
        
    }
    
    return x;
}

/******************************************************************************

    dish::Dec2Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Dec2Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > x(getParam(symtab, "x"));

    switch(x->Type())
    {
        case typeBoolean:
        case typeInteger:
        {
            x->Assign(x->AsInteger() - getParam(symtab, "amt")->AsInteger());
        } break;
        
        case typeReal:
        case typeString:
        {
            x->Assign(x->AsReal() - getParam(symtab, "amt")->AsReal());
        } break;
        
        case typeArray:
        {
            const IntegerT start(x->Member("start")->AsInteger());
            const IntegerT finish(x->Member("finish")->AsInteger());
            
            std::shared_ptr< iAtomic > amt(getParam(symtab, "amt"));
            const IntegerT intamt(amt->AsInteger());
            const RealT realamt(amt->AsReal());
            
            for(IntegerT i(start); i <= finish; ++i)
            {
                std::shared_ptr< iAtomic > arg(x->Element(i));
                
                switch(arg->Type())
                {
                    case typeBoolean:
                    case typeInteger:
                    {
                        arg->Assign(arg->AsInteger() - intamt);
                    } break;
                    
                    case typeReal:
                    case typeString:
                    {
                        arg->Assign(arg->AsReal() - realamt);
                    } break;
                    
                    default:
                    {
                        throw IllegalCastException("Cannot cast to a numeric value for function call 'Dec'.");
                    }
                    
                }
            }
        } break;
        
        default:
        {
            throw IllegalCastException("Cannot cast to a numeric value for function call 'Dec'.");
        }
        
    }
    
    return x;
}

////////////////////////////////////////////////////////////////////////////////

namespace
{

    const dish::ErrorCallbacks::ErrTypeT ErrorTypeValues[dish::ErrorCallbacks::ERR_NUM] =
    {
        dish::ErrorCallbacks::ERR_Null,
                
        dish::ErrorCallbacks::ERR_Ok,

        dish::ErrorCallbacks::ERR_Terminate,
        
        dish::ErrorCallbacks::ERR_IllegalCast,
        dish::ErrorCallbacks::ERR_ValueLocked,
        dish::ErrorCallbacks::ERR_NoSuchMember,
        dish::ErrorCallbacks::ERR_DuplicateSymbol,
        dish::ErrorCallbacks::ERR_NoSuchSymbol,
        dish::ErrorCallbacks::ERR_DivideByZero,
        dish::ErrorCallbacks::ERR_DomainError,
        dish::ErrorCallbacks::ERR_RangeError,
        
        dish::ErrorCallbacks::ERR_IllegalHandle,
        dish::ErrorCallbacks::ERR_IllegalValue,
                
        dish::ErrorCallbacks::ERR_StackOverflowError,

#ifdef LANG_LIB_FILEIO
        dish::ErrorCallbacks::ERR_TooManyOpenFiles,
        dish::ErrorCallbacks::ERR_UnableToOpenFile,
        dish::ErrorCallbacks::ERR_FileNotOpen,
        dish::ErrorCallbacks::ERR_FileWriteError,
        dish::ErrorCallbacks::ERR_FileReadError,
        dish::ErrorCallbacks::ERR_FileReadEndOfFile,
#endif

#ifdef LANG_LIB_NETWORK        
        dish::ErrorCallbacks::ERR_TooManyOpenSockets,
        dish::ErrorCallbacks::ERR_UnableToOpenSocket,
        dish::ErrorCallbacks::ERR_UnableToCloseSocket,
        dish::ErrorCallbacks::ERR_NetworkInvalidAddress,
        dish::ErrorCallbacks::ERR_NetworkUnableToConnectToServer,
        dish::ErrorCallbacks::ERR_NetworkSocketNotOpen,
        dish::ErrorCallbacks::ERR_NetworkSocketWriteError,
        dish::ErrorCallbacks::ERR_NetworkSocketReadError,
#endif
        
#ifdef LANG_LIB_MATH_MATRIX
        dish::ErrorCallbacks::ERR_MatrixInvalidError,
        dish::ErrorCallbacks::ERR_MatrixNotSquareError,
        dish::ErrorCallbacks::ERR_ZeroDeterminantError,
        dish::ErrorCallbacks::ERR_MatrixDimensionError,
#endif
    
#ifdef LANG_LIB_DATABASE
        dish::ErrorCallbacks::ERR_DB_InvalidConnectionType,
        dish::ErrorCallbacks::ERR_DB_TooManyOpenConnections,
        dish::ErrorCallbacks::ERR_DB_UnableToOpenConnection,
        dish::ErrorCallbacks::ERR_DB_ConnectionNotOpen,
        dish::ErrorCallbacks::ERR_DB_ConnectionDropped,
        dish::ErrorCallbacks::ERR_DB_QueryError,
        dish::ErrorCallbacks::ERR_DB_InternalError,
#endif

#ifdef LANG_LIB_RS232
        dish::ErrorCallbacks::ERR_RS232_ConfigurationNotSupported,
        dish::ErrorCallbacks::ERR_RS232_UnableToOpenPort,
        dish::ErrorCallbacks::ERR_RS232_PortNotOpen,
        dish::ErrorCallbacks::ERR_RS232_WriteFailure,
        dish::ErrorCallbacks::ERR_RS232_ReadFailure,
#endif
    };

    INLINEC dish::ErrorCallbacks::ErrTypeT IntegerToErrType(const dish::IntegerT &arg)
    {
        const bool valid(
            (static_cast< dish::IntegerT >(dish::ErrorCallbacks::ERR_Null) <= arg) && (arg < static_cast< dish::IntegerT >(dish::ErrorCallbacks::ERR_NUM))
        );
    
        return (valid ? ErrorTypeValues[arg] : dish::ErrorCallbacks::ERR_Null);
    }

}

/******************************************************************************

    dish::OnErrorPushFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::OnErrorPushFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    dish::ErrorCallbacks::Instance().Push(
        IntegerToErrType(getParam(symtab, "index")->AsInteger()),
        getParam(symtab, "call")
    );

    return dish::NullValue::MakeValue();
}

/******************************************************************************

    dish::OnErrorInvokeFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::OnErrorInvokeFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return dish::BooleanValue::MakeLockedValue(
        dish::ErrorCallbacks::Instance().Invoke(
            IntegerToErrType(getParam(symtab, "index")->AsInteger()),
            dish::ErrorCallbacks::CallbackArgT(),
            symtab
        )
    );
}

/******************************************************************************

    dish::OnErrorPopFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::OnErrorPopFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    dish::ErrorCallbacks::Instance().Pop(
        IntegerToErrType(getParam(symtab, "index")->AsInteger())
    );
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::SymbolOfFunctionFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::SymbolOfFunctionFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return symtab.Lookup(
        getParam(symtab, "funcname")->AsString() + 
        "_" + 
        getParam(symtab, "nparams")->AsString()     //  This parameter should be an integer but we need it as a string to build the identifier.
    );
}

/******************************************************************************

    dish::SymbolExistsFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::SymbolExistsFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return dish::BooleanValue::MakeValue(symtab.Exists(getParam(symtab, "id")->AsString()));
}

/******************************************************************************

    dish::IsExactlyEqualFunction class definitions

 ******************************************************************************/
 
namespace
{

    bool isExactlyEqual(std::shared_ptr< dish::iAtomic > lhs, std::shared_ptr< dish::iAtomic > rhs)
    {
        const dish::iAtomic::TypeT type(lhs->Type());
        if(type == rhs->Type())
        {
            switch(type)
            {
                case dish::iAtomic::typeNull:
                {
                    return true;
                }
                
                case dish::iAtomic::typeType:
                {
                    return false;
                }
                
                case dish::iAtomic::typeBoolean:
                {
                    return (lhs->AsBoolean() == rhs->AsBoolean());
                }
                
                case dish::iAtomic::typeInteger:
                {
                    return (lhs->AsInteger() == rhs->AsInteger());
                }
                
                case dish::iAtomic::typeReal:
                {
                    return (lhs->AsReal() == rhs->AsReal());
                }
                
                case dish::iAtomic::typeString:
                {
                    return dish::IsEqual(lhs->AsString(), rhs->AsString(), dish::CASE_SENSITIVE);
                }
                
                case dish::iAtomic::typeArray:
                {
                    const dish::IntegerT finish(lhs->Member("finish")->AsInteger());
                    if(finish == rhs->Member("finish")->AsInteger())
                    {
                        dish::IntegerT start(lhs->Member("start")->AsInteger());
                        if(start == rhs->Member("start")->AsInteger())
                        {
                            while(start <= finish)
                            {
                                if(isExactlyEqual(lhs->Element(start), rhs->Element(start)))
                                {
                                    ++start;
                                }
                                else
                                {
                                    return false;
                                }
                            }
                            
                            return true;
                        }
                    }
                } break;
                
                case dish::iAtomic::typeDictionary:
                {
                    std::shared_ptr< dish::iAtomic > lhs_keys(lhs->Keys());
                    const dish::IntegerT keys_finish(lhs_keys->Member("finish")->AsInteger());
                    
                    std::shared_ptr< dish::iAtomic > rhs_keys(rhs->Keys());
                    
                    if(keys_finish == rhs_keys->Member("finish")->AsInteger())
                    {
                        dish::IntegerT keys_start(lhs_keys->Member("start")->AsInteger());
                        if(keys_start == rhs_keys->Member("start")->AsInteger())
                        {
                            while(keys_start <= keys_finish)
                            {
                                const dish::StringT key(lhs_keys->Element(keys_start)->AsString());
                                if(dish::IsEqual(key, rhs_keys->Element(keys_start)->AsString(), dish::CASE_SENSITIVE))
                                {
                                    if(isExactlyEqual(rhs->Lookup(key), lhs->Lookup(key)))
                                    {
                                        ++keys_start;
                                    }
                                    else
                                    {
                                        return false;
                                    }
                                }
                                else
                                {
                                    return false;
                                }
                            }
                            
                            return true;
                        }
                    }
                } break;
                
                case dish::iAtomic::typeStructure:
                {
                    dish::iStructureAtomic::MemberNameSetT lhs_members;
                    lhs->Members(lhs_members);
                    
                    dish::iStructureAtomic::MemberNameSetT rhs_members;
                    rhs->Members(rhs_members);
                    
                    if(lhs_members.size() == rhs_members.size())
                    {
                        std::sort(lhs_members.begin(), lhs_members.end());
                        std::sort(rhs_members.begin(), rhs_members.end());
                        
                        dish::iStructureAtomic::MemberNameSetT::const_iterator lhs_i(lhs_members.begin());
                        const dish::iStructureAtomic::MemberNameSetT::const_iterator lhs_last_i(lhs_members.end());
                        
                        dish::iStructureAtomic::MemberNameSetT::const_iterator rhs_i(rhs_members.begin());
                        const dish::iStructureAtomic::MemberNameSetT::const_iterator rhs_last_i(rhs_members.end());
                        
                        while((lhs_i != lhs_last_i) && (rhs_i != rhs_last_i))
                        {
                            if(dish::IsEqual(*lhs_i, *rhs_i, dish::CASE_SENSITIVE))
                            {
                                if(isExactlyEqual(lhs->Member(*lhs_i), rhs->Member(*rhs_i)))
                                {
                                    ++lhs_i;
                                    ++rhs_i;
                                }
                                else
                                {
                                    return false;
                                }
                            }
                            else
                            {
                                return false;
                            }
                        }
                        assert(lhs_i == lhs_last_i);
                        assert(rhs_i == rhs_last_i);
                        
                        return true;
                    }
                    
                    return false;
                }
                
                case dish::iAtomic::typeExecutable:
                {
                    return false;
                }
                
                default:
                {
                    assert(false);
                }
                
            }
        }
        
        return false;
    }

}

std::shared_ptr< dish::iAtomic > dish::IsExactlyEqualFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return BooleanValue::MakeLockedValue(
        isExactlyEqual(getParam(symtab, "lhs"), getParam(symtab, "rhs"))
    );
}

