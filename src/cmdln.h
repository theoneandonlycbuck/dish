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

#ifndef DISH_CMDLN_H
#define DISH_CMDLN_H

#include "dishconfig.h"

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "inline.h"
#include "profile.h"

namespace dish
{

    ////////////////////////////////////////////////////////////////////////////

    class CommandLine
    {
        public:
        
            ////////////////////////////////////////////////////////////////////
        
            class InvalidTypeConversion {};
            class IndexOutOfBounds {};
            class NoSuchSymbol {};
        
            ////////////////////////////////////////////////////////////////////
        
            class iValue
            {
                public:
                    virtual ~iValue() {};
                    
                    virtual bool AsBoolean() const;
                    virtual int AsInteger() const;
                    virtual double AsReal() const;
                    virtual std::string AsString() const;
                    
                    virtual int NumElements() const;
                    virtual void AddElement(std::shared_ptr< iValue > element);
                    virtual std::shared_ptr< iValue > Element(const int index) const;
                    
                    virtual void Print(std::ostream &out) const = 0;
                    
            };
            
            class BooleanValue : public iValue
            {
                private:
                    const bool mValue;
                
                public:
                    INLINE BooleanValue(const bool &value) : iValue(), mValue(value) {};
                    
                    //  From iValue
                    
                    virtual bool AsBoolean() const;
                    
                    virtual void Print(std::ostream &out) const;
                
            };
            
            class IntegerValue : public iValue
            {
                private:
                    const int mValue;
                
                public:
                    INLINE IntegerValue(const int &value) : iValue(), mValue(value) {};
                    
                    //  From iValue
                    
                    virtual int AsInteger() const;
                    
                    virtual void Print(std::ostream &out) const;
                
            };
            
            class RealValue : public iValue
            {
                private:
                    const double mValue;
                
                public:
                    INLINE RealValue(const double &value) : iValue(), mValue(value) {};
                    
                    //  From iValue
                    
                    virtual double AsReal() const;
                    
                    virtual void Print(std::ostream &out) const;
                
            };
            
            class StringValue : public iValue
            {
                private:
                    const std::string mValue;
                
                public:
                    INLINE StringValue(const std::string &value) : iValue(), mValue(value) {};
                    
                    //  From iValue
                    
                    virtual std::string AsString() const;
                    
                    virtual void Print(std::ostream &out) const;
                
            };
            
            class ArrayValue : public iValue
            {
                public:
                
                    typedef std::vector< std::shared_ptr< iValue > > ArrayT;
            
                private:
                    ArrayT mValue;
                
                public:
                    INLINE ArrayValue() : iValue(), mValue() {};
                    
                    //  From iValue
                    
                    virtual int NumElements() const;
                    virtual void AddElement(std::shared_ptr< iValue > element);
                    virtual std::shared_ptr< iValue > Element(const int index) const;
                    
                    virtual void Print(std::ostream &out) const;
                
            };
        
            ////////////////////////////////////////////////////////////////////
            
            typedef std::map< std::string, std::shared_ptr< iValue > > DictionaryT;
        
            ////////////////////////////////////////////////////////////////////

        private:
            DictionaryT mDictionary;
            
        protected:
            INLINE void add(const std::string &key, std::shared_ptr< iValue > value) { mDictionary[key] = value; };
            
            INLINE void add(const std::string &key, const bool value) { add(key, std::shared_ptr< iValue >(new BooleanValue(value))); };
            INLINE void add(const std::string &key, const int value) { add(key, std::shared_ptr< iValue >(new IntegerValue(value))); };
            INLINE void add(const std::string &key, const double value) { add(key, std::shared_ptr< iValue >(new RealValue(value))); };
            INLINE void add(const std::string &key, const std::string value) { add(key, std::shared_ptr< iValue >(new StringValue(value))); };

        public:

            static const std::string EXE;
            
            static const std::string ARGC;
            static const std::string ARGV;
            
            static const std::string RETURN_VALUE;
            
            INLINE CommandLine() : mDictionary() {};
            virtual ~CommandLine() {};
            
            void Print(std::ostream &out) const;
            
            INLINE bool Exists(const std::string &key) const { return (mDictionary.end() != mDictionary.find(key)); };
            std::shared_ptr< iValue > operator[](const std::string &key) const;
            
            /////
            
            INLINE int ReturnValue() const { return (*this)[RETURN_VALUE]->AsInteger(); };
            INLINE void SetReturnValue(const int value) { (*this)[RETURN_VALUE].reset(new IntegerValue(value)); };
            
            /////
            
            virtual void Process(const int argc, const char * const * const argv);
            
            virtual void PrintUsage(std::ostream &out) const = 0;
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class DishCommandLine : public CommandLine
    {
        public:
        
            static const std::string EXECUTE;
        
            static const std::string QUIET_MODE;

            static const std::string INCLUDE_PATHS;
            static const std::string INPUT;
            static const std::string PROGRAM_ARGS;
            
            static const std::string SYMTAB_STAT_MODE;
            static const std::string PRINT_SYMTAB_MODE;
            static const std::string SHUFFLE_SYMTAB;
            
            static const std::string PRINT_RNG_STATS;
            static const std::string PRINT_ATOMIC_STATS;
            static const std::string PRINT_CONST_STATS;
            static const std::string PRINT_PROGRAM_STATS;
            
            static const std::string PRINT_EXECUTION_PROFILE;
            static const std::string SORTBY_EXECUTION_PROFILE;
            static const std::string UNITS_EXECUTION_PROFILE;
            
            static const std::string PRINT_USAGE_INFO;
            
            static const std::string EXECUTE_FROM_CMDLN;
            
            static const std::string VALIDATE_INPUT;
            
            static const std::string DISPLAY_VERSION;
            
            static const std::string STACK_DEPTH;
            
            static const std::string PRINT_PARSE_TREE;
            
            static const std::string RNG_SEED;
            
            static const std::string SUPPRESS_LOCATION;
            
            static const std::string STACK_SIZE;
            
        protected:
            DishCommandLine();
            
        public:
            
            static DishCommandLine &Instance();
            
            /////
            
            INLINE bool Execute() const { return (*this)[EXECUTE]->AsBoolean(); };
            
            INLINE bool QuietMode() const { return (*this)[QUIET_MODE]->AsBoolean(); };
            
            std::string InputFileName(const std::string &fname) const;
            
            INLINE bool SymbolTablestatMode() const { return (*this)[SYMTAB_STAT_MODE]->AsBoolean(); };
            INLINE bool PrintSymbolTableMode() const { return (*this)[PRINT_SYMTAB_MODE]->AsBoolean(); };
            INLINE bool ShuffleSymbolTable() const { return (*this)[SHUFFLE_SYMTAB]->AsBoolean(); };
            
            INLINE bool PrintRngStats() const { return (*this)[PRINT_RNG_STATS]->AsBoolean(); };
            INLINE bool PrintAtomicStats() const { return (*this)[PRINT_ATOMIC_STATS]->AsBoolean(); };
            INLINE bool PrintConstantStats() const { return (*this)[PRINT_CONST_STATS]->AsBoolean(); };
            INLINE bool PrintProgramStats() const { return (*this)[PRINT_PROGRAM_STATS]->AsBoolean(); };
            
            INLINE bool PrintExecutionProfile() const { return (*this)[PRINT_EXECUTION_PROFILE]->AsBoolean(); };
            dish::ExecutionProfile::UnitsT UnitsExecutionProfile() const;
            dish::ExecutionProfile::SortT SortByExecutionProfile() const;
            
            INLINE bool PrintUsageInfo() const { return (*this)[PRINT_USAGE_INFO]->AsBoolean(); };
            
            INLINE bool ExecuteFromCommandLine() const { return (*this)[EXECUTE_FROM_CMDLN]->AsBoolean(); };
            
            INLINE bool ValidateInput() const { return (*this)[VALIDATE_INPUT]->AsBoolean(); };
            
            INLINE bool DisplayVersion() const { return (*this)[DISPLAY_VERSION]->AsBoolean(); };
            
            INLINE int StackDepth() const { return (*this)[STACK_DEPTH]->AsInteger(); };
            
            INLINE bool PrintParseTree() const { return (*this)[PRINT_PARSE_TREE]->AsBoolean(); };
            
            INLINE int RngSeed() const { return (*this)[RNG_SEED]->AsInteger(); };
            
            INLINE bool SuppressLocation() const { return (*this)[SUPPRESS_LOCATION]->AsBoolean(); };
            
            INLINE int StackSize() const { return (*this)[STACK_SIZE]->AsInteger(); };
        
            /////
            
            //  From CommandLine
            
            virtual void Process(const int argc, const char * const * const argv);
            
            virtual void PrintUsage(std::ostream &out) const;
            
    };

    ////////////////////////////////////////////////////////////////////////////

};

#endif

