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

#ifndef DISH_LANGTIME_H
#define DISH_LANGTIME_H

#include "dishconfig.h"

#include <memory>

#include "atomics.h"
#include "inline.h"
#include "language.h"

namespace dish
{
    
    extern std::shared_ptr< iAtomic > CreateDateTimeStructureType();
    
    extern std::shared_ptr< iAtomic > CreateDaysOfTheWeekArray();
    extern std::shared_ptr< iAtomic > CreateMonthsOfTheYearArray();
    
    extern std::shared_ptr< iAtomic > CreateTimezoneStructureType();
    
    ////

    class NowFunction : public ExecutableAtomic
    {
        protected:
            INLINE NowFunction() : ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< NowFunction > MakeValue() { return std::shared_ptr< NowFunction >(new NowFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class ElapsedSecondsFunction : public ExecutableAtomic
    {
        protected:
            INLINE ElapsedSecondsFunction() : ExecutableAtomic() { addParam("start", REFERENCE_PARAMETER); addParam("finish", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< ElapsedSecondsFunction > MakeValue() { return std::shared_ptr< ElapsedSecondsFunction >(new ElapsedSecondsFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    ////

    class DateTimeFunction : public ExecutableAtomic
    {
        protected:
            INLINE DateTimeFunction() : ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< DateTimeFunction > MakeValue() { return std::shared_ptr< DateTimeFunction >(new DateTimeFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class DecomposeDateTimeValueFunction : public ExecutableAtomic
    {
        protected:
            INLINE DecomposeDateTimeValueFunction() : ExecutableAtomic() { addParam("encoded", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< DecomposeDateTimeValueFunction > MakeValue() { return std::shared_ptr< DecomposeDateTimeValueFunction >(new DecomposeDateTimeValueFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class DecomposeUtcDateTimeValueFunction : public ExecutableAtomic
    {
        protected:
            INLINE DecomposeUtcDateTimeValueFunction() : ExecutableAtomic() { addParam("encoded", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< DecomposeUtcDateTimeValueFunction > MakeValue() { return std::shared_ptr< DecomposeUtcDateTimeValueFunction >(new DecomposeUtcDateTimeValueFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class ComposeDateTimeValueFunction : public ExecutableAtomic
    {
        protected:
            INLINE ComposeDateTimeValueFunction() : ExecutableAtomic() { addParam("decoded", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< ComposeDateTimeValueFunction > MakeValue() { return std::shared_ptr< ComposeDateTimeValueFunction >(new ComposeDateTimeValueFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    ////

    class TimeZoneInfoFunction : public ExecutableAtomic
    {
        protected:
            INLINE TimeZoneInfoFunction() : ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< TimeZoneInfoFunction > MakeValue() { return std::shared_ptr< TimeZoneInfoFunction >(new TimeZoneInfoFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class TimeZoneInfo1Function : public ExecutableAtomic
    {
        protected:
            INLINE TimeZoneInfo1Function() : ExecutableAtomic() { addParam("encoded", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< TimeZoneInfo1Function > MakeValue() { return std::shared_ptr< TimeZoneInfo1Function >(new TimeZoneInfo1Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

}

#endif

