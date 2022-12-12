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

#include "cmdln.h"
#include "log.h"

/******************************************************************************

    dish::Log class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::Log > dish::Log::MsgLog;
 
dish::Log::Log(const dish::Log::LevelT &level, std::ostream &out) :
    mLogLevel(level),
    
    mOutput(out)
{
    assert(mLogLevel > logNone);
    assert(mLogLevel < logNUM);
}

dish::Log &dish::Log::Instance()
{
    assert(MsgLog);
    
    return *MsgLog;
}

dish::Log &dish::Log::Instance(const dish::Log::LevelT &level, std::ostream &out)
{
    if(!MsgLog)
    {
        MsgLog.reset(new Log(level, out));
    }
    
    return *MsgLog;
}

bool dish::Log::WillPrint(const dish::Log::LevelT &level) const
{
    assert(level > logNone);
    assert(level < logNUM);
    
    bool print((logMessage == level) ? true : (level >= mLogLevel));
    print &= (!DishCommandLine::Instance().QuietMode());
    
    return print;
}

void dish::Log::Write(const dish::Log::LevelT &level, const std::string &message)
{
    assert(level > logNone);
    assert(level < logNUM);
    
    if(WillPrint(level))
    {
        mOutput << message;
    }
}

void dish::Log::Writeln(const dish::Log::LevelT &level)
{
    assert(level > logNone);
    assert(level < logNUM);
    
    if(WillPrint(level))
    {
        mOutput << std::endl;
    }
}

void dish::Log::Writeln(const dish::Log::LevelT &level, const std::string &message)
{
    assert(level > logNone);
    assert(level < logNUM);
    
    if(WillPrint(level))
    {
        mOutput << message << std::endl;
    }
}

