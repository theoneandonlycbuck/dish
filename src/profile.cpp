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

#include "profile.h"

#include <algorithm>
#include <sstream>

/******************************************************************************

    dish::ExecutionProfile::TimeAccumulator class definitions

 ******************************************************************************/
 
const long double dish::ExecutionProfile::TimeAccumulator::Denomonator[unitsNUM] =
{
    0.0,
    1.0,
    1000.0,
    1000000.0,
    1000000000.0
};

/******************************************************************************

    dish::ExecutionProfile::AccumulateTime class definitions

 ******************************************************************************/
 
void dish::ExecutionProfile::AccumulateTime::accumulate(const dish::ExecutionProfile::TimeAccumulator::ClockT::time_point end)
{
    if(mStart <= end)
    {
        mInformation.second.Accumulate(
            static_cast< IntegerT >(
                std::chrono::duration_cast< std::chrono::nanoseconds >(end - mStart).count()
            )
        );
    }
    else
    {
        mInformation.second.MarkInvalid();
    }
}

/******************************************************************************

    dish::ExecutionProfile class definitions

 ******************************************************************************/
 
const std::string dish::ExecutionProfile::UNIT_LABELS[dish::ExecutionProfile::unitsNUM] =
{
    "<null>",
    "nS",
    "uS",
    "mS",
    "S"
};

const std::string dish::ExecutionProfile::SORT_BY_LABELS[dish::ExecutionProfile::sortNUM] =
{
    "Function-Name",
    "Execution-Time",
    "Number-of-Calls"
};

std::string::size_type dish::ExecutionProfile::keyWidth() const
{
    std::string::size_type width(0);
    
    std::for_each(
        mInformation.begin(), mInformation.end(),
        [&](const ProfileT::value_type &element)
        {
            width = std::max(width, element.first.length());
        }
    );
    
    return width;
}

void dish::ExecutionProfile::printFunction(std::ostream &out, const std::string::size_type width, const dish::ExecutionProfile::FunctionInfoT &finfo, const dish::ExecutionProfile::UnitsT units) const
{
    std::stringstream column1;
    column1 << std::string(width - finfoName(finfo).length(), ' ');
    column1 << finfoName(finfo);
    
    std::stringstream column2;
    column2 << finfoNumCalls(finfo);
    column2 << " call";
    if(finfoNumCalls(finfo) > 1)
    {
        column2 << "s";
    }
    
    std::stringstream column3;
    column3 << finfoTime(finfo, units);
    column3 << " ";
    column3 << UNIT_LABELS[units];
    
    out << column1.str() << " : " << column2.str() << " : " << column3.str();
}

void dish::ExecutionProfile::Print(std::ostream &out, const dish::ExecutionProfile::UnitsT units, const dish::ExecutionProfile::SortT sortby) const
{
    //  Put all of the functions into a list.
    std::vector< FunctionInfoT > flist(mInformation.begin(), mInformation.end());
    
    //  Sort the list accordingly.
    switch(sortby)
    {
        case sortName:
        {
            std::sort(
                flist.begin(), flist.end(),
                [](const FunctionInfoT &lhs, const FunctionInfoT &rhs)
                {
                    return (finfoName(lhs) < finfoName(rhs));
                }
            );
        } break;
        
        case sortTime:
        {
            std::sort(
                flist.begin(), flist.end(),
                [](const FunctionInfoT &lhs, const FunctionInfoT &rhs)
                {
                    return (finfoCount(lhs) > finfoCount(rhs));
                }
            );
        } break;
        
        case sortCalls:
        {
            std::sort(
                flist.begin(), flist.end(),
                [](const FunctionInfoT &lhs, const FunctionInfoT &rhs)
                {
                    if(finfoNumCalls(lhs) > finfoNumCalls(rhs))
                    {
                        return true;
                    }
                    
                    else if(finfoNumCalls(lhs) == finfoNumCalls(rhs))
                    {
                        return (finfoName(lhs) < finfoName(rhs));
                    }
                
                    return false;
                }
            );
        } break;
        
        default:
        {
            assert(false);
        }
        
    }
    
    //  Print the profiling information.
    const std::string::size_type width(keyWidth());
    
    std::for_each(
        flist.begin(), flist.end(),
        [&](const std::vector< FunctionInfoT >::value_type &funcinfo)
        {
            printFunction(std::cout, width, funcinfo, units);
            std::cout << std::endl;
        }
    );
}

