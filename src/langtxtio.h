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

#ifndef DISH_LANGTXTIO_H
#define DISH_LANGTXTIO_H

#include "dishconfig.h"

#include <memory>

#include "atomics.h"
#include "inline.h"

namespace dish
{

    ////////////////////////////////////////////////////////////////////////////

    class TEXTIO_StartFunction : public ExecutableAtomic
    {
        protected:
            INLINE TEXTIO_StartFunction() : ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< TEXTIO_StartFunction > MakeValue() { return std::shared_ptr< TEXTIO_StartFunction >(new TEXTIO_StartFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class TEXTIO_IsStartedFunction : public ExecutableAtomic
    {
        protected:
            INLINE TEXTIO_IsStartedFunction() : ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< TEXTIO_IsStartedFunction > MakeValue() { return std::shared_ptr< TEXTIO_IsStartedFunction >(new TEXTIO_IsStartedFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class TEXTIO_RefreshFunction : public ExecutableAtomic
    {
        protected:
            INLINE TEXTIO_RefreshFunction() : ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< TEXTIO_RefreshFunction > MakeValue() { return std::shared_ptr< TEXTIO_RefreshFunction >(new TEXTIO_RefreshFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class TEXTIO_ClearFunction : public ExecutableAtomic
    {
        protected:
            INLINE TEXTIO_ClearFunction() : ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< TEXTIO_ClearFunction > MakeValue() { return std::shared_ptr< TEXTIO_ClearFunction >(new TEXTIO_ClearFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class TEXTIO_EndFunction : public ExecutableAtomic
    {
        protected:
            INLINE TEXTIO_EndFunction() : ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< TEXTIO_EndFunction > MakeValue() { return std::shared_ptr< TEXTIO_EndFunction >(new TEXTIO_EndFunction()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    ////////////////////////////////////////////////////////////////////////////

    class TEXTIO_GetXSizeFunction : public ExecutableAtomic
    {
        protected:
            INLINE TEXTIO_GetXSizeFunction() : ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< TEXTIO_GetXSizeFunction > MakeValue() { return std::shared_ptr< TEXTIO_GetXSizeFunction >(new TEXTIO_GetXSizeFunction()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class TEXTIO_GetYSizeFunction : public ExecutableAtomic
    {
        protected:
            INLINE TEXTIO_GetYSizeFunction() : ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< TEXTIO_GetYSizeFunction > MakeValue() { return std::shared_ptr< TEXTIO_GetYSizeFunction >(new TEXTIO_GetYSizeFunction()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class TEXTIO_MoveToFunction : public ExecutableAtomic
    {
        protected:
            INLINE TEXTIO_MoveToFunction() : ExecutableAtomic() { addParam("x", REFERENCE_PARAMETER); addParam("y", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< TEXTIO_MoveToFunction > MakeValue() { return std::shared_ptr< TEXTIO_MoveToFunction >(new TEXTIO_MoveToFunction()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    ////////////////////////////////////////////////////////////////////////////

    class TEXTIO_AttrNormalFunction : public ExecutableAtomic
    {
        protected:
            INLINE TEXTIO_AttrNormalFunction() : ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< TEXTIO_AttrNormalFunction > MakeValue() { return std::shared_ptr< TEXTIO_AttrNormalFunction >(new TEXTIO_AttrNormalFunction()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class TEXTIO_AttrGetFunction : public ExecutableAtomic
    {
        protected:
            INLINE TEXTIO_AttrGetFunction() : ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< TEXTIO_AttrGetFunction > MakeValue() { return std::shared_ptr< TEXTIO_AttrGetFunction >(new TEXTIO_AttrGetFunction()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class TEXTIO_AttrSetFunction : public ExecutableAtomic
    {
        protected:
            INLINE TEXTIO_AttrSetFunction() : ExecutableAtomic() { addParam("attr", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< TEXTIO_AttrSetFunction > MakeValue() { return std::shared_ptr< TEXTIO_AttrSetFunction >(new TEXTIO_AttrSetFunction()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class TEXTIO_AttrOnFunction : public ExecutableAtomic
    {
        protected:
            INLINE TEXTIO_AttrOnFunction() : ExecutableAtomic() { addParam("attr", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< TEXTIO_AttrOnFunction > MakeValue() { return std::shared_ptr< TEXTIO_AttrOnFunction >(new TEXTIO_AttrOnFunction()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class TEXTIO_AttrOffFunction : public ExecutableAtomic
    {
        protected:
            INLINE TEXTIO_AttrOffFunction() : ExecutableAtomic() { addParam("attr", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< TEXTIO_AttrOffFunction > MakeValue() { return std::shared_ptr< TEXTIO_AttrOffFunction >(new TEXTIO_AttrOffFunction()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class TEXTIO_SetForegroundColorFunction : public ExecutableAtomic
    {
        protected:
            INLINE TEXTIO_SetForegroundColorFunction() : ExecutableAtomic() { addParam("color", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< TEXTIO_SetForegroundColorFunction > MakeValue() { return std::shared_ptr< TEXTIO_SetForegroundColorFunction >(new TEXTIO_SetForegroundColorFunction()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class TEXTIO_GetForegroundColorFunction : public ExecutableAtomic
    {
        protected:
            INLINE TEXTIO_GetForegroundColorFunction() : ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< TEXTIO_GetForegroundColorFunction > MakeValue() { return std::shared_ptr< TEXTIO_GetForegroundColorFunction >(new TEXTIO_GetForegroundColorFunction()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class TEXTIO_SetBackgroundColorFunction : public ExecutableAtomic
    {
        protected:
            INLINE TEXTIO_SetBackgroundColorFunction() : ExecutableAtomic() { addParam("color", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< TEXTIO_SetBackgroundColorFunction > MakeValue() { return std::shared_ptr< TEXTIO_SetBackgroundColorFunction >(new TEXTIO_SetBackgroundColorFunction()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class TEXTIO_GetBackgroundColorFunction : public ExecutableAtomic
    {
        protected:
            INLINE TEXTIO_GetBackgroundColorFunction() : ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< TEXTIO_GetBackgroundColorFunction > MakeValue() { return std::shared_ptr< TEXTIO_GetBackgroundColorFunction >(new TEXTIO_GetBackgroundColorFunction()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class TEXTIO_SetColorFunction : public ExecutableAtomic
    {
        protected:
            INLINE TEXTIO_SetColorFunction() : ExecutableAtomic() { addParam("fore", REFERENCE_PARAMETER); addParam("back", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< TEXTIO_SetColorFunction > MakeValue() { return std::shared_ptr< TEXTIO_SetColorFunction >(new TEXTIO_SetColorFunction()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class TEXTIO_SetCursorFunction : public ExecutableAtomic
    {
        protected:
            INLINE TEXTIO_SetCursorFunction() : ExecutableAtomic() { addParam("visible", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< TEXTIO_SetCursorFunction > MakeValue() { return std::shared_ptr< TEXTIO_SetCursorFunction >(new TEXTIO_SetCursorFunction()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    ////////////////////////////////////////////////////////////////////////////

}

#endif

