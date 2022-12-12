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

#ifndef DISH_LANGZIP_H
#define DISH_LANGZIP_H

#include "dishconfig.h"

#include <memory>

#include "atomics.h"
#include "inline.h"
#include "language.h"
#include "types.h"

namespace dish
{

    ////////////////////////////////////////////////////////////////////////////

    class Zip1Function : public ExecutableAtomic
    {
        protected:
            INLINE Zip1Function() : ExecutableAtomic()
            {
                addParam("arg1", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< Zip1Function > MakeValue() { return std::shared_ptr< Zip1Function >(new Zip1Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class Zip2Function : public ExecutableAtomic
    {
        protected:
            INLINE Zip2Function() : ExecutableAtomic()
            {
                addParam("arg1", REFERENCE_PARAMETER);
                addParam("arg2", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< Zip2Function > MakeValue() { return std::shared_ptr< Zip2Function >(new Zip2Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class Zip3Function : public ExecutableAtomic
    {
        protected:
            INLINE Zip3Function() : ExecutableAtomic()
            {
                addParam("arg1", REFERENCE_PARAMETER);
                addParam("arg2", REFERENCE_PARAMETER);
                addParam("arg3", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< Zip3Function > MakeValue() { return std::shared_ptr< Zip3Function >(new Zip3Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class Zip4Function : public ExecutableAtomic
    {
        protected:
            INLINE Zip4Function() : ExecutableAtomic()
            {
                addParam("arg1", REFERENCE_PARAMETER);
                addParam("arg2", REFERENCE_PARAMETER);
                addParam("arg3", REFERENCE_PARAMETER);
                addParam("arg4", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< Zip4Function > MakeValue() { return std::shared_ptr< Zip4Function >(new Zip4Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class Zip5Function : public ExecutableAtomic
    {
        protected:
            INLINE Zip5Function() : ExecutableAtomic()
            {
                addParam("arg1", REFERENCE_PARAMETER);
                addParam("arg2", REFERENCE_PARAMETER);
                addParam("arg3", REFERENCE_PARAMETER);
                addParam("arg4", REFERENCE_PARAMETER);
                addParam("arg5", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< Zip5Function > MakeValue() { return std::shared_ptr< Zip5Function >(new Zip5Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class Zip6Function : public ExecutableAtomic
    {
        protected:
            INLINE Zip6Function() : ExecutableAtomic()
            {
                addParam("arg1", REFERENCE_PARAMETER);
                addParam("arg2", REFERENCE_PARAMETER);
                addParam("arg3", REFERENCE_PARAMETER);
                addParam("arg4", REFERENCE_PARAMETER);
                addParam("arg5", REFERENCE_PARAMETER);
                addParam("arg6", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< Zip6Function > MakeValue() { return std::shared_ptr< Zip6Function >(new Zip6Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class Zip7Function : public ExecutableAtomic
    {
        protected:
            INLINE Zip7Function() : ExecutableAtomic()
            {
                addParam("arg1", REFERENCE_PARAMETER);
                addParam("arg2", REFERENCE_PARAMETER);
                addParam("arg3", REFERENCE_PARAMETER);
                addParam("arg4", REFERENCE_PARAMETER);
                addParam("arg5", REFERENCE_PARAMETER);
                addParam("arg6", REFERENCE_PARAMETER);
                addParam("arg7", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< Zip7Function > MakeValue() { return std::shared_ptr< Zip7Function >(new Zip7Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class Zip8Function : public ExecutableAtomic
    {
        protected:
            INLINE Zip8Function() : ExecutableAtomic()
            {
                addParam("arg1", REFERENCE_PARAMETER);
                addParam("arg2", REFERENCE_PARAMETER);
                addParam("arg3", REFERENCE_PARAMETER);
                addParam("arg4", REFERENCE_PARAMETER);
                addParam("arg5", REFERENCE_PARAMETER);
                addParam("arg6", REFERENCE_PARAMETER);
                addParam("arg7", REFERENCE_PARAMETER);
                addParam("arg8", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< Zip8Function > MakeValue() { return std::shared_ptr< Zip8Function >(new Zip8Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class Zip9Function : public ExecutableAtomic
    {
        protected:
            INLINE Zip9Function() : ExecutableAtomic()
            {
                addParam("arg1", REFERENCE_PARAMETER);
                addParam("arg2", REFERENCE_PARAMETER);
                addParam("arg3", REFERENCE_PARAMETER);
                addParam("arg4", REFERENCE_PARAMETER);
                addParam("arg5", REFERENCE_PARAMETER);
                addParam("arg6", REFERENCE_PARAMETER);
                addParam("arg7", REFERENCE_PARAMETER);
                addParam("arg8", REFERENCE_PARAMETER);
                addParam("arg9", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< Zip9Function > MakeValue() { return std::shared_ptr< Zip9Function >(new Zip9Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class Zip10Function : public ExecutableAtomic
    {
        protected:
            INLINE Zip10Function() : dish::ExecutableAtomic()
            {
                addParam("arg1", REFERENCE_PARAMETER);
                addParam("arg2", REFERENCE_PARAMETER);
                addParam("arg3", REFERENCE_PARAMETER);
                addParam("arg4", REFERENCE_PARAMETER);
                addParam("arg5", REFERENCE_PARAMETER);
                addParam("arg6", REFERENCE_PARAMETER);
                addParam("arg7", REFERENCE_PARAMETER);
                addParam("arg8", REFERENCE_PARAMETER);
                addParam("arg9", REFERENCE_PARAMETER);
                addParam("arg10", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< Zip10Function > MakeValue() { return std::shared_ptr< Zip10Function >(new Zip10Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////

    class ZipTogether1Function : public ExecutableAtomic
    {
        protected:
            INLINE ZipTogether1Function() : ExecutableAtomic()
            {
                addParam("arg1", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< ZipTogether1Function > MakeValue() { return std::shared_ptr< ZipTogether1Function >(new ZipTogether1Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class ZipTogether2Function : public ExecutableAtomic
    {
        protected:
            INLINE ZipTogether2Function() : ExecutableAtomic()
            {
                addParam("arg1", REFERENCE_PARAMETER);
                addParam("arg2", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< ZipTogether2Function > MakeValue() { return std::shared_ptr< ZipTogether2Function >(new ZipTogether2Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class ZipTogether3Function : public ExecutableAtomic
    {
        protected:
            INLINE ZipTogether3Function() : ExecutableAtomic()
            {
                addParam("arg1", REFERENCE_PARAMETER);
                addParam("arg2", REFERENCE_PARAMETER);
                addParam("arg3", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< ZipTogether3Function > MakeValue() { return std::shared_ptr< ZipTogether3Function >(new ZipTogether3Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class ZipTogether4Function : public ExecutableAtomic
    {
        protected:
            INLINE ZipTogether4Function() : ExecutableAtomic()
            {
                addParam("arg1", REFERENCE_PARAMETER);
                addParam("arg2", REFERENCE_PARAMETER);
                addParam("arg3", REFERENCE_PARAMETER);
                addParam("arg4", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< ZipTogether4Function > MakeValue() { return std::shared_ptr< ZipTogether4Function >(new ZipTogether4Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class ZipTogether5Function : public ExecutableAtomic
    {
        protected:
            INLINE ZipTogether5Function() : ExecutableAtomic()
            {
                addParam("arg1", REFERENCE_PARAMETER);
                addParam("arg2", REFERENCE_PARAMETER);
                addParam("arg3", REFERENCE_PARAMETER);
                addParam("arg4", REFERENCE_PARAMETER);
                addParam("arg5", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< ZipTogether5Function > MakeValue() { return std::shared_ptr< ZipTogether5Function >(new ZipTogether5Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class ZipTogether6Function : public ExecutableAtomic
    {
        protected:
            INLINE ZipTogether6Function() : ExecutableAtomic()
            {
                addParam("arg1", REFERENCE_PARAMETER);
                addParam("arg2", REFERENCE_PARAMETER);
                addParam("arg3", REFERENCE_PARAMETER);
                addParam("arg4", REFERENCE_PARAMETER);
                addParam("arg5", REFERENCE_PARAMETER);
                addParam("arg6", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< ZipTogether6Function > MakeValue() { return std::shared_ptr< ZipTogether6Function >(new ZipTogether6Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class ZipTogether7Function : public ExecutableAtomic
    {
        protected:
            INLINE ZipTogether7Function() : ExecutableAtomic()
            {
                addParam("arg1", REFERENCE_PARAMETER);
                addParam("arg2", REFERENCE_PARAMETER);
                addParam("arg3", REFERENCE_PARAMETER);
                addParam("arg4", REFERENCE_PARAMETER);
                addParam("arg5", REFERENCE_PARAMETER);
                addParam("arg6", REFERENCE_PARAMETER);
                addParam("arg7", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< ZipTogether7Function > MakeValue() { return std::shared_ptr< ZipTogether7Function >(new ZipTogether7Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class ZipTogether8Function : public ExecutableAtomic
    {
        protected:
            INLINE ZipTogether8Function() : ExecutableAtomic()
            {
                addParam("arg1", REFERENCE_PARAMETER);
                addParam("arg2", REFERENCE_PARAMETER);
                addParam("arg3", REFERENCE_PARAMETER);
                addParam("arg4", REFERENCE_PARAMETER);
                addParam("arg5", REFERENCE_PARAMETER);
                addParam("arg6", REFERENCE_PARAMETER);
                addParam("arg7", REFERENCE_PARAMETER);
                addParam("arg8", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< ZipTogether8Function > MakeValue() { return std::shared_ptr< ZipTogether8Function >(new ZipTogether8Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class ZipTogether9Function : public ExecutableAtomic
    {
        protected:
            INLINE ZipTogether9Function() : ExecutableAtomic()
            {
                addParam("arg1", REFERENCE_PARAMETER);
                addParam("arg2", REFERENCE_PARAMETER);
                addParam("arg3", REFERENCE_PARAMETER);
                addParam("arg4", REFERENCE_PARAMETER);
                addParam("arg5", REFERENCE_PARAMETER);
                addParam("arg6", REFERENCE_PARAMETER);
                addParam("arg7", REFERENCE_PARAMETER);
                addParam("arg8", REFERENCE_PARAMETER);
                addParam("arg9", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< ZipTogether9Function > MakeValue() { return std::shared_ptr< ZipTogether9Function >(new ZipTogether9Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class ZipTogether10Function : public ExecutableAtomic
    {
        protected:
            INLINE ZipTogether10Function() : ExecutableAtomic()
            {
                addParam("arg1", REFERENCE_PARAMETER);
                addParam("arg2", REFERENCE_PARAMETER);
                addParam("arg3", REFERENCE_PARAMETER);
                addParam("arg4", REFERENCE_PARAMETER);
                addParam("arg5", REFERENCE_PARAMETER);
                addParam("arg6", REFERENCE_PARAMETER);
                addParam("arg7", REFERENCE_PARAMETER);
                addParam("arg8", REFERENCE_PARAMETER);
                addParam("arg9", REFERENCE_PARAMETER);
                addParam("arg10", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< ZipTogether10Function > MakeValue() { return std::shared_ptr< ZipTogether10Function >(new ZipTogether10Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class ZipTogether11Function : public ExecutableAtomic
    {
        protected:
            INLINE ZipTogether11Function() : ExecutableAtomic()
            {
                addParam("arg1", REFERENCE_PARAMETER);
                addParam("arg2", REFERENCE_PARAMETER);
                addParam("arg3", REFERENCE_PARAMETER);
                addParam("arg4", REFERENCE_PARAMETER);
                addParam("arg5", REFERENCE_PARAMETER);
                addParam("arg6", REFERENCE_PARAMETER);
                addParam("arg7", REFERENCE_PARAMETER);
                addParam("arg8", REFERENCE_PARAMETER);
                addParam("arg9", REFERENCE_PARAMETER);
                addParam("arg10", REFERENCE_PARAMETER);
                addParam("arg11", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< ZipTogether11Function > MakeValue() { return std::shared_ptr< ZipTogether11Function >(new ZipTogether11Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////

    class ZipValueFunction : public ExecutableAtomic
    {
        protected:
            INLINE ZipValueFunction() : ExecutableAtomic() { addParam("value", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< ZipValueFunction > MakeValue() { return std::shared_ptr< ZipValueFunction >(new ZipValueFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////

    class ZipIncrement0Function : public ExecutableAtomic
    {
        protected:
            INLINE ZipIncrement0Function() : ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< ZipIncrement0Function > MakeValue() { return std::shared_ptr< ZipIncrement0Function >(new ZipIncrement0Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    class ZipIncrement1Function : public ExecutableAtomic
    {
        protected:
            INLINE ZipIncrement1Function() : ExecutableAtomic() { addParam("offset", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< ZipIncrement1Function > MakeValue() { return std::shared_ptr< ZipIncrement1Function >(new ZipIncrement1Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    ////////////////////////////////////////////////////////////////////////////

    class ZipDecrement1Function : public ExecutableAtomic
    {
        protected:
            INLINE ZipDecrement1Function() : ExecutableAtomic() { addParam("offset", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< ZipDecrement1Function > MakeValue() { return std::shared_ptr< ZipDecrement1Function >(new ZipDecrement1Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    ////////////////////////////////////////////////////////////////////////////
    
}

#endif

