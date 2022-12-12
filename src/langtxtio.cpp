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

#include <cassert>
#include <cstdlib>
#include <sstream>

#include <ncurses.h>

#include "langtxtio.h"
#include "textio.h"

namespace
{

    int Dummy(0);
    
}

/******************************************************************************

    dish::TEXTIO_StartFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::TEXTIO_StartFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    if(!NCursesStarted)
    {
        start_ncurses();
        NCursesStarted = true;
    }

    return NullValue::MakeValue();
}

/******************************************************************************

    dish::TEXTIO_IsStartedFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::TEXTIO_IsStartedFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return BooleanValue::MakeLockedValue(NCursesStarted);
}

/******************************************************************************

    dish::TEXTIO_RefreshFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::TEXTIO_RefreshFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    EnsureNCursesStarted();
    
    const int status(refresh());
    assert(ERR != status);
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::TEXTIO_ClearFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::TEXTIO_ClearFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    EnsureNCursesStarted();
    
    const int status(clear());
    assert(ERR != status);
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::TEXTIO_EndFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::TEXTIO_EndFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    EnsureNCursesStarted();
    
    end_ncurses();
    NCursesStarted = false;
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::TEXTIO_GetXSizeFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::TEXTIO_GetXSizeFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    EnsureNCursesStarted();

    int xsize;
    getmaxyx(stdscr, Dummy, xsize);

    return IntegerValue::MakeValue(xsize);
}

/******************************************************************************

    dish::TEXTIO_GetYSizeFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::TEXTIO_GetYSizeFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    EnsureNCursesStarted();
    
    int ysize;
    getmaxyx(stdscr, ysize, Dummy);

    return IntegerValue::MakeValue(ysize);
}

/******************************************************************************

    dish::TEXTIO_MoveToFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::TEXTIO_MoveToFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    EnsureNCursesStarted();

    int xsize;
    int ysize;
    getmaxyx(stdscr, ysize, xsize);
    
    const int x(static_cast< int >(getParam(symtab, "x")->AsInteger()));
    const int y(static_cast< int >(getParam(symtab, "y")->AsInteger()));
    
    if((x >= 0) && (x < xsize) && (y >= 0) && (y < ysize))
    {
        const int status(move(y, x));
        assert(ERR != status);
    }
    else
    {
        std::stringstream message;
        message << "The position (";
        message << x;
        message << ", ";
        message << y;
        message << ") does not fall within the window boundaries: (";
        message << xsize;
        message << ", ";
        message << ysize;
        message << ").";
        
        throw DomainErrorException(message.str());
    }
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::TEXTIO_AttrNormalFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::TEXTIO_AttrNormalFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    EnsureNCursesStarted();

    const int status(attrset(A_NORMAL));
    assert(ERR != status);
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::TEXTIO_AttrGetFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::TEXTIO_AttrGetFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    EnsureNCursesStarted();

    attr_t attr;
    short int color;
    
    const int status(attr_get(&attr, &color, NULL));
    assert(0 == status);

    return IntegerValue::MakeValue(attr);
}

/******************************************************************************

    dish::TEXTIO_AttrSetFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::TEXTIO_AttrSetFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    EnsureNCursesStarted();

    const int status(attrset(static_cast< int >(getParam(symtab, "attr")->AsInteger())));
    assert(ERR != status);
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::TEXTIO_AttrOnFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::TEXTIO_AttrOnFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    EnsureNCursesStarted();

    const int status(attron(static_cast< int >(getParam(symtab, "attr")->AsInteger())));
    assert(ERR != status);
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::TEXTIO_AttrOffFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::TEXTIO_AttrOffFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    EnsureNCursesStarted();

    const int status(attroff(static_cast< int >(getParam(symtab, "attr")->AsInteger())));
    assert(ERR != status);
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::TEXTIO_SetForegroundColorFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::TEXTIO_SetForegroundColorFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    EnsureNCursesStarted();

    SetForegroundColor(getParam(symtab, "color")->AsInteger());
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::TEXTIO_GetForegroundColorFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::TEXTIO_GetForegroundColorFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    EnsureNCursesStarted();
    
    return IntegerValue::MakeValue(ForegroundColor);
}

/******************************************************************************

    dish::TEXTIO_SetBackgroundColorFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::TEXTIO_SetBackgroundColorFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    EnsureNCursesStarted();
    
    SetBackgroundColor(getParam(symtab, "color")->AsInteger());
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::TEXTIO_GetBackgroundColorFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::TEXTIO_GetBackgroundColorFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    EnsureNCursesStarted();
    
    return IntegerValue::MakeValue(BackgroundColor);
}

/******************************************************************************

    dish::TEXTIO_SetColorFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::TEXTIO_SetColorFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    EnsureNCursesStarted();

    SetColor(
        getParam(symtab, "fore")->AsInteger(),
        getParam(symtab, "back")->AsInteger()
    );
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::TEXTIO_SetCursorFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::TEXTIO_SetCursorFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    EnsureNCursesStarted();

    const int status(curs_set(getParam(symtab, "visible")->AsInteger()));
    assert(ERR != status);
    
    return NullValue::MakeValue();
}

