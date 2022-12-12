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

#include "dishconfig.h"

#ifdef LANG_LIB_GRAPH

#include <X11/X.h>
#include <X11/Xlib.h>

/*
    This is required to prevent collision between the DestroyAll macro defined
    in X-Windows and the dish::HandleList< T >::DestroyAll() method defined in 
    utility.h.
*/
#undef DestroyAll

#endif

#include <algorithm>
#include <climits>
#include <cmath>
#include <cstring>

#ifdef EVENT_TRACE
#include <iostream>
#endif

#include <list>
#include <map>
#include <memory>
#include <string>
#include <utility>

#include "exception.h"
#include "graph.h"
#include "langgraph.h"

namespace
{

#ifdef LANG_LIB_GRAPH

    int XSize(-1);
    int YSize(-1);

    Display *gfxDisplay(NULL);
    
    Window gfxWindow = { 0 };
    
    GC gfxGc = { 0 };
    
    std::string gfxFontName;
    XFontStruct *gfxFont(NULL);

#endif

    INLINEC bool IsStarted()
    {
#ifdef LANG_LIB_GRAPH
        return (NULL != gfxDisplay);
#else
        return false;
#endif
    }

    INLINEC void EnsureGraphicsStarted()
    {
        if(!IsStarted())
        {
            throw dish::IllegalFunctionCallException("GRAPH mode not started.");
        }
    }
    
#ifdef LANG_LIB_GRAPH

    void ProcessEvent(XEvent &e)
    {
    #ifdef EVENT_TRACE
        std::cout << "ProcessEvent()" << std::endl;
    #endif
    
        switch(e.type)
        {   
            case GraphicsExpose:
                //  Fall-through
            case NoExpose:
                //  Fall-through
            case Expose:
            {
                dish::GRAPH_EventProcessor::Instance().InvokeRedrawEvent(
                    e.xexpose.x,
                    e.xexpose.y,
                    e.xexpose.x + e.xexpose.width,
                    e.xexpose.y + e.xexpose.height
                );
            } break;
            
            case MappingNotify:
            {
                switch(e.xmapping.request)
                {
                    case MappingModifier:
                        //  Fall-through
                    case MappingKeyboard:
                    {
                        XRefreshKeyboardMapping(&e.xmapping);
                    } break;
                    
                    case MappingPointer:
                    {
                    } break;
                    
                    default:
                    {
                        //  Empty
                    }
                    
                }
            } break;
            
            case ResizeRequest:
            {
                dish::GRAPH_EventProcessor::Instance().InvokeResizeEvent(
                    e.xresizerequest.width,
                    e.xresizerequest.height
                );
            } break;
            
            case ButtonPress:
            {
                int button(-1);
                if(e.xbutton.button & Button1Mask)
                {
                    button = 0;
                }
                else if(e.xbutton.button & Button2Mask)
                {
                    button = 1;
                }
                else if(e.xbutton.button & Button3Mask)
                {
                    button = 2;
                }
                else if(e.xbutton.button & Button4Mask)
                {
                    button = 3;
                }
                else if(e.xbutton.button & Button5Mask)
                {
                    button = 4;
                }
            
                dish::GRAPH_EventProcessor::Instance().InvokeButtonPressEvent(
                    e.xbutton.x,
                    e.xbutton.y,
                    button,
                    (0 != (e.xbutton.state & ShiftMask)),
                    (0 != (e.xbutton.state & ControlMask)),
                    (0 != (e.xbutton.state & LockMask))
                );
            } break;
            
            case ButtonRelease:
            {
                int button(-1);
                if(e.xbutton.button & Button1Mask)
                {
                    button = 0;
                }
                else if(e.xbutton.button & Button2Mask)
                {
                    button = 1;
                }
                else if(e.xbutton.button & Button3Mask)
                {
                    button = 2;
                }
                else if(e.xbutton.button & Button4Mask)
                {
                    button = 3;
                }
                else if(e.xbutton.button & Button5Mask)
                {
                    button = 4;
                }
            
                dish::GRAPH_EventProcessor::Instance().InvokeButtonReleaseEvent(
                    e.xbutton.x,
                    e.xbutton.y,
                    button,
                    (0 != (e.xbutton.state & ShiftMask)),
                    (0 != (e.xbutton.state & ControlMask)),
                    (0 != (e.xbutton.state & LockMask))
                );
            } break;
            
            case KeyPress:
            {
                dish::GRAPH_EventProcessor::Instance().InvokeKeyPressEvent(
                    e.xkey.x,
                    e.xkey.y,
                    static_cast< int >(XLookupKeysym(&e.xkey, 0)),
                    (0 != (e.xkey.state & ShiftMask)),
                    (0 != (e.xkey.state & ControlMask)),
                    (0 != (e.xkey.state & LockMask))
                );
            } break;
        
            case KeyRelease:
            {
                dish::GRAPH_EventProcessor::Instance().InvokeKeyReleaseEvent(
                    e.xkey.x,
                    e.xkey.y,
                    static_cast< int >(XLookupKeysym(&e.xkey, 0)),
                    (0 != (e.xkey.state & ShiftMask)),
                    (0 != (e.xkey.state & ControlMask)),
                    (0 != (e.xkey.state & LockMask))
                );
            } break;
        
            default:
            {
                dish::GRAPH_EventProcessor::Instance().InvokeIdleEvent();
            }
            
        }
    }
    
#endif
    
    void ProcessEvent()
    {
#ifdef LANG_LIB_GRAPH    
        XEvent e;
        XNextEvent(gfxDisplay, &e);
        ProcessEvent(e);
#else
        assert(false);
#endif
    }

}

/******************************************************************************

    dish::GRAPH_EventProcessor::iEventProcessor class definitions

 ******************************************************************************/
 
bool dish::GRAPH_EventProcessor::iEventProcessor::ProcessIdleEvent()
{
#ifdef EVENT_TRACE
    std::cout << "    iEventProcessor::ProcessIdleEvent()" << std::endl;
#endif

    throw OperationNotSupportedException("No support to process IdleEvent.");
}
 
bool dish::GRAPH_EventProcessor::iEventProcessor::ProcessRedrawEvent(const int x0, const int y0, const int x1, const int y1)
{
#ifdef EVENT_TRACE
    std::cout << "    iEventProcessor::ProcessRedrawEvent()" << std::endl;
#endif

    throw OperationNotSupportedException("No support to process RedrawEvent.");
}

bool dish::GRAPH_EventProcessor::iEventProcessor::ProcessResizeEvent(const int newwidth, const int newheight)
{
#ifdef EVENT_TRACE
    std::cout << "    iEventProcessor::ProcessResizeEvent()" << std::endl;
#endif

    throw OperationNotSupportedException("No support to process ResizeEvent.");
}

bool dish::GRAPH_EventProcessor::iEventProcessor::ProcessKeyPressEvent(const int x, const int y, const int ch, const bool shiftst, const bool ctrlst, const bool altst)
{
#ifdef EVENT_TRACE
    std::cout << "    iEventProcessor::ProcessKeyPressEvent()" << std::endl;
#endif

    throw OperationNotSupportedException("No support to process KeyPressEvent.");
}

bool dish::GRAPH_EventProcessor::iEventProcessor::ProcessKeyReleaseEvent(const int x, const int y, const int ch, const bool shiftst, const bool ctrlst, const bool altst)
{
#ifdef EVENT_TRACE
    std::cout << "    iEventProcessor::ProcessKeyReleaseEvent()" << std::endl;
#endif

    throw OperationNotSupportedException("No support to process KeyReleaseEvent.");
}

bool dish::GRAPH_EventProcessor::iEventProcessor::ProcessButtonPressEvent(const int x, const int y, const int button, const bool shiftst, const bool ctrlst, const bool altst)
{
#ifdef EVENT_TRACE
    std::cout << "    iEventProcessor::ProcessButtonPressEvent()" << std::endl;
#endif

    throw OperationNotSupportedException("No support to process ButtonPressEvent.");
}

bool dish::GRAPH_EventProcessor::iEventProcessor::ProcessButtonReleaseEvent(const int x, const int y, const int button, const bool shiftst, const bool ctrlst, const bool altst)
{
#ifdef EVENT_TRACE
    std::cout << "    iEventProcessor::ProcessButtonReleaseEvent()" << std::endl;
#endif

    throw OperationNotSupportedException("No support to process ButtonReleaseEvent.");
}

/******************************************************************************

    dish::GRAPH_EventProcessor class definitions

 ******************************************************************************/
 
const bool dish::GRAPH_EventProcessor::EVENT_CONTINUE(true);
const bool dish::GRAPH_EventProcessor::EVENT_TERMINATE(false);

bool dish::GRAPH_EventProcessor::InvokeIdleEvent()
{
#ifdef EVENT_TRACE
    std::cout << "    GRAPH_EventProcessor::InvokeIdleEvent()" << std::endl;
#endif

    CallbackStackT &callback_set(mCallbackTable.at(eventNull));
    
    bool terminate(EVENT_CONTINUE);
    
    std::for_each(
        callback_set.begin(), callback_set.end(),
        [&](CallbackStackT::value_type &callback)
        {
            if(EVENT_TERMINATE == (callback->ProcessIdleEvent()))
            {
                terminate = EVENT_TERMINATE;
            }
        }
    );
    
    return terminate;
}

bool dish::GRAPH_EventProcessor::InvokeRedrawEvent(const int x0, const int y0, const int x1, const int y1)
{
#ifdef EVENT_TRACE
    std::cout << "    GRAPH_EventProcessor::InvokeRedrawEvent()" << std::endl;
#endif

    CallbackStackT &callback_set(mCallbackTable.at(eventRedraw));
    
    bool terminate(EVENT_CONTINUE);
    
    std::for_each(
        callback_set.begin(), callback_set.end(),
        [&](CallbackStackT::value_type &callback)
        {
            if(EVENT_TERMINATE == (callback->ProcessRedrawEvent(x0, y0, x1, y1)))
            {
                terminate = EVENT_TERMINATE;
            }
        }
    );
    
    return terminate;
}

bool dish::GRAPH_EventProcessor::InvokeResizeEvent(const int newwidth, const int newheight)
{
#ifdef EVENT_TRACE
    std::cout << "    GRAPH_EventProcessor::InvokeResizeEvent()" << std::endl;
#endif

    CallbackStackT &callback_set(mCallbackTable.at(eventResize));
    
    bool terminate(EVENT_CONTINUE);
    
    std::for_each(
        callback_set.begin(), callback_set.end(),
        [&](CallbackStackT::value_type &callback)
        {
            if(EVENT_TERMINATE == (callback->ProcessResizeEvent(newwidth, newheight)))
            {
                terminate = EVENT_TERMINATE;
            }
        }
    );
    
    return terminate;
}

bool dish::GRAPH_EventProcessor::InvokeKeyPressEvent(const int x, const int y, const int ch, const bool shiftst, const bool ctrlst, const bool altst)
{
#ifdef EVENT_TRACE
    std::cout << "    GRAPH_EventProcessor::InvokeKeyPressEvent()" << std::endl;
#endif

    CallbackStackT &callback_set(mCallbackTable.at(eventKeyPress));
    
    bool terminate(EVENT_CONTINUE);
    
    std::for_each(
        callback_set.begin(), callback_set.end(),
        [&](CallbackStackT::value_type &callback)
        {
            if(EVENT_TERMINATE == (callback->ProcessKeyPressEvent(x, y, ch, shiftst, ctrlst, altst)))
            {
                terminate = EVENT_TERMINATE;
            }
        }
    );
    
    return terminate;
}

bool dish::GRAPH_EventProcessor::InvokeKeyReleaseEvent(const int x, const int y, const int ch, const bool shiftst, const bool ctrlst, const bool altst)
{
#ifdef EVENT_TRACE
    std::cout << "    GRAPH_EventProcessor::InvokeKeyReleaseEvent()" << std::endl;
#endif

    CallbackStackT &callback_set(mCallbackTable.at(eventKeyRelease));
    
    bool terminate(EVENT_CONTINUE);
    
    std::for_each(
        callback_set.begin(), callback_set.end(),
        [&](CallbackStackT::value_type &callback)
        {
            if(EVENT_TERMINATE == (callback->ProcessKeyReleaseEvent(x, y, ch, shiftst, ctrlst, altst)))
            {
                terminate = EVENT_TERMINATE;
            }
        }
    );
    
    return terminate;
}

bool dish::GRAPH_EventProcessor::InvokeButtonPressEvent(const int x, const int y, const int button, const bool shiftst, const bool ctrlst, const bool altst)
{
#ifdef EVENT_TRACE
    std::cout << "    GRAPH_EventProcessor::InvokeButtonPressEvent()" << std::endl;
#endif

    CallbackStackT &callback_set(mCallbackTable.at(eventButtonPress));
    
    bool terminate(EVENT_CONTINUE);
    
    std::for_each(
        callback_set.begin(), callback_set.end(),
        [&](CallbackStackT::value_type &callback)
        {
            if(EVENT_TERMINATE == (callback->ProcessButtonPressEvent(x, y, button, shiftst, ctrlst, altst)))
            {
                terminate = EVENT_TERMINATE;
            }
        }
    );
    
    return terminate;
}

bool dish::GRAPH_EventProcessor::InvokeButtonReleaseEvent(const int x, const int y, const int button, const bool shiftst, const bool ctrlst, const bool altst)
{
#ifdef EVENT_TRACE
    std::cout << "    GRAPH_EventProcessor::InvokeButtonReleaseEvent()" << std::endl;
#endif

    CallbackStackT &callback_set(mCallbackTable.at(eventButtonRelease));
    
    bool terminate(EVENT_CONTINUE);
    
    std::for_each(
        callback_set.begin(), callback_set.end(),
        [&](CallbackStackT::value_type &callback)
        {
            if(EVENT_TERMINATE == (callback->ProcessButtonReleaseEvent(x, y, button, shiftst, ctrlst, altst)))
            {
                terminate = EVENT_TERMINATE;
            }
        }
    );
    
    return terminate;
}

dish::GRAPH_EventProcessor &dish::GRAPH_EventProcessor::Instance()
{
    static GRAPH_EventProcessor instance;
    
    return instance;
}

/******************************************************************************

    Constant definitions

 ******************************************************************************/

const dish::IntegerT dish::GRAPH_FillStyle_SOLID(
#ifdef LANG_LIB_GRAPH
    static_cast< dish::IntegerT >(FillSolid)
#else
    -1
#endif
);

const dish::IntegerT dish::GRAPH_FillStyle_TILED(
#ifdef LANG_LIB_GRAPH
    static_cast< dish::IntegerT >(FillTiled)
#else
    -1
#endif
);

const dish::IntegerT dish::GRAPH_FillStyle_OPAQUE_STIPPLED(
#ifdef LANG_LIB_GRAPH
    static_cast< dish::IntegerT >(FillOpaqueStippled)
#else
    -1
#endif
);

const dish::IntegerT dish::GRAPH_FillStyle_STIPPLED(
#ifdef LANG_LIB_GRAPH
    static_cast< dish::IntegerT >(FillStippled)
#else
    -1
#endif
);

const dish::IntegerT dish::GRAPH_LineStyle_SOLID(
#ifdef LANG_LIB_GRAPH
    static_cast< dish::IntegerT >(LineSolid)
#else
    -1
#endif
);

const dish::IntegerT dish::GRAPH_LineStyle_DASHED(
#ifdef LANG_LIB_GRAPH
    static_cast< dish::IntegerT >(LineOnOffDash)
#else
    -1
#endif
);

const dish::IntegerT dish::GRAPH_LineStyle_DOUBLE_DASHED(
#ifdef LANG_LIB_GRAPH
    static_cast< dish::IntegerT >(LineDoubleDash)
#else
    -1
#endif
);
    
const dish::IntegerT dish::GRAPH_LineCap_NOT_LAST(
#ifdef LANG_LIB_GRAPH
    static_cast< dish::IntegerT >(CapNotLast)
#else
    -1
#endif
);

const dish::IntegerT dish::GRAPH_LineCap_BUTT(
#ifdef LANG_LIB_GRAPH
    static_cast< dish::IntegerT >(CapButt)
#else
    -1
#endif
);

const dish::IntegerT dish::GRAPH_LineCap_ROUND(
#ifdef LANG_LIB_GRAPH
    static_cast< dish::IntegerT >(CapRound)
#else
    -1
#endif
);

const dish::IntegerT dish::GRAPH_LineCap_PROJECTING(
#ifdef LANG_LIB_GRAPH
    static_cast< dish::IntegerT >(CapProjecting)
#else
    -1
#endif
);
    
const dish::IntegerT dish::GRAPH_LineJoin_MITRE(
#ifdef LANG_LIB_GRAPH
    static_cast< dish::IntegerT >(JoinMiter)
#else
    -1
#endif
);

const dish::IntegerT dish::GRAPH_LineJoin_ROUND(
#ifdef LANG_LIB_GRAPH
    static_cast< dish::IntegerT >(JoinRound)
#else
    -1
#endif
);

const dish::IntegerT dish::GRAPH_LineJoin_BEVEL(
#ifdef LANG_LIB_GRAPH
    static_cast< dish::IntegerT >(JoinBevel)
#else
    -1
#endif
);

const dish::IntegerT dish::GRAPH_CHAR_ESC(static_cast< dish::IntegerT >(65307));
const dish::IntegerT dish::GRAPH_CHAR_DOWN(static_cast< dish::IntegerT >(65364));
const dish::IntegerT dish::GRAPH_CHAR_UP(static_cast< dish::IntegerT >(65362));
const dish::IntegerT dish::GRAPH_CHAR_LEFT(static_cast< dish::IntegerT >(65361));
const dish::IntegerT dish::GRAPH_CHAR_RIGHT(static_cast< dish::IntegerT >(65363));
const dish::IntegerT dish::GRAPH_CHAR_HOME(static_cast< dish::IntegerT >(65360));
const dish::IntegerT dish::GRAPH_CHAR_END(static_cast< dish::IntegerT >(65367));
const dish::IntegerT dish::GRAPH_CHAR_BACKSPACE(static_cast< dish::IntegerT >(65288));
const dish::IntegerT dish::GRAPH_CHAR_F1(static_cast< dish::IntegerT >(65470));
const dish::IntegerT dish::GRAPH_CHAR_F2(static_cast< dish::IntegerT >(65471));
const dish::IntegerT dish::GRAPH_CHAR_F3(static_cast< dish::IntegerT >(65472));
const dish::IntegerT dish::GRAPH_CHAR_F4(static_cast< dish::IntegerT >(65473));
const dish::IntegerT dish::GRAPH_CHAR_F5(static_cast< dish::IntegerT >(65474));
const dish::IntegerT dish::GRAPH_CHAR_F6(static_cast< dish::IntegerT >(65475));
const dish::IntegerT dish::GRAPH_CHAR_F7(static_cast< dish::IntegerT >(65476));
const dish::IntegerT dish::GRAPH_CHAR_F8(static_cast< dish::IntegerT >(65477));
const dish::IntegerT dish::GRAPH_CHAR_F9(static_cast< dish::IntegerT >(65478));
const dish::IntegerT dish::GRAPH_CHAR_F10(static_cast< dish::IntegerT >(65479));
const dish::IntegerT dish::GRAPH_CHAR_F11(static_cast< dish::IntegerT >(65480));
const dish::IntegerT dish::GRAPH_CHAR_F12(static_cast< dish::IntegerT >(65481));
const dish::IntegerT dish::GRAPH_CHAR_DELETE(static_cast< dish::IntegerT >(0xff9f));
const dish::IntegerT dish::GRAPH_CHAR_INSERT(static_cast< dish::IntegerT >(0xff9e));

const double dish::GRAPH_PI(std::acos(-1.0));

bool dish::GRAPH_IsStarted()
{
#ifdef LANG_LIB_GRAPH
    return IsStarted();
#else
    return false;
#endif
}

void dish::GRAPH_EnsureGraphicsStarted()
{
    EnsureGraphicsStarted();
}

void dish::GRAPH_Start(const int xsize, const int ysize, const char * const title)
{
#ifdef LANG_LIB_GRAPH

    assert(xsize > 0);
    assert(ysize > 0);
    assert(0 != title);

    if(!IsStarted())
    {
        XSize = xsize;
        YSize = ysize;
    
        gfxDisplay = XOpenDisplay(0);
        if(0 == gfxDisplay)
        {
            throw GraphicsFailureException("Unable to open the graphics window.");
        }

        {
            const int blackColor(BlackPixel(gfxDisplay, DefaultScreen(gfxDisplay)));
            gfxWindow = XCreateSimpleWindow(
                gfxDisplay,
                DefaultRootWindow(gfxDisplay),
                0,
                0,
                XSize,
                YSize,
                0,
                blackColor,
                blackColor
            );
        }

        {
            XSetWindowAttributes attr;
            attr.backing_store = Always;

            XChangeWindowAttributes(gfxDisplay, gfxWindow, CWBackingStore, &attr);
        }

        XStoreName(gfxDisplay, gfxWindow, title);

        XSelectInput(
            gfxDisplay,
            gfxWindow,
            ResizeRedirectMask | StructureNotifyMask | ExposureMask | KeyPressMask | ButtonPressMask
        );

        XMapWindow(gfxDisplay, gfxWindow);

        gfxGc = XCreateGC(gfxDisplay, gfxWindow, 0, 0);
        
        gfxFontName = "fixed";
        gfxFont = XLoadQueryFont(gfxDisplay, gfxFontName.c_str());
        assert(NULL != gfxFont);

        XSetForeground(
            gfxDisplay,
            gfxGc,
            WhitePixel(gfxDisplay, DefaultScreen(gfxDisplay))
        );
        
        XSetWindowBackground(
            gfxDisplay,
            gfxWindow,
            BlackPixel(gfxDisplay, DefaultScreen(gfxDisplay))
        );

        // Wait for the MapNotify event
        for(bool done(false); !done; )
        {
            XEvent e;
            XNextEvent(gfxDisplay, &e);
            if(e.type == MapNotify)
            {
                done = true;
            }
        }
    }
    
#else
    throw GraphicsFailureException("Unable to open the graphics window.");
#endif
}

void dish::GRAPH_End()
{
#ifdef LANG_LIB_GRAPH
    if(IsStarted())
    {
        XSize = -1;
        YSize = -1;
    
        XCloseDisplay(gfxDisplay);
        gfxDisplay = 0;
    }
#endif
}

void dish::GRAPH_ProcessEvent()
{
    EnsureGraphicsStarted();
    ProcessEvent();
}

void dish::GRAPH_Refresh()
{
    EnsureGraphicsStarted();

#ifdef LANG_LIB_GRAPH    
    XFlush(gfxDisplay);
#else
    assert(false);
#endif
}

bool dish::GRAPH_KeyPressed()
{
    GRAPH_Refresh();
      
    bool result(false);
    
#ifdef LANG_LIB_GRAPH
    XEvent event;
    if(XCheckMaskEvent(gfxDisplay, -1, &event))
    {
        if(KeyPress == event.type)
        {
            result = true;
        }
        else
        {
            ProcessEvent(event);
        }
    }
#else
    assert(false);
#endif
    
    return result;
}

int dish::GRAPH_GetKey()
{
    GRAPH_Refresh();
    
#ifdef LANG_LIB_GRAPH
    for(XEvent event; true; )
    {
        XNextEvent(gfxDisplay, &event);
        
        if(KeyPress == event.type)
        {
            return static_cast< int >(XLookupKeysym(&event.xkey, 0));
        }
        else
        {
            ProcessEvent(event);
        }
    }

    assert(false);
#else
    assert(false);
#endif
}

void dish::GRAPH_SetForeColor(const int color)
{
    EnsureGraphicsStarted();
    
#ifdef LANG_LIB_GRAPH
    XSetForeground(gfxDisplay, gfxGc, color);
#else
    assert(false);
#endif
}

void dish::GRAPH_SetBackColor(const int color)
{
    EnsureGraphicsStarted();
    
#ifdef LANG_LIB_GRAPH
    XSetWindowBackground(gfxDisplay, gfxWindow, color);
#else
    assert(false);
#endif
}

void dish::GRAPH_SetFillStyle(const int fillstyle)
{
    EnsureGraphicsStarted();
    
#ifdef LANG_LIB_GRAPH
    XSetFillStyle(gfxDisplay, gfxGc, fillstyle);
#else
    assert(false);
#endif
}

void dish::GRAPH_SetLineStyle(const int linewidth, const int linestyle, const int linecapstyle, const int linejoinstyle)
{
    EnsureGraphicsStarted();
    
#ifdef LANG_LIB_GRAPH
    XSetLineAttributes(gfxDisplay, gfxGc, linewidth, linestyle, linecapstyle, linejoinstyle);
#else
    assert(false);
#endif
}

void dish::GRAPH_Clear()
{
    EnsureGraphicsStarted();
    
#ifdef LANG_LIB_GRAPH
    XClearWindow(gfxDisplay, gfxWindow);
#else
    assert(false);
#endif
}

void dish::GRAPH_DrawPixel(const int x, const int y)
{
    assert(x >= 0);
    assert(y >= 0);
    
    EnsureGraphicsStarted();
    
#ifdef LANG_LIB_GRAPH
    XDrawPoint(gfxDisplay, gfxWindow, gfxGc, x, y);
#else
    assert(false);
#endif
}

void dish::GRAPH_DrawLine(const int x0, const int y0, const int x1, const int y1)
{
    assert(x0 >= 0);
    assert(y0 >= 0);
    assert(x1 >= 0);
    assert(y1 >= 0);
    
    EnsureGraphicsStarted();
    
#ifdef LANG_LIB_GRAPH
    XDrawLine(gfxDisplay, gfxWindow, gfxGc, x0, y0, x1, y1);
#else
    assert(false);
#endif
}

void dish::GRAPH_DrawBox(const int x0, const int y0, const int x1, const int y1, const bool fill)
{
    assert(x0 >= 0);
    assert(y0 >= 0);
    assert(x1 >= 0);
    assert(y1 >= 0);
    
    EnsureGraphicsStarted();
    
#ifdef LANG_LIB_GRAPH
    int minx(x0);
    int maxx(x1);
    if(maxx < minx)
    {
        std::swap(minx, maxx);
    }
    
    int miny(y0);
    int maxy(y1);
    if(maxy < miny)
    {
        std::swap(miny, maxy);
    }
    
    const int offset(!fill ? 0 : 1);
    
    (!fill ? XDrawRectangle : XFillRectangle)(
        gfxDisplay,
        gfxWindow,
        gfxGc,
        minx,
        miny,
        maxx - minx + offset,
        maxy - miny + offset
    );
#else
    assert(false);
#endif
}

void dish::GRAPH_DrawArc(const int x0, const int y0, const int x1, const int y1, const double startang, const double endang, const bool fill)
{
    assert(x0 >= 0);
    assert(y0 >= 0);
    assert(x1 >= 0);
    assert(y1 >= 0);
    
    EnsureGraphicsStarted();
    
#ifdef LANG_LIB_GRAPH
    int minx(x0);
    int maxx(x1);
    if(maxx < minx)
    {
        std::swap(minx, maxx);
    }
    
    int miny(y0);
    int maxy(y1);
    if(maxy < miny)
    {
        std::swap(miny, maxy);
    }
    
    (!fill ? XDrawArc : XFillArc)(
        gfxDisplay,
        gfxWindow,
        gfxGc,
        minx,
        miny,
        maxx - minx,
        maxy - miny,
        static_cast< int >((startang / (2.0 * GRAPH_PI)) * 360.0 * 64.0 + 0.5),
        static_cast< int >((endang / (2.0 * GRAPH_PI)) * 360.0 * 64.0 + 0.5)
    );
#else
    assert(false);
#endif
}

void dish::GRAPH_DrawPolygon(dish::GRAPH_PointT * const polygon, const int npoints, const bool fill)
{
    assert(0 != polygon);
    
    EnsureGraphicsStarted();
    
#ifdef LANG_LIB_GRAPH
    if(npoints > 0)
    {
        if(!fill)
        {
            XDrawLines(gfxDisplay, gfxWindow, gfxGc, reinterpret_cast< XPoint * >(polygon), npoints, CoordModeOrigin);
        }
        else
        {
            XFillPolygon(gfxDisplay, gfxWindow, gfxGc, reinterpret_cast< XPoint * >(polygon), npoints, Nonconvex, CoordModeOrigin);
        }
    }
#else
    assert(false);
#endif
}

char **dish::GRAPH_GetFontList(int * const nfonts)
{
    assert(0 != nfonts);

    EnsureGraphicsStarted();
    
#ifdef LANG_LIB_GRAPH
    return XListFonts(gfxDisplay, "*", INT_MAX, nfonts);
#else
    assert(false);
#endif
}

void dish::GRAPH_FreeFontList(char **fontlist)
{
    EnsureGraphicsStarted();
    
#ifdef LANG_LIB_GRAPH
    XFreeFontNames(fontlist);
#else
    assert(false);
#endif
}

const std::string &dish::GRAPH_SetFont(const std::string &font)
{
    EnsureGraphicsStarted();
    
#ifdef LANG_LIB_GRAPH
    if(font != gfxFontName)
    {
        XFreeFont(gfxDisplay, gfxFont);
        
        gfxFontName = font;
        gfxFont = XLoadQueryFont(gfxDisplay, gfxFontName.c_str());
        
        if(NULL == gfxFont)
        {
            gfxFontName = "fixed";
            gfxFont = XLoadQueryFont(gfxDisplay, gfxFontName.c_str());
            assert(NULL != gfxFont);
        }
    }

    return gfxFontName;
#else
    assert(false);
#endif
}

void dish::GRAPH_DrawText(const int x, const int y, const dish::StringT &text)
{
    assert(x >= 0);
    assert(y >= 0);
    
    EnsureGraphicsStarted();
    
#ifdef LANG_LIB_GRAPH
    XDrawString(gfxDisplay, gfxWindow, gfxGc, x, y, text.c_str(), text.length());
#else
    assert(false);
#endif
}

void dish::GRAPH_TextExtents(const dish::StringT &text, int &width, int &height)
{
    EnsureGraphicsStarted();
    
#ifdef LANG_LIB_GRAPH
    width = XTextWidth(gfxFont, text.c_str(), text.length());
    height = gfxFont->ascent + gfxFont->descent;
#else
    assert(false);
#endif
}

