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

#ifndef DISH_LANGFILESYS_H
#define DISH_LANGFILESYS_H

#include "dishconfig.h"

#include <ctime>
#include <memory>
#include <string>

#include "atomics.h"
#include "inline.h"
#include "language.h"
#include "types.h"

namespace dish
{

    ////////////////////////////////////////////////////////////////////////////
    
    extern std::shared_ptr< iAtomic > CreateFileSysFileT();
    extern std::shared_ptr< iAtomic > CreateFileSysDirT();
    extern std::shared_ptr< iAtomic > CreateFileInfoT();

    ////////////////////////////////////////////////////////////////////////////

    class FILESYS_FileExistsFunction : public ExecutableAtomic
    {
        protected:
            INLINE FILESYS_FileExistsFunction() : ExecutableAtomic() { addParam("fname", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< FILESYS_FileExistsFunction > MakeValue() { return std::shared_ptr< FILESYS_FileExistsFunction >(new FILESYS_FileExistsFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class FILESYS_ReadLocationFunction : public ExecutableAtomic
    {
        protected:
            INLINE FILESYS_ReadLocationFunction() : ExecutableAtomic() { addParam("rootdir", REFERENCE_PARAMETER); addParam("recurse", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< FILESYS_ReadLocationFunction > MakeValue() { return std::shared_ptr< FILESYS_ReadLocationFunction >(new FILESYS_ReadLocationFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class FILESYS_ReadFilesFunction : public ExecutableAtomic
    {
        protected:
            INLINE FILESYS_ReadFilesFunction() : ExecutableAtomic() { addParam("rootdir", REFERENCE_PARAMETER); addParam("recurse", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< FILESYS_ReadFilesFunction > MakeValue() { return std::shared_ptr< FILESYS_ReadFilesFunction >(new FILESYS_ReadFilesFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class FILESYS_ReadDirectoriesFunction : public ExecutableAtomic
    {
        protected:
            INLINE FILESYS_ReadDirectoriesFunction() : ExecutableAtomic() { addParam("rootdir", REFERENCE_PARAMETER); addParam("recurse", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< FILESYS_ReadDirectoriesFunction > MakeValue() { return std::shared_ptr< FILESYS_ReadDirectoriesFunction >(new FILESYS_ReadDirectoriesFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class FILESYS_GetFileInfoFunction : public ExecutableAtomic
    {
        protected:
            INLINE FILESYS_GetFileInfoFunction() : ExecutableAtomic() { addParam("fname", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< FILESYS_GetFileInfoFunction > MakeValue() { return std::shared_ptr< FILESYS_GetFileInfoFunction >(new FILESYS_GetFileInfoFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class FILESYS_PrintPathTree1Function : public ExecutableAtomic
    {
        protected:
            INLINE FILESYS_PrintPathTree1Function() : ExecutableAtomic() { addParam("pathtree", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< FILESYS_PrintPathTree1Function > MakeValue() { return std::shared_ptr< FILESYS_PrintPathTree1Function >(new FILESYS_PrintPathTree1Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class FILESYS_PrintPathTreeFunction : public ExecutableAtomic
    {
        protected:
            INLINE FILESYS_PrintPathTreeFunction() : ExecutableAtomic() { addParam("pathtree", REFERENCE_PARAMETER); addParam("indent", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< FILESYS_PrintPathTreeFunction > MakeValue() { return std::shared_ptr< FILESYS_PrintPathTreeFunction >(new FILESYS_PrintPathTreeFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////

}

#endif

