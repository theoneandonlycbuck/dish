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

#ifndef DISH_LANGUAGE_H
#define DISH_LANGUAGE_H

#include "dishconfig.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <string>

#include "atomics.h"
#include "inline.h"
#include "profile.h"
#include "symtab.h"

namespace dish
{

    class LanguageSymbolTable : public iSymbolTable
    {
        private:
            std::shared_ptr< iSymbolTable > mBase;
            
            StackedSymbolTable mStack;
            
            std::shared_ptr< ExecutionProfile > mProfile;
            
        protected:
            void insert(const std::string &key, std::shared_ptr< dish::iAtomic > value) const;
        
        public:
            LanguageSymbolTable(const bool &profile, const int &maxdepth = dish::StackedSymbolTable::INFINITE_STACK_DEPTH);
            LanguageSymbolTable(const LanguageSymbolTable &symtab, const CloneT &type = cloneMinimal);
           
            std::shared_ptr< iAtomic > LookupInBase(const std::string &key) const;
            
            static INLINE std::shared_ptr< iSymbolTable > MakeSystemSymbolTable()
            {
#ifdef LANG_TABLE_HASHED
                return HashedSymbolTable::MakeValue();
#endif
    
#ifdef LANG_TABLE_BASIC
                return BasicSymbolTable::MakeValue();
#endif
            }
            
            INLINE int StackDepth() const { return mStack.Num(); };
            INLINE int MaxStackDepthAttained() const throw() { return mStack.MaxDepthAttained(); };
            
            INLINE bool CollectExecutionProfile() const { return (0 != mProfile.get()); };
            INLINE ExecutionProfile &ProfileInformation() const { assert(CollectExecutionProfile()); return *mProfile; };
            
            //  From iSymbolTable
            
            virtual std::shared_ptr< iSymbolTable > Clone(const CloneT &type = cloneMinimal) const;
            
            virtual void Shuffle();
            
            virtual void Push(std::shared_ptr< iSymbolTable > table);
            virtual void Push();
            virtual void Pop();
            virtual bool IsEmpty() const;
            
            virtual int Num() const;
            
            virtual bool Exists(const std::string &key) const;
            virtual void Insert(const std::string &key, std::shared_ptr< iAtomic > value);
            virtual std::shared_ptr< iAtomic > Lookup(const std::string &key) const;
            
            virtual void Load(iSymbolTable &symtab, const CloneT &type = cloneMinimal) const;
            
            virtual void Clear();
            
            virtual void Histogram(std::ostream &out) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };

}

#endif

