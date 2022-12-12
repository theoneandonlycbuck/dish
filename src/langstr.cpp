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

#include <algorithm>
#include <cctype>
#include <sstream>
#include <string>

#include "exception.h"
#include "langstr.h"
#include "utility.h"

namespace
{

    dish::StringT IntegerToBaseString(const dish::IntegerT num, const dish::StringT &chars)
    {
        if(0 != num)
        {
            uint64_t tmp(static_cast< unsigned dish::IntegerT >(num));
        
            const dish::IntegerT base(chars.length());
            if(base > 1)
            {
                dish::StringT str;
                
                while(0 != tmp)
                {
                    str += dish::StringT(1, chars[tmp % base]);
                    tmp /= base;
                }
                
                return dish::StringT(str.rbegin(), str.rend());
            }
            
            throw dish::DomainErrorException("The conversion base implied by the <chars> argument is invalid in a call to BaseStringToInteger(<str>, <chars>).");
        }
        
        return "0";
    }

    dish::IntegerT BaseStringToInteger(const dish::StringT &str, const dish::StringT &chars)
    {
        const dish::IntegerT base(static_cast< dish::IntegerT >(chars.length()));
        assert(base > 0);
        
        dish::StringT::const_iterator i(str.begin());
        const dish::StringT::const_iterator last_i(str.end());
        
        bool positive(true);
        if('-' == *i)
        {
            if(10 == base)
            {
                positive = false;
                ++i;
            }
            else
            {
                throw dish::DomainErrorException("A '-' sign can only preceed a decimal value in a call to BaseStringToInteger(<str>, <chars>).");
            }
        }
        
        dish::IntegerT value(0);
        while(i != last_i)
        {
            const dish::StringT::size_type digit(chars.find(*i));
            
            if(std::string::npos != digit)
            {
                value *= base;
                value += digit;
                
                ++i;
            }
            else
            {
                throw dish::DomainErrorException("The value passed to BaseStringToInteger(<str>, <chars>) contains digits not contained in <chars>.");
            }
        }
        
        return (positive ? value : -value);
    }

}

/******************************************************************************

    Global definitions

 ******************************************************************************/
 
const dish::IntegerT dish::STRINVALID(-1);

const dish::BooleanT dish::STRSINGLE(true);
const dish::BooleanT dish::STRMULTIPLE(false);

const dish::StringT dish::STR_BINARY_DIGITS("01");
const dish::StringT dish::STR_OCTAL_DIGITS("01234567");
const dish::StringT dish::STR_DECIMAL_DIGITS("0123456789");
const dish::StringT dish::STR_HEXADECIMAL_DIGITS("0123456789ABCDEF");

/******************************************************************************

    dish::OrdFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::OrdFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const std::string str(getParam(symtab, "str")->AsString());
    
    return IntegerValue::MakeValue(!str.empty() ? str[0] : 0);
}

/******************************************************************************

    dish::Ord2Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Ord2Function::Execute(dish::LanguageSymbolTable &symtab) const
{    
    const StringT str(getParam(symtab, "str")->AsString());
    const StringT::size_type strlen(str.length());
    
    std::shared_ptr< iAtomic > array;
    if(!getParam(symtab, "single")->AsBoolean())
    {
        //  Create the array of integers for all of the characters in the
        //  string, including the null-character: \0.
        array = ArrayValue::MakeValue(0, strlen + 1, IntegerTypeAtomic::MakeValue());
    
        //  Populate the array.
        for(StringT::size_type i(0); i < strlen; ++i)
        {
            array->Element(i)->Assign(
                IntegerValue::MakeValue(str[i])
            );
        }
        array->Element(strlen)->Assign(IntegerValue::MakeValue('\0'));
    }
    else
    {
        //  Create the array of integers that will contain the ordinal value of
        //  the single leading character from the string. If the string's length
        //  is zero then the array will contain the ordinal value of the
        //  string's terminating null-character, \0.
        array = ArrayValue::MakeValue(0, 1, IntegerTypeAtomic::MakeValue());

        //  Populate the array.
        array->Element(0)->Assign(
            IntegerValue::MakeValue((strlen > 0) ? str[0] : 0)
        );
    }
    
    assert(array);
    return array;
}

/******************************************************************************

    dish::ChrFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::ChrFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return StringValue::MakeValue(StringT(1, getParam(symtab, "ch")->AsInteger()));
}

/******************************************************************************

    dish::Chr2Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Chr2Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > array(getParam(symtab, "array"));
    
    StringT str;
    if(!getParam(symtab, "single")->AsBoolean())
    {
        IntegerT i(array->Member("start")->AsInteger());
        const IntegerT last_i(array->Member("finish")->AsInteger());
    
        for(bool done(false); (!done) && (i <= last_i); ++i)
        {
            const IntegerT ch(array->Element(i)->AsInteger());
        
            if(0 != ch)
            {
                str.append(1, static_cast< char >(ch));
            }
            else
            {
                done = true;
            }
        }
    }
    else
    {
        const IntegerT ch(array->Element(array->Member("start")->AsInteger())->AsInteger());
    
        if(0 != ch)
        {
            str.append(1, static_cast< char >(ch));
        }
    }
    
    return StringValue::MakeValue(str);
}

/******************************************************************************

    dish::IntegerToBaseStringFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::IntegerToBaseStringFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return StringValue::MakeValue(
        IntegerToBaseString(
            getParam(symtab, "num")->AsInteger(),
            getParam(symtab, "chars")->AsString()
        )
    );
}

/******************************************************************************

    dish::BaseStringToIntegerFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::BaseStringToIntegerFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return IntegerValue::MakeValue(
        BaseStringToInteger(
            getParam(symtab, "str")->AsString(),
            getParam(symtab, "chars")->AsString()
        )
    );
}

/******************************************************************************

    dish::ToUpperCaseFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::ToUpperCaseFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > arg(getParam(symtab, "arg"));

    switch(arg->Type())
    {
        case iAtomic::typeInteger:
        {
            return IntegerValue::MakeValue(static_cast< IntegerT >(std::toupper(arg->AsInteger())));
        }
        
        case iAtomic::typeString:
        {
            StringT str(arg->AsString());
            
            std::for_each(
                str.begin(), str.end(),
                [](StringT::value_type &ch)
                {
                    ch = std::toupper(ch);
                }
            );
            
            return StringValue::MakeValue(str);
        }
        
        default:
        {
            //  Empty
        }
        
    }
    
    std::stringstream message;
    message << "Cannot convert a ";
    message << arg->Type();
    message << " to upper case.";
    
    throw IllegalCastException(message.str());
}

/******************************************************************************

    dish::ToLowerCaseFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::ToLowerCaseFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > arg(getParam(symtab, "arg"));

    switch(arg->Type())
    {
        case iAtomic::typeInteger:
        {
            return IntegerValue::MakeValue(static_cast< IntegerT >(std::tolower(arg->AsInteger())));
        }
        
        case iAtomic::typeString:
        {
            StringT str(arg->AsString());
            
            std::for_each(
                str.begin(), str.end(),
                [](StringT::value_type &ch)
                {
                    ch = std::tolower(ch);
                }
            );
            
            return StringValue::MakeValue(str);
        }
        
        default:
        {
            //  Empty
        }
        
    }
    
    std::stringstream message;
    message << "Cannot convert a ";
    message << arg->Type();
    message << " to lower case.";
    
    throw IllegalCastException(message.str());
}

/******************************************************************************

    dish::IsUpperCaseFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::IsUpperCaseFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > arg(getParam(symtab, "arg"));

    switch(arg->Type())
    {
        case iAtomic::typeInteger:
        {
            return BooleanValue::MakeLockedValue(std::isupper(arg->AsInteger()));
        }
        
        case iAtomic::typeString:
        {
            std::string str(arg->AsString());
            
            for(std::string::const_iterator i(str.begin()), last_i(str.end()); i != last_i; ++i)
            {
                if(std::isalpha(*i) && !std::isupper(*i))
                {
                    return BooleanValue::MakeLockedValue(false);
                }
            }
            
            return BooleanValue::MakeLockedValue(true);
        }
        
        default:
        {
            //  Empty
        }
        
    }
    
    std::stringstream message;
    message << "Cannot determine if a ";
    message << arg->Type();
    message << " can be upper case.";
    
    throw IllegalCastException(message.str());
}

/******************************************************************************

    dish::IsLowerCaseFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::IsLowerCaseFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > arg(getParam(symtab, "arg"));

    switch(arg->Type())
    {
        case iAtomic::typeInteger:
        {
            return BooleanValue::MakeLockedValue(std::islower(arg->AsInteger()));
        }
        
        case iAtomic::typeString:
        {
            const std::string str(arg->AsString());
            
            for(std::string::const_iterator i(str.begin()), last_i(str.end()); i != last_i; ++i)
            {
                if(std::isalpha(*i) && !std::islower(*i))
                {
                    return BooleanValue::MakeLockedValue(false);
                }
            }
            
            return BooleanValue::MakeLockedValue(true);
        }
        
        default:
        {
            //  Empty
        }
        
    }
    
    std::stringstream message;
    message << "Cannot determine if a ";
    message << arg->Type();
    message << " can be lower case.";
    
    throw IllegalCastException(message.str());
}

/******************************************************************************

    dish::IsControlFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::IsControlFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > arg(getParam(symtab, "arg"));

    switch(arg->Type())
    {
        case iAtomic::typeInteger:
        {
            return BooleanValue::MakeLockedValue(std::iscntrl(arg->AsInteger()));
        }
        
        case iAtomic::typeString:
        {
            const std::string str(arg->AsString());
            
            for(std::string::const_iterator i(str.begin()), last_i(str.end()); i != last_i; ++i)
            {
                if(!std::iscntrl(*i))
                {
                    return BooleanValue::MakeLockedValue(false);
                }
            }
            
            return BooleanValue::MakeLockedValue(true);
        }
        
        default:
        {
            //  Empty
        }
        
    }
    
    std::stringstream message;
    message << "Cannot convert a ";
    message << arg->Type();
    message << " to a string.";
    
    throw IllegalCastException(message.str());
}

/******************************************************************************

    dish::IsPrintableFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::IsPrintableFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > arg(getParam(symtab, "arg"));

    switch(arg->Type())
    {
        case iAtomic::typeInteger:
        {
            return BooleanValue::MakeLockedValue(std::isprint(arg->AsInteger()));
        }
        
        case iAtomic::typeString:
        {
            const std::string str(arg->AsString());
            
            for(std::string::const_iterator i(str.begin()), last_i(str.end()); i != last_i; ++i)
            {
                if(!std::isprint(*i))
                {
                    return BooleanValue::MakeLockedValue(false);
                }
            }
            
            return BooleanValue::MakeLockedValue(true);
        }
        
        default:
        {
            //  Empty
        }
        
    }
    
    std::stringstream message;
    message << "Cannot convert a ";
    message << arg->Type();
    message << " to a string.";
    
    throw IllegalCastException(message.str());
}

/******************************************************************************

    dish::IsWhitespaceFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::IsWhitespaceFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > arg(getParam(symtab, "arg"));

    switch(arg->Type())
    {
        case iAtomic::typeInteger:
        {
            return BooleanValue::MakeLockedValue(std::isspace(arg->AsInteger()));
        }
        
        case iAtomic::typeString:
        {
            const std::string str(arg->AsString());
            
            for(std::string::const_iterator i(str.begin()), last_i(str.end()); i != last_i; ++i)
            {
                if(!std::isspace(*i))
                {
                    return BooleanValue::MakeLockedValue(false);
                }
            }
            
            return BooleanValue::MakeLockedValue(true);
        }
        
        default:
        {
            //  Empty
        }
        
    }
    
    std::stringstream message;
    message << "Cannot convert a ";
    message << arg->Type();
    message << " to a string.";
    
    throw IllegalCastException(message.str());
}

/******************************************************************************

    dish::IsPunctuationFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::IsPunctuationFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > arg(getParam(symtab, "arg"));

    switch(arg->Type())
    {
        case iAtomic::typeInteger:
        {
            return BooleanValue::MakeLockedValue(std::ispunct(arg->AsInteger()));
        }
        
        case iAtomic::typeString:
        {
            const std::string str(arg->AsString());
            
            for(std::string::const_iterator i(str.begin()), last_i(str.end()); i != last_i; ++i)
            {
                if(!std::ispunct(*i))
                {
                    return BooleanValue::MakeLockedValue(false);
                }
            }
            
            return BooleanValue::MakeLockedValue(true);
        }
        
        default:
        {
            //  Empty
        }
        
    }
    
    std::stringstream message;
    message << "Cannot convert a ";
    message << arg->Type();
    message << " to a string.";
    
    throw IllegalCastException(message.str());
}

/******************************************************************************

    dish::IsLetterFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::IsLetterFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > arg(getParam(symtab, "arg"));

    switch(arg->Type())
    {
        case iAtomic::typeInteger:
        {
            return BooleanValue::MakeLockedValue(std::isalpha(arg->AsInteger()));
        }
        
        case iAtomic::typeString:
        {
            const std::string str(arg->AsString());
            
            for(std::string::const_iterator i(str.begin()), last_i(str.end()); i != last_i; ++i)
            {
                if(!std::isalpha(*i))
                {
                    return BooleanValue::MakeLockedValue(false);
                }
            }
            
            return BooleanValue::MakeLockedValue(true);
        }
        
        default:
        {
            //  Empty
        }
        
    }
    
    std::stringstream message;
    message << "Cannot convert a ";
    message << arg->Type();
    message << " to a string.";
    
    throw IllegalCastException(message.str());
}

/******************************************************************************

    dish::IsDigitFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::IsDigitFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > arg(getParam(symtab, "arg"));

    switch(arg->Type())
    {
        case iAtomic::typeInteger:
        {
            return BooleanValue::MakeLockedValue(std::isdigit(arg->AsInteger()));
        }
        
        case iAtomic::typeString:
        {
            const std::string str(arg->AsString());
            
            for(std::string::const_iterator i(str.begin()), last_i(str.end()); i != last_i; ++i)
            {
                if(!std::isdigit(*i))
                {
                    return BooleanValue::MakeLockedValue(false);
                }
            }
            
            return BooleanValue::MakeLockedValue(true);
        }
        
        default:
        {
            //  Empty
        }
        
    }
    
    std::stringstream message;
    message << "Cannot convert a ";
    message << arg->Type();
    message << " to a string.";
    
    throw IllegalCastException(message.str());
}

/******************************************************************************

    dish::IsHexDigitFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::IsHexDigitFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > arg(getParam(symtab, "arg"));

    switch(arg->Type())
    {
        case iAtomic::typeInteger:
        {
            return BooleanValue::MakeLockedValue(std::isxdigit(arg->AsInteger()));
        }
        
        case iAtomic::typeString:
        {
            const std::string str(arg->AsString());
            
            for(std::string::const_iterator i(str.begin()), last_i(str.end()); i != last_i; ++i)
            {
                if(!std::isxdigit(*i))
                {
                    return BooleanValue::MakeLockedValue(false);
                }
            }
            
            return BooleanValue::MakeLockedValue(true);
        }
        
        default:
        {
            //  Empty
        }
        
    }
    
    std::stringstream message;
    message << "Cannot convert a ";
    message << arg->Type();
    message << " to a string.";
    
    throw IllegalCastException(message.str());
}

/******************************************************************************

    dish::LeftJustifyFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::LeftJustifyFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const IntegerT width(getParam(symtab, "width")->AsInteger());
    const StringT str(getParam(symtab, "str")->AsString());
    const IntegerT strlen(static_cast< IntegerT >(str.length()));
    
    if(width > strlen)
    {
        return StringValue::MakeValue(str + std::string(width - strlen, ' '));
    }
    else
    {
        return StringValue::MakeValue(str);
    }
}

/******************************************************************************

    dish::RightJustifyFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::RightJustifyFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const IntegerT width(getParam(symtab, "width")->AsInteger());
    const StringT str(getParam(symtab, "str")->AsString());
    const IntegerT strlen(static_cast< IntegerT >(str.length()));

    if(width > strlen)
    {
        return StringValue::MakeValue(std::string(width - strlen, ' ') + str);
    }
    else
    {
        return StringValue::MakeValue(str);
    }
}

/******************************************************************************

    dish::CenterJustifyFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::CenterJustifyFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const IntegerT width(getParam(symtab, "width")->AsInteger());
    const StringT str(getParam(symtab, "str")->AsString());
    const IntegerT strlen(static_cast< IntegerT >(str.length()));
    
    if(width > strlen)
    {
        StringT formatted_str(std::string((width - strlen) / 2, ' ') + str);
        formatted_str += std::string(width - formatted_str.length(), ' ');
    
        return StringValue::MakeValue(formatted_str);
    }
    else
    {
        return StringValue::MakeValue(str);
    }
}

/******************************************************************************

    dish::LeftStringFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::LeftStringFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const StringT str(getParam(symtab, "str")->AsString());
    const IntegerT n(getParam(symtab, "n")->AsInteger());
    
    if(n < static_cast< IntegerT >(str.length()))
    {
        return StringValue::MakeValue(str.substr(0, n));
    }
    else
    {
        return StringValue::MakeValue(str);
    }
}

/******************************************************************************

    dish::RightStringFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::RightStringFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const StringT str(getParam(symtab, "str")->AsString());
    const IntegerT strlen(static_cast< IntegerT >(str.length()));
    
    const IntegerT n(getParam(symtab, "n")->AsInteger());
    
    if(n < strlen)
    {
        return StringValue::MakeValue(str.substr(n, std::string::npos));
    }
    else
    {
        return StringValue::MakeValue(str);
    }
}

/******************************************************************************

    dish::MiddleStringFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::MiddleStringFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const StringT str(getParam(symtab, "str")->AsString());
    const IntegerT strlen(static_cast< IntegerT >(str.length()));
    
    const IntegerT start(getParam(symtab, "start")->AsInteger());
    const IntegerT n(getParam(symtab, "n")->AsInteger());
    
    if(start < strlen)
    {
        if(n <= (strlen - start))
        {
            return StringValue::MakeValue(str.substr(start, n));
        }
        else
        {
            return StringValue::MakeValue(str.substr(start, std::string::npos));
        }
    }
    else
    {
        return StringValue::MakeValue("");
    }
}

/******************************************************************************

    dish::StringBeginsWith2Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::StringBeginsWith2Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    return BooleanValue::MakeLockedValue(
        BeginsWith(
            getParam(symtab, "str")->AsString(),
            getParam(symtab, "substr")->AsString()
        )
    );
}

/******************************************************************************

    dish::StringBeginsWith3Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::StringBeginsWith3Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    return BooleanValue::MakeLockedValue(
        BeginsWith(
            getParam(symtab, "str")->AsString(),
            getParam(symtab, "substr")->AsString(),
            getParam(symtab, "case_sensitive")->AsBoolean()
        )
    );
}

/******************************************************************************

    dish::StringEndsWith2Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::StringEndsWith2Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    return BooleanValue::MakeLockedValue(
        EndsWith(
            getParam(symtab, "str")->AsString(),
            getParam(symtab, "substr")->AsString()
        )
    );
}

/******************************************************************************

    dish::StringEndsWith3Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::StringEndsWith3Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    return BooleanValue::MakeLockedValue(
        EndsWith(
            getParam(symtab, "str")->AsString(),
            getParam(symtab, "substr")->AsString(),
            getParam(symtab, "case_sensitive")->AsBoolean()
        )
    );
}

/******************************************************************************

    dish::StringFindFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::StringFindFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const StringT searchstr(getParam(symtab, "searchstr")->AsString());
    const IntegerT searchstr_len(static_cast< IntegerT >(searchstr.length()));
    
    //  Make sure the string we are searching is not empty.
    if(searchstr_len > 0)
    {
        std::shared_ptr< iAtomic > substr_arg(getParam(symtab, "substr"));
        const StringT substr((iAtomic::typeInteger != substr_arg->Type()) ? substr_arg->AsString() : StringT(1, substr_arg->AsInteger()));
        const IntegerT substr_len(static_cast< IntegerT >(substr.length()));
        
        //  Make sure the substring we are looking for is not empty and is not
        //  longer than the string we are searching.
        if((substr_len > 0) && (substr_len <= searchstr_len))
        {
            const IntegerT pos(getParam(symtab, "pos")->AsInteger());
        
            //  Make sure the initial position is within the search string.
            if((pos >= 0) && (pos < searchstr_len))
            {
                //  Are we doing a case-sensitive or case-insensitive search?
                if(getParam(symtab, "case_sensitive")->AsBoolean())
                {
                    //  Case-sensitive...
                    const IntegerT searchpos(
                        static_cast< IntegerT >(searchstr.find(substr, static_cast< StringT::size_type >(pos)))
                    );
                    
                    if((searchpos >= 0) && (searchpos < searchstr_len))
                    {
                        return dish::IntegerValue::MakeValue(searchpos);
                    }
                }
                else
                {
                    //  Case-insensitive...
                    for(IntegerT i(pos), last_i(searchstr_len - substr_len); i < last_i; ++i)
                    {
                        bool match(true);
                        
                        for(IntegerT j(0); match && (j < substr_len); ++j)
                        {
                            if(std::toupper(substr[j]) != std::toupper(searchstr[i + j]))
                            {
                                match = false;
                            }
                        }
                        
                        if(match)
                        {
                            return dish::IntegerValue::MakeValue(i);
                        }
                    }
                }
            }
        }
    }
        
    return dish::IntegerValue::MakeValue(STRINVALID);
}

/******************************************************************************

    dish::StringFindNextOfFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::StringFindNextOfFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    StringT searchstr(getParam(symtab, "searchstr")->AsString());
    
    //  Make sure the string we are searching is not empty.
    if(!searchstr.empty())
    {
        std::shared_ptr< iAtomic > searchchars_arg(getParam(symtab, "searchchars"));
        StringT searchchars((iAtomic::typeInteger != searchchars_arg->Type()) ? searchchars_arg->AsString() : StringT(1, searchchars_arg->AsInteger()));
        
        //  Make sure we are looking for at least one character.
        if(!searchchars.empty())
        {
            const IntegerT pos(getParam(symtab, "pos")->AsInteger());
            const IntegerT searchstr_len(static_cast< IntegerT >(searchstr.length()));
        
            //  Make sure the initial position is within the search-string.
            if((pos >= 0) && (pos < searchstr_len))
            {
                if(!getParam(symtab, "case_sensitive")->AsBoolean())
                {
                    //  Convert the search-string to upper-case.
                    searchstr = ToUpper(searchstr);
                
                    //  Convert all of the search-characters to upper-case.
                    searchchars = ToUpper(searchchars);
                }
                
                const StringT::size_type found_pos(searchstr.find_first_of(searchchars, static_cast< StringT::size_type >(pos)));
                
                return dish::IntegerValue::MakeValue(
                    (StringT::npos != found_pos) ? static_cast< IntegerT>(found_pos) : STRINVALID
                );
            }
        }
    }
        
    return dish::IntegerValue::MakeValue(STRINVALID);
}

/******************************************************************************

    dish::StringFindNextNotOfFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::StringFindNextNotOfFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    StringT searchstr(getParam(symtab, "searchstr")->AsString());
    
    //  Make sure the string we are searching is not empty.
    if(!searchstr.empty())
    {
        std::shared_ptr< iAtomic > searchchars_arg(getParam(symtab, "searchchars"));
        StringT searchchars((iAtomic::typeInteger != searchchars_arg->Type()) ? searchchars_arg->AsString() : StringT(1, searchchars_arg->AsInteger()));
        
        //  Make sure we are looking for at least one character.
        if(!searchchars.empty())
        {
            const IntegerT pos(getParam(symtab, "pos")->AsInteger());
            const IntegerT searchstr_len(static_cast< IntegerT >(searchstr.length()));
        
            //  Make sure the initial position is within the search-string.
            if((pos >= 0) && (pos < searchstr_len))
            {
                if(!getParam(symtab, "case_sensitive")->AsBoolean())
                {
                    //  Convert the search-string to upper-case.
                    searchstr = ToUpper(searchstr);
                
                    //  Convert all of the search-characters to upper-case.
                    searchchars = ToUpper(searchchars);
                }
                
                const StringT::size_type found_pos(searchstr.find_first_not_of(searchchars, static_cast< StringT::size_type >(pos)));
                
                return dish::IntegerValue::MakeValue(
                    (StringT::npos != found_pos) ? static_cast< IntegerT>(found_pos) : STRINVALID
                );
            }
        }
    }
        
    return dish::IntegerValue::MakeValue(STRINVALID);
}

/******************************************************************************

    dish::StringFindLastOfFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::StringFindLastOfFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    StringT searchstr(getParam(symtab, "searchstr")->AsString());
    
    //  Make sure the string we are searching is not empty.
    if(!searchstr.empty())
    {
        std::shared_ptr< iAtomic > searchchars_arg(getParam(symtab, "searchchars"));
        StringT searchchars((iAtomic::typeInteger != searchchars_arg->Type()) ? searchchars_arg->AsString() : StringT(1, searchchars_arg->AsInteger()));
        
        //  Make sure we are looking for at least one character.
        if(!searchchars.empty())
        {
            const IntegerT pos(getParam(symtab, "pos")->AsInteger());
            const IntegerT searchstr_len(static_cast< IntegerT >(searchstr.length()));
        
            //  Make sure the initial position is within the search-string.
            if((pos >= 0) && (pos < searchstr_len))
            {
                if(!getParam(symtab, "case_sensitive")->AsBoolean())
                {
                    //  Convert the search-string to upper-case.
                    searchstr = ToUpper(searchstr);
                
                    //  Convert all of the search-characters to upper-case.
                    searchchars = ToUpper(searchchars);
                }
                
                const StringT::size_type found_pos(searchstr.find_last_of(searchchars, static_cast< StringT::size_type >(pos)));
                
                return dish::IntegerValue::MakeValue(
                    (StringT::npos != found_pos) ? static_cast< IntegerT>(found_pos) : STRINVALID
                );
            }
        }
    }
        
    return dish::IntegerValue::MakeValue(STRINVALID);
}

/******************************************************************************

    dish::StringFindLastNotOfFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::StringFindLastNotOfFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    StringT searchstr(getParam(symtab, "searchstr")->AsString());
    
    //  Make sure the string we are searching is not empty.
    if(!searchstr.empty())
    {
        std::shared_ptr< iAtomic > searchchars_arg(getParam(symtab, "searchchars"));
        StringT searchchars((iAtomic::typeInteger != searchchars_arg->Type()) ? searchchars_arg->AsString() : StringT(1, searchchars_arg->AsInteger()));
        
        //  Make sure we are looking for at least one character.
        if(!searchchars.empty())
        {
            const IntegerT pos(getParam(symtab, "pos")->AsInteger());
            const IntegerT searchstr_len(static_cast< IntegerT >(searchstr.length()));
        
            //  Make sure the initial position is within the search-string.
            if((pos >= 0) && (pos < searchstr_len))
            {
                if(!getParam(symtab, "case_sensitive")->AsBoolean())
                {
                    //  Convert the search-string to upper-case.
                    searchstr = ToUpper(searchstr);
                
                    //  Convert all of the search-characters to upper-case.
                    searchchars = ToUpper(searchchars);
                }
                
                const StringT::size_type found_pos(searchstr.find_last_not_of(searchchars, static_cast< StringT::size_type >(pos)));
                
                return dish::IntegerValue::MakeValue(
                    (StringT::npos != found_pos) ? static_cast< IntegerT>(found_pos) : STRINVALID
                );
            }
        }
    }
        
    return dish::IntegerValue::MakeValue(STRINVALID);
}

/******************************************************************************

    dish::StringTrimLeadingFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::StringTrimLeadingFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const StringT str(getParam(symtab, "str")->AsString());
    const StringT chars(getParam(symtab, "chars")->AsString());
    
    const StringT::size_type pos(str.find_first_not_of(chars));
    
    return StringValue::MakeValue((StringT::npos != pos) ? str.substr(pos, StringT::npos) : str);
}

/******************************************************************************

    dish::StringTrimTrailingFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::StringTrimTrailingFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const StringT str(getParam(symtab, "str")->AsString());
    const StringT chars(getParam(symtab, "chars")->AsString());
    
    const StringT::size_type pos(str.find_last_not_of(chars));
    
    return StringValue::MakeValue((StringT::npos != pos) ? str.substr(0, pos + 1) : str);
}

/******************************************************************************

    dish::StringRemoveAllOfFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::StringRemoveAllOfFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const StringT str(getParam(symtab, "str")->AsString());
    const StringT chars(getParam(symtab, "chars")->AsString());
    
    StringT newstr;
    
    std::for_each(
        str.begin(), str.end(),
        [&](const StringT::value_type &ch)
        {
            if(StringT::npos == chars.find(ch))
            {
                newstr.push_back(ch);
            }
        }
    );
    
    return StringValue::MakeValue(newstr);
}

/******************************************************************************

    dish::StringRemoveAllNotOfFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::StringRemoveAllNotOfFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const StringT str(getParam(symtab, "str")->AsString());
    const StringT chars(getParam(symtab, "chars")->AsString());
    
    StringT newstr;
    
    std::for_each(
        str.begin(), str.end(),
        [&](const StringT::value_type &ch)
        {
            if(StringT::npos != chars.find(ch))
            {
                newstr.push_back(ch);
            }
        }
    );
    
    return StringValue::MakeValue(newstr);
}

/******************************************************************************

    dish::StringReplaceAllFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::StringReplaceAllFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const StringT str(getParam(symtab, "str")->AsString());
    const StringT target(getParam(symtab, "target")->AsString());
    const StringT::size_type target_len(target.length());
    const StringT replace(getParam(symtab, "replace")->AsString());

    if(target_len > 0)
    {
        StringT::size_type cur_pos(0);
        StringT newstr;
        
        if(getParam(symtab, "casesensitive")->AsBoolean())
        {
            for(bool done(false); !done; )
            {
                const StringT::size_type next_pos(str.find(target, cur_pos));
                
                if(StringT::npos != next_pos)
                {
                    newstr += str.substr(cur_pos, next_pos - cur_pos);
                
                    newstr += replace;
                    
                    cur_pos = next_pos + target_len;
                }
                else
                {
                    newstr += str.substr(cur_pos, StringT::npos);
                    
                    done = true;
                }
            }
        }
        else
        {
            const StringT srcstr(ToUpper(str));
            const StringT srctarget(ToUpper(target));
            
            for(bool done(false); !done; )
            {
                const StringT::size_type next_pos(srcstr.find(srctarget, cur_pos));
                
                if(StringT::npos != next_pos)
                {
                    newstr += str.substr(cur_pos, next_pos - cur_pos);
                    
                    newstr += replace;
                    
                    cur_pos = next_pos + target_len;
                }
                else
                {
                    newstr += str.substr(cur_pos, StringT::npos);
                    
                    done = true;
                }
            }
        }
        
        return StringValue::MakeValue(newstr);
    }
    
    else if(str.empty())
    {
        return StringValue::MakeValue(replace);
    }
    
    return StringValue::MakeValue(str);
}

/******************************************************************************

    dish::StringReplaceAllWithPosFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::StringReplaceAllWithPosFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const StringT str(getParam(symtab, "str")->AsString());
    const StringT target(getParam(symtab, "target")->AsString());
    const StringT::size_type target_len(target.length());
    const StringT replace(getParam(symtab, "replace")->AsString());

    if(target_len > 0)
    {
        StringT::size_type cur_pos(getParam(symtab, "pos")->AsInteger());        
        StringT newstr;
        
        if(getParam(symtab, "casesensitive")->AsBoolean())
        {
            for(bool done(false); !done; )
            {
                const StringT::size_type next_pos(str.find(target, cur_pos));
                
                if(StringT::npos != next_pos)
                {
                    newstr += str.substr(cur_pos, next_pos - cur_pos);
                    
                    newstr += replace;
                    
                    cur_pos = next_pos + target_len;
                }
                else
                {
                    newstr += str.substr(cur_pos, StringT::npos);
                    
                    done = true;
                }
            }
        }
        else
        {
            const StringT srcstr(ToUpper(str));
            const StringT srctarget(ToUpper(target));
            
            for(bool done(false); !done; )
            {
                const StringT::size_type next_pos(srcstr.find(srctarget, cur_pos));
                
                if(StringT::npos != next_pos)
                {
                    newstr += str.substr(cur_pos, next_pos - cur_pos);
                    
                    newstr += replace;
                    
                    cur_pos = next_pos + target_len;
                }
                else
                {
                    newstr += str.substr(cur_pos, StringT::npos);
                    
                    done = true;
                }
            }
        }
        
        return StringValue::MakeValue(newstr);
    }
    
    else if(str.empty())
    {
        return StringValue::MakeValue(replace);
    }
    
    return StringValue::MakeValue(str);
}

/******************************************************************************

    dish::StringReplaceFirstFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::StringReplaceFirstFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const StringT str(getParam(symtab, "str")->AsString());
    const StringT target(getParam(symtab, "target")->AsString());
    const StringT::size_type target_len(target.length());
    const StringT replace(getParam(symtab, "replace")->AsString());

    if(target_len > 0)
    {
        StringT newstr;
        
        if(getParam(symtab, "casesensitive")->AsBoolean())
        {
            const StringT::size_type next_pos(str.find(target));
            
            if(StringT::npos != next_pos)
            {
                newstr += str.substr(0, next_pos);
                newstr += replace;
                newstr += str.substr(next_pos + target_len, StringT::npos);
            }
            else
            {
                newstr = str;
            }
        }
        else
        {
            const StringT::size_type next_pos(
                ToUpper(str).find(ToUpper(target))
            );
            
            if(StringT::npos != next_pos)
            {
                newstr += str.substr(0, next_pos);
                newstr += replace;
                newstr += str.substr(next_pos + target_len, StringT::npos);
            }
            else
            {
                newstr = str;
            }
        }
        
        return StringValue::MakeValue(newstr);
    }
    
    else if(str.empty())
    {
        return StringValue::MakeValue(replace);
    }
    
    return StringValue::MakeValue(str);
}

/******************************************************************************

    dish::StringReplaceFirstWithPosFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::StringReplaceFirstWithPosFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const StringT str(getParam(symtab, "str")->AsString());
    const IntegerT pos(getParam(symtab, "pos")->AsInteger());
    const StringT target(getParam(symtab, "target")->AsString());
    const StringT::size_type target_len(target.length());
    const StringT replace(getParam(symtab, "replace")->AsString());

    if(target_len > 0)
    {
        StringT newstr;
        
        if(getParam(symtab, "casesensitive")->AsBoolean())
        {
            const StringT::size_type next_pos(str.find(target, pos));
            
            if(StringT::npos != next_pos)
            {
                newstr += str.substr(0, next_pos);
                newstr += replace;
                newstr += str.substr(next_pos + target_len, StringT::npos);
            }
            else
            {
                newstr = str;
            }
        }
        else
        {
            const StringT::size_type next_pos(
                ToUpper(str).find(ToUpper(target), pos)
            );
            
            if(StringT::npos != next_pos)
            {
                newstr += str.substr(0, next_pos);
                newstr += replace;
                newstr += str.substr(next_pos + target_len, StringT::npos);
            }
            else
            {
                newstr = str;
            }
        }
        
        return StringValue::MakeValue(newstr);
    }
    
    else if(str.empty())
    {
        return StringValue::MakeValue(replace);
    }
    
    return StringValue::MakeValue(str);
}

/******************************************************************************

    dish::StringReplicateFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::StringReplicateFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    StringT value;
    
    const StringT str(getParam(symtab, "str")->AsString());

    for(IntegerT n(getParam(symtab, "n")->AsInteger()); n-- > 0; )
    {
        value += str;
    }

    return StringValue::MakeValue(value);
}

/******************************************************************************

    dish::StringReverseFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::StringReverseFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const StringT str(getParam(symtab, "str")->AsString());

    return StringValue::MakeValue(StringT(str.rbegin(), str.rend()));
}

