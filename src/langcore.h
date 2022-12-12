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

#ifndef DISH_LANGCORE_H
#define DISH_LANGCORE_H

#include "dishconfig.h"

#include <unistd.h>

#include <memory>

#include "atomics.h"
#include "inline.h"
#include "language.h"
#include "version.h"

namespace dish
{

    ////////////////////////////////////////////////////////////////////////////

    class IsEntryPointFunction : public ExecutableAtomic
    {
        public:
            INLINE IsEntryPointFunction() : ExecutableAtomic() {};
            
            static INLINE std::shared_ptr< IsEntryPointFunction > MakeValue() { return std::shared_ptr< IsEntryPointFunction >(new IsEntryPointFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    class ReleaseCachedParseTreeNodesFunction : public ExecutableAtomic
    {
        public:
            INLINE ReleaseCachedParseTreeNodesFunction() : ExecutableAtomic() {};
            
            static INLINE std::shared_ptr< ReleaseCachedParseTreeNodesFunction > MakeValue() { return std::shared_ptr< ReleaseCachedParseTreeNodesFunction >(new ReleaseCachedParseTreeNodesFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////
    
    extern std::shared_ptr< iAtomic > CreateVersionStructureType();
    extern std::shared_ptr< iAtomic > CreateVersionStructure(const IntegerT &major, const IntegerT &minor, const IntegerT &revision, const bool locked);
    
    INLINEC std::shared_ptr< iAtomic > CreateVersionStructure(const Version &version, const bool locked)
    {
        return CreateVersionStructure(version.Major(), version.Minor(), version.Revision(), locked);
    }

    ////////////////////////////////////////////////////////////////////////////
    
    class MakeVersionFunction : public ExecutableAtomic
    {
        protected:
            INLINE MakeVersionFunction() : ExecutableAtomic() { addParam("major", REFERENCE_PARAMETER); addParam("minor", REFERENCE_PARAMETER); addParam("revision", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< MakeVersionFunction > MakeValue() { return std::shared_ptr< MakeVersionFunction >(new MakeVersionFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    class VersionLessThanFunction : public ExecutableAtomic
    {
        protected:
            INLINE VersionLessThanFunction() : ExecutableAtomic() { addParam("lhs", REFERENCE_PARAMETER); addParam("rhs", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< VersionLessThanFunction > MakeValue() { return std::shared_ptr< VersionLessThanFunction >(new VersionLessThanFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    class VersionEqualFunction : public ExecutableAtomic
    {
        protected:
            INLINE VersionEqualFunction() : ExecutableAtomic() { addParam("lhs", REFERENCE_PARAMETER); addParam("rhs", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< VersionEqualFunction > MakeValue() { return std::shared_ptr< VersionEqualFunction >(new VersionEqualFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    class VersionAsStringFunction : public ExecutableAtomic
    {
        protected:
            INLINE VersionAsStringFunction() : ExecutableAtomic() { addParam("version", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< VersionAsStringFunction > MakeValue() { return std::shared_ptr< VersionAsStringFunction >(new VersionAsStringFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class GetEnvironmentVariableFunction : public ExecutableAtomic
    {
        protected:
            INLINE GetEnvironmentVariableFunction() : ExecutableAtomic() { addParam("env", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< GetEnvironmentVariableFunction > MakeValue() { return std::shared_ptr< GetEnvironmentVariableFunction >(new GetEnvironmentVariableFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    class TerminateFunction : public ExecutableAtomic
    {
        protected:
            INLINE TerminateFunction() : ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< TerminateFunction > MakeValue() { return std::shared_ptr< TerminateFunction >(new TerminateFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;

    };

    class SleepFunction : public ExecutableAtomic
    {
        protected:
            INLINE SleepFunction() : ExecutableAtomic() { addParam("amt", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< SleepFunction > MakeValue() { return std::shared_ptr< SleepFunction >(new SleepFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    class SystemFunction : public ExecutableAtomic
    {
        protected:
            INLINE SystemFunction() : ExecutableAtomic() { addParam("cmdln", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< SystemFunction > MakeValue() { return std::shared_ptr< SystemFunction >(new SystemFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
        
    };
    
    class ExecuteFunction : public ExecutableAtomic
    {
        protected:
            INLINE ExecuteFunction() : ExecutableAtomic() { addParam("cmdln", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< ExecuteFunction > MakeValue() { return std::shared_ptr< ExecuteFunction >(new ExecuteFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
        
    };

    class CopyFunction : public ExecutableAtomic
    {
        protected:
            INLINE CopyFunction() : ExecutableAtomic() { addParam("value", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< CopyFunction > MakeValue() { return std::shared_ptr< CopyFunction >(new CopyFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class CloneFunction : public ExecutableAtomic
    {
        protected:
            INLINE CloneFunction() : ExecutableAtomic() { addParam("value", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< CloneFunction > MakeValue() { return std::shared_ptr< CloneFunction >(new CloneFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class AsBooleanFunction : public ExecutableAtomic
    {
        protected:
            INLINE AsBooleanFunction() : ExecutableAtomic() { addParam("value", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< AsBooleanFunction > MakeValue() { return std::shared_ptr< AsBooleanFunction >(new AsBooleanFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class AsIntegerFunction : public ExecutableAtomic
    {
        protected:
            INLINE AsIntegerFunction() : ExecutableAtomic() { addParam("value", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< AsIntegerFunction > MakeValue() { return std::shared_ptr< AsIntegerFunction >(new AsIntegerFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class AsRealFunction : public ExecutableAtomic
    {
        protected:
            INLINE AsRealFunction() : ExecutableAtomic() { addParam("value", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< AsRealFunction > MakeValue() { return std::shared_ptr< AsRealFunction >(new AsRealFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class AsStringFunction : public ExecutableAtomic
    {
        protected:
            INLINE AsStringFunction() : ExecutableAtomic() { addParam("value", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< AsStringFunction > MakeValue() { return std::shared_ptr< AsStringFunction >(new AsStringFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    class AppendFunction : public ExecutableAtomic
    {
        protected:
            INLINE AppendFunction() : ExecutableAtomic() { addParam("A", REFERENCE_PARAMETER); addParam("elem", VALUE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< AppendFunction > MakeValue() { return std::shared_ptr< AppendFunction >(new AppendFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    class InsertFunction : public ExecutableAtomic
    {
        protected:
            INLINE InsertFunction() : ExecutableAtomic() { addParam("A", REFERENCE_PARAMETER); addParam("pos", REFERENCE_PARAMETER); addParam("elem", VALUE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< InsertFunction > MakeValue() { return std::shared_ptr< InsertFunction >(new InsertFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    ////////////////////////////////////////////////////////////////////////////
    
    class CompareLessThanFunction : public ExecutableAtomic
    {
        protected:
            INLINE CompareLessThanFunction() : ExecutableAtomic() { addParam("arg1", REFERENCE_PARAMETER); addParam("arg2", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< CompareLessThanFunction > MakeValue() { return std::shared_ptr< CompareLessThanFunction >(new CompareLessThanFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };
    
    class CompareGreaterThanFunction : public ExecutableAtomic
    {
        protected:
            INLINE CompareGreaterThanFunction() : ExecutableAtomic() { addParam("arg1", REFERENCE_PARAMETER); addParam("arg2", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< CompareGreaterThanFunction > MakeValue() { return std::shared_ptr< CompareGreaterThanFunction >(new CompareGreaterThanFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };
    
    class CompareEqualFunction : public ExecutableAtomic
    {
        protected:
            INLINE CompareEqualFunction() : ExecutableAtomic() { addParam("arg1", REFERENCE_PARAMETER); addParam("arg2", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< CompareEqualFunction > MakeValue() { return std::shared_ptr< CompareEqualFunction >(new CompareEqualFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };
    
    class SortFunction : public ExecutableAtomic
    {
        protected:
            INLINE SortFunction() : ExecutableAtomic() { addParam("A", REFERENCE_PARAMETER); addParam("compareF", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< SortFunction > MakeValue() { return std::shared_ptr< SortFunction >(new SortFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    class SwapFunction : public ExecutableAtomic
    {
        protected:
            INLINE SwapFunction() : ExecutableAtomic() { addParam("A", REFERENCE_PARAMETER); addParam("index1", REFERENCE_PARAMETER); addParam("index2", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< SwapFunction > MakeValue() { return std::shared_ptr< SwapFunction >(new SwapFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    ////////////////////////////////////////////////////////////////////////////
    
    class FindFunction : public ExecutableAtomic
    {
        protected:
            INLINE FindFunction() : ExecutableAtomic() { addParam("A", REFERENCE_PARAMETER); addParam("elem", REFERENCE_PARAMETER); addParam("compareF", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< FindFunction > MakeValue() { return std::shared_ptr< FindFunction >(new FindFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    class FindSortedFunction : public ExecutableAtomic
    {
        protected:
            INLINE FindSortedFunction() : ExecutableAtomic() { addParam("A", REFERENCE_PARAMETER); addParam("elem", REFERENCE_PARAMETER); addParam("compareF", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< FindSortedFunction > MakeValue() { return std::shared_ptr< FindSortedFunction >(new FindSortedFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    class IsLockedFunction : public ExecutableAtomic
    {
        protected:
            INLINE IsLockedFunction() : ExecutableAtomic() { addParam("arg", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< IsLockedFunction > MakeValue() { return std::shared_ptr< IsLockedFunction >(new IsLockedFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class IsNullFunction : public ExecutableAtomic
    {
        protected:
            INLINE IsNullFunction() : ExecutableAtomic() { addParam("value", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< IsNullFunction > MakeValue() { return std::shared_ptr< IsNullFunction >(new IsNullFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class IsTypeFunction : public ExecutableAtomic
    {
        protected:
            INLINE IsTypeFunction() : ExecutableAtomic() { addParam("value", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< IsTypeFunction > MakeValue() { return std::shared_ptr< IsTypeFunction >(new IsTypeFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class IsBooleanFunction : public ExecutableAtomic
    {
        protected:
            INLINE IsBooleanFunction() : ExecutableAtomic() { addParam("value", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< IsBooleanFunction > MakeValue() { return std::shared_ptr< IsBooleanFunction >(new IsBooleanFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class IsIntegerFunction : public ExecutableAtomic
    {
        protected:
            INLINE IsIntegerFunction() : ExecutableAtomic() { addParam("value", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< IsIntegerFunction > MakeValue() { return std::shared_ptr< IsIntegerFunction >(new IsIntegerFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class IsRealFunction : public ExecutableAtomic
    {
        protected:
            INLINE IsRealFunction() : ExecutableAtomic() { addParam("value", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< IsRealFunction > MakeValue() { return std::shared_ptr< IsRealFunction >(new IsRealFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class IsStringFunction : public ExecutableAtomic
    {
        protected:
            INLINE IsStringFunction() : ExecutableAtomic() { addParam("value", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< IsStringFunction > MakeValue() { return std::shared_ptr< IsStringFunction >(new IsStringFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class IsArrayFunction : public ExecutableAtomic
    {
        protected:
            INLINE IsArrayFunction() : ExecutableAtomic() { addParam("value", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< IsArrayFunction > MakeValue() { return std::shared_ptr< IsArrayFunction >(new IsArrayFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class IsDictionaryFunction : public ExecutableAtomic
    {
        protected:
            INLINE IsDictionaryFunction() : ExecutableAtomic() { addParam("value", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< IsDictionaryFunction > MakeValue() { return std::shared_ptr< IsDictionaryFunction >(new IsDictionaryFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class IsStructureFunction : public ExecutableAtomic
    {
        protected:
            INLINE IsStructureFunction() : ExecutableAtomic() { addParam("value", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< IsStructureFunction > MakeValue() { return std::shared_ptr< IsStructureFunction >(new IsStructureFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class IsFunctionFunction : public ExecutableAtomic
    {
        protected:
            INLINE IsFunctionFunction() : ExecutableAtomic() { addParam("value", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< IsFunctionFunction > MakeValue() { return std::shared_ptr< IsFunctionFunction >(new IsFunctionFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class StringAsNumericFunction : public ExecutableAtomic
    {
        protected:
            INLINE StringAsNumericFunction() : ExecutableAtomic() { addParam("str", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< StringAsNumericFunction > MakeValue() { return std::shared_ptr< StringAsNumericFunction >(new StringAsNumericFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class TypeOfFunction : public ExecutableAtomic
    {
        protected:
            INLINE TypeOfFunction() : ExecutableAtomic() { addParam("expr", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< TypeOfFunction > MakeValue() { return std::shared_ptr< TypeOfFunction >(new TypeOfFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class TypeIdFunction : public ExecutableAtomic
    {
        protected:
            INLINE TypeIdFunction() : ExecutableAtomic() { addParam("arg", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< TypeIdFunction > MakeValue() { return std::shared_ptr< TypeIdFunction >(new TypeIdFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    ////////////////////////////////////////////////////////////////////////////

    class OnErrorPushFunction : public ExecutableAtomic
    {
        protected:
            INLINE OnErrorPushFunction() : ExecutableAtomic() { addParam("index", REFERENCE_PARAMETER); addParam("call", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< OnErrorPushFunction > MakeValue() { return std::shared_ptr< OnErrorPushFunction >(new OnErrorPushFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class OnErrorInvokeFunction : public ExecutableAtomic
    {
        protected:
            INLINE OnErrorInvokeFunction() : ExecutableAtomic() { addParam("index", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< OnErrorInvokeFunction > MakeValue() { return std::shared_ptr< OnErrorInvokeFunction >(new OnErrorInvokeFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    class OnErrorPopFunction : public ExecutableAtomic
    {
        protected:
            INLINE OnErrorPopFunction() : ExecutableAtomic() { addParam("index", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< OnErrorPopFunction > MakeValue() { return std::shared_ptr< OnErrorPopFunction >(new OnErrorPopFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
            
    };

    ////////////////////////////////////////////////////////////////////////////

    class MinimumFunction : public ExecutableAtomic
    {
        protected:
            INLINE MinimumFunction() : ExecutableAtomic() { addParam("A", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< MinimumFunction > MakeValue() { return std::shared_ptr< MinimumFunction >(new MinimumFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    class Minimum2Function : public ExecutableAtomic
    {
        protected:
            INLINE Minimum2Function() : ExecutableAtomic() { addParam("x", REFERENCE_PARAMETER); addParam("y", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< Minimum2Function > MakeValue() { return std::shared_ptr< Minimum2Function >(new Minimum2Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    class Minimum3Function : public ExecutableAtomic
    {
        protected:
            INLINE Minimum3Function() : ExecutableAtomic() { addParam("x", REFERENCE_PARAMETER); addParam("y", REFERENCE_PARAMETER); addParam("z", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< Minimum3Function > MakeValue() { return std::shared_ptr< Minimum3Function >(new Minimum3Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    class MaximumFunction : public ExecutableAtomic
    {
        protected:
            INLINE MaximumFunction() : ExecutableAtomic() { addParam("A", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< MaximumFunction > MakeValue() { return std::shared_ptr< MaximumFunction >(new MaximumFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    class Maximum2Function : public ExecutableAtomic
    {
        protected:
            INLINE Maximum2Function() : ExecutableAtomic() { addParam("x", REFERENCE_PARAMETER); addParam("y", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< Maximum2Function > MakeValue() { return std::shared_ptr< Maximum2Function >(new Maximum2Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    class Maximum3Function : public ExecutableAtomic
    {
        protected:
            INLINE Maximum3Function() : ExecutableAtomic() { addParam("x", REFERENCE_PARAMETER); addParam("y", REFERENCE_PARAMETER); addParam("z", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< Maximum3Function > MakeValue() { return std::shared_ptr< Maximum3Function >(new Maximum3Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    ////////////////////////////////////////////////////////////////////////////

    class IncFunction : public ExecutableAtomic
    {
        protected:
            INLINE IncFunction() : ExecutableAtomic() { addParam("x", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< IncFunction > MakeValue() { return std::shared_ptr< IncFunction >(new IncFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class Inc2Function : public ExecutableAtomic
    {
        protected:
            INLINE Inc2Function() : ExecutableAtomic() { addParam("x", REFERENCE_PARAMETER); addParam("amt", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< Inc2Function > MakeValue() { return std::shared_ptr< Inc2Function >(new Inc2Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class DecFunction : public ExecutableAtomic
    {
        protected:
            INLINE DecFunction() : ExecutableAtomic() { addParam("x", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< DecFunction > MakeValue() { return std::shared_ptr< DecFunction >(new DecFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class Dec2Function : public ExecutableAtomic
    {
        protected:
            INLINE Dec2Function() : ExecutableAtomic() { addParam("x", REFERENCE_PARAMETER); addParam("amt", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< Dec2Function > MakeValue() { return std::shared_ptr< Dec2Function >(new Dec2Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////

    class SymbolOfFunctionFunction : public ExecutableAtomic
    {
        protected:
            INLINE SymbolOfFunctionFunction() : ExecutableAtomic() { addParam("funcname", REFERENCE_PARAMETER); addParam("nparams", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< SymbolOfFunctionFunction > MakeValue() { return std::shared_ptr< SymbolOfFunctionFunction >(new SymbolOfFunctionFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class SymbolExistsFunction : public ExecutableAtomic
    {
        protected:
            INLINE SymbolExistsFunction() : ExecutableAtomic() { addParam("id", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< SymbolExistsFunction > MakeValue() { return std::shared_ptr< SymbolExistsFunction >(new SymbolExistsFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////

    class IsExactlyEqualFunction : public ExecutableAtomic
    {
        protected:
            INLINE IsExactlyEqualFunction() : ExecutableAtomic() { addParam("lhs", REFERENCE_PARAMETER); addParam("rhs", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< IsExactlyEqualFunction > MakeValue() { return std::shared_ptr< IsExactlyEqualFunction >(new IsExactlyEqualFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////
    
}

#endif

