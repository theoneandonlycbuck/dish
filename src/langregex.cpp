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

////////////////////////////////////////////////////////////////////////////////
//

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
//  Regular expression support in g++ was not completed until v4.9. This test
//  verifies that dish is being compiled with that version of the compiler or
//  later.
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifdef __GNUC__

    #include <features.h>

    #if not __GNUC_PREREQ(4, 9)
    #error Regular expression support requires g++ v4.9 or later.
    #endif

#endif

//
////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <regex>
#include <string>

#include "exception.h"
#include "langregex.h"
#include "utility.h"

namespace
{

    ////////////////////////////////////////////////////////////////////////////
        
    class RegEx
    {
        private:
            std::unique_ptr< std::regex > mRegEx;
    
        public:
            INLINE RegEx() : mRegEx() {};
            
            INLINE void Create(const dish::StringT &regex) { mRegEx.reset(new std::regex(regex)); };
            
            INLINE dish::StringT Next(const dish::StringT &src, dish::IntegerT &pos)
            {
                assert(mRegEx);
                
                const dish::StringT::size_type posi(static_cast< std::string::size_type >(pos));
                const std::regex_iterator< dish::StringT::const_iterator > rit(
                    ((posi < src.length()) ? (src.begin() + posi) : src.end()), src.end(), *mRegEx
                );
                
                dish::StringT result;
                if(!rit->empty())
                {
                    pos += static_cast< dish::IntegerT >(rit->position() + rit->str().length());
            
                    result = rit->str();
                }
                else
                {
                    pos = static_cast< dish::IntegerT >(std::string::npos);
                }
            
                return result;
            }
            
            INLINE dish::StringT &ReplaceNext(dish::StringT &src, dish::IntegerT &pos, const dish::StringT &replace)
            {
                assert(mRegEx);
                
                const dish::StringT::size_type srclen(src.length());
                const dish::StringT::size_type posi(static_cast< std::string::size_type >(pos));
                
                std::string result;
                std::regex_replace(
                    std::back_inserter(result), 
                    ((posi < srclen) ? (src.begin() + posi) : src.end()), 
                    src.end(), 
                    *mRegEx, 
                    replace + "$2",
                    std::regex_constants::format_first_only
                );
                
                src = result;
                pos += replace.length();
            
                return src;
            }
    
            INLINE dish::StringT &ReplaceAll(dish::StringT &src, dish::IntegerT &pos, const dish::StringT &replace)
            {
                assert(mRegEx);
                
                const dish::StringT::size_type srclen(src.length());
                const dish::StringT::size_type posi((pos >= 0) ? static_cast< std::string::size_type >(pos) : std::string::npos);
                
                std::string result;
                std::regex_replace(
                    std::back_inserter(result),
                    ((posi < srclen) ? (src.begin() + posi) : src.end()),
                    src.end(),
                    *mRegEx,
                    replace + "$2"
                );
                
                src = result;
                pos = -1;
            
                return src;
                
            }
            
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class RegExHandleSet : public dish::HandleList< RegEx, REGEX_MAX_NUM_HANDLES >
    {
        public:
            INLINE RegExHandleSet() : dish::HandleList< RegEx, REGEX_MAX_NUM_HANDLES >() {};
        
            INLINE unsigned int Open(const dish::StringT &str)
            {
                const unsigned int handle(Allocate());
                operator[](handle).Create(str);
                
                return handle;
            }
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    RegExHandleSet RegExHandles;

    ////////////////////////////////////////////////////////////////////////////

}

/******************************************************************************

    dish::CreateRegularExpressionFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::CreateRegularExpressionFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return IntegerValue::MakeValue(
        static_cast< IntegerT >(RegExHandles.Open(getParam(symtab, "regex")->AsString()))
    );
}

/******************************************************************************

    dish::NumCreatedRegularExpressionFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::NumCreatedRegularExpressionFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return IntegerValue::MakeValue(
        static_cast< IntegerT >(RegExHandles.NumAllocated())
    );
}

/******************************************************************************

    dish::IsCreatedRegularExpressionFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::IsCreatedRegularExpressionFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return BooleanValue::MakeLockedValue(
        RegExHandles.IsValid(getParam(symtab, "handle")->AsInteger())
    );
}

/******************************************************************************

    dish::DestroyRegularExpressionFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::DestroyRegularExpressionFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return BooleanValue::MakeLockedValue(
        RegExHandles.Destroy(getParam(symtab, "handle")->AsInteger())
    );
}

/******************************************************************************

    dish::DestroyAllRegularExpressionFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::DestroyAllRegularExpressionFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    RegExDestroyAllHandles();

    return NullValue::MakeValue();
}

/******************************************************************************

    dish::MatchRegularExpressionFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::MatchRegularExpressionFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    //  Get the funtion arguments.
    const IntegerT handle(getParam(symtab, "handle")->AsInteger());
    const StringT src(getParam(symtab, "src")->AsString());
    std::shared_ptr< iAtomic > posatomic(getParam(symtab, "pos"));
    IntegerT pos(posatomic->AsInteger());

    //  Get the next text from the source string matching the reg-ex.
    const StringT result(RegExHandles[handle].Next(src, pos));
    
    //  Update the position argument.
    posatomic->Assign(pos);
    
    return StringValue::MakeValue(result);
}

/******************************************************************************

    dish::ReplaceNextRegularExpressionFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::ReplaceNextRegularExpressionFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    //  Get the funtion arguments.
    const IntegerT handle(getParam(symtab, "handle")->AsInteger());
    StringT src(getParam(symtab, "src")->AsString());
    std::shared_ptr< iAtomic > posatomic(getParam(symtab, "pos"));
    IntegerT pos(posatomic->AsInteger());
    const StringT replace(getParam(symtab, "replace")->AsString());

    //  Get the next text from the source string matching the reg-ex.
    const StringT result(RegExHandles[handle].ReplaceNext(src, pos, replace));
    
    //  Update the position argument.
    posatomic->Assign(pos);

    return StringValue::MakeValue(result);
}

/******************************************************************************

    dish::ReplaceAllRegularExpressionFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::ReplaceAllRegularExpressionFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    //  Get the funtion arguments.
    const IntegerT handle(getParam(symtab, "handle")->AsInteger());
    StringT src(getParam(symtab, "src")->AsString());
    std::shared_ptr< iAtomic > posatomic(getParam(symtab, "pos"));
    IntegerT pos(posatomic->AsInteger());
    const StringT replace(getParam(symtab, "replace")->AsString());

    //  Get the next text from the source string matching the reg-ex.
    const StringT result(RegExHandles[handle].ReplaceAll(src, pos, replace));
    
    //  Update the position argument.
    posatomic->Assign(pos);

    return StringValue::MakeValue(result);
}

/******************************************************************************

    Global definitions

 ******************************************************************************/
 
void dish::RegExDestroyAllHandles()
{
    RegExHandles.DestroyAll();
}

