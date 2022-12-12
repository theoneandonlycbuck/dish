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

#ifndef DISH_INPUT_H
#define DISH_INPUT_H

#include "dishconfig.h"

#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <sstream>
#include <string>

#include "inline.h"
#include "utility.h"

namespace dish
{

    ////////////////////////////////////////////////////////////////////////////
        
    extern const bool STRING_INPUT;
    extern const bool FILE_INPUT;

    ////////////////////////////////////////////////////////////////////////////

    class iInputStream
    {
        public:
        
            static const int END_OF_INPUT;
        
            virtual ~iInputStream() {};
            
            std::string LocationString() const;
            
            virtual bool Empty() = 0;
            
            virtual int Get() = 0;
            virtual void Unget(const int byte) = 0;
            
            virtual const std::string &Source() const = 0;
            virtual const int &Line() const = 0;
            virtual const int &Column() const = 0;
            
            virtual void Print(std::ostream &out = std::cout) = 0;
        
    };
    
    class InputStream : public iInputStream
    {
        private:
            bool mNextByteAvailable;
            int mNextByte;
            
        protected:
            INLINE bool empty() const throw() { return (!mNextByteAvailable); };
        
        public:
            INLINE InputStream() : iInputStream(), mNextByteAvailable(false), mNextByte(END_OF_INPUT) {};
            
            //  From iInputStream
            
            virtual bool Empty() { return empty(); };
            
            virtual int Get() { return (!empty() ? (mNextByteAvailable = false, mNextByte) : END_OF_INPUT); };
            virtual void Unget(const int byte) { mNextByte = byte; mNextByteAvailable = true; };
            
            virtual void Print(std::ostream &out = std::cout);
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class FileInputStream : public InputStream
    {
        private:
            const std::string mFileName;
            int mLine;
            int mColumn;
            int mLastColumn;
            
            std::ifstream mInput;
        
        public:
            FileInputStream(const std::string &fname);
            INLINE ~FileInputStream() { mInput.close(); };
            
            //  From iInputStream
            
            virtual bool Empty();
            
            virtual int Get();
            virtual void Unget(const int byte);
            
            virtual const std::string &Source() const;
            virtual const int &Line() const;
            virtual const int &Column() const;
        
    };
    
    class StringInputStream : public InputStream
    {
        private:
            int mLine;
            int mColumn;
            int mLastColumn;
            
            std::stringstream mInput;
        
        public:
            INLINE StringInputStream(const std::string &str) : InputStream(), mLine(1), mColumn(1), mLastColumn(-1), mInput(str) {};
            
            //  From iInputStream
            
            virtual bool Empty();
            
            virtual int Get();
            virtual void Unget(const int byte);
            
            virtual const std::string &Source() const;
            virtual const int &Line() const;
            virtual const int &Column() const;
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class StackedInputStream : public InputStream
    {
        public:
        
            typedef std::list< std::string > SearchPathT;
        
            typedef std::set< std::string > LoadedFileSetT;
        
            typedef std::list< std::pair< std::string, std::shared_ptr< iInputStream > > > InputStackT;
    
        private:
            SearchPathT mSearchPath;
            LoadedFileSetT mLoadedFileSet;
        
            InputStackT mInputStack;
            
            bool mInEntryPoint;
            
        protected:
            void buildPathList();
            
            INLINE void updateInEntryPoint() { mInEntryPoint = (1 >= mInputStack.size()); };
            
        public:
            StackedInputStream();
            StackedInputStream(const std::string &source, const bool finput);
            
            INLINE void Push(const std::string &source, const bool finput) { if(finput) { PushFile(source); } else { PushString(source); } };
            void PushFile(const std::string &fname);
            void PushString(const std::string &str);
            INLINE void Pop() { if(!mInputStack.empty()) { mInputStack.pop_front(); } updateInEntryPoint(); };
            
            void Load(const std::string &fname);
            
            //  This method returns true if the DISH-program's entry point (the
            //  file specifed on the command-line of the interpreter) is being
            //  processed, or false otherwise (an imported file is being 
            //  processed).
            INLINE bool IsEntryPoint() const { return mInEntryPoint; };
            
            //  From iInputStream
            
            virtual bool Empty();
            
            virtual int Get();
            virtual void Unget(const int byte);
            
            virtual void Print(std::ostream &out = std::cout);
            
            virtual const std::string &Source() const;
            virtual const int &Line() const;
            virtual const int &Column() const;
        
    };
    
    ////////////////////////////////////////////////////////////////////////////

}

#endif

