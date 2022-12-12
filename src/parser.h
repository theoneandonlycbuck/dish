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

#ifndef DISH_PARSER_H
#define DISH_PARSER_H

#include "dishconfig.h"

#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <vector>

#include "inline.h"
#include "input.h"
#include "language.h"
#include "ptnode.h"
#include "tokenizer.h"

namespace dish
{

    class Parser
    {
        public:
        
#ifdef LIST_TYPE_PREFER_VECTOR
            using ExpressionListT = std::vector< std::shared_ptr< iParseTreeNode > >;
#else
            using ExpressionListT = std::list< std::shared_ptr< iParseTreeNode > >;
#endif
    
        private:
            std::shared_ptr< LanguageSymbolTable > mSymbolTable;
            
            StackedInputStream mInput;
            Tokenizer mTokenizer;
            
            const bool mSuppressLocationInformation;
            
            ExpressionListT mExpressionList;
            ExpressionListT mDeclarationList;
            
        protected:
            void generateMismatchError(const TokenTypeT &found, const TokenTypeT &expecting, const std::string &locstr) const;
        
            INLINE bool doesMatch(const TokenTypeT &tkntype) const throw() { return (tkntype == mTokenizer.This().Type); };
            
            INLINE void match(const TokenTypeT &tkntype) const { if(doesMatch(tkntype)) { return; } generateMismatchError(mTokenizer.This().Type, tkntype, mInput.LocationString()); };
            INLINE void match(const TokenTypeT &tkntype, const std::string &loc) const { if(doesMatch(tkntype)) { return; } generateMismatchError(mTokenizer.This().Type, tkntype, loc); };
            
            INLINE void consume()
            {
#ifdef TRACE
                std::cout << "Consuming a ";
                Print(mTokenizer.This());
                std::cout << "...";
                std::cout << std::endl;
#endif
            
                mTokenizer.Next(); 
            }
            
            INLINE void consume(const TokenTypeT &tkntype) { match(tkntype); consume(); };
            INLINE void consume(const TokenTypeT &tkntype, const std::string &loc) { match(tkntype, loc); consume(); };
            
            std::shared_ptr< iParseTreeNode > parseAddChain(std::shared_ptr< iParseTreeNode > node);
            std::shared_ptr< iParseTreeNode > parseMulChain(std::shared_ptr< iParseTreeNode > node);
            
            std::shared_ptr< iParseTreeNode > parseAndChain(std::shared_ptr< iParseTreeNode > node);
            std::shared_ptr< iParseTreeNode > parseOrChain(std::shared_ptr< iParseTreeNode > node);
            std::shared_ptr< iParseTreeNode > parseXorChain(std::shared_ptr< iParseTreeNode > node);
            
            std::shared_ptr< iParseTreeNode > matchInList(ExpressionListT &list, std::shared_ptr< iParseTreeNode > node);
        
        public:
            Parser(const bool profile, const int maxdepth, const std::string &source, const bool finput, const bool suppressloc = false);
            Parser(std::shared_ptr< LanguageSymbolTable > symtab, const std::string &source, const bool finput, const bool suppressloc = false);
            
            std::shared_ptr< iParseTreeNode > ParseTerminalFollower(std::shared_ptr< iParseTreeNode > base);
            std::shared_ptr< iParseTreeNode > ParseArrayLiteral();
            std::shared_ptr< iParseTreeNode > ParseTerminal();
            std::shared_ptr< iParseTreeNode > ParseParenthesized();
            std::shared_ptr< iParseTreeNode > ParsePower();
            std::shared_ptr< iParseTreeNode > ParseFactor();
            std::shared_ptr< iParseTreeNode > ParseTerm();
            std::shared_ptr< iParseTreeNode > ParseComparison();
            std::shared_ptr< iParseTreeNode > ParseExpr();
            std::shared_ptr< iParseTreeNode > ParseExpression();                //  <--
            
            std::shared_ptr< iParseTreeNode > ParseArray();
            std::shared_ptr< iParseTreeNode > ParseFunction();
            std::shared_ptr< iParseTreeNode > ParseLambdaFunction();
            std::shared_ptr< iParseTreeNode > ParseStructure();
            std::shared_ptr< iParseTreeNode > ParseType();
            std::shared_ptr< iParseTreeNode > ParseReferece();
            std::shared_ptr< iParseTreeNode > ParseDeclaration();               //  <--
            
            std::shared_ptr< iParseTreeNode > ParseLock();                      //  <--
            
            std::shared_ptr< iParseTreeNode > ParseStatementBlock();            //  <--
            
            std::shared_ptr< iParseTreeNode > ParseIfThenElse();                //  <--
            std::shared_ptr< iParseTreeNode > ParseSwitch();                    //  <--
            
            std::shared_ptr< iParseTreeNode > ParseForLoop();                   //  <--
            std::shared_ptr< iParseTreeNode > ParseForEachLoop();               //  <--
            std::shared_ptr< iParseTreeNode > ParseWhileLoop();                 //  <--
            std::shared_ptr< iParseTreeNode > ParseRepeatLoop();                //  <--
            
            std::shared_ptr< iParseTreeNode > ParseReturn();                    //  <--
            
            std::shared_ptr< iParseTreeNode > ParseImport();                    //  <--
            
            std::shared_ptr< iParseTreeNode > ParseAssert();                    //  <--
            
            
            std::shared_ptr< iParseTreeNode > ParseStatement();                 //  <--
            
            
            INLINE const LanguageSymbolTable &SymbolTable() const { return *mSymbolTable; };
            INLINE LanguageSymbolTable &SymbolTable() { return *mSymbolTable; };
            
            std::shared_ptr< iAtomic > Run();
            void Validate();
            void PrintParseTree(std::ostream &out);
            
            INLINE const std::string &Source() const { return mInput.Source(); };
            INLINE const int &Line() const { return mInput.Line(); };
            INLINE const int &Column() const { return mInput.Column(); };
            
            std::string LocationString() const;
            
            //  This method returns true if the DISH-program's entry point (the
            //  file specifed on the command-line of the interpreter) is being
            //  processed, or false otherwise (an imported file is being 
            //  processed). This information is available from the input stack.
            INLINE bool IsEntryPoint() const { return mInput.IsEntryPoint(); };
            
            void PrintRemainder(std::ostream &out);
            
            INLINE IntegerT NumCachedExpressions() const { return static_cast< IntegerT >(mExpressionList.size()); };
            INLINE IntegerT NumCachedDeclarations() const { return static_cast< IntegerT >(mDeclarationList.size()); };
            
            IntegerT ReleaseCachedParseTreeNodes();
        
    };

}

#endif

