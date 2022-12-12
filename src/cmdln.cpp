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

#include <algorithm>
#include <cassert>
#include <sstream>

#include "cmdln.h"
#include "language.h"
#include "symtab.h"
#include "utility.h"

/******************************************************************************

    dish::CommandLine::iValue class definitions

 ******************************************************************************/
 
bool dish::CommandLine::iValue::AsBoolean() const
{
    throw InvalidTypeConversion();
}

int dish::CommandLine::iValue::AsInteger() const
{
    throw InvalidTypeConversion();
}

double dish::CommandLine::iValue::AsReal() const
{
    throw InvalidTypeConversion();
}

std::string dish::CommandLine::iValue::AsString() const
{
    throw InvalidTypeConversion();
}

int dish::CommandLine::iValue::NumElements() const
{
    return 0;
}

void dish::CommandLine::iValue::AddElement(std::shared_ptr< dish::CommandLine::iValue > element)
{
    throw InvalidTypeConversion();
}

std::shared_ptr< dish::CommandLine::iValue > dish::CommandLine::iValue::Element(const int index) const
{
    throw InvalidTypeConversion();
}

/******************************************************************************

    dish::CommandLine::BooleanValue class definitions

 ******************************************************************************/
 
bool dish::CommandLine::BooleanValue::AsBoolean() const
{
    return mValue;
}

void dish::CommandLine::BooleanValue::Print(std::ostream &out) const
{
    out << (mValue ? "True" : "False");
}

/******************************************************************************

    dish::CommandLine::IntegerValue class definitions

 ******************************************************************************/
 
int dish::CommandLine::IntegerValue::AsInteger() const
{
    return mValue;
}

void dish::CommandLine::IntegerValue::Print(std::ostream &out) const
{
    out << mValue;
}

/******************************************************************************

    dish::CommandLine::RealValue class definitions

 ******************************************************************************/
 
double dish::CommandLine::RealValue::AsReal() const
{
    return mValue;
}

void dish::CommandLine::RealValue::Print(std::ostream &out) const
{
    out << mValue;
}

/******************************************************************************

    dish::CommandLine::StringValue class definitions

 ******************************************************************************/
 
std::string dish::CommandLine::StringValue::AsString() const
{
    return mValue;
}

void dish::CommandLine::StringValue::Print(std::ostream &out) const
{
    out << mValue;
}

/******************************************************************************

    dish::CommandLine::ArrayValue class definitions

 ******************************************************************************/
 
int dish::CommandLine::ArrayValue::NumElements() const
{
    return static_cast< int >(mValue.size());
}

void dish::CommandLine::ArrayValue::AddElement(std::shared_ptr< dish::CommandLine::iValue > element)
{
    assert(element);

    mValue.push_back(element);
}

std::shared_ptr< dish::CommandLine::iValue > dish::CommandLine::ArrayValue::Element(const int index) const
{
    return mValue.at(index);
}

void dish::CommandLine::ArrayValue::Print(std::ostream &out) const
{
    out << "CmdLn::Array[  ";

    std::for_each(
        mValue.begin(), mValue.end(),
        [&](const ArrayT::value_type &element)
        {
            element->Print(out);
            out << "  ";
        }
    );
    
    out << "]" << std::endl;
}

/******************************************************************************

    dish::CommandLine class definitions

 ******************************************************************************/

const std::string dish::CommandLine::EXE("exe");

const std::string dish::CommandLine::ARGC("argc");
const std::string dish::CommandLine::ARGV("argv");

const std::string dish::CommandLine::RETURN_VALUE("ReturnValue");

void dish::CommandLine::Print(std::ostream &out) const
{
    out << "Dictionary" << std::endl;
    out << "{" << std::endl;

    std::for_each(
        mDictionary.begin(), mDictionary.end(),
        [&](const DictionaryT::value_type &value)
        {
            out << "    ";
            out << value.first;
            out << " = ";
            value.second->Print(out);
            out << std::endl;
        }
    );
    
    out << "}" << std::endl;
}

std::shared_ptr< dish::CommandLine::iValue > dish::CommandLine::operator[](const std::string &key) const
{
    const DictionaryT::const_iterator element(mDictionary.find(key));
    
    if(mDictionary.end() != element)
    {
        return element->second;
    }
    
    throw NoSuchSymbol();
}

void dish::CommandLine::Process(const int argc, const char * const * const argv)
{
    assert(argc > 0);
    assert(0 != argv);
    
    //  Add the executable.
    add(EXE, argv[0]);
    
    //  Add the argument count.
    add(ARGC, argc);
    
    //  Add the argument values.
    {
        std::shared_ptr< iValue > argvnode(new ArrayValue());
        
        for(int i(0); i < argc; ++i)
        {
            argvnode->AddElement(std::shared_ptr< iValue >(new StringValue(argv[i])));
        }
        
        add(ARGV, argvnode);
    }
    
    //  Add the return value.
    add(RETURN_VALUE, 0);
}

/******************************************************************************

    dish::DishCommandLine class definitions

 ******************************************************************************/
 
const std::string dish::DishCommandLine::EXECUTE("Execute");
 
const std::string dish::DishCommandLine::QUIET_MODE("QuietMode");
 
const std::string dish::DishCommandLine::INCLUDE_PATHS("IncludePath");
const std::string dish::DishCommandLine::INPUT("Input");
const std::string dish::DishCommandLine::PROGRAM_ARGS("Arguments");

const std::string dish::DishCommandLine::SYMTAB_STAT_MODE("SymbolTableStatsMode");
const std::string dish::DishCommandLine::PRINT_SYMTAB_MODE("PrintSymbolTableMode");
const std::string dish::DishCommandLine::SHUFFLE_SYMTAB("SuffleSymbolTable");

const std::string dish::DishCommandLine::PRINT_RNG_STATS("PrintRandomNumberGeneratorStats");
const std::string dish::DishCommandLine::PRINT_ATOMIC_STATS("PrintAtomicStats");
const std::string dish::DishCommandLine::PRINT_CONST_STATS("PrintConstStats");
const std::string dish::DishCommandLine::PRINT_PROGRAM_STATS("PrintProgramStats");

const std::string dish::DishCommandLine::PRINT_EXECUTION_PROFILE("PrintExecutionProfile");
const std::string dish::DishCommandLine::SORTBY_EXECUTION_PROFILE("SortByExecutionProfile");
const std::string dish::DishCommandLine::UNITS_EXECUTION_PROFILE("UnitsExecutionProfile");

const std::string dish::DishCommandLine::PRINT_USAGE_INFO("PrintUsageInfo");

const std::string dish::DishCommandLine::EXECUTE_FROM_CMDLN("ExecuteFromCommandLine");

const std::string dish::DishCommandLine::VALIDATE_INPUT("ValidateInput");

const std::string dish::DishCommandLine::DISPLAY_VERSION("DisplayVersion");

const std::string dish::DishCommandLine::STACK_DEPTH("StackDepth");

const std::string dish::DishCommandLine::PRINT_PARSE_TREE("PrintParseTree");

const std::string dish::DishCommandLine::RNG_SEED("RngSeedValue");

const std::string dish::DishCommandLine::SUPPRESS_LOCATION("SuppressLocation");

const std::string dish::DishCommandLine::STACK_SIZE("StackSize");

dish::DishCommandLine::DishCommandLine() : dish::CommandLine()
{
    add(EXECUTE, true);
    add(QUIET_MODE, false);
    add(INCLUDE_PATHS, std::shared_ptr< iValue >(new ArrayValue()));
    add(PROGRAM_ARGS, std::shared_ptr< iValue >(new ArrayValue()));
    add(SYMTAB_STAT_MODE, false);
    add(PRINT_SYMTAB_MODE, false);
    add(SHUFFLE_SYMTAB, false);
    add(PRINT_USAGE_INFO, false);
    add(PRINT_RNG_STATS, false);
    add(PRINT_ATOMIC_STATS, false);
    add(PRINT_CONST_STATS, false);
    add(PRINT_PROGRAM_STATS, false);
    add(PRINT_EXECUTION_PROFILE, false);
    add(SORTBY_EXECUTION_PROFILE, static_cast< int >(dish::ExecutionProfile::sortName));
    add(UNITS_EXECUTION_PROFILE, static_cast< int >(dish::ExecutionProfile::unitsMicroSeconds));
    add(EXECUTE_FROM_CMDLN, false);
    add(VALIDATE_INPUT, false);
    add(DISPLAY_VERSION, false);
    add(STACK_DEPTH, StackedSymbolTable::INFINITE_STACK_DEPTH);
    add(PRINT_PARSE_TREE, false);
    add(RNG_SEED, static_cast< int >(-1));
    add(SUPPRESS_LOCATION, true);
    add(STACK_SIZE, static_cast< int >(8 * 1024 * 1024));
}

dish::DishCommandLine &dish::DishCommandLine::Instance()
{
    static DishCommandLine cmdln;
    
    return cmdln;
}

std::string dish::DishCommandLine::InputFileName(const std::string &fname) const
{
    if(FileExists(fname))
    {
        return fname;
    }
    
    {
        std::shared_ptr< iValue > paths((*this)[INCLUDE_PATHS]);
    
        for(int i(0), last_i(paths->NumElements()); i != last_i; ++i)
        {
            const std::string full_fname(paths->Element(i)->AsString() + fname);
            
            if(FileExists(full_fname))
            {
                return full_fname;
            }
        }
    }
    
    std::stringstream message;
    message << "File not found: ";
    message << fname;
    message << ".";
    
    throw NoSuchFileException(message.str());
}

dish::ExecutionProfile::UnitsT dish::DishCommandLine::UnitsExecutionProfile() const
{
    switch((*this)[UNITS_EXECUTION_PROFILE]->AsInteger())
    {
        case ExecutionProfile::unitsNanoSeconds:
        {
            return ExecutionProfile::unitsNanoSeconds;
        }
        
        case ExecutionProfile::unitsMicroSeconds:
        {
            return ExecutionProfile::unitsMicroSeconds;
        }
        
        case ExecutionProfile::unitsMilliSeconds:
        {
            return ExecutionProfile::unitsMilliSeconds;
        }
        
        case ExecutionProfile::unitsSeconds:
        {
            return ExecutionProfile::unitsSeconds;
        }
        
        default:
        {
            //  Empty
        }
         
    }
    
    return ExecutionProfile::unitsMicroSeconds;
}

dish::ExecutionProfile::SortT dish::DishCommandLine::SortByExecutionProfile() const
{
    switch((*this)[SORTBY_EXECUTION_PROFILE]->AsInteger())
    {
        case ExecutionProfile::sortName:
        {
            return ExecutionProfile::sortName;
        }
        
        case ExecutionProfile::sortTime:
        {
            return ExecutionProfile::sortTime;
        }
        
        case ExecutionProfile::sortCalls:
        {
            return ExecutionProfile::sortCalls;
        }
        
        default:
        {
            //  Empty
        }
         
    }
    
    return ExecutionProfile::sortName;
}

void dish::DishCommandLine::Process(const int argc, const char * const * const argv)
{
    CommandLine::Process(argc, argv);
    
    //  Process the argument list.
    int i(1);
    for(bool done(false); (!done) && (i < argc); ++i)
    {
        const std::string arg(argv[i]);
        
        if((arg == "-quiet") || (arg == "-q"))
        {
            add(QUIET_MODE, true);
        }
    
        else if(BeginsWith(arg, "-I"))
        {
            std::string path(arg.substr(2));
            
            if(!EndsWith(path, '/'))
            {
                path += static_cast< char >('/');
            }
            
            (*this)[INCLUDE_PATHS]->AddElement(std::shared_ptr< iValue >(new StringValue(path)));
        }
        
        else if(arg == "-symtabstats")
        {
            add(SYMTAB_STAT_MODE, true);
        }
        
        else if(arg == "-printsymtab")
        {
            add(PRINT_SYMTAB_MODE, true);
        }
        
        else if(arg == "-shufflesymtab")
        {
            add(SHUFFLE_SYMTAB, true);
        }
        
        else if(arg == "-rngstats")
        {
            add(PRINT_RNG_STATS, true);
        }
        
        else if(arg == "-atomicstats")
        {
            add(PRINT_ATOMIC_STATS, true);
        }
        
        else if(arg == "-conststats")
        {
            add(PRINT_CONST_STATS, true);
        }
        
        else if(arg == "-progstats")
        {
            add(PRINT_PROGRAM_STATS, true);
        }
        
        else if(arg == "-profile")
        {
            add(PRINT_EXECUTION_PROFILE, true);
        }
        
        else if(arg == "-profsort")
        {
            if(++i < argc)
            {
                const std::string criteria(argv[i]);
            
                if(criteria == "fname")
                {
                    add(SORTBY_EXECUTION_PROFILE, static_cast< int >(ExecutionProfile::sortName));
                }
                
                else if(criteria == "calls")
                {
                    add(SORTBY_EXECUTION_PROFILE, static_cast< int >(ExecutionProfile::sortCalls));
                }
                
                else if(criteria == "time")
                {
                    add(SORTBY_EXECUTION_PROFILE, static_cast< int >(ExecutionProfile::sortTime));
                }
                
                else
                {
                    add(EXECUTE, false);
                    add(PRINT_USAGE_INFO, true);
                    
                    std::cerr << std::endl;
                    std::cerr << "ERROR: '" << criteria << "' is not a valid argument for the -profsort command-line option." << std::endl;
                    std::cerr << std::endl;
                    
                    done = true;
                }
            }
            else
            {
                add(EXECUTE, false);
                add(PRINT_USAGE_INFO, true);
                
                std::cerr << std::endl;
                std::cerr << "ERROR: The -profsort command-line option requires an argument." << std::endl;
                std::cerr << std::endl;
                
                done = true;
            }
        }
        
        else if(arg == "-profunits")
        {
            if(++i < argc)
            {
                const std::string units(argv[i]);
            
                if(units == "ns")
                {
                    add(UNITS_EXECUTION_PROFILE, static_cast< int >(ExecutionProfile::unitsNanoSeconds));
                }
                
                else if(units == "us")
                {
                    add(UNITS_EXECUTION_PROFILE, static_cast< int >(ExecutionProfile::unitsMicroSeconds));
                }
                
                else if(units == "ms")
                {
                    add(UNITS_EXECUTION_PROFILE, static_cast< int >(ExecutionProfile::unitsMilliSeconds));
                }
                
                else if(units == "s")
                {
                    add(UNITS_EXECUTION_PROFILE, static_cast< int >(ExecutionProfile::unitsSeconds));
                }
                
                else
                {
                    add(EXECUTE, false);
                    add(PRINT_USAGE_INFO, true);
                    
                    std::cerr << std::endl;
                    std::cerr << "ERROR: '" << units << "' is not a valid argument for the -profunits command-line option." << std::endl;
                    std::cerr << std::endl;
                    
                    done = true;
                }
            }
            else
            {
                add(EXECUTE, false);
                add(PRINT_USAGE_INFO, true);
                
                std::cerr << std::endl;
                std::cerr << "ERROR: The -profunits command-line option requires an argument." << std::endl;
                std::cerr << std::endl;
                
                done = true;
            }
        }
        
        else if((arg == "-help") || (arg == "-?"))
        {
            add(EXECUTE, false);
            add(PRINT_USAGE_INFO, true);
        }
        
        else if(arg == "-x")
        {
            add(EXECUTE_FROM_CMDLN, true);
        }
        
        else if(arg == "-validate")
        {
            add(VALIDATE_INPUT, true);
        }
        
        else if(arg == "-version")
        {
            add(EXECUTE, false);
            add(DISPLAY_VERSION, true);
        }
        
        else if(arg == "-stack")
        {
            if(++i < argc)
            {
                std::stringstream input(argv[i]);
                
                int stackdepth;
                input >> stackdepth;
            
                add(STACK_DEPTH, stackdepth);
            }
            else
            {
                add(EXECUTE, false);
                add(PRINT_USAGE_INFO, true);
                
                std::cerr << std::endl;
                std::cerr << "ERROR: The -stack command-line option requires an argument." << std::endl;
                std::cerr << std::endl;
                
                done = true;
            }
        }
        
        else if(arg == "-sysstack")
        {
            if(++i < argc)
            {
                std::stringstream input(argv[i]);
                
                int sysstack;
                input >> sysstack;
            
                add(STACK_SIZE, sysstack);
            }
            else
            {
                add(EXECUTE, false);
                add(PRINT_USAGE_INFO, true);
                
                std::cerr << std::endl;
                std::cerr << "ERROR: The -sysstack command-line option requires an argument." << std::endl;
                std::cerr << std::endl;
                
                done = true;
            }
        }
        
        else if(arg == "-rngseed")
        {
            if(++i < argc)
            {
                std::stringstream input(argv[i]);
                
                int rngseed;
                input >> rngseed;
            
                add(RNG_SEED, rngseed);
            }
            else
            {
                add(EXECUTE, false);
                add(PRINT_USAGE_INFO, true);
                
                std::cerr << std::endl;
                std::cerr << "ERROR: The -rngseed command-line option requires an argument." << std::endl;
                std::cerr << std::endl;
                
                done = true;
            }
        }
        
        else if(arg == "-printparsetree")
        {
            add(PRINT_PARSE_TREE, true);
        }
        
        else if(arg == "-addlocation")
        {
            add(SUPPRESS_LOCATION, false);
        }
        
        else
        {
            add(INPUT, arg);
            done = true;
        }
    }
    
    for(; i < argc; ++i)
    {
        (*this)[PROGRAM_ARGS]->AddElement(std::shared_ptr< iValue >(new StringValue(argv[i])));
    }
}

void dish::DishCommandLine::PrintUsage(std::ostream &out) const
{
    out << "Usage:" << std::endl;
    out << std::endl;
    out << "    dish [options] <source files>" << std::endl;
    out << std::endl;
    out << "where [options] is one or more of the following:" << std::endl;
    out << std::endl;
    out << "    -quiet             : Run in quiet mode." << std::endl;
    out << "    -symtabstats       : Display symbol-table statistics." << std::endl;
    out << "    -printsymtab       : Print the symbol tables." << std::endl;
    out << "    -shufflesymtab     : Shuffle the insertion order of the runtime into the symbol table." << std::endl;
    out << "    -rngstats          : Display random-number-generator statistics." << std::endl;
    out << "    -atomicstats       : Display atomic type instance counts." << std::endl;
    out << "    -conststats        : Display constant-value statistics." << std::endl;
    out << "    -progstats         : Display static program-structure statistics." << std::endl;
    out << "    -profile           : Print an execution profile (function timings)." << std::endl;
    out << "    -profsort <crit>   : Set the sorting criteria for the profile report, where <crit> must" << std::endl;
    out << "                         be one of:" << std::endl;
    out << "                             fname : Sort by increasing function name." << std::endl;
    out << "                             calls : Sort by decreasing number of function calls." << std::endl;
    out << "                              time : Sort by decreating execution time." << std::endl;
    out << "    -profunits <units> : Set the time units for the profile report, where <units> must be" << std::endl;
    out << "                         one of:" << std::endl;
    out << "                                ns : Nano-seconds" << std::endl;
    out << "                                us : Micro-seconds" << std::endl;
    out << "                                ms : Milli-seconds" << std::endl;
    out << "                                 s : Seconds" << std::endl;
    out << "    -x                 : Execute from the command-line." << std::endl;
    out << "    -validate          : Validate, don't execute, the input." << std::endl;
    out << "    -I<dir>            : Add a search path for source files." << std::endl;
    out << "    -rngseed <int>     : Set the seed-value for the random-number generator." << std::endl;
    out << "    -stack <int>       : Set the maximum stack depth." << std::endl;
    out << "    -printparsetree    : Print the parse-tree of the specified input." << std::endl;
    out << "    -addlocation       : Add location information to the parse-tree." << std::endl;
    out << "    -version           : Display the version of the interpreter and language." << std::endl;
    out << "    -sysstack <int>    : Set the stack size for the interpreter (default 8MB)." << std::endl;
    out << "    -? or -help        : Display this usage information." << std::endl;
    out << std::endl;
}

