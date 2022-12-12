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

#ifndef DISH_LANGDB_H
#define DISH_LANGDB_H

#include "dishconfig.h"

#include <memory>

#include "atomics.h"
#include "inline.h"
#include "language.h"
#include "types.h"

namespace dish
{

    ////////////////////////////////////////////////////////////////////////////
    
    extern std::shared_ptr< iAtomic > CreateDbConnectionParametersType();

    ////////////////////////////////////////////////////////////////////////////

    class DbMakeDefaultConnectionParametersFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE DbMakeDefaultConnectionParametersFunction() : dish::ExecutableAtomic() { addParam("connparams", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< DbMakeDefaultConnectionParametersFunction > MakeValue() { return std::shared_ptr< DbMakeDefaultConnectionParametersFunction >(new DbMakeDefaultConnectionParametersFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class DbMakeDefaultConnectionParameters2Function : public dish::ExecutableAtomic
    {
        protected:
            INLINE DbMakeDefaultConnectionParameters2Function() : dish::ExecutableAtomic() { addParam("type", REFERENCE_PARAMETER); addParam("connparams", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< DbMakeDefaultConnectionParameters2Function > MakeValue() { return std::shared_ptr< DbMakeDefaultConnectionParameters2Function >(new DbMakeDefaultConnectionParameters2Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////

    class DbOpenConnectionFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE DbOpenConnectionFunction() : dish::ExecutableAtomic() { addParam("type", REFERENCE_PARAMETER); addParam("config", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< DbOpenConnectionFunction > MakeValue() { return std::shared_ptr< DbOpenConnectionFunction >(new DbOpenConnectionFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class DbCloseConnectionFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE DbCloseConnectionFunction() : dish::ExecutableAtomic() { addParam("handle", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< DbCloseConnectionFunction > MakeValue() { return std::shared_ptr< DbCloseConnectionFunction >(new DbCloseConnectionFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class DbCloseAllConnectionsFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE DbCloseAllConnectionsFunction() : dish::ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< DbCloseAllConnectionsFunction > MakeValue() { return std::shared_ptr< DbCloseAllConnectionsFunction >(new DbCloseAllConnectionsFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    ////////////////////////////////////////////////////////////////////////////

    class DbIsOpenFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE DbIsOpenFunction() : dish::ExecutableAtomic() { addParam("handle", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< DbIsOpenFunction > MakeValue() { return std::shared_ptr< DbIsOpenFunction >(new DbIsOpenFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class DbNumOpenConnectionsFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE DbNumOpenConnectionsFunction() : dish::ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< DbNumOpenConnectionsFunction > MakeValue() { return std::shared_ptr< DbNumOpenConnectionsFunction >(new DbNumOpenConnectionsFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class DbNumOpenConnections1Function : public dish::ExecutableAtomic
    {
        protected:
            INLINE DbNumOpenConnections1Function() : dish::ExecutableAtomic() { addParam("validate", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< DbNumOpenConnections1Function > MakeValue() { return std::shared_ptr< DbNumOpenConnections1Function >(new DbNumOpenConnections1Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    ////////////////////////////////////////////////////////////////////////////

    class DbServerVersionFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE DbServerVersionFunction() : dish::ExecutableAtomic() { addParam("handle", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< DbServerVersionFunction > MakeValue() { return std::shared_ptr< DbServerVersionFunction >(new DbServerVersionFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    ////////////////////////////////////////////////////////////////////////////

    class DbIssueQueryFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE DbIssueQueryFunction() : dish::ExecutableAtomic() { addParam("handle", REFERENCE_PARAMETER); addParam("query", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< DbIssueQueryFunction > MakeValue() { return std::shared_ptr< DbIssueQueryFunction >(new DbIssueQueryFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    ////////////////////////////////////////////////////////////////////////////

}

#endif

