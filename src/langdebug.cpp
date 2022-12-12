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

#include <iostream>

#include "langdebug.h"
#include "langfile.h"
#include "language.h"
#include "parser.h"
#include "ptnode.h"

/******************************************************************************

    dish::DebugPrintSymbolTableFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::DebugPrintSymbolTableFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    symtab.Print(std::cout);

    return NullValue::MakeValue();
}

/******************************************************************************

    dish::DebugPrintSymbolTable1Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::DebugPrintSymbolTable1Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > logfile_param(getParam(symtab, "logfile"));

    if(iAtomic::typeInteger == logfile_param->Type())
    {
        std::stringstream out;
        
        symtab.Print(out);
        out << std::endl;
        
        std::fputs(
            out.str().c_str(),
            FileList::Instance().Handle(logfile_param->AsInteger())
        );
    }
    else
    {
        std::ofstream out;
        out.open(logfile_param->AsString().c_str());
        
        symtab.Print(out);
        out << std::endl;
    }

    return NullValue::MakeValue();
}

/******************************************************************************

    dish::DebugPrintSymbolTableStatsFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::DebugPrintSymbolTableStatsFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    symtab.Histogram(std::cout);

    return NullValue::MakeValue();
}

/******************************************************************************

    dish::DebugPrintSymbolTableStats1Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::DebugPrintSymbolTableStats1Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > logfile_param(getParam(symtab, "logfile"));

    if(iAtomic::typeInteger == logfile_param->Type())
    {
        std::stringstream out;
        
        symtab.Histogram(out);
        out << std::endl;
        
        std::fputs(
            out.str().c_str(),
            FileList::Instance().Handle(logfile_param->AsInteger())
        );
    }
    else
    {
        std::ofstream out;
        out.open(logfile_param->AsString().c_str());
        
        symtab.Histogram(out);
        out << std::endl;
    }

    return NullValue::MakeValue();
}

/******************************************************************************

    dish::DebugPrintParseTreeFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::DebugPrintParseTreeFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    Parser parser(
        std::shared_ptr< LanguageSymbolTable >(new LanguageSymbolTable(symtab, iSymbolTable::cloneMinimal)), 
        getParam(symtab, "stmt")->AsString(),
        dish::STRING_INPUT
    );
    
    parser.PrintParseTree(std::cout);

    return NullValue::MakeValue();
}

/******************************************************************************

    dish::DebugPrintParseTree2Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::DebugPrintParseTree2Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > logfile_param(getParam(symtab, "logfile"));
    
    Parser parser(
        std::shared_ptr< LanguageSymbolTable >(new LanguageSymbolTable(symtab, iSymbolTable::cloneMinimal)), 
        getParam(symtab, "stmt")->AsString(),
        dish::STRING_INPUT
    );

    if(iAtomic::typeInteger == logfile_param->Type())
    {
        std::stringstream out;
        
        parser.PrintParseTree(out);
        out << std::endl;
        
        std::fputs(
            out.str().c_str(),
            FileList::Instance().Handle(logfile_param->AsInteger())
        );
    }
    else
    {
        std::ofstream out;
        out.open(logfile_param->AsString().c_str());
        
        parser.PrintParseTree(out);
        out << std::endl;
    }

    return NullValue::MakeValue();
}

/******************************************************************************

    dish::DebugPrintParseTreeNodeStatsFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::DebugPrintParseTreeNodeStatsFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    PrintParseTreeStatistics(std::cout);

    return NullValue::MakeValue();
}

/******************************************************************************

    dish::DebugPrintParseTreeNodeStats1Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::DebugPrintParseTreeNodeStats1Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > logfile_param(getParam(symtab, "logfile"));

    if(iAtomic::typeInteger == logfile_param->Type())
    {
        std::stringstream out;
        
        PrintParseTreeStatistics(out);
        out << std::endl;
        
        std::fputs(
            out.str().c_str(),
            FileList::Instance().Handle(logfile_param->AsInteger())
        );
    }
    else
    {
        std::ofstream out;
        out.open(logfile_param->AsString().c_str());
        
        PrintParseTreeStatistics(out);
        out << std::endl;
    }

    return NullValue::MakeValue();
}

/******************************************************************************

    dish::DebugCurrentStackDepthFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::DebugCurrentStackDepthFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return IntegerValue::MakeValue(symtab.StackDepth());
}

/******************************************************************************

    dish::DebugLogFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::DebugLogFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > logfile_param(getParam(symtab, "logfile"));

    if(iAtomic::typeInteger == logfile_param->Type())
    {
        std::fputs(
            getParam(symtab, "message")->AsString().c_str(),
            FileList::Instance().Handle(logfile_param->AsInteger())
        );
    }
    else
    {
        std::ofstream out;
        out.open(logfile_param->AsString().c_str());
        
        out << getParam(symtab, "message")->AsString();
        out << std::endl;
    }

    return NullValue::MakeValue();
}

