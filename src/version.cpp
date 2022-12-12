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

#include "version.h"

/******************************************************************************

    Version class definitions

 ******************************************************************************/

bool Version::operator<(const Version &rhs) const throw()
{
    if(Major() < rhs.Major())
    {
        return true;
    }
    
    else if(Major() == rhs.Major())
    {
        if(Minor() < rhs.Minor())
        {
            return true;
        }
        
        else if(Minor() == rhs.Minor())
        {
            if(Revision() < rhs.Revision())
            {
                return true;
            }
        }
    }
    
    return false;
}

/******************************************************************************

    Public function definitions

 ******************************************************************************/

std::ostream &operator<<(std::ostream &out, const Version &version)
{
    out << version.Major();
    out << ".";
    out << version.Minor();
    out << ".";
    out << version.Revision();

    return out;
}

