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

#include "dishconfig.h"

#include <sys/resource.h>

#include <algorithm>
#include <cassert>
#include <exception>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "atomics.h"
#include "cmdln.h"
#include "input.h"
#include "language.h"
#include "langmath.h"
#include "langtxtio.h"
#include "language.h"
#include "log.h"
#include "parser.h"
#include "ptnode.h"
#include "textio.h"
#include "version.h"

namespace
{

    const dish::Log::LevelT LogLevel(dish::Log::logOff);

    const Version version(MAJOR_VERSION, MINOR_VERSION, REVISION_VERSION);
    
    const Version language_version(LANG_MAJOR_VERSION, LANG_MINOR_VERSION, LANG_REVISION_VERSION);
    
    const Version library_version(LIBRARY_MAJOR_VERSION, LIBRARY_MINOR_VERSION, LIBRARY_REVISION_VERSION);
    
    std::unique_ptr< dish::Parser > parser;
    
    std::ostream &PrintSectionHeader(std::ostream &out, const std::string &title)
    {
        out << "*******************************************************************************" << std::endl;
        out << "*******************************************************************************" << std::endl;
        out << "**" << std::endl;
        out << "**  " << title << std::endl;
        out << "**" << std::endl;
        out << "*******************************************************************************" << std::endl;
        out << "*******************************************************************************" << std::endl;
        
        return out;
    }

}

bool IsInputEntryPoint()
{
    assert(0 != parser.get());

    return parser->IsEntryPoint();
}

dish::IntegerT ReleaseCachedParseTreeNodes()
{
    dish::IntegerT count(0);
    
    if(0 != parser.get())
    {
        count += parser->ReleaseCachedParseTreeNodes();
    }
    
    count += dish::IdentifierParseTreeNode::ReleaseCachedParseTreeNodes();
    count += dish::LiteralParseTreeNode::ReleaseCachedParseTreeNodes();

    return count;
}

int main(const int argc, const char * const * const argv)
{
    //  Create the logging mechanism.
    dish::Log &log(dish::Log::Instance(LogLevel, std::cout));

    //  Process the command-line arguments.
    dish::DishCommandLine &cmdln(dish::DishCommandLine::Instance());
    cmdln.Process(argc, argv);
    
    //  Set the stack size for the interpreter.
    {
        struct rlimit rl = { 0 };
        const unsigned int stacksize(
            static_cast< unsigned int >(cmdln[dish::DishCommandLine::STACK_SIZE]->AsInteger())
        );
        
        if(0 == getrlimit(RLIMIT_STACK, &rl))
        {
            const int oldstacksize(rl.rlim_cur);
        
            if(stacksize > rl.rlim_cur)
            {
                rl.rlim_cur = stacksize;
                if(0 != setrlimit(RLIMIT_STACK, &rl))
                {
                    std::cerr << std::endl;
                    std::cerr << "Unable to adjust stack size to " << stacksize << "bytes; continuing with stack size of " << oldstacksize << " bytes." << std::endl;
                    std::cerr << std::endl;
                }
            }
        }
    }
    
    //  Print the banner to the logging mechanism.
    if(!cmdln.QuietMode())
    {
        std::stringstream message;
        message << "DISH programming language v";
        message << version;
        message << " Copyright (c) 2014-2022 by Chris Buck." << std::endl;
    
        log.Writeln(dish::Log::logMessage);
        log.Writeln(dish::Log::logMessage, message.str());
        log.Writeln(dish::Log::logMessage);
    }
    
    //  Display the version number, as requested.
    if(cmdln.DisplayVersion())
    {
        std::stringstream message;
        message << "   Interpreter v" << version << std::endl;
        message << "      Language v" << language_version << std::endl;
        message << "       Library v" << library_version << std::endl;
    
        log.Writeln(dish::Log::logMessage);
        log.Writeln(dish::Log::logMessage, message.str());
        log.Writeln(dish::Log::logMessage);
    }
    
    //  Was a new seed-value for the RNG supplied? If so, apply it.
    {
        const dish::IntegerT rngseed(
            static_cast< dish::IntegerT >(cmdln.RngSeed())
        );
    
        if(rngseed > 0)
        {
            dish::RngInstance(rngseed);
        }
    }
    
    //  Are we to continue executing?
    if(cmdln.Execute())
    {
        //  Yes; if there is valid input (either file-based or passed on the 
        //  command-line), continue with execution. Otherwise the application's
        //  print usage information
        if(cmdln.Exists(dish::DishCommandLine::INPUT))
        {
            //  Build a parser for the specified input type (file vs. command-line 
            //  argument).
            {
                const std::string codesrc(cmdln.InputFileName(cmdln[dish::DishCommandLine::INPUT]->AsString()));
                
                if(!dish::DishCommandLine::Instance().ExecuteFromCommandLine())
                {
                    //  A program file was passed on the command-line.
                    log.Writeln(dish::Log::logInfo, std::string("Running ") + codesrc + "...");
                    
                    parser.reset(
                        new dish::Parser(
                            cmdln.PrintExecutionProfile(),
                            cmdln.StackDepth(),
                            codesrc,
                            dish::FILE_INPUT,
                            cmdln.SuppressLocation()
                        )
                    );
                }
                else
                {
                    //  The source to execute was passed on the command-line.
                    log.Writeln(dish::Log::logInfo, "Running code from the command-line...");
                    
                    parser.reset(
                        new dish::Parser(
                            cmdln.PrintExecutionProfile(),
                            cmdln.StackDepth(),
                            codesrc,
                            dish::STRING_INPUT,
                            cmdln.SuppressLocation()
                        )
                    );
                }
                assert(parser);
            }
            
            //  Randomize the symbol table, if requested.
            if(cmdln.ShuffleSymbolTable())
            {
                parser->SymbolTable().Shuffle();
            }
            
            //  Pass the command-line arguments to the program.
            {
                std::shared_ptr< dish::CommandLine::iValue > pargs(cmdln[dish::DishCommandLine::PROGRAM_ARGS]);
                
                std::shared_ptr< dish::iAtomic > args(dish::ArrayValue::MakeValue(0));
                
                for(int i(0), last_i(pargs->NumElements()); i < last_i; ++i)
                {
                    args->Add(dish::StringValue::MakeValue(pargs->Element(i)->AsString()), i + 1);
                }
                
                args->Lock();
                parser->SymbolTable().Insert("`CmdLnArgs", args);
                
                parser->SymbolTable().Insert("`NumCmdLnArgs", 
                    dish::IntegerValue::MakeValue(
                        (dish::iAtomic::typeNull == args->Element(0)->Type()) ? 0 : args->Member("Length")->AsInteger(), dish::LOCKED
                    )
                );
            }
            
            //  Do we print the parse-tree, execute the input, or validate it?
            if(!cmdln.PrintParseTree())
            {
                if(!cmdln.ValidateInput())
                {
                    //  Execute the input.
                    try
                    {
                        //  Make sure the terminal window is restored to non-curses mode 
                        //  upon termination.
                        dish::RestoreTerminal restore_terminal;
                        
                        //  Execute the source code via the parser.
                        parser->Run();
                    }
                    
                    catch(dish::TerminateExecutionException &e)
                    {
                        //  Invoke the termination callback.
                        dish::ErrorCallbacks::Instance().Invoke(
                            dish::ErrorCallbacks::ERR_Terminate,
                            dish::ErrorCallbacks::CallbackArg(),
                            parser->SymbolTable()
                        );
                    }
                    
                    catch(std::shared_ptr< dish::iAtomic > ret)
                    {
                        try
                        {
                            dish::DishCommandLine::Instance().SetReturnValue(static_cast< int >(ret->AsInteger()));
                        }
                        catch(...)
                        {
                            dish::DishCommandLine::Instance().SetReturnValue(-1);
                        }
                    }
                    
                    catch(dish::iExecutableAtomic::ReturnValue ret)
                    {
                        try
                        {
                            dish::DishCommandLine::Instance().SetReturnValue(static_cast< int >(ret.Value()->AsInteger()));
                        }
                        catch(...)
                        {
                            dish::DishCommandLine::Instance().SetReturnValue(-1);
                        }
                    }
                    
                    catch(dish::RuntimeException &e)
                    {
                        cmdln.SetReturnValue(-1);
                    
                        std::cerr << std::endl;
                        std::cerr << e.what() << std::endl;
                        std::cerr << std::endl;
                    }
                    
                    catch(std::exception &e)
                    {
                        cmdln.SetReturnValue(-1);
                    
                        std::cerr << std::endl;
                        std::cerr << parser->Source();
                        std::cerr << " (Ln ";
                        std::cerr << parser->Line();
                        std::cerr << ", Col ";
                        std::cerr << parser->Column();
                        std::cerr << ") : ";
                        std::cerr << e.what();
                        std::cerr << std::endl;
                        
                        std::cerr << std::endl;
                    }
                    
                    //  Invoke the OK-error handler chain if the program terminated
                    //  normally (via a call to Terminate, or returning from the global
                    //  scope). "Normal" termination is signified by a process return-
                    //  value >= 0.
                    if(cmdln.ReturnValue() >= 0)
                    {
                        try
                        {
                            dish::ErrorCallbacks::Instance().Invoke(
                                dish::ErrorCallbacks::ERR_Ok,
                                dish::ErrorCallbacks::CallbackArg(),
                                parser->SymbolTable()
                            );
                        }
                        
                        catch(dish::RuntimeException &e)
                        {
                            cmdln.SetReturnValue(-1);
                        
                            std::cerr << std::endl;
                            std::cerr << e.what() << std::endl;
                            std::cerr << std::endl;
                        }
                        
                        catch(std::exception &e)
                        {
                            cmdln.SetReturnValue(-1);
                        
                            std::cerr << std::endl;
                            std::cerr << parser->Source();
                            std::cerr << " (Ln ";
                            std::cerr << parser->Line();
                            std::cerr << ", Col ";
                            std::cerr << parser->Column();
                            std::cerr << ") : ";
                            std::cerr << e.what();
                            std::cerr << std::endl;
                            
                            std::cerr << std::endl;
                        }
                    }
                    
                    //  Print symbol-table statistics if specified on the
                    //  command-line.
                    if(cmdln.SymbolTablestatMode())
                    {
                        std::cout << std::endl;
                        std::cout << std::endl;
                        PrintSectionHeader(std::cout, "Symbol Table Statistics");
                        std::cout << std::endl;
                        parser->SymbolTable().Histogram(std::cout);
                        std::cout << std::endl;
                        std::cout << "Hashed Table Lookups: " << dish::HashedSymbolTable::GetLookupCount() << std::endl;
                        std::cout << " Basic Table Lookups: " << dish::BasicSymbolTable::GetLookupCount() << std::endl;
                        std::cout << std::endl;
                        std::cout << " Maximum Table Depth: " << parser->SymbolTable().MaxStackDepthAttained() << std::endl;
                    }
                    
                    //  Print the symbol-table contents if specified on the
                    //  command-line.
                    if(cmdln.PrintSymbolTableMode())
                    {
                        std::cout << std::endl;
                        std::cout << std::endl;
                        PrintSectionHeader(std::cout, "Symbol Table Contents");
                        std::cout << std::endl;
                        parser->SymbolTable().Print(std::cout);
                        std::cout << std::endl;
                    }
                    
                    //  Print the random-number-generator statistics if 
                    //  specified on the command-line.
                    if(cmdln.PrintRngStats())
                    {
                        std::cout << std::endl;
                        std::cout << std::endl;
                        PrintSectionHeader(std::cout, "Random-Number Generator Statistics");
                        std::cout << std::endl;
                        std::cout << "RNG Seed: " << dish::RngInstance().Seed() << std::endl;
                        std::cout << " RNG Num: " << dish::RngInstance().Num() << std::endl;
                        std::cout << std::endl;
                    }
                    
                    //  Print the constant-value statistics if specified on the
                    //  command-line.
                    if(cmdln.PrintConstantStats())
                    {
                        std::cout << std::endl;
                        std::cout << std::endl;
                        PrintSectionHeader(std::cout, "Constant-Value Statistics");
                        std::cout << std::endl;
                        dish::IntegerValue::PrintTableStatistics(std::cout);
                        std::cout << std::endl;
                    }
                    
                    //  Print the atomic instance statistics if specified on the
                    //  command-line.
                    if(cmdln.PrintAtomicStats())
                    {
                        std::cout << std::endl;
                        std::cout << std::endl;
                        PrintSectionHeader(std::cout, "Atomic-Type Usage Statistics");
                        std::cout << std::endl;
                        std::cout << "       BooleanType count: " << dish::BooleanTypeAtomic::NumInstances() << std::endl;
                        std::cout << "       IntegerType count: " << dish::IntegerTypeAtomic::NumInstances() << std::endl;
                        std::cout << " RangedIntegerType count: " << dish::RangedIntegerTypeAtomic::NumInstances() << std::endl;
                        std::cout << "          RealType count: " << dish::RealTypeAtomic::NumInstances() << std::endl;
                        std::cout << "    RangedRealType count: " << dish::RangedRealTypeAtomic::NumInstances() << std::endl;
                        std::cout << "        StringType count: " << dish::StringTypeAtomic::NumInstances() << std::endl;
                        std::cout << "         ArrayType count: " << dish::ArrayTypeAtomic::NumInstances() << std::endl;
                        std::cout << "    DictionaryType count: " << dish::DictionaryTypeAtomic::NumInstances() << std::endl;
                        std::cout << "     StructureType count: " << dish::StructureTypeAtomic::NumInstances() << std::endl;
                        std::cout << std::endl;
                        std::cout << "         NullValue count: " << dish::NullValue::NumInstances() << std::endl;
                        std::cout << std::endl;
                        std::cout << "    ReferenceValue count: " << dish::ReferenceValue::NumInstances() << std::endl;
                        std::cout << "      BooleanValue count: " << dish::BooleanValue::NumInstances() << std::endl;
                        std::cout << "      IntegerValue count: " << dish::IntegerValue::NumInstances() << std::endl;
                        std::cout << "RangedIntegerValue count: " << dish::RangedIntegerValue::NumInstances() << std::endl;
                        std::cout << "         RealValue count: " << dish::RealValue::NumInstances() << std::endl;
                        std::cout << "   RangedRealValue count: " << dish::RangedRealValue::NumInstances() << std::endl;
                        std::cout << "       StringValue count: " << dish::StringValue::NumInstances() << std::endl;
                        std::cout << "        ArrayValue count: " << dish::ArrayValue::NumInstances() << std::endl;
                        std::cout << "    StructureValue count: " << dish::StructureValue::NumInstances() << std::endl;
                        std::cout << "   DictionaryValue count: " << dish::DictionaryValue::NumInstances() << std::endl;
                        std::cout << std::endl;
                        std::cout << "        Executable count: " << dish::ExecutableAtomic::NumInstances() << std::endl;
                        std::cout << std::endl;
                    }
                    
                    //  Print the static-program structure statistics if
                    //  specified on the command-line.
                    if(cmdln.PrintProgramStats())
                    {
                        std::cout << std::endl;
                        PrintSectionHeader(std::cout, "Static Program (parse-tree) Statistics");
                        std::cout << std::endl;
                        
                        dish::PrintParseTreeStatistics(std::cout);
                        std::cout << std::endl;
                        std::cout << std::endl;
                        std::cout << "             # Cached ID Nodes: " << dish::IdentifierParseTreeNode::NumCachedNodes() << std::endl;
                        std::cout << "# Cached Integer Literal Nodes: " << dish::LiteralParseTreeNode::NumCachedIntegerLiteralNodes() << std::endl;
                        std::cout << "   # Cached Real Literal Nodes: " << dish::LiteralParseTreeNode::NumCachedRealLiteralNodes() << std::endl;
                        std::cout << " # Cached String Literal Nodes: " << dish::LiteralParseTreeNode::NumCachedStringLiteralNodes() << std::endl;
                        std::cout << "          # Cached Expressions: " << parser->NumCachedExpressions() << std::endl;
                        std::cout << "         # Cached Declarations: " << parser->NumCachedDeclarations() << std::endl;
                        std::cout << std::endl;
                    }
                    
                    //  Print the profile information for the run-time if
                    //  specified on the command-line.
                    if(cmdln.PrintExecutionProfile())
                    {
                        const dish::ExecutionProfile profile_info(parser->SymbolTable().ProfileInformation());
                        
                        std::cout << std::endl;
                        PrintSectionHeader(std::cout, "Run-Time Profile Information");
                        std::cout << std::endl;
                        
                        std::cout << "Sort-by: " << dish::ExecutionProfile::SORT_BY_LABELS[cmdln.SortByExecutionProfile()] << std::endl;
                        std::cout << "  Units: " << dish::ExecutionProfile::UNIT_LABELS[cmdln.UnitsExecutionProfile()] << std::endl;
                        std::cout << std::endl;
                        
                        std::cout << profile_info.NumUniqueFunctionCalls() << " unique functions called." << std::endl;
                        std::cout << std::endl;
                        
                        std::cout << "*******************************************************************************" << std::endl;
                        
                        std::cout << std::endl;
                        profile_info.Print(std::cout, cmdln.UnitsExecutionProfile(), cmdln.SortByExecutionProfile());
                        std::cout << std::endl;
                    }
                }
                else
                {
                    //  Validate the input.
                    try
                    {
                        parser->Validate();
                        
                        std::cout << std::endl;
                        std::cout << "OK" << std::endl;
                        std::cout << std::endl;
                    }
                    
                    catch(std::exception &e)
                    {
                        cmdln.SetReturnValue(-1);
                    
                        std::cerr << std::endl;
                        std::cerr << parser->Source();
                        std::cerr << " (Ln ";
                        std::cerr << parser->Line();
                        std::cerr << ", Col ";
                        std::cerr << parser->Column();
                        std::cerr << ") : ";
                        std::cerr << e.what();
                        std::cerr << std::endl;
                        
                        std::cerr << std::endl;
                    }
                }
            }
            else
            {
                //  Print the parse-tree node for the specified input.
                parser->PrintParseTree(std::cout);
            }
        }
    }
    
    if(cmdln.PrintUsageInfo())
    {
        cmdln.PrintUsage(std::cout);
    }
    
#ifdef RECYCLE_PRIMITIVES

    //  Clean up any cached atomic values.
    dish::BooleanValue::Destroy();
    dish::IntegerValue::Destroy();
    dish::RealValue::Destroy();
    dish::StringValue::Destroy();
    
#endif
    
    return cmdln.ReturnValue();
}

