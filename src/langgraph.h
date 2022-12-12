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

#ifndef DISH_LANGGRAPH_H
#define DISH_LANGGRAPH_H

#include "dishconfig.h"

#include <memory>

#include "atomics.h"
#include "inline.h"
#include "types.h"

namespace dish
{

    ////////////////////////////////////////////////////////////////////////////
    
    class LanguageSymbolTable;

    ////////////////////////////////////////////////////////////////////////////
    
    extern std::shared_ptr< iAtomic > GRAPH_CreateGraphicsContextType();
    
    extern std::shared_ptr< iAtomic > GRAPH_CreateIntegerPointType();
    extern std::shared_ptr< iAtomic > GRAPH_CreateRealPointType();
    
    extern std::shared_ptr< iAtomic > GRAPH_CreateIntegerLineType();
    extern std::shared_ptr< iAtomic > GRAPH_CreateRealLineType();

    ////////////////////////////////////////////////////////////////////////////
    
    class GRAPH_CreateContext2Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_CreateContext2Function() : ExecutableAtomic() 
            {
                addParam("xsize", REFERENCE_PARAMETER); 
                addParam("ysize", REFERENCE_PARAMETER); 
            };
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_CreateContext2Function > MakeValue() { return std::shared_ptr< GRAPH_CreateContext2Function >(new GRAPH_CreateContext2Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };
    
    class GRAPH_CreateContext3Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_CreateContext3Function() : ExecutableAtomic() 
            {
                addParam("xsize", REFERENCE_PARAMETER); 
                addParam("ysize", REFERENCE_PARAMETER);
                
                addParam("title", REFERENCE_PARAMETER); 
            };
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_CreateContext3Function > MakeValue() { return std::shared_ptr< GRAPH_CreateContext3Function >(new GRAPH_CreateContext3Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class GRAPH_CreateContext7Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_CreateContext7Function() : ExecutableAtomic() 
            {
                addParam("xsize", REFERENCE_PARAMETER); 
                addParam("ysize", REFERENCE_PARAMETER);
                
                addParam("title", REFERENCE_PARAMETER); 
                
                addParam("ul_x", REFERENCE_PARAMETER);
                addParam("ul_y", REFERENCE_PARAMETER); 
                addParam("lr_x", REFERENCE_PARAMETER);
                addParam("lr_y", REFERENCE_PARAMETER);  
            };
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_CreateContext7Function > MakeValue() { return std::shared_ptr< GRAPH_CreateContext7Function >(new GRAPH_CreateContext7Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class GRAPH_CreatePointFunction : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_CreatePointFunction() : ExecutableAtomic() 
            {
                addParam("x", REFERENCE_PARAMETER); 
                addParam("y", REFERENCE_PARAMETER); 
            };
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_CreatePointFunction > MakeValue() { return std::shared_ptr< GRAPH_CreatePointFunction >(new GRAPH_CreatePointFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };
    
    class GRAPH_CreateLine2Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_CreateLine2Function() : ExecutableAtomic() 
            {
                addParam("pt0", REFERENCE_PARAMETER); 
                addParam("pt1", REFERENCE_PARAMETER); 
            };
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_CreateLine2Function > MakeValue() { return std::shared_ptr< GRAPH_CreateLine2Function >(new GRAPH_CreateLine2Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };
    
    class GRAPH_CreateLine4Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_CreateLine4Function() : ExecutableAtomic() 
            {
                addParam("x0", REFERENCE_PARAMETER); 
                addParam("y0", REFERENCE_PARAMETER);
                addParam("x1", REFERENCE_PARAMETER); 
                addParam("y1", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_CreateLine4Function > MakeValue() { return std::shared_ptr< GRAPH_CreateLine4Function >(new GRAPH_CreateLine4Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    ////////////////////////////////////////////////////////////////////////////

    class GRAPH_StartFunction : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_StartFunction() : ExecutableAtomic() { addParam("context", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_StartFunction > MakeValue() { return std::shared_ptr< GRAPH_StartFunction >(new GRAPH_StartFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class GRAPH_IsStartedFunction : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_IsStartedFunction() : ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_IsStartedFunction > MakeValue() { return std::shared_ptr< GRAPH_IsStartedFunction >(new GRAPH_IsStartedFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class GRAPH_EndFunction : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_EndFunction() : ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_EndFunction > MakeValue() { return std::shared_ptr< GRAPH_EndFunction >(new GRAPH_EndFunction()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class GRAPH_PushEventProcessorFunction : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_PushEventProcessorFunction() : ExecutableAtomic() { addParam("event", REFERENCE_PARAMETER); addParam("procF", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_PushEventProcessorFunction > MakeValue() { return std::shared_ptr< GRAPH_PushEventProcessorFunction >(new GRAPH_PushEventProcessorFunction()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class GRAPH_PopEventProcessorFunction : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_PopEventProcessorFunction() : ExecutableAtomic() { addParam("event", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_PopEventProcessorFunction > MakeValue() { return std::shared_ptr< GRAPH_PopEventProcessorFunction >(new GRAPH_PopEventProcessorFunction()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class GRAPH_ProcessEventFunction : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_ProcessEventFunction() : ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_ProcessEventFunction > MakeValue() { return std::shared_ptr< GRAPH_ProcessEventFunction >(new GRAPH_ProcessEventFunction()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class GRAPH_ProcessEvent1Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_ProcessEvent1Function() : ExecutableAtomic() { addParam("event", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_ProcessEvent1Function > MakeValue() { return std::shared_ptr< GRAPH_ProcessEvent1Function >(new GRAPH_ProcessEvent1Function()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class GRAPH_EventLoopFunction : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_EventLoopFunction() : ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_EventLoopFunction > MakeValue() { return std::shared_ptr< GRAPH_EventLoopFunction >(new GRAPH_EventLoopFunction()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class GRAPH_EventLoop1Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_EventLoop1Function() : ExecutableAtomic() { addParam("done", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_EventLoop1Function > MakeValue() { return std::shared_ptr< GRAPH_EventLoop1Function >(new GRAPH_EventLoop1Function()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class GRAPH_RefreshFunction : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_RefreshFunction() : ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_RefreshFunction > MakeValue() { return std::shared_ptr< GRAPH_RefreshFunction >(new GRAPH_RefreshFunction()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    ////////////////////////////////////////////////////////////////////////////

    class GRAPH_MakeColorFunction : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_MakeColorFunction() : ExecutableAtomic() { addParam("context", REFERENCE_PARAMETER); addParam("red", REFERENCE_PARAMETER); addParam("green", REFERENCE_PARAMETER); addParam("blue", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_MakeColorFunction > MakeValue() { return std::shared_ptr< GRAPH_MakeColorFunction >(new GRAPH_MakeColorFunction()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class GRAPH_ApplyContextFunction : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_ApplyContextFunction() : ExecutableAtomic() { addParam("context", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_ApplyContextFunction > MakeValue() { return std::shared_ptr< GRAPH_ApplyContextFunction >(new GRAPH_ApplyContextFunction()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    ////////////////////////////////////////////////////////////////////////////

    class GRAPH_Clear1Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_Clear1Function() : ExecutableAtomic() { addParam("context", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_Clear1Function > MakeValue() { return std::shared_ptr< GRAPH_Clear1Function >(new GRAPH_Clear1Function()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class GRAPH_Clear2Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_Clear2Function() : ExecutableAtomic() { addParam("context", REFERENCE_PARAMETER); addParam("bgcolor", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_Clear2Function > MakeValue() { return std::shared_ptr< GRAPH_Clear2Function >(new GRAPH_Clear2Function()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    ////////////////////////////////////////////////////////////////////////////

    class GRAPH_DrawPixel2Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_DrawPixel2Function() : ExecutableAtomic() { addParam("context", REFERENCE_PARAMETER); addParam("pt", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_DrawPixel2Function > MakeValue() { return std::shared_ptr< GRAPH_DrawPixel2Function >(new GRAPH_DrawPixel2Function()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class GRAPH_DrawPixel3Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_DrawPixel3Function() : ExecutableAtomic() { addParam("context", REFERENCE_PARAMETER); addParam("x", REFERENCE_PARAMETER); addParam("y", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_DrawPixel3Function > MakeValue() { return std::shared_ptr< GRAPH_DrawPixel3Function >(new GRAPH_DrawPixel3Function()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    ////////////////////////////////////////////////////////////////////////////

    class GRAPH_DrawLine2Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_DrawLine2Function() : ExecutableAtomic()
            {
                addParam("context", REFERENCE_PARAMETER);
                addParam("line", REFERENCE_PARAMETER);
            }
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_DrawLine2Function > MakeValue() { return std::shared_ptr< GRAPH_DrawLine2Function >(new GRAPH_DrawLine2Function()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class GRAPH_DrawLine3Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_DrawLine3Function() : ExecutableAtomic()
            {
                addParam("context", REFERENCE_PARAMETER);
                addParam("pt0", REFERENCE_PARAMETER);
                addParam("pt1", REFERENCE_PARAMETER);
            }
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_DrawLine3Function > MakeValue() { return std::shared_ptr< GRAPH_DrawLine3Function >(new GRAPH_DrawLine3Function()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class GRAPH_DrawLine5Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_DrawLine5Function() : ExecutableAtomic()
            {
                addParam("context", REFERENCE_PARAMETER);
                addParam("x0", REFERENCE_PARAMETER);
                addParam("y0", REFERENCE_PARAMETER);
                addParam("x1", REFERENCE_PARAMETER);
                addParam("y1", REFERENCE_PARAMETER);
            }
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_DrawLine5Function > MakeValue() { return std::shared_ptr< GRAPH_DrawLine5Function >(new GRAPH_DrawLine5Function()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    ////////////////////////////////////////////////////////////////////////////

    class GRAPH_DrawLinesFunction : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_DrawLinesFunction() : ExecutableAtomic()
            {
                addParam("context", REFERENCE_PARAMETER);
                addParam("lines", REFERENCE_PARAMETER);
            }
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_DrawLinesFunction > MakeValue() { return std::shared_ptr< GRAPH_DrawLinesFunction >(new GRAPH_DrawLinesFunction()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    ////////////////////////////////////////////////////////////////////////////

    class GRAPH_DrawBox3Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_DrawBox3Function() : ExecutableAtomic()
            {
                addParam("context", REFERENCE_PARAMETER);
                addParam("pt0", REFERENCE_PARAMETER);
                addParam("pt1", REFERENCE_PARAMETER);
            }
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_DrawBox3Function > MakeValue() { return std::shared_ptr< GRAPH_DrawBox3Function >(new GRAPH_DrawBox3Function()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class GRAPH_DrawBox4Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_DrawBox4Function() : ExecutableAtomic()
            {
                addParam("context", REFERENCE_PARAMETER);
                addParam("pt0", REFERENCE_PARAMETER);
                addParam("pt1", REFERENCE_PARAMETER);
                addParam("fill", REFERENCE_PARAMETER);
            }
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_DrawBox4Function > MakeValue() { return std::shared_ptr< GRAPH_DrawBox4Function >(new GRAPH_DrawBox4Function()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class GRAPH_DrawBox5Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_DrawBox5Function() : ExecutableAtomic()
            {
                addParam("context", REFERENCE_PARAMETER);
                addParam("x0", REFERENCE_PARAMETER);
                addParam("y0", REFERENCE_PARAMETER);
                addParam("x1", REFERENCE_PARAMETER);
                addParam("y1", REFERENCE_PARAMETER);
            }
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_DrawBox5Function > MakeValue() { return std::shared_ptr< GRAPH_DrawBox5Function >(new GRAPH_DrawBox5Function()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class GRAPH_DrawBox6Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_DrawBox6Function() : ExecutableAtomic()
            {
                addParam("context", REFERENCE_PARAMETER);
                addParam("x0", REFERENCE_PARAMETER);
                addParam("y0", REFERENCE_PARAMETER);
                addParam("x1", REFERENCE_PARAMETER);
                addParam("y1", REFERENCE_PARAMETER);
                addParam("fill", REFERENCE_PARAMETER);
            }
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_DrawBox6Function > MakeValue() { return std::shared_ptr< GRAPH_DrawBox6Function >(new GRAPH_DrawBox6Function()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    ////////////////////////////////////////////////////////////////////////////

    class GRAPH_DrawArc5Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_DrawArc5Function() : ExecutableAtomic()
            {
                addParam("context", REFERENCE_PARAMETER);
                addParam("pt0", REFERENCE_PARAMETER);
                addParam("pt1", REFERENCE_PARAMETER);
                addParam("startang", REFERENCE_PARAMETER);
                addParam("endang", REFERENCE_PARAMETER);
            }
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_DrawArc5Function > MakeValue() { return std::shared_ptr< GRAPH_DrawArc5Function >(new GRAPH_DrawArc5Function()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class GRAPH_DrawArc6Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_DrawArc6Function() : ExecutableAtomic()
            {
                addParam("context", REFERENCE_PARAMETER);
                addParam("pt0", REFERENCE_PARAMETER);
                addParam("pt1", REFERENCE_PARAMETER);
                addParam("startang", REFERENCE_PARAMETER);
                addParam("endang", REFERENCE_PARAMETER);
                addParam("fill", REFERENCE_PARAMETER);
            }
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_DrawArc6Function > MakeValue() { return std::shared_ptr< GRAPH_DrawArc6Function >(new GRAPH_DrawArc6Function()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class GRAPH_DrawArc7Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_DrawArc7Function() : ExecutableAtomic()
            {
                addParam("context", REFERENCE_PARAMETER);
                addParam("x0", REFERENCE_PARAMETER);
                addParam("y0", REFERENCE_PARAMETER);
                addParam("x1", REFERENCE_PARAMETER);
                addParam("y1", REFERENCE_PARAMETER);
                addParam("startang", REFERENCE_PARAMETER);
                addParam("endang", REFERENCE_PARAMETER);
            }
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_DrawArc7Function > MakeValue() { return std::shared_ptr< GRAPH_DrawArc7Function >(new GRAPH_DrawArc7Function()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class GRAPH_DrawArc8Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_DrawArc8Function() : ExecutableAtomic()
            {
                addParam("context", REFERENCE_PARAMETER);
                addParam("x0", REFERENCE_PARAMETER);
                addParam("y0", REFERENCE_PARAMETER);
                addParam("x1", REFERENCE_PARAMETER);
                addParam("y1", REFERENCE_PARAMETER);
                addParam("startang", REFERENCE_PARAMETER);
                addParam("endang", REFERENCE_PARAMETER);
                addParam("fill", REFERENCE_PARAMETER);
            }
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_DrawArc8Function > MakeValue() { return std::shared_ptr< GRAPH_DrawArc8Function >(new GRAPH_DrawArc8Function()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    ////////////////////////////////////////////////////////////////////////////

    class GRAPH_DrawPolygon2Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_DrawPolygon2Function() : ExecutableAtomic()
            {
                addParam("context", REFERENCE_PARAMETER);
                addParam("points", REFERENCE_PARAMETER);
            }
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_DrawPolygon2Function > MakeValue() { return std::shared_ptr< GRAPH_DrawPolygon2Function >(new GRAPH_DrawPolygon2Function()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class GRAPH_DrawPolygon3Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_DrawPolygon3Function() : ExecutableAtomic()
            {
                addParam("context", REFERENCE_PARAMETER);
                addParam("points", REFERENCE_PARAMETER);
                addParam("fill", REFERENCE_PARAMETER);
            }
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_DrawPolygon3Function > MakeValue() { return std::shared_ptr< GRAPH_DrawPolygon3Function >(new GRAPH_DrawPolygon3Function()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    ////////////////////////////////////////////////////////////////////////////

    class GRAPH_GetFontList0Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_GetFontList0Function() : ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_GetFontList0Function > MakeValue() { return std::shared_ptr< GRAPH_GetFontList0Function >(new GRAPH_GetFontList0Function()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class GRAPH_GetTextDimensions3Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_GetTextDimensions3Function() : ExecutableAtomic()
            {
                addParam("context", REFERENCE_PARAMETER);
                addParam("text", REFERENCE_PARAMETER);
                addParam("pt", REFERENCE_PARAMETER);
            }
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_GetTextDimensions3Function > MakeValue() { return std::shared_ptr< GRAPH_GetTextDimensions3Function >(new GRAPH_GetTextDimensions3Function()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class GRAPH_GetTextDimensions4Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_GetTextDimensions4Function() : ExecutableAtomic()
            {
                addParam("context", REFERENCE_PARAMETER);
                addParam("text", REFERENCE_PARAMETER);
                addParam("width", REFERENCE_PARAMETER);
                addParam("height", REFERENCE_PARAMETER);
            }
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_GetTextDimensions4Function > MakeValue() { return std::shared_ptr< GRAPH_GetTextDimensions4Function >(new GRAPH_GetTextDimensions4Function()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class GRAPH_DrawText2Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_DrawText2Function() : ExecutableAtomic()
            {
                addParam("context", REFERENCE_PARAMETER);
                addParam("text", REFERENCE_PARAMETER);
            }
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_DrawText2Function > MakeValue() { return std::shared_ptr< GRAPH_DrawText2Function >(new GRAPH_DrawText2Function()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class GRAPH_DrawText3Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_DrawText3Function() : ExecutableAtomic()
            {
                addParam("context", REFERENCE_PARAMETER);
                addParam("pt", REFERENCE_PARAMETER);
                addParam("text", REFERENCE_PARAMETER);
            }
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_DrawText3Function > MakeValue() { return std::shared_ptr< GRAPH_DrawText3Function >(new GRAPH_DrawText3Function()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class GRAPH_DrawText4Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_DrawText4Function() : ExecutableAtomic()
            {
                addParam("context", REFERENCE_PARAMETER);
                addParam("x", REFERENCE_PARAMETER);
                addParam("y", REFERENCE_PARAMETER);
                addParam("text", REFERENCE_PARAMETER);
            }
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_DrawText4Function > MakeValue() { return std::shared_ptr< GRAPH_DrawText4Function >(new GRAPH_DrawText4Function()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    ////////////////////////////////////////////////////////////////////////////

    class GRAPH_MoveTo2Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_MoveTo2Function() : ExecutableAtomic()
            {
                addParam("context", REFERENCE_PARAMETER);
                addParam("pt", REFERENCE_PARAMETER);
            }
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_MoveTo2Function > MakeValue() { return std::shared_ptr< GRAPH_MoveTo2Function >(new GRAPH_MoveTo2Function()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class GRAPH_MoveTo3Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_MoveTo3Function() : ExecutableAtomic()
            {
                addParam("context", REFERENCE_PARAMETER);
                addParam("x", REFERENCE_PARAMETER);
                addParam("y", REFERENCE_PARAMETER);
            }
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_MoveTo3Function > MakeValue() { return std::shared_ptr< GRAPH_MoveTo3Function >(new GRAPH_MoveTo3Function()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class GRAPH_LineTo2Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_LineTo2Function() : ExecutableAtomic()
            {
                addParam("context", REFERENCE_PARAMETER);
                addParam("pt", REFERENCE_PARAMETER);
            }
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_LineTo2Function > MakeValue() { return std::shared_ptr< GRAPH_LineTo2Function >(new GRAPH_LineTo2Function()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class GRAPH_LineTo3Function : public ExecutableAtomic
    {
        protected:
            INLINE GRAPH_LineTo3Function() : ExecutableAtomic()
            {
                addParam("context", REFERENCE_PARAMETER);
                addParam("x", REFERENCE_PARAMETER);
                addParam("y", REFERENCE_PARAMETER);
            }
            
        public:
            
            static INLINE std::shared_ptr< GRAPH_LineTo3Function > MakeValue() { return std::shared_ptr< GRAPH_LineTo3Function >(new GRAPH_LineTo3Function()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class GraphicsCallbacks
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
        
            typedef std::shared_ptr< iAtomic > CallbackT;
            typedef std::list< CallbackT > CallbackStackT;
            typedef std::vector< CallbackStackT > CallbackTableT;
        
        private:
            CallbackTableT mCallbackTable;
        
        protected:
            INLINE GraphicsCallbacks() : mCallbackTable(GraphicsCallbacks::eventNUM) {};
        
        public:
        
            static const bool CALLBACK_CONTINUE;
            static const bool CALLBACK_TERMINATE;
            
            INLINE void Push(const EventT &event, std::shared_ptr< iAtomic > exe) { assert(0 != exe.get()); mCallbackTable.at(event).push_back(exe); };
            bool Invoke(LanguageSymbolTable &symtab, std::shared_ptr< iAtomic > event) const;
            INLINE void Pop(const EventT &event) { CallbackStackT callbacks(mCallbackTable.at(event)); if(!callbacks.empty()) { callbacks.pop_back(); } };
        
            static GraphicsCallbacks &Instance();
        
    };

    ////////////////////////////////////////////////////////////////////////////
            
    extern std::shared_ptr< iAtomic > GRAPH_CreateIdleEventInfoT();
    extern std::shared_ptr< iAtomic > GRAPH_CreateIdleEventInfo();
            
    extern std::shared_ptr< iAtomic > GRAPH_CreateRedrawEventInfoT();
    extern std::shared_ptr< iAtomic > GRAPH_CreateRedrawEventInfo(const int x0, const int y0, const int x1, const int y1);
    
    extern std::shared_ptr< iAtomic > GRAPH_CreateResizeEventInfoT();
    extern std::shared_ptr< iAtomic > GRAPH_CreateResizeEventInfo(const int newwidth, const int newheight);
    
    extern std::shared_ptr< iAtomic > GRAPH_CreateKeyEventInfoT();
    extern std::shared_ptr< iAtomic > GRAPH_CreateKeyPressEventInfo(const int x, const int y, const int ch, const bool shiftst, const bool ctrlst, const bool altst);
    extern std::shared_ptr< iAtomic > GRAPH_CreateKeyReleaseEventInfo(const int x, const int y, const int ch, const bool shiftst, const bool ctrlst, const bool altst);
    
    extern std::shared_ptr< iAtomic > GRAPH_CreateButtonEventInfoT();
    extern std::shared_ptr< iAtomic > GRAPH_CreateButtonPressEventInfo(const int x, const int y, const int button, const bool shiftst, const bool ctrlst, const bool altst);
    extern std::shared_ptr< iAtomic > GRAPH_CreateButtonReleaseEventInfo(const int x, const int y, const int button, const bool shiftst, const bool ctrlst, const bool altst);

    ////////////////////////////////////////////////////////////////////////////

}

#endif

