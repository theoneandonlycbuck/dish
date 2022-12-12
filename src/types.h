/*
    This file is part of the DISH programming language, Copyright 2014-2017 by 
    Chris Buck.
    
    DISH is free software for non-commercial use; you can redistribute it and/or
    modify it provided
    
        (1) The following Copyright notice is displayed at runtime and in any
            accompanying documentation:
    
            DISH programming language copyright (c) 2014-2017 by Chris Buck.
        
        (2) All source files duplicate this copyright statement in full.
        
    Commercial licenses can be negotiated by contacting Chris Buck at
    chrisbuck1220@hotmail.com.

    DISH is distributed in the hope that it will be useful, but WITHOUT ANY 
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS 
    FOR A PARTICULAR PURPOSE.
*/

#ifndef DISH_TYPES_H
#define DISH_TYPES_H

#include "dishconfig.h"

#include <cstdint>
#include <string>

namespace dish
{
    
#ifdef DISH_32BIT_ATOMICS
    
    using BooleanT = bool;
    using IntegerT = std::int32_t;
    using RealT = float;
    using StringT = std::string;
    
#endif
    
#ifdef DISH_64BIT_ATOMICS
    
    using BooleanT = bool;
    using IntegerT = std::int64_t;
    using RealT = double;
    using StringT = std::string;
    
#endif

    extern const IntegerT BOOLEAN_NBYTES;
    extern const BooleanT BOOLEAN_MIN;
    extern const BooleanT BOOLEAN_MAX;

    extern const IntegerT INTEGER_NBYTES;
    extern const IntegerT INTEGER_MIN;
    extern const IntegerT INTEGER_MAX;
    extern const IntegerT INTEGER_EPS;

    extern const IntegerT REAL_NBYTES;
    extern const RealT REAL_MIN;
    extern const RealT REAL_MAX;
    extern const RealT REAL_EPS;

}

#endif

