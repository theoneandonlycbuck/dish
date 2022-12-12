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

#ifndef DISH_PLDISH_H
#define DISH_PLDISH_H

#include "dishconfig.h"

#include <algorithm>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "atomics.h"
#include "exception.h"
#include "inline.h"
#include "input.h"
#include "language.h"
#include "parser.h"
#include "symtab.h"
#include "types.h"

namespace dish
{

    ////////////////////////////////////////////////////////////////////////////
        
    class iCppReferenceType
    {
        public:
            virtual ~iCppReferenceType() {};
            
            virtual IntegerT Size() const = 0;
            
            virtual std::shared_ptr< iAtomic > Declare(void * const ptr, const bool &locked = false) const = 0;
            
            virtual void Swap(void * const val1, void * const val2) const = 0;
        
    };
    
    class BooleanCppReferenceType : public iCppReferenceType
    {
        public:
            INLINE BooleanCppReferenceType() {};
            
            //  From iType
            
            virtual IntegerT Size() const { return static_cast< IntegerT >(sizeof(BooleanT)); };
            
            virtual std::shared_ptr< iAtomic > Declare(void * const ptr, const bool &locked = false) const;
            
            virtual void Swap(void * const val1, void * const val2) const;
            
    };
    
    class IntegerCppReferenceType : public iCppReferenceType
    {
        public:
            INLINE IntegerCppReferenceType() {};
            
            //  From iType
            
            virtual IntegerT Size() const { return static_cast< IntegerT >(sizeof(IntegerT)); };
            
            virtual std::shared_ptr< iAtomic > Declare(void * const ptr, const bool &locked = false) const;
            
            virtual void Swap(void * const val1, void * const val2) const;
            
    };
    
    class RealCppReferenceType : public iCppReferenceType
    {
        public:
            INLINE RealCppReferenceType() {};
            
            //  From iType
            
            virtual IntegerT Size() const { return static_cast< IntegerT >(sizeof(RealT)); };
            
            virtual std::shared_ptr< iAtomic > Declare(void * const ptr, const bool &locked = false) const;
            
            virtual void Swap(void * const val1, void * const val2) const;
            
    };
    
    class StringCppReferenceType : public iCppReferenceType
    {
        public:
            INLINE StringCppReferenceType() {};
            
            //  From iType
            
            virtual IntegerT Size() const { return static_cast< IntegerT >(sizeof(StringT)); };
            
            virtual std::shared_ptr< iAtomic > Declare(void * const ptr, const bool &locked = false) const;
            
            virtual void Swap(void * const val1, void * const val2) const;
            
    };
    
    class ArrayCppReferenceType : public iCppReferenceType
    {
        private:
            const IntegerT mNumElements;
            std::shared_ptr< iCppReferenceType > mType;
    
        public:
            ArrayCppReferenceType(const IntegerT &n, std::shared_ptr< iCppReferenceType > type);
            
            //  From iType
            
            virtual IntegerT Size() const { return (mNumElements * mType->Size()); };
            
            virtual std::shared_ptr< iAtomic > Declare(void * const ptr, const bool &locked = false) const;
            
            virtual void Swap(void * const val1, void * const val2) const;
            
    };
    
    class StructureCppReferenceType : public iCppReferenceType
    {
        public:
            
            using MemberSetT =  std::vector< std::pair< std::string, std::pair< std::shared_ptr< iCppReferenceType >, size_t > > >;
            
        private:
            const IntegerT mStructureSize;
        
            MemberSetT mMembers;
        
        public:
            StructureCppReferenceType(const IntegerT size);
            
            void AddMember(const std::string &member, std::shared_ptr< iCppReferenceType > type, const size_t &offset);
            
            INLINE void AddBooleanMember(const std::string &member, const size_t &offset) { AddMember(member, std::shared_ptr< iCppReferenceType >(new BooleanCppReferenceType()), offset); };
            INLINE void AddIntegerMember(const std::string &member, const size_t &offset) { AddMember(member, std::shared_ptr< iCppReferenceType >(new IntegerCppReferenceType()), offset); };
            INLINE void AddRealMember(const std::string &member, const size_t &offset) { AddMember(member, std::shared_ptr< iCppReferenceType >(new RealCppReferenceType()), offset); };
            INLINE void AddStringMember(const std::string &member, const size_t &offset) { AddMember(member, std::shared_ptr< iCppReferenceType >(new StringCppReferenceType()), offset); };
            
            //  From iType
            
            virtual IntegerT Size() const { return mStructureSize; };
            
            virtual std::shared_ptr< iAtomic > Declare(void * const ptr, const bool &locked = false) const;
            
            virtual void Swap(void * const val1, void * const val2) const;
        
    };
    
    ////////////////////////////////////////////////////////////////////////////
    
    class BooleanCppReferenceValue : public BooleanValueBase
    {
        private:
            void * const mValue;
            
        protected:
            BooleanCppReferenceValue(void * const value, const bool &locked = false);
            BooleanCppReferenceValue(BooleanT &value, const bool &locked = false);
        
            //  From BooleanValueBase
            
            virtual const BooleanT &value() const { return *reinterpret_cast< BooleanT * >(mValue); };
            virtual BooleanT &value() { return *reinterpret_cast< BooleanT * >(mValue); };
    
        public:
            
            static INLINE std::shared_ptr< BooleanCppReferenceValue > MakeValue(void * const value, const bool &locked = false) { return std::shared_ptr< BooleanCppReferenceValue >(new BooleanCppReferenceValue(value, locked)); };
            static INLINE std::shared_ptr< BooleanCppReferenceValue > MakeValue(BooleanT &value, const bool &locked = false) { return std::shared_ptr< BooleanCppReferenceValue >(new BooleanCppReferenceValue(value, locked)); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Copy() const;
        
    };
    
    class IntegerCppReferenceValue : public IntegerValueBase
    {
        private:
            void * const mValue;
            
        protected:
            IntegerCppReferenceValue(void * const value, const bool &locked = false);
            IntegerCppReferenceValue(IntegerT &value, const bool &locked = false);
        
            //  From IntegerValueBase
            
            virtual const IntegerT &value() const { return *reinterpret_cast< IntegerT * >(mValue); };
            virtual IntegerT &value() { return *reinterpret_cast< IntegerT * >(mValue); };
    
        public:
            
            static INLINE std::shared_ptr< IntegerCppReferenceValue > MakeValue(void * const value, const bool &locked = false) { return std::shared_ptr< IntegerCppReferenceValue >(new IntegerCppReferenceValue(value, locked)); };
            static INLINE std::shared_ptr< IntegerCppReferenceValue > MakeValue(IntegerT &value, const bool &locked = false) { return std::shared_ptr< IntegerCppReferenceValue >(new IntegerCppReferenceValue(value, locked)); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Copy() const;
        
    };
    
    class RealCppReferenceValue : public RealValueBase
    {
        private:
            void * const mValue;
            
        protected:
            RealCppReferenceValue(void * const value, const bool &locked = false);
            RealCppReferenceValue(RealT &value, const bool &locked = false);
        
            //  From RealValueBase
            
            virtual const RealT &value() const { return *reinterpret_cast< RealT * >(mValue); };
            virtual RealT &value() { return *reinterpret_cast< RealT * >(mValue); };
    
        public:
            
            static INLINE std::shared_ptr< RealCppReferenceValue > MakeValue(void * const value, const bool &locked = false) { return std::shared_ptr< RealCppReferenceValue >(new RealCppReferenceValue(value, locked)); };
            static INLINE std::shared_ptr< RealCppReferenceValue > MakeValue(RealT &value, const bool &locked = false) { return std::shared_ptr< RealCppReferenceValue >(new RealCppReferenceValue(value, locked)); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Copy() const;
        
    };
    
    class StringCppReferenceValue : public StringValueBase
    {
        private:
            void * const mValue;
            
        protected:
            StringCppReferenceValue(void * const value, const bool &locked = false);
            StringCppReferenceValue(StringT &value, const bool &locked = false);
        
            //  From StringValueBase
            
            virtual const StringT &value() const { return *reinterpret_cast< StringT * >(mValue); };
            virtual StringT &value() { return *reinterpret_cast< StringT * >(mValue); };
    
        public:
            
            static INLINE std::shared_ptr< StringCppReferenceValue > MakeValue(void * const value, const bool &locked = false) { return std::shared_ptr< StringCppReferenceValue >(new StringCppReferenceValue(value, locked)); };
            static INLINE std::shared_ptr< StringCppReferenceValue > MakeValue(StringT &value, const bool &locked = false) { return std::shared_ptr< StringCppReferenceValue >(new StringCppReferenceValue(value, locked)); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Copy() const;
        
    };
    
    class ArrayCppReferenceValue : public iAtomic
    {
        private:
            const IntegerT mNumElements;
            void * const mValues;
            std::shared_ptr< iCppReferenceType > mType;
                  
        protected:
            ArrayCppReferenceValue(const IntegerT n, void * const values, std::shared_ptr< iCppReferenceType > type, const bool &locked = false);
                  
        public:
            
            static INLINE std::shared_ptr< ArrayCppReferenceValue > MakeValue(const IntegerT n, void * const value, std::shared_ptr< iCppReferenceType > type, const bool &locked = false) { return std::shared_ptr< ArrayCppReferenceValue >(new ArrayCppReferenceValue(n, value, type, locked)); };
            
            //  From iAtomic
            
            virtual iAtomic::TypeT Type() const throw();
            
            virtual std::shared_ptr< iAtomic > Copy() const;
            
            virtual std::shared_ptr< iAtomic > Member(const std::string &member) const;
            
            virtual IntegerT Add(std::shared_ptr< iAtomic > element);
            virtual IntegerT Add(std::shared_ptr< iAtomic > element, const IntegerT &index);
            virtual std::shared_ptr< iAtomic > Element(const IntegerT &index) const;
            virtual void Swap(const IntegerT &a, const IntegerT &b);
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
            
    };
    
    class IntegerVectorCppReferenceValue : public iAtomic
    {
        public:
        
            using VectorT = std::vector< IntegerT >;
    
        private:
            VectorT &mValues;
                  
        protected:
            INLINE IntegerVectorCppReferenceValue(VectorT &vec, const bool &locked = false) : iAtomic(locked), mValues(vec) {};
                  
        public:
            
            static INLINE std::shared_ptr< iAtomic > MakeValue(VectorT &vec, const bool &locked = false) { return std::shared_ptr< iAtomic >(new IntegerVectorCppReferenceValue(vec, locked)); };
            
            //  From iAtomic
            
            virtual iAtomic::TypeT Type() const throw();
            
            virtual std::shared_ptr< iAtomic > Copy() const;
            
            virtual std::shared_ptr< iAtomic > Member(const std::string &member) const;
            
            virtual IntegerT Add(std::shared_ptr< iAtomic > element);
            virtual IntegerT Add(std::shared_ptr< iAtomic > element, const IntegerT &index);
            virtual std::shared_ptr< iAtomic > Element(const IntegerT &index) const;
            virtual void Swap(const IntegerT &a, const IntegerT &b);
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
            
    };
    
    class RealVectorCppReferenceValue : public iAtomic
    {
        public:
        
            using VectorT = std::vector< RealT >;
    
        private:
            VectorT &mValues;
                  
        protected:
            INLINE RealVectorCppReferenceValue(VectorT &vec, const bool &locked = false) : iAtomic(locked), mValues(vec) {};
                  
        public:
            
            static INLINE std::shared_ptr< iAtomic > MakeValue(VectorT &vec, const bool &locked = false) { return std::shared_ptr< iAtomic >(new RealVectorCppReferenceValue(vec, locked)); };
            
            //  From iAtomic
            
            virtual iAtomic::TypeT Type() const throw();
            
            virtual std::shared_ptr< iAtomic > Copy() const;
            
            virtual std::shared_ptr< iAtomic > Member(const std::string &member) const;
            
            virtual IntegerT Add(std::shared_ptr< iAtomic > element);
            virtual IntegerT Add(std::shared_ptr< iAtomic > element, const IntegerT &index);
            virtual std::shared_ptr< iAtomic > Element(const IntegerT &index) const;
            virtual void Swap(const IntegerT &a, const IntegerT &b);
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
            
    };
    
    class StringVectorCppReferenceValue : public iAtomic
    {
        public:
        
            using VectorT = std::vector< StringT >;
    
        private:
            VectorT &mValues;
                  
        protected:
            INLINE StringVectorCppReferenceValue(VectorT &vec, const bool &locked = false) : iAtomic(locked), mValues(vec) {};
                  
        public:
            
            static INLINE std::shared_ptr< iAtomic > MakeValue(VectorT &vec, const bool &locked = false) { return std::shared_ptr< iAtomic >(new StringVectorCppReferenceValue(vec, locked)); };
            
            //  From iAtomic
            
            virtual iAtomic::TypeT Type() const throw();
            
            virtual std::shared_ptr< iAtomic > Copy() const;
            
            virtual std::shared_ptr< iAtomic > Member(const std::string &member) const;
            
            virtual IntegerT Add(std::shared_ptr< iAtomic > element);
            virtual IntegerT Add(std::shared_ptr< iAtomic > element, const IntegerT &index);
            virtual std::shared_ptr< iAtomic > Element(const IntegerT &index) const;
            virtual void Swap(const IntegerT &a, const IntegerT &b);
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
            
    };
    
    class StructureCppReferenceValue : public iAtomic
    {
        public:
        
            using MemberSetT = std::map< std::string, std::shared_ptr< iAtomic > >;
    
        private:
            void * const mValue;
            
            MemberSetT mMembers;
        
        public:
            StructureCppReferenceValue(void * const ptr, const bool &locked = false);
            
            void AddMember(const std::string &member, std::shared_ptr< iAtomic > value);
            INLINE void AddMember(const std::string &member, BooleanT &value) { AddMember(member, BooleanCppReferenceValue::MakeValue(value)); };
            INLINE void AddMember(const std::string &member, IntegerT &value) { AddMember(member, IntegerCppReferenceValue::MakeValue(value)); };
            INLINE void AddMember(const std::string &member, RealT &value) { AddMember(member, RealCppReferenceValue::MakeValue(value)); };
            INLINE void AddMember(const std::string &member, StringT &value) { AddMember(member, StringCppReferenceValue::MakeValue(value)); };
            
            //  From iAtomic
            
            virtual void Lock() throw();
            
            virtual TypeT Type() const throw();
            
            virtual std::shared_ptr< iAtomic > Copy() const;
            
            virtual std::shared_ptr< iAtomic > Member(const std::string &member) const;
            
    };
    
    ////////////////////////////////////////////////////////////////////////////
    
    class ExecutableCppValue : public ExecutableAtomic
    {
        public:
        
            using ArgumentListT = std::vector< std::shared_ptr< iAtomic > >;
    
        protected:
            std::shared_ptr< iAtomic > call(LanguageSymbolTable &symtab, const std::string &fid, const ArgumentListT &args) const;
            
            INLINE std::shared_ptr< iAtomic > call(LanguageSymbolTable &symtab, const std::string &fid, std::shared_ptr< iAtomic > arg1) const { return call(symtab, fid, ArgumentListT( { arg1 } )); };
            INLINE std::shared_ptr< iAtomic > call(LanguageSymbolTable &symtab, const std::string &fid, std::shared_ptr< iAtomic > arg1, std::shared_ptr< iAtomic > arg2) const { return call(symtab, fid, ArgumentListT( { arg1, arg2 } )); };
            INLINE std::shared_ptr< iAtomic > call(LanguageSymbolTable &symtab, const std::string &fid, std::shared_ptr< iAtomic > arg1, std::shared_ptr< iAtomic > arg2, std::shared_ptr< iAtomic > arg3) const { return call(symtab, fid, ArgumentListT( { arg1, arg2, arg3 } )); };
            INLINE std::shared_ptr< iAtomic > call(LanguageSymbolTable &symtab, const std::string &fid, std::shared_ptr< iAtomic > arg1, std::shared_ptr< iAtomic > arg2, std::shared_ptr< iAtomic > arg3, std::shared_ptr< iAtomic > arg4) const { return call(symtab, fid, ArgumentListT( { arg1, arg2, arg3, arg4 } )); };
            INLINE std::shared_ptr< iAtomic > call(LanguageSymbolTable &symtab, const std::string &fid, std::shared_ptr< iAtomic > arg1, std::shared_ptr< iAtomic > arg2, std::shared_ptr< iAtomic > arg3, std::shared_ptr< iAtomic > arg4, std::shared_ptr< iAtomic > arg5) const { return call(symtab, fid, ArgumentListT( { arg1, arg2, arg3, arg4, arg5 } )); };
        
        public:
            INLINE ExecutableCppValue() : ExecutableAtomic() {};
        
    };
    
    class DishMachine
    {
        public:
        
            using ArgumentListT = std::vector< std::shared_ptr< iAtomic > >;
    
        private:
            std::shared_ptr< LanguageSymbolTable > mSymbolTable;
        
        public:
            INLINE DishMachine() : mSymbolTable(new LanguageSymbolTable(StackedSymbolTable::INFINITE_STACK_DEPTH)) {};
            INLINE DishMachine(const int maxdepth) : mSymbolTable(new LanguageSymbolTable(maxdepth)) {};
            INLINE DishMachine(std::shared_ptr< LanguageSymbolTable > symtab);
            
            INLINE void Parse(const std::string &source, const bool finput) { Parser(mSymbolTable, source, finput).Run(); };
            INLINE void ParseFile(const std::string &source) { Parse(source, FILE_INPUT); };
            INLINE void ParseString(const std::string &source) { Parse(source, STRING_INPUT); };
            
            INLINE const LanguageSymbolTable &SymbolTable() const { return *mSymbolTable; };
            INLINE LanguageSymbolTable &SymbolTable() { return *mSymbolTable; };
            
            std::shared_ptr< iAtomic > Call(const std::string &fid, const ArgumentListT &args) const;
            
            INLINE std::shared_ptr< iAtomic > Call(const std::string &fid, std::shared_ptr< iAtomic > arg1) const { return Call(fid, ArgumentListT( { arg1 } )); };
            INLINE std::shared_ptr< iAtomic > Call(const std::string &fid, std::shared_ptr< iAtomic > arg1, std::shared_ptr< iAtomic > arg2) const { return Call(fid, ArgumentListT( { arg1, arg2 } )); };
            INLINE std::shared_ptr< iAtomic > Call(const std::string &fid, std::shared_ptr< iAtomic > arg1, std::shared_ptr< iAtomic > arg2, std::shared_ptr< iAtomic > arg3) const { return Call(fid, ArgumentListT( { arg1, arg2, arg3 } )); };
            INLINE std::shared_ptr< iAtomic > Call(const std::string &fid, std::shared_ptr< iAtomic > arg1, std::shared_ptr< iAtomic > arg2, std::shared_ptr< iAtomic > arg3, std::shared_ptr< iAtomic > arg4) const { return Call(fid, ArgumentListT( { arg1, arg2, arg3, arg4 } )); };
            INLINE std::shared_ptr< iAtomic > Call(const std::string &fid, std::shared_ptr< iAtomic > arg1, std::shared_ptr< iAtomic > arg2, std::shared_ptr< iAtomic > arg3, std::shared_ptr< iAtomic > arg4, std::shared_ptr< iAtomic > arg5) const { return Call(fid, ArgumentListT( { arg1, arg2, arg3, arg4, arg5 } )); };
        
    };

    ////////////////////////////////////////////////////////////////////////////

}

#endif

