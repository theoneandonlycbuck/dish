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

#ifndef DISH_GRAPH_H
#define DISH_GRAPH_H

#include "dishconfig.h"

#include <stdint.h>

#include <algorithm>
#include <cassert>
#include <list>
#include <memory>
#include <vector>

#include "inline.h"
#include "types.h"

namespace dish
{

    ////////////////////////////////////////////////////////////////////////////
    
    class GRAPH_EventProcessor
    {
        public:
        
            using EventT = enum
            {
                eventNull = 0,
                
                eventRedraw,
                
                eventResize,
                
                eventKeyPress,
                eventKeyRelease,
                
                eventButtonPress,
                eventButtonRelease,
                
                eventNUM
            };
        
            class iEventProcessor
            {
                public:
                    virtual ~iEventProcessor() {};
              
                    virtual bool ProcessIdleEvent();
                    virtual bool ProcessRedrawEvent(const int x0, const int y0, const int x1, const int y1);
                    virtual bool ProcessResizeEvent(const int newwidth, const int newheight);
                    virtual bool ProcessKeyPressEvent(const int x, const int y, const int ch, const bool shiftst, const bool ctrlst, const bool altst);
                    virtual bool ProcessKeyReleaseEvent(const int x, const int y, const int ch, const bool shiftst, const bool ctrlst, const bool altst);
                    virtual bool ProcessButtonPressEvent(const int x, const int y, const int button, const bool shiftst, const bool ctrlst, const bool altst);
                    virtual bool ProcessButtonReleaseEvent(const int x, const int y, const int button, const bool shiftst, const bool ctrlst, const bool altst);
                      
            };
        
            typedef std::shared_ptr< iEventProcessor > CallbackT;
            typedef std::list< CallbackT > CallbackStackT;
            typedef std::vector< CallbackStackT > CallbackTableT;
        
        private:
            CallbackTableT mCallbackTable;
        
        protected:
            INLINE GRAPH_EventProcessor() : mCallbackTable(eventNUM) {};
        
        public:
        
            static const bool EVENT_CONTINUE;
            static const bool EVENT_TERMINATE;
            
            INLINE void Push(const EventT &event, std::shared_ptr< iEventProcessor > exe) { assert(0 != exe.get()); mCallbackTable.at(event).push_back(exe); };
            bool InvokeIdleEvent();
            bool InvokeRedrawEvent(const int x0, const int y0, const int x1, const int y1);
            bool InvokeResizeEvent(const int newwidth, const int newheight);
            bool InvokeKeyPressEvent(const int x, const int y, const int ch, const bool shiftst, const bool ctrlst, const bool altst);
            bool InvokeKeyReleaseEvent(const int x, const int y, const int ch, const bool shiftst, const bool ctrlst, const bool altst);
            bool InvokeButtonPressEvent(const int x, const int y, const int button, const bool shiftst, const bool ctrlst, const bool altst);
            bool InvokeButtonReleaseEvent(const int x, const int y, const int button, const bool shiftst, const bool ctrlst, const bool altst);
            INLINE void Pop(const EventT &event) { CallbackStackT &callbacks(mCallbackTable.at(event)); if(!callbacks.empty()) { callbacks.pop_back(); } };
        
            static GRAPH_EventProcessor &Instance();
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    extern const IntegerT GRAPH_FillStyle_SOLID;
    extern const IntegerT GRAPH_FillStyle_TILED;
    extern const IntegerT GRAPH_FillStyle_OPAQUE_STIPPLED;
    extern const IntegerT GRAPH_FillStyle_STIPPLED;
    
    extern const IntegerT GRAPH_LineStyle_SOLID;
    extern const IntegerT GRAPH_LineStyle_DASHED;
    extern const IntegerT GRAPH_LineStyle_DOUBLE_DASHED;
    
    extern const IntegerT GRAPH_LineCap_NOT_LAST;
    extern const IntegerT GRAPH_LineCap_BUTT;
    extern const IntegerT GRAPH_LineCap_ROUND;
    extern const IntegerT GRAPH_LineCap_PROJECTING;
    
    extern const IntegerT GRAPH_LineJoin_MITRE;
    extern const IntegerT GRAPH_LineJoin_ROUND;
    extern const IntegerT GRAPH_LineJoin_BEVEL;
    
    extern const IntegerT GRAPH_CHAR_ESC;
    extern const IntegerT GRAPH_CHAR_DOWN;
    extern const IntegerT GRAPH_CHAR_UP;
    extern const IntegerT GRAPH_CHAR_LEFT;
    extern const IntegerT GRAPH_CHAR_RIGHT;
    extern const IntegerT GRAPH_CHAR_HOME;
    extern const IntegerT GRAPH_CHAR_END;
    extern const IntegerT GRAPH_CHAR_BACKSPACE;
    extern const IntegerT GRAPH_CHAR_F1;
    extern const IntegerT GRAPH_CHAR_F2;
    extern const IntegerT GRAPH_CHAR_F3;
    extern const IntegerT GRAPH_CHAR_F4;
    extern const IntegerT GRAPH_CHAR_F5;
    extern const IntegerT GRAPH_CHAR_F6;
    extern const IntegerT GRAPH_CHAR_F7;
    extern const IntegerT GRAPH_CHAR_F8;
    extern const IntegerT GRAPH_CHAR_F9;
    extern const IntegerT GRAPH_CHAR_F10;
    extern const IntegerT GRAPH_CHAR_F11;
    extern const IntegerT GRAPH_CHAR_F12;
    extern const IntegerT GRAPH_CHAR_DELETE;
    extern const IntegerT GRAPH_CHAR_INSERT;

    ////////////////////////////////////////////////////////////////////////////
    
    extern bool GRAPH_IsStarted();
    extern void GRAPH_EnsureGraphicsStarted();
    
    extern void GRAPH_Start(const int xsize, const int ysize, const char * const title);
    extern void GRAPH_End();
    
    extern void GRAPH_ProcessEvent();
    
    extern void GRAPH_Refresh();

    ////////////////////////////////////////////////////////////////////////////
    
    extern bool GRAPH_KeyPressed();
    extern int GRAPH_GetKey();

    ////////////////////////////////////////////////////////////////////////////
    
    extern const double GRAPH_PI;
    
    INLINEC constexpr int GRAPH_MakeColorRGB(const uint8_t red, const uint8_t green, const uint8_t blue)
    {
        return ((static_cast< int >(red) << 16) | (static_cast< int >(green) << 8) | static_cast< int >(blue));
    }
    
    INLINEC int GRAPH_MakeColorRGB(const double &red, const double &green, const double &blue)
    {
        return GRAPH_MakeColorRGB(
           static_cast< uint8_t >(std::max(std::min(static_cast< int >((255.0 * red) + 0.5), 0xFF), 0x00)),
           static_cast< uint8_t >(std::max(std::min(static_cast< int >((255.0 * green) + 0.5), 0xFF), 0x00)),
           static_cast< uint8_t >(std::max(std::min(static_cast< int >((255.0 * blue) + 0.5), 0xFF), 0x00))
        );
    }
    
    extern void GRAPH_SetForeColor(const int color);
    extern void GRAPH_SetBackColor(const int color);
    
    extern void GRAPH_SetFillStyle(const int fillstyle);
    extern void GRAPH_SetLineStyle(const int linewidth, const int linestyle, const int linecapstyle, const int linejoinstyle);

    ////////////////////////////////////////////////////////////////////////////
    
    extern void GRAPH_Clear();
    
    extern void GRAPH_DrawPixel(const int x, const int y);
    extern void GRAPH_DrawLine(const int x0, const int y0, const int x1, const int y1);
    
    extern void GRAPH_DrawBox(const int x0, const int y0, const int x1, const int y1, const bool fill);
    extern void GRAPH_DrawArc(const int x0, const int y0, const int x1, const int y1, const double startang, const double endang, const bool fill);
    
    typedef struct
    {
        short int x;
        short int y;
    } GRAPH_PointT;
    extern void GRAPH_DrawPolygon(GRAPH_PointT * const polygon, const int npoints, const bool fill);
    
    extern char **GRAPH_GetFontList(int * const nfonts);
    extern void GRAPH_FreeFontList(char **fontlist);
    extern const std::string &GRAPH_SetFont(const std::string &font);
    
    extern void GRAPH_DrawText(const int x, const int y, const StringT &text);
    extern void GRAPH_TextExtents(const StringT &text, int &width, int &height);

    ////////////////////////////////////////////////////////////////////////////
    
}

#endif

