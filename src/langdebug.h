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

#ifndef DISH_LANG_DEBUG_H
#define DISH_LANG_DEBUG_H

#include "dishconfig.h"

#include <memory>

#include "atomics.h"
#include "inline.h"

namespace dish
{

    ////////////////////////////////////////////////////////////////////////////
    
    class DebugPrintSymbolTableFunction : public ExecutableAtomic
    {
        protected:
            INLINE DebugPrintSymbolTableFunction() : ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< DebugPrintSymbolTableFunction > MakeValue() { return std::shared_ptr< DebugPrintSymbolTableFunction >(new DebugPrintSymbolTableFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    class DebugPrintSymbolTable1Function : public ExecutableAtomic
    {
        protected:
            INLINE DebugPrintSymbolTable1Function() : ExecutableAtomic() { addParam("logfile", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< DebugPrintSymbolTable1Function > MakeValue() { return std::shared_ptr< DebugPrintSymbolTable1Function >(new DebugPrintSymbolTable1Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class DebugPrintSymbolTableStatsFunction : public ExecutableAtomic
    {
        protected:
            INLINE DebugPrintSymbolTableStatsFunction() : ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< DebugPrintSymbolTableStatsFunction > MakeValue() { return std::shared_ptr< DebugPrintSymbolTableStatsFunction >(new DebugPrintSymbolTableStatsFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    class DebugPrintSymbolTableStats1Function : public ExecutableAtomic
    {
        protected:
            INLINE DebugPrintSymbolTableStats1Function() : ExecutableAtomic() { addParam("logfile", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< DebugPrintSymbolTableStats1Function > MakeValue() { return std::shared_ptr< DebugPrintSymbolTableStats1Function >(new DebugPrintSymbolTableStats1Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////

    class DebugPrintParseTreeNodeStatsFunction : public ExecutableAtomic
    {
        protected:
            INLINE DebugPrintParseTreeNodeStatsFunction() : ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< DebugPrintParseTreeNodeStatsFunction > MakeValue() { return std::shared_ptr< DebugPrintParseTreeNodeStatsFunction >(new DebugPrintParseTreeNodeStatsFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class DebugPrintParseTreeNodeStats1Function : public ExecutableAtomic
    {
        protected:
            INLINE DebugPrintParseTreeNodeStats1Function() : ExecutableAtomic() { addParam("logfile", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< DebugPrintParseTreeNodeStats1Function > MakeValue() { return std::shared_ptr< DebugPrintParseTreeNodeStats1Function >(new DebugPrintParseTreeNodeStats1Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////

    class DebugPrintParseTreeFunction : public ExecutableAtomic
    {
        protected:
            INLINE DebugPrintParseTreeFunction() : ExecutableAtomic() { addParam("stmt", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< DebugPrintParseTreeFunction > MakeValue() { return std::shared_ptr< DebugPrintParseTreeFunction >(new DebugPrintParseTreeFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class DebugPrintParseTree2Function : public ExecutableAtomic
    {
        protected:
            INLINE DebugPrintParseTree2Function() : ExecutableAtomic() { addParam("logfile", REFERENCE_PARAMETER); addParam("stmt", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< DebugPrintParseTree2Function > MakeValue() { return std::shared_ptr< DebugPrintParseTree2Function >(new DebugPrintParseTree2Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////

    class DebugCurrentStackDepthFunction : public ExecutableAtomic
    {
        protected:
            INLINE DebugCurrentStackDepthFunction() : ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< DebugCurrentStackDepthFunction > MakeValue() { return std::shared_ptr< DebugCurrentStackDepthFunction >(new DebugCurrentStackDepthFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////

    class DebugLogFunction : public ExecutableAtomic
    {
        protected:
            INLINE DebugLogFunction() : ExecutableAtomic() { addParam("logfile", REFERENCE_PARAMETER); addParam("message", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< DebugLogFunction > MakeValue() { return std::shared_ptr< DebugLogFunction >(new DebugLogFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////

}

#endif

