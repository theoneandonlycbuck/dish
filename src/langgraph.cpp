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

#include <string.h>

#include <cassert>
#include <cstdlib>

#ifdef EVENT_TRACE
#include <iostream>
#endif
#include <sstream>

#include "atomics.h"
#include "exception.h"
#include "graph.h"
#include "langgraph.h"
#include "utility.h"

namespace
{

    ////

    class EventProcessor : public dish::GRAPH_EventProcessor::iEventProcessor
    {
        private:
            dish::LanguageSymbolTable &mSymbolTable;
        
        protected:
            INLINE EventProcessor(dish::LanguageSymbolTable &symtab) : dish::GRAPH_EventProcessor::iEventProcessor(), mSymbolTable(symtab) {};
            
            INLINE dish::LanguageSymbolTable &SymbolTable() { return mSymbolTable; };
        
    };

    ////

    class IdleEventProcessor : public EventProcessor
    {
        protected:
            INLINE IdleEventProcessor(dish::LanguageSymbolTable &symtab) : EventProcessor(symtab) {};
            
        public:
        
            static INLINE std::shared_ptr< IdleEventProcessor > MakeValue(dish::LanguageSymbolTable &symtab) { return std::shared_ptr< IdleEventProcessor >(new IdleEventProcessor(symtab)); };
            
            //  From dish::GRAPH_EventProcessor::iEventProcessor
            
            virtual bool ProcessIdleEvent();
        
    };
    
    bool IdleEventProcessor::ProcessIdleEvent()
    {
#ifdef EVENT_TRACE
        std::cout << "    IdleEventProcessor::ProcessIdleEvent()" << std::endl;
#endif

        return dish::GraphicsCallbacks::Instance().Invoke(
            SymbolTable(),
            dish::GRAPH_CreateIdleEventInfo()
        );
    }

    ////

    class RedrawEventProcessor : public EventProcessor
    {
        protected:
            INLINE RedrawEventProcessor(dish::LanguageSymbolTable &symtab) : EventProcessor(symtab) {};
            
        public:
        
            static INLINE std::shared_ptr< RedrawEventProcessor > MakeValue(dish::LanguageSymbolTable &symtab) { return std::shared_ptr< RedrawEventProcessor >(new RedrawEventProcessor(symtab)); };
            
            //  From dish::GRAPH_EventProcessor::iEventProcessor
            
            virtual bool ProcessRedrawEvent(const int x0, const int y0, const int x1, const int y1);
        
    };
    
    bool RedrawEventProcessor::ProcessRedrawEvent(const int x0, const int y0, const int x1, const int y1)
    {
#ifdef EVENT_TRACE
        std::cout << 
            "    RedrawEventProcessor::ProcessRedrawEvent(" << 
            x0 << ", " << 
            y0 << ", " << 
            x1 << ", " << 
            y1 <<
            ")" << std::endl;
#endif

        return dish::GraphicsCallbacks::Instance().Invoke(
            SymbolTable(),
            dish::GRAPH_CreateRedrawEventInfo(x0, y0, x1, y1)
        );
    }

    ////

    class ResizeEventProcessor : public EventProcessor
    {
        protected:
            INLINE ResizeEventProcessor(dish::LanguageSymbolTable &symtab) : EventProcessor(symtab) {};
            
        public:
        
            static INLINE std::shared_ptr< ResizeEventProcessor > MakeValue(dish::LanguageSymbolTable &symtab) { return std::shared_ptr< ResizeEventProcessor >(new ResizeEventProcessor(symtab)); };
            
            //  From dish::GRAPH_EventProcessor::iEventProcessor
            
            virtual bool ProcessResizeEvent(const int newwidth, const int newheight);
        
    };
    
    bool ResizeEventProcessor::ProcessResizeEvent(const int newwidth, const int newheight)
    {
#ifdef EVENT_TRACE
        std::cout << 
            "    ResizeEventProcessor::ProcessResizeEvent(" << 
            newwidth << ", " << 
            newheight <<
            ")" << std::endl;
#endif

        return dish::GraphicsCallbacks::Instance().Invoke(
            SymbolTable(),
            dish::GRAPH_CreateResizeEventInfo(newwidth, newheight)
        );
    }

    ////

    class KeyPressEventProcessor : public EventProcessor
    {
        protected:
            INLINE KeyPressEventProcessor(dish::LanguageSymbolTable &symtab) : EventProcessor(symtab) {};
            
        public:
        
            static INLINE std::shared_ptr< KeyPressEventProcessor > MakeValue(dish::LanguageSymbolTable &symtab) { return std::shared_ptr< KeyPressEventProcessor >(new KeyPressEventProcessor(symtab)); };
            
            //  From dish::GRAPH_EventProcessor::iEventProcessor
            
            virtual bool ProcessKeyPressEvent(const int x, const int y, const int ch, const bool shiftst, const bool ctrlst, const bool altst);
        
    };
    
    bool KeyPressEventProcessor::ProcessKeyPressEvent(const int x, const int y, const int ch, const bool shiftst, const bool ctrlst, const bool altst)
    {
#ifdef EVENT_TRACE
        std::cout << 
            "    KeyPressEventProcessor::ProcessKeyPressEvent(" << 
            x << ", " << 
            y << ", " << 
            ch << ", " <<
            (shiftst ? "true" : "false") << ", " <<
            (ctrlst ? "true" : "false") << ", " <<
            (altst ? "true" : "false") <<
            ")" << std::endl;
#endif

        return dish::GraphicsCallbacks::Instance().Invoke(
            SymbolTable(),
            dish::GRAPH_CreateKeyPressEventInfo(x, y, ch, shiftst, ctrlst, altst)
        );
    }

    ////

    class KeyReleaseEventProcessor : public EventProcessor
    {
        protected:
            INLINE KeyReleaseEventProcessor(dish::LanguageSymbolTable &symtab) : EventProcessor(symtab) {};
            
        public:
        
            static INLINE std::shared_ptr< KeyReleaseEventProcessor > MakeValue(dish::LanguageSymbolTable &symtab) { return std::shared_ptr< KeyReleaseEventProcessor >(new KeyReleaseEventProcessor(symtab)); };
            
            //  From dish::GRAPH_EventProcessor::iEventProcessor
            
            virtual bool ProcessKeyPressEvent(const int x, const int y, const int ch, const bool shiftst, const bool ctrlst, const bool altst);
        
    };
    
    bool KeyReleaseEventProcessor::ProcessKeyPressEvent(const int x, const int y, const int ch, const bool shiftst, const bool ctrlst, const bool altst)
    {
#ifdef EVENT_TRACE
        std::cout << 
            "    KeyReleaseEventProcessor::ProcessKeyPressEvent(" << 
            x << ", " << 
            y << ", " << 
            ch << ", " <<
            (shiftst ? "true" : "false") << ", " <<
            (ctrlst ? "true" : "false") << ", " <<
            (altst ? "true" : "false") <<
            ")" << std::endl;
#endif

        return dish::GraphicsCallbacks::Instance().Invoke(
            SymbolTable(),
            dish::GRAPH_CreateKeyReleaseEventInfo(x, y, ch, shiftst, ctrlst, altst)
        );
    }

    ////

    class ButtonPressEventProcessor : public EventProcessor
    {
        protected:
            INLINE ButtonPressEventProcessor(dish::LanguageSymbolTable &symtab) : EventProcessor(symtab) {};
            
        public:
        
            static INLINE std::shared_ptr< ButtonPressEventProcessor > MakeValue(dish::LanguageSymbolTable &symtab) { return std::shared_ptr< ButtonPressEventProcessor >(new ButtonPressEventProcessor(symtab)); };
            
            
            //  From dish::GRAPH_EventProcessor::iEventProcessor
            
            virtual bool ProcessButtonPressEvent(const int x, const int y, const int button, const bool shiftst, const bool ctrlst, const bool altst);
        
    };
    
    bool ButtonPressEventProcessor::ProcessButtonPressEvent(const int x, const int y, const int button, const bool shiftst, const bool ctrlst, const bool altst)
    {
#ifdef EVENT_TRACE
        std::cout << "    ButtonPressEventProcessor::ProcessButtonPressEvent(" << 
            x << ", " << 
            y << ", " << 
            button << ", " <<
            (shiftst ? "true" : "false") << ", " <<
            (ctrlst ? "true" : "false") << ", " <<
            (altst ? "true" : "false") <<
            ")" << std::endl;
#endif

        return dish::GraphicsCallbacks::Instance().Invoke(
            SymbolTable(),
            dish::GRAPH_CreateButtonPressEventInfo(x, y, button, shiftst, ctrlst, altst)
        );
    }

    ////

    class ButtonReleaseEventProcessor : public EventProcessor
    {
        protected:
            INLINE ButtonReleaseEventProcessor(dish::LanguageSymbolTable &symtab) : EventProcessor(symtab) {};
            
        public:
        
            static INLINE std::shared_ptr< ButtonReleaseEventProcessor > MakeValue(dish::LanguageSymbolTable &symtab) { return std::shared_ptr< ButtonReleaseEventProcessor >(new ButtonReleaseEventProcessor(symtab)); };
            
            //  From dish::GRAPH_EventProcessor::iEventProcessor
            
            virtual bool ProcessButtonPressEvent(const int x, const int y, const int button, const bool shiftst, const bool ctrlst, const bool altst);
        
    };
    
    bool ButtonReleaseEventProcessor::ProcessButtonPressEvent(const int x, const int y, const int button, const bool shiftst, const bool ctrlst, const bool altst)
    {
#ifdef EVENT_TRACE
        std::cout << 
            "    ButtonReleaseEventProcessor::ProcessButtonPressEvent(" << 
            x << ", " << 
            y << ", " << 
            button << ", " <<
            (shiftst ? "true" : "false") << ", " <<
            (ctrlst ? "true" : "false") << ", " <<
            (altst ? "true" : "false") <<
            ")" << std::endl;
#endif

        return dish::GraphicsCallbacks::Instance().Invoke(
            SymbolTable(),
            dish::GRAPH_CreateButtonReleaseEventInfo(x, y, button, shiftst, ctrlst, altst)
        );
    }

    ////
    
    INLINEC void ValidateGraphicsContext(std::shared_ptr< dish::iAtomic > context)
    {
        if(!(context->Member("initialized")->AsBoolean()))
        {
            throw dish::GraphicsFailureException("Graphics context not initialized.");
        }
    }
 
    std::shared_ptr< dish::iAtomic > CreateGraphicsContext(const dish::IntegerT &xsize, const dish::IntegerT &ysize, const bool &locked = false)
    {
        std::shared_ptr< dish::iAtomic > context(dish::GRAPH_CreateGraphicsContextType()->Declare());
        context->Member("initialized")->Assign(true);
        
        context->Member("XSize")->Assign(xsize);
        context->Member("YSize")->Assign(ysize);
        
        context->Member("Title")->Assign("");
        
        context->Member("UpperLeftX")->Assign(static_cast< dish::RealT >(0));
        context->Member("UpperLeftY")->Assign(static_cast< dish::RealT >(0));
        context->Member("LowerRghtX")->Assign(static_cast< dish::RealT >(xsize));
        context->Member("LowerRghtY")->Assign(static_cast< dish::RealT >(ysize));
        
        context->Member("recoordinate")->Assign(false);
        context->Member("offsetx")->Assign(static_cast< dish::RealT >(0.0));
        context->Member("scalex")->Assign(static_cast< dish::RealT >(1.0));
        context->Member("offsety")->Assign(static_cast< dish::RealT >(0.0));
        context->Member("scaley")->Assign(static_cast< dish::RealT >(1.0));
        
        context->Member("ForegroundColor")->Assign(
            static_cast< dish::IntegerT >(
                dish::GRAPH_MakeColorRGB(static_cast< uint8_t >(0xFF), static_cast< uint8_t >(0xFF), static_cast< uint8_t >(0xFF))
            )
        );
        
        context->Member("BackgroundColor")->Assign(
            static_cast< dish::IntegerT >(
                dish::GRAPH_MakeColorRGB(static_cast< uint8_t >(0x00), static_cast< uint8_t >(0x00), static_cast< uint8_t >(0x00))
            )
        );
        
        context->Member("Font")->Assign("fixed");
        
        context->Member("FillStyle")->Assign(dish::GRAPH_FillStyle_SOLID);
        
        context->Member("LineWidth")->Assign(static_cast< dish::IntegerT >(1));
        context->Member("LineStyle")->Assign(dish::GRAPH_LineStyle_SOLID);
        context->Member("LineCapStyle")->Assign(dish::GRAPH_LineCap_BUTT);
        context->Member("LineJoinStyle")->Assign(dish::GRAPH_LineJoin_MITRE);
        
        context->Member("xpos")->Assign(static_cast< dish::IntegerT >(0));
        context->Member("ypos")->Assign(static_cast< dish::IntegerT >(0));
        
        if(locked)
        {
            context->Lock();
        }
        
        return context;
    }
 
    std::shared_ptr< dish::iAtomic > CreateGraphicsContext(const dish::IntegerT &xsize, const dish::IntegerT &ysize, const dish::StringT &title, const bool &locked = false)
    {
        std::shared_ptr< dish::iAtomic > context(dish::GRAPH_CreateGraphicsContextType()->Declare());
        context->Member("initialized")->Assign(true);
        
        context->Member("XSize")->Assign(xsize);
        context->Member("YSize")->Assign(ysize);
        
        context->Member("Title")->Assign(title);
        
        context->Member("UpperLeftX")->Assign(static_cast< dish::RealT >(0));
        context->Member("UpperLeftY")->Assign(static_cast< dish::RealT >(0));
        context->Member("LowerRghtX")->Assign(static_cast< dish::RealT >(xsize));
        context->Member("LowerRghtY")->Assign(static_cast< dish::RealT >(ysize));
        
        context->Member("recoordinate")->Assign(false);
        context->Member("offsetx")->Assign(static_cast< dish::RealT >(0.0));
        context->Member("scalex")->Assign(static_cast< dish::RealT >(1.0));
        context->Member("offsety")->Assign(static_cast< dish::RealT >(0.0));
        context->Member("scaley")->Assign(static_cast< dish::RealT >(1.0));
        
        context->Member("ForegroundColor")->Assign(
            static_cast< dish::IntegerT >(
                dish::GRAPH_MakeColorRGB(static_cast< uint8_t >(0xFF), static_cast< uint8_t >(0xFF), static_cast< uint8_t >(0xFF))
            )
        );
        
        context->Member("BackgroundColor")->Assign(
            static_cast< dish::IntegerT >(
                dish::GRAPH_MakeColorRGB(static_cast< uint8_t >(0x00), static_cast< uint8_t >(0x00), static_cast< uint8_t >(0x00))
            )
        );
        
        context->Member("Font")->Assign("fixed");
        
        context->Member("FillStyle")->Assign(dish::GRAPH_FillStyle_SOLID);
        
        context->Member("LineWidth")->Assign(static_cast< dish::IntegerT >(1));
        context->Member("LineStyle")->Assign(dish::GRAPH_LineStyle_SOLID);
        context->Member("LineCapStyle")->Assign(dish::GRAPH_LineCap_BUTT);
        context->Member("LineJoinStyle")->Assign(dish::GRAPH_LineJoin_MITRE);
        
        context->Member("xpos")->Assign(static_cast< dish::IntegerT >(0));
        context->Member("ypos")->Assign(static_cast< dish::IntegerT >(0));
        
        if(locked)
        {
            context->Lock();
        }
        
        return context;
    }
     
    std::shared_ptr< dish::iAtomic > CreateGraphicsContext(const dish::IntegerT &xsize, const dish::IntegerT &ysize, const dish::StringT &title, const dish::RealT &ul_x, const dish::RealT &ul_y, const dish::RealT &lr_x, const dish::RealT &lr_y, const bool &locked = false)
    {
        std::shared_ptr< dish::iAtomic > context(dish::GRAPH_CreateGraphicsContextType()->Declare());
        context->Member("initialized")->Assign(true);
        
        context->Member("XSize")->Assign(xsize);
        context->Member("YSize")->Assign(ysize);
        
        context->Member("Title")->Assign(title);
        
        context->Member("UpperLeftX")->Assign(ul_x);
        context->Member("UpperLeftY")->Assign(ul_y);
        context->Member("LowerRghtX")->Assign(lr_x);
        context->Member("LowerRghtY")->Assign(lr_y);
        
        {
            const dish::BooleanT recoordinate(
                !dish::IsZero(ul_x) || 
                !dish::IsZero(ul_y) || 
                !dish::IsEqual(static_cast< dish::RealT >(xsize), lr_x) || 
                !dish::IsEqual(static_cast< dish::RealT >(ysize), lr_y)
            );
            context->Member("recoordinate")->Assign(recoordinate);
            
            if(recoordinate)
            {
                //  !!!
                throw dish::OperationNotSupportedException();
            }
        }
        
        context->Member("ForegroundColor")->Assign(
            static_cast< dish::IntegerT >(
                dish::GRAPH_MakeColorRGB(static_cast< uint8_t >(0xFF), static_cast< uint8_t >(0xFF), static_cast< uint8_t >(0xFF))
            )
        );
        
        context->Member("BackgroundColor")->Assign(
            static_cast< dish::IntegerT >(
                dish::GRAPH_MakeColorRGB(static_cast< uint8_t >(0x00), static_cast< uint8_t >(0x00), static_cast< uint8_t >(0x00))
            )
        );
        
        context->Member("Font")->Assign("fixed");
        
        context->Member("FillStyle")->Assign(dish::GRAPH_FillStyle_SOLID);
        
        context->Member("LineWidth")->Assign(static_cast< dish::IntegerT >(1));
        context->Member("LineStyle")->Assign(dish::GRAPH_LineStyle_SOLID);
        context->Member("LineCapStyle")->Assign(dish::GRAPH_LineCap_BUTT);
        context->Member("LineJoinStyle")->Assign(dish::GRAPH_LineJoin_MITRE);
        
        context->Member("xpos")->Assign(static_cast< dish::IntegerT >(0));
        context->Member("ypos")->Assign(static_cast< dish::IntegerT >(0));
        
        if(locked)
        {
            context->Lock();
        }
        
        return context;
    }

    INLINEC uint8_t colorValueToByteValue(std::shared_ptr< dish::iAtomic > color)
    {
        if(dish::iAtomic::typeInteger == color->Type())
        {
            const dish::IntegerT color_value(color->AsInteger());
            if(color_value >= static_cast< dish::IntegerT >(0xFF))
            {
                return 0xFF;
            }
            
            else if(color_value <= static_cast< dish::IntegerT >(0x00))
            {
                return 0x00;
            }
            
            else
            {
                return static_cast< uint8_t >(color_value & static_cast< dish::IntegerT >(0xFF));
            }
        }
        else
        {
            const dish::RealT color_value(color->AsReal());
            if(color_value >= 1.0)
            {
                return 0xFF;
            }
            
            else if(color_value <= 0.0)
            {
                return 0x00;
            }
            
            else
            {
                return static_cast< uint8_t >(static_cast< dish::IntegerT >(0xFF) * color->AsReal() + 0.5);
            }
        }
        
        assert(false);
    }
    
    INLINEC void transformCoordinate(std::shared_ptr< dish::iAtomic > context, std::shared_ptr< dish::iAtomic > worldx, std::shared_ptr< dish::iAtomic > worldy, int &x, int &y)
    {
        if(!context->Member("recoordinate")->AsBoolean())
        {
            x = static_cast< int >(worldx->AsInteger());
            y = static_cast< int >(worldy->AsInteger());
        }
        else
        {
            x = static_cast< int >(context->Member("scalex")->AsReal() * (worldx->AsReal() + context->Member("offsetx")->AsReal()) + 0.5);
            y = static_cast< int >(context->Member("scaley")->AsReal() * (worldy->AsReal() + context->Member("offsety")->AsReal()) + 0.5);
        }
    }
    
    INLINEC void transformCoordinates(std::shared_ptr< dish::iAtomic > context, std::shared_ptr< dish::iAtomic > worldx0, std::shared_ptr< dish::iAtomic > worldy0, int &x0, int &y0, std::shared_ptr< dish::iAtomic > worldx1, std::shared_ptr< dish::iAtomic > worldy1, int &x1, int &y1)
    {
        if(!context->Member("recoordinate")->AsBoolean())
        {
            x0 = static_cast< int >(worldx0->AsInteger());
            y0 = static_cast< int >(worldy0->AsInteger());
            x1 = static_cast< int >(worldx1->AsInteger());
            y1 = static_cast< int >(worldy1->AsInteger());
        }
        else
        {
            const dish::RealT offsetx(context->Member("offsetx")->AsReal());
            const dish::RealT scalex(context->Member("scalex")->AsReal());
            const dish::RealT offsety(context->Member("offsety")->AsReal());
            const dish::RealT scaley(context->Member("scaley")->AsReal());
            
            x0 = static_cast< int >(scalex * (worldx0->AsReal() + offsetx) + 0.5);
            y0 = static_cast< int >(scaley * (worldy0->AsReal() + offsety) + 0.5);
            x1 = static_cast< int >(scalex * (worldx1->AsReal() + offsetx) + 0.5);
            y1 = static_cast< int >(scaley * (worldy1->AsReal() + offsety) + 0.5);
        }
    }

}

/******************************************************************************

    Public definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_CreateGraphicsContextType()
{
    static std::shared_ptr< StructureTypeAtomic > structure;
    
    if(0 == structure.get())
    {
        std::shared_ptr< BooleanTypeAtomic > boolean_type(BooleanTypeAtomic::MakeValue());
        std::shared_ptr< IntegerTypeAtomic > integer_type(IntegerTypeAtomic::MakeValue());
        std::shared_ptr< RealTypeAtomic > real_type(RealTypeAtomic::MakeValue());
        std::shared_ptr< StringTypeAtomic > string_type(StringTypeAtomic::MakeValue());
        
        structure = StructureTypeAtomic::MakeValue();
        structure->Add("initialized", boolean_type);
        
        structure->Add("XSize", integer_type);
        structure->Add("YSize", integer_type);
        
        structure->Add("Title", string_type);
        
        structure->Add("UpperLeftX", real_type);
        structure->Add("UpperLeftY", real_type);
        structure->Add("LowerRghtX", real_type);
        structure->Add("LowerRghtY", real_type);
        
        structure->Add("recoordinate", boolean_type);
        structure->Add("offsetx", real_type);
        structure->Add("scalex", real_type);
        structure->Add("offsety", real_type);
        structure->Add("scaley", real_type);
        
        structure->Add("ForegroundColor", integer_type);
        structure->Add("BackgroundColor", integer_type);
        
        structure->Add("Font", string_type);
        
        structure->Add("FillStyle", integer_type);
        
        structure->Add("LineWidth", integer_type);
        structure->Add("LineStyle", integer_type);
        structure->Add("LineCapStyle", integer_type);
        structure->Add("LineJoinStyle", integer_type);
        
        structure->Add("xpos", integer_type);
        structure->Add("ypos", integer_type);
    }

    return structure;
}

std::shared_ptr< dish::iAtomic > dish::GRAPH_CreateIntegerPointType()
{
    static std::shared_ptr< StructureTypeAtomic > structure;
    
    if(0 == structure.get())
    {
        std::shared_ptr< IntegerTypeAtomic > integer_type(IntegerTypeAtomic::MakeValue());
        
        structure = StructureTypeAtomic::MakeValue();
        structure->Add("X", integer_type);
        structure->Add("Y", integer_type);
    }

    return structure;
}

std::shared_ptr< dish::iAtomic > dish::GRAPH_CreateRealPointType()
{
    static std::shared_ptr< StructureTypeAtomic > structure;
    
    if(0 == structure.get())
    {
        std::shared_ptr< RealTypeAtomic > real_type(RealTypeAtomic::MakeValue());
        
        structure = StructureTypeAtomic::MakeValue();
        structure->Add("X", real_type);
        structure->Add("Y", real_type);
    }

    return structure;
}

std::shared_ptr< dish::iAtomic > dish::GRAPH_CreateIntegerLineType()
{
    static std::shared_ptr< StructureTypeAtomic > structure;
    
    if(0 == structure.get())
    {
        std::shared_ptr< iAtomic > point_type(GRAPH_CreateIntegerPointType());
    
        structure = StructureTypeAtomic::MakeValue();
        structure->Add("Pt0", point_type);
        structure->Add("Pt1", point_type);
    }

    return structure;
}

std::shared_ptr< dish::iAtomic > dish::GRAPH_CreateRealLineType()
{
    static std::shared_ptr< StructureTypeAtomic > structure;
    
    if(0 == structure.get())
    {
        std::shared_ptr< iAtomic > point_type(GRAPH_CreateRealPointType());
    
        structure = StructureTypeAtomic::MakeValue();
        structure->Add("Pt0", point_type);
        structure->Add("Pt1", point_type);
    }

    return structure;
}

/******************************************************************************

    dish::GRAPH_CreateContext2Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_CreateContext2Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    return CreateGraphicsContext(
        getParam(symtab, "xsize")->AsInteger(),
        getParam(symtab, "ysize")->AsInteger()
    );
}

/******************************************************************************

    dish::GRAPH_CreateContext3Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_CreateContext3Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    return CreateGraphicsContext(
        getParam(symtab, "xsize")->AsInteger(),
        getParam(symtab, "ysize")->AsInteger(),
        
        getParam(symtab, "title")->AsString()
    );
}

/******************************************************************************

    dish::GRAPH_CreateContext7Function class definitions

 ******************************************************************************/
  
std::shared_ptr< dish::iAtomic > dish::GRAPH_CreateContext7Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    return CreateGraphicsContext(
        getParam(symtab, "xsize")->AsInteger(),
        getParam(symtab, "ysize")->AsInteger(),
        
        getParam(symtab, "title")->AsString(),
        
        getParam(symtab, "ul_x")->AsInteger(),
        getParam(symtab, "ul_y")->AsInteger(),
        getParam(symtab, "lr_x")->AsInteger(),
        getParam(symtab, "lr_y")->AsInteger()
    );
}

/******************************************************************************

    dish::GRAPH_CreatePointFunction class definitions

 ******************************************************************************/
  
std::shared_ptr< dish::iAtomic > dish::GRAPH_CreatePointFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > x(getParam(symtab, "x"));
    std::shared_ptr< iAtomic > y(getParam(symtab, "y"));
    
    std::shared_ptr< dish::iAtomic > pt;
    
    if((dish::iAtomic::typeReal == x->Type()) || (dish::iAtomic::typeReal == y->Type()))
    {
        pt = dish::GRAPH_CreateRealPointType()->Declare();
        pt->Member("X")->Assign(x->AsReal());
        pt->Member("Y")->Assign(y->AsReal());
    }
    else
    {
        pt = dish::GRAPH_CreateIntegerPointType()->Declare();
        pt->Member("X")->Assign(x->AsInteger());
        pt->Member("Y")->Assign(y->AsInteger());
    }
    
    assert(0 != pt.get());
    return pt;
}

/******************************************************************************

    dish::GRAPH_CreateLine2Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_CreateLine2Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > pt0(getParam(symtab, "pt0"));
    std::shared_ptr< iAtomic > pt1(getParam(symtab, "pt1"));
    
    std::shared_ptr< dish::iAtomic > line;
    
    if(
        (dish::iAtomic::typeReal == pt0->Member("x")->Type()) || 
        (dish::iAtomic::typeReal == pt0->Member("y")->Type()) ||
        (dish::iAtomic::typeReal == pt1->Member("x")->Type()) || 
        (dish::iAtomic::typeReal == pt1->Member("y")->Type())
      )
    {
        line = GRAPH_CreateRealLineType()->Declare();
        line->Member("Pt0")->Member("X")->Assign(pt0->Member("X")->AsReal());
        line->Member("Pt0")->Member("Y")->Assign(pt0->Member("Y")->AsReal());
        line->Member("Pt1")->Member("X")->Assign(pt1->Member("X")->AsReal());
        line->Member("Pt1")->Member("Y")->Assign(pt1->Member("Y")->AsReal());
    }
    else
    {
        line = GRAPH_CreateIntegerLineType()->Declare();
        line->Member("Pt0")->Member("X")->Assign(pt0->Member("X")->AsInteger());
        line->Member("Pt0")->Member("Y")->Assign(pt0->Member("Y")->AsInteger());
        line->Member("Pt1")->Member("X")->Assign(pt1->Member("X")->AsInteger());
        line->Member("Pt1")->Member("Y")->Assign(pt1->Member("Y")->AsInteger());
    }
    
    assert(0 != line.get());
    return line;
}

/******************************************************************************

    dish::GRAPH_CreateLine4Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_CreateLine4Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > x0(getParam(symtab, "x0"));
    std::shared_ptr< iAtomic > y0(getParam(symtab, "y0"));
    std::shared_ptr< iAtomic > x1(getParam(symtab, "x1"));
    std::shared_ptr< iAtomic > y1(getParam(symtab, "y1"));
    
    std::shared_ptr< dish::iAtomic > line;
    
    if(
        (dish::iAtomic::typeReal == x0->Type()) || 
        (dish::iAtomic::typeReal == y0->Type()) ||
        (dish::iAtomic::typeReal == x1->Type()) || 
        (dish::iAtomic::typeReal == y1->Type())
      )
    {
        line = GRAPH_CreateRealLineType()->Declare();
        line->Member("Pt0")->Member("X")->Assign(x0->AsReal());
        line->Member("Pt0")->Member("Y")->Assign(y0->AsReal());
        line->Member("Pt1")->Member("X")->Assign(x1->AsReal());
        line->Member("Pt1")->Member("Y")->Assign(y1->AsReal());
    }
    else
    {
        line = GRAPH_CreateIntegerLineType()->Declare();
        line->Member("Pt0")->Member("X")->Assign(x0->AsInteger());
        line->Member("Pt0")->Member("Y")->Assign(y0->AsInteger());
        line->Member("Pt1")->Member("X")->Assign(x1->AsInteger());
        line->Member("Pt1")->Member("Y")->Assign(y1->AsInteger());
    }
    
    assert(0 != line.get());
    return line;
}

/******************************************************************************

    dish::GRAPH_StartFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_StartFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    {
        GRAPH_EventProcessor &processor(GRAPH_EventProcessor::Instance());

        processor.Push(GRAPH_EventProcessor::eventNull, IdleEventProcessor::MakeValue(symtab));
        processor.Push(GRAPH_EventProcessor::eventRedraw, RedrawEventProcessor::MakeValue(symtab));
        processor.Push(GRAPH_EventProcessor::eventResize, ResizeEventProcessor::MakeValue(symtab));
        processor.Push(GRAPH_EventProcessor::eventKeyPress, KeyPressEventProcessor::MakeValue(symtab));
        processor.Push(GRAPH_EventProcessor::eventKeyRelease, KeyReleaseEventProcessor::MakeValue(symtab));
        processor.Push(GRAPH_EventProcessor::eventButtonPress, ButtonPressEventProcessor::MakeValue(symtab));
        processor.Push(GRAPH_EventProcessor::eventButtonRelease, ButtonReleaseEventProcessor::MakeValue(symtab));
    }
    
    {
        std::shared_ptr< iAtomic > context(getParam(symtab, "context"));
        
        GRAPH_Start(
            context->Member("XSize")->AsInteger(),
            context->Member("YSize")->AsInteger(),
            
            strdup(context->Member("Title")->AsString().c_str())
        );
    }
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_IsStartedFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_IsStartedFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return BooleanValue::MakeValue(GRAPH_IsStarted(), dish::LOCKED);
}

/******************************************************************************

    dish::GRAPH_EndFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_EndFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    GRAPH_End();
    
    {
        GRAPH_EventProcessor &processor(GRAPH_EventProcessor::Instance());

        processor.Pop(GRAPH_EventProcessor::eventNull);
        processor.Pop(GRAPH_EventProcessor::eventRedraw);
        processor.Pop(GRAPH_EventProcessor::eventResize);
        processor.Pop(GRAPH_EventProcessor::eventKeyPress);
        processor.Pop(GRAPH_EventProcessor::eventKeyRelease);
        processor.Pop(GRAPH_EventProcessor::eventButtonPress);
        processor.Pop(GRAPH_EventProcessor::eventButtonRelease);
    }
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_ProcessEventFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_ProcessEventFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    GRAPH_ProcessEvent();
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_ProcessEvent1Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_ProcessEvent1Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > event(getParam(symtab, "event"));

    switch(event->Member("Type")->AsInteger())
    {
        case GRAPH_EventProcessor::eventRedraw:
        {
            return BooleanValue::MakeLockedValue(
                GRAPH_EventProcessor::Instance().InvokeRedrawEvent(
                    static_cast< int >(event->Member("X0")->AsInteger()),
                    static_cast< int >(event->Member("Y0")->AsInteger()),
                    static_cast< int >(event->Member("X1")->AsInteger()),
                    static_cast< int >(event->Member("Y1")->AsInteger())
                )
            );
        }
        
        case GRAPH_EventProcessor::eventResize:
        {
            return BooleanValue::MakeLockedValue(
                GRAPH_EventProcessor::Instance().InvokeResizeEvent(
                    static_cast< int >(event->Member("Width")->AsInteger()),
                    static_cast< int >(event->Member("Height")->AsInteger())
                )
            );
        }
        
        case GRAPH_EventProcessor::eventKeyPress:
        {
            return BooleanValue::MakeLockedValue(
                GRAPH_EventProcessor::Instance().InvokeKeyPressEvent(
                    static_cast< int >(event->Member("Key")->AsInteger()),
                    static_cast< int >(event->Member("X")->AsInteger()),
                    static_cast< int >(event->Member("Y")->AsInteger()),
                    static_cast< bool >(event->Member("ShiftState")->AsBoolean()),
                    static_cast< bool >(event->Member("CtrlState")->AsBoolean()),
                    static_cast< bool >(event->Member("AltState")->AsBoolean())
                )
            );
        }
        
        case GRAPH_EventProcessor::eventKeyRelease:
        {
            return BooleanValue::MakeLockedValue(
                GRAPH_EventProcessor::Instance().InvokeKeyReleaseEvent(
                    static_cast< int >(event->Member("Key")->AsInteger()),
                    static_cast< int >(event->Member("X")->AsInteger()),
                    static_cast< int >(event->Member("Y")->AsInteger()),
                    static_cast< bool >(event->Member("ShiftState")->AsBoolean()),
                    static_cast< bool >(event->Member("CtrlState")->AsBoolean()),
                    static_cast< bool >(event->Member("AltState")->AsBoolean())
                )
            );
        }
        
        case GRAPH_EventProcessor::eventButtonPress:
        {
            return BooleanValue::MakeLockedValue(
                GRAPH_EventProcessor::Instance().InvokeButtonPressEvent(
                    static_cast< int >(event->Member("Button")->AsInteger()),
                    static_cast< int >(event->Member("X")->AsInteger()),
                    static_cast< int >(event->Member("Y")->AsInteger()),
                    static_cast< bool >(event->Member("ShiftState")->AsBoolean()),
                    static_cast< bool >(event->Member("CtrlState")->AsBoolean()),
                    static_cast< bool >(event->Member("AltState")->AsBoolean())
                )
            );
        }
        
        case GRAPH_EventProcessor::eventButtonRelease:
        {
            return BooleanValue::MakeLockedValue(
                GRAPH_EventProcessor::Instance().InvokeButtonReleaseEvent(
                    static_cast< int >(event->Member("Button")->AsInteger()),
                    static_cast< int >(event->Member("X")->AsInteger()),
                    static_cast< int >(event->Member("Y")->AsInteger()),
                    static_cast< bool >(event->Member("ShiftState")->AsBoolean()),
                    static_cast< bool >(event->Member("CtrlState")->AsBoolean()),
                    static_cast< bool >(event->Member("AltState")->AsBoolean())
                )
            );
        }
        
        default:
        {
            //  Empty
        }
        
    }
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_EventLoopFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_EventLoopFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    while(true)
    {
        GRAPH_ProcessEvent();
    }
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_EventLoop1Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_EventLoop1Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    for(std::shared_ptr< iAtomic > done(getParam(symtab, "done")); !done->AsBoolean(); )
    {
        GRAPH_ProcessEvent();
    }
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_PushEventProcessorFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_PushEventProcessorFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const IntegerT event(getParam(symtab, "event")->AsInteger());
    
    if((event >= GraphicsCallbacks::eventNull) && (event < GraphicsCallbacks::eventNUM))
    {
        GraphicsCallbacks::Instance().Push(
            static_cast< GraphicsCallbacks::EventT >(event),
            getParam(symtab, "procF")
        );
    }
    else
    {
        std::stringstream message;
        message << "Illegal event index: ";
        message << event;
        message << ".";
    
        throw IllegalIndexException(message.str());
    }
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_PopEventProcessorFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_PopEventProcessorFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const IntegerT event(getParam(symtab, "event")->AsInteger());
    
    if((event >= GraphicsCallbacks::eventNull) && (event < GraphicsCallbacks::eventNUM))
    {
        GraphicsCallbacks::Instance().Pop(
            static_cast< GraphicsCallbacks::EventT >(event)
        );
    }
    else
    {
        std::stringstream message;
        message << "Illegal event index: ";
        message << event;
        message << ".";
    
        throw IllegalIndexException(message.str());
    }
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_RefreshFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_RefreshFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    GRAPH_Refresh();
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_MakeColorFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_MakeColorFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return IntegerValue::MakeValue(
        static_cast< IntegerT >(
            GRAPH_MakeColorRGB(
                colorValueToByteValue(getParam(symtab, "red")),
                colorValueToByteValue(getParam(symtab, "green")),
                colorValueToByteValue(getParam(symtab, "blue"))
            )
        )
    );
}

/******************************************************************************

    dish::GRAPH_ApplyContextFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_ApplyContextFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > context(getParam(symtab, "context"));
    ValidateGraphicsContext(context);
    
    GRAPH_SetForeColor(static_cast< int >(context->Member("ForegroundColor")->AsInteger()));
    
    GRAPH_SetBackColor(static_cast< int >(context->Member("BackgroundColor")->AsInteger()));
    
    {
        std::shared_ptr< iAtomic > fontname(context->Member("Font"));
        const StringT font(fontname->AsString());
        const StringT actual_font(GRAPH_SetFont(font));
        
        if(font != actual_font)
        {
            fontname->Assign(actual_font);
        }
    }
    
    GRAPH_SetFillStyle(static_cast< int >(context->Member("FillStyle")->AsInteger()));
    
    GRAPH_SetLineStyle(
        static_cast< int >(context->Member("LineWidth")->AsInteger()),
        static_cast< int >(context->Member("LineStyle")->AsInteger()),
        static_cast< int >(context->Member("LineCapStyle")->AsInteger()),
        static_cast< int >(context->Member("LineJoinStyle")->AsInteger())
    );
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_Clear1Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_Clear1Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    ValidateGraphicsContext(getParam(symtab, "context"));
    
    GRAPH_Clear();
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_Clear2Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_Clear2Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > context(getParam(symtab, "context"));
    ValidateGraphicsContext(context);
    
    GRAPH_SetBackColor(static_cast< int >(getParam(symtab, "bgcolor")->AsInteger()));
    GRAPH_Clear();
    GRAPH_SetBackColor(static_cast< int >(context->Member("BackgroundColor")->AsInteger()));
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_DrawPixel2Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_DrawPixel2Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > context(getParam(symtab, "context"));
    ValidateGraphicsContext(context);
    
    std::shared_ptr< iAtomic > pt(getParam(symtab, "pt"));

    int x(0);
    int y(0);
    transformCoordinate(
        context, 
        pt->Member("X"), pt->Member("Y"), x, y
    );
    
    GRAPH_DrawPixel(x, y);
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_DrawPixel3Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_DrawPixel3Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > context(getParam(symtab, "context"));
    ValidateGraphicsContext(context);

    int x(0);
    int y(0);
    transformCoordinate(
        context, 
        getParam(symtab, "x"), getParam(symtab, "y"), x, y
    );
    
    GRAPH_DrawPixel(x, y);
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_DrawLine2Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_DrawLine2Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > context(getParam(symtab, "context"));
    ValidateGraphicsContext(context);
    
    std::shared_ptr< iAtomic > lines(getParam(symtab, "line"));

    int x0(0);
    int y0(0);
    int x1(0);
    int y1(0);
    transformCoordinates(
        context, 
        lines->Member("Pt0")->Member("X"), lines->Member("Pt0")->Member("Y"), x0, y0, 
        lines->Member("Pt1")->Member("X"), lines->Member("Pt1")->Member("Y"), x1, y1
    );

    GRAPH_DrawLine(x0, y0, x1, y1);
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_DrawLine3Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_DrawLine3Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > context(getParam(symtab, "context"));
    ValidateGraphicsContext(context);
    
    std::shared_ptr< iAtomic > pt0(getParam(symtab, "pt0"));
    std::shared_ptr< iAtomic > pt1(getParam(symtab, "pt1"));

    int x0(0);
    int y0(0);
    int x1(0);
    int y1(0);
    transformCoordinates(
        context, 
        pt0->Member("X"), pt0->Member("Y"), x0, y0, 
        pt1->Member("X"), pt1->Member("Y"), x1, y1
    );

    GRAPH_DrawLine(x0, y0, x1, y1);
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_DrawLine5Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_DrawLine5Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > context(getParam(symtab, "context"));
    ValidateGraphicsContext(context);

    int x0(0);
    int y0(0);
    int x1(0);
    int y1(0);
    transformCoordinates(
        context, 
        getParam(symtab, "x0"), getParam(symtab, "y0"), x0, y0, 
        getParam(symtab, "x1"), getParam(symtab, "y1"), x1, y1
    );

    GRAPH_DrawLine(x0, y0, x1, y1);
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_DrawLinesFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_DrawLinesFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > context(getParam(symtab, "context"));
    ValidateGraphicsContext(context);

    std::shared_ptr< iAtomic > lines(getParam(symtab, "lines"));
    
    for(IntegerT i(lines->Member("start")->AsInteger()), last_i(lines->Member("finish")->AsInteger()); i <= last_i; ++i)
    {
        std::shared_ptr< iAtomic > line(lines->Element(i));
        std::shared_ptr< iAtomic > pt0(line->Member("Pt0"));
        std::shared_ptr< iAtomic > pt1(line->Member("Pt1"));
        
        int x0(0);
        int y0(0);
        int x1(0);
        int y1(0);
        transformCoordinates(
            context, 
            pt0->Member("X"), pt0->Member("Y"), x0, y0, 
            pt1->Member("X"), pt1->Member("Y"), x1, y1
        );
        
        GRAPH_DrawLine(x0, y0, x1, y1);
    }
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_DrawBox3Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_DrawBox3Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > context(getParam(symtab, "context"));
    ValidateGraphicsContext(context);
    
    std::shared_ptr< iAtomic > pt0(getParam(symtab, "pt0"));
    std::shared_ptr< iAtomic > pt1(getParam(symtab, "pt1"));

    int x0(0);
    int y0(0);
    int x1(0);
    int y1(0);
    transformCoordinates(
        context, 
        pt0->Member("X"), pt0->Member("Y"), x0, y0, 
        pt1->Member("X"), pt1->Member("Y"), x1, y1
    );

    GRAPH_DrawBox(x0, y0, x1, y1, false);
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_DrawBox4Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_DrawBox4Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > context(getParam(symtab, "context"));
    ValidateGraphicsContext(context);
    
    std::shared_ptr< iAtomic > pt0(getParam(symtab, "pt0"));
    std::shared_ptr< iAtomic > pt1(getParam(symtab, "pt1"));

    int x0(0);
    int y0(0);
    int x1(0);
    int y1(0);
    transformCoordinates(
        context,
        pt0->Member("X"), pt0->Member("Y"), x0, y0, 
        pt1->Member("X"), pt1->Member("Y"), x1, y1
    );

    GRAPH_DrawBox(x0, y0, x1, y1, getParam(symtab, "fill")->AsBoolean());
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_DrawBox5Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_DrawBox5Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > context(getParam(symtab, "context"));
    ValidateGraphicsContext(context);

    int x0(0);
    int y0(0);
    int x1(0);
    int y1(0);
    transformCoordinates(
        context, 
        getParam(symtab, "x0"), getParam(symtab, "y0"), x0, y0, 
        getParam(symtab, "x1"), getParam(symtab, "y1"), x1, y1
    );

    GRAPH_DrawBox(x0, y0, x1, y1, false);
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_DrawBox6Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_DrawBox6Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > context(getParam(symtab, "context"));
    ValidateGraphicsContext(context);

    int x0(0);
    int y0(0);
    int x1(0);
    int y1(0);
    transformCoordinates(
        context, 
        getParam(symtab, "x0"), getParam(symtab, "y0"), x0, y0, 
        getParam(symtab, "x1"), getParam(symtab, "y1"), x1, y1
    );

    GRAPH_DrawBox(x0, y0, x1, y1, getParam(symtab, "fill")->AsBoolean());
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_DrawArc5Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_DrawArc5Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > context(getParam(symtab, "context"));
    ValidateGraphicsContext(context);
    
    std::shared_ptr< iAtomic > pt0(getParam(symtab, "pt0"));
    std::shared_ptr< iAtomic > pt1(getParam(symtab, "pt1"));

    int x0(0);
    int y0(0);
    int x1(0);
    int y1(0);
    transformCoordinates(
        context, 
        pt0->Member("X"), pt0->Member("Y"), x0, y0, 
        pt1->Member("X"), pt1->Member("Y"), x1, y1
    );
    
    GRAPH_DrawArc(
        x0, y0,
        x1, y1, 
        getParam(symtab, "startang")->AsReal(), getParam(symtab, "endang")->AsReal(),
        false
    );
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_DrawArc6Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_DrawArc6Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > context(getParam(symtab, "context"));
    ValidateGraphicsContext(context);
    
    std::shared_ptr< iAtomic > pt0(getParam(symtab, "pt0"));
    std::shared_ptr< iAtomic > pt1(getParam(symtab, "pt1"));

    int x0(0);
    int y0(0);
    int x1(0);
    int y1(0);
    transformCoordinates(
        context, 
        pt0->Member("X"), pt0->Member("Y"), x0, y0, 
        pt1->Member("X"), pt1->Member("Y"), x1, y1
    );
    
    GRAPH_DrawArc(
        x0, y0,
        x1, y1, 
        getParam(symtab, "startang")->AsReal(), getParam(symtab, "endang")->AsReal(),
        getParam(symtab, "fill")->AsBoolean()
    );
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_DrawArc7Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_DrawArc7Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > context(getParam(symtab, "context"));
    ValidateGraphicsContext(context);

    int x0(0);
    int y0(0);
    int x1(0);
    int y1(0);
    transformCoordinates(
        context, 
        getParam(symtab, "x0"), getParam(symtab, "y0"), x0, y0, 
        getParam(symtab, "x1"), getParam(symtab, "y1"), x1, y1
    );
    
    GRAPH_DrawArc(
        x0, y0,
        x1, y1, 
        getParam(symtab, "startang")->AsReal(), getParam(symtab, "endang")->AsReal(),
        false
    );
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_DrawArc8Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_DrawArc8Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > context(getParam(symtab, "context"));
    ValidateGraphicsContext(context);

    int x0(0);
    int y0(0);
    int x1(0);
    int y1(0);
    transformCoordinates(
        context, 
        getParam(symtab, "x0"), getParam(symtab, "y0"), x0, y0, 
        getParam(symtab, "x1"), getParam(symtab, "y1"), x1, y1
    );
    
    GRAPH_DrawArc(
        x0, y0,
        x1, y1, 
        getParam(symtab, "startang")->AsReal(), getParam(symtab, "endang")->AsReal(),
        getParam(symtab, "fill")->AsBoolean()
    );
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_DrawPolygon2Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_DrawPolygon2Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > context(getParam(symtab, "context"));
    ValidateGraphicsContext(context);
    
    std::shared_ptr< iAtomic > points(getParam(symtab, "points"));
    const IntegerT npoints(points->Member("length")->AsInteger());
    
    if(npoints > 0)
    {
        GRAPH_PointT polygon[npoints] = { 0 };
        size_t pos(0);
        
        for(IntegerT i(points->Member("start")->AsInteger()), last_i(points->Member("finish")->AsInteger()); i <= last_i; ++i, ++pos)
        {
            int x(0);
            int y(0);
            transformCoordinate(
                context, 
                getParam(symtab, "x"), getParam(symtab, "y"), x, y
            );
         
            polygon[pos].x = static_cast< short int >(x);
            polygon[pos].y = static_cast< short int >(y);
        }
        
        GRAPH_DrawPolygon(polygon, static_cast< int >(npoints), false);
    }
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_DrawPolygon3Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_DrawPolygon3Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > context(getParam(symtab, "context"));
    ValidateGraphicsContext(context);
    
    std::shared_ptr< iAtomic > points(getParam(symtab, "points"));
    const IntegerT npoints(points->Member("length")->AsInteger());
    
    if(npoints > 0)
    {
        GRAPH_PointT polygon[npoints] = { 0 };
        size_t pos(0);
        
        for(IntegerT i(points->Member("start")->AsInteger()), last_i(points->Member("finish")->AsInteger()); i <= last_i; ++i, ++pos)
        {
            int x(0);
            int y(0);
            transformCoordinate(
                context, 
                getParam(symtab, "x"), getParam(symtab, "y"), x, y
            );
         
            polygon[pos].x = static_cast< short int >(x);
            polygon[pos].y = static_cast< short int >(y);
        }
        
        GRAPH_DrawPolygon(polygon, static_cast< int >(npoints), getParam(symtab, "fill")->AsBoolean());
    }
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_GetFontList0Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_GetFontList0Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    int nfonts(0);
    char **fontlist(GRAPH_GetFontList(&nfonts));

    std::shared_ptr< iAtomic > fontarray(ArrayValue::MakeValue(0));
    
    if(NULL != fontlist)
    {
        for(int i(0); i < nfonts; ++i)
        {
            fontarray->Add(StringValue::MakeValue(fontlist[i]));
        }
    }
    
    GRAPH_FreeFontList(fontlist);
    
    return fontarray;
}

/******************************************************************************

    dish::GRAPH_GetTextDimensions3Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_GetTextDimensions3Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > context(getParam(symtab, "context"));
    ValidateGraphicsContext(context);

    int width(0);
    int height(0);
    GRAPH_TextExtents(getParam(symtab, "text")->AsString(), width, height);
    
    //  Undo transformation
    std::shared_ptr< iAtomic > pt(getParam(symtab, "pt"));
    if(!context->Member("recoordinate")->AsBoolean())
    {
        pt->Member("x")->Assign(static_cast< IntegerT >(width));
        pt->Member("y")->Assign(static_cast< IntegerT >(height));
    }
    else
    {
        pt->Member("x")->Assign((static_cast< RealT >(width) / context->Member("scalex")->AsReal()) - context->Member("offsetx")->AsReal());
        pt->Member("y")->Assign((static_cast< RealT >(height) / context->Member("scaley")->AsReal()) - context->Member("offsety")->AsReal());
    }
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_GetTextDimensions4Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_GetTextDimensions4Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > context(getParam(symtab, "context"));
    ValidateGraphicsContext(context);

    int width(0);
    int height(0);
    GRAPH_TextExtents(getParam(symtab, "text")->AsString(), width, height);
    
    //  Undo transformation
    if(!context->Member("recoordinate")->AsBoolean())
    {
        getParam(symtab, "width")->Assign(static_cast< IntegerT >(width));
        getParam(symtab, "height")->Assign(static_cast< IntegerT >(height));
    }
    else
    {
        getParam(symtab, "width")->Assign((static_cast< RealT >(width) / context->Member("scalex")->AsReal()) - context->Member("offsetx")->AsReal());
        getParam(symtab, "height")->Assign((static_cast< RealT >(height) / context->Member("scaley")->AsReal()) - context->Member("offsety")->AsReal());
    }
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_DrawText2Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_DrawText2Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > context(getParam(symtab, "context"));
    ValidateGraphicsContext(context);

    int x(0);
    int y(0);
    transformCoordinate(
        context, 
        context->Member("xpos"), context->Member("ypos"), x, y
    );
    
    GRAPH_DrawText(x, y, getParam(symtab, "text")->AsString());
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_DrawText3Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_DrawText3Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > context(getParam(symtab, "context"));
    ValidateGraphicsContext(context);
    
    std::shared_ptr< iAtomic > pt(getParam(symtab, "pt"));

    int x(0);
    int y(0);
    transformCoordinate(
        context, 
        pt->Member("X"), pt->Member("Y"), x, y
    );
    
    GRAPH_DrawText(x, y, getParam(symtab, "text")->AsString());
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_DrawText4Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_DrawText4Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > context(getParam(symtab, "context"));
    ValidateGraphicsContext(context);

    int x(0);
    int y(0);
    transformCoordinate(
        context, 
        getParam(symtab, "x"), getParam(symtab, "y"), x, y
    );
    
    GRAPH_DrawText(x, y, getParam(symtab, "text")->AsString());
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_MoveTo2Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_MoveTo2Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > context(getParam(symtab, "context"));
    ValidateGraphicsContext(context);
    
    std::shared_ptr< iAtomic > pt(getParam(symtab, "pt"));
    
    int x(0);
    int y(0);
    transformCoordinate(
        context, 
        pt->Member("X"), pt->Member("Y"), x, y
    );
    
    context->Member("xpos")->Assign(static_cast< IntegerT >(x));
    context->Member("ypos")->Assign(static_cast< IntegerT >(y));
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_MoveTo3Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_MoveTo3Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > context(getParam(symtab, "context"));
    ValidateGraphicsContext(context);

    int x(0);
    int y(0);
    transformCoordinate(
        context, 
        getParam(symtab, "x"), getParam(symtab, "y"), x, y
    );
    
    context->Member("xpos")->Assign(static_cast< IntegerT >(x));
    context->Member("ypos")->Assign(static_cast< IntegerT >(y));
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_LineTo2Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_LineTo2Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > context(getParam(symtab, "context"));
    ValidateGraphicsContext(context);
    
    std::shared_ptr< iAtomic > pt(getParam(symtab, "pt"));
    
    int x(0);
    int y(0);
    transformCoordinate(
        context, 
        pt->Member("X"), pt->Member("Y"), x, y
    );
    
    GRAPH_DrawLine(
        static_cast< int >(context->Member("xpos")->AsInteger()),
        static_cast< int >(context->Member("ypos")->AsInteger()),
        x, y
    );
    
    context->Member("xpos")->Assign(static_cast< IntegerT >(x));
    context->Member("ypos")->Assign(static_cast< IntegerT >(y));
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GRAPH_LineTo3Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_LineTo3Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > context(getParam(symtab, "context"));
    ValidateGraphicsContext(context);

    int x(0);
    int y(0);
    transformCoordinate(
        context, 
        getParam(symtab, "x"), getParam(symtab, "y"), x, y
    );
    
    GRAPH_DrawLine(
        static_cast< int >(context->Member("xpos")->AsInteger()),
        static_cast< int >(context->Member("ypos")->AsInteger()),
        x, y
    );
    
    context->Member("xpos")->Assign(static_cast< IntegerT >(x));
    context->Member("ypos")->Assign(static_cast< IntegerT >(y));
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::GraphicsCallbacks class definitions

 ******************************************************************************/
 
const bool dish::GraphicsCallbacks::CALLBACK_CONTINUE(dish::GRAPH_EventProcessor::EVENT_CONTINUE);
const bool dish::GraphicsCallbacks::CALLBACK_TERMINATE(dish::GRAPH_EventProcessor::EVENT_TERMINATE);

bool dish::GraphicsCallbacks::Invoke(dish::LanguageSymbolTable &symtab, std::shared_ptr< dish::iAtomic > event) const
{
    assert(0 != event.get());
    
    const IntegerT type(event->Member("Type")->AsInteger());
    if(type < static_cast< IntegerT >(eventNUM))
    {
        ScopedScope scope(symtab);
        symtab.Insert("info", event);
        
        for(CallbackStackT::const_iterator i(mCallbackTable[type].begin()), last_i(mCallbackTable[type].end()); i != last_i; ++i)
        {
            try
            {
                if(CALLBACK_CONTINUE == (*i)->Execute(symtab)->AsBoolean())
                {
                    return CALLBACK_CONTINUE;
                }
            }
            catch(dish::iExecutableAtomic::ReturnValue e)
            {
                if(CALLBACK_CONTINUE == e.Value()->AsBoolean())
                {
                    return CALLBACK_TERMINATE;
                }
            }
        }
        
        return CALLBACK_CONTINUE;
    }
    
    std::stringstream message;
    message << "Illegal event-type value, ";
    message << type;
    message << " not within [";
    message << static_cast< int >(eventNull);
    message << ", ";
    message << static_cast< int >(eventNUM);
    message << ".";

    throw dish::IllegalIndexException(message.str());
}

dish::GraphicsCallbacks &dish::GraphicsCallbacks::Instance()
{
    static GraphicsCallbacks instance;
    
    return instance;
}

/******************************************************************************

    Graphics-event public function definitions

 ******************************************************************************/
 
////

std::shared_ptr< dish::iAtomic > dish::GRAPH_CreateIdleEventInfoT()
{
    static std::shared_ptr< StructureTypeAtomic > structure;
    
    if(0 == structure.get())
    {
        std::shared_ptr< IntegerTypeAtomic > integer_type(IntegerTypeAtomic::MakeValue());
    
        structure = StructureTypeAtomic::MakeValue();
        structure->Add("Type", integer_type);
        structure->Add("Num", integer_type);
    }
    
    return structure;
}

std::shared_ptr< dish::iAtomic > dish::GRAPH_CreateIdleEventInfo()
{
    static IntegerT num(0);

    std::shared_ptr< iAtomic > event(GRAPH_CreateIdleEventInfoT()->Declare());
    
    event->Member("Type")->Assign(static_cast< IntegerT >(GraphicsCallbacks::eventNull));
    event->Member("Num")->Assign(num++);
    
    event->Lock();
    
    return event;
}

////
 
std::shared_ptr< dish::iAtomic > dish::GRAPH_CreateRedrawEventInfoT()
{
    static std::shared_ptr< StructureTypeAtomic > structure;
    
    if(0 == structure.get())
    {
        std::shared_ptr< IntegerTypeAtomic > integer_type(IntegerTypeAtomic::MakeValue());
        
        structure = StructureTypeAtomic::MakeValue();
        structure->Add("Type", integer_type);
        structure->Add("X0", integer_type);
        structure->Add("Y0", integer_type);
        structure->Add("X1", integer_type);
        structure->Add("Y1", integer_type);
    }

    return structure;
}

std::shared_ptr< dish::iAtomic > dish::GRAPH_CreateRedrawEventInfo(const int x0, const int y0, const int x1, const int y1)
{
    std::shared_ptr< iAtomic > event(GRAPH_CreateRedrawEventInfoT()->Declare());
    
    event->Member("Type")->Assign(static_cast< IntegerT >(GraphicsCallbacks::eventRedraw));
    event->Member("X0")->Assign(static_cast< IntegerT >(x0));
    event->Member("Y0")->Assign(static_cast< IntegerT >(y0));
    event->Member("X1")->Assign(static_cast< IntegerT >(x1));
    event->Member("Y1")->Assign(static_cast< IntegerT >(y1));
    
    event->Lock();
    
    return event;
}

////

std::shared_ptr< dish::iAtomic > dish::GRAPH_CreateResizeEventInfoT()
{
    static std::shared_ptr< StructureTypeAtomic > structure;
    
    if(0 == structure.get())
    {
        std::shared_ptr< IntegerTypeAtomic > integer_type(IntegerTypeAtomic::MakeValue());
        
        structure = StructureTypeAtomic::MakeValue();
        structure->Add("Type", integer_type);
        structure->Add("Width", integer_type);
        structure->Add("Height", integer_type);
    }

    return structure;
}

std::shared_ptr< dish::iAtomic > dish::GRAPH_CreateResizeEventInfo(const int newwidth, const int newheight)
{
    std::shared_ptr< iAtomic > event(GRAPH_CreateResizeEventInfoT()->Declare());
    
    event->Member("Type")->Assign(static_cast< IntegerT >(GraphicsCallbacks::eventResize));
    event->Member("Width")->Assign(static_cast< IntegerT >(newwidth));
    event->Member("Height")->Assign(static_cast< IntegerT >(newheight));
    
    event->Lock();
    
    return event;
}

////

std::shared_ptr< dish::iAtomic > dish::GRAPH_CreateKeyEventInfoT()
{
    static std::shared_ptr< StructureTypeAtomic > structure;
    
    if(0 == structure.get())
    {
        structure = StructureTypeAtomic::MakeValue();
        
        {
            std::shared_ptr< IntegerTypeAtomic > integer_type(IntegerTypeAtomic::MakeValue());
            structure->Add("Type", integer_type);
            structure->Add("Key", integer_type);
            structure->Add("X", integer_type);
            structure->Add("Y", integer_type);
        }
        
        {
            std::shared_ptr< BooleanTypeAtomic > boolean_type(BooleanTypeAtomic::MakeValue());
            structure->Add("ShiftState", boolean_type);
            structure->Add("CtrlState", boolean_type);
            structure->Add("AltState", boolean_type);
        }
    }

    return structure;
}

std::shared_ptr< dish::iAtomic > dish::GRAPH_CreateKeyPressEventInfo(const int x, const int y, const int ch, const bool shiftst, const bool ctrlst, const bool altst)
{
    std::shared_ptr< iAtomic > event(GRAPH_CreateKeyEventInfoT()->Declare());
    
    event->Member("Type")->Assign(static_cast< IntegerT >(GraphicsCallbacks::eventKeyPress));
    event->Member("Key")->Assign(static_cast< IntegerT >(ch));
    event->Member("X")->Assign(static_cast< IntegerT >(x));
    event->Member("Y")->Assign(static_cast< IntegerT >(y));
    event->Member("ShiftState")->Assign(static_cast< BooleanT >(shiftst));
    event->Member("CtrlState")->Assign(static_cast< BooleanT >(ctrlst));
    event->Member("AltState")->Assign(static_cast< BooleanT >(altst));
    
    event->Lock();
    
    return event;
}

std::shared_ptr< dish::iAtomic > dish::GRAPH_CreateKeyReleaseEventInfo(const int x, const int y, const int ch, const bool shiftst, const bool ctrlst, const bool altst)
{
    std::shared_ptr< iAtomic > event(GRAPH_CreateKeyEventInfoT()->Declare());
    
    event->Member("Type")->Assign(static_cast< IntegerT >(GraphicsCallbacks::eventKeyRelease));
    event->Member("Key")->Assign(static_cast< IntegerT >(ch));
    event->Member("X")->Assign(static_cast< IntegerT >(x));
    event->Member("Y")->Assign(static_cast< IntegerT >(y));
    event->Member("ShiftState")->Assign(static_cast< BooleanT >(shiftst));
    event->Member("CtrlState")->Assign(static_cast< BooleanT >(ctrlst));
    event->Member("AltState")->Assign(static_cast< BooleanT >(altst));
    
    event->Lock();
    
    return event;
}

////

std::shared_ptr< dish::iAtomic > dish::GRAPH_CreateButtonEventInfoT()
{
    static std::shared_ptr< StructureTypeAtomic > structure;
    
    if(0 == structure.get())
    {
        structure = StructureTypeAtomic::MakeValue();
        
        {
            std::shared_ptr< IntegerTypeAtomic > integer_type(IntegerTypeAtomic::MakeValue());
            structure->Add("Type", integer_type);
            structure->Add("Button", integer_type);
            structure->Add("X", integer_type);
            structure->Add("Y", integer_type);
        }
        
        {
            std::shared_ptr< BooleanTypeAtomic > boolean_type(BooleanTypeAtomic::MakeValue());
            structure->Add("ShiftState", boolean_type);
            structure->Add("CtrlState", boolean_type);
            structure->Add("AltState", boolean_type);
        }
    }

    return structure;
}

std::shared_ptr< dish::iAtomic > dish::GRAPH_CreateButtonPressEventInfo(const int x, const int y, const int button, const bool shiftst, const bool ctrlst, const bool altst)
{
    std::shared_ptr< iAtomic > event(GRAPH_CreateButtonEventInfoT()->Declare());
    
    event->Member("Type")->Assign(static_cast< IntegerT >(GraphicsCallbacks::eventButtonPress));
    event->Member("Button")->Assign(static_cast< IntegerT >(button));
    event->Member("X")->Assign(static_cast< IntegerT >(x));
    event->Member("Y")->Assign(static_cast< IntegerT >(y));
    event->Member("ShiftState")->Assign(static_cast< BooleanT >(shiftst));
    event->Member("CtrlState")->Assign(static_cast< BooleanT >(ctrlst));
    event->Member("AltState")->Assign(static_cast< BooleanT >(altst));
    
    event->Lock();
    
    return event;
}

std::shared_ptr< dish::iAtomic > dish::GRAPH_CreateButtonReleaseEventInfo(const int x, const int y, const int button, const bool shiftst, const bool ctrlst, const bool altst)
{
    std::shared_ptr< iAtomic > event(GRAPH_CreateButtonEventInfoT()->Declare());
    
    event->Member("Type")->Assign(static_cast< IntegerT >(GraphicsCallbacks::eventButtonRelease));
    event->Member("Button")->Assign(static_cast< IntegerT >(button));
    event->Member("X")->Assign(static_cast< IntegerT >(x));
    event->Member("Y")->Assign(static_cast< IntegerT >(y));
    event->Member("ShiftState")->Assign(static_cast< BooleanT >(shiftst));
    event->Member("CtrlState")->Assign(static_cast< BooleanT >(ctrlst));
    event->Member("AltState")->Assign(static_cast< BooleanT >(altst));
    
    event->Lock();
    
    return event;
}

////

