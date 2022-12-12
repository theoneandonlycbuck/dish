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

#include <cassert>
#include <cstdlib>
#include <sstream>

#include "input.h"

/******************************************************************************

    Global variable definitions

 ******************************************************************************/
 
const bool dish::STRING_INPUT(false);
const bool dish::FILE_INPUT(true);

/******************************************************************************

    dish::iInputStream class definitions

 ******************************************************************************/

const int dish::iInputStream::END_OF_INPUT(EOF);

std::string dish::iInputStream::LocationString() const
{
    std::stringstream locstr;
    locstr << Source();
    locstr << " (Ln ";
    locstr << Line();
    locstr << "; Col ";
    locstr << Column();
    locstr << ")";
    
    return locstr.str();
}

/******************************************************************************

    dish::InputStream class definitions

 ******************************************************************************/

void dish::InputStream::Print(std::ostream &out)
{
    if(mNextByteAvailable)
    {
        out << "('";
        out << static_cast< char >(mNextByte);
        out << "'): ";
        
        mNextByteAvailable = false;
    }
    
    out << "\"";
    
    while(!Empty())
    {
        out << static_cast< char >(Get());
    }
    
    out << "\"";
}

/******************************************************************************

    dish::FileInputStream class definitions

 ******************************************************************************/
 
dish::FileInputStream::FileInputStream(const std::string &fname) : InputStream(), 
    mFileName(fname),
    
    mLine(1),
    mColumn(1),
    mLastColumn(-1),
    
    mInput(fname)
{
    if(!mInput)
    {
        std::stringstream message;
        message << "Unable to import ";
        message << fname;
        message << ".";
    
        throw UnableToImportFileException(message.str());
    }
}

bool dish::FileInputStream::Empty()
{
    const int byte(Get());
    
    if(END_OF_INPUT != byte)
    {
        Unget(byte);
        
        return false;
    }
    
    return true;
}

int dish::FileInputStream::Get()
{
    const int byte(empty() ? mInput.get() : InputStream::Get());
    
    if('\n' == byte)
    {
        ++mLine;
        
        mLastColumn = mColumn;
        mColumn = 1;
    }
    
    return byte;
}

void dish::FileInputStream::Unget(const int byte)
{
    if('\n' == byte)
    {
        mColumn = mLastColumn;
        --mLine;
    }
    
    InputStream::Unget(byte);
}

const std::string &dish::FileInputStream::Source() const
{
    return mFileName;
}

const int &dish::FileInputStream::Line() const
{
    return mLine;
}

const int &dish::FileInputStream::Column() const
{
    return mColumn;
}

/******************************************************************************

    dish::StringInputStream class definitions

 ******************************************************************************/

bool dish::StringInputStream::Empty()
{
    const int byte(Get());

    if(END_OF_INPUT != byte)
    {
        Unget(byte);
    
        return false;
    }
    
    return true;
}

int dish::StringInputStream::Get()
{
    const int byte(empty() ? mInput.get() : InputStream::Get());
    
    if('\n' == byte)
    {
        ++mLine;
        
        mLastColumn = mColumn;
        mColumn = 1;
    }
    
    return byte;
}

void dish::StringInputStream::Unget(const int byte)
{
    if('\n' == byte)
    {
        mColumn = mLastColumn;
        --mLine;
    }
    
    InputStream::Unget(byte);
}

const std::string &dish::StringInputStream::Source() const
{
    static const std::string SourceName("< string >");

    return SourceName;
}

const int &dish::StringInputStream::Line() const
{
    return mLine;
}

const int &dish::StringInputStream::Column() const
{
    return mColumn;
}

/******************************************************************************

    dish::StackedInputStream class definitions

 ******************************************************************************/
 
void dish::StackedInputStream::buildPathList()
{
    //  Add the current path.
    mSearchPath.push_back("./");
    
    //  Fetch the environment variable.
    const char * const envstr(std::getenv("DISHDIR"));

    //  Process the environment variable.
    if(NULL != envstr)
    {
        const std::string dishdir(envstr);
    
        for(std::string::size_type index(0); std::string::npos != index; )
        {
            const std::string::size_type next_index(dishdir.find(":", index));
            
            std::string dirstr(dishdir.substr(index, next_index - index));
            Trim(dirstr, WHITESPACE_CHARACTERS);
            if(!EndsWith(dirstr, '/'))
            {
                dirstr += "/";
            }
            
            mSearchPath.push_back(dirstr);
            
            index = (std::string::npos != next_index) ? (next_index + 1) : next_index;
        }
    }
}

dish::StackedInputStream::StackedInputStream() : InputStream(),
    mSearchPath(),
    mLoadedFileSet(),
    
    mInputStack(),
    
    mInEntryPoint(false)
{
    buildPathList();
}

dish::StackedInputStream::StackedInputStream(const std::string &source, const bool finput) : InputStream(),
    mSearchPath(),
    mLoadedFileSet(),
    
    mInputStack(),
    
    mInEntryPoint(false)
{
    buildPathList();
    Push(source, finput);
}

void dish::StackedInputStream::PushFile(const std::string &fname)
{
    if(mLoadedFileSet.end() == mLoadedFileSet.find(fname))
    {
        mLoadedFileSet.insert(fname);

        mInputStack.push_front(std::make_pair(fname, std::shared_ptr< iInputStream >(new FileInputStream(fname))));
    }
    
    updateInEntryPoint();
}

void dish::StackedInputStream::PushString(const std::string &str)
{
    mInputStack.push_front(
        std::make_pair(
            "<string>", std::shared_ptr< iInputStream >(new StringInputStream(str))
        )
    );
    
    updateInEntryPoint();
}

void dish::StackedInputStream::Load(const std::string &fname)
{
    if(std::string::npos == fname.find('/'))
    {
        for(SearchPathT::const_iterator i(mSearchPath.begin()), last_i(mSearchPath.end()); i != last_i; ++i)
        {
            const std::string abspath(*i + fname);
            
            if(FileExists(abspath))
            {
                if(mLoadedFileSet.end() == mLoadedFileSet.find(abspath))
                {
                    PushFile(abspath);
                    mLoadedFileSet.insert(abspath);
                }
                
                return;
            }
        }
    }
    
    if(FileExists(fname))
    {
        if(mLoadedFileSet.end() == mLoadedFileSet.find(fname))
        {
            PushFile(fname);
            mLoadedFileSet.insert(fname);
        }
        
        return;
    }
    
    std::stringstream message;
    message << "The specified file \"";
    message << fname;
    message << "\" cannot be found.";
    
    throw NoSuchFileException(message.str());
}

bool dish::StackedInputStream::Empty()
{
    while((!mInputStack.empty()) && mInputStack.front().second->Empty())
    {
        mInputStack.pop_front();
    }
    
    return (mInputStack.empty() && InputStream::Empty());
}

int dish::StackedInputStream::Get()
{
    while((!mInputStack.empty()) && mInputStack.front().second->Empty())
    {
        mInputStack.pop_front();
    }
    
    if(!mInputStack.empty())
    {
        return mInputStack.front().second->Get();
    }
    
    return InputStream::Get();
}

void dish::StackedInputStream::Unget(const int byte)
{
    if(!mInputStack.empty())
    {
        mInputStack.front().second->Unget(byte);
    }
    else
    {
        InputStream::Unget(byte);
    }
}

void dish::StackedInputStream::Print(std::ostream &out)
{
    while(!mInputStack.empty())
    {
        out << mInputStack.size();
        out << " - ";
        mInputStack.front().second->Print(out);
        out << std::endl;
        
        mInputStack.pop_front();
    }
    
    if(!Empty())
    {
        out << std::endl;
    
        out << "('";
        out << static_cast< char >(Get());
        out << "')";
        out << std::endl;
    }
}

const std::string &dish::StackedInputStream::Source() const
{
    if(!mInputStack.empty())
    {
        return mInputStack.front().second->Source();
    }
    else
    {
        static const std::string SourceString("< stack empty >");
    
        return SourceString;
    }
}

const int &dish::StackedInputStream::Line() const
{
    if(!mInputStack.empty())
    {
        return mInputStack.front().second->Line();
    }
    else
    {
        static const int SourceLine(-1);
    
        return SourceLine;
    }
}

const int &dish::StackedInputStream::Column() const
{
    if(!mInputStack.empty())
    {
        return mInputStack.front().second->Column();
    }
    else
    {
        static const int SourceColumn(-1);
    
        return SourceColumn;
    }
}

