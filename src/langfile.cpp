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

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <sstream>

#include "exception.h"
#include "langfile.h"

namespace
{

    dish::FileList::FileModeT Mode(const dish::IntegerT mode)
    {
        switch(mode)
        {
            case 0:
            {
                return dish::FileList::fmRead;
            };
            
            case 1:
            {
                return dish::FileList::fmWrite;
            };
            
            case 2:
            {
                return dish::FileList::fmExWrite;
            };
            
            case 3:
            {
                return dish::FileList::fmAppend;
            };
            
            default:
            {
                //  Empty
            }
            
        }
        
        std::stringstream message;
        message << "Illegal mode: ";
        message << mode;
        message << ".";
        
        throw dish::UnableToOpenFileException(message.str());
    }

}

/******************************************************************************

    dish::FileList class definitions

 ******************************************************************************/
 
const dish::FileList::FileListT::size_type dish::FileList::MAX_OPEN_FILES(100);

dish::FileList &dish::FileList::Instance()
{
    static FileList singleton;
    
    return singleton;
}

dish::IntegerT dish::FileList::Open(const std::string &fname, const dish::FileList::FileModeT mode)
{
    for(FileListT::size_type i(0), last_i(mOpenFiles.size()); i != last_i; ++i)
    {
        if(NULL == mOpenFiles[i])
        {
            static const std::string FILE_MODES[fmNUM] =
            {
                "r",
                "w",
                "w+",
                "a"
            };
        
            mOpenFiles[i] = std::fopen(fname.c_str(), FILE_MODES[mode].c_str());
            
            if(NULL == mOpenFiles[i])
            {
                static const std::string FILE_MODE_NAMES[fmNUM] = 
                {
                    "reading",
                    "writing",
                    "exclusive writing",
                    "appending"
                };
                
                std::stringstream message;
                message << "Unable to open ";
                message << fname;
                message << " for ";
                message << FILE_MODE_NAMES[mode];
                message << ".";
                
                throw UnableToOpenFileException(message.str());
            }
        }
        
        ++mNumOpenFiles;
        
        return i;
    }
    
    throw TooManyOpenFilesException("Too many open files.");
}

std::FILE *dish::FileList::Handle(const dish::IntegerT &handle)
{
    if(handle < static_cast< IntegerT >(mOpenFiles.size()))
    {
        return mOpenFiles[handle];
    }
    
    throw IllegalHandleException("Illegal handle.");
}

void dish::FileList::Close(const dish::IntegerT &handle)
{
    if(IsOpen(handle))
    {
        std::fclose(Handle(handle));
        mOpenFiles[handle] = NULL;
    
        --mNumOpenFiles;
    }
}

void dish::FileList::Close()
{
    std::for_each(
        mOpenFiles.begin(), mOpenFiles.end(),
        [&](FileListT::value_type &file)
        {
            if(NULL != file)
            {
                std::fclose(file);
                file = NULL;
            }
        }
    );
    
    mNumOpenFiles = 0;
}

/******************************************************************************

    dish::FileOpenFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::FileOpenFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return IntegerValue::MakeValue(
        FileList::Instance().Open(
            getParam(symtab, "fname")->AsString(), 
            Mode(getParam(symtab, "mode")->AsInteger())
        )
    );
}

/******************************************************************************

    dish::FileNumOpenFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::FileNumOpenFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return IntegerValue::MakeValue(FileList::Instance().NumOpen());
}

/******************************************************************************

    dish::FileWriteFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::FileWriteFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::FILE * const fp(FileList::Instance().Handle(getParam(symtab, "handle")->AsInteger()));
    assert(NULL != fp);

    const int error(
        std::fprintf(
            fp,
            "%s",
            getParam(symtab, "str")->AsString().c_str()
        )
    );
    
    if(error >= 0)
    {
        return NullValue::MakeValue();
    }
    
    throw FileWriteErrorException("Error writing to a file.");
}

/******************************************************************************

    dish::FileWritelnFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::FileWritelnFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::FILE * const fp(FileList::Instance().Handle(getParam(symtab, "handle")->AsInteger()));
    assert(NULL != fp);

    const int error(
        std::fprintf(
            fp,
            "%s\n",
            getParam(symtab, "str")->AsString().c_str()
        )
    );
    
    if(error >= 0)
    {
        return NullValue::MakeValue();
    }
    
    throw FileWriteErrorException("Error writing to a file.");
}

/******************************************************************************

    dish::FileFlushFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::FileFlushFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::FILE * const fp(FileList::Instance().Handle(getParam(symtab, "handle")->AsInteger()));
    assert(NULL != fp);

    const int error(std::fflush(fp));
    
    if(error >= 0)
    {
        return NullValue::MakeValue();
    }
    
    throw FileWriteErrorException("Error flushing file.");
}

/******************************************************************************

    dish::FileReadTextFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::FileReadTextFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::FILE * const fp(FileList::Instance().Handle(getParam(symtab, "handle")->AsInteger()));
    assert(NULL != fp);

    StringT text;
    
    for(bool done(false); !done; )
    {
        const int ch(std::fgetc(fp));
        
        if(EOF != ch)
        {
            text.append(1, ch);
        }
        else
        {
            done = true;
        }
    }
    
    return StringValue::MakeValue(text);
}

/******************************************************************************

    dish::FileReadBooleanFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::FileReadBooleanFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::FILE * const fp(FileList::Instance().Handle(getParam(symtab, "handle")->AsInteger()));
    assert(NULL != fp);
    
    switch(toupper(std::fgetc(fp)))
    {
        case 'F':
        {
            if('A' == toupper(std::fgetc(fp)))
            {
                if('L' == toupper(std::fgetc(fp)))
                {
                    if('S' == toupper(std::fgetc(fp)))
                    {
                        if('E' == toupper(std::fgetc(fp)))
                        {
                            return BooleanValue::MakeLockedValue(false);
                        }
                    }
                }
            }
        } break;
        
        case 'T':
        {
            if('R' == toupper(std::fgetc(fp)))
            {
                if('U' == toupper(std::fgetc(fp)))
                {
                    if('E' == toupper(std::fgetc(fp)))
                    {
                        return BooleanValue::MakeLockedValue(true);
                    }
                }
            }
        } break;;
        
        default:
        {
            //  Empty
        }
        
    }
    
    throw FileReadErrorException("Invalid boolean value read fro file.");
}

/******************************************************************************

    dish::FileReadIntegerFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::FileReadIntegerFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::FILE * const fp(FileList::Instance().Handle(getParam(symtab, "handle")->AsInteger()));
    assert(NULL != fp);
    
    long long int value;
    if(std::fscanf(fp, "%lld", &value))
    {
        return IntegerValue::MakeValue(static_cast< IntegerT >(value));
    }
    
    throw FileReadErrorException("Invalid integer value read fro file.");
}

/******************************************************************************

    dish::FileReadRealFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::FileReadRealFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::FILE * const fp(FileList::Instance().Handle(getParam(symtab, "handle")->AsInteger()));
    assert(NULL != fp);
    
    double value;
    
    if(std::fscanf(fp, "%lf", &value))
    {
        return RealValue::MakeValue(value);
    }
    
    throw FileReadErrorException("Invalid real value read fro file.");
}

/******************************************************************************

    dish::FileReadlnFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::FileReadlnFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::FILE * const fp(FileList::Instance().Handle(getParam(symtab, "handle")->AsInteger()));
    assert(NULL != fp);

    StringT text;
    
    //  Read the string from the file.
    for(bool done(false); !done; )
    {
        const int ch(std::fgetc(fp));
        
        if(('\r' != ch) && ('\n' != ch) && (EOF != ch))
        {
            text.append(1, ch);
        }
        else
        {
            done = true;
        }
    }
    
    //  Consume the EOLN characters that terminated the string from the file.
    for(bool done(false); !done; )
    {
        const int ch(std::fgetc(fp));
        
        if(('\r' != ch) && ('\n' != ch))
        {
            if(EOF != ch)
            {
                const int result(ungetc(ch, fp));
                assert(EOF != result);
            }
            
            done = true;
        }
    }
    
    return StringValue::MakeValue(text);
}

/******************************************************************************

    dish::FileEndOfFileFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::FileEndOfFileFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::FILE * const fp(FileList::Instance().Handle(getParam(symtab, "handle")->AsInteger()));
    assert(NULL != fp);

    return BooleanValue::MakeLockedValue(std::feof(fp));
}

/******************************************************************************

    dish::FileCloseFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::FileCloseFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    FileList::Instance().Close(getParam(symtab, "handle")->AsInteger());
    
    return NullValue::MakeValue();
}

