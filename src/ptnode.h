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

#ifndef DISH_PTNODE_H
#define DISH_PTNODE_H

#include "dishconfig.h"

#include <cassert>
#include <iostream>

#ifndef LIST_TYPE_PREFER_VECTOR
#include <list>
#endif

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "atomics.h"
#include "inline.h"
#include "input.h"
#include "language.h"
#include "types.h"
#include "utility.h"

namespace dish
{

    ////////////////////////////////////////////////////////////////////////////
    
    class NullParseTreeNode;
    
    class ReferenceParseTreeNode;
    
    class LiteralParseTreeNode;
    class LiteralArrayParseTreeNode;
    
    class IdentifierParseTreeNode;
    
    class LockParseTreeNode;
    
    class BooleanTypeParseTreeNode;
    class IntegerTypeParseTreeNode;
    class RangedIntegerTypeParseTreeNode;
    class RealTypeParseTreeNode;
    class RangedRealTypeParseTreeNode;
    class StringTypeParseTreeNode;
    class ArrayTypeParseTreeNode;
    class DictionaryTypeParseTreeNode;
    class StructureTypeParseTreeNode;
    
    class DeclareParseTreeNode;
    class DeclareTypeParseTreeNode;
    class DeclareFunctionParseTreeNode;
    class DeclareReferenceParseTreeNode;
    
    class AssignmentParseTreeNode;
    
    class IndexParseTreeNode;
    class MemberParseTreeNode;
    
    class FunctionCallParseTreeNode;
    
    class ReturnParseTreeNode;
    
    class NegateOpParseTreeNode;
    class AddOpChainParseTreeNode;
    class SubOpParseTreeNode;
    class MulOpChainParseTreeNode;
    class DivOpParseTreeNode;
    class ModOpParseTreeNode;
    class PowOpParseTreeNode;
    
    class NotOpParseTreeNode;
    class AndOpChainParseTreeNode;
    class OrOpChainParseTreeNode;
    class XorOpChainParseTreeNode;
    
    class LessThanOpParseTreeNode;
    class LessThanEqualOpParseTreeNode;
    class EqualOpParseTreeNode;
    class NotEqualOpParseTreeNode;
    class GreaterThanEqualOpParseTreeNode;
    class GreaterThanOpParseTreeNode;
    
    class StatementBlockParseTreeNode;
    
    class IfStatementParseTreeNode;
    class SwitchStatementParseTreeNode;
    
    class ForLoopParseTreeNode;
    class ForEachLoopParseTreeNode;
    class WhileLoopParseTreeNode;
    class RepeatUntilLoopParseTreeNode;
    
    class AssertParseTreeNode;

    ////////////////////////////////////////////////////////////////////////////
    
    class iParseTreeNode : public iPrintable
    {
        friend NullParseTreeNode;
    
        friend ReferenceParseTreeNode;
    
        friend LiteralParseTreeNode;
        friend LiteralArrayParseTreeNode;
    
        friend IdentifierParseTreeNode;
    
        friend LockParseTreeNode;
    
        friend BooleanTypeParseTreeNode;
        friend IntegerTypeParseTreeNode;
        friend RangedIntegerTypeParseTreeNode;
        friend RealTypeParseTreeNode;
        friend RangedRealTypeParseTreeNode;
        friend StringTypeParseTreeNode;
        friend ArrayTypeParseTreeNode;
        friend DictionaryTypeParseTreeNode;
        friend StructureTypeParseTreeNode;
    
        friend DeclareParseTreeNode;
        friend DeclareTypeParseTreeNode;
        friend DeclareFunctionParseTreeNode;
        friend DeclareReferenceParseTreeNode;
    
        friend AssignmentParseTreeNode;
    
        friend IndexParseTreeNode;
        friend MemberParseTreeNode;
    
        friend FunctionCallParseTreeNode;
    
        friend ReturnParseTreeNode;
    
        friend NegateOpParseTreeNode;
        friend AddOpChainParseTreeNode;
        friend SubOpParseTreeNode;
        friend MulOpChainParseTreeNode;
        friend DivOpParseTreeNode;
        friend ModOpParseTreeNode;
        friend PowOpParseTreeNode;
    
        friend NotOpParseTreeNode;
        friend AndOpChainParseTreeNode;
        friend OrOpChainParseTreeNode;
        friend XorOpChainParseTreeNode;
    
        friend LessThanOpParseTreeNode;
        friend LessThanEqualOpParseTreeNode;
        friend EqualOpParseTreeNode;
        friend NotEqualOpParseTreeNode;
        friend GreaterThanEqualOpParseTreeNode;
        friend GreaterThanOpParseTreeNode;
    
        friend StatementBlockParseTreeNode;
    
        friend IfStatementParseTreeNode;
        friend SwitchStatementParseTreeNode;
    
        friend ForLoopParseTreeNode;
        friend ForEachLoopParseTreeNode;
        friend WhileLoopParseTreeNode;
        friend RepeatUntilLoopParseTreeNode;
    
        friend AssertParseTreeNode;
    
        protected:
            virtual bool isEqual(const NullParseTreeNode &ptn) const = 0;
    
            virtual bool isEqual(const ReferenceParseTreeNode &ptn) const = 0;
    
            virtual bool isEqual(const LiteralParseTreeNode &ptn) const = 0;
            virtual bool isEqual(const LiteralArrayParseTreeNode &ptn) const = 0;
    
            virtual bool isEqual(const IdentifierParseTreeNode &ptn) const = 0;
    
            virtual bool isEqual(const LockParseTreeNode &ptn) const = 0;
    
            virtual bool isEqual(const BooleanTypeParseTreeNode &ptn) const = 0;
            virtual bool isEqual(const IntegerTypeParseTreeNode &ptn) const = 0;
            virtual bool isEqual(const RangedIntegerTypeParseTreeNode &ptn) const = 0;
            virtual bool isEqual(const RealTypeParseTreeNode &ptn) const = 0;
            virtual bool isEqual(const RangedRealTypeParseTreeNode &ptn) const = 0;
            virtual bool isEqual(const StringTypeParseTreeNode &ptn) const = 0;
            virtual bool isEqual(const ArrayTypeParseTreeNode &ptn) const = 0;
            virtual bool isEqual(const DictionaryTypeParseTreeNode &ptn) const = 0;
            virtual bool isEqual(const StructureTypeParseTreeNode &ptn) const = 0;
    
            virtual bool isEqual(const DeclareParseTreeNode &ptn) const = 0;
            virtual bool isEqual(const DeclareTypeParseTreeNode &ptn) const = 0;
            virtual bool isEqual(const DeclareFunctionParseTreeNode &ptn) const = 0;
            virtual bool isEqual(const DeclareReferenceParseTreeNode &ptn) const = 0;
    
            virtual bool isEqual(const AssignmentParseTreeNode &ptn) const = 0;
    
            virtual bool isEqual(const IndexParseTreeNode &ptn) const = 0;
            virtual bool isEqual(const MemberParseTreeNode &ptn) const = 0;
    
            virtual bool isEqual(const FunctionCallParseTreeNode &ptn) const = 0;
    
            virtual bool isEqual(const ReturnParseTreeNode &ptn) const = 0;
    
            virtual bool isEqual(const NegateOpParseTreeNode &ptn) const = 0;
            virtual bool isEqual(const AddOpChainParseTreeNode &ptn) const = 0;
            virtual bool isEqual(const SubOpParseTreeNode &ptn) const = 0;
            virtual bool isEqual(const MulOpChainParseTreeNode &ptn) const = 0;
            virtual bool isEqual(const DivOpParseTreeNode &ptn) const = 0;
            virtual bool isEqual(const ModOpParseTreeNode &ptn) const = 0;
            virtual bool isEqual(const PowOpParseTreeNode &ptn) const = 0;
    
            virtual bool isEqual(const NotOpParseTreeNode &ptn) const = 0;
            virtual bool isEqual(const AndOpChainParseTreeNode &ptn) const = 0;
            virtual bool isEqual(const OrOpChainParseTreeNode &ptn) const = 0;
            virtual bool isEqual(const XorOpChainParseTreeNode &ptn) const = 0;
    
            virtual bool isEqual(const LessThanOpParseTreeNode &ptn) const = 0;
            virtual bool isEqual(const LessThanEqualOpParseTreeNode &ptn) const = 0;
            virtual bool isEqual(const EqualOpParseTreeNode &ptn) const = 0;
            virtual bool isEqual(const NotEqualOpParseTreeNode &ptn) const = 0;
            virtual bool isEqual(const GreaterThanEqualOpParseTreeNode &ptn) const = 0;
            virtual bool isEqual(const GreaterThanOpParseTreeNode &ptn) const = 0;
    
            virtual bool isEqual(const StatementBlockParseTreeNode &ptn) const = 0;
    
            virtual bool isEqual(const IfStatementParseTreeNode &ptn) const = 0;
            virtual bool isEqual(const SwitchStatementParseTreeNode &ptn) const = 0;
    
            virtual bool isEqual(const ForLoopParseTreeNode &ptn) const = 0;
            virtual bool isEqual(const ForEachLoopParseTreeNode &ptn) const = 0;
            virtual bool isEqual(const WhileLoopParseTreeNode &ptn) const = 0;
            virtual bool isEqual(const RepeatUntilLoopParseTreeNode &ptn) const = 0;
    
            virtual bool isEqual(const AssertParseTreeNode &ptn) const = 0;
    
        public:
            virtual ~iParseTreeNode() {};
            
            virtual const std::string &LocationString() const = 0;
            
            virtual bool IsLiteral() const = 0;
            
            virtual std::shared_ptr< iAtomic > Execute() = 0;
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) = 0;
            
            virtual void Validate(LanguageSymbolTable &symtab) const = 0;
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const = 0;
            
            virtual const std::string &ToString() const = 0;
        
    };
    
    class ParseTreeNode : public iParseTreeNode
    {
        private:
            const std::string mLocationString;
        
        protected:
            INLINE ParseTreeNode() : iParseTreeNode(), mLocationString() {};
            INLINE ParseTreeNode(const std::string &locstr) : iParseTreeNode(), mLocationString(locstr) {};
            
            //  From iParseTreeNode
            
            virtual bool isEqual(const NullParseTreeNode &ptn) const;
    
            virtual bool isEqual(const ReferenceParseTreeNode &ptn) const;
    
            virtual bool isEqual(const LiteralParseTreeNode &ptn) const;
            virtual bool isEqual(const LiteralArrayParseTreeNode &ptn) const;
    
            virtual bool isEqual(const IdentifierParseTreeNode &ptn) const;
    
            virtual bool isEqual(const LockParseTreeNode &ptn) const;
    
            virtual bool isEqual(const BooleanTypeParseTreeNode &ptn) const;
            virtual bool isEqual(const IntegerTypeParseTreeNode &ptn) const;
            virtual bool isEqual(const RangedIntegerTypeParseTreeNode &ptn) const;
            virtual bool isEqual(const RealTypeParseTreeNode &ptn) const;
            virtual bool isEqual(const RangedRealTypeParseTreeNode &ptn) const;
            virtual bool isEqual(const StringTypeParseTreeNode &ptn) const;
            virtual bool isEqual(const ArrayTypeParseTreeNode &ptn) const;
            virtual bool isEqual(const DictionaryTypeParseTreeNode &ptn) const;
            virtual bool isEqual(const StructureTypeParseTreeNode &ptn) const;
    
            virtual bool isEqual(const DeclareParseTreeNode &ptn) const;
            virtual bool isEqual(const DeclareTypeParseTreeNode &ptn) const;
            virtual bool isEqual(const DeclareFunctionParseTreeNode &ptn) const;
            virtual bool isEqual(const DeclareReferenceParseTreeNode &ptn) const;
    
            virtual bool isEqual(const AssignmentParseTreeNode &ptn) const;
    
            virtual bool isEqual(const IndexParseTreeNode &ptn) const;
            virtual bool isEqual(const MemberParseTreeNode &ptn) const;
    
            virtual bool isEqual(const FunctionCallParseTreeNode &ptn) const;
    
            virtual bool isEqual(const ReturnParseTreeNode &ptn) const;
    
            virtual bool isEqual(const NegateOpParseTreeNode &ptn) const;
            virtual bool isEqual(const AddOpChainParseTreeNode &ptn) const;
            virtual bool isEqual(const SubOpParseTreeNode &ptn) const;
            virtual bool isEqual(const MulOpChainParseTreeNode &ptn) const;
            virtual bool isEqual(const DivOpParseTreeNode &ptn) const;
            virtual bool isEqual(const ModOpParseTreeNode &ptn) const;
            virtual bool isEqual(const PowOpParseTreeNode &ptn) const;
    
            virtual bool isEqual(const NotOpParseTreeNode &ptn) const;
            virtual bool isEqual(const AndOpChainParseTreeNode &ptn) const;
            virtual bool isEqual(const OrOpChainParseTreeNode &ptn) const;
            virtual bool isEqual(const XorOpChainParseTreeNode &ptn) const;
    
            virtual bool isEqual(const LessThanOpParseTreeNode &ptn) const;
            virtual bool isEqual(const LessThanEqualOpParseTreeNode &ptn) const;
            virtual bool isEqual(const EqualOpParseTreeNode &ptn) const;
            virtual bool isEqual(const NotEqualOpParseTreeNode &ptn) const;
            virtual bool isEqual(const GreaterThanEqualOpParseTreeNode &ptn) const;
            virtual bool isEqual(const GreaterThanOpParseTreeNode &ptn) const;
    
            virtual bool isEqual(const StatementBlockParseTreeNode &ptn) const;
    
            virtual bool isEqual(const IfStatementParseTreeNode &ptn) const;
            virtual bool isEqual(const SwitchStatementParseTreeNode &ptn) const;
    
            virtual bool isEqual(const ForLoopParseTreeNode &ptn) const;
            virtual bool isEqual(const ForEachLoopParseTreeNode &ptn) const;
            virtual bool isEqual(const WhileLoopParseTreeNode &ptn) const;
            virtual bool isEqual(const RepeatUntilLoopParseTreeNode &ptn) const;
    
            virtual bool isEqual(const AssertParseTreeNode &ptn) const;
        
        public:
            
            //  From iParseTreeNode
            
            virtual const std::string &LocationString() const;
            
            virtual bool IsLiteral() const;
            
            virtual std::shared_ptr< iAtomic > Execute();
            
            virtual void Validate(LanguageSymbolTable &symtab) const;
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            virtual const std::string &ToString() const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class NullParseTreeNode : public ParseTreeNode
    {
        private:
        
            static IntegerT Count;
            static IntegerT Instances;
    
        protected:
            INLINE NullParseTreeNode() : ParseTreeNode() { ++Count; ++Instances; };
            INLINE NullParseTreeNode(const std::string &locstr) : ParseTreeNode(locstr) { ++Count; ++Instances; };
            
            //  From iParseTreeNode
            
            virtual bool isEqual(const NullParseTreeNode &ptn) const;
        
        public:
            virtual ~NullParseTreeNode() { --Instances; };
            
            static std::shared_ptr< NullParseTreeNode > MakeValue();
            static INLINE std::shared_ptr< NullParseTreeNode > MakeValue(const std::string &locstr) { return std::shared_ptr< NullParseTreeNode >(new NullParseTreeNode(locstr)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
            
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class ReferenceParseTreeNode : public ParseTreeNode
    {
        private:
            std::shared_ptr< iAtomic > mReference;
        
            static IntegerT Count;
            static IntegerT Instances;
        
        protected:
            INLINE ReferenceParseTreeNode(std::shared_ptr< iAtomic > &ref) : ParseTreeNode(), mReference(ref) { assert(mReference); ++Count; ++Instances; };
            
            //  From iParseTreeNode
            
            virtual bool isEqual(const ReferenceParseTreeNode &ptn) const;
        
        public:
            virtual ~ReferenceParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< ReferenceParseTreeNode > MakeValue(std::shared_ptr< iAtomic > &ref) { return std::shared_ptr< ReferenceParseTreeNode >(new ReferenceParseTreeNode(ref)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual bool IsLiteral() const;
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class LiteralParseTreeNode : public ParseTreeNode
    {
        private:
            std::shared_ptr< iAtomic > mLiteral;
        
            static IntegerT Count;
            static IntegerT Instances;
            
            static std::map< IntegerT, std::shared_ptr< LiteralParseTreeNode > > CachedIntegerLiteralNodes;
            static std::map< RealT, std::shared_ptr< LiteralParseTreeNode > > CachedRealLiteralNodes;
            static std::map< StringT, std::shared_ptr< LiteralParseTreeNode > > CachedStringLiteralNodes;

        protected:
            INLINE LiteralParseTreeNode(std::shared_ptr< iAtomic > &value) : ParseTreeNode(), mLiteral(value) { assert(0 != mLiteral.get()); ++Count; ++Instances; };
            INLINE explicit LiteralParseTreeNode(const BooleanT &value) : ParseTreeNode(), mLiteral(BooleanValue::MakeUnlockedValue(value)) { assert(0 != mLiteral.get()); ++Count; ++Instances; };
            INLINE explicit LiteralParseTreeNode(const IntegerT &value) : ParseTreeNode(), mLiteral(IntegerValue::MakeValue(value)) { assert(0 != mLiteral.get()); ++Count; ++Instances; };
            INLINE explicit LiteralParseTreeNode(const RealT &value) : ParseTreeNode(), mLiteral(RealValue::MakeValue(value)) { assert(0 != mLiteral.get()); ++Count; ++Instances; };
            INLINE explicit LiteralParseTreeNode(const StringT &value) : ParseTreeNode(), mLiteral(StringValue::MakeValue(value)) { assert(0 != mLiteral.get()); ++Count; ++Instances; };
            
            INLINE LiteralParseTreeNode(const std::string &locstr, std::shared_ptr< iAtomic > &value) : ParseTreeNode(locstr), mLiteral(value) { assert(0 != mLiteral.get()); ++Count; ++Instances; };
            INLINE LiteralParseTreeNode(const std::string &locstr, const BooleanT &value) : ParseTreeNode(locstr), mLiteral(BooleanValue::MakeUnlockedValue(value)) { assert(0 != mLiteral.get()); ++Count; ++Instances; };
            INLINE LiteralParseTreeNode(const std::string &locstr, const IntegerT &value) : ParseTreeNode(locstr), mLiteral(IntegerValue::MakeValue(value)) { assert(0 != mLiteral.get()); ++Count; ++Instances; };
            INLINE LiteralParseTreeNode(const std::string &locstr, const RealT &value) : ParseTreeNode(locstr), mLiteral(RealValue::MakeValue(value)) { assert(0 != mLiteral.get()); ++Count; ++Instances; };
            INLINE LiteralParseTreeNode(const std::string &locstr, const StringT &value) : ParseTreeNode(locstr), mLiteral(StringValue::MakeValue(value)) { assert(0 != mLiteral.get()); ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const LiteralParseTreeNode &ptn) const;
        
        public:
            virtual ~LiteralParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< LiteralParseTreeNode > MakeValue(std::shared_ptr< iAtomic > &value) { return std::shared_ptr< LiteralParseTreeNode >(new LiteralParseTreeNode(value)); };
            static std::shared_ptr< LiteralParseTreeNode > MakeValue(const BooleanT &value);
            static std::shared_ptr< LiteralParseTreeNode > MakeValue(const IntegerT &value);
            static std::shared_ptr< LiteralParseTreeNode > MakeValue(const RealT &value);
            static std::shared_ptr< LiteralParseTreeNode > MakeValue(const StringT &value);
            
            static INLINE std::shared_ptr< LiteralParseTreeNode > MakeValue(const std::string &locstr, std::shared_ptr< iAtomic > &value) { return std::shared_ptr< LiteralParseTreeNode >(new LiteralParseTreeNode(locstr, value)); };
            static INLINE std::shared_ptr< LiteralParseTreeNode > MakeValue(const std::string &locstr, const BooleanT &value) { return std::shared_ptr< LiteralParseTreeNode >(new LiteralParseTreeNode(locstr, value)); };
            static INLINE std::shared_ptr< LiteralParseTreeNode > MakeValue(const std::string &locstr, const IntegerT &value) { return std::shared_ptr< LiteralParseTreeNode >(new LiteralParseTreeNode(locstr, value)); };
            static INLINE std::shared_ptr< LiteralParseTreeNode > MakeValue(const std::string &locstr, const RealT &value) { return std::shared_ptr< LiteralParseTreeNode >(new LiteralParseTreeNode(locstr, value)); };
            static INLINE std::shared_ptr< LiteralParseTreeNode > MakeValue(const std::string &locstr, const StringT &value) { return std::shared_ptr< LiteralParseTreeNode >(new LiteralParseTreeNode(locstr, value)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            static INLINE IntegerT NumCachedIntegerLiteralNodes() { return static_cast< IntegerT >(CachedIntegerLiteralNodes.size()); };
            static INLINE IntegerT NumCachedRealLiteralNodes() { return static_cast< IntegerT >(CachedRealLiteralNodes.size()); };
            static INLINE IntegerT NumCachedStringLiteralNodes() { return static_cast< IntegerT >(CachedStringLiteralNodes.size()); };
            
            static IntegerT ReleaseCachedParseTreeNodes();
            
            //  From iParseTreeNode
            
            virtual bool IsLiteral() const;
            
            virtual std::shared_ptr< iAtomic > Execute();
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;

    };
    
    class LiteralArrayParseTreeNode : public ParseTreeNode
    {
        public:
        
            using ElementT = std::vector< std::shared_ptr< iParseTreeNode > >;
    
        private:
            ElementT mElements;
        
            static IntegerT Count;
            static IntegerT Instances;
        
        protected:
            INLINE LiteralArrayParseTreeNode() : ParseTreeNode(), mElements() { ++Count; ++Instances; };
            INLINE LiteralArrayParseTreeNode(const std::string &locstr) : ParseTreeNode(locstr), mElements() { ++Count; ++Instances; };
        
        public:
            virtual ~LiteralArrayParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< LiteralArrayParseTreeNode > MakeValue() { return std::shared_ptr< LiteralArrayParseTreeNode >(new LiteralArrayParseTreeNode()); };
            static INLINE std::shared_ptr< LiteralArrayParseTreeNode > MakeValue(const StringT &locstr) { return std::shared_ptr< LiteralArrayParseTreeNode >(new LiteralArrayParseTreeNode(locstr)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            INLINE void Add(std::shared_ptr< iParseTreeNode > elem) { assert(elem); mElements.push_back(elem); };
            
            //  From iParseTreeNode
            
            virtual bool IsLiteral() const;
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };

    class IdentifierParseTreeNode : public ParseTreeNode
    {
        private:
            const bool mBaseId;
            std::string mId;
        
            static IntegerT Count;
            static IntegerT Instances;
            
            static std::map< std::string, std::shared_ptr< IdentifierParseTreeNode > > CachedNodes;

        protected:
            INLINE IdentifierParseTreeNode(const std::string &id) : ParseTreeNode(), mBaseId(BeginsWith(id, '`')), mId()
                { mId = (!mBaseId) ? id : id.substr(1, std::string::npos); ++Count; ++Instances; };
                
            INLINE IdentifierParseTreeNode(const std::string &locstr, const std::string &id) : ParseTreeNode(locstr), mBaseId(BeginsWith(id, '`')), mId()
                { mId = (!mBaseId) ? id : id.substr(1, std::string::npos); ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const IdentifierParseTreeNode &ptn) const;
        
        public:
            virtual ~IdentifierParseTreeNode() { --Instances; };
            
            static std::shared_ptr< IdentifierParseTreeNode > MakeValue(const std::string &id);
            static INLINE std::shared_ptr< IdentifierParseTreeNode > MakeValue(const std::string &locstr, const std::string &id) { return std::shared_ptr< IdentifierParseTreeNode >(new IdentifierParseTreeNode(locstr, id)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            INLINE const std::string &Id() const { return mId; };
            
            static INLINE IntegerT NumCachedNodes() { return static_cast< IntegerT >(CachedNodes.size()); };
            
            static IntegerT ReleaseCachedParseTreeNodes();
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual void Validate(LanguageSymbolTable &symtab) const;
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            virtual const std::string &ToString() const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;

    };

    class LockParseTreeNode : public ParseTreeNode
    {
        private:
            const std::string mId;
        
            static IntegerT Count;
            static IntegerT Instances;

        protected:
            INLINE LockParseTreeNode(const std::string &id) : ParseTreeNode(), mId(id) { ++Count; ++Instances; };
            INLINE LockParseTreeNode(const std::string &locstr, const std::string &id) : ParseTreeNode(locstr), mId(id) { ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const LockParseTreeNode &ptn) const;
        
        public:
            virtual ~LockParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< LockParseTreeNode > MakeValue(const std::string &id) { return std::shared_ptr< LockParseTreeNode >(new LockParseTreeNode(id)); };
            static INLINE std::shared_ptr< LockParseTreeNode > MakeValue(const StringT &locstr, const std::string &id) { return std::shared_ptr< LockParseTreeNode >(new LockParseTreeNode(locstr, id)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;

    };

    ////////////////////////////////////////////////////////////////////////////
    
    class BooleanTypeParseTreeNode : public ParseTreeNode
    {
        private:
        
            static IntegerT Count;
            static IntegerT Instances;
    
        protected:
            INLINE BooleanTypeParseTreeNode() : ParseTreeNode() { ++Count; ++Instances; };
            INLINE BooleanTypeParseTreeNode(const std::string &locstr) : ParseTreeNode(locstr) { ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const BooleanTypeParseTreeNode &ptn) const;
        
        public:
            virtual ~BooleanTypeParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< BooleanTypeParseTreeNode > MakeValue() { return std::shared_ptr< BooleanTypeParseTreeNode >(new BooleanTypeParseTreeNode()); };
            static INLINE std::shared_ptr< BooleanTypeParseTreeNode > MakeValue(const StringT &locstr) { return std::shared_ptr< BooleanTypeParseTreeNode >(new BooleanTypeParseTreeNode(locstr)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class IntegerTypeParseTreeNode : public ParseTreeNode
    {
        private:
        
            static IntegerT Count;
            static IntegerT Instances;
            
        protected:
            INLINE IntegerTypeParseTreeNode() : ParseTreeNode() { ++Count; ++Instances; };
            INLINE IntegerTypeParseTreeNode(const std::string &locstr) : ParseTreeNode(locstr) { ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const IntegerTypeParseTreeNode &ptn) const;
        
        public:
            virtual ~IntegerTypeParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< IntegerTypeParseTreeNode > MakeValue() { return std::shared_ptr< IntegerTypeParseTreeNode >(new IntegerTypeParseTreeNode()); };
            static INLINE std::shared_ptr< IntegerTypeParseTreeNode > MakeValue(const StringT &locstr) { return std::shared_ptr< IntegerTypeParseTreeNode >(new IntegerTypeParseTreeNode(locstr)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class RangedIntegerTypeParseTreeNode : public ParseTreeNode
    {
        private:
            std::shared_ptr< iParseTreeNode > mMinimum;
            std::shared_ptr< iParseTreeNode > mMaximum;
            std::shared_ptr< iParseTreeNode > mBoundary;
        
            static IntegerT Count;
            static IntegerT Instances;
            
        protected:
            INLINE RangedIntegerTypeParseTreeNode(std::shared_ptr< iParseTreeNode > &min, std::shared_ptr< iParseTreeNode > &max, std::shared_ptr< iParseTreeNode > &bound) : 
                ParseTreeNode(), mMinimum(min), mMaximum(max), mBoundary(bound) { assert(0 != mMinimum.get()); assert(0 != mMaximum.get()); assert(0 != mBoundary.get()); ++Count; ++Instances; };
            
            INLINE RangedIntegerTypeParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &min, std::shared_ptr< iParseTreeNode > &max, std::shared_ptr< iParseTreeNode > &bound) : 
                ParseTreeNode(locstr), mMinimum(min), mMaximum(max), mBoundary(bound) { assert(0 != mMinimum.get()); assert(0 != mMaximum.get()); assert(0 != mBoundary.get()); ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const RangedIntegerTypeParseTreeNode &ptn) const;
        
        public:
            virtual ~RangedIntegerTypeParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< RangedIntegerTypeParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &min, std::shared_ptr< iParseTreeNode > &max, std::shared_ptr< iParseTreeNode > &bound) { return std::shared_ptr< RangedIntegerTypeParseTreeNode >(new RangedIntegerTypeParseTreeNode(min, max, bound)); };
            static INLINE std::shared_ptr< RangedIntegerTypeParseTreeNode > MakeValue(const StringT &locstr, std::shared_ptr< iParseTreeNode > &min, std::shared_ptr< iParseTreeNode > &max, std::shared_ptr< iParseTreeNode > &bound) { return std::shared_ptr< RangedIntegerTypeParseTreeNode >(new RangedIntegerTypeParseTreeNode(locstr, min, max, bound)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class RealTypeParseTreeNode : public ParseTreeNode
    {
        private:
        
            static IntegerT Count;
            static IntegerT Instances;
            
        protected:
            INLINE RealTypeParseTreeNode() : ParseTreeNode() { ++Count; ++Instances; };
            INLINE RealTypeParseTreeNode(const std::string &locstr) : ParseTreeNode(locstr) { ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const RealTypeParseTreeNode &ptn) const;
        
        public:
            virtual ~RealTypeParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< RealTypeParseTreeNode > MakeValue() { return std::shared_ptr< RealTypeParseTreeNode >(new RealTypeParseTreeNode()); };
            static INLINE std::shared_ptr< RealTypeParseTreeNode > MakeValue(const StringT &locstr) { return std::shared_ptr< RealTypeParseTreeNode >(new RealTypeParseTreeNode(locstr)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class RangedRealTypeParseTreeNode : public ParseTreeNode
    {
        private:
            std::shared_ptr< iParseTreeNode > mMinimum;
            std::shared_ptr< iParseTreeNode > mMaximum;
            std::shared_ptr< iParseTreeNode > mBoundary;
        
            static IntegerT Count;
            static IntegerT Instances;
            
        protected:
            INLINE RangedRealTypeParseTreeNode(std::shared_ptr< iParseTreeNode > &min, std::shared_ptr< iParseTreeNode > &max, std::shared_ptr< iParseTreeNode > &bound) : 
                ParseTreeNode(), mMinimum(min), mMaximum(max), mBoundary(bound) { assert(0 != mMinimum.get()); assert(0 != mMaximum.get()); assert(0 != mBoundary.get()); ++Count; ++Instances; };
            
            INLINE RangedRealTypeParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &min, std::shared_ptr< iParseTreeNode > &max, std::shared_ptr< iParseTreeNode > &bound) : 
                ParseTreeNode(locstr), mMinimum(min), mMaximum(max), mBoundary(bound) { assert(0 != mMinimum.get()); assert(0 != mMaximum.get()); assert(0 != mBoundary.get()); ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const RangedRealTypeParseTreeNode &ptn) const;
        
        public:
            virtual ~RangedRealTypeParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< RangedRealTypeParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &min, std::shared_ptr< iParseTreeNode > &max, std::shared_ptr< iParseTreeNode > &bound) { return std::shared_ptr< RangedRealTypeParseTreeNode >(new RangedRealTypeParseTreeNode(min, max, bound)); };
            static INLINE std::shared_ptr< RangedRealTypeParseTreeNode > MakeValue(const StringT &locstr, std::shared_ptr< iParseTreeNode > &min, std::shared_ptr< iParseTreeNode > &max, std::shared_ptr< iParseTreeNode > &bound) { return std::shared_ptr< RangedRealTypeParseTreeNode >(new RangedRealTypeParseTreeNode(locstr, min, max, bound)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class StringTypeParseTreeNode : public ParseTreeNode
    {
        private:
        
            static IntegerT Count;
            static IntegerT Instances;
            
        protected:
            INLINE StringTypeParseTreeNode() : ParseTreeNode() { ++Count; ++Instances; };
            INLINE StringTypeParseTreeNode(const std::string &locstr) : ParseTreeNode(locstr) { ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const StringTypeParseTreeNode &ptn) const;
        
        public:
            virtual ~StringTypeParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< StringTypeParseTreeNode > MakeValue() { return std::shared_ptr< StringTypeParseTreeNode >(new StringTypeParseTreeNode()); };
            static INLINE std::shared_ptr< StringTypeParseTreeNode > MakeValue(const StringT &locstr) { return std::shared_ptr< StringTypeParseTreeNode >(new StringTypeParseTreeNode(locstr)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class ArrayTypeParseTreeNode : public ParseTreeNode
    {
        private:
            std::shared_ptr< iParseTreeNode > mFromIndex;
            std::shared_ptr< iParseTreeNode > mToIndex;
            
            std::shared_ptr< iParseTreeNode > mType;
        
            static IntegerT Count;
            static IntegerT Instances;
        
        protected:
            INLINE ArrayTypeParseTreeNode(std::shared_ptr< iParseTreeNode > &from, std::shared_ptr< iParseTreeNode > &to, std::shared_ptr< iParseTreeNode > &type) : 
                ParseTreeNode(), mFromIndex(from), mToIndex(to), mType(type) { assert(mFromIndex); assert(mToIndex); assert(mType); ++Count; ++Instances; };
                
            INLINE ArrayTypeParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &from, std::shared_ptr< iParseTreeNode > &to, std::shared_ptr< iParseTreeNode > &type) : 
                ParseTreeNode(locstr), mFromIndex(from), mToIndex(to), mType(type) { assert(mFromIndex); assert(mToIndex); assert(mType); ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const ArrayTypeParseTreeNode &ptn) const;
        
        public:
            virtual ~ArrayTypeParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< ArrayTypeParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &from, std::shared_ptr< iParseTreeNode > &to, std::shared_ptr< iParseTreeNode > &type) { return std::shared_ptr< ArrayTypeParseTreeNode >(new ArrayTypeParseTreeNode(from, to, type)); };
            static INLINE std::shared_ptr< ArrayTypeParseTreeNode > MakeValue(const StringT &locstr, std::shared_ptr< iParseTreeNode > &from, std::shared_ptr< iParseTreeNode > &to, std::shared_ptr< iParseTreeNode > &type) { return std::shared_ptr< ArrayTypeParseTreeNode >(new ArrayTypeParseTreeNode(locstr, from, to, type)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual void Validate(LanguageSymbolTable &symtab) const;
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class DictionaryTypeParseTreeNode : public ParseTreeNode
    {
        private:
        
            static IntegerT Count;
            static IntegerT Instances;
            
        protected:
            INLINE DictionaryTypeParseTreeNode() : ParseTreeNode() { ++Count; ++Instances; };
            INLINE DictionaryTypeParseTreeNode(const std::string &locstr) : ParseTreeNode(locstr) { ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const DictionaryTypeParseTreeNode &ptn) const;
        
        public:
            virtual ~DictionaryTypeParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< DictionaryTypeParseTreeNode > MakeValue() { return std::shared_ptr< DictionaryTypeParseTreeNode >(new DictionaryTypeParseTreeNode()); };
            static INLINE std::shared_ptr< DictionaryTypeParseTreeNode > MakeValue(const StringT &locstr) { return std::shared_ptr< DictionaryTypeParseTreeNode >(new DictionaryTypeParseTreeNode(locstr)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class StructureTypeParseTreeNode : public ParseTreeNode
    {
        public:
        
#ifdef LIST_TYPE_PREFER_VECTOR
            using MemberListT = std::vector< std::pair< std::string, std::shared_ptr< iParseTreeNode > > >;
#else
            using MemberListT = std::list< std::pair< std::string, std::shared_ptr< iParseTreeNode > > >;
#endif
    
        private:
            MemberListT mMemberList;
            
            std::shared_ptr< StructureTypeAtomic > mStructureNode;
        
            static IntegerT Count;
            static IntegerT Instances;
        
        protected:
            INLINE StructureTypeParseTreeNode() : ParseTreeNode(), mMemberList(), mStructureNode()
            {
#ifdef LIST_TYPE_PREFER_VECTOR
                mMemberList.reserve(LIST_TYPE_PREFER_VECTOR);
#endif

                ++Count;
                ++Instances;
            };
            
            INLINE StructureTypeParseTreeNode(const std::string &locstr) : ParseTreeNode(locstr), mMemberList(), mStructureNode()
            {
#ifdef LIST_TYPE_PREFER_VECTOR
                mMemberList.reserve(LIST_TYPE_PREFER_VECTOR);
#endif

                ++Count;
                ++Instances;
            };
        
        public:
            virtual ~StructureTypeParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< StructureTypeParseTreeNode > MakeValue() { return std::shared_ptr< StructureTypeParseTreeNode >(new StructureTypeParseTreeNode()); };
            static INLINE std::shared_ptr< StructureTypeParseTreeNode > MakeValue(const StringT &locstr) { return std::shared_ptr< StructureTypeParseTreeNode >(new StructureTypeParseTreeNode(locstr)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            void Add(const std::string &id, std::shared_ptr< iParseTreeNode > type);
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class DeclareParseTreeNode : public ParseTreeNode
    {
        private:
            std::shared_ptr< iParseTreeNode > mType;
            const std::string mId;
        
            static IntegerT Count;
            static IntegerT Instances;
        
        protected:
            INLINE DeclareParseTreeNode(std::shared_ptr< iParseTreeNode > &type, const std::string &id) : ParseTreeNode(), mType(type), mId(id) { assert(mType); ++Count; ++Instances; };
            INLINE DeclareParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &type, const std::string &id) : ParseTreeNode(locstr), mType(type), mId(id) { assert(mType); ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const DeclareParseTreeNode &ptn) const;
        
        public:
            virtual ~DeclareParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< DeclareParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &type, const std::string &id) { return std::shared_ptr< DeclareParseTreeNode >(new DeclareParseTreeNode(type, id)); };
            static INLINE std::shared_ptr< DeclareParseTreeNode > MakeValue(const StringT &locstr, std::shared_ptr< iParseTreeNode > &type, const std::string &id) { return std::shared_ptr< DeclareParseTreeNode >(new DeclareParseTreeNode(locstr, type, id)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual void Validate(LanguageSymbolTable &symtab) const;
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
    
    };
    
    class DeclareTypeParseTreeNode : public ParseTreeNode
    {
        private:
            std::shared_ptr< iParseTreeNode > mType;
            const std::string mId;
        
            static IntegerT Count;
            static IntegerT Instances;
        
        protected:
            INLINE DeclareTypeParseTreeNode(std::shared_ptr< iParseTreeNode > &type, const std::string &id) : ParseTreeNode(), mType(type), mId(id) { assert(mType); ++Count; ++Instances; };
            INLINE DeclareTypeParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &type, const std::string &id) : ParseTreeNode(locstr), mType(type), mId(id) { assert(mType); ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const DeclareTypeParseTreeNode &ptn) const;
        
        public:
            virtual ~DeclareTypeParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< DeclareTypeParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &type, const std::string &id) { return std::shared_ptr< DeclareTypeParseTreeNode >(new DeclareTypeParseTreeNode(type, id)); };
            static INLINE std::shared_ptr< DeclareTypeParseTreeNode > MakeValue(const StringT &locstr, std::shared_ptr< iParseTreeNode > &type, const std::string &id) { return std::shared_ptr< DeclareTypeParseTreeNode >(new DeclareTypeParseTreeNode(locstr, type, id)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual void Validate(LanguageSymbolTable &symtab) const;
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    ////
    
    class FunctionParseTreeNode : public ParseTreeNode
    {
        public:
        
            using ParamListT = iExecutableAtomic::ParamListT;
            
            class FunctionValue : public ExecutableAtomic
            {
                private:
                    std::shared_ptr< iParseTreeNode > mBody;
                    
                protected:
                    INLINE FunctionValue(const ParamListT &params, std::shared_ptr< iParseTreeNode > &body) : ExecutableAtomic(), mBody(body) { assert(0 != mBody.get()); AddParam(params); };
                
                public:
                
                    static INLINE std::shared_ptr< FunctionValue > MakeValue(const ParamListT &params, std::shared_ptr< iParseTreeNode > &body) { return std::shared_ptr< FunctionValue >(new FunctionValue(params, body)); };
                
                    //  From iAtomic
                    
                    virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
                    virtual void Validate(LanguageSymbolTable &symtab) const;
                
            };
            
        private:
            ParamListT mFormalParameters;
            
            std::shared_ptr< iParseTreeNode > mBody;
            
        protected:
            INLINE FunctionParseTreeNode(const ParamListT &params, std::shared_ptr< iParseTreeNode > &body) : ParseTreeNode(), mFormalParameters(params), mBody(body) { assert(0 != mBody.get()); };
            INLINE FunctionParseTreeNode(const std::string &locstr, const ParamListT &params, std::shared_ptr< iParseTreeNode > &body) : ParseTreeNode(locstr), mFormalParameters(params), mBody(body) { assert(0 != mBody.get()); };

            INLINE const ParamListT &formalParameters() const { return mFormalParameters; };
            INLINE ParamListT &formalParameters() { return mFormalParameters; };
            
            INLINE const std::shared_ptr< iParseTreeNode > &body() const { return mBody; };
            INLINE std::shared_ptr< iParseTreeNode > &body() { return mBody; };

    };
    
    class DeclareFunctionParseTreeNode : public FunctionParseTreeNode
    {
        private:
            const std::string mId;
        
            static IntegerT Count;
            static IntegerT Instances;
    
        protected:
            INLINE DeclareFunctionParseTreeNode(const std::string &id, const ParamListT &params, std::shared_ptr< iParseTreeNode > &body) : FunctionParseTreeNode(params, body), mId(id) { ++Count; ++Instances; };
            INLINE DeclareFunctionParseTreeNode(const std::string &locstr, const std::string &id, const ParamListT &params, std::shared_ptr< iParseTreeNode > &body) : FunctionParseTreeNode(locstr, params, body), mId(id) { ++Count; ++Instances; };
        
        public:
            virtual ~DeclareFunctionParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< DeclareFunctionParseTreeNode > MakeValue(const std::string &id, const ParamListT &params, std::shared_ptr< iParseTreeNode > &body) { return std::shared_ptr< DeclareFunctionParseTreeNode >(new DeclareFunctionParseTreeNode(id, params, body)); };
            static INLINE std::shared_ptr< DeclareFunctionParseTreeNode > MakeValue(const StringT &locstr, const std::string &id, const ParamListT &params, std::shared_ptr< iParseTreeNode > &body) { return std::shared_ptr< DeclareFunctionParseTreeNode >(new DeclareFunctionParseTreeNode(locstr, id, params, body)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual void Validate(LanguageSymbolTable &symtab) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class LambdaFunctionParseTreeNode : public FunctionParseTreeNode
    {
        private:
        
            static IntegerT Count;
            static IntegerT Instances;
        
        protected:
            INLINE LambdaFunctionParseTreeNode(const ParamListT &params, std::shared_ptr< iParseTreeNode > &body) : FunctionParseTreeNode(params, body) { ++Count; ++Instances; };
            INLINE LambdaFunctionParseTreeNode(const std::string &locstr, const ParamListT &params, std::shared_ptr< iParseTreeNode > &body) : FunctionParseTreeNode(locstr, params, body) { ++Count; ++Instances; };
        
        public:
            virtual ~LambdaFunctionParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< LambdaFunctionParseTreeNode > MakeValue(const ParamListT &params, std::shared_ptr< iParseTreeNode > &body) { return std::shared_ptr< LambdaFunctionParseTreeNode >(new LambdaFunctionParseTreeNode(params, body)); };
            static INLINE std::shared_ptr< LambdaFunctionParseTreeNode > MakeValue(const StringT &locstr, const ParamListT &params, std::shared_ptr< iParseTreeNode > &body) { return std::shared_ptr< LambdaFunctionParseTreeNode >(new LambdaFunctionParseTreeNode(locstr, params, body)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual void Validate(LanguageSymbolTable &symtab) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    ////
    
    class DeclareReferenceParseTreeNode : public ParseTreeNode
    {
        private:
            const std::string mId;
            
            std::shared_ptr< iParseTreeNode > mExpression;
        
            static IntegerT Count;
            static IntegerT Instances;
        
        protected:
            INLINE DeclareReferenceParseTreeNode(const std::string &id, std::shared_ptr< iParseTreeNode > &expr) : 
                ParseTreeNode(), mId(id), mExpression(expr) { assert(mExpression); ++Count; ++Instances; };
                
            INLINE DeclareReferenceParseTreeNode(const std::string &locstr, const std::string &id, std::shared_ptr< iParseTreeNode > &expr) : 
                ParseTreeNode(locstr), mId(id), mExpression(expr) { assert(mExpression); ++Count; ++Instances; };
        
        public:
            virtual ~DeclareReferenceParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< DeclareReferenceParseTreeNode > MakeValue(const std::string &id, std::shared_ptr< iParseTreeNode > &expr) { return std::shared_ptr< DeclareReferenceParseTreeNode >(new DeclareReferenceParseTreeNode(id, expr)); };
            static INLINE std::shared_ptr< DeclareReferenceParseTreeNode > MakeValue(const StringT &locstr, const std::string &id, std::shared_ptr< iParseTreeNode > &expr) { return std::shared_ptr< DeclareReferenceParseTreeNode >(new DeclareReferenceParseTreeNode(locstr, id, expr)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual void Validate(LanguageSymbolTable &symtab) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class AssignmentParseTreeNode : public ParseTreeNode
    {
        private:
            std::shared_ptr< iParseTreeNode > mLeftHandSide;
            std::shared_ptr< iParseTreeNode > mRightHandSide;
        
            static IntegerT Count;
            static IntegerT Instances;
        
        protected:
            INLINE AssignmentParseTreeNode(std::shared_ptr< iParseTreeNode > &lhs, std::shared_ptr< iParseTreeNode > &rhs) : 
                ParseTreeNode(), mLeftHandSide(lhs), mRightHandSide(rhs) { assert(mLeftHandSide); assert(mRightHandSide); ++Count; ++Instances; };
                
            INLINE AssignmentParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &lhs, std::shared_ptr< iParseTreeNode > &rhs) : 
                ParseTreeNode(locstr), mLeftHandSide(lhs), mRightHandSide(rhs) { assert(mLeftHandSide); assert(mRightHandSide); ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const AssignmentParseTreeNode &ptn) const;
        
        public:
            virtual ~AssignmentParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< AssignmentParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &lhs, std::shared_ptr< iParseTreeNode > &rhs) { return std::shared_ptr< AssignmentParseTreeNode >(new AssignmentParseTreeNode(lhs, rhs)); };
            static INLINE std::shared_ptr< AssignmentParseTreeNode > MakeValue(const StringT &locstr, std::shared_ptr< iParseTreeNode > &lhs, std::shared_ptr< iParseTreeNode > &rhs) { return std::shared_ptr< AssignmentParseTreeNode >(new AssignmentParseTreeNode(locstr, lhs, rhs)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual void Validate(LanguageSymbolTable &symtab) const;
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class IndexParseTreeNode : public ParseTreeNode
    {
        private:
            std::shared_ptr< iParseTreeNode > mBase;
            std::shared_ptr< iParseTreeNode > mIndex;
        
            static IntegerT Count;
            static IntegerT Instances;
        
        protected:
            INLINE IndexParseTreeNode(std::shared_ptr< iParseTreeNode > &base, std::shared_ptr< iParseTreeNode > &index) : 
                ParseTreeNode(), mBase(base), mIndex(index) { assert(mBase); assert(mIndex); ++Count; ++Instances; };
                
            INLINE IndexParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &base, std::shared_ptr< iParseTreeNode > &index) : 
                ParseTreeNode(locstr), mBase(base), mIndex(index) { assert(mBase); assert(mIndex); ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const IndexParseTreeNode &ptn) const;
        
        public:
            virtual ~IndexParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< IndexParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &base, std::shared_ptr< iParseTreeNode > &index) { return std::shared_ptr< IndexParseTreeNode >(new IndexParseTreeNode(base, index)); };
            static INLINE std::shared_ptr< IndexParseTreeNode > MakeValue(const StringT &locstr, std::shared_ptr< iParseTreeNode > &base, std::shared_ptr< iParseTreeNode > &index) { return std::shared_ptr< IndexParseTreeNode >(new IndexParseTreeNode(locstr, base, index)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual void Validate(LanguageSymbolTable &symtab) const;
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class MemberParseTreeNode : public ParseTreeNode
    {
        private:
            std::shared_ptr< iParseTreeNode > mBase;
            const std::string mMember;
        
            static IntegerT Count;
            static IntegerT Instances;
        
        protected:
            INLINE MemberParseTreeNode(std::shared_ptr< iParseTreeNode > &base, const std::string &member) : 
                ParseTreeNode(), mBase(base), mMember(member) { assert(mBase); ++Count; ++Instances; };
                
            INLINE MemberParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &base, const std::string &member) : 
                ParseTreeNode(locstr), mBase(base), mMember(member) { assert(mBase); ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const MemberParseTreeNode &ptn) const;
        
        public:
            virtual ~MemberParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< MemberParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &base, const std::string &member) { return std::shared_ptr< MemberParseTreeNode >(new MemberParseTreeNode(base, member)); };
            static INLINE std::shared_ptr< MemberParseTreeNode > MakeValue(const StringT &locstr, std::shared_ptr< iParseTreeNode > &base, const std::string &member) { return std::shared_ptr< MemberParseTreeNode >(new MemberParseTreeNode(locstr, base, member)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual void Validate(LanguageSymbolTable &symtab) const;
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class FunctionCallParseTreeNode : public ParseTreeNode
    {
        public:
        
#ifdef LIST_TYPE_PREFER_VECTOR
            using ParameterListT = std::vector< std::shared_ptr< iParseTreeNode > >;
#else
            using ParameterListT = std::list< std::shared_ptr< iParseTreeNode > >;
#endif
    
        private:
            std::shared_ptr< iParseTreeNode > mFunction;
            ParameterListT mParameterList;
        
            static IntegerT Count;
            static IntegerT Instances;
        
        protected:
            INLINE FunctionCallParseTreeNode(std::shared_ptr< iParseTreeNode > &function) : ParseTreeNode(), mFunction(function), mParameterList()
            {
                assert(mFunction);
                
#ifdef LIST_TYPE_PREFER_VECTOR
                mParameterList.reserve(LIST_TYPE_PREFER_VECTOR);
#endif

                ++Count;
                ++Instances;
            };
                
            INLINE FunctionCallParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &function) : ParseTreeNode(locstr), mFunction(function), mParameterList()
            {
                assert(mFunction);
                
#ifdef LIST_TYPE_PREFER_VECTOR
                mParameterList.reserve(LIST_TYPE_PREFER_VECTOR);
#endif

                ++Count;
                ++Instances;
            };
            
            INLINE FunctionCallParseTreeNode(std::shared_ptr< iParseTreeNode > &function, const ParameterListT &plist) : ParseTreeNode(), mFunction(function), mParameterList(plist.begin(), plist.end())
            {
                assert(mFunction);
                
#ifdef LIST_TYPE_PREFER_VECTOR
                mParameterList.reserve(LIST_TYPE_PREFER_VECTOR);
#endif

                ++Count;
                ++Instances;
            };
                
            INLINE FunctionCallParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &function, const ParameterListT &plist) : ParseTreeNode(locstr), mFunction(function), mParameterList(plist.begin(), plist.end())
            {
                assert(mFunction);
                
#ifdef LIST_TYPE_PREFER_VECTOR
                mParameterList.reserve(LIST_TYPE_PREFER_VECTOR);
#endif

                ++Count;
                ++Instances;
            };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const FunctionCallParseTreeNode &ptn) const;
        
        public:
            virtual ~FunctionCallParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< FunctionCallParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > function) { return std::shared_ptr< FunctionCallParseTreeNode >(new FunctionCallParseTreeNode(function)); };
            static INLINE std::shared_ptr< FunctionCallParseTreeNode > MakeValue(const std::string &locstr, std::shared_ptr< iParseTreeNode > function) { return std::shared_ptr< FunctionCallParseTreeNode >(new FunctionCallParseTreeNode(locstr, function)); };
            
            static INLINE std::shared_ptr< FunctionCallParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > function, const ParameterListT &plist) { return std::shared_ptr< FunctionCallParseTreeNode >(new FunctionCallParseTreeNode(function, plist)); };
            static INLINE std::shared_ptr< FunctionCallParseTreeNode > MakeValue(const std::string &locstr, std::shared_ptr< iParseTreeNode > function, const ParameterListT &plist) { return std::shared_ptr< FunctionCallParseTreeNode >(new FunctionCallParseTreeNode(locstr, function, plist)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            INLINE void Add(std::shared_ptr< iParseTreeNode > param) { assert(param); mParameterList.push_back(param); };
            INLINE void Add(const ParameterListT &plist) { mParameterList.insert(mParameterList.end(), plist.begin(), plist.end()); };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual void Validate(LanguageSymbolTable &symtab) const;
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class ReturnParseTreeNode : public ParseTreeNode
    {
        public:
        
            using ReturnValueT = std::shared_ptr< iAtomic >;
        
            static IntegerT Count;
            static IntegerT Instances;
    
        private:
            std::shared_ptr< iParseTreeNode > mReturn;
        
        protected:
            INLINE ReturnParseTreeNode(std::shared_ptr< iParseTreeNode > &ret) : ParseTreeNode(), mReturn(ret) { ++Count; ++Instances; };
            INLINE ReturnParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &ret) : ParseTreeNode(locstr), mReturn(ret) { ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const ReturnParseTreeNode &ptn) const;
        
        public:
            virtual ~ReturnParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< ReturnParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &ret) { return std::shared_ptr< ReturnParseTreeNode >(new ReturnParseTreeNode(ret)); };
            static INLINE std::shared_ptr< ReturnParseTreeNode > MakeValue(const std::string &locstr, std::shared_ptr< iParseTreeNode > &ret) { return std::shared_ptr< ReturnParseTreeNode >(new ReturnParseTreeNode(locstr, ret)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual void Validate(LanguageSymbolTable &symtab) const;
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class OneOprParseTreeNode : public ParseTreeNode
    {
        protected:
            std::shared_ptr< iParseTreeNode > mOpr;
            
            INLINE OneOprParseTreeNode(std::shared_ptr< iParseTreeNode > opr) : ParseTreeNode(), mOpr(opr) { assert(0 != mOpr.get()); };
            INLINE OneOprParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &opr) : ParseTreeNode(locstr), mOpr(opr) { assert(0 != mOpr.get()); };
            
            INLINE bool equal(const OneOprParseTreeNode &ptn) const { return mOpr->IsEqual(*(ptn.mOpr)); };
            
        public:
            
            //  From iParseTreeNode
            
            virtual bool IsLiteral() const;
            
            virtual void Validate(LanguageSymbolTable &symtab) const;
            
    };
    
    class TwoOprParseTreeNode : public ParseTreeNode
    {
        protected:
            std::shared_ptr< iParseTreeNode > mOpr1;
            std::shared_ptr< iParseTreeNode > mOpr2;
            
            INLINE TwoOprParseTreeNode(std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) : 
                ParseTreeNode(), mOpr1(opr1), mOpr2(opr2) { assert(0 != mOpr1.get()); assert(0 != mOpr2.get()); };
                
            INLINE TwoOprParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) : 
                ParseTreeNode(locstr), mOpr1(opr1), mOpr2(opr2) { assert(0 != mOpr1.get()); assert(0 != mOpr2.get()); };
                
            INLINE bool equal(const TwoOprParseTreeNode &ptn) const { return (mOpr1->IsEqual(*(ptn.mOpr1)) && mOpr2->IsEqual(*(ptn.mOpr2))); };
        
        public:
            
            //  From iParseTreeNode
            
            virtual bool IsLiteral() const;
            
            virtual void Validate(LanguageSymbolTable &symtab) const;
            
    };
    
    class ChainedOprParseTreeNode : public ParseTreeNode
    {
        public:
        
            using ChainedOprListT = std::list< std::shared_ptr< iParseTreeNode > >;
        
        protected:
            ChainedOprListT mOprList;
            
            INLINE ChainedOprParseTreeNode() : ParseTreeNode(), mOprList() {};
            INLINE ChainedOprParseTreeNode(std::shared_ptr< iParseTreeNode > &opr) : ParseTreeNode(), mOprList() { assert(0 != opr.get()); mOprList.push_back(opr); };
            
            INLINE ChainedOprParseTreeNode(const std::string &locstr) : ParseTreeNode(locstr), mOprList() {};
            INLINE ChainedOprParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &opr) : ParseTreeNode(locstr), mOprList() { assert(0 != opr.get()); mOprList.push_back(opr); };
            
            bool equal(const ChainedOprParseTreeNode &ptn) const;
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > opr1, std::shared_ptr< iAtomic > opr2) = 0;
        
        public:
        
            void AddOperand(std::shared_ptr< iParseTreeNode > opr);
            
            //  From iParseTreeNode
            
            virtual bool IsLiteral() const;
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class NegateOpParseTreeNode : public OneOprParseTreeNode
    {
        private:
        
            static IntegerT Count;
            static IntegerT Instances;
    
        protected:
            INLINE NegateOpParseTreeNode(std::shared_ptr< iParseTreeNode > &opr) : OneOprParseTreeNode(opr) { ++Count; ++Instances; };
            INLINE NegateOpParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &opr) : OneOprParseTreeNode(locstr, opr) { ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const NegateOpParseTreeNode &ptn) const;
            
        public:
            virtual ~NegateOpParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< NegateOpParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &opr) { return std::shared_ptr< NegateOpParseTreeNode >(new NegateOpParseTreeNode(opr)); };
            static INLINE std::shared_ptr< NegateOpParseTreeNode > MakeValue(const std::string &locstr, std::shared_ptr< iParseTreeNode > &opr) { return std::shared_ptr< NegateOpParseTreeNode >(new NegateOpParseTreeNode(locstr, opr)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute();
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class AddOpChainParseTreeNode : public ChainedOprParseTreeNode
    {
        private:
        
            static IntegerT Count;
            static IntegerT Instances;
    
        protected:
            INLINE AddOpChainParseTreeNode(std::shared_ptr< iParseTreeNode > &term) : ChainedOprParseTreeNode(term) { ++Count; ++Instances; };
            INLINE AddOpChainParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &term) : ChainedOprParseTreeNode(locstr, term) { ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const AddOpChainParseTreeNode &ptn) const;
            
            //  From ChainedOprParseTreeNode
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > opr1, std::shared_ptr< iAtomic > opr2);
            
            virtual std::string oprString() const;
        
        public:
            virtual ~AddOpChainParseTreeNode() { --Instances; };
        
            static INLINE std::shared_ptr< AddOpChainParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &term) { return std::shared_ptr< AddOpChainParseTreeNode >(new AddOpChainParseTreeNode(term)); };
            static INLINE std::shared_ptr< AddOpChainParseTreeNode > MakeValue(const std::string &locstr, std::shared_ptr< iParseTreeNode > &term) { return std::shared_ptr< AddOpChainParseTreeNode >(new AddOpChainParseTreeNode(locstr, term)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute();
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class SubOpParseTreeNode : public TwoOprParseTreeNode
    {
        private:
        
            static IntegerT Count;
            static IntegerT Instances;
    
        protected:
            INLINE SubOpParseTreeNode(std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) : TwoOprParseTreeNode(opr1, opr2) { ++Count; ++Instances; };
            INLINE SubOpParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) : TwoOprParseTreeNode(locstr, opr1, opr2) { ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const SubOpParseTreeNode &ptn) const;
            
        public:
            virtual ~SubOpParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< SubOpParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) { return std::shared_ptr< SubOpParseTreeNode >(new SubOpParseTreeNode(opr1, opr2)); };
            static INLINE std::shared_ptr< SubOpParseTreeNode > MakeValue(const std::string &locstr, std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) { return std::shared_ptr< SubOpParseTreeNode >(new SubOpParseTreeNode(locstr, opr1, opr2)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute();
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class MulOpChainParseTreeNode : public ChainedOprParseTreeNode
    {
        private:
        
            static IntegerT Count;
            static IntegerT Instances;
    
        protected:
            INLINE MulOpChainParseTreeNode(std::shared_ptr< iParseTreeNode > &term) : ChainedOprParseTreeNode(term) { ++Count; ++Instances; };
            INLINE MulOpChainParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &term) : ChainedOprParseTreeNode(locstr, term) { ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const MulOpChainParseTreeNode &ptn) const;
            
            //  From ChainedOprParseTreeNode
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > opr1, std::shared_ptr< iAtomic > opr2);
            
            virtual std::string oprString() const;
        
        public:
            virtual ~MulOpChainParseTreeNode() { --Instances; };
        
            static INLINE std::shared_ptr< MulOpChainParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &term) { return std::shared_ptr< MulOpChainParseTreeNode >(new MulOpChainParseTreeNode(term)); };
            static INLINE std::shared_ptr< MulOpChainParseTreeNode > MakeValue(const std::string &locstr, std::shared_ptr< iParseTreeNode > &term) { return std::shared_ptr< MulOpChainParseTreeNode >(new MulOpChainParseTreeNode(locstr, term)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute();
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
            
    };
    
    class DivOpParseTreeNode : public TwoOprParseTreeNode
    {
        private:
        
            static IntegerT Count;
            static IntegerT Instances;
    
        protected:
            INLINE DivOpParseTreeNode(std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) : TwoOprParseTreeNode(opr1, opr2) { ++Count; ++Instances; };
            INLINE DivOpParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) : TwoOprParseTreeNode(locstr, opr1, opr2) { ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const DivOpParseTreeNode &ptn) const;
            
        public:
            virtual ~DivOpParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< DivOpParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) { return std::shared_ptr< DivOpParseTreeNode >(new DivOpParseTreeNode(opr1, opr2)); };
            static INLINE std::shared_ptr< DivOpParseTreeNode > MakeValue(const std::string &locstr, std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) { return std::shared_ptr< DivOpParseTreeNode >(new DivOpParseTreeNode(locstr, opr1, opr2)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute();
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class ModOpParseTreeNode : public TwoOprParseTreeNode
    {
        private:
        
            static IntegerT Count;
            static IntegerT Instances;
    
        protected:
            INLINE ModOpParseTreeNode(std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) : TwoOprParseTreeNode(opr1, opr2) { ++Count; ++Instances; };
            INLINE ModOpParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) : TwoOprParseTreeNode(locstr, opr1, opr2) { ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const ModOpParseTreeNode &ptn) const;
            
        public:
            virtual ~ModOpParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< ModOpParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) { return std::shared_ptr< ModOpParseTreeNode >(new ModOpParseTreeNode(opr1, opr2)); };
            static INLINE std::shared_ptr< ModOpParseTreeNode > MakeValue(const std::string &locstr, std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) { return std::shared_ptr< ModOpParseTreeNode >(new ModOpParseTreeNode(locstr, opr1, opr2)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute();
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class PowOpParseTreeNode : public TwoOprParseTreeNode
    {
        private:
        
            static IntegerT Count;
            static IntegerT Instances;
    
        protected:
            INLINE PowOpParseTreeNode(std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) : TwoOprParseTreeNode(opr1, opr2) { ++Count; ++Instances; };
            INLINE PowOpParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) : TwoOprParseTreeNode(locstr, opr1, opr2) { ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const PowOpParseTreeNode &ptn) const;
            
        public:
            virtual ~PowOpParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< PowOpParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) { return std::shared_ptr< PowOpParseTreeNode >(new PowOpParseTreeNode(opr1, opr2)); };
            static INLINE std::shared_ptr< PowOpParseTreeNode > MakeValue(const std::string &locstr, std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) { return std::shared_ptr< PowOpParseTreeNode >(new PowOpParseTreeNode(locstr, opr1, opr2)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute();
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class NotOpParseTreeNode : public OneOprParseTreeNode
    {
        private:
        
            static IntegerT Count;
            static IntegerT Instances;
    
        protected:
            INLINE NotOpParseTreeNode(std::shared_ptr< iParseTreeNode > &opr) : OneOprParseTreeNode(opr) { ++Count; ++Instances; };
            INLINE NotOpParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &opr) : OneOprParseTreeNode(locstr, opr) { ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const NotOpParseTreeNode &ptn) const;
            
        public:
            virtual ~NotOpParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< NotOpParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &opr) { return std::shared_ptr< NotOpParseTreeNode >(new NotOpParseTreeNode(opr)); };
            static INLINE std::shared_ptr< NotOpParseTreeNode > MakeValue(const std::string &locstr, std::shared_ptr< iParseTreeNode > &opr) { return std::shared_ptr< NotOpParseTreeNode >(new NotOpParseTreeNode(locstr, opr)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute();
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class AndOpChainParseTreeNode : public ChainedOprParseTreeNode
    {
        private:
        
            static IntegerT Count;
            static IntegerT Instances;
    
        protected:
            INLINE AndOpChainParseTreeNode(std::shared_ptr< iParseTreeNode > &term) : ChainedOprParseTreeNode(term) { ++Count; ++Instances; };
            INLINE AndOpChainParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &term) : ChainedOprParseTreeNode(locstr, term) { ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const AndOpChainParseTreeNode &ptn) const;
            
            //  From ChainedOprParseTreeNode
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > opr1, std::shared_ptr< iAtomic > opr2);
            
            virtual std::string oprString() const;
        
        public:
            virtual ~AndOpChainParseTreeNode() { --Instances; };
        
            static INLINE std::shared_ptr< AndOpChainParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &term) { return std::shared_ptr< AndOpChainParseTreeNode >(new AndOpChainParseTreeNode(term)); };
            static INLINE std::shared_ptr< AndOpChainParseTreeNode > MakeValue(const std::string &locstr, std::shared_ptr< iParseTreeNode > &term) { return std::shared_ptr< AndOpChainParseTreeNode >(new AndOpChainParseTreeNode(locstr, term)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute();
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
            
    };
    
    class OrOpChainParseTreeNode : public ChainedOprParseTreeNode
    {
        private:
        
            static IntegerT Count;
            static IntegerT Instances;
    
        protected:
            INLINE OrOpChainParseTreeNode(std::shared_ptr< iParseTreeNode > &term) : ChainedOprParseTreeNode(term) { ++Count; ++Instances; };
            INLINE OrOpChainParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &term) : ChainedOprParseTreeNode(locstr, term) { ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const OrOpChainParseTreeNode &ptn) const;
            
            //  From ChainedOprParseTreeNode
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > opr1, std::shared_ptr< iAtomic > opr2);
            
            virtual std::string oprString() const;
            
        
        public:
            virtual ~OrOpChainParseTreeNode() { --Instances; };
        
            static INLINE std::shared_ptr< OrOpChainParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &term) { return std::shared_ptr< OrOpChainParseTreeNode >(new OrOpChainParseTreeNode(term)); };
            static INLINE std::shared_ptr< OrOpChainParseTreeNode > MakeValue(const std::string &locstr, std::shared_ptr< iParseTreeNode > &term) { return std::shared_ptr< OrOpChainParseTreeNode >(new OrOpChainParseTreeNode(locstr, term)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute();
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
            
    };
    
    class XorOpChainParseTreeNode : public ChainedOprParseTreeNode
    {
        private:
        
            static IntegerT Count;
            static IntegerT Instances;
    
        protected:
            INLINE XorOpChainParseTreeNode(std::shared_ptr< iParseTreeNode > &term) : ChainedOprParseTreeNode(term) { ++Count; ++Instances; };
            INLINE XorOpChainParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &term) : ChainedOprParseTreeNode(locstr, term) { ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const XorOpChainParseTreeNode &ptn) const;
            
            //  From ChainedOprParseTreeNode
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > opr1, std::shared_ptr< iAtomic > opr2);
            
            virtual std::string oprString() const;
        
        public:
            virtual ~XorOpChainParseTreeNode() { --Instances; };
        
            static INLINE std::shared_ptr< XorOpChainParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &term) { return std::shared_ptr< XorOpChainParseTreeNode >(new XorOpChainParseTreeNode(term)); };
            static INLINE std::shared_ptr< XorOpChainParseTreeNode > MakeValue(const std::string &locstr, std::shared_ptr< iParseTreeNode > &term) { return std::shared_ptr< XorOpChainParseTreeNode >(new XorOpChainParseTreeNode(locstr, term)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute();
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
            
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class LessThanOpParseTreeNode : public TwoOprParseTreeNode
    {
        private:
        
            static IntegerT Count;
            static IntegerT Instances;
    
        protected:
            INLINE LessThanOpParseTreeNode(std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) : TwoOprParseTreeNode(opr1, opr2) { ++Count; ++Instances; };
            INLINE LessThanOpParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) : TwoOprParseTreeNode(locstr, opr1, opr2) { ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const LessThanOpParseTreeNode &ptn) const;
            
        public:
            virtual ~LessThanOpParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< LessThanOpParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) { return std::shared_ptr< LessThanOpParseTreeNode >(new LessThanOpParseTreeNode(opr1, opr2)); };
            static INLINE std::shared_ptr< LessThanOpParseTreeNode > MakeValue(const std::string &locstr, std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) { return std::shared_ptr< LessThanOpParseTreeNode >(new LessThanOpParseTreeNode(locstr, opr1, opr2)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute();
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class LessThanEqualOpParseTreeNode : public TwoOprParseTreeNode
    {
        private:
        
            static IntegerT Count;
            static IntegerT Instances;
    
        protected:
            INLINE LessThanEqualOpParseTreeNode(std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) : TwoOprParseTreeNode(opr1, opr2) { ++Count; ++Instances; };
            INLINE LessThanEqualOpParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) : TwoOprParseTreeNode(locstr, opr1, opr2) { ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const LessThanEqualOpParseTreeNode &ptn) const;
            
        public:
            virtual ~LessThanEqualOpParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< LessThanEqualOpParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) { return std::shared_ptr< LessThanEqualOpParseTreeNode >(new LessThanEqualOpParseTreeNode(opr1, opr2)); };
            static INLINE std::shared_ptr< LessThanEqualOpParseTreeNode > MakeValue(const std::string &locstr, std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) { return std::shared_ptr< LessThanEqualOpParseTreeNode >(new LessThanEqualOpParseTreeNode(locstr, opr1, opr2)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute();
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class EqualOpParseTreeNode : public TwoOprParseTreeNode
    {
        private:
        
            static IntegerT Count;
            static IntegerT Instances;
    
        protected:
            INLINE EqualOpParseTreeNode(std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) : TwoOprParseTreeNode(opr1, opr2) { ++Count; ++Instances; };
            INLINE EqualOpParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) : TwoOprParseTreeNode(locstr, opr1, opr2) { ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const EqualOpParseTreeNode &ptn) const;
            
        public:
            virtual ~EqualOpParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< EqualOpParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) { return std::shared_ptr< EqualOpParseTreeNode >(new EqualOpParseTreeNode(opr1, opr2)); };
            static INLINE std::shared_ptr< EqualOpParseTreeNode > MakeValue(const std::string &locstr, std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) { return std::shared_ptr< EqualOpParseTreeNode >(new EqualOpParseTreeNode(locstr, opr1, opr2)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute();
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class NotEqualOpParseTreeNode : public TwoOprParseTreeNode
    {
        private:
        
            static IntegerT Count;
            static IntegerT Instances;
    
        protected:
            INLINE NotEqualOpParseTreeNode(std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) : TwoOprParseTreeNode(opr1, opr2) { ++Count; ++Instances; };
            INLINE NotEqualOpParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) : TwoOprParseTreeNode(locstr, opr1, opr2) { ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const NotEqualOpParseTreeNode &ptn) const;
            
        public:
            virtual ~NotEqualOpParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< NotEqualOpParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) { return std::shared_ptr< NotEqualOpParseTreeNode >(new NotEqualOpParseTreeNode(opr1, opr2)); };
            static INLINE std::shared_ptr< NotEqualOpParseTreeNode > MakeValue(const std::string &locstr, std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) { return std::shared_ptr< NotEqualOpParseTreeNode >(new NotEqualOpParseTreeNode(locstr, opr1, opr2)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute();
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class GreaterThanEqualOpParseTreeNode : public TwoOprParseTreeNode
    {
        private:
        
            static IntegerT Count;
            static IntegerT Instances;
    
        protected:
            INLINE GreaterThanEqualOpParseTreeNode(std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) : TwoOprParseTreeNode(opr1, opr2) { ++Count; ++Instances; };
            INLINE GreaterThanEqualOpParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) : TwoOprParseTreeNode(locstr, opr1, opr2) { ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const GreaterThanEqualOpParseTreeNode &ptn) const;
            
        public:
            virtual ~GreaterThanEqualOpParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< GreaterThanEqualOpParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) { return std::shared_ptr< GreaterThanEqualOpParseTreeNode >(new GreaterThanEqualOpParseTreeNode(opr1, opr2)); };
            static INLINE std::shared_ptr< GreaterThanEqualOpParseTreeNode > MakeValue(const std::string &locstr, std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) { return std::shared_ptr< GreaterThanEqualOpParseTreeNode >(new GreaterThanEqualOpParseTreeNode(locstr, opr1, opr2)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute();
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class GreaterThanOpParseTreeNode : public TwoOprParseTreeNode
    {
        private:
        
            static IntegerT Count;
            static IntegerT Instances;
    
        protected:
            INLINE GreaterThanOpParseTreeNode(std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) : TwoOprParseTreeNode(opr1, opr2) { ++Count; ++Instances; };
            INLINE GreaterThanOpParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) : TwoOprParseTreeNode(locstr, opr1, opr2) { ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const GreaterThanOpParseTreeNode &ptn) const;
            
        public:
            virtual ~GreaterThanOpParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< GreaterThanOpParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) { return std::shared_ptr< GreaterThanOpParseTreeNode >(new GreaterThanOpParseTreeNode(opr1, opr2)); };
            static INLINE std::shared_ptr< GreaterThanOpParseTreeNode > MakeValue(const std::string &locstr, std::shared_ptr< iParseTreeNode > &opr1, std::shared_ptr< iParseTreeNode > &opr2) { return std::shared_ptr< GreaterThanOpParseTreeNode >(new GreaterThanOpParseTreeNode(locstr, opr1, opr2)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute();
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class StatementBlockParseTreeNode : public ParseTreeNode
    {
        public:
        
#ifdef LIST_TYPE_PREFER_VECTOR
            using StatementBlockT = std::vector< std::shared_ptr< iParseTreeNode > >;
#else
            using StatementBlockT = std::list< std::shared_ptr< iParseTreeNode > >;
#endif
    
        private:
            StatementBlockT mBlock;
        
            static IntegerT Count;
            static IntegerT Instances;
    
        protected:
            INLINE StatementBlockParseTreeNode() : ParseTreeNode(), mBlock()
            {
#ifdef LIST_TYPE_PREFER_VECTOR
                mBlock.reserve(LIST_TYPE_PREFER_VECTOR);
#endif

                ++Count;
                ++Instances;
            };
            
            INLINE StatementBlockParseTreeNode(const std::string &locstr) : ParseTreeNode(locstr), mBlock()
            {
#ifdef LIST_TYPE_PREFER_VECTOR
                mBlock.reserve(LIST_TYPE_PREFER_VECTOR);
#endif

                ++Count;
                ++Instances;
            };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const StatementBlockParseTreeNode &ptn) const;
            
        public:
            virtual ~StatementBlockParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< StatementBlockParseTreeNode > MakeValue() { return std::shared_ptr< StatementBlockParseTreeNode >(new StatementBlockParseTreeNode()); };
            static INLINE std::shared_ptr< StatementBlockParseTreeNode > MakeValue(const std::string &locstr) { return std::shared_ptr< StatementBlockParseTreeNode >(new StatementBlockParseTreeNode(locstr)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            INLINE void Add(std::shared_ptr< iParseTreeNode > &stmt) { assert(stmt); mBlock.push_back(stmt); };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual void Validate(LanguageSymbolTable &symtab) const;
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class IfStatementParseTreeNode : public ParseTreeNode
    {
        private:
            std::shared_ptr< iParseTreeNode > mCondition;
            std::shared_ptr< iParseTreeNode > mIfBlock;
            std::shared_ptr< iParseTreeNode > mElseBlock;
        
            static IntegerT Count;
            static IntegerT Instances;
        
        protected:
            INLINE IfStatementParseTreeNode(std::shared_ptr< iParseTreeNode > &cond, std::shared_ptr< iParseTreeNode > &ifblk) : 
                ParseTreeNode(), mCondition(cond), mIfBlock(ifblk), mElseBlock() { assert(mCondition); assert(mIfBlock); ++Count; ++Instances; };
                
            INLINE IfStatementParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &cond, std::shared_ptr< iParseTreeNode > &ifblk) : 
                ParseTreeNode(locstr), mCondition(cond), mIfBlock(ifblk), mElseBlock() { assert(mCondition); assert(mIfBlock); ++Count; ++Instances; };
            
            INLINE IfStatementParseTreeNode(std::shared_ptr< iParseTreeNode > &cond, std::shared_ptr< iParseTreeNode > &ifblk, std::shared_ptr< iParseTreeNode > &elseblk) : 
                ParseTreeNode(), mCondition(cond), mIfBlock(ifblk), mElseBlock(elseblk) { assert(mCondition); assert(mIfBlock); assert(mElseBlock); ++Count; ++Instances; };
                
            INLINE IfStatementParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &cond, std::shared_ptr< iParseTreeNode > &ifblk, std::shared_ptr< iParseTreeNode > &elseblk) : 
                ParseTreeNode(locstr), mCondition(cond), mIfBlock(ifblk), mElseBlock(elseblk) { assert(mCondition); assert(mIfBlock); assert(mElseBlock); ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const IfStatementParseTreeNode &ptn) const;
            
        public:
            virtual ~IfStatementParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< IfStatementParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &cond, std::shared_ptr< iParseTreeNode > &ifblk) { return std::shared_ptr< IfStatementParseTreeNode >(new IfStatementParseTreeNode(cond, ifblk)); };
            static INLINE std::shared_ptr< IfStatementParseTreeNode > MakeValue(const std::string &locstr, std::shared_ptr< iParseTreeNode > &cond, std::shared_ptr< iParseTreeNode > &ifblk) { return std::shared_ptr< IfStatementParseTreeNode >(new IfStatementParseTreeNode(locstr, cond, ifblk)); };
            
            static INLINE std::shared_ptr< IfStatementParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &cond, std::shared_ptr< iParseTreeNode > &ifblk, std::shared_ptr< iParseTreeNode > &elseblk) { return std::shared_ptr< IfStatementParseTreeNode >(new IfStatementParseTreeNode(cond, ifblk, elseblk)); };
            static INLINE std::shared_ptr< IfStatementParseTreeNode > MakeValue(const std::string &locstr, std::shared_ptr< iParseTreeNode > &cond, std::shared_ptr< iParseTreeNode > &ifblk, std::shared_ptr< iParseTreeNode > &elseblk) { return std::shared_ptr< IfStatementParseTreeNode >(new IfStatementParseTreeNode(locstr, cond, ifblk, elseblk)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual void Validate(LanguageSymbolTable &symtab) const;
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class SwitchStatementParseTreeNode : public ParseTreeNode
    {
        public:
        
            struct atomic_less
            {
            
                INLINE bool operator()(std::shared_ptr< iAtomic > &arg1, std::shared_ptr< iAtomic > &arg2) const
                {
                    return (arg1 < arg2)->AsBoolean();
	            }
                
            };
        
            using SwitchStatementT = std::vector< std::pair< std::shared_ptr< iParseTreeNode >, std::shared_ptr< iParseTreeNode > > >;
    
        private:
            std::shared_ptr< iParseTreeNode > mExpression;
        
            SwitchStatementT mSwitch;
            
            std::shared_ptr< iParseTreeNode > mOtherwise;
        
            static IntegerT Count;
            static IntegerT Instances;
        
        protected:
            INLINE SwitchStatementParseTreeNode(std::shared_ptr< iParseTreeNode > &expr) : ParseTreeNode(), mExpression(expr), mSwitch(), mOtherwise() { assert(mExpression); ++Count; ++Instances; };
            INLINE SwitchStatementParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &expr) : ParseTreeNode(locstr), mExpression(expr), mSwitch(), mOtherwise() { assert(mExpression); ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const SwitchStatementParseTreeNode &ptn) const;
        
        public:
            virtual ~SwitchStatementParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< SwitchStatementParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &expr) { return std::shared_ptr< SwitchStatementParseTreeNode >(new SwitchStatementParseTreeNode(expr)); };
            static INLINE std::shared_ptr< SwitchStatementParseTreeNode > MakeValue(const std::string &locstr, std::shared_ptr< iParseTreeNode > &expr) { return std::shared_ptr< SwitchStatementParseTreeNode >(new SwitchStatementParseTreeNode(locstr, expr)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
        
            INLINE void AddCase(std::shared_ptr< iParseTreeNode > &key, std::shared_ptr< iParseTreeNode > &value) { assert(key); assert(value); mSwitch.push_back(std::make_pair(key, value)); };
            INLINE void AddOtherwise(std::shared_ptr< iParseTreeNode > &otherwise) { assert(otherwise); mOtherwise = otherwise; };
        
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual void Validate(LanguageSymbolTable &symtab) const;
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
            
    };
    
    class ForLoopParseTreeNode : public ParseTreeNode
    {
        public:
            
            static std::shared_ptr< iParseTreeNode > OneLit;
        
            class StepF : public ParseTreeNode
            {
                friend ForLoopParseTreeNode;
            
                private:
                    std::shared_ptr< iParseTreeNode > mLeftHandSide;
                    std::shared_ptr< iParseTreeNode > mStep;
                
                protected:
                    INLINE StepF(std::shared_ptr< iParseTreeNode > &lhs) : ParseTreeNode(), mLeftHandSide(lhs), mStep(OneLit) { assert(0 != mLeftHandSide.get()); assert(0 != mStep.get()); };
                    INLINE StepF(std::shared_ptr< iParseTreeNode > &lhs, const std::string &locstr) : ParseTreeNode(locstr), mLeftHandSide(lhs), mStep(OneLit) { assert(0 != mLeftHandSide.get()); assert(0 != mStep.get()); };
                    INLINE StepF(std::shared_ptr< iParseTreeNode > &lhs, std::shared_ptr< iParseTreeNode > &step) : ParseTreeNode(), mLeftHandSide(lhs), mStep(step) { assert(0 != mLeftHandSide.get()); assert(0 != mStep.get()); };
                    INLINE StepF(std::shared_ptr< iParseTreeNode > &lhs, std::shared_ptr< iParseTreeNode > &step, const std::string &locstr) : ParseTreeNode(locstr), mLeftHandSide(lhs), mStep(step) { assert(0 != mLeftHandSide.get()); assert(0 != mStep.get()); };
                
                public:
                
                    static std::shared_ptr< StepF > MakeValue(std::shared_ptr< iParseTreeNode > &lhs) { return std::shared_ptr< StepF >(new StepF(lhs)); };
                    static std::shared_ptr< StepF > MakeValue(std::shared_ptr< iParseTreeNode > &lhs, const std::string &locstr) { return std::shared_ptr< StepF >(new StepF(lhs, locstr)); };
                    static std::shared_ptr< StepF > MakeValue(std::shared_ptr< iParseTreeNode > &lhs, std::shared_ptr< iParseTreeNode > &step) { return std::shared_ptr< StepF >(new StepF(lhs, step)); };
                    static std::shared_ptr< StepF > MakeValue(std::shared_ptr< iParseTreeNode > &lhs, std::shared_ptr< iParseTreeNode > &step, const std::string &locstr) { return std::shared_ptr< StepF >(new StepF(lhs, step, locstr)); };
            
                    //  From iParseTreeNode
                    
                    virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
                    
                    //  From iPrintable
                    
                    virtual void Print(std::ostream &out, const int &indent = 0) const;
                    
            };
    
        private:
            std::shared_ptr< iParseTreeNode > mBody;
            
            std::shared_ptr< iParseTreeNode > mAssign;
            std::shared_ptr< iParseTreeNode > mCondition;
            std::shared_ptr< StepF > mIncrement;
        
            static IntegerT Count;
            static IntegerT Instances;
        
        protected:
            INLINE ForLoopParseTreeNode(std::shared_ptr< iParseTreeNode > &id, std::shared_ptr< iParseTreeNode > &from, std::shared_ptr< iParseTreeNode > &to, std::shared_ptr< iParseTreeNode > &body) : ParseTreeNode(),
                mBody(body),
                
                mAssign(AssignmentParseTreeNode::MakeValue(id, from)),
                mCondition(NotEqualOpParseTreeNode::MakeValue(id, to)),
                mIncrement(StepF::MakeValue(id, OneLit))
            {
                assert(mAssign);
                assert(mCondition);
                assert(mIncrement);
                assert(mBody);
                
                ++Count;
                ++Instances;
            }
            
            INLINE ForLoopParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &id, std::shared_ptr< iParseTreeNode > &from, std::shared_ptr< iParseTreeNode > &to, std::shared_ptr< iParseTreeNode > &body) : ParseTreeNode(locstr),
                mBody(body),
                
                mAssign(AssignmentParseTreeNode::MakeValue(locstr, id, from)),
                mCondition(NotEqualOpParseTreeNode::MakeValue(locstr, id, to)),
                mIncrement(StepF::MakeValue(id, OneLit, locstr))
            {
                assert(mAssign);
                assert(mCondition);
                assert(mIncrement);
                assert(mBody);
                
                ++Count;
                ++Instances;
            }
            
            INLINE ForLoopParseTreeNode(std::shared_ptr< iParseTreeNode > &id, std::shared_ptr< iParseTreeNode > &from, std::shared_ptr< iParseTreeNode > &to, std::shared_ptr< iParseTreeNode > &step, std::shared_ptr< iParseTreeNode > &body) : ParseTreeNode(),
                mBody(body),
                
                mAssign(AssignmentParseTreeNode::MakeValue(id, from)),
                mCondition(NotEqualOpParseTreeNode::MakeValue(id, to)),
                mIncrement(StepF::MakeValue(id, step))
            {
                assert(mAssign);
                assert(mCondition);
                assert(mIncrement);
                assert(mBody);
                
                ++Count;
                ++Instances;
            }
            
            INLINE ForLoopParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &id, std::shared_ptr< iParseTreeNode > &from, std::shared_ptr< iParseTreeNode > &to, std::shared_ptr< iParseTreeNode > &step, std::shared_ptr< iParseTreeNode > &body) : ParseTreeNode(locstr),
                mBody(body),
                
                mAssign(AssignmentParseTreeNode::MakeValue(locstr, id, from)),
                mCondition(NotEqualOpParseTreeNode::MakeValue(locstr, id, to)),
                mIncrement(StepF::MakeValue(id, step, locstr))
            {
                assert(mAssign);
                assert(mCondition);
                assert(mIncrement);
                assert(mBody);
                
                ++Count;
                ++Instances;
            }
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const ForLoopParseTreeNode &ptn) const;
        
        public:
            virtual ~ForLoopParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< ForLoopParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &id, std::shared_ptr< iParseTreeNode > &from, std::shared_ptr< iParseTreeNode > &to, std::shared_ptr< iParseTreeNode > &body) { return std::shared_ptr< ForLoopParseTreeNode >(new ForLoopParseTreeNode(id, from, to, body)); };
            static INLINE std::shared_ptr< ForLoopParseTreeNode > MakeValue(const std::string &locstr, std::shared_ptr< iParseTreeNode > &id, std::shared_ptr< iParseTreeNode > &from, std::shared_ptr< iParseTreeNode > &to, std::shared_ptr< iParseTreeNode > &body) { return std::shared_ptr< ForLoopParseTreeNode >(new ForLoopParseTreeNode(locstr, id, from, to, body)); };
            
            static INLINE std::shared_ptr< ForLoopParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > id, std::shared_ptr< iParseTreeNode > &from, std::shared_ptr< iParseTreeNode > &to, std::shared_ptr< iParseTreeNode > &step, std::shared_ptr< iParseTreeNode > &body) { return std::shared_ptr< ForLoopParseTreeNode >(new ForLoopParseTreeNode(id, from, to, step, body)); };
            static INLINE std::shared_ptr< ForLoopParseTreeNode > MakeValue(const std::string &locstr, std::shared_ptr< iParseTreeNode > &id, std::shared_ptr< iParseTreeNode > &from, std::shared_ptr< iParseTreeNode > &to, std::shared_ptr< iParseTreeNode > &step, std::shared_ptr< iParseTreeNode > &body) { return std::shared_ptr< ForLoopParseTreeNode >(new ForLoopParseTreeNode(locstr, id, from, to, step, body)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual void Validate(LanguageSymbolTable &symtab) const;
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class ForEachLoopParseTreeNode : public ParseTreeNode
    {
        private:
            const bool mReference;
            const std::string mId;
            
            std::shared_ptr< iParseTreeNode > mCollection;
            std::shared_ptr< iParseTreeNode > mBody;
        
            static IntegerT Count;
            static IntegerT Instances;
        
        protected:
            INLINE ForEachLoopParseTreeNode(const bool &ref, const std::string &id, std::shared_ptr< iParseTreeNode > &collection, std::shared_ptr< iParseTreeNode > &body) : 
                ParseTreeNode(), mReference(ref), mId(id), mCollection(collection), mBody(body) { assert(mCollection); assert(mBody); ++Count; ++Instances; };
                
            INLINE ForEachLoopParseTreeNode(const std::string &locstr, const bool &ref, const std::string &id, std::shared_ptr< iParseTreeNode > &collection, std::shared_ptr< iParseTreeNode > &body) : 
                ParseTreeNode(locstr), mReference(ref), mId(id), mCollection(collection), mBody(body) { assert(mCollection); assert(mBody); ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const ForEachLoopParseTreeNode &ptn) const;
        
        public:
            virtual ~ForEachLoopParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< ForEachLoopParseTreeNode > MakeValue(const bool &ref, const std::string &id, std::shared_ptr< iParseTreeNode > &collection, std::shared_ptr< iParseTreeNode > &body) { return std::shared_ptr< ForEachLoopParseTreeNode >(new ForEachLoopParseTreeNode(ref, id, collection, body)); };
            static INLINE std::shared_ptr< ForEachLoopParseTreeNode > MakeValue(const std::string &locstr, const bool &ref, const std::string &id, std::shared_ptr< iParseTreeNode > &collection, std::shared_ptr< iParseTreeNode > &body) { return std::shared_ptr< ForEachLoopParseTreeNode >(new ForEachLoopParseTreeNode(locstr, ref, id, collection, body)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual void Validate(LanguageSymbolTable &symtab) const;
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class WhileLoopParseTreeNode : public ParseTreeNode
    {
        private:
            std::shared_ptr< iParseTreeNode > mCondition;
            std::shared_ptr< iParseTreeNode > mBody;
        
            static IntegerT Count;
            static IntegerT Instances;
        
        protected:
            INLINE WhileLoopParseTreeNode(std::shared_ptr< iParseTreeNode > &condition, std::shared_ptr< iParseTreeNode > &body) : 
                ParseTreeNode(), mCondition(condition), mBody(body) { assert(mCondition); assert(mBody); ++Count; ++Instances; };
                
            INLINE WhileLoopParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &condition, std::shared_ptr< iParseTreeNode > &body) : 
                ParseTreeNode(locstr), mCondition(condition), mBody(body) { assert(mCondition); assert(mBody); ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const WhileLoopParseTreeNode &ptn) const;
        
        public:
            virtual ~WhileLoopParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< WhileLoopParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &condition, std::shared_ptr< iParseTreeNode > &body) { return std::shared_ptr< WhileLoopParseTreeNode >(new WhileLoopParseTreeNode(condition, body)); };
            static INLINE std::shared_ptr< WhileLoopParseTreeNode > MakeValue(const std::string &locstr, std::shared_ptr< iParseTreeNode > &condition, std::shared_ptr< iParseTreeNode > &body) { return std::shared_ptr< WhileLoopParseTreeNode >(new WhileLoopParseTreeNode(locstr, condition, body)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual void Validate(LanguageSymbolTable &symtab) const;
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };
    
    class RepeatUntilLoopParseTreeNode : public ParseTreeNode
    {
        public:
        
#ifdef LIST_TYPE_PREFER_VECTOR
            using BodyT = std::vector< std::shared_ptr< iParseTreeNode > >;
#else
            using BodyT = std::list< std::shared_ptr< iParseTreeNode > >;
#endif
    
        private:
            BodyT mBody;
            std::shared_ptr< iParseTreeNode > mCondition;
        
            static IntegerT Count;
            static IntegerT Instances;
        
        protected:
            INLINE RepeatUntilLoopParseTreeNode(const BodyT &body, std::shared_ptr< iParseTreeNode > &condition) : ParseTreeNode(), mBody(body.begin(), body.end()), mCondition(condition)
            {
                assert(mCondition);
                
#ifdef LIST_TYPE_PREFER_VECTOR
                mBody.reserve(LIST_TYPE_PREFER_VECTOR);
#endif

                ++Count;
                ++Instances;
            };
                
            INLINE RepeatUntilLoopParseTreeNode(const std::string &locstr, const BodyT &body, std::shared_ptr< iParseTreeNode > &condition) : ParseTreeNode(locstr), mBody(body.begin(), body.end()), mCondition(condition)
            {
                assert(mCondition);
                
#ifdef LIST_TYPE_PREFER_VECTOR
                mBody.reserve(LIST_TYPE_PREFER_VECTOR);
#endif

                ++Count;
                ++Instances;
            };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const RepeatUntilLoopParseTreeNode &ptn) const;
        
        public:
            virtual ~RepeatUntilLoopParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< RepeatUntilLoopParseTreeNode > MakeValue(const BodyT &body, std::shared_ptr< iParseTreeNode > &condition) { return std::shared_ptr< RepeatUntilLoopParseTreeNode >(new RepeatUntilLoopParseTreeNode(body, condition)); };
            static INLINE std::shared_ptr< RepeatUntilLoopParseTreeNode > MakeValue(const std::string &locstr, const BodyT &body, std::shared_ptr< iParseTreeNode > &condition) { return std::shared_ptr< RepeatUntilLoopParseTreeNode >(new RepeatUntilLoopParseTreeNode(locstr, body, condition)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual void Validate(LanguageSymbolTable &symtab) const;
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class AssertParseTreeNode : public ParseTreeNode
    {
        private:
            std::shared_ptr< iParseTreeNode > mCondition;
        
            static IntegerT Count;
            static IntegerT Instances;
        
        protected:
            INLINE AssertParseTreeNode(std::shared_ptr< iParseTreeNode > &condition) : ParseTreeNode(), mCondition(condition) { assert(mCondition); ++Count; ++Instances; };
            INLINE AssertParseTreeNode(const std::string &locstr, std::shared_ptr< iParseTreeNode > &condition) : ParseTreeNode(locstr), mCondition(condition) { assert(mCondition); ++Count; ++Instances; };
            
            //  From iParseTreeNode
    
            virtual bool isEqual(const AssertParseTreeNode &ptn) const;
        
        public:
            virtual ~AssertParseTreeNode() { --Instances; };
            
            static INLINE std::shared_ptr< AssertParseTreeNode > MakeValue(std::shared_ptr< iParseTreeNode > &condition) { return std::shared_ptr< AssertParseTreeNode >(new AssertParseTreeNode(condition)); };
            static INLINE std::shared_ptr< AssertParseTreeNode > MakeValue(const std::string &locstr, std::shared_ptr< iParseTreeNode > &condition) { return std::shared_ptr< AssertParseTreeNode >(new AssertParseTreeNode(locstr, condition)); };
            
            static INLINE const IntegerT &NumInstances() throw() { return Count; };
            static INLINE const IntegerT &NumLiveInstances() throw() { return Instances; };
            
            //  From iParseTreeNode
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab);
            
            virtual void Validate(LanguageSymbolTable &symtab) const;
            
            virtual bool IsEqual(const iParseTreeNode &ptn) const;
            
            //  From iPrintable
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    extern void PrintParseTreeStatistics(std::ostream &out);

    ////////////////////////////////////////////////////////////////////////////

}

#endif

