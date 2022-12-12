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

#ifndef RS232_H
#define RS232_H

    #include "dishconfig.h"

    #include <termios.h>
    
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Determine the supported baud rates.
    //
    ////////////////////////////////////////////////////////////////////////////
    
    #if defined(B50)
        #define RS232_BAUDRATE_50_SUPPORTED
    #endif
    
    #if defined(B75)
        #define RS232_BAUDRATE_75_SUPPORTED
    #endif
    
    #if defined(B110)
        #define RS232_BAUDRATE_110_SUPPORTED
    #endif
    
    #if defined(B134)
        #define RS232_BAUDRATE_134_SUPPORTED
    #endif
    
    #if defined(B150)
        #define RS232_BAUDRATE_150_SUPPORTED
    #endif
    
    #if defined(B200)
        #define RS232_BAUDRATE_200_SUPPORTED
    #endif
    
    #if defined(B300)
        #define RS232_BAUDRATE_300_SUPPORTED
    #endif
    
    #if defined(B600)
        #define RS232_BAUDRATE_600_SUPPORTED
    #endif
    
    #if defined(B1200)
        #define RS232_BAUDRATE_1200_SUPPORTED
    #endif
    
    #if defined(B1800)
        #define RS232_BAUDRATE_1800_SUPPORTED
    #endif
    
    #if defined(B2400)
        #define RS232_BAUDRATE_2400_SUPPORTED
    #endif
    
    #if defined(B4800)
        #define RS232_BAUDRATE_4800_SUPPORTED
    #endif
    
    #if defined(B9600)
        #define RS232_BAUDRATE_9600_SUPPORTED
    #endif
    
    #if defined(B19200)
        #define RS232_BAUDRATE_19200_SUPPORTED
    #endif
    
    #if defined(B38400)
        #define RS232_BAUDRATE_38400_SUPPORTED
    #endif
    
    #if defined(B57600)
        #define RS232_BAUDRATE_57600_SUPPORTED
    #endif
    
    #if defined(B115200)
        #define RS232_BAUDRATE_115200_SUPPORTED
    #endif
    
    #if defined(B230400)
        #define RS232_BAUDRATE_230400_SUPPORTED
    #endif
    
    #if defined(B460800)
        #define RS232_BAUDRATE_460800_SUPPORTED
    #endif
    
    #if defined(B500000)
        #define RS232_BAUDRATE_500000_SUPPORTED
    #endif
    
    #if defined(B576000)
        #define RS232_BAUDRATE_576000_SUPPORTED
    #endif
    
    #if defined(B921600)
        #define RS232_BAUDRATE_921600_SUPPORTED
    #endif
    
    #if defined(B1000000)
        #define RS232_BAUDRATE_1000000_SUPPORTED
    #endif
    
    #if defined(B1152000)
        #define RS232_BAUDRATE_1152000_SUPPORTED
    #endif
    
    #if defined(B1500000)
        #define RS232_BAUDRATE_1500000_SUPPORTED
    #endif
    
    #if defined(B2000000)
        #define RS232_BAUDRATE_2000000_SUPPORTED
    #endif
    
    #if defined(B2500000)
        #define RS232_BAUDRATE_2500000_SUPPORTED
    #endif
    
    #if defined(B3000000)
        #define RS232_BAUDRATE_3000000_SUPPORTED
    #endif
    
    #if defined(B3500000)
        #define RS232_BAUDRATE_3500000_SUPPORTED
    #endif
    
    #if defined(B4000000)
        #define RS232_BAUDRATE_4000000_SUPPORTED
    #endif
    
    
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Determine the supported data-bits.
    //
    ////////////////////////////////////////////////////////////////////////////
    
    #if defined(CS5)
        #define RS232_DATABITS_5_SUPPORTED
    #endif
    
    #if defined(CS6)
        #define RS232_DATABITS_6_SUPPORTED
    #endif
    
    #if defined(CS7)
        #define RS232_DATABITS_7_SUPPORTED
    #endif
    
    #if defined(CS8)
        #define RS232_DATABITS_8_SUPPORTED
    #endif
    
    
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Determine the supported parity schemes.
    //
    ////////////////////////////////////////////////////////////////////////////
    
    #define RS232_PARITY_NO_SUPPORTED
    
    #if defined(PARODD)
        #define RS232_PARITY_ODD_SUPPORTED
        #define RS232_PARITY_EVEN_SUPPORTED
    #endif
    
    
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Determine the supported stop-bits.
    //
    ////////////////////////////////////////////////////////////////////////////
    
    #if defined(CSTOPB)
        #define RS232_STOPBITS_1_SUPPORTED
        #define RS232_STOPBITS_2_SUPPORTED
    #endif
    
    
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Determine whether or not hardware flow-control is supported and if so,
    //  which control bits to use to enable it.
    //
    ////////////////////////////////////////////////////////////////////////////
    
    #define RS232_FLOWCONTROL_NONE_SUPPORTED
    #define RS232_FLOWCONTROL_SOFTWARE_SUPPORTED
    
    #if defined(CNEW_RTSCTS)
    
        #define RS232_FLOWCONTROL_HARDWARE_SUPPORTED
        #define RS232_RTSCTS_BITS     CNEW_RTSCTS
        
    #elif defined(CRTSCTS)

        #define RS232_FLOWCONTROL_HARDWARE_SUPPORTED
        #define RS232_RTSCTS_BITS     CRTSCTS

    #endif
    
    
    ////////////////////////////////////////////////////////////////////////////

#endif

