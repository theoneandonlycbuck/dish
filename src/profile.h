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

#ifndef DISH_PROFILE_H
#define DISH_PROFILE_H

#include "dishconfig.h"

#include <chrono>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "types.h"
#include "utility.h"

namespace dish
{
    
    class ExecutionProfile
    {
        public:
        
            /////
            
            using UnitsT = enum
            {
                unitsNull = 0,
                
                unitsNanoSeconds,
                unitsMicroSeconds,
                unitsMilliSeconds,
                unitsSeconds,
                
                unitsNUM
            };
            
            using SortT = enum
            {
                sortName,
                sortTime,
                sortCalls,
                
                sortNUM
            };
        
            /////
    
            class TimeAccumulator
            {
                public:
                
                    using ClockT = std::chrono::high_resolution_clock;
                
                private:
                    IntegerT mCount;
                    
                    static const long double Denomonator[unitsNUM];
                
                public:
                    INLINE TimeAccumulator() : mCount(0) {};
                    
                    INLINE bool IsValid() const { return (mCount >= 0); };
                    INLINE void MarkInvalid() { mCount = -1; };
                    
                    INLINE const IntegerT &Count() const { return mCount; };
                    INLINE double Time(const UnitsT units) const { return Divide(static_cast< long double >(Count()), Denomonator[units]); };
                    
                    INLINE void Accumulate(const IntegerT inc) { if(IsValid()) { mCount += inc; } };
                
            };
            
            using ProfileInformationT = std::pair< IntegerT, TimeAccumulator >;
        
            /////
    
            class AccumulateTime
            {
                private:
                    ProfileInformationT &mInformation;
                    
                    const TimeAccumulator::ClockT::time_point mStart;
                    
                    void accumulate(const TimeAccumulator::ClockT::time_point end);
                
                public:
                    INLINE AccumulateTime(ProfileInformationT &info) : mInformation(info), mStart(TimeAccumulator::ClockT::now()) { ++mInformation.first; };
                    INLINE ~AccumulateTime() { accumulate(TimeAccumulator::ClockT::now()); };
                
            };
            
            using ProfileT = std::map< std::string, ProfileInformationT >;
            
            using FunctionInfoT = std::pair< std::string, ProfileInformationT >;
        
            /////
            
            static const std::string UNIT_LABELS[unitsNUM];
            static const std::string SORT_BY_LABELS[sortNUM];
        
        private:
            ProfileT mInformation;
            
        protected:
            std::string::size_type keyWidth() const;
            
            void printFunction(std::ostream &out, const std::string::size_type width, const FunctionInfoT &finfo, const UnitsT units) const;
            
            static INLINE const std::string &finfoName(const FunctionInfoT &finfo) { return finfo.first; };
            static INLINE const IntegerT &finfoNumCalls(const FunctionInfoT &finfo) { return finfo.second.first; };
            static INLINE const IntegerT &finfoCount(const FunctionInfoT &finfo) { return finfo.second.second.Count(); };
            static INLINE double finfoTime(const FunctionInfoT &finfo, const UnitsT units) { return finfo.second.second.Time(units); };
        
        public:
            INLINE ExecutionProfile() : mInformation() {};
            
            INLINE IntegerT NumUniqueFunctionCalls() const { return static_cast< IntegerT >(mInformation.size()); };
            
            INLINE std::shared_ptr< AccumulateTime > ScopedProfileAccumulator(const std::string &key) { return std::shared_ptr< AccumulateTime >(new AccumulateTime(mInformation[key])); };
            
            void Print(std::ostream &out, const UnitsT units, const SortT sortby) const;
        
    };

}

#endif

