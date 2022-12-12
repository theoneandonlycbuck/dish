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

#include <cassert>
#include <sstream>
#include <system_error>

#include "exception.h"

////////////////////////////////////////////////////////////////////////////////
//

//#define CHECK_ALL_ERRORS

//
////////////////////////////////////////////////////////////////////////////////

/******************************************************************************

    dish::DishException class definitions

 ******************************************************************************/
 
dish::DishException::DishException() : std::exception(), 
    mMessage(), 
    mLocationSupplied(false)
{
#ifdef TRACE
    std::cout << "throwing DishException..." << std::endl;
#endif             
}

dish::DishException::DishException(const std::string &msg) : std::exception(), 
    mMessage(msg), 
    mLocationSupplied(false)
{
#ifdef TRACE
    std::cout << "throwing \"" << mMessage << "\"" << std::endl;
#endif             
}

dish::DishException::DishException(const std::string &loc, const std::string &msg) : std::exception(), 
    mMessage(loc + " : " + msg), 
    mLocationSupplied(true)
{
#ifdef TRACE
    std::cout << "throwing \"" << mMessage << "\"" << std::endl;
#endif
}

void dish::DishException::AddLocation(const std::string &loc)
{
    if(!mLocationSupplied)
    {
        mMessage = loc + " : " + mMessage;
        mLocationSupplied = true;
    }
}
 
const char *dish::DishException::what() const throw()
{
    return mMessage.c_str();
}

/******************************************************************************

    dish function definitions

 ******************************************************************************/

void dish::CheckForError(const int errcode)
{

#ifdef CHECK_ALL_ERRORS
    const char *code("uninitialized");
#endif
    
    switch(errcode)
    {
        
#ifdef CHECK_ALL_ERRORS

        case 0:
        {
            return;
        }
        
#endif
    
        case EDOM:
        {
            throw DomainErrorException("Domain error.");
        }
        
        case ERANGE:
        {
            throw RangeErrorException("Range error.");
        }
        
#ifdef CHECK_ALL_ERRORS

        case EAFNOSUPPORT:
        {
            code = "EAFNOSUPPORT";
        } break;
        
        case EADDRINUSE:
        {
            code = "EADDRINUSE";
        } break;
        
        case EADDRNOTAVAIL:
        {
            code = "EADDRNOTAVAIL";
        } break;
        
        case EISCONN:
        {
            code = "EISCONN";
        } break;
        
        case E2BIG:
        {
            code = "E2BIG";
        } break;
        
        case EFAULT:
        {
            code = "EFAULT";
        } break;
        
        case EBADF:
        {
            code = "EBADF";
        } break;
        
        case EBADMSG:
        {
            code = "EBADMSG";
        } break;
        
        case EPIPE:
        {
            code = "EPIPE";
        } break;
        
        case ECONNABORTED:
        {
            code = "ECONNABORTED";
        } break;
        
        case EALREADY:
        {
            code = "EALREADY";
        } break;
        
        case ECONNREFUSED:
        {
            code = "ECONNREFUSED";
        } break;
        
        case EXDEV:
        {
            code = "EXDEV";
        } break;
        
        case EDESTADDRREQ:
        {
            code = "EDESTADDRREQ";
        } break;
        
        case EBUSY:
        {
            code = "EBUSY";
        } break;
        
        case ENOTEMPTY:
        {
            code = "ENOTEMPTY";
        } break;
        
        case ENOEXEC:
        {
            code = "ENOEXEC";
        } break;
        
        case EEXIST:
        {
            code = "EEXIST";
        } break;
        
        case EFBIG:
        {
            code = "EFBIG";
        } break;
        
        case ENAMETOOLONG:
        {
            code = "ENAMETOOLONG";
        } break;
        
        case ENOSYS:
        {
            code = "ENOSYS";
        } break;
        
        case EHOSTUNREACH:
        {
            code = "EHOSTUNREACH";
        } break;
        
        case EIDRM:
        {
            code = "EIDRM";
        } break;
        
        case EILSEQ:
        {
            code = "EILSEQ";
        } break;
        
        case ENOTTY:
        {
            code = "ENOTTY";
        } break;
        
        case EINTR:
        {
            code = "EINTR";
        } break;
        
        case EINVAL:
        {
            code = "EINVAL";
        } break;
        
        case ESPIPE:
        {
            code = "ESPIPE";
        } break;
        
        case EIO:
        {
            code = "EIO";
        } break;
        
        case EISDIR:
        {
            code = "EISDIR";
        } break;
        
        case EMSGSIZE:
        {
            code = "EMSGSIZE";
        } break;
        
        case ENETDOWN:
        {
            code = "ENETDOWN";
        } break;
        
        case ENETRESET:
        {
            code = "ENETRESET";
        } break;
        
        case ENETUNREACH:
        {
            code = "ENETUNREACH";
        } break;
        
        case ENOBUFS:
        {
            code = "ENOBUFS";
        } break;
        
        case ECHILD:
        {
            code = "ECHILD";
        } break;
        
        case ENOLINK:
        {
            code = "ENOLINK";
        } break;
        
        case ENOMSG:
        {
            code = "ENOMSG";
        } break;
        
        case ENODATA:
        {
            code = "ENODATA";
        } break;
        
        case ENOPROTOOPT:
        {
            code = "ENOPROTOOPT";
        } break;
        
        case ENOSPC:
        {
            code = "ENOSPC";
        } break;
        
        case ENOSR:
        {
            code = "ENOSR";
        } break;
        
        case ENODEV:
        {
            code = "ENODEV";
        } break;
        
        case ENXIO:
        {
            code = "ENXIO";
        } break;
        
        case ENOENT:
        {
            code = "ENOENT";
        } break;
        
        case ESRCH:
        {
            code = "ESRCH";
        } break;
        
        case ENOTDIR:
        {
            code = "ENOTDIR";
        } break;
        
        case ENOTSOCK:
        {
            code = "ENOTSOCK";
        } break;
        
        case ENOSTR:
        {
            code = "ENOSTR";
        } break;
        
        case ENOTCONN:
        {
            code = "ENOTCONN";
        } break;
        
        case ENOMEM:
        {
            code = "ENOMEM";
        } break;
        
        case ENOTSUP:
        {
            code = "ENOTSUP";
        } break;
        
        case ECANCELED:
        {
            code = "ECANCELED";
        } break;
        
        case EINPROGRESS:
        {
            code = "EINPROGRESS";
        } break;
        
        case EPERM:
        {
            code = "EPERM";
        } break;
        
        case EWOULDBLOCK:
        {
            code = "EWOULDBLOCK";
        } break;
        
        case EOWNERDEAD:
        {
            code = "EOWNERDEAD";
        } break;
        
        case EACCES:
        {
            code = "EACCES";
        } break;
        
        case EPROTO:
        {
            code = "EPROTO";
        } break;
        
        case EPROTONOSUPPORT:
        {
            code = "EPROTONOSUPPORT";
        } break;
        
        case EROFS:
        {
            code = "EROFS";
        } break;
        
        case EDEADLK:
        {
            code = "EDEADLK";
        } break;
        
        case ENOTRECOVERABLE:
        {
            code = "ENOTRECOVERABLE";
        } break;
        
        case ETIME:
        {
            code = "ETIME";
        } break;
        
        case ETXTBSY:
        {
            code = "ETXTBSY";
        } break;
        
        case ETIMEDOUT:
        {
            code = "ETIMEDOUT";
        } break;
        
        case EMFILE:
        {
            code = "EMFILE";
        } break;
        
        case ENFILE:
        {
            code = "ENFILE";
        } break;
        
        case EMLINK:
        {
            code = "EMLINK";
        } break;
        
        case ELOOP:
        {
            code = "ELOOP";
        } break;
        
        case EOVERFLOW:
        {
            code = "EOVERFLOW";
        } break;
        
        case EPROTOTYPE:
        {
            code = "EPROTOTYPE";
        } break;
    
        default:
        {
            code = "<empty>";
        }
        
#else

        default:
        {
            //  Empty
        }
        
#endif
                
    }
    
#ifdef CHECK_ALL_ERRORS

    std::error_condition error(errcode, std::generic_category());
    
    std::stringstream message;
    message << error.message();
    message << ": ";
    message << code;
    message << " (";
    message << errcode;
    message << ").";
    
    throw UnknownRuntimeException(message.str());
    
#endif
}

