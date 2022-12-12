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

#include <cassert>

#include "exception.h"
#include "textio.h"

/******************************************************************************

    Global definitions

 ******************************************************************************/

bool dish::NCursesStarted(false);

int dish::ForegroundColor(
#ifdef LANG_LIB_TEXTIO
    COLOR_WHITE
#else
    -1
#endif
);

int dish::BackgroundColor(
#ifdef LANG_LIB_TEXTIO
    COLOR_BLACK
#else
    -1
#endif
);

int dish::NColorSet(0);

/******************************************************************************

    dish::RestoreTerminal class definitions

 ******************************************************************************/
 
dish::RestoreTerminal::~RestoreTerminal()
{
    if(NCursesStarted)
    {
#ifdef LANG_LIB_TEXTIO
        end_ncurses();
#endif

        NCursesStarted = false;
    }
    
    if(GRAPH_IsStarted())
    {
#ifdef LANG_LIB_GRAPH
        GRAPH_End();
#endif
    }
}

/******************************************************************************

    Function definitions

 ******************************************************************************/
    
void dish::EnsureNCursesStarted()
{
    if(!dish::NCursesStarted)
    {
        throw dish::IllegalFunctionCallException("TEXTIO mode not started.");
    }
}

void dish::SetForegroundColor(const int color)
{
    ForegroundColor = color;
 
#ifdef LANG_LIB_TEXTIO
    const int status(attrset(COLOR_PAIR(1 + ((8 * BackgroundColor) | ForegroundColor) % NColorSet)));
    assert(ERR != status);
#endif
}

void dish::SetBackgroundColor(const int color)
{
    BackgroundColor = color;

#ifdef LANG_LIB_TEXTIO
    const int status(attrset(COLOR_PAIR(1 + ((8 * BackgroundColor) | ForegroundColor) % NColorSet)));
    assert(ERR != status);
#endif
}

void dish::SetColor(const int fore, const int back)
{
    ForegroundColor = fore;
    BackgroundColor = back;

#ifdef LANG_LIB_TEXTIO
    const int status(attrset(COLOR_PAIR(1 + ((8 * BackgroundColor) | ForegroundColor) % NColorSet)));
    assert(ERR != status);
#endif
}

void dish::start_ncurses()
{
#ifdef LANG_LIB_TEXTIO
    int status;
    void *ret;

    ret = initscr();
    assert(NULL != ret);
    
    status = raw();
    assert(ERR != status);
    
    status = noecho();
    assert(ERR != status);
    
    status = cbreak();
    assert(ERR != status);
    
    status = keypad(stdscr, TRUE);
    assert(ERR != status);
    
    status = attrset(A_NORMAL);
    assert(ERR != status);
    
    if(has_colors())
    {
        status = start_color();
        assert(ERR != status);
        
        NColorSet = 0;
        
        (void)init_pair(++NColorSet, COLOR_BLACK, COLOR_BLACK);
        (void)init_pair(++NColorSet, COLOR_RED, COLOR_BLACK);
        (void)init_pair(++NColorSet, COLOR_GREEN, COLOR_BLACK);
        (void)init_pair(++NColorSet, COLOR_YELLOW, COLOR_BLACK);
        (void)init_pair(++NColorSet, COLOR_BLUE, COLOR_BLACK);
        (void)init_pair(++NColorSet, COLOR_MAGENTA, COLOR_BLACK);
        (void)init_pair(++NColorSet, COLOR_CYAN, COLOR_BLACK);
        (void)init_pair(++NColorSet, COLOR_WHITE, COLOR_BLACK);
        
        (void)init_pair(++NColorSet, COLOR_BLACK, COLOR_RED);
        (void)init_pair(++NColorSet, COLOR_RED, COLOR_RED);
        (void)init_pair(++NColorSet, COLOR_GREEN, COLOR_RED);
        (void)init_pair(++NColorSet, COLOR_YELLOW, COLOR_RED);
        (void)init_pair(++NColorSet, COLOR_BLUE, COLOR_RED);
        (void)init_pair(++NColorSet, COLOR_MAGENTA, COLOR_RED);
        (void)init_pair(++NColorSet, COLOR_CYAN, COLOR_RED);
        (void)init_pair(++NColorSet, COLOR_WHITE, COLOR_RED);
        
        (void)init_pair(++NColorSet, COLOR_BLACK, COLOR_GREEN);
        (void)init_pair(++NColorSet, COLOR_RED, COLOR_GREEN);
        (void)init_pair(++NColorSet, COLOR_GREEN, COLOR_GREEN);
        (void)init_pair(++NColorSet, COLOR_YELLOW, COLOR_GREEN);
        (void)init_pair(++NColorSet, COLOR_BLUE, COLOR_GREEN);
        (void)init_pair(++NColorSet, COLOR_MAGENTA, COLOR_GREEN);
        (void)init_pair(++NColorSet, COLOR_CYAN, COLOR_GREEN);
        (void)init_pair(++NColorSet, COLOR_WHITE, COLOR_GREEN);
        
        (void)init_pair(++NColorSet, COLOR_BLACK, COLOR_YELLOW);
        (void)init_pair(++NColorSet, COLOR_RED, COLOR_YELLOW);
        (void)init_pair(++NColorSet, COLOR_GREEN, COLOR_YELLOW);
        (void)init_pair(++NColorSet, COLOR_YELLOW, COLOR_YELLOW);
        (void)init_pair(++NColorSet, COLOR_BLUE, COLOR_YELLOW);
        (void)init_pair(++NColorSet, COLOR_MAGENTA, COLOR_YELLOW);
        (void)init_pair(++NColorSet, COLOR_CYAN, COLOR_YELLOW);
        (void)init_pair(++NColorSet, COLOR_WHITE, COLOR_YELLOW);
        
        (void)init_pair(++NColorSet, COLOR_BLACK, COLOR_BLUE);
        (void)init_pair(++NColorSet, COLOR_RED, COLOR_BLUE);
        (void)init_pair(++NColorSet, COLOR_GREEN, COLOR_BLUE);
        (void)init_pair(++NColorSet, COLOR_YELLOW, COLOR_BLUE);
        (void)init_pair(++NColorSet, COLOR_BLUE, COLOR_BLUE);
        (void)init_pair(++NColorSet, COLOR_MAGENTA, COLOR_BLUE);
        (void)init_pair(++NColorSet, COLOR_CYAN, COLOR_BLUE);
        (void)init_pair(++NColorSet, COLOR_WHITE, COLOR_BLUE);
        
        (void)init_pair(++NColorSet, COLOR_BLACK, COLOR_MAGENTA);
        (void)init_pair(++NColorSet, COLOR_RED, COLOR_MAGENTA);
        (void)init_pair(++NColorSet, COLOR_GREEN, COLOR_MAGENTA);
        (void)init_pair(++NColorSet, COLOR_YELLOW, COLOR_MAGENTA);
        (void)init_pair(++NColorSet, COLOR_BLUE, COLOR_MAGENTA);
        (void)init_pair(++NColorSet, COLOR_MAGENTA, COLOR_MAGENTA);
        (void)init_pair(++NColorSet, COLOR_CYAN, COLOR_MAGENTA);
        (void)init_pair(++NColorSet, COLOR_WHITE, COLOR_MAGENTA);
        
        (void)init_pair(++NColorSet, COLOR_BLACK, COLOR_CYAN);
        (void)init_pair(++NColorSet, COLOR_RED, COLOR_CYAN);
        (void)init_pair(++NColorSet, COLOR_GREEN, COLOR_CYAN);
        (void)init_pair(++NColorSet, COLOR_YELLOW, COLOR_CYAN);
        (void)init_pair(++NColorSet, COLOR_BLUE, COLOR_CYAN);
        (void)init_pair(++NColorSet, COLOR_MAGENTA, COLOR_CYAN);
        (void)init_pair(++NColorSet, COLOR_CYAN, COLOR_CYAN);
        (void)init_pair(++NColorSet, COLOR_WHITE, COLOR_CYAN);
        
        (void)init_pair(++NColorSet, COLOR_BLACK, COLOR_WHITE);
        (void)init_pair(++NColorSet, COLOR_RED, COLOR_WHITE);
        (void)init_pair(++NColorSet, COLOR_GREEN, COLOR_WHITE);
        (void)init_pair(++NColorSet, COLOR_YELLOW, COLOR_WHITE);
        (void)init_pair(++NColorSet, COLOR_BLUE, COLOR_WHITE);
        (void)init_pair(++NColorSet, COLOR_MAGENTA, COLOR_WHITE);
        (void)init_pair(++NColorSet, COLOR_CYAN, COLOR_WHITE);
        (void)init_pair(++NColorSet, COLOR_WHITE, COLOR_WHITE);
        
        SetColor(COLOR_WHITE, COLOR_BLACK);
    }
    
    status = refresh();
    assert(ERR != status);
#else
    assert(false);
#endif
}

void dish::end_ncurses()
{
#ifdef LANG_LIB_TEXTIO
    int status;

    status = curs_set(1);
    assert(ERR != status);
    
    status = attrset(A_NORMAL);
    assert(ERR != status);
    
    status = refresh();
    assert(ERR != status);
    
    status = endwin();
    assert(ERR != status);
#else
    assert(false);
#endif
}

