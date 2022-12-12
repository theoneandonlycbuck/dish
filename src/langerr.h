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

#ifndef DISH_LANGERR_H
#define DISH_LANGERR_H

#include "dishconfig.h"

#include <list>
#include <memory>
#include <string>
#include <vector>

#include "inline.h"
#include "types.h"

namespace dish
{

    ////////////////////////////////////////////////////////////////////////////
    
    class iAtomic;
    class LanguageSymbolTable;

    ////////////////////////////////////////////////////////////////////////////

    class ErrorCallbacks
    {
        public:
            
            ////

            using ErrTypeT = enum
            {
                ERR_Null = 0,
                
                ERR_Ok,

                ERR_Terminate,
                
                ERR_IllegalCast,
                ERR_ValueLocked,
                ERR_NoSuchMember,
                ERR_DuplicateSymbol,
                ERR_NoSuchSymbol,
                ERR_DivideByZero,
                ERR_DomainError,
                ERR_RangeError,
                
                ERR_IllegalHandle,
                ERR_IllegalValue,
                
                ERR_StackOverflowError,
                
#ifdef LANG_LIB_FILEIO
                ERR_TooManyOpenFiles,
                ERR_UnableToOpenFile,
                ERR_FileNotOpen,
                ERR_FileWriteError,
                ERR_FileReadError,
                ERR_FileReadEndOfFile,
#endif
                
#ifdef LANG_LIB_NETWORK
                ERR_TooManyOpenSockets,
                ERR_UnableToOpenSocket,
                ERR_UnableToCloseSocket,
                ERR_NetworkInvalidAddress,
                ERR_NetworkUnableToConnectToServer,
                ERR_NetworkSocketNotOpen,
                ERR_NetworkSocketWriteError,
                ERR_NetworkSocketReadError,
#endif
                
#ifdef LANG_LIB_MATH_MATRIX
                ERR_MatrixInvalidError,
                ERR_MatrixNotSquareError,
                ERR_ZeroDeterminantError,
                ERR_MatrixDimensionError,
#endif
            
#ifdef LANG_LIB_DATABASE
                ERR_DB_InvalidConnectionType,
                ERR_DB_TooManyOpenConnections,
                ERR_DB_UnableToOpenConnection,
                ERR_DB_ConnectionNotOpen,
                ERR_DB_ConnectionDropped,
                ERR_DB_QueryError,
                ERR_DB_InternalError,
#endif

#ifdef LANG_LIB_RS232
                ERR_RS232_ConfigurationNotSupported,
                ERR_RS232_UnableToOpenPort,
                ERR_RS232_PortNotOpen,
                ERR_RS232_WriteFailure,
                ERR_RS232_ReadFailure,
#endif
                
                ERR_NUM
            };
            
            static const std::string ErrorStrings[ERR_NUM + 1];
            
            ////
        
            using CallbackArgT = struct CallbackArg
            {
                const std::string Location;
                const std::string Message;
                
                INLINE CallbackArg() : Location(), Message() {};
                INLINE CallbackArg(const std::string &msg) : Location(), Message(msg) {};
                INLINE CallbackArg(const std::string &loc, const std::string &msg) : Location(loc), Message(msg) {};
                INLINE CallbackArg(const CallbackArg &arg) : Location(arg.Location), Message(arg.Message) {};
            };
        
            using CallbackT = std::shared_ptr< iAtomic >;
            using CallbackStackT = std::list< CallbackT >;
            using CallbackTableT = std::vector< CallbackStackT >;
            
            ////
        
        private:
            CallbackTableT mCallbackTable;
        
        protected:
            ErrorCallbacks();
            
            INLINE void push(const ErrTypeT &err, std::shared_ptr< iAtomic > exe) { mCallbackTable[err].push_back(exe); };
            
        public:
            
            void Push(const ErrTypeT &err, std::shared_ptr< iAtomic > exe);
            bool Invoke(const ErrTypeT &err, const CallbackArgT &arg, LanguageSymbolTable &symtab) const;
            void Pop(const ErrTypeT &err);
        
            static ErrorCallbacks &Instance();
        
    };

    ////////////////////////////////////////////////////////////////////////////

    extern std::shared_ptr< iAtomic > CreateErrorStructureType();
    
    extern std::shared_ptr< iAtomic > CreateErrorStructure(const ErrorCallbacks::CallbackArgT &err);

    ////////////////////////////////////////////////////////////////////////////

}

#endif

