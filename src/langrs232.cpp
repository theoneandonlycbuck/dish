/*
    This file is part of the DISH programming language, Copyright 2014-2020 by 
    Chris Buck.
    
    DISH is free software for non-commercial use; you can redistribute it and/or
    modify it provided
    
        (1) The following Copyright notice is displayed at runtime and in any
            accompanying documentation:
    
            DISH programming language copyright (c) 2014-2020 by Chris Buck.
        
        (2) All source files duplicate this copyright statement in full.
        
    Commercial licenses can be negotiated by contacting Chris Buck at
    chrisbuck1220@hotmail.com.

    DISH is distributed in the hope that it will be useful, but WITHOUT ANY 
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS 
    FOR A PARTICULAR PURPOSE.
*/

#include <fcntl.h>
#include <sys/ioctl.h>
#include <termios.h>

#if _POSIX_C_SOURCE >= 199309L
#include <time.h>
#else
#include <sys/timeb.h>
#endif

#include <unistd.h>

#include <cassert>
#include <sstream>

#include "langrs232.h"
#include "rs232.h"

namespace
{

    ////////////////////////////////////////////////////////////////////////////

    const dish::RS232_BaudRateT BaudRateValues[dish::RS232_BAUD_RATE_NUM] =
    {
        dish::RS232_BAUD_RATE_NULL,
        dish::RS232_BAUD_RATE_50,
        dish::RS232_BAUD_RATE_75,
        dish::RS232_BAUD_RATE_110,
        dish::RS232_BAUD_RATE_134,
        dish::RS232_BAUD_RATE_150,
        dish::RS232_BAUD_RATE_200,
        dish::RS232_BAUD_RATE_300,
        dish::RS232_BAUD_RATE_600,
        dish::RS232_BAUD_RATE_1200,
        dish::RS232_BAUD_RATE_1800,
        dish::RS232_BAUD_RATE_2400,
        dish::RS232_BAUD_RATE_4800,
        dish::RS232_BAUD_RATE_9600,
        dish::RS232_BAUD_RATE_19200,
        dish::RS232_BAUD_RATE_38400,
        dish::RS232_BAUD_RATE_57600,
        dish::RS232_BAUD_RATE_115200,
        dish::RS232_BAUD_RATE_230400,
        dish::RS232_BAUD_RATE_460800,
        dish::RS232_BAUD_RATE_500000,
        dish::RS232_BAUD_RATE_576000,
        dish::RS232_BAUD_RATE_921600,
        dish::RS232_BAUD_RATE_1000000,
        dish::RS232_BAUD_RATE_1152000,
        dish::RS232_BAUD_RATE_1500000,
        dish::RS232_BAUD_RATE_2000000,
        dish::RS232_BAUD_RATE_2500000,
        dish::RS232_BAUD_RATE_3000000,
        dish::RS232_BAUD_RATE_3500000,
        dish::RS232_BAUD_RATE_4000000
    };
    
    INLINEC dish::RS232_BaudRateT IntegerToBaudRate(const dish::IntegerT &arg)
    {
        const bool valid(
            (static_cast< dish::IntegerT >(dish::RS232_BAUD_RATE_NULL) <= arg) && (arg < static_cast< dish::IntegerT >(dish::RS232_BAUD_RATE_NUM))
        );
    
        return (valid ? BaudRateValues[arg] : dish::RS232_BAUD_RATE_NULL);
    }
    
    ////
    
    const dish::RS232_DataBitsT DataBitsValues[dish::RS232_DATA_BITS_NUM] = 
    {
        dish::RS232_DATA_BITS_NULL,
        dish::RS232_DATA_BITS_5,
        dish::RS232_DATA_BITS_6,
        dish::RS232_DATA_BITS_7,
        dish::RS232_DATA_BITS_8
    };
    
    INLINEC dish::RS232_DataBitsT IntegerToDataBits(const dish::IntegerT &arg)
    {
        const bool valid(
            (static_cast< dish::IntegerT >(dish::RS232_DATA_BITS_NULL) <= arg) && (arg < static_cast< dish::IntegerT >(dish::RS232_DATA_BITS_NUM))
        );
    
        return (valid ? DataBitsValues[arg] : dish::RS232_DATA_BITS_NULL);
    }
    
    ////
    
    const dish::RS232_ParityT ParityValues[dish::RS232_PARITY_NUM] =
    {
        dish::RS232_PARITY_NULL,
        dish::RS232_PARITY_NO,
        dish::RS232_PARITY_ODD,
        dish::RS232_PARITY_EVEN
    };
    
    INLINEC dish::RS232_ParityT IntegerToParity(const dish::IntegerT &arg)
    {
        const bool valid(
            (static_cast< dish::IntegerT >(dish::RS232_PARITY_NULL) <= arg) && (arg < static_cast< dish::IntegerT >(dish::RS232_PARITY_NUM))
        );
    
        return (valid ? ParityValues[arg] : dish::RS232_PARITY_NULL);
    }
    
    ////
    
    const dish::RS232_StopBitsT StopBitsValues[dish::RS232_STOP_BITS_NUM] =
    {
        dish::RS232_STOP_BITS_NULL,
        dish::RS232_STOP_BITS_1,
        dish::RS232_STOP_BITS_2
    };
    
    INLINEC dish::RS232_StopBitsT IntegerToStopBits(const dish::IntegerT &arg)
    {
        const bool valid(
            (static_cast< dish::IntegerT >(dish::RS232_STOP_BITS_NULL) <= arg) && (arg < static_cast< dish::IntegerT >(dish::RS232_STOP_BITS_NUM))
        );
    
        return (valid ? StopBitsValues[arg] : dish::RS232_STOP_BITS_NULL);
    }
    
    ////
    
    const dish::RS232_FlowControlT FlowControlValues[dish::RS232_FLOWCTRL_NUM] =
    {
        dish::RS232_FLOWCTRL_NULL,
        dish::RS232_FLOWCTRL_NONE,
        dish::RS232_FLOWCTRL_SOFTWARE,
        dish::RS232_FLOWCTRL_HARDWARE
    };
    
    INLINEC dish::RS232_FlowControlT IntegerToFlowControl(const dish::IntegerT &arg)
    {
        const bool valid(
            (static_cast< dish::IntegerT >(dish::RS232_FLOWCTRL_NULL) <= arg) && (arg < static_cast< dish::IntegerT >(dish::RS232_FLOWCTRL_NUM))
        );
    
        return (valid ? FlowControlValues[arg] : dish::RS232_FLOWCTRL_NULL);
    }

    ////////////////////////////////////////////////////////////////////////////
    
    INLINEC long long int nowMs()
    {
        for(int i(0); i < 5; ++i)
        {
#if _POSIX_C_SOURCE >= 199309L
            struct timespec timer_msec;
            if(0 == clock_gettime(CLOCK_MONOTONIC_COARSE, &timer_msec))
            {
                return (static_cast< long long int >(1000) * static_cast< long long int >(timer_msec.tv_sec) + static_cast< long long int >(timer_msec.tv_nsec / 1000));
            }
#else
            struct timeb timer_msec;
            if(0 == ftime(&timer_msec))
            {
                return (static_cast< long long int >(1000) * static_cast< long long int >(timer_msec.time) + static_cast< long long int >(timer_msec.millitm));
            }
#endif
        }
        
        return -1;
    }

    ////////////////////////////////////////////////////////////////////////////
    
    class RS232Port
    {
        public:
        
            static const int INVALID_FD;
            
            static const dish::RS232_DataBitsT DEFAULT_DATA_BITS;
            static const dish::RS232_ParityT DEFAULT_PARITY;
            static const dish::RS232_StopBitsT DEFAULT_STOP_BITS;
            static const dish::RS232_FlowControlT DEFAULT_FLOW_CONTROL;
            static const dish::IntegerT DEFAULT_TIMEOUT;
            
            static const dish::IntegerT DEFAULT_RECEIVE_TIMEOUT;
    
        private:
            int mFileDescriptor;
            
            dish::IntegerT mXOn;
            dish::IntegerT mXOff;
            
            mutable dish::StringT mReceiveBuffer;
            
        protected:
        
            INLINE bool receive() const throw()
            {
                //  Read input characters from the serial port.
                char buffer[4096];
                const int nbytes(read(mFileDescriptor, buffer, 4096));
                
                //  Did we get any bytes?
                if(nbytes > 0)
                {
                    //  Yes, append the recently read bytes to the internal
                    //  buffer.
                    mReceiveBuffer.append(buffer, nbytes);
                    
                    //  Declare success!
                    return true;
                }
                
                else if(0 == nbytes)
                {
                    //  No, we did not get any bytes but the call was still
                    //  successful.
                    return true;
                }
                
                else
                {
                    //  There was some sort of error reading from the serial
                    //  port.
                    return false;
                }
                
                assert(false);
            }
        
        public:
            INLINE RS232Port() : mFileDescriptor(INVALID_FD), mXOn(-1), mXOff(-1), mReceiveBuffer() {};
            INLINE ~RS232Port() { Close(); };
            
            INLINE bool IsOpen() const throw() { return (mFileDescriptor > 0); };
            
            void Open(
                const dish::StringT &port, 
                const dish::RS232_BaudRateT &baud, 
                const dish::RS232_DataBitsT &databits, 
                const dish::RS232_ParityT &parity, 
                const dish::RS232_StopBitsT &stopbits, 
                const dish::RS232_FlowControlT &flowctrl,
                const dish::IntegerT &timeout
            );
            
            INLINE int Send(const dish::IntegerT &byte) const
            {
                if(IsOpen())
                {
                    const char byte(static_cast< char >(byte));
                
                    if(1 == write(mFileDescriptor, &byte, 1))
                    {
                        return 1;
                    }
                
                    throw dish::Rs232WriteFailureException("Failure to write 1 byte to the specified serial port.");
                }
                
                throw dish::Rs232PortNotOpenException("The serial port is not open.");
            }
    
            INLINE int Send(const dish::StringT &str) const
            {
                if(IsOpen())
                {
                    const int nbytes(static_cast< int >(str.length()));
                
                    if(nbytes == write(mFileDescriptor, str.c_str(), nbytes))
                    {
                        return nbytes;
                    }
                    
                    std::stringstream message;
                    message << "Failure to write ";
                    message << nbytes;
                    message << " bytes to the specified serial port.";
                
                    throw dish::Rs232WriteFailureException(message.str());
                }
                
                throw dish::Rs232PortNotOpenException("The serial port is not open.");
            }
            
            INLINE int SendXOn() const { assert(mXOn >= 0); return Send(mXOn); };
            INLINE int SendXOff() const { assert(mXOff >= 0); return Send(mXOff); };
            
            INLINE dish::IntegerT NumCharactersAvailable() const
            {
                int nbytes(0);
                
                if(IsOpen())
                {
                    if(ioctl(mFileDescriptor, FIONREAD, &nbytes) < 0)
                    {
                        throw dish::Rs232ReadFailureException("Unable to determine number of available characters from the serial port.");
                    }
                }
            
                assert(nbytes >= 0);
                return static_cast< dish::IntegerT >(nbytes);
            }
            
            dish::StringT Receive() const;
            dish::StringT ReceiveTimeout(const dish::IntegerT &timeout) const;
            dish::StringT ReceiveNumCharacters(const dish::IntegerT &nchars, const dish::IntegerT &timeout) const;
            dish::StringT ReceiveTerminated(const dish::StringT &terminal, const bool &case_sensitive, const dish::IntegerT &timeout) const;
            
            INLINE void Close()
            {
                //  First, make sure the serial port is open.
                if(IsOpen())
                {
                    //  The port is open, close it.
                    close(mFileDescriptor);
                    
                    //  Reset the file-descriptor.
                    mFileDescriptor = INVALID_FD;
                    mXOn = -1;
                    mXOff = -1;
                }
            }
        
    };
    
    const int RS232Port::INVALID_FD(-1);
    
#ifndef RS232_DATABITS_8_SUPPORTED
#warning  Default 8-data-bits not supported by target platform.
#endif
    const dish::RS232_DataBitsT RS232Port::DEFAULT_DATA_BITS(dish::RS232_DATA_BITS_8);
    
#ifndef RS232_PARITY_NO_SUPPORTED
#warning  Default no-parity not supported by target platform.
#endif
    const dish::RS232_ParityT RS232Port::DEFAULT_PARITY(dish::RS232_PARITY_NO);
    
#ifndef RS232_STOPBITS_1_SUPPORTED
#warning  Default 1-stop-bit not supported by target platform.
#endif
    const dish::RS232_StopBitsT RS232Port::DEFAULT_STOP_BITS(dish::RS232_STOP_BITS_1);
    
#ifndef RS232_FLOWCONTROL_NONE_SUPPORTED
#warning  Default no-flow-control not supported by target platform.
#endif
    const dish::RS232_FlowControlT RS232Port::DEFAULT_FLOW_CONTROL(dish::RS232_FLOWCTRL_NONE);
    
    const dish::IntegerT RS232Port::DEFAULT_TIMEOUT(100);
    
    const dish::IntegerT RS232Port::DEFAULT_RECEIVE_TIMEOUT(1000);
    
    void RS232Port::Open(
        const dish::StringT &port, 
        const dish::RS232_BaudRateT &baud, 
        const dish::RS232_DataBitsT &databits, 
        const dish::RS232_ParityT &parity, 
        const dish::RS232_StopBitsT &stopbits, 
        const dish::RS232_FlowControlT &flowctrl,
        const dish::IntegerT &timeout)
    {
        //  Make sure the file-descriptor is closed.
        if(!IsOpen())
        {
            //  Open the serial port.
            mFileDescriptor = open(
                port.c_str(), 
                O_RDWR | O_NOCTTY | O_NDELAY
            );
            
            //  Was the port successfully opened?
            if(mFileDescriptor > 0)
            {
                //  Yes, configure the port. Begin by retrieving the configuration
                //  for the port.
                struct termios options = { 0 };
                tcgetattr(mFileDescriptor, &options);
                
                //  Get the XON and XOFF characters.
                mXOn = static_cast< dish::IntegerT >(options.c_cc[VSTART]);
                mXOff = static_cast< dish::IntegerT >(options.c_cc[VSTOP]);
                
                //  Set the baud-rate.
                switch(baud)
                {
#ifdef RS232_BAUDRATE_50_SUPPORTED
                    case dish::RS232_BAUD_RATE_50:
                    {
                        cfsetispeed(&options, B50);
                        cfsetospeed(&options, B50);
                    } break;
#endif

#ifdef RS232_BAUDRATE_75_SUPPORTED
                    case dish::RS232_BAUD_RATE_75:
                    {
                        cfsetispeed(&options, B75);
                        cfsetospeed(&options, B75);
                    } break;
#endif

#ifdef RS232_BAUDRATE_110_SUPPORTED
                    case dish::RS232_BAUD_RATE_110:
                    {
                        cfsetispeed(&options, B110);
                        cfsetospeed(&options, B110);
                    } break;
#endif

#ifdef RS232_BAUDRATE_134_SUPPORTED
                    case dish::RS232_BAUD_RATE_134:
                    {
                        cfsetispeed(&options, B134);
                        cfsetospeed(&options, B134);
                    } break;
#endif

#ifdef RS232_BAUDRATE_150_SUPPORTED
                    case dish::RS232_BAUD_RATE_150:
                    {
                        cfsetispeed(&options, B150);
                        cfsetospeed(&options, B150);
                    } break;
#endif

#ifdef RS232_BAUDRATE_200_SUPPORTED
                    case dish::RS232_BAUD_RATE_200:
                    {
                        cfsetispeed(&options, B200);
                        cfsetospeed(&options, B200);
                    } break;
#endif

#ifdef RS232_BAUDRATE_300_SUPPORTED
                    case dish::RS232_BAUD_RATE_300:
                    {
                        cfsetispeed(&options, B300);
                        cfsetospeed(&options, B300);
                    } break;
#endif

#ifdef RS232_BAUDRATE_50_SUPPORTED
                    case dish::RS232_BAUD_RATE_600:
                    {
                        cfsetispeed(&options, B600);
                        cfsetospeed(&options, B600);
                    } break;
#endif

#ifdef RS232_BAUDRATE_1200_SUPPORTED
                    case dish::RS232_BAUD_RATE_1200:
                    {
                        cfsetispeed(&options, B1200);
                        cfsetospeed(&options, B1200);
                    } break;
#endif

#ifdef RS232_BAUDRATE_1800_SUPPORTED
                    case dish::RS232_BAUD_RATE_1800:
                    {
                        cfsetispeed(&options, B1800);
                        cfsetospeed(&options, B1800);
                    } break;
#endif

#ifdef RS232_BAUDRATE_2400_SUPPORTED
                    case dish::RS232_BAUD_RATE_2400:
                    {
                        cfsetispeed(&options, B2400);
                        cfsetospeed(&options, B2400);
                    } break;
#endif

#ifdef RS232_BAUDRATE_4800_SUPPORTED
                    case dish::RS232_BAUD_RATE_4800:
                    {
                        cfsetispeed(&options, B4800);
                        cfsetospeed(&options, B4800);
                    } break;
#endif

#ifdef RS232_BAUDRATE_9600_SUPPORTED
                    case dish::RS232_BAUD_RATE_9600:
                    {
                        cfsetispeed(&options, B9600);
                        cfsetospeed(&options, B9600);
                    } break;
#endif

#ifdef RS232_BAUDRATE_19200_SUPPORTED
                    case dish::RS232_BAUD_RATE_19200:
                    {
                        cfsetispeed(&options, B19200);
                        cfsetospeed(&options, B19200);
                    } break;
#endif

#ifdef RS232_BAUDRATE_38400_SUPPORTED
                    case dish::RS232_BAUD_RATE_38400:
                    {
                        cfsetispeed(&options, B38400);
                        cfsetospeed(&options, B38400);
                    } break;
#endif

#ifdef RS232_BAUDRATE_57600_SUPPORTED
                    case dish::RS232_BAUD_RATE_57600:
                    {
                        cfsetispeed(&options, B57600);
                        cfsetospeed(&options, B57600);
                    } break;
#endif

#ifdef RS232_BAUDRATE_115200_SUPPORTED
                    case dish::RS232_BAUD_RATE_115200:
                    {
                        cfsetispeed(&options, B115200);
                        cfsetospeed(&options, B115200);
                    } break;
#endif

#ifdef RS232_BAUDRATE_230400_SUPPORTED
                    case dish::RS232_BAUD_RATE_230400:
                    {
                        cfsetispeed(&options, B230400);
                        cfsetospeed(&options, B230400);
                    } break;
#endif

#ifdef RS232_BAUDRATE_460800_SUPPORTED
                    case dish::RS232_BAUD_RATE_460800:
                    {
                        cfsetispeed(&options, B460800);
                        cfsetospeed(&options, B460800);
                    } break;
#endif

#ifdef RS232_BAUDRATE_500000_SUPPORTED
                    case dish::RS232_BAUD_RATE_500000:
                    {
                        cfsetispeed(&options, B500000);
                        cfsetospeed(&options, B500000);
                    } break;
#endif

#ifdef RS232_BAUDRATE_576000_SUPPORTED
                    case dish::RS232_BAUD_RATE_576000:
                    {
                        cfsetispeed(&options, B576000);
                        cfsetospeed(&options, B576000);
                    } break;
#endif

#ifdef RS232_BAUDRATE_921600_SUPPORTED
                    case dish::RS232_BAUD_RATE_921600:
                    {
                        cfsetispeed(&options, B921600);
                        cfsetospeed(&options, B921600);
                    } break;
#endif

#ifdef RS232_BAUDRATE_1000000_SUPPORTED
                    case dish::RS232_BAUD_RATE_1000000:
                    {
                        cfsetispeed(&options, B1000000);
                        cfsetospeed(&options, B1000000);
                    } break;
#endif

#ifdef RS232_BAUDRATE_1152000_SUPPORTED
                    case dish::RS232_BAUD_RATE_1152000:
                    {
                        cfsetispeed(&options, B1152000);
                        cfsetospeed(&options, B1152000);
                    } break;
#endif

#ifdef RS232_BAUDRATE_1500000_SUPPORTED
                    case dish::RS232_BAUD_RATE_1500000:
                    {
                        cfsetispeed(&options, B1500000);
                        cfsetospeed(&options, B1500000);
                    } break;
#endif

#ifdef RS232_BAUDRATE_2000000_SUPPORTED
                    case dish::RS232_BAUD_RATE_2000000:
                    {
                        cfsetispeed(&options, B2000000);
                        cfsetospeed(&options, B2000000);
                    } break;
#endif

#ifdef RS232_BAUDRATE_2500000_SUPPORTED
                    case dish::RS232_BAUD_RATE_2500000:
                    {
                        cfsetispeed(&options, B2500000);
                        cfsetospeed(&options, B2500000);
                    } break;
#endif

#ifdef RS232_BAUDRATE_3000000_SUPPORTED
                    case dish::RS232_BAUD_RATE_3000000:
                    {
                        cfsetispeed(&options, B3000000);
                        cfsetospeed(&options, B3000000);
                    } break;
#endif

#ifdef RS232_BAUDRATE_3500000_SUPPORTED
                    case dish::RS232_BAUD_RATE_3500000:
                    {
                        cfsetispeed(&options, B3500000);
                        cfsetospeed(&options, B3500000);
                    } break;
#endif

#ifdef RS232_BAUDRATE_4000000_SUPPORTED
                    case dish::RS232_BAUD_RATE_4000000:
                    {
                        cfsetispeed(&options, B4000000);
                        cfsetospeed(&options, B4000000);
                    } break;
#endif

                    default:
                    {
                        throw dish::Rs232BadConfigurationException("Bad RS-232 configuration: baud-rate.");
                    }
                     
                }
                
                //  Set the number of data-bits.
                options.c_cflag &= ~CSIZE;
                switch(databits)
                {
#ifdef RS232_DATABITS_5_SUPPORTED
                    case dish::RS232_DATA_BITS_5:
                    {
                        options.c_cflag |= CS5;
                    } break;
#endif

#ifdef RS232_DATABITS_6_SUPPORTED
                    case dish::RS232_DATA_BITS_6:
                    {
                        options.c_cflag |= CS6;
                    } break;
#endif

#ifdef RS232_DATABITS_7_SUPPORTED
                    case dish::RS232_DATA_BITS_7:
                    {
                        options.c_cflag |= CS7;
                    } break;
#endif

#ifdef RS232_DATABITS_8_SUPPORTED
                    case dish::RS232_DATA_BITS_8:
                    {
                        options.c_cflag |= CS8;
                    } break;
#endif
                    
                    default:
                    {
                        throw dish::Rs232BadConfigurationException("Bad RS-232 configuration: data-bits.");
                    }
                    
                }
                
                //  Set the parity.
                options.c_cflag &= ~PARENB;
                switch(parity)
                {
#ifdef RS232_PARITY_NO_SUPPORTED
                    case dish::RS232_PARITY_NO:
                    {
                        //  Empty.
                    } break;
#endif

#ifdef RS232_PARITY_ODD_SUPPORTED
                    case dish::RS232_PARITY_ODD:
                    {
                        options.c_cflag |= PARENB;
                        options.c_cflag |= PARODD;
                        
                        options.c_iflag |= (INPCK | ISTRIP);
                    } break;
#endif

#ifdef RS232_PARITY_EVEN_SUPPORTED
                    case dish::RS232_PARITY_EVEN:
                    {
                        options.c_cflag |= PARENB;
                        options.c_cflag &= ~PARODD;
                        
                        options.c_iflag |= (INPCK | ISTRIP);
                    } break;
#endif
                    
                    default:
                    {
                        throw dish::Rs232BadConfigurationException("Bad RS-232 configuration: parity.");
                    }
                     
                }
            
                //  Set the number of stop-bits.
                options.c_cflag &= ~CSTOPB;
                switch(stopbits)
                {
#ifdef RS232_STOPBITS_1_SUPPORTED
                    case dish::RS232_STOP_BITS_1:
                    {
                        //  Empty
                    } break;
#endif

#ifdef RS232_STOPBITS_2_SUPPORTED
                    case dish::RS232_STOP_BITS_2:
                    {
                        options.c_cflag |= CSTOPB;
                    } break;
#endif
                    
                    default:
                    {
                        throw dish::Rs232BadConfigurationException("Bad RS-232 configuration: stop-bits.");
                    }
                    
                }
                
                //  Setup flow-control.
                switch(flowctrl)
                {
#ifdef RS232_FLOWCONTROL_NONE_SUPPORTED
                    case dish::RS232_FLOWCTRL_NONE:
                    {
                        options.c_iflag &= ~(IXON | IXOFF | IXANY);
    #ifdef RS232_FLOWCONTROL_HARDWARE_SUPPORTED
                        options.c_cflag &= ~RS232_RTSCTS_BITS;
    #endif
                    } break;
#endif
                    
#ifdef RS232_FLOWCONTROL_SOFTWARE_SUPPORTED
                    case dish::RS232_FLOWCTRL_SOFTWARE:
                    {
                        options.c_iflag |= (IXON | IXOFF | IXANY);
                    } break;
#endif

#ifdef RS232_FLOWCONTROL_HARDWARE_SUPPORTED
                    case dish::RS232_FLOWCTRL_HARDWARE:
                    {
                        options.c_cflag |= RS232_RTSCTS_BITS;
                    } break;
#endif
                    
                    default:
                    {
                        throw dish::Rs232BadConfigurationException("Bad RS-232 configuration: flow-control.");
                    }
                    
                }
                
                //  Set the timeout for the port, measured in 1/10 second, not mS.
                options.c_cc[VMIN]  = 0;
                options.c_cc[VTIME] = static_cast< int >((timeout / 100) + (0 != (timeout % 100)) ? 1 : 0);
                
                //  Set additional base-configuration.
                options.c_cflag |= (CLOCAL | CREAD);
                options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
                
                //  Apply the configuration.
                tcsetattr(mFileDescriptor, TCSANOW, &options);
            }
            else
            {
                throw dish::Rs232UnableToOpenPortException("Unable to open the serial port.");
            }
        }
        else
        {
            throw dish::Rs232UnableToOpenPortException("Unable to open serial port: port alredy open.");
        }
    }
    
    dish::StringT RS232Port::Receive() const
    {
        //  Make sure the serial-port is open.
        if(IsOpen())
        {
            //  Receive any available bytes from the serial-port.
            if(receive())
            {
                const dish::StringT ret(mReceiveBuffer);
                mReceiveBuffer.clear();
                
                return ret;
            }
            
            throw dish::Rs232ReadFailureException("Unable to read from the serial port.");
        }
        
        throw dish::Rs232PortNotOpenException("The serial port is not open.");
    }
    
    dish::StringT RS232Port::ReceiveTimeout(const dish::IntegerT &timeout) const
    {
        if(IsOpen())
        {
            //  Get the ending timestamp.
            long long int end_time(nowMs());
            
            if(end_time >= 0)
            {
                end_time += static_cast< long long int >(timeout);
                
                //  Read characters from the input file-descriptor for the
                //  specified amount of time.
                for(bool done(false); !done; )
                {
                    if(receive())
                    {
                        const long long int now(nowMs());
                    
                        if((-1 == now) || (now >= end_time))
                        {
                            done = true;
                        }
                    }
                    else
                    {
                        done = true;
                    }
                }
            }
            
            const dish::StringT ret(mReceiveBuffer);
            mReceiveBuffer.clear();
            
            return ret;
        }
        
        throw dish::Rs232PortNotOpenException("The serial port is not open.");
    }
    
    dish::StringT RS232Port::ReceiveNumCharacters(const dish::IntegerT &nchars, const dish::IntegerT &timeout) const
    {
        if(IsOpen())
        {
            //  Get the ending timestamp.
            long long int end_time(nowMs());
            
            if(end_time >= 0)
            {
                end_time += static_cast< long long int >(timeout);
                
                //  Read characters from the input file-descriptor for the
                //  specified amount of time.
                for(bool done(false); !done; )
                {
                    //  Read the next series of bytes from the serial-port.
                    if(receive())
                    {
                        //  Have we received enough characters?
                        if(mReceiveBuffer.length() < static_cast< std::string::size_type >(nchars))
                        {
                            //  Has the call timed-out?
                            const long long int now(nowMs());
                        
                            if((-1 == now) || (now >= end_time))
                            {
                                //  Timeout
                                done = true;
                            }
                        }
                        else
                        {
                            //  We got the requested number of bytes
                            done = true;
                        }
                    }
                    else
                    {
                        //  There was an error reading bytes from the serial-
                        //  port
                        done = true;
                    }
                }
            }
            
            const dish::StringT ret(mReceiveBuffer.substr(0, static_cast< std::string::size_type >(nchars)));
            mReceiveBuffer.erase(0, static_cast< std::string::size_type >(nchars));
            
            return ret;
        }
        
        throw dish::Rs232PortNotOpenException("The serial port is not open.");
    }
    
    dish::StringT RS232Port::ReceiveTerminated(const dish::StringT &terminal, const bool &case_sensitive, const dish::IntegerT &timeout) const
    {
        if(IsOpen())
        {
            //  Get the ending timestamp.
            long long int end_time(nowMs());
            
            if(end_time >= 0)
            {
                end_time += static_cast< long long int >(timeout);
                
                //  Read characters from the input file-descriptor for the
                //  specified amount of time.
                for(bool done(false); !done; )
                {
                    //  Read the next series of bytes from the serial-port.
                    if(receive())
                    {
                        const std::string::size_type index(dish::IndexOf(mReceiveBuffer, terminal, case_sensitive));
                        
                        //  Have we seen the terminal string?
                        if(std::string::npos == index)
                        {
                            //  Has the call timed-out?
                            const long long int now(nowMs());
                        
                            if((-1 == now) || (now >= end_time))
                            {
                                //  Timeout
                                done = true;
                            }
                        }
                        else
                        {
                            const dish::StringT ret(mReceiveBuffer.substr(0, index));
                            mReceiveBuffer.erase(0, index);
                            
                            return ret;
                        }
                    }
                    else
                    {
                        //  There was an error reading bytes from the serial-
                        //  port
                        done = true;
                    }
                }
            }
            
            const dish::StringT ret(mReceiveBuffer);
            mReceiveBuffer.clear();
            
            return ret;
        }
        
        throw dish::Rs232PortNotOpenException("The serial port is not open.");
    }

    ////////////////////////////////////////////////////////////////////////////
    
    class RS232HandleSet : public dish::HandleList< RS232Port, RS232_MAX_NUM_HANDLES >
    {
        public:
            INLINE RS232HandleSet() : dish::HandleList< RS232Port, RS232_MAX_NUM_HANDLES >() {};
        
            INLINE unsigned int Open(
                const dish::StringT &port, 
                const dish::RS232_BaudRateT &baud, 
                const dish::RS232_DataBitsT &databits, 
                const dish::RS232_ParityT &parity, 
                const dish::RS232_StopBitsT &stopbits, 
                const dish::RS232_FlowControlT &flowctrl,
                const dish::IntegerT &timeout)
            {
                const unsigned int handle(Allocate());
                operator[](handle).Open(port, baud, databits, parity, stopbits, flowctrl, timeout);
                
                return handle;
            }
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    RS232HandleSet RS232Handles;

    ////////////////////////////////////////////////////////////////////////////

}

/******************************************************************************

    dish::Rs232BaudRateSupportedFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Rs232BaudRateSupportedFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const IntegerT baud(getParam(symtab, "baud")->AsInteger());

    return BooleanValue::MakeLockedValue(
        (static_cast< IntegerT >(RS232_BAUD_RATE_NULL) < baud) && (baud < static_cast< IntegerT >(RS232_BAUD_RATE_NUM))
    );
}

/******************************************************************************

    dish::Rs232DataBitsSupportedFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Rs232DataBitsSupportedFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const IntegerT databits(getParam(symtab, "databits")->AsInteger());

    return BooleanValue::MakeLockedValue(
        (static_cast< IntegerT >(RS232_DATA_BITS_NULL) < databits) && (databits < static_cast< IntegerT >(RS232_DATA_BITS_NUM))
    );
}

/******************************************************************************

    dish::Rs232ParitySupportedFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Rs232ParitySupportedFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const IntegerT parity(getParam(symtab, "parity")->AsInteger());

    return BooleanValue::MakeLockedValue(
        (static_cast< IntegerT >(RS232_PARITY_NULL) < parity) && (parity < static_cast< IntegerT >(RS232_PARITY_NUM))
    );
}

/******************************************************************************

    dish::Rs232StopBitsSupportedFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Rs232StopBitsSupportedFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const IntegerT stopbits(getParam(symtab, "stopbits")->AsInteger());

    return BooleanValue::MakeLockedValue(
        (static_cast< IntegerT >(RS232_STOP_BITS_NULL) < stopbits) && (stopbits < static_cast< IntegerT >(RS232_STOP_BITS_NUM))
    );
}

/******************************************************************************

    dish::Rs232FlowControlSupportedFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Rs232FlowControlSupportedFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const IntegerT flowcontrol(getParam(symtab, "flowcontrol")->AsInteger());

    return BooleanValue::MakeLockedValue(
        (static_cast< IntegerT >(RS232_FLOWCTRL_NULL) < flowcontrol) && (flowcontrol < static_cast< IntegerT >(RS232_FLOWCTRL_NUM))
    );
}

/******************************************************************************
CreateRs232ConfigurationStructure()
    dish::Rs232DefaultConfigurationFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Rs232DefaultConfigurationFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > config(getParam(symtab, "config"));

    config->Member("BaudRate")->Assign(static_cast< IntegerT >(RS232_BAUD_RATE_NULL));
    config->Member("DataBits")->Assign(static_cast< IntegerT >(RS232Port::DEFAULT_DATA_BITS));
    config->Member("StopBits")->Assign(static_cast< IntegerT >(RS232Port::DEFAULT_PARITY));
    config->Member("Parity")->Assign(static_cast< IntegerT >(RS232Port::DEFAULT_STOP_BITS));
    config->Member("FlowControl")->Assign(static_cast< IntegerT >(RS232Port::DEFAULT_FLOW_CONTROL));
    config->Member("Timeout")->Assign(static_cast< IntegerT >(RS232Port::DEFAULT_TIMEOUT));

    return config;
}

/******************************************************************************

    dish::Rs232MakeConfiguration1Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Rs232MakeConfiguration1Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > config(CreateRs232ConfigurationStructure()->Declare());

    config->Member("BaudRate")->Assign(getParam(symtab, "baudrate")->AsInteger());
    config->Member("DataBits")->Assign(static_cast< IntegerT >(RS232Port::DEFAULT_DATA_BITS));
    config->Member("StopBits")->Assign(static_cast< IntegerT >(RS232Port::DEFAULT_PARITY));
    config->Member("Parity")->Assign(static_cast< IntegerT >(RS232Port::DEFAULT_STOP_BITS));
    config->Member("FlowControl")->Assign(static_cast< IntegerT >(RS232Port::DEFAULT_FLOW_CONTROL));
    config->Member("Timeout")->Assign(static_cast< IntegerT >(RS232Port::DEFAULT_TIMEOUT));

    return config;
}

/******************************************************************************

    dish::Rs232MakeConfiguration4Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Rs232MakeConfiguration4Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > config(CreateRs232ConfigurationStructure()->Declare());

    config->Member("BaudRate")->Assign(getParam(symtab, "baudrate")->AsInteger());
    config->Member("DataBits")->Assign(getParam(symtab, "databits")->AsInteger());
    config->Member("StopBits")->Assign(getParam(symtab, "stopbits")->AsInteger());
    config->Member("Parity")->Assign(getParam(symtab, "parity")->AsInteger());
    config->Member("FlowControl")->Assign(static_cast< IntegerT >(RS232Port::DEFAULT_FLOW_CONTROL));
    config->Member("Timeout")->Assign(static_cast< IntegerT >(RS232Port::DEFAULT_TIMEOUT));

    return config;
}

/******************************************************************************

    dish::Rs232MakeConfiguration5Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Rs232MakeConfiguration5Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > config(CreateRs232ConfigurationStructure()->Declare());

    config->Member("BaudRate")->Assign(getParam(symtab, "baudrate")->AsInteger());
    config->Member("DataBits")->Assign(getParam(symtab, "databits")->AsInteger());
    config->Member("StopBits")->Assign(getParam(symtab, "stopbits")->AsInteger());
    config->Member("Parity")->Assign(getParam(symtab, "parity")->AsInteger());
    config->Member("FlowControl")->Assign(getParam(symtab, "flowcontrol")->AsInteger());
    config->Member("Timeout")->Assign(static_cast< IntegerT >(RS232Port::DEFAULT_TIMEOUT));

    return config;
}

/******************************************************************************

    dish::Rs232MakeConfiguration6Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Rs232MakeConfiguration6Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > config(CreateRs232ConfigurationStructure()->Declare());

    config->Member("BaudRate")->Assign(getParam(symtab, "baudrate")->AsInteger());
    config->Member("DataBits")->Assign(getParam(symtab, "databits")->AsInteger());
    config->Member("StopBits")->Assign(getParam(symtab, "stopbits")->AsInteger());
    config->Member("Parity")->Assign(getParam(symtab, "parity")->AsInteger());
    config->Member("FlowControl")->Assign(getParam(symtab, "flowcontrol")->AsInteger());
    config->Member("Timeout")->Assign(getParam(symtab, "timeout")->AsInteger());

    return config;
}

/******************************************************************************

    dish::Rs232OpenFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Rs232OpenFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > config(getParam(symtab, "config"));

    return dish::IntegerValue::MakeValue(
        static_cast< IntegerT >(
            RS232Handles.Open(
                getParam(symtab, "port")->AsString(),
                IntegerToBaudRate(config->Member("BaudRate")->AsInteger()),
                IntegerToDataBits(config->Member("DataBits")->AsInteger()),
                IntegerToParity(config->Member("Parity")->AsInteger()),
                IntegerToStopBits(config->Member("StopBits")->AsInteger()),
                IntegerToFlowControl(config->Member("FlowControl")->AsInteger()),
                config->Member("Timeout")->AsInteger()
            )
        ), 
        LOCKED
    );
}

/******************************************************************************

    dish::Rs232NumOpenFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Rs232NumOpenFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return dish::IntegerValue::MakeValue(
        static_cast< IntegerT >(RS232Handles.NumAllocated()), LOCKED
    );
}

/******************************************************************************

    dish::Rs232IsOpenFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Rs232IsOpenFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const IntegerT handle(getParam(symtab, "handle")->AsInteger());

    if(RS232Handles.IsValid(handle))
    {
        return BooleanValue::MakeLockedValue(RS232Handles[handle].IsOpen());
    }

    return BooleanValue::MakeValue(false, LOCKED);
}

/******************************************************************************

    dish::Rs232SendFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Rs232SendFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const IntegerT handle(getParam(symtab, "handle")->AsInteger());

    return IntegerValue::MakeValue(
        RS232Handles[handle].Send(getParam(symtab, "arg")->AsString()), LOCKED
    );
}

/******************************************************************************

    dish::Rs232SendXOnFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Rs232SendXOnFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const IntegerT handle(getParam(symtab, "handle")->AsInteger());

    return IntegerValue::MakeValue(RS232Handles[handle].SendXOn(), LOCKED);
}

/******************************************************************************

    dish::Rs232SendXOffFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Rs232SendXOffFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const IntegerT handle(getParam(symtab, "handle")->AsInteger());

    return IntegerValue::MakeValue(RS232Handles[handle].SendXOff(), LOCKED);
}

/******************************************************************************

    dish::Rs232NumCharactersAvailableFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Rs232NumCharactersAvailableFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const IntegerT handle(getParam(symtab, "handle")->AsInteger());

    return IntegerValue::MakeValue(RS232Handles[handle].NumCharactersAvailable(), LOCKED);
}

/******************************************************************************

    dish::Rs232ReceiveFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Rs232ReceiveFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const IntegerT handle(getParam(symtab, "handle")->AsInteger());

    return StringValue::MakeValue(RS232Handles[handle].Receive(), LOCKED);
}

/******************************************************************************

    dish::Rs232ReceiveTimeoutFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Rs232ReceiveTimeoutFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    //  Get the serial-port.
    const RS232Port &port(
        RS232Handles[getParam(symtab, "handle")->AsInteger()]
    );

    return StringValue::MakeValue(
        port.ReceiveTimeout(getParam(symtab, "timeout")->AsInteger()),
        LOCKED
    );
}

/******************************************************************************

    dish::Rs232ReceiveNumCharacters2Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Rs232ReceiveNumCharacters2Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    //  Get the serial-port.
    const RS232Port &port(
        RS232Handles[getParam(symtab, "handle")->AsInteger()]
    );

    return StringValue::MakeValue(
        port.ReceiveNumCharacters(
            getParam(symtab, "nchars")->AsInteger(),
            RS232Port::DEFAULT_RECEIVE_TIMEOUT
        ),
        LOCKED
    );
}

/******************************************************************************

    dish::Rs232ReceiveNumCharacters3Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Rs232ReceiveNumCharacters3Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    //  Get the serial-port.
    const RS232Port &port(
        RS232Handles[getParam(symtab, "handle")->AsInteger()]
    );

    return StringValue::MakeValue(
        port.ReceiveNumCharacters(
            getParam(symtab, "nchars")->AsInteger(),
            getParam(symtab, "timeout")->AsInteger()
        ),
        LOCKED
    );
}

/******************************************************************************

    dish::Rs232ReceiveSentinel2Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Rs232ReceiveSentinel2Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    //  Get the serial-port.
    const RS232Port &port(
        RS232Handles[getParam(symtab, "handle")->AsInteger()]
    );

    return StringValue::MakeValue(
        port.ReceiveTerminated(
            getParam(symtab, "sentinel")->AsString(),
            true,
            RS232Port::DEFAULT_RECEIVE_TIMEOUT
        ),
        LOCKED
    );
}

/******************************************************************************

    dish::Rs232ReceiveSentinel3Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Rs232ReceiveSentinel3Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    //  Get the serial-port.
    const RS232Port &port(
        RS232Handles[getParam(symtab, "handle")->AsInteger()]
    );

    return StringValue::MakeValue(
        port.ReceiveTerminated(
            getParam(symtab, "sentinel")->AsString(),
            getParam(symtab, "casesensitive")->AsBoolean(),
            RS232Port::DEFAULT_RECEIVE_TIMEOUT
        ),
        LOCKED
    );
}

/******************************************************************************

    dish::Rs232ReceiveSentinel4Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Rs232ReceiveSentinel4Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    //  Get the serial-port.
    const RS232Port &port(
        RS232Handles[getParam(symtab, "handle")->AsInteger()]
    );

    return StringValue::MakeValue(
        port.ReceiveTerminated(
            getParam(symtab, "sentinel")->AsString(),
            getParam(symtab, "casesensitive")->AsBoolean(),
            getParam(symtab, "timeout")->AsInteger()
        ),
        LOCKED
    );
}

/******************************************************************************

    dish::Rs232CloseFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Rs232CloseFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const IntegerT handle(getParam(symtab, "handle")->AsInteger());

    return BooleanValue::MakeLockedValue(RS232Handles.Destroy(handle));
}

/******************************************************************************

    dish::Rs232CloseAllFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Rs232CloseAllFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    Rs232DestroyAllHandles();

    return NullValue::MakeValue();
}

/******************************************************************************

    Global definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::CreateRs232ConfigurationStructure()
{
    static std::shared_ptr< StructureTypeAtomic > structure;
    
    if(0 == structure.get())
    {
        std::shared_ptr< IntegerTypeAtomic > integer_type(IntegerTypeAtomic::MakeValue());
        
        structure = StructureTypeAtomic::MakeValue();
        structure->Add("BaudRate", integer_type);
        structure->Add("DataBits", integer_type);
        structure->Add("StopBits", integer_type);
        structure->Add("Parity", integer_type);
        structure->Add("FlowControl", integer_type);
        structure->Add("Timeout", integer_type);
    }

    return structure;
}
 
void dish::Rs232DestroyAllHandles()
{
    RS232Handles.DestroyAll();
}

