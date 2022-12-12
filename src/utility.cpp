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
#include <fstream>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "utility.h"

/******************************************************************************

    Global variable definitions

 ******************************************************************************/
 
const std::string dish::EOLN_CHARACTERS("\r\n");
const std::string dish::WHITESPACE_CHARACTERS(" \t\v\r\n");
const std::string dish::DIGIT_CHARACTERS("0123456789");
const std::string dish::LOWER_CASE_LETTER_CHARACTERS("abcdefghijklmnopqrstuvwxyz");
const std::string dish::UPPER_CASE_LETTER_CHARACTERS("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
const std::string dish::LETTER_CHARACTERS(UPPER_CASE_LETTER_CHARACTERS + LOWER_CASE_LETTER_CHARACTERS);

const std::string dish::VALID_FILE_NAME_CHARACTERS(DIGIT_CHARACTERS + LETTER_CHARACTERS + "./\\:");
    
const std::string dish::VALID_ID_CHARACTERS(DIGIT_CHARACTERS + LETTER_CHARACTERS + "_");
 
const bool dish::CASE_SENSITIVE(true);
const bool dish::CASE_INSENSITIVE(false);

/******************************************************************************

    dish::iPrintable class definitions

 ******************************************************************************/
 
const std::string::size_type dish::iPrintable::INDENT(4);

/******************************************************************************

    dish::TraceBlock class definitions

 ******************************************************************************/
 
int dish::TraceBlock::Indent(0);
 
dish::TraceBlock::TraceBlock(const std::string &name) : mName(name)
{
    assert(Indent >= 0);

    std::cout << std::string(Indent, static_cast< char >(' ')) << "Entering " << mName << std::endl;
    Indent += 2;
}

dish::TraceBlock::~TraceBlock()
{
    Indent -= 2;
    
    assert(Indent >= 0);

    std::cout << std::string(Indent, static_cast< char >(' ')) << "Exiting " << mName << std::endl;
}

/******************************************************************************

    dish-namespace function definitions

 ******************************************************************************/
 
bool dish::IsEqual(const std::string &lhs, const std::string &rhs, const bool &case_sensitive)
{
    if(!case_sensitive)
    {
        const std::string::size_type lhs_length(lhs.length());
        const std::string::size_type rhs_length(rhs.length());
    
        if(lhs_length == rhs_length)
        {
            for(std::string::size_type i(0); i < lhs_length; ++i)
            {
                if(std::toupper(lhs[i]) != std::toupper(rhs[i]))
                {
                    return false;
                }
            }
            
            return true;
        }
            
        return false;
    }
    
    return (lhs == rhs);
}

bool dish::IsLessThan(const std::string &lhs, const std::string &rhs, const bool &case_sensitive)
{
    if(!case_sensitive)
    {
        std::string::const_iterator lhs_i(lhs.begin());
        const std::string::const_iterator lhs_last_i(lhs.end());
        
        std::string::const_iterator rhs_i(rhs.begin());
        const std::string::const_iterator rhs_last_i(rhs.end());
        
        while((lhs_i != lhs_last_i) && (rhs_i != rhs_last_i))
        {
            const int ch1(std::toupper(*lhs_i));
            const int ch2(std::toupper(*rhs_i));
        
            if(ch1 < ch2)
            {
                return true;
            }
            
            else if(ch1 > ch2)
            {
                return false;
            }
            
            else
            {
                ++lhs_i;
                ++rhs_i;
            }
        }
    
        return ((lhs_i == lhs_last_i) && (rhs_i != rhs_last_i));
    }
    
    return (lhs < rhs);
}

std::string::size_type dish::caseInsensitiveIndexOf(const std::string &lhs, const int &rhs)
{
    const int uc_rhs(std::toupper(rhs));
    
    for(std::string::size_type i(0), last_i(lhs.length()); i < last_i; ++i)
    {
        if(uc_rhs == std::toupper(lhs[i]))
        {
            return i;
        }
    }
    
    return std::string::npos;
}

std::string::size_type dish::caseInsensitiveIndexOf(const std::string &lhs, const std::string &rhs)
{
    const std::string::size_type lhs_length(lhs.length());
    const std::string::size_type rhs_length(rhs.length());

    if(lhs_length <= rhs_length)
    {
        for(std::string::size_type i(0), last_i(lhs_length - rhs_length); i <= last_i; ++i)
        {
            if(std::toupper(lhs[i]) == std::toupper(rhs[0]))
            {
                bool match(true);
            
                for(std::string::size_type j(1); match && (j < rhs_length); ++j)
                {
                    if(std::toupper(lhs[i + j]) != std::toupper(rhs[j]))
                    {
                        match = false;
                    }
                }
                
                if(match)
                {
                    return i;
                }
            }
        }
    }

    return std::string::npos;
}

void dish::TrimBegin(std::string &str, const std::string &trim)
{
    if(!str.empty())
    {
        const std::string::size_type pos(str.find_first_not_of(trim));
    
        if(std::string::npos != pos)
        {
            str = str.substr(pos, std::string::npos);
        }
        else
        {
            str.erase(0, std::string::npos);
        }
    }
}

void dish::TrimEnd(std::string &str, const std::string &trim)
{
    if(!str.empty())
    {
        const std::string::size_type pos(str.find_last_not_of(trim));
    
        if(std::string::npos != pos)
        {
            str = str.substr(pos, std::string::npos);
        }
        else
        {
            str.erase(0, std::string::npos);
        }
    }
}

std::string dish::ToUpper(const std::string &str)
{
    std::string ret;
    
    std::for_each(
        str.begin(), str.end(),
        [&](const std::string::value_type &ch)
        {
            ret.append(1, std::toupper(ch));
        }
    );
    
    return ret;
}

std::string dish::ToLower(const std::string &str)
{
    std::string ret;
    
    std::for_each(
        str.begin(), str.end(),
        [&](const std::string::value_type &ch)
        {
            ret.append(1, std::tolower(ch));
        }
    );
    
    return ret;
}

bool dish::FileExists(const std::string &fname)
{
    static struct stat statinfo;
    
    return (0 == stat(fname.c_str(), &statinfo));
}

/******************************************************************************

    dish::RNG class definitions

 ******************************************************************************/

dish::IntegerT dish::RNG::operator*()
{
    ++mNum;

    return static_cast< IntegerT >(mGenerator() & 0x7FFFFFFFFFFFFFFF);
}

dish::IntegerT dish::RNG::Maximum() const
{
    return static_cast< IntegerT >(mGenerator.max() & 0x7FFFFFFFFFFFFFFF);
}

dish::IntegerT dish::RNG::Seed() const
{
    return mSeed;
}

dish::IntegerT dish::RNG::Num() const
{
    return mNum;
}

/******************************************************************************

    dish::BucketCounts class definitions

 ******************************************************************************/
 
const dish::IntegerT &dish::BucketCounts::operator[](const unsigned int &index) const
{
    for(typename BucketListT::const_iterator i(mBuckets.begin()), last_i(mBuckets.end()); i != last_i; ++i)
    {
        if((static_cast< unsigned int >(RangeMinimum(*i)) <= index) && (index < static_cast< unsigned int >(RangeMaximum(*i))))
        {
            return Count(*i);
        }
    }
    
    return mOverCount;
}

dish::IntegerT &dish::BucketCounts::operator[](const unsigned int &index)
{
    for(typename BucketListT::iterator i(mBuckets.begin()), last_i(mBuckets.end()); i != last_i; ++i)
    {
        if((static_cast< unsigned int >(RangeMinimum(*i)) <= index) && (index < static_cast< unsigned int >(RangeMaximum(*i))))
        {
            return Count(*i);
        }
    }
    
    return mOverCount;
}

