/*
    This file is part of the DISH programming language, Copyright 2014, 2015,
    2016 by Chris Buck.
    
    DISH is free software: you can redistribute it and/or modify it provided
    
    
        (1) The following Copyright notice is displayed at runtime:
    
            DISH programming language copyright (c) 2014, 2015, 2016 by Chris Buck.
        
        (2) All source files duplicate this copyright statement in full.

    DISH is distributed in the hope that it will be useful, but WITHOUT ANY 
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS 
    FOR A PARTICULAR PURPOSE.
*/

#ifndef DISH_EXCEPTIONS_H
#define DISH_EXCEPTIONS_H

#include "dishconfig.h"

#include <cassert>
#include <cerrno>
#include <exception>
#include <iostream>
#include <string>

#include "inline.h"

namespace dish
{

    ////////////////////////////////////////////////////////////////////////////

    class DishException : public std::exception
    {
        private:
            std::string mMessage;
            bool mLocationSupplied;
    
        public:
            DishException();
            DishException(const std::string &msg);
            DishException(const std::string &loc, const std::string &msg);
            
            INLINE const bool &IsLocationSupplied() const throw() { return mLocationSupplied; };
            void AddLocation(const std::string &loc);
            
            //  From std::exception
            
            virtual const char *what() const throw();
        
    };
    
    class ParserException : public DishException
    {
        public:
            INLINE ParserException() : DishException() {};
            INLINE ParserException(const std::string &msg) : DishException(msg) {};
            INLINE ParserException(const std::string &loc, const std::string &msg) : DishException(loc, msg) {};
        
    };
    
    class RuntimeException : public DishException
    {
        public:
            INLINE RuntimeException() : DishException() {};
            INLINE RuntimeException(const std::string &msg) : DishException(msg) {};
            INLINE RuntimeException(const std::string &loc, const std::string &msg) : DishException(loc, msg) {};
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class UnknownRuntimeException : public RuntimeException
    {
        public:
            INLINE UnknownRuntimeException() : RuntimeException() {};
            INLINE UnknownRuntimeException(const std::string &msg) : RuntimeException(msg) {};
            INLINE UnknownRuntimeException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
            
    };
    
    class OperationNotSupportedException : public RuntimeException
    {
        public:
            INLINE OperationNotSupportedException() : RuntimeException() {};
            INLINE OperationNotSupportedException(const std::string &msg) : RuntimeException(msg) {};
            INLINE OperationNotSupportedException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
            
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class UnableToImportFileException : public ParserException
    {
        public:
            INLINE UnableToImportFileException() : ParserException() {};
            INLINE UnableToImportFileException(const std::string &msg) : ParserException(msg) {};
            INLINE UnableToImportFileException(const std::string &loc, const std::string &msg) : ParserException(loc, msg) {};
            
    };
    
    class IllegalInputException : public ParserException
    {
        public:
            INLINE IllegalInputException() : ParserException() {};
            INLINE IllegalInputException(const std::string &msg) : ParserException(msg) {};
            INLINE IllegalInputException(const std::string &loc, const std::string &msg) : ParserException(loc, msg) {};
            
    };
    
    class UnexpectedEndOfInputException : public ParserException
    {
        public:
            INLINE UnexpectedEndOfInputException() : ParserException() {};
            INLINE UnexpectedEndOfInputException(const std::string &msg) : ParserException(msg) {};
            INLINE UnexpectedEndOfInputException(const std::string &loc, const std::string &msg) : ParserException(loc, msg) {};
            
    };
    
    class SyntaxErrorException : public ParserException
    {
        public:
            INLINE SyntaxErrorException() : ParserException() {};
            INLINE SyntaxErrorException(const std::string &msg) : ParserException(msg) {};
            INLINE SyntaxErrorException(const std::string &loc, const std::string &msg) : ParserException(loc, msg) {};
            
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class IllegalCastException : public RuntimeException
    {
        public:
            INLINE IllegalCastException() : RuntimeException() {};
            INLINE IllegalCastException(const std::string &msg) : RuntimeException(msg) {};
            INLINE IllegalCastException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class ValueLockedException : public RuntimeException
    {
        public:
            INLINE ValueLockedException() : RuntimeException() {};
            INLINE ValueLockedException(const std::string &msg) : RuntimeException(msg) {};
            INLINE ValueLockedException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class IllegalValueException : public RuntimeException
    {
        public:
            INLINE IllegalValueException() : RuntimeException() {};
            INLINE IllegalValueException(const std::string &msg) : RuntimeException(msg) {};
            INLINE IllegalValueException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class ValueNotLeftHandSideException : public RuntimeException
    {
        public:
            INLINE ValueNotLeftHandSideException() : RuntimeException() {};
            INLINE ValueNotLeftHandSideException(const std::string &msg) : RuntimeException(msg) {};
            INLINE ValueNotLeftHandSideException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class NoSuchMemberException : public RuntimeException
    {
        public:
            INLINE NoSuchMemberException() : RuntimeException() {};
            INLINE NoSuchMemberException(const std::string &msg) : RuntimeException(msg) {};
            INLINE NoSuchMemberException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class IllegalIndexException : public RuntimeException
    {
        public:
            INLINE IllegalIndexException() : RuntimeException() {};
            INLINE IllegalIndexException(const std::string &msg) : RuntimeException(msg) {};
            INLINE IllegalIndexException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class IllegalParameterException : public RuntimeException
    {
        public:
            INLINE IllegalParameterException() : RuntimeException() {};
            INLINE IllegalParameterException(const std::string &msg) : RuntimeException(msg) {};
            INLINE IllegalParameterException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class IllegalTypeException : public RuntimeException
    {
        public:
            INLINE IllegalTypeException() : RuntimeException() {};
            INLINE IllegalTypeException(const std::string &msg) : RuntimeException(msg) {};
            INLINE IllegalTypeException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class IllegalOperationException : public RuntimeException
    {
        public:
            INLINE IllegalOperationException() : RuntimeException() {};
            INLINE IllegalOperationException(const std::string &msg) : RuntimeException(msg) {};
            INLINE IllegalOperationException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class NotExecutableException : public RuntimeException
    {
        public:
            INLINE NotExecutableException() : RuntimeException() {};
            INLINE NotExecutableException(const std::string &msg) : RuntimeException(msg) {};
            INLINE NotExecutableException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class DuplicateSymbolException : public RuntimeException
    {
        public:
            INLINE DuplicateSymbolException() : RuntimeException() {};
            INLINE DuplicateSymbolException(const std::string &msg) : RuntimeException(msg) {};
            INLINE DuplicateSymbolException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class NoSuchSymbolException : public RuntimeException
    {
        public:
            INLINE NoSuchSymbolException() : RuntimeException() {};
            INLINE NoSuchSymbolException(const std::string &msg) : RuntimeException(msg) {};
            INLINE NoSuchSymbolException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class DivideByZeroException : public RuntimeException
    {
        public:
            INLINE DivideByZeroException() : RuntimeException() {};
            INLINE DivideByZeroException(const std::string &msg) : RuntimeException(msg) {};
            INLINE DivideByZeroException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class DomainErrorException : public RuntimeException
    {
        public:
            INLINE DomainErrorException() : RuntimeException() {};
            INLINE DomainErrorException(const std::string &msg) : RuntimeException(msg) {};
            INLINE DomainErrorException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class RangeErrorException : public RuntimeException
    {
        public:
            INLINE RangeErrorException() : RuntimeException() {};
            INLINE RangeErrorException(const std::string &msg) : RuntimeException(msg) {};
            INLINE RangeErrorException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class NoSuchFileException : public RuntimeException
    {
        public:
            INLINE NoSuchFileException() : RuntimeException() {};
            INLINE NoSuchFileException(const std::string &msg) : RuntimeException(msg) {};
            INLINE NoSuchFileException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class NonLiteralExpressionException : public RuntimeException
    {
        public:
            INLINE NonLiteralExpressionException() : RuntimeException() {};
            INLINE NonLiteralExpressionException(const std::string &msg) : RuntimeException(msg) {};
            INLINE NonLiteralExpressionException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class IllegalFunctionCallException : public RuntimeException
    {
        public:
            INLINE IllegalFunctionCallException() : RuntimeException() {};
            INLINE IllegalFunctionCallException(const std::string &msg) : RuntimeException(msg) {};
            INLINE IllegalFunctionCallException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class CaseNotHandledException : public RuntimeException
    {
        public:
            INLINE CaseNotHandledException() : RuntimeException() {};
            INLINE CaseNotHandledException(const std::string &msg) : RuntimeException(msg) {};
            INLINE CaseNotHandledException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    //////////
    
    class IllegalHandleException : public RuntimeException
    {
        public:
            INLINE IllegalHandleException() : RuntimeException() {};
            INLINE IllegalHandleException(const std::string &msg) : RuntimeException(msg) {};
            INLINE IllegalHandleException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class TooManyOpenFilesException : public RuntimeException
    {
        public:
            INLINE TooManyOpenFilesException() : RuntimeException() {};
            INLINE TooManyOpenFilesException(const std::string &msg) : RuntimeException(msg) {};
            INLINE TooManyOpenFilesException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class UnableToOpenFileException : public RuntimeException
    {
        public:
            INLINE UnableToOpenFileException() : RuntimeException() {};
            INLINE UnableToOpenFileException(const std::string &msg) : RuntimeException(msg) {};
            INLINE UnableToOpenFileException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class FileNotOpenException : public RuntimeException
    {
        public:
            INLINE FileNotOpenException() : RuntimeException() {};
            INLINE FileNotOpenException(const std::string &msg) : RuntimeException(msg) {};
            INLINE FileNotOpenException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class FileWriteErrorException : public RuntimeException
    {
        public:
            INLINE FileWriteErrorException() : RuntimeException() {};
            INLINE FileWriteErrorException(const std::string &msg) : RuntimeException(msg) {};
            INLINE FileWriteErrorException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class FileReadErrorException : public RuntimeException
    {
        public:
            INLINE FileReadErrorException() : RuntimeException() {};
            INLINE FileReadErrorException(const std::string &msg) : RuntimeException(msg) {};
            INLINE FileReadErrorException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class FileReadEndOfFileException : public RuntimeException
    {
        public:
            INLINE FileReadEndOfFileException() : RuntimeException() {};
            INLINE FileReadEndOfFileException(const std::string &msg) : RuntimeException(msg) {};
            INLINE FileReadEndOfFileException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    //////////
    
    class TooManyOpenSocketsException : public RuntimeException
    {
        public:
            TooManyOpenSocketsException() : RuntimeException() {};
            TooManyOpenSocketsException(const std::string &msg) : RuntimeException(msg) {};
            TooManyOpenSocketsException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class UnableToOpenSocketException : public RuntimeException
    {
        public:
            INLINE UnableToOpenSocketException() : RuntimeException() {};
            INLINE UnableToOpenSocketException(const std::string &msg) : RuntimeException(msg) {};
            INLINE UnableToOpenSocketException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class UnableToCloseSocketException : public RuntimeException
    {
        public:
            INLINE UnableToCloseSocketException() : RuntimeException() {};
            INLINE UnableToCloseSocketException(const std::string &msg) : RuntimeException(msg) {};
            INLINE UnableToCloseSocketException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class SocketInvalidAddressException : public RuntimeException
    {
        public:
            INLINE SocketInvalidAddressException() : RuntimeException() {};
            INLINE SocketInvalidAddressException(const std::string &msg) : RuntimeException(msg) {};
            INLINE SocketInvalidAddressException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class SocketUnableToConnectToServerException : public RuntimeException
    {
        public:
            INLINE SocketUnableToConnectToServerException() : RuntimeException() {};
            INLINE SocketUnableToConnectToServerException(const std::string &msg) : RuntimeException(msg) {};
            INLINE SocketUnableToConnectToServerException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class SocketNotOpenException : public RuntimeException
    {
        public:
            INLINE SocketNotOpenException() : RuntimeException() {};
            INLINE SocketNotOpenException(const std::string &msg) : RuntimeException(msg) {};
            INLINE SocketNotOpenException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class SocketWriteErrorException : public RuntimeException
    {
        public:
            INLINE SocketWriteErrorException() : RuntimeException() {};
            INLINE SocketWriteErrorException(const std::string &msg) : RuntimeException(msg) {};
            INLINE SocketWriteErrorException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class SocketReadErrorException : public RuntimeException
    {
        public:
            INLINE SocketReadErrorException() : RuntimeException() {};
            INLINE SocketReadErrorException(const std::string &msg) : RuntimeException(msg) {};
            INLINE SocketReadErrorException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class MatrixNotValidException : public RuntimeException
    {
        public:
            INLINE MatrixNotValidException() : RuntimeException() {};
            INLINE MatrixNotValidException(const std::string &msg) : RuntimeException(msg) {};
            INLINE MatrixNotValidException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class MatrixNotSquareException : public RuntimeException
    {
        public:
            INLINE MatrixNotSquareException() : RuntimeException() {};
            INLINE MatrixNotSquareException(const std::string &msg) : RuntimeException(msg) {};
            INLINE MatrixNotSquareException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class ZeroDeterminantException : public RuntimeException
    {
        public:
            INLINE ZeroDeterminantException() : RuntimeException() {};
            INLINE ZeroDeterminantException(const std::string &msg) : RuntimeException(msg) {};
            INLINE ZeroDeterminantException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class MatrixDimensionErrorException : public RuntimeException
    {
        public:
            INLINE MatrixDimensionErrorException() : RuntimeException() {};
            INLINE MatrixDimensionErrorException(const std::string &msg) : RuntimeException(msg) {};
            INLINE MatrixDimensionErrorException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class TerminateExecutionException : public RuntimeException
    {
        public:
            INLINE TerminateExecutionException() : RuntimeException() {};
            INLINE TerminateExecutionException(const std::string &msg) : RuntimeException(msg) {};
            INLINE TerminateExecutionException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class FailedAssertionException : public RuntimeException
    {
        public:
            INLINE FailedAssertionException() : RuntimeException() {};
            INLINE FailedAssertionException(const std::string &msg) : RuntimeException(msg) {};
            INLINE FailedAssertionException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class StackOverflowException : public RuntimeException
    {
        public:
            INLINE StackOverflowException() : RuntimeException() {};
            INLINE StackOverflowException(const std::string &msg) : RuntimeException(msg) {};
            INLINE StackOverflowException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class DatabaseInternalErrorException : public RuntimeException
    {
        public:
            INLINE DatabaseInternalErrorException() : RuntimeException() {};
            INLINE DatabaseInternalErrorException(const std::string &msg) : RuntimeException(msg) {};
            INLINE DatabaseInternalErrorException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class DatabaseFeatureNotSupportedException : public RuntimeException
    {
        public:
            INLINE DatabaseFeatureNotSupportedException() : RuntimeException() {};
            INLINE DatabaseFeatureNotSupportedException(const std::string &msg) : RuntimeException(msg) {};
            INLINE DatabaseFeatureNotSupportedException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class DatabaseInvalidConnectionTypeException : public RuntimeException
    {
        public:
            INLINE DatabaseInvalidConnectionTypeException() : RuntimeException() {};
            INLINE DatabaseInvalidConnectionTypeException(const std::string &msg) : RuntimeException(msg) {};
            INLINE DatabaseInvalidConnectionTypeException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class DatabaseInvalidHandleException : public RuntimeException
    {
        public:
            INLINE DatabaseInvalidHandleException() : RuntimeException() {};
            INLINE DatabaseInvalidHandleException(const std::string &msg) : RuntimeException(msg) {};
            INLINE DatabaseInvalidHandleException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class DatabaseTooManyOpenConnectionsException : public RuntimeException
    {
        public:
            INLINE DatabaseTooManyOpenConnectionsException() : RuntimeException() {};
            INLINE DatabaseTooManyOpenConnectionsException(const std::string &msg) : RuntimeException(msg) {};
            INLINE DatabaseTooManyOpenConnectionsException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class DatabaseUnableToOpenConnectionException : public RuntimeException
    {
        public:
            INLINE DatabaseUnableToOpenConnectionException() : RuntimeException() {};
            INLINE DatabaseUnableToOpenConnectionException(const std::string &msg) : RuntimeException(msg) {};
            INLINE DatabaseUnableToOpenConnectionException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class DatabaseConnectionNotOpenException : public RuntimeException
    {
        public:
            INLINE DatabaseConnectionNotOpenException() : RuntimeException() {};
            INLINE DatabaseConnectionNotOpenException(const std::string &msg) : RuntimeException(msg) {};
            INLINE DatabaseConnectionNotOpenException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class DatabaseConnectionAlreadyOpenException : public RuntimeException
    {
        public:
            INLINE DatabaseConnectionAlreadyOpenException() : RuntimeException() {};
            INLINE DatabaseConnectionAlreadyOpenException(const std::string &msg) : RuntimeException(msg) {};
            INLINE DatabaseConnectionAlreadyOpenException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class DatabaseConnectionDroppedException : public RuntimeException
    {
        public:
            INLINE DatabaseConnectionDroppedException() : RuntimeException() {};
            INLINE DatabaseConnectionDroppedException(const std::string &msg) : RuntimeException(msg) {};
            INLINE DatabaseConnectionDroppedException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class DatabaseQueryErrorException : public RuntimeException
    {
        public:
            INLINE DatabaseQueryErrorException() : RuntimeException() {};
            INLINE DatabaseQueryErrorException(const std::string &msg) : RuntimeException(msg) {};
            INLINE DatabaseQueryErrorException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    
    
    class DatabaseUnknownException : public RuntimeException
    {
        public:
            INLINE DatabaseUnknownException() : RuntimeException() {};
            INLINE DatabaseUnknownException(const std::string &msg) : RuntimeException(msg) {};
            INLINE DatabaseUnknownException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class TooManyOpenHandlesException : public RuntimeException
    {
        public:
            INLINE TooManyOpenHandlesException() : RuntimeException() {};
            INLINE TooManyOpenHandlesException(const std::string &msg) : RuntimeException(msg) {};
            INLINE TooManyOpenHandlesException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class InvalidHandleException : public RuntimeException
    {
        public:
            INLINE InvalidHandleException() : RuntimeException() {};
            INLINE InvalidHandleException(const std::string &msg) : RuntimeException(msg) {};
            INLINE InvalidHandleException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class Rs232BadConfigurationException : public RuntimeException
    {
        public:
            INLINE Rs232BadConfigurationException() : RuntimeException() {};
            INLINE Rs232BadConfigurationException(const std::string &msg) : RuntimeException(msg) {};
            INLINE Rs232BadConfigurationException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class Rs232UnableToOpenPortException : public RuntimeException
    {
        public:
            INLINE Rs232UnableToOpenPortException() : RuntimeException() {};
            INLINE Rs232UnableToOpenPortException(const std::string &msg) : RuntimeException(msg) {};
            INLINE Rs232UnableToOpenPortException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class Rs232PortNotOpenException : public RuntimeException
    {
        public:
            INLINE Rs232PortNotOpenException() : RuntimeException() {};
            INLINE Rs232PortNotOpenException(const std::string &msg) : RuntimeException(msg) {};
            INLINE Rs232PortNotOpenException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class Rs232WriteFailureException : public RuntimeException
    {
        public:
            INLINE Rs232WriteFailureException() : RuntimeException() {};
            INLINE Rs232WriteFailureException(const std::string &msg) : RuntimeException(msg) {};
            INLINE Rs232WriteFailureException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };
    
    class Rs232ReadFailureException : public RuntimeException
    {
        public:
            INLINE Rs232ReadFailureException() : RuntimeException() {};
            INLINE Rs232ReadFailureException(const std::string &msg) : RuntimeException(msg) {};
            INLINE Rs232ReadFailureException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class GraphicsFailureException : public RuntimeException
    {
        public:
            INLINE GraphicsFailureException() : RuntimeException() {};
            INLINE GraphicsFailureException(const std::string &msg) : RuntimeException(msg) {};
            INLINE GraphicsFailureException(const std::string &loc, const std::string &msg) : RuntimeException(loc, msg) {};
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    extern void CheckForError(const int errcode);
    INLINEC void CheckForError() { const int errcode(errno); errno = 0; CheckForError(errcode); };
    
    class ScopedCheckForError
    {
        public:
            INLINE ScopedCheckForError() { errno = 0; };
            INLINE ~ScopedCheckForError() { CheckForError(); };
            
    };

    ////////////////////////////////////////////////////////////////////////////

}

#endif

