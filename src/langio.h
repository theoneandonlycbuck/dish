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

#ifndef DISH_LANGIO_H
#define DISH_LANGIO_H

#include "dishconfig.h"

#include <memory>

#include "atomics.h"
#include "inline.h"
#include "language.h"

namespace dish
{

    ////////////////////////////////////////////////////////////////////////////

    class PrintFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE PrintFunction() : dish::ExecutableAtomic() { addParam("str", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< PrintFunction > MakeValue() { return std::shared_ptr< PrintFunction >(new PrintFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class Println0Function : public dish::ExecutableAtomic
    {
        protected:
            INLINE Println0Function() : dish::ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< Println0Function > MakeValue() { return std::shared_ptr< Println0Function >(new Println0Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class PrintlnFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE PrintlnFunction() : dish::ExecutableAtomic() { addParam("str", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< PrintlnFunction > MakeValue() { return std::shared_ptr< PrintlnFunction >(new PrintlnFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class NewlnFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE NewlnFunction() : dish::ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< NewlnFunction > MakeValue() { return std::shared_ptr< NewlnFunction >(new NewlnFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////

    class KeyPressedFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE KeyPressedFunction() : dish::ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< KeyPressedFunction > MakeValue() { return std::shared_ptr< KeyPressedFunction >(new KeyPressedFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class ReadFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE ReadFunction() : dish::ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< ReadFunction > MakeValue() { return std::shared_ptr< ReadFunction >(new ReadFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class ReadChFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE ReadChFunction() : dish::ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< ReadChFunction > MakeValue() { return std::shared_ptr< ReadChFunction >(new ReadChFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class ReadIntegerFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE ReadIntegerFunction() : dish::ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< ReadIntegerFunction > MakeValue() { return std::shared_ptr< ReadIntegerFunction >(new ReadIntegerFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class ReadRealFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE ReadRealFunction() : dish::ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< ReadRealFunction > MakeValue() { return std::shared_ptr< ReadRealFunction >(new ReadRealFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class ReadlnFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE ReadlnFunction() : dish::ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< ReadlnFunction > MakeValue() { return std::shared_ptr< ReadlnFunction >(new ReadlnFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////

}

#endif

