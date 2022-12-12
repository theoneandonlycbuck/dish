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

#ifndef DISH_LANGRS232_H
#define DISH_LANGRS232_H

#include <memory>

#include "atomics.h"
#include "inline.h"
#include "langid.h"
#include "language.h"
#include "symtab.h"

#define RS232_MAX_NUM_HANDLES       8

namespace dish
{
    
    ////////////////////////////////////////////////////////////////////////////
    
    using RS232_ReceiveModeT = enum
    {
        RS232_RCVMODE_NULL = 0,
        
        RS232_RCVMODE_TIMEOUT,
        RS232_RCVMODE_NUMCHARS,
        RS232_RCVMODE_SENTINEL
    };

    using RS232_BaudRateT = enum
    {
        RS232_BAUD_RATE_NULL = 0,
        
        RS232_BAUD_RATE_50,
        RS232_BAUD_RATE_75,
        RS232_BAUD_RATE_110,
        RS232_BAUD_RATE_134,
        RS232_BAUD_RATE_150,
        RS232_BAUD_RATE_200,
        RS232_BAUD_RATE_300,
        RS232_BAUD_RATE_600,
        RS232_BAUD_RATE_1200,
        RS232_BAUD_RATE_1800,
        RS232_BAUD_RATE_2400,
        RS232_BAUD_RATE_4800,
        RS232_BAUD_RATE_9600,
        RS232_BAUD_RATE_19200,
        RS232_BAUD_RATE_38400,
        RS232_BAUD_RATE_57600,
        RS232_BAUD_RATE_115200,
        RS232_BAUD_RATE_230400,
        RS232_BAUD_RATE_460800,
        RS232_BAUD_RATE_500000,
        RS232_BAUD_RATE_576000,
        RS232_BAUD_RATE_921600,
        RS232_BAUD_RATE_1000000,
        RS232_BAUD_RATE_1152000,
        RS232_BAUD_RATE_1500000,
        RS232_BAUD_RATE_2000000,
        RS232_BAUD_RATE_2500000,
        RS232_BAUD_RATE_3000000,
        RS232_BAUD_RATE_3500000,
        RS232_BAUD_RATE_4000000,
        
        RS232_BAUD_RATE_NUM
    };
    
    using RS232_DataBitsT = enum
    {
        RS232_DATA_BITS_NULL = 0,
        
        RS232_DATA_BITS_5,
        RS232_DATA_BITS_6,
        RS232_DATA_BITS_7,
        RS232_DATA_BITS_8,
        
        RS232_DATA_BITS_NUM
    };
    
    using RS232_ParityT = enum
    {
        RS232_PARITY_NULL = 0,
        
        RS232_PARITY_NO,
        RS232_PARITY_ODD,
        RS232_PARITY_EVEN,
        
        RS232_PARITY_NUM
    };
    
    using RS232_StopBitsT = enum
    {
        RS232_STOP_BITS_NULL = 0,
        
        RS232_STOP_BITS_1,
        RS232_STOP_BITS_2,
        
        RS232_STOP_BITS_NUM
    };
    
    using RS232_FlowControlT = enum
    {
        RS232_FLOWCTRL_NULL = 0,
        
        RS232_FLOWCTRL_NONE,
        RS232_FLOWCTRL_SOFTWARE,
        RS232_FLOWCTRL_HARDWARE,
        
        RS232_FLOWCTRL_NUM
    };
    
    ////////////////////////////////////////////////////////////////////////////

    class Rs232BaudRateSupportedFunction : public ExecutableAtomic
    {
        protected:
            INLINE Rs232BaudRateSupportedFunction() : ExecutableAtomic() { addParam("baud", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< Rs232BaudRateSupportedFunction > MakeValue() { return std::shared_ptr< Rs232BaudRateSupportedFunction >(new Rs232BaudRateSupportedFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class Rs232DataBitsSupportedFunction : public ExecutableAtomic
    {
        protected:
            INLINE Rs232DataBitsSupportedFunction() : ExecutableAtomic() { addParam("databits", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< Rs232DataBitsSupportedFunction > MakeValue() { return std::shared_ptr< Rs232DataBitsSupportedFunction >(new Rs232DataBitsSupportedFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class Rs232ParitySupportedFunction : public ExecutableAtomic
    {
        protected:
            INLINE Rs232ParitySupportedFunction() : ExecutableAtomic() { addParam("parity", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< Rs232ParitySupportedFunction > MakeValue() { return std::shared_ptr< Rs232ParitySupportedFunction >(new Rs232ParitySupportedFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class Rs232StopBitsSupportedFunction : public ExecutableAtomic
    {
        protected:
            INLINE Rs232StopBitsSupportedFunction() : ExecutableAtomic() { addParam("stopbits", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< Rs232StopBitsSupportedFunction > MakeValue() { return std::shared_ptr< Rs232StopBitsSupportedFunction >(new Rs232StopBitsSupportedFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class Rs232FlowControlSupportedFunction : public ExecutableAtomic
    {
        protected:
            INLINE Rs232FlowControlSupportedFunction() : ExecutableAtomic() { addParam("flowcontrol", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< Rs232FlowControlSupportedFunction > MakeValue() { return std::shared_ptr< Rs232FlowControlSupportedFunction >(new Rs232FlowControlSupportedFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    ////

    class Rs232DefaultConfigurationFunction : public ExecutableAtomic
    {
        protected:
            INLINE Rs232DefaultConfigurationFunction() : ExecutableAtomic() { addParam("config", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< Rs232DefaultConfigurationFunction > MakeValue() { return std::shared_ptr< Rs232DefaultConfigurationFunction >(new Rs232DefaultConfigurationFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class Rs232MakeConfiguration1Function : public ExecutableAtomic
    {
        protected:
            INLINE Rs232MakeConfiguration1Function() : ExecutableAtomic()
            {
                addParam("baudrate", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< Rs232MakeConfiguration1Function > MakeValue() { return std::shared_ptr< Rs232MakeConfiguration1Function >(new Rs232MakeConfiguration1Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class Rs232MakeConfiguration4Function : public ExecutableAtomic
    {
        protected:
            INLINE Rs232MakeConfiguration4Function() : ExecutableAtomic()
            {
                addParam("baudrate", REFERENCE_PARAMETER);
                addParam("databits", REFERENCE_PARAMETER);
                addParam("parity", REFERENCE_PARAMETER);
                addParam("stopbits", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< Rs232MakeConfiguration4Function > MakeValue() { return std::shared_ptr< Rs232MakeConfiguration4Function >(new Rs232MakeConfiguration4Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class Rs232MakeConfiguration5Function : public ExecutableAtomic
    {
        protected:
            INLINE Rs232MakeConfiguration5Function() : ExecutableAtomic()
            {
                addParam("baudrate", REFERENCE_PARAMETER);
                addParam("databits", REFERENCE_PARAMETER);
                addParam("parity", REFERENCE_PARAMETER);
                addParam("stopbits", REFERENCE_PARAMETER);
                addParam("flowcontrol", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< Rs232MakeConfiguration5Function > MakeValue() { return std::shared_ptr< Rs232MakeConfiguration5Function >(new Rs232MakeConfiguration5Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class Rs232MakeConfiguration6Function : public ExecutableAtomic
    {
        protected:
            INLINE Rs232MakeConfiguration6Function() : ExecutableAtomic()
            {
                addParam("baudrate", REFERENCE_PARAMETER);
                addParam("databits", REFERENCE_PARAMETER);
                addParam("parity", REFERENCE_PARAMETER);
                addParam("stopbits", REFERENCE_PARAMETER);
                addParam("flowcontrol", REFERENCE_PARAMETER);
                addParam("timeout", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< Rs232MakeConfiguration6Function > MakeValue() { return std::shared_ptr< Rs232MakeConfiguration6Function >(new Rs232MakeConfiguration6Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    ////

    class Rs232OpenFunction : public ExecutableAtomic
    {
        protected:
            INLINE Rs232OpenFunction() : ExecutableAtomic()
            {
                addParam("port", REFERENCE_PARAMETER);
                addParam("config", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< Rs232OpenFunction > MakeValue() { return std::shared_ptr< Rs232OpenFunction >(new Rs232OpenFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class Rs232NumOpenFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE Rs232NumOpenFunction() : ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< Rs232NumOpenFunction > MakeValue() { return std::shared_ptr< Rs232NumOpenFunction >(new Rs232NumOpenFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class Rs232IsOpenFunction : public ExecutableAtomic
    {
        protected:
            INLINE Rs232IsOpenFunction() : ExecutableAtomic() { addParam("handle", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< Rs232IsOpenFunction > MakeValue() { return std::shared_ptr< Rs232IsOpenFunction >(new Rs232IsOpenFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    class Rs232SendFunction : public ExecutableAtomic
    {
        protected:
            INLINE Rs232SendFunction() : ExecutableAtomic() { addParam("handle", REFERENCE_PARAMETER); addParam("arg", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< Rs232SendFunction > MakeValue() { return std::shared_ptr< Rs232SendFunction >(new Rs232SendFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    class Rs232SendXOnFunction : public ExecutableAtomic
    {
        protected:
            INLINE Rs232SendXOnFunction() : dish::ExecutableAtomic() { addParam("handle", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< Rs232SendXOnFunction > MakeValue() { return std::shared_ptr< Rs232SendXOnFunction >(new Rs232SendXOnFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    class Rs232SendXOffFunction : public ExecutableAtomic
    {
        protected:
            INLINE Rs232SendXOffFunction() : ExecutableAtomic() { addParam("handle", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< Rs232SendXOffFunction > MakeValue() { return std::shared_ptr< Rs232SendXOffFunction >(new Rs232SendXOffFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    class Rs232NumCharactersAvailableFunction : public ExecutableAtomic
    {
        protected:
            INLINE Rs232NumCharactersAvailableFunction() : ExecutableAtomic() { addParam("handle", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< Rs232NumCharactersAvailableFunction > MakeValue() { return std::shared_ptr< Rs232NumCharactersAvailableFunction >(new Rs232NumCharactersAvailableFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    class Rs232ReceiveFunction : public ExecutableAtomic
    {
        protected:
            INLINE Rs232ReceiveFunction() : ExecutableAtomic() { addParam("handle", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< Rs232ReceiveFunction > MakeValue() { return std::shared_ptr< Rs232ReceiveFunction >(new Rs232ReceiveFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    class Rs232ReceiveTimeoutFunction : public ExecutableAtomic
    {
        protected:
            INLINE Rs232ReceiveTimeoutFunction() : ExecutableAtomic()
            {
                addParam("handle", REFERENCE_PARAMETER);
                addParam("timeout", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< Rs232ReceiveTimeoutFunction > MakeValue() { return std::shared_ptr< Rs232ReceiveTimeoutFunction >(new Rs232ReceiveTimeoutFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    class Rs232ReceiveNumCharacters2Function : public ExecutableAtomic
    {
        protected:
            INLINE Rs232ReceiveNumCharacters2Function() : ExecutableAtomic()
            {
                addParam("handle", REFERENCE_PARAMETER);
                addParam("nchars", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< Rs232ReceiveNumCharacters2Function > MakeValue() { return std::shared_ptr< Rs232ReceiveNumCharacters2Function >(new Rs232ReceiveNumCharacters2Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    class Rs232ReceiveNumCharacters3Function : public ExecutableAtomic
    {
        protected:
            INLINE Rs232ReceiveNumCharacters3Function() : ExecutableAtomic()
            {
                addParam("handle", REFERENCE_PARAMETER);
                addParam("nchars", REFERENCE_PARAMETER);
                addParam("timeout", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< Rs232ReceiveNumCharacters3Function > MakeValue() { return std::shared_ptr< Rs232ReceiveNumCharacters3Function >(new Rs232ReceiveNumCharacters3Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    class Rs232ReceiveSentinel2Function : public ExecutableAtomic
    {
        protected:
            INLINE Rs232ReceiveSentinel2Function() : ExecutableAtomic() 
            {
                addParam("handle", REFERENCE_PARAMETER);
                addParam("sentinel", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< Rs232ReceiveSentinel2Function > MakeValue() { return std::shared_ptr< Rs232ReceiveSentinel2Function >(new Rs232ReceiveSentinel2Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    class Rs232ReceiveSentinel3Function : public ExecutableAtomic
    {
        protected:
            INLINE Rs232ReceiveSentinel3Function() : ExecutableAtomic() 
            {
                addParam("handle", REFERENCE_PARAMETER);
                addParam("sentinel", REFERENCE_PARAMETER);
                addParam("casesensitive", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< Rs232ReceiveSentinel3Function > MakeValue() { return std::shared_ptr< Rs232ReceiveSentinel3Function >(new Rs232ReceiveSentinel3Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    class Rs232ReceiveSentinel4Function : public ExecutableAtomic
    {
        protected:
            INLINE Rs232ReceiveSentinel4Function() : ExecutableAtomic() 
            {
                addParam("handle", REFERENCE_PARAMETER);
                addParam("sentinel", REFERENCE_PARAMETER);
                addParam("casesensitive", REFERENCE_PARAMETER);
                addParam("timeout", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< Rs232ReceiveSentinel4Function > MakeValue() { return std::shared_ptr< Rs232ReceiveSentinel4Function >(new Rs232ReceiveSentinel4Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    class Rs232CloseFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE Rs232CloseFunction() : ExecutableAtomic() { addParam("handle", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< Rs232CloseFunction > MakeValue() { return std::shared_ptr< Rs232CloseFunction >(new Rs232CloseFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    class Rs232CloseAllFunction : public ExecutableAtomic
    {
        protected:
            INLINE Rs232CloseAllFunction() : ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< Rs232CloseAllFunction > MakeValue() { return std::shared_ptr< Rs232CloseAllFunction >(new Rs232CloseAllFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    ////////////////////////////////////////////////////////////////////////////
    
    extern std::shared_ptr< iAtomic > CreateRs232ConfigurationStructure();
    
    extern void Rs232DestroyAllHandles();

    ////////////////////////////////////////////////////////////////////////////

}

#endif

