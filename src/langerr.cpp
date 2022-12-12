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

#include <cassert>
#include <iostream>
#include <sstream>

#include "atomics.h"
#include "db.h"
#include "exception.h"
#include "langerr.h"
#include "langfile.h"
#include "langnet.h"
#include "langregex.h"
#include "langrs232.h"
#include "language.h"

namespace
{

    ////////////////////////////////////////////////////////////////////////////

    class ErrNullCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE ErrNullCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< ErrNullCallackFunction > MakeValue() { return std::shared_ptr< ErrNullCallackFunction >(new ErrNullCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > ErrNullCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::UnknownRuntimeException(
            getParam(symtab, "err")->Member("Message")->AsString() + " : NULL Error callback."
        );
    }

    ////////////////////////////////////////////////////////////////////////////

    class OkCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE OkCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
    
        public:
            
            static INLINE std::shared_ptr< OkCallackFunction > MakeValue() { return std::shared_ptr< OkCallackFunction >(new OkCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > OkCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
#ifdef LANG_LIB_FILEIO
        //  Close all open files.
        dish::FileList::Instance().Close();
#endif
      
#ifdef LANG_LIB_NETWORK  
        //  Close all open sockets.
        dish::SocketList::Instance().Close();
#endif
        
#ifdef LANG_LIB_DATABASE
        //  Close all open database connections.
        dish::DbConnectionFactory::Instance().CloseAllConnections();
#endif

#ifdef LANG_LIB_REGULAR_EXPRESSION
        //  Destroy all open regular-expressions.
        dish::RegExDestroyAllHandles();
#endif

#ifdef LANG_LIB_RS232
        //  Destroy all open RS-232 ports.
        dish::Rs232DestroyAllHandles();
#endif
        
        //  ...
    
        return dish::BooleanValue::MakeLockedValue(true);
    }

    ////////////////////////////////////////////////////////////////////////////

    class TerminateCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE TerminateCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< TerminateCallackFunction > MakeValue() { return std::shared_ptr< TerminateCallackFunction >(new TerminateCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > TerminateCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        return dish::BooleanValue::MakeLockedValue(true);
    }

    ////////////////////////////////////////////////////////////////////////////

    class IllegalCastCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE IllegalCastCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< IllegalCastCallackFunction > MakeValue() { return std::shared_ptr< IllegalCastCallackFunction >(new IllegalCastCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > IllegalCastCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::IllegalCastException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class ValueLockedCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE ValueLockedCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
        
        public:
            
            static INLINE std::shared_ptr< ValueLockedCallackFunction > MakeValue() { return std::shared_ptr< ValueLockedCallackFunction >(new ValueLockedCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > ValueLockedCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::ValueLockedException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class NoSuchMemberCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE NoSuchMemberCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< NoSuchMemberCallackFunction > MakeValue() { return std::shared_ptr< NoSuchMemberCallackFunction >(new NoSuchMemberCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > NoSuchMemberCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::NoSuchMemberException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class DuplicateSymbolCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE DuplicateSymbolCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< DuplicateSymbolCallackFunction > MakeValue() { return std::shared_ptr< DuplicateSymbolCallackFunction >(new DuplicateSymbolCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > DuplicateSymbolCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::DuplicateSymbolException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class NoSuchSymbolCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE NoSuchSymbolCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< NoSuchSymbolCallackFunction > MakeValue() { return std::shared_ptr< NoSuchSymbolCallackFunction >(new NoSuchSymbolCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > NoSuchSymbolCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::NoSuchSymbolException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class DivideByZeroCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE DivideByZeroCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< DivideByZeroCallackFunction > MakeValue() { return std::shared_ptr< DivideByZeroCallackFunction >(new DivideByZeroCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > DivideByZeroCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::DivideByZeroException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class DomainErrorCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE DomainErrorCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< DomainErrorCallackFunction > MakeValue() { return std::shared_ptr< DomainErrorCallackFunction >(new DomainErrorCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > DomainErrorCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::DomainErrorException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class RangeErrorCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE RangeErrorCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< RangeErrorCallackFunction > MakeValue() { return std::shared_ptr< RangeErrorCallackFunction >(new RangeErrorCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > RangeErrorCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::RangeErrorException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class IllegalHandleCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE IllegalHandleCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< IllegalHandleCallackFunction > MakeValue() { return std::shared_ptr< IllegalHandleCallackFunction >(new IllegalHandleCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > IllegalHandleCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::IllegalHandleException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class IllegalValueCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE IllegalValueCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< IllegalValueCallackFunction > MakeValue() { return std::shared_ptr< IllegalValueCallackFunction >(new IllegalValueCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > IllegalValueCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        //  !!!
        std::cout << std::endl << "THERE!" << std::endl;
    
        throw dish::IllegalValueException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

#ifdef LANG_LIB_FILEIO

    ////////////////////////////////////////////////////////////////////////////

    class TooManyOpenFilesCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE TooManyOpenFilesCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< TooManyOpenFilesCallackFunction > MakeValue() { return std::shared_ptr< TooManyOpenFilesCallackFunction >(new TooManyOpenFilesCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > TooManyOpenFilesCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::TooManyOpenFilesException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class UnableToOpenFileCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE UnableToOpenFileCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< UnableToOpenFileCallackFunction > MakeValue() { return std::shared_ptr< UnableToOpenFileCallackFunction >(new UnableToOpenFileCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > UnableToOpenFileCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::UnableToOpenFileException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class FileNotOpenCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE FileNotOpenCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< FileNotOpenCallackFunction > MakeValue() { return std::shared_ptr< FileNotOpenCallackFunction >(new FileNotOpenCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > FileNotOpenCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::FileNotOpenException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class FileWriteErrorCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE FileWriteErrorCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< FileWriteErrorCallackFunction > MakeValue() { return std::shared_ptr< FileWriteErrorCallackFunction >(new FileWriteErrorCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > FileWriteErrorCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::FileWriteErrorException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class FileReadErrorCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE FileReadErrorCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< FileReadErrorCallackFunction > MakeValue() { return std::shared_ptr< FileReadErrorCallackFunction >(new FileReadErrorCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > FileReadErrorCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::FileReadErrorException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////
    
#endif

#ifdef LANG_LIB_NETWORK

    ////////////////////////////////////////////////////////////////////////////

    class TooManyOpenSocketsCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE TooManyOpenSocketsCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< TooManyOpenSocketsCallackFunction > MakeValue() { return std::shared_ptr< TooManyOpenSocketsCallackFunction >(new TooManyOpenSocketsCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > TooManyOpenSocketsCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::TooManyOpenSocketsException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class UnableToOpenSocketCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE UnableToOpenSocketCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< UnableToOpenSocketCallackFunction > MakeValue() { return std::shared_ptr< UnableToOpenSocketCallackFunction >(new UnableToOpenSocketCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > UnableToOpenSocketCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::UnableToOpenSocketException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class UnableToCloseSocketCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE UnableToCloseSocketCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
        
        public:
            
            static INLINE std::shared_ptr< UnableToCloseSocketCallackFunction > MakeValue() { return std::shared_ptr< UnableToCloseSocketCallackFunction >(new UnableToCloseSocketCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > UnableToCloseSocketCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::UnableToCloseSocketException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class NetworkInvalidAddressCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE NetworkInvalidAddressCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< NetworkInvalidAddressCallackFunction > MakeValue() { return std::shared_ptr< NetworkInvalidAddressCallackFunction >(new NetworkInvalidAddressCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > NetworkInvalidAddressCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::SocketInvalidAddressException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class NetworkUnableToConnectToServerCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE NetworkUnableToConnectToServerCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< NetworkUnableToConnectToServerCallackFunction > MakeValue() { return std::shared_ptr< NetworkUnableToConnectToServerCallackFunction >(new NetworkUnableToConnectToServerCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > NetworkUnableToConnectToServerCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::SocketUnableToConnectToServerException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class NetworkSocketNotOpenCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE NetworkSocketNotOpenCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< NetworkSocketNotOpenCallackFunction > MakeValue() { return std::shared_ptr< NetworkSocketNotOpenCallackFunction >(new NetworkSocketNotOpenCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > NetworkSocketNotOpenCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::SocketNotOpenException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class NetworkSocketWriteErrorCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE NetworkSocketWriteErrorCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< NetworkSocketWriteErrorCallackFunction > MakeValue() { return std::shared_ptr< NetworkSocketWriteErrorCallackFunction >(new NetworkSocketWriteErrorCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > NetworkSocketWriteErrorCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::SocketWriteErrorException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class NetworkSocketReadErrorCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE NetworkSocketReadErrorCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< NetworkSocketReadErrorCallackFunction > MakeValue() { return std::shared_ptr< NetworkSocketReadErrorCallackFunction >(new NetworkSocketReadErrorCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > NetworkSocketReadErrorCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::SocketReadErrorException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

#endif

#ifdef LANG_LIB_MATH_MATRIX

    ////////////////////////////////////////////////////////////////////////////

    class MatrixInvalidCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE MatrixInvalidCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< MatrixInvalidCallackFunction > MakeValue() { return std::shared_ptr< MatrixInvalidCallackFunction >(new MatrixInvalidCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > MatrixInvalidCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::MatrixNotValidException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class MatrixNotSquareCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE MatrixNotSquareCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< MatrixNotSquareCallackFunction > MakeValue() { return std::shared_ptr< MatrixNotSquareCallackFunction >(new MatrixNotSquareCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > MatrixNotSquareCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::MatrixNotSquareException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class ZeroDeterminantCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE ZeroDeterminantCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< ZeroDeterminantCallackFunction > MakeValue() { return std::shared_ptr< ZeroDeterminantCallackFunction >(new ZeroDeterminantCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > ZeroDeterminantCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::ZeroDeterminantException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class MatrixDimensionErrorCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE MatrixDimensionErrorCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< MatrixDimensionErrorCallackFunction > MakeValue() { return std::shared_ptr< MatrixDimensionErrorCallackFunction >(new MatrixDimensionErrorCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > MatrixDimensionErrorCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::MatrixDimensionErrorException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////
    
#endif

    ////////////////////////////////////////////////////////////////////////////

    class StackOverflowCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE StackOverflowCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< StackOverflowCallackFunction > MakeValue() { return std::shared_ptr< StackOverflowCallackFunction >(new StackOverflowCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > StackOverflowCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::StackOverflowException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

#ifdef LANG_LIB_DATABASE

    ////////////////////////////////////////////////////////////////////////////

    class DbInvalidConnectionTypeCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE DbInvalidConnectionTypeCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< DbInvalidConnectionTypeCallackFunction > MakeValue() { return std::shared_ptr< DbInvalidConnectionTypeCallackFunction >(new DbInvalidConnectionTypeCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > DbInvalidConnectionTypeCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::DatabaseInvalidConnectionTypeException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class DbTooManyOpenConnectionsCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE DbTooManyOpenConnectionsCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< DbTooManyOpenConnectionsCallackFunction > MakeValue() { return std::shared_ptr< DbTooManyOpenConnectionsCallackFunction >(new DbTooManyOpenConnectionsCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > DbTooManyOpenConnectionsCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::DatabaseTooManyOpenConnectionsException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class DbUnableToOpenConnectionCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE DbUnableToOpenConnectionCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< DbUnableToOpenConnectionCallackFunction > MakeValue() { return std::shared_ptr< DbUnableToOpenConnectionCallackFunction >(new DbUnableToOpenConnectionCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > DbUnableToOpenConnectionCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::DatabaseUnableToOpenConnectionException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class DbConnectionNotOpenCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE DbConnectionNotOpenCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< DbConnectionNotOpenCallackFunction > MakeValue() { return std::shared_ptr< DbConnectionNotOpenCallackFunction >(new DbConnectionNotOpenCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > DbConnectionNotOpenCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::DatabaseConnectionNotOpenException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class DbConnectionDroppedCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE DbConnectionDroppedCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< DbConnectionDroppedCallackFunction > MakeValue() { return std::shared_ptr< DbConnectionDroppedCallackFunction >(new DbConnectionDroppedCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > DbConnectionDroppedCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::DatabaseConnectionDroppedException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class DbQueryErrorCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE DbQueryErrorCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< DbQueryErrorCallackFunction > MakeValue() { return std::shared_ptr< DbQueryErrorCallackFunction >(new DbQueryErrorCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > DbQueryErrorCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::DatabaseQueryErrorException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class DbInternalErrorCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE DbInternalErrorCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< DbInternalErrorCallackFunction > MakeValue() { return std::shared_ptr< DbInternalErrorCallackFunction >(new DbInternalErrorCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > DbInternalErrorCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::DatabaseQueryErrorException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

#endif

#ifdef LANG_LIB_RS232

    ////////////////////////////////////////////////////////////////////////////

    class Rs232ConfigurationNotSupportedCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE Rs232ConfigurationNotSupportedCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< Rs232ConfigurationNotSupportedCallackFunction > MakeValue() { return std::shared_ptr< Rs232ConfigurationNotSupportedCallackFunction >(new Rs232ConfigurationNotSupportedCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > Rs232ConfigurationNotSupportedCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::Rs232BadConfigurationException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class Rs232UnableOpenPortCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE Rs232UnableOpenPortCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< Rs232UnableOpenPortCallackFunction > MakeValue() { return std::shared_ptr< Rs232UnableOpenPortCallackFunction >(new Rs232UnableOpenPortCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > Rs232UnableOpenPortCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::Rs232UnableToOpenPortException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class Rs232PortNotOpenCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE Rs232PortNotOpenCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< Rs232PortNotOpenCallackFunction > MakeValue() { return std::shared_ptr< Rs232PortNotOpenCallackFunction >(new Rs232PortNotOpenCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > Rs232PortNotOpenCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::Rs232PortNotOpenException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class Rs232WriteFailureCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE Rs232WriteFailureCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< Rs232WriteFailureCallackFunction > MakeValue() { return std::shared_ptr< Rs232WriteFailureCallackFunction >(new Rs232WriteFailureCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > Rs232WriteFailureCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::Rs232WriteFailureException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

    class Rs232ReadFailureCallackFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE Rs232ReadFailureCallackFunction() : dish::ExecutableAtomic() { addParam("err", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< Rs232ReadFailureCallackFunction > MakeValue() { return std::shared_ptr< Rs232ReadFailureCallackFunction >(new Rs232ReadFailureCallackFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };
    
    std::shared_ptr< dish::iAtomic > Rs232ReadFailureCallackFunction::Execute(dish::LanguageSymbolTable &symtab) const
    {
        throw dish::Rs232ReadFailureException(getParam(symtab, "err")->Member("Message")->AsString());
    }

    ////////////////////////////////////////////////////////////////////////////

#endif

}

/******************************************************************************

    dish::ErrorCallbacks class definitions

 ******************************************************************************/
 
const std::string dish::ErrorCallbacks::ErrorStrings[dish::ErrorCallbacks::ERR_NUM + 1] =
{
    "ERR_Null",
    "ERR_Terminate",
    "ERR_IllegalCast",
    "ERR_ValueLocked",
    "ERR_NoSuchMember",
    "ERR_DuplicateSymbol",
    "ERR_NoSuchSymbol",
    "ERR_DivideByZero",
    "ERR_DomainError",
    "ERR_RangeError",
    
    "ERR_IllegalHandle",
    "ERR_IllegalValue",
    
    "ERR_StackOverflowError",
                
#ifdef LANG_LIB_FILEIO
    "ERR_TooManyOpenFiles",
    "ERR_UnableToOpenFile",
    "ERR_FileNotOpen",
    "ERR_FileWriteError",
    "ERR_FileReadError",
    "ERR_FileReadEndOfFile",
#endif
                
#ifdef LANG_LIB_NETWORK
    "ERR_TooManyOpenSockets",
    "ERR_UnableToOpenSocket",
    "ERR_UnableToCloseSocket",
    "ERR_NetworkInvalidAddress",
    "ERR_NetworkUnableToConnectToServer",
    "ERR_NetworkSocketNotOpen",
    "ERR_NetworkSocketWriteError",
    "ERR_NetworkSocketReadError",
#endif
                
#ifdef LANG_LIB_MATH_MATRIX
    "ERR_MatrixInvalidError",
    "ERR_MatrixNotSquareError",
    "ERR_ZeroDeterminantError",
    "ERR_MatrixDimensionError",
#endif
            
#ifdef LANG_LIB_DATABASE
    "ERR_DB_InvalidConnectionType",
    "ERR_DB_TooManyOpenConnections",
    "ERR_DB_UnableToOpenConnection",
    "ERR_DB_ConnectionNotOpen",
    "ERR_DB_ConnectionDropped",
    "ERR_DB_QueryError",
    "ERR_DB_InternalError",
#endif

#ifdef LANG_LIB_RS232
    "ERR_RS232_ConfigurationNotSupported",
    "ERR_RS232_UnableToOpenPort",
    "ERR_RS232_PortNotOpen",
    "ERR_RS232_WriteFailure",
    "ERR_RS232_ReadFailure",
#endif

    "ERR_NUM"
};
    
dish::ErrorCallbacks::ErrorCallbacks() : mCallbackTable(dish::ErrorCallbacks::ERR_NUM)
{
    push(ERR_Null, ErrNullCallackFunction::MakeValue());

    push(ERR_Ok, OkCallackFunction::MakeValue());
    push(ERR_Terminate, TerminateCallackFunction::MakeValue());
    
    push(ERR_IllegalCast, IllegalCastCallackFunction::MakeValue());
    push(ERR_ValueLocked, ValueLockedCallackFunction::MakeValue());
    push(ERR_NoSuchMember, NoSuchMemberCallackFunction::MakeValue());
    push(ERR_DuplicateSymbol, DuplicateSymbolCallackFunction::MakeValue());
    push(ERR_NoSuchSymbol, NoSuchSymbolCallackFunction::MakeValue());
    push(ERR_DivideByZero, DivideByZeroCallackFunction::MakeValue());
    push(ERR_DomainError, DomainErrorCallackFunction::MakeValue());
    push(ERR_RangeError, RangeErrorCallackFunction::MakeValue());
    
    push(ERR_IllegalHandle, IllegalHandleCallackFunction::MakeValue());
    push(ERR_IllegalValue, IllegalValueCallackFunction::MakeValue());
    
    push(ERR_StackOverflowError, StackOverflowCallackFunction::MakeValue());
    
#ifdef LANG_LIB_FILEIO
    push(ERR_TooManyOpenFiles, TooManyOpenFilesCallackFunction::MakeValue());
    push(ERR_UnableToOpenFile, UnableToOpenFileCallackFunction::MakeValue());
    push(ERR_FileNotOpen, FileNotOpenCallackFunction::MakeValue());
    push(ERR_FileWriteError, FileWriteErrorCallackFunction::MakeValue());
    push(ERR_FileReadError, FileReadErrorCallackFunction::MakeValue());
#endif
    
#ifdef LANG_LIB_NETWORK
    push(ERR_TooManyOpenSockets, TooManyOpenSocketsCallackFunction::MakeValue());
    push(ERR_UnableToOpenSocket, UnableToOpenSocketCallackFunction::MakeValue());
    push(ERR_UnableToCloseSocket, UnableToCloseSocketCallackFunction::MakeValue());
    push(ERR_NetworkInvalidAddress, NetworkInvalidAddressCallackFunction::MakeValue());
    push(ERR_NetworkUnableToConnectToServer, NetworkUnableToConnectToServerCallackFunction::MakeValue());
    push(ERR_NetworkSocketNotOpen, NetworkSocketNotOpenCallackFunction::MakeValue());
    push(ERR_NetworkSocketWriteError, NetworkSocketWriteErrorCallackFunction::MakeValue());
    push(ERR_NetworkSocketReadError, NetworkSocketReadErrorCallackFunction::MakeValue());
#endif
    
#ifdef LANG_LIB_MATH_MATRIX
    push(ERR_MatrixInvalidError, MatrixInvalidCallackFunction::MakeValue());
    push(ERR_MatrixNotSquareError, MatrixNotSquareCallackFunction::MakeValue());
    push(ERR_ZeroDeterminantError, ZeroDeterminantCallackFunction::MakeValue());
    push(ERR_MatrixDimensionError, MatrixDimensionErrorCallackFunction::MakeValue());
#endif
    
#ifdef LANG_LIB_DATABASE
    push(ERR_DB_InvalidConnectionType, DbInvalidConnectionTypeCallackFunction::MakeValue());
    push(ERR_DB_TooManyOpenConnections, DbInvalidConnectionTypeCallackFunction::MakeValue());
    push(ERR_DB_UnableToOpenConnection, DbInvalidConnectionTypeCallackFunction::MakeValue());
    push(ERR_DB_ConnectionNotOpen, DbInvalidConnectionTypeCallackFunction::MakeValue());
    push(ERR_DB_ConnectionDropped, DbInvalidConnectionTypeCallackFunction::MakeValue());
    push(ERR_DB_QueryError, DbInvalidConnectionTypeCallackFunction::MakeValue());
    push(ERR_DB_InternalError, DbInternalErrorCallackFunction::MakeValue());
#endif
    
#ifdef LANG_LIB_RS232
    push(ERR_RS232_ConfigurationNotSupported, Rs232ConfigurationNotSupportedCallackFunction::MakeValue());
    push(ERR_RS232_UnableToOpenPort, Rs232UnableOpenPortCallackFunction::MakeValue());
    push(ERR_RS232_PortNotOpen, Rs232PortNotOpenCallackFunction::MakeValue());
    push(ERR_RS232_WriteFailure, Rs232WriteFailureCallackFunction::MakeValue());
    push(ERR_RS232_ReadFailure, Rs232ReadFailureCallackFunction::MakeValue());
#endif
}

void dish::ErrorCallbacks::Push(const dish::ErrorCallbacks::ErrTypeT &err, std::shared_ptr< dish::iAtomic > exe)
{
    assert(0 != exe.get());
    
    if((err >= 0) && (err < ERR_NUM))
    {
        push(err, exe);
    }
    else
    {
        std::stringstream message;
        message << "The specified index, ";
        message << err;
        message << ", is not a valid error callback index in the range [0, ";
        message << ERR_NUM;
        message << ").";
        
        throw IllegalIndexException(message.str());
    }
}

bool dish::ErrorCallbacks::Invoke(const dish::ErrorCallbacks::ErrTypeT &err, const dish::ErrorCallbacks::CallbackArgT &arg, dish::LanguageSymbolTable &symtab) const
{
    if((err >= 0) && (err < ERR_NUM))
    {
        ScopedScope scope(symtab);
        
        symtab.Insert("err", CreateErrorStructure(arg));
        
        for(CallbackStackT::const_reverse_iterator i(mCallbackTable[err].rbegin()), last_i(mCallbackTable[err].rend()); i != last_i; ++i)
        {
            try
            {
                if(!(*i)->Execute(symtab)->AsBoolean())
                {
                    return false;
                }
            }
            catch(dish::iExecutableAtomic::ReturnValue e)
            {
                if(!e.Value()->AsBoolean())
                {
                    return false;
                }
            }
        }
        
        return true;
    }
    
    std::stringstream message;
    message << "The specified index, ";
    message << err;
    message << ", is not a valid error callback index in the range [0, ";
    message << ERR_NUM;
    message << ").";
    
    throw IllegalIndexException(message.str());
}

void dish::ErrorCallbacks::Pop(const dish::ErrorCallbacks::ErrTypeT &err)
{
    if((err >= 0) && (err < ERR_NUM))
    {
        if(!mCallbackTable[err].empty())
        {
            mCallbackTable[err].pop_back();
        }
    }
    else
    {
        std::stringstream message;
        message << "The specified index, ";
        message << err;
        message << ", is not a valid error callback index in the range [0, ";
        message << ERR_NUM;
        message << ").";
    
        throw IllegalIndexException(message.str());
    }
}
    
dish::ErrorCallbacks &dish::ErrorCallbacks::Instance()
{
    static ErrorCallbacks instance;
    
    return instance;
}

/******************************************************************************

    Function definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::CreateErrorStructureType()
{
    static std::shared_ptr< StructureTypeAtomic > structure;
    
    if(0 == structure.get())
    {
        std::shared_ptr< StringTypeAtomic > string_type(StringTypeAtomic::MakeValue());
    
        structure = StructureTypeAtomic::MakeValue();
        structure->Add("Location", string_type);
        structure->Add("Message", string_type);
    }

    return structure;
}

std::shared_ptr< dish::iAtomic > dish::CreateErrorStructure(const dish::ErrorCallbacks::CallbackArgT &err)
{
    std::shared_ptr< iAtomic > error(CreateErrorStructureType()->Declare());
    error->Member("Location")->Assign(err.Location);
    error->Member("Message")->Assign(err.Message);
    
    return error; 
}

