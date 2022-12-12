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

#ifndef INLINE_H
#define INLINE_H

    #include "dishconfig.h"

    #if defined(AGGRESSIVE_INLINE)
    
        #ifdef __GNUC__
        
            #define INLINE      inline __attribute__((always_inline))
            #define INLINEC     inline __attribute__((always_inline))
            
        #else
        
            #define INLINE      inline
            #define INLINEC     inline
            
        #endif
            
    #elif defined(PREVENT_INLINE)
    
        #ifdef __GNUC__
        
            #define INLINE      __attribute__((noinline))
            #define INLINEC     static __attribute__((noinline))
            
            //  Disable unused-function-warning as there are quite a few
            //  generated when function-inlining is disabled.
            #pragma GCC diagnostic ignored "-Wunused-function"
            
        #else
        
            #define INLINE
            
            //  Admittedly, this is a little weird, but declaring inlined C
            //  functions static is necessary to prevent multiple-definition
            //  errors from the linker. A serious side-effect, though, is it
            //  also explodes the size of the executable because every source
            //  file that includes a header with an inlined C function gets its
            //  own copy of the function (remember: static prevents the symbol
            //  from being exported to the linker in C). *sigh*
            #define INLINEC     static
            
        #endif
    
    #else
    
        #define INLINE
        #define INLINEC         inline
        
    #endif

#endif

