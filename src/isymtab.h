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

#ifndef DISH_ISYMTAB_H
#define DISH_ISYMTAB_H

#include "dishconfig.h"

#include <memory>
#include <string>

#include "inline.h"
#include "utility.h"

namespace dish
{

    ////////////////////////////////////////////////////////////////////////////
    
    class iAtomic;

    ////////////////////////////////////////////////////////////////////////////

    class iSymbolTable : public iPrintable
    {
        public:
        
            using CloneT = enum
            {
                cloneNull = 0,
            
                cloneMinimal,
                cloneShallow,
                cloneDeep
            };
            
            INLINE iSymbolTable() : iPrintable() {};
        
            virtual ~iSymbolTable() {};
            
            virtual std::shared_ptr< iSymbolTable > Clone(const CloneT &type = cloneMinimal) const = 0;
            
            virtual void Shuffle() = 0;
            
            virtual void Push(std::shared_ptr< iSymbolTable > table) = 0;
            virtual void Push() = 0;
            virtual void Pop() = 0;
            virtual bool IsEmpty() const = 0;
            
            virtual int Num() const = 0;
            
            virtual bool Exists(const std::string &key) const = 0;
            virtual void Insert(const std::string &key, std::shared_ptr< iAtomic > value) = 0;
            virtual std::shared_ptr< iAtomic > Lookup(const std::string &key) const = 0;
            
            virtual void Load(iSymbolTable &symtab, const CloneT &type = cloneMinimal) const = 0;
            
            virtual void Clear() = 0;
            
            virtual void Histogram(std::ostream &out) const = 0;
            
            INLINE std::shared_ptr< iAtomic > operator[](const std::string &key) const { return Lookup(key); };
        
    };

    ////////////////////////////////////////////////////////////////////////////

}

#endif

