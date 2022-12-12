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

#ifndef DISH_LANGFILE_H
#define DISH_LANGFILE_H

#include "dishconfig.h"

#include <cstdio>
#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

#include "atomics.h"
#include "inline.h"
#include "language.h"
#include "types.h"

namespace dish
{

    ////////////////////////////////////////////////////////////////////////////

    class FileList
    {
        public:
            
            typedef std::vector< std::FILE * > FileListT;
            
            typedef enum
            {
                fmRead,
                
                fmWrite,
                fmExWrite,
                
                fmAppend,
                
                fmNUM
            } FileModeT;
            
            static const FileListT::size_type MAX_OPEN_FILES;
    
        private:
            FileListT mOpenFiles;
            IntegerT mNumOpenFiles;
        
        protected:
            FileList() : mOpenFiles(MAX_OPEN_FILES, NULL), mNumOpenFiles(0) {};
            
        public:
            ~FileList() { Close(); };
            
            static FileList &Instance();
            
            IntegerT Open(const std::string &fname, const FileModeT mode);
            const IntegerT &NumOpen() const { return mNumOpenFiles; };
            std::FILE *Handle(const IntegerT &handle);
            bool IsOpen(const IntegerT &handle) { return (NULL != Handle(handle)); };
            void Close(const IntegerT &handle);
            void Close();
        
    };

    ////////////////////////////////////////////////////////////////////////////

    class FileOpenFunction : public ExecutableAtomic
    {
        protected:
            INLINE FileOpenFunction() : dish::ExecutableAtomic() { addParam("fname", REFERENCE_PARAMETER); addParam("mode", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< FileOpenFunction > MakeValue() { return std::shared_ptr< FileOpenFunction >(new FileOpenFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class FileNumOpenFunction : public ExecutableAtomic
    {
        protected:
            INLINE FileNumOpenFunction() : ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< FileNumOpenFunction > MakeValue() { return std::shared_ptr< FileNumOpenFunction >(new FileNumOpenFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class FileWriteFunction : public ExecutableAtomic
    {
        protected:
            INLINE FileWriteFunction() : dish::ExecutableAtomic() { addParam("handle", REFERENCE_PARAMETER); addParam("str", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< FileWriteFunction > MakeValue() { return std::shared_ptr< FileWriteFunction >(new FileWriteFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class FileWritelnFunction : public ExecutableAtomic
    {
        protected:
            INLINE FileWritelnFunction() : dish::ExecutableAtomic() { addParam("handle", REFERENCE_PARAMETER); addParam("str", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< FileWritelnFunction > MakeValue() { return std::shared_ptr< FileWritelnFunction >(new FileWritelnFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class FileFlushFunction : public ExecutableAtomic
    {
        protected:
            INLINE FileFlushFunction() : dish::ExecutableAtomic() { addParam("handle", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< FileFlushFunction > MakeValue() { return std::shared_ptr< FileFlushFunction >(new FileFlushFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class FileReadTextFunction : public ExecutableAtomic
    {
        protected:
            INLINE FileReadTextFunction() : dish::ExecutableAtomic() { addParam("handle", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< FileReadTextFunction > MakeValue() { return std::shared_ptr< FileReadTextFunction >(new FileReadTextFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class FileReadBooleanFunction : public ExecutableAtomic
    {
        protected:
            INLINE FileReadBooleanFunction() : dish::ExecutableAtomic() { addParam("handle", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< FileReadBooleanFunction > MakeValue() { return std::shared_ptr< FileReadBooleanFunction >(new FileReadBooleanFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class FileReadIntegerFunction : public ExecutableAtomic
    {
        protected:
            INLINE FileReadIntegerFunction() : dish::ExecutableAtomic() { addParam("handle", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< FileReadIntegerFunction > MakeValue() { return std::shared_ptr< FileReadIntegerFunction >(new FileReadIntegerFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class FileReadRealFunction : public ExecutableAtomic
    {
        protected:
            INLINE FileReadRealFunction() : dish::ExecutableAtomic() { addParam("handle", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< FileReadRealFunction > MakeValue() { return std::shared_ptr< FileReadRealFunction >(new FileReadRealFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class FileReadlnFunction : public ExecutableAtomic
    {
        protected:
            INLINE FileReadlnFunction() : dish::ExecutableAtomic() { addParam("handle", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< FileReadlnFunction > MakeValue() { return std::shared_ptr< FileReadlnFunction >(new FileReadlnFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class FileEndOfFileFunction : public ExecutableAtomic
    {
        protected:
            INLINE FileEndOfFileFunction() : dish::ExecutableAtomic() { addParam("handle", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< FileEndOfFileFunction > MakeValue() { return std::shared_ptr< FileEndOfFileFunction >(new FileEndOfFileFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class FileCloseFunction : public ExecutableAtomic
    {
        protected:
            INLINE FileCloseFunction() : dish::ExecutableAtomic() { addParam("handle", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< FileCloseFunction > MakeValue() { return std::shared_ptr< FileCloseFunction >(new FileCloseFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////
    
};

#endif

