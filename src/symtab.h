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

#ifndef DISH_SYMTAB_H
#define DISH_SYMTAB_H

#include "dishconfig.h"

#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "exception.h"
#include "inline.h"
#include "isymtab.h"
#include "utility.h"

namespace dish
{

    ////////////////////////////////////////////////////////////////////////////
    
    class iAtomic;

    ////////////////////////////////////////////////////////////////////////////
    
    class SymbolTable : public iSymbolTable
    {
        public:
            
            //  From iSymbolTable
            
            virtual void Push(std::shared_ptr< iSymbolTable > table);
            virtual void Push();
            virtual void Pop();
            virtual bool IsEmpty() const;
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class SingleSymbolTable : public SymbolTable
    {
        private:
            const std::string mId;
            std::shared_ptr< iAtomic > mValue;
            
            static IntegerT LookupCount;
            
        protected:
            INLINE SingleSymbolTable(const std::string &id, std::shared_ptr< iAtomic > &value) : SymbolTable(), mId(id), mValue(value) { assert(0 != mValue.get()); };
        
        public:
        
            static INLINE std::shared_ptr< SingleSymbolTable > MakeValue(const std::string &id, std::shared_ptr< iAtomic > value) { return std::shared_ptr< SingleSymbolTable >(new SingleSymbolTable(id, value)); };
        
            static INLINE IntegerT GetLookupCount() throw() { return LookupCount; };
            
            //  From iSymbolTable
            
            virtual std::shared_ptr< iSymbolTable > Clone(const CloneT &type = cloneMinimal) const;
            
            virtual void Shuffle();
            
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
    
    class BasicSymbolTable : public SymbolTable
    {
        public:
        
            using TableT = std::map< std::string, std::shared_ptr< iAtomic > >;
    
        private:
            TableT mTable;
            
            static IntegerT LookupCount;
        
        public:
            INLINE BasicSymbolTable() : SymbolTable(), mTable() {};
            BasicSymbolTable(const BasicSymbolTable &table, const CloneT &type = cloneMinimal);
            
            static INLINE std::shared_ptr< BasicSymbolTable > MakeValue() { return std::shared_ptr< BasicSymbolTable >(new BasicSymbolTable()); };
            static INLINE std::shared_ptr< BasicSymbolTable > MakeValue(const BasicSymbolTable &table, const CloneT &type = cloneMinimal) { return std::shared_ptr< BasicSymbolTable >(new BasicSymbolTable(table, type)); };
            
            static INLINE IntegerT GetLookupCount() throw() { return LookupCount; };
            
            //  From iSymbolTable
            
            virtual std::shared_ptr< iSymbolTable > Clone(const CloneT &type = cloneMinimal) const;
            
            virtual void Shuffle();
            
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
    
    class HashedSymbolTable : public SymbolTable
    {
        public:
        
            using TableT = std::vector< BasicSymbolTable >;
            
            static IntegerT LookupCount;
            
            static const TableT::size_type TABLE_SIZE;
    
        private:
            TableT mTable;
            
        protected:
            
            //  The hash function is defined in the .cpp file as part of the
            //  anonymous namespace so it can be inlined without cluttering up
            //  this here header file :)
            //static TableT::size_type h(const std::string &key);
            
        public:
            INLINE HashedSymbolTable() : SymbolTable(), mTable(TABLE_SIZE) {};
            HashedSymbolTable(const HashedSymbolTable &table, const CloneT &type = cloneMinimal);
            
            static INLINE std::shared_ptr< HashedSymbolTable > MakeValue() { return std::shared_ptr< HashedSymbolTable >(new HashedSymbolTable()); };
            static INLINE std::shared_ptr< HashedSymbolTable > MakeValue(const HashedSymbolTable &table, const CloneT &type = cloneMinimal) { return std::shared_ptr< HashedSymbolTable >(new HashedSymbolTable(table, type)); };
            
            static INLINE IntegerT GetLookupCount() throw() { return LookupCount; };
            
            //  From iSymbolTable
            
            virtual std::shared_ptr< iSymbolTable > Clone(const CloneT &type = cloneMinimal) const;
            
            virtual void Shuffle();
            
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
    
    class StackedSymbolTable : public SymbolTable
    {
        public:
        
            using TableT = std::list< std::shared_ptr< iSymbolTable > >;
            
            static const int INFINITE_STACK_DEPTH;
            
#ifdef RECYCLE_SYMBOL_TABLES
            using RecycleListT = std::vector< std::shared_ptr< iSymbolTable > >;
            
            static const RecycleListT::size_type RESERVED_RECYCLE_BIN_DEPTH;
            static const RecycleListT::size_type MAXIMUM_RECYCLE_BIN_DEPTH;
#endif
    
        private:
            TableT mStack;
            
#ifdef RECYCLE_SYMBOL_TABLES
            RecycleListT mRecycleBin;
#endif
            
            const int mMaximumStackDepth;
            mutable int mMaximumStackDepthAttained;
            
        protected:
            
            INLINE void checkStackSize() const
            {
                const int stack_size(static_cast< int >(mStack.size()));
            
                if((mMaximumStackDepth <= 0) || (stack_size <= mMaximumStackDepth))
                {
                    if(stack_size > mMaximumStackDepthAttained)
                    {
                        mMaximumStackDepthAttained = stack_size;
                    }
                
                    return;
                }

                throw StackOverflowException("Maximum stack-depth exceeded.");
            }
        
        public:
        
#ifdef RECYCLE_SYMBOL_TABLES
            INLINE StackedSymbolTable(const int &maxdepth) : SymbolTable(), mStack(), mRecycleBin(), mMaximumStackDepth(maxdepth), mMaximumStackDepthAttained(0) { mRecycleBin.reserve(RESERVED_RECYCLE_BIN_DEPTH); };
            StackedSymbolTable(const StackedSymbolTable &symtab, const CloneT &type = cloneMinimal);
#else
            INLINE StackedSymbolTable(const int &maxdepth) : SymbolTable(), mStack(), mMaximumStackDepth(maxdepth), mMaximumStackDepthAttained(0) {};
            StackedSymbolTable(const StackedSymbolTable &symtab, const CloneT &type = cloneMinimal);
#endif
            
            static INLINE std::shared_ptr< StackedSymbolTable > MakeValue(const int &maxdepth) { return std::shared_ptr< StackedSymbolTable >(new StackedSymbolTable(maxdepth)); };
            static INLINE std::shared_ptr< StackedSymbolTable > MakeValue(const StackedSymbolTable &symtab, const CloneT &type = cloneMinimal) { return std::shared_ptr< StackedSymbolTable >(new StackedSymbolTable(symtab, type)); };
            
            INLINE const int &MaxDepth() const throw() { return mMaximumStackDepth; };
            INLINE const int &MaxDepthAttained() const throw() { return mMaximumStackDepthAttained; };
            
            
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

    ////////////////////////////////////////////////////////////////////////////
    
    class ScopedScope
    {
        private:
            iSymbolTable &mSymbolTable;
            
        public:
            INLINE ScopedScope(iSymbolTable &symtab) : mSymbolTable(symtab) { mSymbolTable.Push(); };
            INLINE ScopedScope(iSymbolTable &symtab, std::shared_ptr< iSymbolTable > table) : mSymbolTable(symtab) { mSymbolTable.Push(table); };
            INLINE ~ScopedScope() { mSymbolTable.Pop(); };
            
    };

    ////////////////////////////////////////////////////////////////////////////

}

#endif

