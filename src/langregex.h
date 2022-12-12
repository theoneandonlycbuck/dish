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

#ifndef DISH_LANGREGEX_H
#define DISH_LANGREGEX_H

#include "dishconfig.h"

#include <memory>

#include "atomics.h"
#include "inline.h"
#include "langid.h"
#include "symtab.h"
#include "types.h"

#define REGEX_MAX_NUM_HANDLES       15

namespace dish
{

    ////////////////////////////////////////////////////////////////////////////

    class CreateRegularExpressionFunction : public ExecutableAtomic
    {
        protected:
            INLINE CreateRegularExpressionFunction() : ExecutableAtomic() { addParam("regex", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< CreateRegularExpressionFunction > MakeValue() { return std::shared_ptr< CreateRegularExpressionFunction >(new CreateRegularExpressionFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class NumCreatedRegularExpressionFunction : public ExecutableAtomic
    {
        protected:
            INLINE NumCreatedRegularExpressionFunction() : ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< NumCreatedRegularExpressionFunction > MakeValue() { return std::shared_ptr< NumCreatedRegularExpressionFunction >(new NumCreatedRegularExpressionFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class IsCreatedRegularExpressionFunction : public ExecutableAtomic
    {
        protected:
            INLINE IsCreatedRegularExpressionFunction() : ExecutableAtomic() { addParam("handle", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< IsCreatedRegularExpressionFunction > MakeValue() { return std::shared_ptr< IsCreatedRegularExpressionFunction >(new IsCreatedRegularExpressionFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class DestroyRegularExpressionFunction : public ExecutableAtomic
    {
        protected:
            INLINE DestroyRegularExpressionFunction() : ExecutableAtomic() { addParam("handle", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< DestroyRegularExpressionFunction > MakeValue() { return std::shared_ptr< DestroyRegularExpressionFunction >(new DestroyRegularExpressionFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class DestroyAllRegularExpressionFunction : public ExecutableAtomic
    {
        protected:
            INLINE DestroyAllRegularExpressionFunction() : ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< DestroyAllRegularExpressionFunction > MakeValue() { return std::shared_ptr< DestroyAllRegularExpressionFunction >(new DestroyAllRegularExpressionFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class MatchRegularExpressionFunction : public ExecutableAtomic
    {
        protected:
            INLINE MatchRegularExpressionFunction() : ExecutableAtomic() { addParam("handle", REFERENCE_PARAMETER); addParam("src", REFERENCE_PARAMETER); addParam("pos", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< MatchRegularExpressionFunction > MakeValue() { return std::shared_ptr< MatchRegularExpressionFunction >(new MatchRegularExpressionFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class ReplaceNextRegularExpressionFunction : public ExecutableAtomic
    {
        protected:
            INLINE ReplaceNextRegularExpressionFunction() : ExecutableAtomic() { addParam("handle", REFERENCE_PARAMETER); addParam("src", REFERENCE_PARAMETER); addParam("pos", REFERENCE_PARAMETER); addParam("replace", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< ReplaceNextRegularExpressionFunction > MakeValue() { return std::shared_ptr< ReplaceNextRegularExpressionFunction >(new ReplaceNextRegularExpressionFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class ReplaceAllRegularExpressionFunction : public ExecutableAtomic
    {
        protected:
            INLINE ReplaceAllRegularExpressionFunction() : ExecutableAtomic() { addParam("handle", REFERENCE_PARAMETER); addParam("src", REFERENCE_PARAMETER); addParam("pos", REFERENCE_PARAMETER); addParam("replace", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< ReplaceAllRegularExpressionFunction > MakeValue() { return std::shared_ptr< ReplaceAllRegularExpressionFunction >(new ReplaceAllRegularExpressionFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////
    
    extern void RegExDestroyAllHandles();

    ////////////////////////////////////////////////////////////////////////////
    
}

#endif

