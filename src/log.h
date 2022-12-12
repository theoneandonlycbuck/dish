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

#ifndef DISH_LOG_H
#define DISH_LOG_H

#include "dishconfig.h"

#include <iostream>
#include <memory>
#include <string>

namespace dish
{

    class Log
    {
        public:
        
            typedef enum
            {
                logNone = 0,
                
                logMessage,
                
                logInfo,
                logMaximum,
                
                logOff,
                
                logNUM
            } LevelT;
        
        private:
            const LevelT mLogLevel;
            
            std::ostream &mOutput;
            
            static std::shared_ptr< Log > MsgLog;
            
        protected:
            Log(const LevelT &level, std::ostream &out);
        
        public:
        
            static Log &Instance();
            static Log &Instance(const LevelT &level, std::ostream &out);
            
            bool WillPrint(const LevelT &level) const;
            
            void Write(const LevelT &level, const std::string &message);
            
            void Writeln(const LevelT &level);
            void Writeln(const LevelT &level, const std::string &message);
        
    };

}

#endif

