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

#ifndef DISH_UTILITY_H
#define DISH_UTILITY_H

#include "dishconfig.h"

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <iostream>
#include <limits>
#include <list>
#include <memory>
#include <random>
#include <string>
#include <vector>

#include "exception.h"
#include "inline.h"
#include "langerr.h"
#include "types.h"

namespace dish
{

    ////////////////////////////////////////////////////////////////////////////
    
    extern const std::string EOLN_CHARACTERS;
    extern const std::string WHITESPACE_CHARACTERS;
    extern const std::string DIGIT_CHARACTERS;
    extern const std::string LOWER_CASE_LETTER_CHARACTERS;
    extern const std::string UPPER_CASE_LETTER_CHARACTERS;
    extern const std::string LETTER_CHARACTERS;
    
    extern const std::string VALID_FILE_NAME_CHARACTERS;
    
    extern const std::string VALID_ID_CHARACTERS;

    ////////////////////////////////////////////////////////////////////////////

    class iPrintable
    {
        protected:
        
            static const std::string::size_type INDENT;
        
            static INLINE void printIndent(std::ostream &out, const std::string::size_type &indent) { if(indent > 0) { out << std::string(indent, ' '); } };
    
        public:
            virtual ~iPrintable() {};
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const = 0;
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class TraceBlock
    {
        private:
            const std::string mName;
            
            static int Indent;
        
        public:
            TraceBlock(const std::string &name);
            ~TraceBlock();
        
    };

    ////////////////////////////////////////////////////////////////////////////

    INLINEC bool IsEqual(const BooleanT &lhs, const BooleanT &rhs) 
    {
        return (lhs == rhs);
    }

    INLINEC bool IsEqual(const IntegerT &lhs, const IntegerT &rhs) 
    {
        return (lhs == rhs);
    }
    
    INLINEC bool IsEqual(const RealT &lhs, const RealT &rhs) 
    {
        RealT tmp;
        {
            ScopedCheckForError checkforerror;
            tmp = std::fabs(lhs - rhs);
        }
    
        return (tmp <= (2 * std::numeric_limits< RealT >::epsilon()));
    }
    
    INLINEC bool IsEqual(const long double &lhs, const long double &rhs) 
    {
        RealT tmp;
        {
            ScopedCheckForError checkforerror;
            tmp = std::fabs(lhs - rhs);
        }
    
        return (tmp <= (2 * std::numeric_limits< long double >::epsilon()));
    }
    
    extern const bool CASE_SENSITIVE;
    extern const bool CASE_INSENSITIVE;
    extern bool IsEqual(const std::string &lhs, const std::string &rhs, const bool &case_sensitive);
    extern bool IsLessThan(const std::string &lhs, const std::string &rhs, const bool &case_sensitive);
    
    struct CaseInsensitiveStringCompare
    {
    
        INLINE bool operator()(const std::string &lhs, const std::string &rhs) const
        {
            return IsLessThan(lhs, rhs, CASE_INSENSITIVE);
        }
    
    };
    
    INLINEC bool IsZero(const IntegerT &arg)
    {
        return (0 == arg);
    }
    
    INLINEC bool IsZero(const RealT &arg)
    {
        RealT absarg;
        {
            ScopedCheckForError checkforerror;
            absarg = std::fabs(arg);
        }
        
        return (absarg <= (2 * std::numeric_limits< RealT >::epsilon()));
    }
    
    INLINEC bool IsZero(const long double &arg)
    {
        RealT absarg;
        {
            ScopedCheckForError checkforerror;
            absarg = std::fabs(arg);
        }
        
        return (absarg <= (2 * std::numeric_limits< long double >::epsilon()));
    }

    ////////////////////////////////////////////////////////////////////////////
    
    INLINEC IntegerT Divide(const IntegerT &numer, const IntegerT &denom)
    {
        if(!IsZero(denom))
        {
            return (!IsZero(numer)) ? (numer / denom) : 0;
        }
        
        throw DivideByZeroException("A zero denomonator was detected.");
    }
    
    INLINEC RealT Divide(const RealT &numer, const RealT &denom)
    {
        if(!IsZero(denom))
        {
            ScopedCheckForError checkforerror;
            
            return (!IsZero(numer)) ? (numer / denom) : 0.0;
        }
        
        throw DivideByZeroException("A zero denomonator was detected.");
    }
    
    INLINEC long double Divide(const long double &numer, const long double &denom)
    {
        if(!IsZero(denom))
        {
            ScopedCheckForError checkforerror;
            
            return (!IsZero(numer)) ? (numer / denom) : 0.0;
        }
        
        throw DivideByZeroException("A zero denomonator was detected.");
    }
    
    INLINEC IntegerT Modulus(const IntegerT &numer, const IntegerT &denom)
    {
        if(!IsZero(denom))
        {
            return (!IsZero(numer)) ? (numer % denom) : 0;
        }
        
        throw DivideByZeroException("A zero denomonator was detected.");
    }
    
    INLINEC RealT Modulus(const RealT &numer, const RealT &denom)
    {
        if(!IsZero(denom))
        {
            ScopedCheckForError checkforerror;
            
            return std::fmod(numer, denom);
        }
        
        throw DivideByZeroException("A zero denomonator was detected.");
    }
    
    INLINEC long double Modulus(const long double &numer, const long double &denom)
    {
        if(!IsZero(denom))
        {
            ScopedCheckForError checkforerror;
            
            return std::fmod(numer, denom);
        }
        
        throw DivideByZeroException("A zero denomonator was detected.");
    }
    
    INLINEC IntegerT Pow(const IntegerT &x, IntegerT expon)
    {
        assert(expon >= 0);

        IntegerT ret(1);
        
        while(expon-- > 0)
        {
            ret *= x;
        }
        
        return ret;
    }
    
    INLINEC RealT InvPow(const IntegerT &x, IntegerT expon)
    { 
        assert(expon <= 0);
        
        return Divide(1.0, static_cast< RealT >(Pow(x, -expon)));
    }
           
    INLINEC RealT Pow(const RealT &base, const RealT &expon)
    {
        ScopedCheckForError checkforerror;
        
        return std::pow(base, expon);
    }
    
    INLINEC long double Pow(const long double &base, const long double &expon)
    {
        ScopedCheckForError checkforerror;
        
        return std::pow(base, expon);
    }
    
    template
    <
        typename T
    >
    INLINEC T SignOf(const T &arg)
    {
        return ((arg >= 0) ? static_cast< T >(1) : static_cast< T >(-1));
    }

    ////////////////////////////////////////////////////////////////////////////
    
    INLINEC bool BeginsWith(const std::string &lhs, const int &rhs, const bool &case_sensitive = false)
    { 
        return (!lhs.empty()) ? (case_sensitive ? (lhs.front() == rhs) : (std::toupper(lhs.front()) == std::toupper(rhs))) : false;
    }
    
    INLINEC bool BeginsWith(const std::string &lhs, const std::string &rhs, const bool &case_sensitive = false)
    {
        const std::string::size_type rhs_length(rhs.length());
        const std::string::size_type lhs_length(lhs.length());
        
        if(rhs_length < lhs_length)
        {
            return IsEqual(lhs.substr(0, rhs_length), rhs, case_sensitive);
        }
        
        else if(rhs_length == lhs_length)
        {
            return IsEqual(lhs, rhs, case_sensitive);
        }
        
        return false;
    }
    
    INLINEC bool EndsWith(const std::string &lhs, const int &rhs, const bool &case_sensitive = false)
    {
        return (!lhs.empty()) ? (case_sensitive ? (lhs.back() == rhs) : (std::toupper(lhs.back()) == std::toupper(rhs))) : false;
    }
    
    INLINEC bool EndsWith(const std::string &lhs, const std::string &rhs, const bool &case_sensitive = false)
    {
        const std::string::size_type rhs_length(rhs.length());
        const std::string::size_type lhs_length(lhs.length());
        
        if(rhs_length < lhs_length)
        {
            return IsEqual(lhs.substr(lhs_length - rhs_length, std::string::npos), rhs, case_sensitive);
        }
        
        else if(rhs_length == lhs_length)
        {
            return IsEqual(lhs, rhs, case_sensitive);
        }
        
        return false;
    }
    
    extern std::string::size_type caseInsensitiveIndexOf(const std::string &lhs, const int &rhs);
    INLINEC std::string::size_type IndexOf(const std::string &lhs, const int &rhs, const bool &case_sensitive = false) { return case_sensitive ? lhs.find(static_cast< char >(rhs)) : caseInsensitiveIndexOf(lhs, rhs); };
    
    extern std::string::size_type caseInsensitiveIndexOf(const std::string &lhs, const std::string &rhs);
    INLINEC std::string::size_type IndexOf(const std::string &lhs, const std::string &rhs, const bool &case_sensitive = false) { return case_sensitive ? lhs.find(rhs) : caseInsensitiveIndexOf(lhs, rhs); };
    
    extern void TrimBegin(std::string &str, const std::string &trim);
    extern void TrimEnd(std::string &str, const std::string &trim);
    INLINEC void Trim(std::string &str, const std::string &trim) { TrimBegin(str, trim); TrimEnd(str, trim); };
    
    extern std::string ToUpper(const std::string &str);
    extern std::string ToLower(const std::string &str);

    ////////////////////////////////////////////////////////////////////////////
    
    extern bool FileExists(const std::string &fname);

    ////////////////////////////////////////////////////////////////////////////
    
    class iRNG
    {
        public:
            virtual ~iRNG() {};
            
            virtual IntegerT operator*() = 0;
            
            virtual IntegerT Maximum() const = 0;
            
            virtual IntegerT Seed() const = 0;
            virtual IntegerT Num() const = 0;
            
    };
    
    class RNG : public iRNG
    {
        private:
            const IntegerT mSeed;
            
#ifdef DISH_64BIT_ATOMICS
            std::mt19937_64 mGenerator;
#endif
            
#ifdef DISH_32BIT_ATOMICS
            std::mt19937 mGenerator;
#endif
            
            IntegerT mNum;
        
        public:
            INLINE RNG(const IntegerT &seed) : iRNG(), mSeed(seed), mGenerator(seed), mNum(0) {};
            
            //  From iRNG
            
            virtual IntegerT operator*();
            
            virtual IntegerT Maximum() const;
            
            virtual IntegerT Seed() const;
            virtual IntegerT Num() const;
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    template
    <
        typename T
    >
    struct EmptyDestroy
    {
    
        static INLINE void Destroy(const T &object)
        {
            //  Empty
        }
        
    };
    
    template
    <
        typename T,
        
        unsigned int Size = 10,
        
        typename DestroyF = EmptyDestroy< T >
    >
    class HandleList
    {
        public:
        
            typedef std::vector< std::shared_ptr< T > > ListT;
    
        private:
            ListT mList;
        
        public:
            INLINE HandleList() : mList() { mList.reserve(Size); }
                        
            INLINE unsigned int Allocate()
            {
                for(typename ListT::size_type handle(0); handle < Size; ++handle)
                {
                    if(0 == mList[handle].get())
                    {
                        mList[handle].reset(new T);
                        
                        return handle + 1;
                    }
                }
                
                throw TooManyOpenHandlesException("Too many open handles.");
            }
            
            INLINE unsigned int NumAllocated() const
            {
                unsigned int num(0);

                std::for_each(
                    mList.begin(), mList.end(),
                    [&](const typename ListT::value_type &elem)
                    {
                        if(0 != elem.get())
                        {
                            ++num;
                        }
                    }
                );
                
                return num;
            }
            
            INLINE bool IsValid(const unsigned int &handle) const
            {
                if((handle > 0) && (handle <= Size))
                {
                    return (0 != mList[handle - 1].get());
                }
                
                throw InvalidHandleException("Invalid handle specified.");
            }
            
            INLINE T &operator[](const unsigned int &handle) const
            {
                if((handle > 0) && (handle <= Size))
                {
                    const typename ListT::size_type adjhandle(handle - 1); 
                
                    if(0 != mList[adjhandle].get())
                    {
                        return *mList[adjhandle];
                    }
                }
                
                throw InvalidHandleException("Invalid handle specified.");
            }
            
            INLINE bool Destroy(const unsigned int &handle)
            {
                if((handle > 0) && (handle <= Size))
                {
                    const typename ListT::size_type adjhandle(handle - 1); 
                
                    bool destroyed(false);
                
                    if(0 != mList[adjhandle].get())
                    {
                        DestroyF::Destroy(*mList[adjhandle]);
                        destroyed = true;
                    }
                
                    mList[adjhandle].reset();
                    
                    return destroyed;
                }
                
                throw InvalidHandleException("Invalid handle specified.");
            }
            
            INLINE void DestroyAll()
            {
                std::for_each(
                    mList.begin(), mList.end(),
                    [](typename ListT::value_type &object)
                    {
                        if(0 != object.get())
                        {
                            DestroyF::Destroy(*object);
                        }
                            
                        object.reset();
                    }
                );
            }
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    template
    <
        typename T,
        
        unsigned int InitialSize = 1000,
        unsigned int MaxSize = 100000
    >
    class BufferStack
    {
        private:
            std::vector< T > mBuffer;
            
            unsigned int mMaxBufferSize;
        
        public:
            INLINE BufferStack() : mBuffer(), mMaxBufferSize(0) { assert((MaxSize <= 0) || (InitialSize <= MaxSize)); mBuffer.reserve(InitialSize); };
            
            INLINE bool IsEmpty() const { return mBuffer.empty(); };
            INLINE bool IsFull() const { return (mBuffer.size() >= MaxSize); };
            
            INLINE unsigned int BufferSize() const { return static_cast< unsigned int >(mBuffer.size()); };
            INLINE unsigned int MaxBufferSize() const { return mMaxBufferSize; };
            
            INLINE bool Insert(T arg)
            {
                unsigned int size(static_cast< unsigned int >(mBuffer.size()));
            
                if((MaxSize <= 0) || (size < MaxSize))
                {
                    mBuffer.push_back(arg);
                    
                    if(++size > mMaxBufferSize)
                    {
                        mMaxBufferSize = size;
                    }
                    
                    return true;
                }
                
                return false;
            }
            
            INLINE T Next()
            {
                if(!IsEmpty())
                {
                    T tmp(mBuffer.back());
                    mBuffer.pop_back();
                    
                    return tmp;
                }
                
                throw IllegalOperationException("The circular buffer is empty; no 'next' element to return.");
            }
        
    };

    ////////////////////////////////////////////////////////////////////////////

    class BucketCounts
    {
        public:
        
            ////
            
            using RangeT = std::pair< IntegerT, IntegerT >;
            using NodeT = std::pair< RangeT, IntegerT >;
            
            static INLINE const RangeT &Range(const NodeT &node) throw() { return node.first; };
            static INLINE RangeT &Range(NodeT &node) throw() { return node.first; };
            
            static INLINE const IntegerT &RangeMaximum(const NodeT &node) throw() { return Range(node).first; };
            static INLINE IntegerT &RangeMaximum(NodeT &node) throw() { return Range(node).first; };
            
            static INLINE const IntegerT &RangeMinimum(const NodeT &node) throw() { return Range(node).second; };
            static INLINE IntegerT &RangeMinimum(NodeT &node) throw() { return Range(node).second; };
            
            static INLINE const IntegerT &Count(const NodeT &node) throw() { return node.second; };
            static INLINE IntegerT &Count(NodeT &node) throw() { return node.second; };
        
            ////
            
            using BucketListT = std::vector< NodeT >;
        
        private:
            BucketListT mBuckets;
            
            IntegerT mOverCount;
        
        public:
            INLINE BucketCounts() : mBuckets(), mOverCount(0) {};
            INLINE BucketCounts(const unsigned int &nbuckets) : mBuckets(), mOverCount(0) { mBuckets.reserve(nbuckets); };
            
            INLINE unsigned int AddBucket(const IntegerT &min, const IntegerT &max)
                { assert(max > min); const unsigned int index(mBuckets.size()); mBuckets.push_back(std::make_pair(std::make_pair(max, min), 0)); return index; };
            
            INLINE IntegerT NumNodex() const { return static_cast< IntegerT >(mBuckets.size()); };
            INLINE const NodeT &GetNode(const unsigned int &index) const { return mBuckets.at(index); };
            
            const IntegerT &operator[](const unsigned int &index) const;
            IntegerT &operator[](const unsigned int &index);
            
    };

    ////////////////////////////////////////////////////////////////////////////

}

INLINEC std::ostream &operator<<(std::ostream &out, const dish::iPrintable &obj) { obj.Print(out); return out; };

#endif

