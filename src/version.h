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

#ifndef VERSION_H
#define VERSION_H

#include <cassert>
#include <iostream>

#include "inline.h"

////////////////////////////////////////////////////////////////////////////////

#define MAJOR_VERSION               0
#define MINOR_VERSION               1
#define REVISION_VERSION            18

#define LANG_MAJOR_VERSION          0
#define LANG_MINOR_VERSION          3
#define LANG_REVISION_VERSION       0

#define LIBRARY_MAJOR_VERSION       0
#define LIBRARY_MINOR_VERSION       1
#define LIBRARY_REVISION_VERSION    0

////////////////////////////////////////////////////////////////////////////////

class Version
{
    private:
        const int mMajor;
        const int mMinor;
        const int mRevision;
    
    public:
        INLINE Version(const int &maj, const int &min, const int &rev) : mMajor(maj), mMinor(min), mRevision(rev) { assert(mMajor >= 0); assert(mMinor >= 0); assert(mRevision >= 0); };
        INLINE Version(const Version &ver) : mMajor(ver.Major()), mMinor(ver.Minor()), mRevision(ver.Revision()) { assert(mMajor >= 0); assert(mMinor >= 0); assert(mRevision >= 0); };
        
        INLINE const int &Major() const throw() { return mMajor; };
        INLINE const int &Minor() const throw() { return mMinor; };
        INLINE const int &Revision() const throw() { return mRevision; };
        
        bool operator<(const Version &rhs) const throw();
        INLINE bool operator<=(const Version &rhs) const throw() { return ((*this < rhs) || (*this == rhs)); };
        INLINE bool operator==(const Version &rhs) const throw() { return ((Major() == rhs.Major()) && (Minor() == rhs.Minor()) && (Revision() == rhs.Revision())); };
        INLINE bool operator!=(const Version &rhs) const throw() { return ((Major() != rhs.Major()) || (Minor() != rhs.Minor()) || (Revision() != rhs.Revision())); };
        INLINE bool operator>=(const Version &rhs) const throw() { return ((rhs < *this) || (rhs == *this)); };
        INLINE bool operator>(const Version &rhs) const throw() { return (rhs < *this); };
    
};

////////////////////////////////////////////////////////////////////////////////

extern std::ostream &operator<<(std::ostream &out, const Version &version);

////////////////////////////////////////////////////////////////////////////////

#endif

