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

#ifndef DISH_TOKENIZER_H
#define DISH_TOKENIZER_H

#include "dishconfig.h"

#include <ostream>
#include <string>

#include "inline.h"
#include "input.h"
#include "types.h"

namespace dish
{

    ////////////////////////////////////////////////////////////////////////////
    
    typedef enum
    {
        tknNull = 0,
        
        tknAddOp,
        tknSubtractOp,
        tknMultiplyOp,
        tknDivideOp,
        tknModulusOp,
        tknPowerOp,
        
        tknLessThanOp,
        tknLessThanEqualOp,
        tknEqualOp,
        tknNotEqualOp,
        tknGreaterThanEqualOp,
        tknGreaterThanOp,
        
        tknAssignmentOp,
        
        tknPeriod,
        tknComma,
        tknSemiColon,
        tknColon,
        
        tknOpenParenthesis,
        tknCloseParenthesis,
        
        tknOpenSquareBrace,
        tknCloseSquareBrace,
        
        tknOpenCurlyBrace,
        tknCloseCurlyBrace,
        
        tknAmpersand,
        
        tknAndRW,
        tknArrayRW,
        tknAsRW,
        tknAssertRW,
        tknBeginRW,
        tknBooleanRW,
        tknDictionaryRW,
        tknDeclareRW,
        tknDoRW,
        tknElseRW,
        tknEndRW,
        tknForRW,
        tknForEachRW,
        tknFunctionRW,
        tknIfRW,
        tknImportRW,
        tknInRW,
        tknIntegerRW,
        tknLambdaRW,
        tknLockRW,
        tknNotRW,
        tknOfRW,
        tknOtherwiseRW,
        tknOrRW,
        tknRealRW,
        tknReferenceRW,
        tknRepeatRW,
        tknReturnRW,
        tknStepRW,
        tknStringRW,
        tknStructureRW,
        tknSwitchRW,
        tknThenRW,
        tknToRW,
        tknTypeRW,
        tknUntilRW,
        tknWhileRW,
        tknXorRW,
        
        tknBooleanLit,
        tknIntegerLit,
        tknRealLit,
        tknStringLit,
        
        tknIdentifier,
        
        tknNUM
    } TokenTypeT;
    
    ////////////////////////////////////////////////////////////////////////////
    
    typedef struct
    {
        TokenTypeT      Type;
    } SymbolTokenT;
    
    typedef struct
    {
        TokenTypeT      Type;
        BooleanT        Value;
    } BooleanLitTokenT;
    
    typedef struct
    {
        TokenTypeT      Type;
        IntegerT        Value;
    } IntegerLitTokenT;
    
    typedef struct
    {
        TokenTypeT      Type;
        RealT           Value;
    } RealLitTokenT;
    
    typedef struct
    {
        TokenTypeT      Type;
        char *          Value;
    } StringLitTokenT;
    
    typedef struct
    {
        TokenTypeT      Type;
        char *          Id;
    } IdentifierTokenT;
    
    union TokenT
    {
        TokenTypeT          Type;
        
        SymbolTokenT        Null;
        
        SymbolTokenT        AddOp;
        SymbolTokenT        SubtractOp;
        SymbolTokenT        MultiplyOp;
        SymbolTokenT        DivideOp;
        SymbolTokenT        ModulusOp;
        SymbolTokenT        PowerOp;
        
        SymbolTokenT        LessThanOp;
        SymbolTokenT        LessThanEqualOp;
        SymbolTokenT        EqualOp;
        SymbolTokenT        NotEqualOp;
        SymbolTokenT        GreaterThanEqualOp;
        SymbolTokenT        GreaterThanOp;
        
        SymbolTokenT        AssignmentOp;
        
        SymbolTokenT        Period;
        SymbolTokenT        Comma;
        SymbolTokenT        SemiColon;
        SymbolTokenT        Colon;
        
        SymbolTokenT        OpenParenthesis;
        SymbolTokenT        CloseParenthesis;
        
        SymbolTokenT        OpenSquareBrace;
        SymbolTokenT        CloseSquareBrace;
        
        SymbolTokenT        OpenCurlyBrace;
        SymbolTokenT        CloseCurlyBrace;
        
        SymbolTokenT        Ampersand;
        
        SymbolTokenT        AndRW;
        SymbolTokenT        ArrayRW;
        SymbolTokenT        AsRW;
        SymbolTokenT        AssertRW;
        SymbolTokenT        BeginRW;
        SymbolTokenT        BooleanRW;
        SymbolTokenT        DeclareRW;
        SymbolTokenT        DictionaryRW;
        SymbolTokenT        DoRW;
        SymbolTokenT        ElseRW;
        SymbolTokenT        EndRW;
        SymbolTokenT        ForRW;
        SymbolTokenT        ForEachRW;
        SymbolTokenT        FunctionRW;
        SymbolTokenT        IfRW;
        SymbolTokenT        InRW;
        SymbolTokenT        IntegerRW;
        SymbolTokenT        ImportRW;
        SymbolTokenT        LambdaRW;
        SymbolTokenT        LockRW;
        SymbolTokenT        NotRW;
        SymbolTokenT        OfRW;
        SymbolTokenT        OtherwiseRW;
        SymbolTokenT        OrRW;
        SymbolTokenT        RealRW;
        SymbolTokenT        ReferenceRW;
        SymbolTokenT        RepeatRW;
        SymbolTokenT        ReturnRW;
        SymbolTokenT        StepRW;
        SymbolTokenT        StringRW;
        SymbolTokenT        StructureRW;
        SymbolTokenT        SwitchRW;
        SymbolTokenT        ThenRW;
        SymbolTokenT        ToRW;
        SymbolTokenT        TypeRW;
        SymbolTokenT        UntilRW;
        SymbolTokenT        WhileRW;
        SymbolTokenT        XorRW;
        
        BooleanLitTokenT    BooleanLit;
        IntegerLitTokenT    IntegerLit;
        RealLitTokenT       RealLit;
        StringLitTokenT     StringLit;
        
        IdentifierTokenT    Identifier;
        
        INLINE TokenT() : Type(tknNull) {};
        ~TokenT();
           
    };
    
    extern void DestroyToken(TokenT &tkn);
    
    ////////////////////////////////////////////////////////////////////////////

    class Tokenizer
    {
        private:
            TokenT mToken;
            
            StackedInputStream &mInput;
        
        protected:
        
            ////////////////////////////////////////////////////////////////////
        
            INLINE void destroyToken() { DestroyToken(mToken); };
            
            INLINE void setTokenType(const TokenTypeT type) { mToken.Type = type; };
            
            INLINE void createNullToken() { setTokenType(tknNull); };
            
            INLINE void createPlusOpToken() { setTokenType(tknAddOp); };
            INLINE void createSubtractOpToken() { setTokenType(tknSubtractOp); };
            INLINE void createMultiplyOpToken() { setTokenType(tknMultiplyOp); };
            INLINE void createDivideOpToken() { setTokenType(tknDivideOp); };
            INLINE void createModulusOpToken() { setTokenType(tknModulusOp); };
            INLINE void createPowerOpToken() { setTokenType(tknPowerOp); };
            
            INLINE void createLessThanOpToken() { setTokenType(tknLessThanOp); };
            INLINE void createLessThanEqualOpToken() { setTokenType(tknLessThanEqualOp); };
            INLINE void createEqualOpToken() { setTokenType(tknEqualOp); };
            INLINE void createNotEqualOpToken() { setTokenType(tknNotEqualOp); };
            INLINE void createGreaterThanEqualOpToken() { setTokenType(tknGreaterThanEqualOp); };
            INLINE void createGreaterThanOpToken() { setTokenType(tknGreaterThanOp); };
            
            INLINE void createAssignmentOpToken() { setTokenType(tknAssignmentOp); };
            
            INLINE void createPeriodToken() { setTokenType(tknPeriod); };
            INLINE void createCommaToken() { setTokenType(tknComma); };
            INLINE void createSemiColonToken() { setTokenType(tknSemiColon); };
            INLINE void createColonToken() { setTokenType(tknColon); };
            
            INLINE void createOpenParenthesisToken() { setTokenType(tknOpenParenthesis); };
            INLINE void createCloseParenthesisToken() { setTokenType(tknCloseParenthesis); };
            
            INLINE void createOpenSquareBraceToken() { setTokenType(tknOpenSquareBrace); };
            INLINE void createCloseSquareBraceToken() { setTokenType(tknCloseSquareBrace); };
            
            INLINE void createOpenCurlyBraceToken() { setTokenType(tknOpenCurlyBrace); };
            INLINE void createCloseCurlyBraceToken() { setTokenType(tknCloseCurlyBrace); };
            
            INLINE void createAmpersandToken() { setTokenType(tknAmpersand); };
            
            INLINE void createAndRWToken() { setTokenType(tknAndRW); };
            INLINE void createArrayRWToken() { setTokenType(tknArrayRW); };
            INLINE void createAsRWToken() { setTokenType(tknAsRW); };
            INLINE void createAssertRWToken() { setTokenType(tknAssertRW); };
            INLINE void createBeginRWToken() { setTokenType(tknBeginRW); };
            INLINE void createBooleanRWToken() { setTokenType(tknBooleanRW); };
            INLINE void createDeclareRWToken() { setTokenType(tknDeclareRW); };
            INLINE void createDictionaryRWToken() { setTokenType(tknDictionaryRW); };
            INLINE void createDoRWToken() { setTokenType(tknDoRW); };
            INLINE void createElseRWToken() { setTokenType(tknElseRW); };
            INLINE void createEndRWToken() { setTokenType(tknEndRW); };
            INLINE void createForRWToken() { setTokenType(tknForRW); };
            INLINE void createForEachRWToken() { setTokenType(tknForEachRW); };
            INLINE void createFunctionRWToken() { setTokenType(tknFunctionRW); };
            INLINE void createIfRWToken() { setTokenType(tknIfRW); };
            INLINE void createImportRWToken() { setTokenType(tknImportRW); };
            INLINE void createInRWToken() { setTokenType(tknInRW); };
            INLINE void createIntegerRWToken() { setTokenType(tknIntegerRW); };
            INLINE void createLambdaRWToken() { setTokenType(tknLambdaRW); };
            INLINE void createLockRWToken() { setTokenType(tknLockRW); };
            INLINE void createNotRWToken() { setTokenType(tknNotRW); };
            INLINE void createOfRWToken() { setTokenType(tknOfRW); };
            INLINE void createOtherwiseRWToken() { setTokenType(tknOtherwiseRW); };
            INLINE void createOrRWToken() { setTokenType(tknOrRW); };
            INLINE void createRealRWToken() { setTokenType(tknRealRW); };
            INLINE void createReferenceRWToken() { setTokenType(tknReferenceRW); };
            INLINE void createRepeatRWToken() { setTokenType(tknRepeatRW); };
            INLINE void createReturnRWToken() { setTokenType(tknReturnRW); };
            INLINE void createStepRWToken() { setTokenType(tknStepRW); };
            INLINE void createStringRWToken() { setTokenType(tknStringRW); };
            INLINE void createStructureRWToken() { setTokenType(tknStructureRW); };
            INLINE void createSwitchRWToken() { setTokenType(tknSwitchRW); };
            INLINE void createThenRWToken() { setTokenType(tknThenRW); };
            INLINE void createToRWToken() { setTokenType(tknToRW); };
            INLINE void createTypeRWToken() { setTokenType(tknTypeRW); };
            INLINE void createUntilRWToken() { setTokenType(tknUntilRW); };
            INLINE void createWhileRWToken() { setTokenType(tknWhileRW); };
            INLINE void createXorRWToken() { setTokenType(tknXorRW); };
            
            INLINE void createBooleanLitToken(const BooleanT value) { setTokenType(tknBooleanLit); mToken.BooleanLit.Value = value; };
            INLINE void createIntegerLitToken(const IntegerT value) { setTokenType(tknIntegerLit); mToken.IntegerLit.Value = value; };
            INLINE void createRealLitToken(const RealT value) { setTokenType(tknRealLit); mToken.RealLit.Value = value; };
            void createStringLitToken(const StringT &value);
            
            void createIdentifierToken(const std::string &id);
        
            ////////////////////////////////////////////////////////////////////
            
            void skipAllOf(const std::string &skip);
            void skipAllNotOf(const std::string &dontskip);
            
            void collectAllOf(const std::string &allow, std::string &read);
            void collectAllNotOf(const std::string &dontallow, std::string &read);
            
            INLINE void skipWhitespace() { skipAllOf(WHITESPACE_CHARACTERS); };
        
            ////////////////////////////////////////////////////////////////////
            
            static const bool POSITIVE;
            static const bool NEGATIVE;
            
            void buildNumericToken(const bool negative);
            
            
            void buildLiteralStringToken(const bool single_quote);
            
            
            static const bool ACCENTED;
            static const bool NOT_ACCENTED;
            
            void buildIdentifierToken(const bool accented);
        
            ////////////////////////////////////////////////////////////////////
        
        public:
            INLINE Tokenizer(StackedInputStream &input) : mToken(), mInput(input) { createNullToken(); };
            INLINE ~Tokenizer() { destroyToken(); };
            
            INLINE bool Empty() const throw() { return mInput.Empty(); };
            
            INLINE const TokenT &This() const throw() { return mToken; };
            const TokenT &Next();

    };
    
    ////////////////////////////////////////////////////////////////////////////
    
    extern void Print(const TokenTypeT &tkn, std::ostream &out = std::cout);
    extern void Print(const TokenT &tkn, std::ostream &out = std::cout);
    
    ////////////////////////////////////////////////////////////////////////////

}

#endif

