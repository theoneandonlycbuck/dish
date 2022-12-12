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

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#ifdef LANG_LIB_TEXTIO
#include <ncurses.h>
#endif

#include <iostream>
#include <sstream>
#include <string>

#include "graph.h"
#include "langio.h"
#include "textio.h"

namespace
{

#ifndef LANG_LIB_TEXTIO

    int getch()
    {
	    struct termios oldt;
	    tcgetattr(STDIN_FILENO, &oldt);
	    
	    struct termios newt(oldt);
	    newt.c_lflag &= ~( ICANON | ECHO );
	    
	    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	    const int ch(getchar());
	    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	    
	    return ch;
    }

#endif

}

/******************************************************************************

    dish::PrintFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::PrintFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    if(NCursesStarted)
    {
#ifdef LANG_LIB_TEXTIO
        printw(getParam(symtab, "str")->AsString().c_str());
#else
        assert(false);
#endif
    }
    else
    {
        std::cout << getParam(symtab, "str")->AsString();
        std::cout.flush();
    }

    return NullValue::MakeValue();
}

/******************************************************************************

    dish::Println0Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Println0Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    if(NCursesStarted)
    {
#ifdef LANG_LIB_TEXTIO
        printw("\n");
#else
        assert(false);
#endif
    }
    else
    {
        std::cout << std::endl;
    }

    return NullValue::MakeValue();
}

/******************************************************************************

    dish::PrintlnFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::PrintlnFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    if(NCursesStarted)
    {
#ifdef LANG_LIB_TEXTIO
        printw(getParam(symtab, "str")->AsString().c_str());
        printw("\n");
#else
        assert(false);
#endif
    }
    else
    {
        std::cout << getParam(symtab, "str")->AsString();
        std::cout << std::endl;
    }

    return NullValue::MakeValue();
}

/******************************************************************************

    dish::NewlnFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::NewlnFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    if(NCursesStarted)
    {
#ifdef LANG_LIB_TEXTIO
        printw("\r\n");
#else
        assert(false);
#endif
    }
    else
    {
        std::cout << std::endl;
    }

    return NullValue::MakeValue();
}

/******************************************************************************

    dish::KeyPressedFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::KeyPressedFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    bool key_pressed(false);

    if(GRAPH_IsStarted())
    {
        key_pressed = GRAPH_KeyPressed();
    }
    else
    {
        struct termios oldt;
        tcgetattr(STDIN_FILENO, &oldt);
        
        struct termios newt(oldt);
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        
        const int oldf(fcntl(STDIN_FILENO, F_GETFL, 0));
        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

        const int ch(getchar());

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);

        if(EOF != ch)
        {
            std::ungetc(ch, stdin);
            
            key_pressed = true;
        }
    }

    return BooleanValue::MakeLockedValue(key_pressed);
}

/******************************************************************************

    dish::ReadFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::ReadFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    if(NCursesStarted)
    {
        return StringValue::MakeValue(StringT(1, getch()));
    }
    
    else if(GRAPH_IsStarted())
    {
        return StringValue::MakeValue(StringT(1, GRAPH_GetKey()));
    }
    
    return StringValue::MakeValue(StringT(1, std::getchar()));
}

/******************************************************************************

    dish::ReadChFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::ReadChFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    if(NCursesStarted)
    {
        return IntegerValue::MakeValue(getch());
    }
    
    else if(GRAPH_IsStarted())
    {
        return IntegerValue::MakeValue(GRAPH_GetKey());
    }
    
    return IntegerValue::MakeValue(std::getchar());
}

/******************************************************************************

    dish::ReadIntegerFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::ReadIntegerFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::string str;
    std::cin >> str;
    
    std::stringstream input(str);
    
    IntegerT value;
    input >> value;
    
    return IntegerValue::MakeValue(value);
}

/******************************************************************************

    dish::ReadRealFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::ReadRealFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::string str;
    std::cin >> str;
    
    std::stringstream input(str);
    
    RealT value;
    input >> value;
    
    return RealValue::MakeValue(value);
}

/******************************************************************************

    dish::ReadlnFunction class definitions

 ******************************************************************************/
 
namespace
{

    const int INPUT_BUFFER_LENGTH(4096);

}

std::shared_ptr< dish::iAtomic > dish::ReadlnFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    if(NCursesStarted)
    {
#ifdef LANG_LIB_TEXTIO
        int status(echo());
        assert(ERR != status);
    
        char input[INPUT_BUFFER_LENGTH] = { '\0' };
        status = getnstr(input, INPUT_BUFFER_LENGTH);
        assert(ERR != status);
        
        status = noecho();
        assert(ERR != status);
        
        return StringValue::MakeValue(std::string(input));
#else
        assert(false);
#endif
    }
    else
    {
        std::string input;
        std::cin >> input;
    
        return StringValue::MakeValue(input);
    }
}

