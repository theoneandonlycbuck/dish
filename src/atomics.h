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

#ifndef DISH_ATOMICS_H
#define DISH_ATOMICS_H

#include "dishconfig.h"

#ifndef LANG_FORMAL_PARAM_LIST_TYPE_VECTOR
#include <list>
#endif

#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "inline.h"
#include "isymtab.h"
#include "language.h"
#include "symtab.h"
#include "types.h"
#include "utility.h"

namespace dish
{

    ////////////////////////////////////////////////////////////////////////////
    
    class iAtomic;
    class iSymbolTable;

    ////////////////////////////////////////////////////////////////////////////
    
    extern const bool UNLOCKED;
    extern const bool LOCKED;
    
    extern const bool REFERENCE_PARAMETER;
    extern const bool VALUE_PARAMETER;
    
    class iValueAtomic
    {
        public:
            virtual ~iValueAtomic() {};
            
            virtual const bool &IsLocked() const throw() = 0;
            virtual void Lock() throw() = 0;
            
            virtual BooleanT AsBoolean() const = 0;
            virtual IntegerT AsInteger() const = 0;
            virtual RealT AsReal() const = 0;
            virtual StringT AsString() const = 0;
            
            virtual void Assign(std::shared_ptr< iAtomic > rhs) = 0;
            virtual void Assign(const iValueAtomic &rhs) = 0;
            virtual void Assign(const BooleanT &rhs) = 0;
            virtual void Assign(const IntegerT &rhs) = 0;
            virtual void Assign(const RealT &rhs) = 0;
            virtual void Assign(const StringT &rhs) = 0;
            
            INLINE const iValueAtomic &operator=(const iValueAtomic &rhs) { Assign(rhs); return *this; };
            
    };
    
    class iStructureAtomic
    {
        public:
        
            using MemberNameSetT = std::vector< std::string >;
        
            virtual ~iStructureAtomic() {};
            
            virtual IntegerT Members(MemberNameSetT &members) const = 0;
            virtual std::shared_ptr< iAtomic > Member(const std::string &member) const = 0;
    
    };
    
    class iArrayAtomic
    {
        public:
            virtual ~iArrayAtomic() {};
            
            virtual IntegerT Add(std::shared_ptr< iAtomic > element) = 0;
            virtual IntegerT Add(std::shared_ptr< iAtomic > element, const IntegerT &index) = 0;
            
            virtual std::shared_ptr< iAtomic > Element(const IntegerT &index) const = 0;
            virtual void Swap(const IntegerT &a, const IntegerT &b) = 0;
        
    };
    
    class iDictionaryAtomic
    {
        public:
            virtual ~iDictionaryAtomic() {};
            
            virtual IntegerT Add(std::shared_ptr< iAtomic > key, std::shared_ptr< iAtomic > value) = 0;
            
            virtual std::shared_ptr< iAtomic > Keys() const = 0;
            
            virtual std::shared_ptr< iAtomic > Lookup(const StringT &key) const = 0;
        
    };
    
    class iTypeAtomic
    {
        public:
        
            using RangeCapT = enum
            {
                capNull = 0,
                
                capCap,
                capRollover,
                capError
            };
            
            virtual ~iTypeAtomic() {};
            
            virtual std::shared_ptr< iAtomic > Declare() const = 0;
        
    };
    
    class iExecutableAtomic
    {
        public:
        
            ////
            
#ifdef LIST_TYPE_PREFER_VECTOR
            using ParamListT = std::vector< std::pair< std::string, bool > >;
#else
            using ParamListT = std::list< std::pair< std::string, bool > >;
#endif

            ////
            
            class ReturnValue
            {
                private:
                    std::shared_ptr< iAtomic > mValue;
                
                public:
                    INLINE ReturnValue(std::shared_ptr< iAtomic > &value) : mValue(value) {};
                    INLINE ReturnValue(const ReturnValue &ret) : mValue(ret.mValue) {};
                    
                    INLINE std::shared_ptr< iAtomic > Value() const { return mValue; };
                    
                    INLINE const ReturnValue &operator=(const ReturnValue &rhs) { mValue = rhs.mValue; return *this; };
                
            };
        
            ////
            
            virtual ~iExecutableAtomic() {};
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const = 0;
            virtual const ParamListT &ParameterList() const = 0;
            virtual IntegerT NumParameters() const = 0;
        
    };
    
    class iAtomic : 
        public iValueAtomic, 
        public iStructureAtomic,
        public iArrayAtomic,
        public iDictionaryAtomic,
        public iTypeAtomic,
        public iExecutableAtomic,
        
        public iPrintable
    {
        public:
            
            typedef enum
            {
                typeNull = 0,
            
                typeType,
                
                typeBoolean,
                typeInteger,
                typeReal,
                typeString,
                
                typeArray,
                typeDictionary,
                typeStructure,
                
                typeExecutable,
                
                typeNUM
            } TypeT;
            
            typedef enum
            {
                rngbndError = 0,
                
                rngbndCap,
                rngbndRollover
            } RangeBoundsT;
            
        private:
            bool mLocked;
            
        protected:
        
            virtual std::shared_ptr< iAtomic > memberBytes() const;
            virtual std::shared_ptr< iAtomic > memberMinimum() const;
            virtual std::shared_ptr< iAtomic > memberMaximum() const;
            virtual std::shared_ptr< iAtomic > memberEps() const;
    
        public:
            INLINE iAtomic() : iValueAtomic(), iStructureAtomic(), iArrayAtomic(), iDictionaryAtomic(), iTypeAtomic(), iExecutableAtomic(), iPrintable(), mLocked(false) {};
            INLINE iAtomic(const bool &locked) : iValueAtomic(), iStructureAtomic(), iArrayAtomic(), iDictionaryAtomic(), iTypeAtomic(), iExecutableAtomic(), iPrintable(), mLocked(locked) {};
            INLINE iAtomic(const iAtomic &value) : iValueAtomic(), iStructureAtomic(), iArrayAtomic(), iDictionaryAtomic(), iTypeAtomic(), iExecutableAtomic(), iPrintable(), mLocked(value.mLocked) {};
            
            virtual TypeT Type() const throw() = 0;
            
            virtual std::shared_ptr< iAtomic > Copy() const = 0;                //  A modifiable (non-locked) deep-copy of the object
            virtual std::shared_ptr< iAtomic > Clone() const;                   //  A deep copy of the object, including locked status
            
            //  From iValueAtomic
            
            virtual const bool &IsLocked() const throw();
            virtual void Lock() throw();
            
            virtual BooleanT AsBoolean() const;
            virtual IntegerT AsInteger() const;
            virtual RealT AsReal() const;
            virtual StringT AsString() const;
            
            virtual void Assign(std::shared_ptr< iAtomic > rhs);
            virtual void Assign(const iValueAtomic &rhs);
            virtual void Assign(const BooleanT &rhs);
            virtual void Assign(const IntegerT &rhs);
            virtual void Assign(const RealT &rhs);
            virtual void Assign(const StringT &rhs);
            
            //  From iStructureAtomic
            
            virtual IntegerT Members(MemberNameSetT &members) const;
            virtual std::shared_ptr< iAtomic > Member(const std::string &member) const;
            
            //  From iArrayAtomic
            
            virtual IntegerT Add(std::shared_ptr< iAtomic > element);
            virtual IntegerT Add(std::shared_ptr< iAtomic > element, const IntegerT &index);
            virtual std::shared_ptr< iAtomic > Element(const IntegerT &index) const;
            virtual void Swap(const IntegerT &a, const IntegerT &b);
            
            //  From iDictionary
            
            virtual IntegerT Add(std::shared_ptr< iAtomic > key, std::shared_ptr< iAtomic > value);
            virtual std::shared_ptr< iAtomic > Keys() const;
            virtual std::shared_ptr< iAtomic > Lookup(const StringT &key) const;
            
            //  From iTypeAtomic
            
            virtual std::shared_ptr< iAtomic > Declare() const;
            
            //  From iExecutableAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            virtual const ParamListT &ParameterList() const;
            virtual IntegerT NumParameters() const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
            
    };
    
    extern void AssertIs(std::shared_ptr< iAtomic > atomic, const iAtomic::TypeT &type);
    
    INLINEC void AssertIsType(std::shared_ptr< iAtomic > atomic) { AssertIs(atomic, iAtomic::typeType); };
    INLINEC void AssertIsBoolean(std::shared_ptr< iAtomic > atomic) { AssertIs(atomic, iAtomic::typeBoolean); };
    INLINEC void AssertIsInteger(std::shared_ptr< iAtomic > atomic) { AssertIs(atomic, iAtomic::typeInteger); };
    INLINEC void AssertIsReal(std::shared_ptr< iAtomic > atomic) { AssertIs(atomic, iAtomic::typeReal); };
    INLINEC void AssertIsString(std::shared_ptr< iAtomic > atomic) { AssertIs(atomic, iAtomic::typeString); };
    INLINEC void AssertIsArray(std::shared_ptr< iAtomic > atomic) { AssertIs(atomic, iAtomic::typeArray); };
    INLINEC void AssertIsDictionary(std::shared_ptr< iAtomic > atomic) { AssertIs(atomic, iAtomic::typeDictionary); };
    INLINEC void AssertIsStructure(std::shared_ptr< iAtomic > atomic) { AssertIs(atomic, iAtomic::typeStructure); };
    
    extern std::ostream &operator<<(std::ostream &out, const iAtomic::TypeT &type);
    
    ////////////////////////////////////////////////////////////////////////////
    
    class TypeAtomic : public iAtomic
    {
        private:
            mutable IntegerT mNumInstances;
            
        protected:
            INLINE TypeAtomic() : iAtomic(LOCKED), mNumInstances(0) {};
        
            INLINE void declare() const throw() { ++mNumInstances; };
    
        public:
            
            //  From iAtomic
            
            virtual TypeT Type() const throw();
            
            virtual std::shared_ptr< iAtomic > Member(const std::string &member) const;
            
    };
    
    ////
    
    class BooleanTypeAtomic : public TypeAtomic
    {
        private:
            const BooleanT mInitialValue;
        
            static IntegerT Count;
            
        protected:
            INLINE BooleanTypeAtomic(const BooleanT &value = false) : TypeAtomic(), mInitialValue(value) { ++Count; };
    
        public:
        
            static INLINE IntegerT NumInstances() throw() { return Count; };
            
            static INLINE std::shared_ptr< BooleanTypeAtomic > MakeValue(const BooleanT &value = false) { return std::shared_ptr< BooleanTypeAtomic >(new BooleanTypeAtomic(value)); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Copy() const;
            
            virtual std::shared_ptr< iAtomic > Declare() const;
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
            
    };
    
    ////
    
    class IntegerTypeAtomic : public TypeAtomic
    {
        private:
            const IntegerT mInitialValue;
        
            static IntegerT Count;
            
        protected:
            INLINE IntegerTypeAtomic(const IntegerT &value = 0) : TypeAtomic(), mInitialValue(value) { ++Count; };
    
        public:
        
            static INLINE IntegerT NumInstances() throw() { return Count; };
            
            static INLINE std::shared_ptr< IntegerTypeAtomic > MakeValue(const IntegerT &value = 0) { return std::shared_ptr< IntegerTypeAtomic >(new IntegerTypeAtomic(value)); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Copy() const;
            
            virtual std::shared_ptr< iAtomic > Declare() const;
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
            
    };
    
    class RangedIntegerTypeAtomic : public TypeAtomic
    {
        private:
            const IntegerT mMinimumRange;
            const IntegerT mMaximumRange;
            const RangeBoundsT mRangeBoundary;
        
            const IntegerT mInitialValue;
        
            static IntegerT Count;
            
        protected:
            INLINE RangedIntegerTypeAtomic(const IntegerT &min, const IntegerT &max, const RangeBoundsT &bounds, const IntegerT &value = 0) : TypeAtomic(), mMinimumRange(min), mMaximumRange(max), mRangeBoundary(bounds), mInitialValue(value) { assert(mMinimumRange <= mMaximumRange); ++Count; };
    
        public:
        
            static INLINE IntegerT NumInstances() throw() { return Count; };
            
            static INLINE std::shared_ptr< RangedIntegerTypeAtomic > MakeValue(const IntegerT &min, const IntegerT &max, const RangeBoundsT &bounds, const IntegerT &value = 0) { return std::shared_ptr< RangedIntegerTypeAtomic >(new RangedIntegerTypeAtomic(min, max, bounds, value)); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Copy() const;
            
            virtual std::shared_ptr< iAtomic > Declare() const;
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
            
    };
    
    ////
    
    class RealTypeAtomic : public TypeAtomic
    {
        private:
            const RealT mInitialValue;
        
            static IntegerT Count;
            
        protected:
            INLINE RealTypeAtomic(const RealT &value = 0.0) : TypeAtomic(), mInitialValue(value) { ++Count; };
    
        public:
        
            static INLINE IntegerT NumInstances() throw() { return Count; };
            
            static INLINE std::shared_ptr< RealTypeAtomic > MakeValue(const RealT &value = 0.0) { return std::shared_ptr< RealTypeAtomic >(new RealTypeAtomic(value)); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Copy() const;
            
            virtual std::shared_ptr< iAtomic > Declare() const;
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
            
    };
    
    class RangedRealTypeAtomic : public TypeAtomic
    {
        private:
            const RealT mMinimumRange;
            const RealT mMaximumRange;
            const RangeBoundsT mRangeBoundary;
        
            const RealT mInitialValue;
        
            static IntegerT Count;
            
        protected:
            INLINE RangedRealTypeAtomic(const RealT &min, const RealT &max, const RangeBoundsT &bounds, const RealT &value = 0) : TypeAtomic(), mMinimumRange(min), mMaximumRange(max), mRangeBoundary(bounds), mInitialValue(value) { assert((mMinimumRange <= mMaximumRange) || IsEqual(mMinimumRange, mMaximumRange)); ++Count; };
    
        public:
        
            static INLINE IntegerT NumInstances() throw() { return Count; };
            
            static INLINE std::shared_ptr< RangedRealTypeAtomic > MakeValue(const RealT &min, const RealT &max, const RangeBoundsT &bounds, const RealT &value = 0) { return std::shared_ptr< RangedRealTypeAtomic >(new RangedRealTypeAtomic(min, max, bounds, value)); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Copy() const;
            
            virtual std::shared_ptr< iAtomic > Declare() const;
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
            
    };
    
    ////
    
    class StringTypeAtomic : public TypeAtomic
    {
        private:
            const StringT mInitialValue;
        
            static IntegerT Count;
            
        protected:
            INLINE StringTypeAtomic(const StringT &value = "") : TypeAtomic(), mInitialValue(value) { ++Count; };
    
        public:
        
            static INLINE IntegerT NumInstances() throw() { return Count; };
            
            static INLINE std::shared_ptr< StringTypeAtomic > MakeValue(const StringT &value = "") { return std::shared_ptr< StringTypeAtomic >(new StringTypeAtomic(value)); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Copy() const;
            
            virtual std::shared_ptr< iAtomic > Declare() const;
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
            
    };
    
    class ArrayTypeAtomic : public TypeAtomic
    {
        private:
            const IntegerT mMinimumIndex;
            const IntegerT mMaximumIndex;
            
            std::shared_ptr< iAtomic > mType;
        
            static IntegerT Count;
            
        protected:
            INLINE ArrayTypeAtomic(const IntegerT &min) : TypeAtomic(), mMinimumIndex(min), mMaximumIndex(min), mType(0) { ++Count; };
            ArrayTypeAtomic(const IntegerT &min, const IntegerT &max, std::shared_ptr< iAtomic > type);
    
        public:
        
            static INLINE IntegerT NumInstances() throw() { return Count; };
            
            static INLINE std::shared_ptr< ArrayTypeAtomic > MakeValue(const IntegerT &min) { return std::shared_ptr< ArrayTypeAtomic >(new ArrayTypeAtomic(min)); };
            static INLINE std::shared_ptr< ArrayTypeAtomic > MakeValue(const IntegerT &min, const IntegerT &max, std::shared_ptr< iAtomic > type) { return std::shared_ptr< ArrayTypeAtomic >(new ArrayTypeAtomic(min, max, type)); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Copy() const;
            
            virtual std::shared_ptr< iAtomic > Declare() const;
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class DictionaryTypeAtomic : public TypeAtomic
    {
        protected:
            INLINE DictionaryTypeAtomic() : TypeAtomic() { ++Count; };
        
            static IntegerT Count;
    
        public:
        
            static INLINE IntegerT NumInstances() throw() { return Count; };
            
            static INLINE std::shared_ptr< DictionaryTypeAtomic > MakeValue() { return std::shared_ptr< DictionaryTypeAtomic >(new DictionaryTypeAtomic()); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Copy() const;
            
            virtual std::shared_ptr< iAtomic > Declare() const;
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class StructureTypeAtomic : public TypeAtomic
    {
        public:
        
#ifdef LIST_TYPE_PREFER_VECTOR
            using MemberListT = std::vector< std::pair< std::string, std::shared_ptr< iAtomic > > >;
#else
            using MemberListT = std::list< std::pair< std::string, std::shared_ptr< iAtomic > > >;
#endif
        
            static IntegerT Count;
    
        private:
            MemberListT mMemberList;
            
        protected:
            INLINE StructureTypeAtomic() : TypeAtomic(), mMemberList()
            { 
                ++Count;
            
#ifdef LIST_TYPE_PREFER_VECTOR
                mMemberList.reserve(LIST_TYPE_PREFER_VECTOR);
#endif
            };
        
        public:
        
            static INLINE IntegerT NumInstances() throw() { return Count; };
            
            static INLINE std::shared_ptr< StructureTypeAtomic > MakeValue() { return std::shared_ptr< StructureTypeAtomic >(new StructureTypeAtomic()); };
            
            void Add(const std::string &id, std::shared_ptr< iAtomic > type);
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Copy() const;
            
            virtual std::shared_ptr< iAtomic > Declare() const;
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class NullValue : public iAtomic
    {
        private:
        
            static std::shared_ptr< NullValue > Value;
        
            static IntegerT Count;
    
        protected:
            INLINE NullValue() : iAtomic(LOCKED) { ++Count; };
    
        public:
        
            static INLINE IntegerT NumInstances() throw() { return Count; };
        
            static INLINE std::shared_ptr< NullValue > MakeValue() { return Value; };
        
            //  From iAtomic
            
            virtual TypeT Type() const throw();
            
            virtual std::shared_ptr< iAtomic > Copy() const;
            
            virtual StringT AsString() const;
            
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class ExecutableAtomic : public iAtomic
    {
        private:
            ParamListT mParamList;
        
            static IntegerT Count;
    
        protected:
            INLINE ExecutableAtomic() : iAtomic(LOCKED), mParamList()
            { 
                ++Count;
                
#ifdef LIST_TYPE_PREFER_VECTOR
                mParamList.reserve(LIST_TYPE_PREFER_VECTOR);
#endif
            };
        
            INLINE void addParam(const std::string &param, const bool &ref) { mParamList.push_back(std::make_pair(param, ref)); };
        
            static INLINE std::shared_ptr< iAtomic > getParam(iSymbolTable &symtab, const std::string &id) { return symtab.Lookup(id); };
            
        public:
        
            static INLINE IntegerT NumInstances() throw() { return Count; };
            
            void AddParam(const std::string &param, const bool &ref);
            void AddParam(const ParamListT &params);
            
            //  From iAtomic
            
            virtual TypeT Type() const throw();
            
            virtual std::shared_ptr< iAtomic > Copy() const;
            virtual std::shared_ptr< iAtomic > Clone() const;
            
            virtual StringT AsString() const;
            
            virtual const ParamListT &ParameterList() const;
            virtual IntegerT NumParameters() const;
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class ReferenceValue : public iAtomic
    {
        private:
            std::shared_ptr< iAtomic > mValue;
        
            static IntegerT Count;
            
        protected:
            INLINE ReferenceValue(std::shared_ptr< iAtomic > value) : iAtomic(value->IsLocked()), mValue(value) { ++Count; };
        
        public:
        
            static INLINE IntegerT NumInstances() throw() { return Count; };
            
            static INLINE std::shared_ptr< ReferenceValue > MakeValue(std::shared_ptr< iAtomic > value) { return std::shared_ptr< ReferenceValue >(new ReferenceValue(value)); };
            
            //  From iAtomic
            
            virtual void Lock() throw();
            
            virtual TypeT Type() const throw();
            
            virtual std::shared_ptr< iAtomic > Copy() const;
            virtual std::shared_ptr< iAtomic > Clone() const;
            
            virtual BooleanT AsBoolean() const;
            virtual IntegerT AsInteger() const;
            virtual RealT AsReal() const;
            virtual StringT AsString() const;
            
            virtual void Assign(std::shared_ptr< iAtomic > rhs);
            virtual void Assign(const iValueAtomic &rhs);
            virtual void Assign(const BooleanT &rhs);
            virtual void Assign(const IntegerT &rhs);
            virtual void Assign(const RealT &rhs);
            virtual void Assign(const StringT &rhs);
            
            virtual std::shared_ptr< iAtomic > Member(const std::string &member) const;
            
            virtual IntegerT Add(std::shared_ptr< iAtomic > element);
            virtual IntegerT Add(std::shared_ptr< iAtomic > element, const IntegerT &index);
            virtual std::shared_ptr< iAtomic > Element(const IntegerT &index) const;
            
            virtual IntegerT Add(std::shared_ptr< iAtomic > key, std::shared_ptr< iAtomic > value);
            virtual std::shared_ptr< iAtomic > Keys() const;
            virtual std::shared_ptr< iAtomic > Lookup(const StringT &key) const;
            
            virtual std::shared_ptr< iAtomic > Declare() const;
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            virtual const ParamListT &ParameterList() const;
            virtual IntegerT NumParameters() const;
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    ////
    
    class BooleanValueBase : public iAtomic
    {
        private:
        
            static IntegerT Count;
    
        protected:
            INLINE BooleanValueBase(const bool &locked = UNLOCKED) : iAtomic(locked) { ++Count; };
            
            virtual const BooleanT &value() const = 0;
            virtual BooleanT &value() = 0;
            
            //  From iAtomic
        
            virtual std::shared_ptr< iAtomic > memberBytes() const;
            virtual std::shared_ptr< iAtomic > memberMinimum() const;
            virtual std::shared_ptr< iAtomic > memberMaximum() const;
    
        public:
        
            static INLINE IntegerT NumInstances() throw() { return Count; };
            
            //  From iAtomic
            
            virtual TypeT Type() const throw();
            
            virtual BooleanT AsBoolean() const;
            virtual IntegerT AsInteger() const;
            virtual StringT AsString() const;
            
            virtual void Assign(std::shared_ptr< iAtomic > rhs);
            virtual void Assign(const iValueAtomic &rhs);
            virtual void Assign(const BooleanT &rhs);
            virtual void Assign(const IntegerT &rhs);
        
    };
    
    class BooleanValue : public BooleanValueBase
    {
        private:
            BooleanT mValue;
            
#ifdef RECYCLE_PRIMITIVES
            static BufferStack< void * > ObjectCache;
#endif

            static std::shared_ptr< BooleanValue > Values[2];
        
        protected:
            INLINE BooleanValue() : BooleanValueBase(), mValue(false) {};
            INLINE BooleanValue(const BooleanT &value, const bool &locked = UNLOCKED) : BooleanValueBase(locked), mValue(value) {};
        
            //  From BooleanValueBase
        
            virtual const BooleanT &value() const { return mValue; };
            virtual BooleanT &value() { return mValue; };
        
        public:
                
            static INLINE std::shared_ptr< BooleanValue > MakeLockedValue(const BooleanT &value) { return Values[static_cast< int >(value)]; };
            static INLINE std::shared_ptr< BooleanValue > MakeUnlockedValue(const BooleanT &value) { return std::shared_ptr< BooleanValue >(new BooleanValue(value, UNLOCKED)); };
            
            static INLINE std::shared_ptr< BooleanValue > MakeValue() { return std::shared_ptr< BooleanValue >(new BooleanValue()); };
            static INLINE std::shared_ptr< BooleanValue > MakeValue(const BooleanT &value, const bool &locked = false) { return (locked ? MakeLockedValue(value) : MakeUnlockedValue(value)); };
            
#ifdef RECYCLE_PRIMITIVES
            static void *operator new(const std::size_t size);
            static void operator delete(void * const ptr, const std::size_t size) throw();
            static void Destroy() throw();
#endif
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Copy() const;
            virtual std::shared_ptr< iAtomic > Clone() const;
        
    };
    
    ////
    
    class IntegerValueBase : public iAtomic
    {
        private:
        
            static IntegerT Count;
    
        protected:
            INLINE IntegerValueBase(const bool &locked = UNLOCKED) : iAtomic(locked) { ++Count; };
            
            virtual const IntegerT &value() const = 0;
            virtual IntegerT &value() = 0;
            
            //  From iAtomic
        
            virtual std::shared_ptr< iAtomic > memberBytes() const;
            virtual std::shared_ptr< iAtomic > memberMinimum() const;
            virtual std::shared_ptr< iAtomic > memberMaximum() const;
            virtual std::shared_ptr< iAtomic > memberEps() const;
    
        public:
        
            static INLINE IntegerT NumInstances() throw() { return Count; };
            
            //  From iAtomic
            
            virtual TypeT Type() const throw();
            
            virtual BooleanT AsBoolean() const;
            virtual IntegerT AsInteger() const;
            virtual RealT AsReal() const;
            virtual StringT AsString() const;
            
            virtual void Assign(std::shared_ptr< iAtomic > rhs);
            virtual void Assign(const iValueAtomic &rhs);
            virtual void Assign(const BooleanT &rhs);
            virtual void Assign(const IntegerT &rhs);
        
    };
    
    class IntegerValue : public IntegerValueBase
    {
        public:
        
            using ValueTableT = std::vector< std::pair< IntegerT, std::shared_ptr< IntegerValue > > >;
    
            static const IntegerT CONSTANT_INTEGER_VALUES_MIN_INDEX;
            static const IntegerT CONSTANT_INTEGER_VALUES_MAX_INDEX;
    
        private:
            IntegerT mValue;
            
            static ValueTableT ValueTable;
            
#ifdef RECYCLE_PRIMITIVES
            static BufferStack< void * > ObjectCache;
#endif
        
        protected:
            INLINE IntegerValue() : IntegerValueBase(), mValue(0) {};
            INLINE IntegerValue(const IntegerT &value, const bool &locked = UNLOCKED) : IntegerValueBase(locked), mValue(value) {};
        
            //  From IntegerValueBase
        
            virtual const IntegerT &value() const { return mValue; };
            virtual IntegerT &value() { return mValue; };
    
        public:
            
            static std::shared_ptr< IntegerValue > MakeValue(const IntegerT &value, const bool &locked = UNLOCKED);
            static INLINE std::shared_ptr< IntegerValue > MakeValue() { return MakeValue(0, UNLOCKED); };
            
            static void PrintTableStatistics(std::ostream &out = std::cout);
            
#ifdef RECYCLE_PRIMITIVES
            static void *operator new(const std::size_t size);
            static void operator delete(void * const ptr, const std::size_t size) throw();
            static void Destroy() throw();
#endif
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Copy() const;
            virtual std::shared_ptr< iAtomic > Clone() const;
        
    };
    
    class RangedIntegerValue : public IntegerValueBase
    {
        private:
            const IntegerT mMinimumValue;
            const IntegerT mMaximumValue;
            const RangeBoundsT mRangeBounds;
            
            IntegerT mValue;
        
        protected:
            INLINE RangedIntegerValue(const IntegerT &min, const IntegerT &max, const RangeBoundsT &bound, const IntegerT &value, const bool &locked = UNLOCKED) : IntegerValueBase(locked), mMinimumValue(min), mMaximumValue(max), mRangeBounds(bound), mValue(value) { assert(mMinimumValue <= mMaximumValue); };
        
            void checkValue();
        
            //  From IntegerValueBase
        
            virtual const IntegerT &value() const { return mValue; };
            virtual IntegerT &value() { return mValue; };
    
        public:
            
            static INLINE std::shared_ptr< RangedIntegerValue > MakeValue(const IntegerT &min, const IntegerT &max, const RangeBoundsT &bound, const IntegerT &value, const bool &locked = UNLOCKED) { return std::shared_ptr< RangedIntegerValue >(new RangedIntegerValue(min, max, bound, value, locked)); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Copy() const;
            virtual std::shared_ptr< iAtomic > Clone() const;
            
            virtual void Assign(std::shared_ptr< iAtomic > rhs);
            virtual void Assign(const iValueAtomic &rhs);
            virtual void Assign(const BooleanT &rhs);
            virtual void Assign(const IntegerT &rhs);
        
    };
    
    ////
    
    class RealValueBase : public iAtomic
    {
        private:
        
            static IntegerT Count;
    
        protected:
            INLINE RealValueBase(const bool &locked = UNLOCKED) : iAtomic(locked) { ++Count; };
            
            virtual const RealT &value() const = 0;
            virtual RealT &value() = 0;
            
            //  From iAtomic
        
            virtual std::shared_ptr< iAtomic > memberBytes() const;
            virtual std::shared_ptr< iAtomic > memberMinimum() const;
            virtual std::shared_ptr< iAtomic > memberMaximum() const;
            virtual std::shared_ptr< iAtomic > memberEps() const;
    
        public:
            
            static INLINE IntegerT NumInstances() throw() { return Count; };
            
            //  From iAtomic
            
            virtual TypeT Type() const throw();
            
            virtual BooleanT AsBoolean() const;
            virtual IntegerT AsInteger() const;
            virtual RealT AsReal() const;
            virtual StringT AsString() const;
            
            virtual void Assign(std::shared_ptr< iAtomic > rhs);
            virtual void Assign(const iValueAtomic &rhs);
            virtual void Assign(const IntegerT &rhs);
            virtual void Assign(const RealT &rhs);
        
    };
    
    class RealValue : public RealValueBase
    {
        private:
            RealT mValue;
            
#ifdef RECYCLE_PRIMITIVES
            static BufferStack< void * > ObjectCache;
#endif
        
        protected:
            INLINE RealValue() : RealValueBase(), mValue(0.0) {};
            INLINE RealValue(const RealT &value, const bool &locked = UNLOCKED) : RealValueBase(locked), mValue(value) {};
        
            //  From RealValueBase
        
            virtual const RealT &value() const { return mValue; };
            virtual RealT &value() { return mValue; };
    
        public:
            
            static INLINE std::shared_ptr< RealValue > MakeValue() { return std::shared_ptr< RealValue >(new RealValue()); };
            static INLINE std::shared_ptr< RealValue > MakeValue(const RealT &value, const bool &locked = false) { return std::shared_ptr< RealValue >(new RealValue(value, locked)); };
            
#ifdef RECYCLE_PRIMITIVES
            static void *operator new(const std::size_t size);
            static void operator delete(void * const ptr, const std::size_t size) throw();
            static void Destroy() throw();
#endif
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Copy() const;
            virtual std::shared_ptr< iAtomic > Clone() const;
        
    };
    
    class RangedRealValue : public RealValueBase
    {
        private:
            const RealT mMinimumValue;
            const RealT mMaximumValue;
            const RangeBoundsT mRangeBounds;
            
            RealT mValue;
        
        protected:
            INLINE RangedRealValue(const RealT &min, const RealT &max, const RangeBoundsT &bound, const RealT &value, const bool &locked = UNLOCKED) : RealValueBase(locked), mMinimumValue(min), mMaximumValue(max), mRangeBounds(bound), mValue(value) { assert((mMinimumValue <= mMaximumValue) || IsEqual(mMinimumValue, mMaximumValue)); };
        
            void checkValue();
        
            //  From RealValueBase
        
            virtual const RealT &value() const { return mValue; };
            virtual RealT &value() { return mValue; };
    
        public:
            
            static INLINE std::shared_ptr< RangedRealValue > MakeValue(const IntegerT &min, const IntegerT &max, const RangeBoundsT &bound, const IntegerT &value, const bool &locked = UNLOCKED) { return std::shared_ptr< RangedRealValue >(new RangedRealValue(min, max, bound, value, locked)); };
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Copy() const;
            virtual std::shared_ptr< iAtomic > Clone() const;
            
            virtual void Assign(std::shared_ptr< iAtomic > rhs);
            virtual void Assign(const iValueAtomic &rhs);
            virtual void Assign(const BooleanT &rhs);
            virtual void Assign(const IntegerT &rhs);
        
    };
    
    ////
    
    class StringValueBase : public iAtomic
    {
        private:
            
            mutable std::shared_ptr< iAtomic > mFinishV;
            mutable std::shared_ptr< iAtomic > mLengthV;
        
            static IntegerT Count;
    
        protected:
            INLINE StringValueBase(const bool &locked = UNLOCKED) : iAtomic(locked), mFinishV(), mLengthV() { ++Count; };
            
            virtual const StringT &value() const = 0;
            virtual StringT &value() = 0;
            
            INLINE void invalidate() const { mFinishV.reset(); mLengthV.reset(); };
    
        public:
        
            static INLINE IntegerT NumInstances() throw() { return Count; };
            
            //  From iAtomic
            
            virtual TypeT Type() const throw();
            
            virtual BooleanT AsBoolean() const;
            virtual IntegerT AsInteger() const;
            virtual RealT AsReal() const;
            virtual StringT AsString() const;
            
            virtual void Assign(std::shared_ptr< iAtomic > rhs);
            virtual void Assign(const iValueAtomic &rhs);
            virtual void Assign(const StringT &rhs);
            
            virtual std::shared_ptr< iAtomic > Member(const std::string &member) const;
            
            virtual std::shared_ptr< iAtomic > Element(const IntegerT &index) const;
            virtual void Swap(const IntegerT &a, const IntegerT &b);
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class StringValue : public StringValueBase
    {
        private:
            StringT mValue;
            
#ifdef RECYCLE_PRIMITIVES
            static BufferStack< void * > ObjectCache;
#endif
        
        protected:
            INLINE StringValue() : StringValueBase(), mValue() {};
            INLINE StringValue(const StringT &value, const bool &locked = UNLOCKED) : StringValueBase(locked), mValue(value) {};
        
            //  From StringValueBase
        
            virtual const StringT &value() const { return mValue; };
            virtual StringT &value() { return mValue; };
    
        public:
            
            static INLINE std::shared_ptr< StringValue > MakeValue() { return std::shared_ptr< StringValue >(new StringValue()); };
            static INLINE std::shared_ptr< StringValue > MakeValue(const StringT &value, const bool &locked = false) { return std::shared_ptr< StringValue >(new StringValue(value, locked)); };
            
#ifdef RECYCLE_PRIMITIVES
            static void *operator new(const std::size_t size);
            static void operator delete(void * const ptr, const std::size_t size) throw();
            static void Destroy() throw();
#endif
            
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Copy() const;
            virtual std::shared_ptr< iAtomic > Clone() const;
        
    };
    
    ////
    
    class ArrayValue : public iAtomic
    {
        //  This friend is needed to efficiantly add elements to literal arrays
        //  in ptnode.cpp.
        friend class LiteralArrayParseTreeNode;
    
        public:
        
            using ArrayT = std::vector< std::shared_ptr< iAtomic > >;
        
            static IntegerT Count;
    
        private:
            ArrayT mValue;
            
            const IntegerT mIndexOffset;
            
            bool mInitialized;
            
            mutable std::shared_ptr< iAtomic > mFinishV;
            mutable std::shared_ptr< iAtomic > mLengthV;
            mutable std::shared_ptr< iAtomic > mStartV;
            
        protected:
            INLINE ArrayValue(const IntegerT &mini) : dish::iAtomic(), mValue(), mIndexOffset(-mini), mInitialized(false), mFinishV(), mLengthV(), mStartV()
                { mValue.push_back(NullValue::MakeValue()); ++Count; };
                
            INLINE ArrayValue(const IntegerT &mini, const IntegerT &nelem) : dish::iAtomic(), mValue(), mIndexOffset(-mini), mInitialized(false), mFinishV(), mLengthV(), mStartV()
                { mValue.assign(nelem, NullValue::MakeValue()); ++Count; };
                
            ArrayValue(const IntegerT &mini, const IntegerT &nelem, std::shared_ptr< iAtomic > type);
            
            INLINE void invalidate() const { mFinishV.reset(); mLengthV.reset(); mStartV.reset(); };
            
            INLINE void clear() { mValue.clear(); invalidate(); };
        
        public:
        
            static INLINE IntegerT NumInstances() throw() { return Count; };
            
            static INLINE std::shared_ptr< ArrayValue > MakeValue(const IntegerT &mini) { return std::shared_ptr< ArrayValue >(new ArrayValue(mini)); };
            static INLINE std::shared_ptr< ArrayValue > MakeValue(const IntegerT &mini, const IntegerT &nelem) { return std::shared_ptr< ArrayValue >(new ArrayValue(mini, nelem)); };
            static INLINE std::shared_ptr< ArrayValue > MakeValue(const IntegerT &mini, const IntegerT &nelem, std::shared_ptr< iAtomic > type) { return std::shared_ptr< ArrayValue >(new ArrayValue(mini, nelem, type)); };
            
            //  From iAtomic
            
            virtual void Lock() throw();
            
            virtual TypeT Type() const throw();
            
            virtual std::shared_ptr< iAtomic > Copy() const;
            
            virtual StringT AsString() const;
            
            virtual void Assign(std::shared_ptr< iAtomic > rhs);
            
            virtual std::shared_ptr< iAtomic > Member(const std::string &member) const;
            
            virtual IntegerT Add(std::shared_ptr< iAtomic > element);
            virtual IntegerT Add(std::shared_ptr< iAtomic > element, const IntegerT &index);
            virtual std::shared_ptr< iAtomic > Element(const IntegerT &index) const;
            virtual void Swap(const IntegerT &a, const IntegerT &b);
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    ////
    
    class DictionaryValue : public iAtomic
    {
        public:
        
            ////
            
            class ContainsMethod : public ExecutableAtomic
            {
                private:
                    const DictionaryValue &mThis;
                    
                protected:
                    INLINE ContainsMethod(const DictionaryValue &this_ref) : ExecutableAtomic(), mThis(this_ref) { addParam("str", dish::REFERENCE_PARAMETER); };
                    
                    INLINE const DictionaryValue &thisValue() const { return mThis; };
                
                public:
                    
                    static INLINE std::shared_ptr< ContainsMethod > MakeValue(const DictionaryValue &this_ref) { return std::shared_ptr< ContainsMethod >(new ContainsMethod(this_ref)); };
                    
                    //  From iAtomic
                    
                    virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                
            };
        
            ////
        
            class ValueHolder : public iAtomic
            {
                private:
                    const DictionaryValue &mDictionary;
                    
                    std::shared_ptr< iAtomic > mHeldValue;
                    
                protected:
                    INLINE ValueHolder(const DictionaryValue &dict, std::shared_ptr< iAtomic > value) : iAtomic(), mDictionary(dict), mHeldValue(value) {};
                
                public:
                    
                    static INLINE std::shared_ptr< ValueHolder > MakeValue(const DictionaryValue &dict, std::shared_ptr< iAtomic > value) { return std::shared_ptr< ValueHolder >(new ValueHolder(dict, value)); };
            
                    //  From iAtomic
                    
                    virtual void Lock() throw();
                    
                    virtual TypeT Type() const throw();
                    
                    virtual std::shared_ptr< iAtomic > Copy() const;
                    virtual std::shared_ptr< iAtomic > Clone() const;
                    
                    virtual BooleanT AsBoolean() const;
                    virtual IntegerT AsInteger() const;
                    virtual RealT AsReal() const;
                    virtual StringT AsString() const;
                    
                    virtual void Assign(std::shared_ptr< iAtomic > rhs);
                    
                    virtual std::shared_ptr< iAtomic > Member(const std::string &member) const;
                    
                    virtual IntegerT Add(std::shared_ptr< iAtomic > element);
                    virtual IntegerT Add(std::shared_ptr< iAtomic > element, const IntegerT &index);
                    virtual std::shared_ptr< iAtomic > Element(const IntegerT &index) const;
            
                    virtual IntegerT Add(std::shared_ptr< iAtomic > key, std::shared_ptr< iAtomic > value);
                    virtual std::shared_ptr< iAtomic > Keys() const;
                    virtual std::shared_ptr< iAtomic > Lookup(const StringT &key) const;
                    
                    virtual std::shared_ptr< iAtomic > Declare() const;
                    
                    virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    virtual const ParamListT &ParameterList() const;
                    virtual IntegerT NumParameters() const;
                
            };
        
            ////
            
            using DictionaryT = std::map< std::string, std::shared_ptr< iAtomic > >;
        
            ////
        
            static IntegerT Count;
    
        private:
        
            //  Must be mutable to allow the Element(const StringT &) to insert 
            //  an item into the dictionary on first reference to the new
            //  element.
            mutable DictionaryT mValue;
            
            mutable std::shared_ptr< iAtomic > mContainsF;
            mutable std::shared_ptr< iAtomic > mCountV;
            mutable std::shared_ptr< iAtomic > mEmptyV;
            mutable std::shared_ptr< iAtomic > mKeysV;
            
        protected:
            INLINE DictionaryValue() : iAtomic(), mValue(), mContainsF(), mCountV(), mEmptyV(), mKeysV() { ++Count; };
            
            INLINE void invalidate() const { mCountV.reset(); mEmptyV.reset(); mKeysV.reset(); };
        
        public:
        
            static INLINE IntegerT NumInstances() throw() { return Count; };
            
            static INLINE std::shared_ptr< DictionaryValue > MakeValue() { return std::shared_ptr< DictionaryValue >(new DictionaryValue()); };
            
            //  From iAtomic
            
            virtual void Lock() throw();
            
            virtual TypeT Type() const throw();
            
            virtual std::shared_ptr< iAtomic > Copy() const;
            
            virtual StringT AsString() const;
            
            virtual void Assign(std::shared_ptr< iAtomic > rhs);
            
            virtual std::shared_ptr< iAtomic > Member(const std::string &member) const;
            
            virtual IntegerT Add(std::shared_ptr< iAtomic > key, std::shared_ptr< iAtomic > value);
            virtual std::shared_ptr< iAtomic > Keys() const;
            virtual std::shared_ptr< iAtomic > Lookup(const StringT &key) const;
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    ////
    
    class StructureValue : public iAtomic
    {
        public:
            
            typedef std::map< std::string, std::shared_ptr< iAtomic > > MemberSetT;
        
            static IntegerT Count;
        
        private:
            MemberSetT mMemberSet;
            
        protected:
            static void generateStructureMemberExistsError(const std::string &id);
            
            INLINE StructureValue() : iAtomic(), mMemberSet() { ++Count; };
        
        public:
        
            static INLINE IntegerT NumInstances() throw() { return Count; };
        
            static INLINE std::shared_ptr< StructureValue > MakeValue() { return std::shared_ptr< StructureValue >(new StructureValue()); };
            
            INLINE void Add(const std::string &id, std::shared_ptr< iAtomic > value)
                { assert(0 != value.get()); if(!mMemberSet.insert(std::make_pair(id, value)).second) { generateStructureMemberExistsError(id); } };
            
            //  From iAtomic
            
            virtual void Lock() throw();
            
            virtual TypeT Type() const throw();
            
            virtual std::shared_ptr< iAtomic > Copy() const;
            
            virtual StringT AsString() const;
            
            virtual IntegerT Members(iAtomic::MemberNameSetT &members) const;
            virtual std::shared_ptr< iAtomic > Member(const std::string &member) const;
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    typedef std::shared_ptr< dish::iAtomic > (*OneArgOpF)(const dish::iAtomic &arg);
    typedef bool (*OneArgBoolOpF)(const dish::iAtomic &arg);
    
    typedef std::shared_ptr< dish::iAtomic > (*TwoArgOpF)(const dish::iAtomic &arg1, const dish::iAtomic &arg);
    typedef bool (*TwoArgBoolOpF)(const dish::iAtomic &arg1, const dish::iAtomic &arg);
    
    extern const OneArgOpF OpNeg_FuncTable[iAtomic::typeNUM];
    extern const TwoArgOpF OpAdd_FuncTable[iAtomic::typeNUM][iAtomic::typeNUM];
    extern const TwoArgOpF OpSub_FuncTable[iAtomic::typeNUM][iAtomic::typeNUM];
    extern const TwoArgOpF OpMul_FuncTable[iAtomic::typeNUM][iAtomic::typeNUM];
    extern const TwoArgOpF OpDiv_FuncTable[iAtomic::typeNUM][iAtomic::typeNUM];
    extern const TwoArgOpF OpMod_FuncTable[iAtomic::typeNUM][iAtomic::typeNUM];
    extern const TwoArgOpF OpPow_FuncTable[iAtomic::typeNUM][iAtomic::typeNUM];
    
    extern const OneArgBoolOpF OpNot_FuncTable[iAtomic::typeNUM];
    extern const TwoArgBoolOpF OpAnd_FuncTable[iAtomic::typeNUM][iAtomic::typeNUM];
    extern const TwoArgBoolOpF OpOr_FuncTable[iAtomic::typeNUM][iAtomic::typeNUM];
    extern const TwoArgBoolOpF OpXor_FuncTable[iAtomic::typeNUM][iAtomic::typeNUM];
    extern const TwoArgBoolOpF OpLessThan_FuncTable[iAtomic::typeNUM][iAtomic::typeNUM];
    extern const TwoArgBoolOpF OpLessThanOrEqual_FuncTable[iAtomic::typeNUM][iAtomic::typeNUM];
    extern const TwoArgBoolOpF OpEqual_FuncTable[iAtomic::typeNUM][iAtomic::typeNUM];
    extern const TwoArgBoolOpF OpNotEqual_FuncTable[iAtomic::typeNUM][iAtomic::typeNUM];
    extern const TwoArgBoolOpF OpGreaterThanOrEqual_FuncTable[iAtomic::typeNUM][iAtomic::typeNUM];
    extern const TwoArgBoolOpF OpGreaterThan_FuncTable[iAtomic::typeNUM][iAtomic::typeNUM];

    ////////////////////////////////////////////////////////////////////////////
    
    INLINEC std::shared_ptr< iAtomic > OpNeg(const iAtomic &arg) { return OpNeg_FuncTable[arg.Type()](arg); };
    INLINEC std::shared_ptr< iAtomic > OpNeg(std::shared_ptr< iAtomic > arg) { return OpNeg(*arg); };
    
    INLINEC std::shared_ptr< iAtomic > OpAdd(const iAtomic &arg1, const iAtomic &arg2) { return OpAdd_FuncTable[arg1.Type()][arg2.Type()](arg1, arg2); };
    INLINEC std::shared_ptr< iAtomic > OpAdd(std::shared_ptr< iAtomic > arg1, std::shared_ptr< iAtomic > arg2) { return OpAdd(*arg1, *arg2); };
    
    INLINEC std::shared_ptr< iAtomic > OpSub(const iAtomic &arg1, const iAtomic &arg2) { return OpSub_FuncTable[arg1.Type()][arg2.Type()](arg1, arg2); };
    INLINEC std::shared_ptr< iAtomic > OpSub(std::shared_ptr< iAtomic > arg1, std::shared_ptr< iAtomic > arg2) { return OpSub(*arg1, *arg2); };
    
    INLINEC std::shared_ptr< iAtomic > OpMul(const iAtomic &arg1, const iAtomic &arg2) { return OpMul_FuncTable[arg1.Type()][arg2.Type()](arg1, arg2); };
    INLINEC std::shared_ptr< iAtomic > OpMul(std::shared_ptr< iAtomic > arg1, std::shared_ptr< iAtomic > arg2) { return OpMul(*arg1, *arg2); };
    
    INLINEC std::shared_ptr< iAtomic > OpDiv(const iAtomic &arg1, const iAtomic &arg2) { return OpDiv_FuncTable[arg1.Type()][arg2.Type()](arg1, arg2); };
    INLINEC std::shared_ptr< iAtomic > OpDiv(std::shared_ptr< iAtomic > arg1, std::shared_ptr< iAtomic > arg2) { return OpDiv(*arg1, *arg2); };
    
    INLINEC std::shared_ptr< iAtomic > OpMod(const iAtomic &arg1, const iAtomic &arg2) { return OpMod_FuncTable[arg1.Type()][arg2.Type()](arg1, arg2); };
    INLINEC std::shared_ptr< iAtomic > OpMod(std::shared_ptr< iAtomic > arg1, std::shared_ptr< iAtomic > arg2) { return OpMod(*arg1, *arg2); };
    
    INLINEC std::shared_ptr< iAtomic > OpPow(const iAtomic &arg1, const iAtomic &arg2) { return OpPow_FuncTable[arg1.Type()][arg2.Type()](arg1, arg2); };
    INLINEC std::shared_ptr< iAtomic > OpPow(std::shared_ptr< iAtomic > arg1, std::shared_ptr< iAtomic > arg2) { return OpPow(*arg1, *arg2); };
    
    INLINEC bool OpNot(const iAtomic &arg) { return OpNot_FuncTable[arg.Type()](arg); };
    INLINEC std::shared_ptr< iAtomic > OpNot(std::shared_ptr< iAtomic > arg) { return dish::BooleanValue::MakeLockedValue(OpNot(*arg)); };
    
    INLINEC bool OpAnd(const iAtomic &arg1, const iAtomic &arg2) { return OpAnd_FuncTable[arg1.Type()][arg2.Type()](arg1, arg2); };
    INLINEC std::shared_ptr< iAtomic > OpAnd(std::shared_ptr< iAtomic > arg1, std::shared_ptr< iAtomic > arg2) { return dish::BooleanValue::MakeLockedValue(OpAnd(*arg1, *arg2)); };
    
    INLINEC bool OpOr(const iAtomic &arg1, const iAtomic &arg2) { return OpOr_FuncTable[arg1.Type()][arg2.Type()](arg1, arg2); };
    INLINEC std::shared_ptr< iAtomic > OpOr(std::shared_ptr< iAtomic > arg1, std::shared_ptr< iAtomic > arg2) { return dish::BooleanValue::MakeLockedValue(OpOr(*arg1, *arg2)); };
    
    INLINEC bool OpXor(const iAtomic &arg1, const iAtomic &arg2) { return OpXor_FuncTable[arg1.Type()][arg2.Type()](arg1, arg2); };
    INLINEC std::shared_ptr< iAtomic > OpXor(std::shared_ptr< iAtomic > arg1, std::shared_ptr< iAtomic > arg2) { return dish::BooleanValue::MakeLockedValue(OpXor(*arg1, *arg2)); };
    
    INLINEC bool OpLessThan(const iAtomic &arg1, const iAtomic &arg2) { return OpLessThan_FuncTable[arg1.Type()][arg2.Type()](arg1, arg2); };
    INLINEC std::shared_ptr< iAtomic > OpLessThan(std::shared_ptr< iAtomic > arg1, std::shared_ptr< iAtomic > arg2) { return dish::BooleanValue::MakeLockedValue(OpLessThan(*arg1, *arg2)); };
    
    INLINEC bool OpLessThanOrEqual(const iAtomic &arg1, const iAtomic &arg2) { return OpLessThanOrEqual_FuncTable[arg1.Type()][arg2.Type()](arg1, arg2); };
    INLINEC std::shared_ptr< iAtomic > OpLessThanOrEqual(std::shared_ptr< iAtomic > arg1, std::shared_ptr< iAtomic > arg2) { return dish::BooleanValue::MakeLockedValue(OpLessThanOrEqual(*arg1, *arg2)); };
    
    INLINEC bool OpEqual(const iAtomic &arg1, const iAtomic &arg2) { return OpEqual_FuncTable[arg1.Type()][arg2.Type()](arg1, arg2); };
    INLINEC std::shared_ptr< iAtomic > OpEqual(std::shared_ptr< iAtomic > arg1, std::shared_ptr< iAtomic > arg2) { return dish::BooleanValue::MakeLockedValue(OpEqual(*arg1, *arg2)); };
    
    INLINEC bool OpNotEqual(const iAtomic &arg1, const iAtomic &arg2) { return OpNotEqual_FuncTable[arg1.Type()][arg2.Type()](arg1, arg2); };
    INLINEC std::shared_ptr< iAtomic > OpNotEqual(std::shared_ptr< iAtomic > arg1, std::shared_ptr< iAtomic > arg2) { return dish::BooleanValue::MakeLockedValue(OpNotEqual(*arg1, *arg2)); };
    
    INLINEC bool OpGreaterThanOrEqual(const iAtomic &arg1, const iAtomic &arg2) { return OpGreaterThanOrEqual_FuncTable[arg1.Type()][arg2.Type()](arg1, arg2); };
    INLINEC std::shared_ptr< iAtomic > OpGreaterThanOrEqual(std::shared_ptr< iAtomic > arg1, std::shared_ptr< iAtomic > arg2) { return dish::BooleanValue::MakeLockedValue(OpGreaterThanOrEqual(*arg1, *arg2)); };
    
    INLINEC bool OpGreaterThan(const iAtomic &arg1, const iAtomic &arg2) { return OpGreaterThan_FuncTable[arg1.Type()][arg2.Type()](arg1, arg2); };
    INLINEC std::shared_ptr< iAtomic > OpGreaterThan(std::shared_ptr< iAtomic > arg1, std::shared_ptr< iAtomic > arg2) { return dish::BooleanValue::MakeLockedValue(OpGreaterThan(*arg1, *arg2)); };

    ////////////////////////////////////////////////////////////////////////////

    extern std::string TypeToString(const iAtomic::TypeT type);
    
    ////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////

INLINEC std::shared_ptr< dish::iAtomic > operator-(std::shared_ptr< dish::iAtomic > arg) { return dish::OpNeg(arg); };
INLINEC std::shared_ptr< dish::iAtomic > operator+(std::shared_ptr< dish::iAtomic > arg1, std::shared_ptr< dish::iAtomic > arg2) { return dish::OpAdd(arg1, arg2); };
INLINEC std::shared_ptr< dish::iAtomic > operator-(std::shared_ptr< dish::iAtomic > arg1, std::shared_ptr< dish::iAtomic > arg2) { return dish::OpSub(arg1, arg2); };
INLINEC std::shared_ptr< dish::iAtomic > operator*(std::shared_ptr< dish::iAtomic > arg1, std::shared_ptr< dish::iAtomic > arg2) { return dish::OpMul(arg1, arg2); };
INLINEC std::shared_ptr< dish::iAtomic > operator/(std::shared_ptr< dish::iAtomic > arg1, std::shared_ptr< dish::iAtomic > arg2) { return dish::OpDiv(arg1, arg2); };
INLINEC std::shared_ptr< dish::iAtomic > operator%(std::shared_ptr< dish::iAtomic > arg1, std::shared_ptr< dish::iAtomic > arg2) { return dish::OpMod(arg1, arg2); };

INLINEC std::shared_ptr< dish::iAtomic > operator!(std::shared_ptr< dish::iAtomic > arg) { return dish::OpNot(arg); };

INLINEC bool operator<(const dish::iAtomic &arg1, const dish::iAtomic &arg2) { return dish::OpLessThan(arg1, arg2); };
INLINEC std::shared_ptr< dish::iAtomic > operator<(std::shared_ptr< dish::iAtomic > arg1, std::shared_ptr< dish::iAtomic > arg2) { return dish::OpLessThan(arg1, arg2); };

INLINEC bool operator<=(const dish::iAtomic &arg1, const dish::iAtomic &arg2) { return dish::OpLessThanOrEqual(arg1, arg2); };
INLINEC std::shared_ptr< dish::iAtomic > operator<=(std::shared_ptr< dish::iAtomic > arg1, std::shared_ptr< dish::iAtomic > arg2) { return dish::OpLessThanOrEqual(arg1, arg2); };

INLINEC bool operator==(const dish::iAtomic &arg1, const dish::iAtomic &arg2) { return dish::OpEqual(arg1, arg2); };
INLINEC std::shared_ptr< dish::iAtomic > operator==(std::shared_ptr< dish::iAtomic > arg1, std::shared_ptr< dish::iAtomic > arg2) { return dish::OpEqual(arg1, arg2); };

INLINEC bool operator!=(const dish::iAtomic &arg1, const dish::iAtomic &arg2) { return dish::OpNotEqual(arg1, arg2); };
INLINEC std::shared_ptr< dish::iAtomic > operator!=(std::shared_ptr< dish::iAtomic > arg1, std::shared_ptr< dish::iAtomic > arg2) { return dish::OpNotEqual(arg1, arg2); };

INLINEC bool operator>=(const dish::iAtomic &arg1, const dish::iAtomic &arg2) { return dish::OpGreaterThanOrEqual(arg1, arg2); };
INLINEC std::shared_ptr< dish::iAtomic > operator>=(std::shared_ptr< dish::iAtomic > arg1, std::shared_ptr< dish::iAtomic > arg2) { return dish::OpGreaterThanOrEqual(arg1, arg2); };

INLINEC bool operator>(const dish::iAtomic &arg1, const dish::iAtomic &arg2) { return dish::OpGreaterThan(arg1, arg2); };
INLINEC std::shared_ptr< dish::iAtomic > operator>(std::shared_ptr< dish::iAtomic > arg1, std::shared_ptr< dish::iAtomic > arg2) { return dish::OpGreaterThan(arg1, arg2); };

////////////////////////////////////////////////////////////////////////////////

#endif

