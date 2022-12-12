 /*
    This file is part of the DISH programming language, Copyright 2014-2018 by 
    Chris Buck.
    
    DISH is free software for non-commercial use: you can redistribute it and/or
    modify it provided
    
        (1) The following Copyright notice is displayed at runtime:
    
            DISH programming language copyright (c) 2014-2018 by Chris Buck.
        
        (2) All source files duplicate this copyright statement in full.
        
    Commercial licenses can be negotiated by contacting Chris Buck at
    chrisbuck1220@hotmail.com.

    DISH is distributed in the hope that it will be useful, but WITHOUT ANY 
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS 
    FOR A PARTICULAR PURPOSE.
*/

#ifndef DISH_TEXTIO_H
#define DISH_TEXTIO_H

#include "dishconfig.h"

#ifdef LANG_LIB_TEXTIO
#include <ncurses.h>
#endif

#include "graph.h"
#include "inline.h"

namespace dish
{

    ////////////////////////////////////////////////////////////////////////////

    extern bool NCursesStarted;
    
    extern int ForegroundColor;
    extern int BackgroundColor;
    extern int NColorSet;

    ////////////////////////////////////////////////////////////////////////////
    
    class RestoreTerminal
    {
        public:
            INLINE RestoreTerminal() {};
            ~RestoreTerminal();
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    extern void EnsureNCursesStarted();
    extern void SetForegroundColor(const int color);
    extern void SetBackgroundColor(const int color);
    extern void SetColor(const int fore, const int back);
    
    extern void start_ncurses();
    extern void end_ncurses();

    ////////////////////////////////////////////////////////////////////////////

}

#endif

