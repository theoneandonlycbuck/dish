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

/******************************************************************************

    This file confirms the validity of the configuration of the Dish build, as
    typically specified in dishconfig.h. When built using the makefile (via
    'make config') this file is automatically included at the end, after all of
    the configuration macros have been set, so no other file should include it
    explicitly.

 ******************************************************************************/

#ifndef DISH_VERIFY_CONFIG_H
#define DISH_VERIFY_CONFIG_H

///////////////////////////////////////////////////////////////////////////////
    
#if defined(AGGRESSIVE_INLINE) and defined(PREVENT_INLINE)
    #error  Cannot simultaneously invoke aggressive inlining and prevent inlining.
#endif

///////////////////////////////////////////////////////////////////////////////

#if not defined(DISH_32BIT_ATOMICS) and not defined(DISH_64BIT_ATOMICS)
    #error Must define either DISH_32BIT_ATOMICS or DISH_64BIT_ATOMICS to select the size, 32- or 64-bit, of the raw atomic types.
#endif

#if defined(DISH_32BIT_ATOMICS) and defined(DISH_64BIT_ATOMICS)
    #error Either DISH_32BIT_ATOMICS or DISH_64BIT_ATOMICS must be defined to select the size, 32- or 64-bit, of the raw atomic types, both are defined.
#endif

///////////////////////////////////////////////////////////////////////////////

#if not defined(LANG_TABLE_BASIC) and not defined(LANG_TABLE_HASHED)
    #error Must define either LANG_TABLE_BASIC or LANG_TABLE_HASHED to select the base-symbol-table type.
#endif

#if defined(LANG_TABLE_BASIC) and defined(LANG_TABLE_HASHED)
    #error Either LANG_TABLE_BASIC or LANG_TABLE_HASHED must be defined to select the base-symbol-table type, both are currently defined.
#endif

///////////////////////////////////////////////////////////////////////////////

#if not defined(LANG_LIB_CORE)
    #error LANG_LIB_CORE *MUST* be defined because for-loops are implemented in terms of the Inc function included in the core library.
#endif

///////////////////////////////////////////////////////////////////////////////

#endif

