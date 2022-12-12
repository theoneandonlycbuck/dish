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

#include <cctype>
#include <cstring>
#include <map>
#include <sstream>

#include "exception.h"
#include "tokenizer.h"
#include "utility.h"

namespace
{

    struct ci_less
    {
    
        INLINE bool operator()(const std::string &s1, const std::string &s2) const
        {
            return dish::IsLessThan(s1, s2, dish::CASE_INSENSITIVE);
	    }
        
    };

}

/******************************************************************************

    dish::TokenT member definitions

 ******************************************************************************/

dish::TokenT::~TokenT()
{
    DestroyToken(*this);
}

/******************************************************************************

    dish::TokenT function definitions

 ******************************************************************************/

void dish::DestroyToken(dish::TokenT &tkn)
{
    switch(tkn.Type)
    {
        case tknStringLit:
        {
            delete [] tkn.StringLit.Value;
            tkn.StringLit.Value = 0;
        } break;
        
        case tknIdentifier:
        {
            delete [] tkn.Identifier.Id;
            tkn.Identifier.Id = 0;
        } break;
        
        default:
        {
            //  Empty;
        }
        
    }
    
    tkn.Type = tknNull;
}

/******************************************************************************

    dish::Tokenizer class definitions

 ******************************************************************************/
 
const bool dish::Tokenizer::POSITIVE(false);
const bool dish::Tokenizer::NEGATIVE(true);

const bool dish::Tokenizer::ACCENTED(true);
const bool dish::Tokenizer::NOT_ACCENTED(false);

void dish::Tokenizer::createStringLitToken(const dish::StringT &value)
{
    mToken.Type = tknStringLit;
    
    const std::string::size_type nbytes(value.length() + 1);

    mToken.StringLit.Value = new char[nbytes];
    std::strncpy(mToken.StringLit.Value, value.c_str(), nbytes);
}

void dish::Tokenizer::createIdentifierToken(const std::string &id)
{
    mToken.Type = tknIdentifier;
    
    const std::string::size_type nbytes(id.length() + 1);

    mToken.Identifier.Id = new char[nbytes];
    std::strncpy(mToken.Identifier.Id, id.c_str(), nbytes);
}

void dish::Tokenizer::skipAllOf(const std::string &skip)
{
    int ch;
    
    do
    {
        ch = mInput.Get();
    } while(std::string::npos != skip.find(ch));
    
    if(iInputStream::END_OF_INPUT != ch)
    {
        mInput.Unget(ch);
    }
}

void dish::Tokenizer::skipAllNotOf(const std::string &dontskip)
{
    int ch;
    
    do
    {
        ch = mInput.Get();
    } while(std::string::npos == dontskip.find(ch));
    
    if(iInputStream::END_OF_INPUT != ch)
    {
        mInput.Unget(ch);
    }
}

void dish::Tokenizer::collectAllOf(const std::string &allow, std::string &read)
{
    int ch;
    
    for(bool done(false); !done; )
    {
        ch = mInput.Get();
        
        if(std::string::npos != allow.find(ch))
        {
            read.push_back(ch);
        }
        else
        {
            done = true;
        }
    }
    
    if(iInputStream::END_OF_INPUT != ch)
    {
        mInput.Unget(ch);
    }
}

void dish::Tokenizer::collectAllNotOf(const std::string &dontallow, std::string &read)
{
    int ch;
    
    for(bool done(false); !done; )
    {
        ch = mInput.Get();
        
        if(std::string::npos == dontallow.find(ch))
        {
            read.push_back(ch);
        }
        else
        {
            done = true;
        }
    }
    
    if(iInputStream::END_OF_INPUT != ch)
    {
        mInput.Unget(ch);
    }
}

void dish::Tokenizer::buildNumericToken(const bool negative)
{
    std::string numeric;
    collectAllOf(DIGIT_CHARACTERS, numeric);
    
    const int ch(mInput.Get());
    if('.' == ch)
    {
        numeric.push_back(ch);
        collectAllOf(DIGIT_CHARACTERS, numeric);
        
        RealT value;
        {
            std::stringstream input(numeric);
            input >> value;
        }
        
        createRealLitToken(negative ? -value : value);
    }
    else
    {
        mInput.Unget(ch);
    
        IntegerT value;
        {
            std::stringstream input(numeric);
            input >> value;
        }
        
        createIntegerLitToken(negative ? -value : value);
    }
}

void dish::Tokenizer::buildLiteralStringToken(const bool single_quote)
{
    const int terminal_quote(single_quote ? '\'' : '\"');
    std::string value;
    
    for(bool done(false); !done; )
    {
        int ch(mInput.Get());
        
        if('\\' == ch)
        {
            ch = mInput.Get();
            
            switch(ch)
            {
                case '\\':
                {
                    value.push_back('\\');
                } break;
                
                case '\'':
                {
                    value.push_back('\'');
                } break;
                
                case '\"':
                {
                    value.push_back('\"');
                } break;
                
                case 'r':
                {
                    value.push_back('\r');
                } break;
                
                case 'n':
                {
                    value.push_back('\n');
                } break;
                
                case 't':
                {
                    value.push_back('\t');
                } break;
                
                default:
                {
                    std::stringstream message;
                    message << "Invalid escape sequence within a string literal: \\";
                    message << static_cast< char >(ch);
                    message << ".";
                    
                    throw IllegalInputException(message.str());
                }
                
            }
        }
        
        else if(terminal_quote == ch)
        {
            done = true;
        }
        
        else if(iInputStream::END_OF_INPUT == ch)
        {
            throw UnexpectedEndOfInputException("Unexpected end-of-input before termination of a string literal.");
        }
        
        else
        {
            value.push_back(ch);
        }
    }
    
    createStringLitToken(value);
}

void dish::Tokenizer::buildIdentifierToken(const bool accented)
{
    std::string id;
    collectAllOf(VALID_ID_CHARACTERS, id);
    
    if(!id.empty())
    {
    
        using Id2RwT = std::map< std::string, TokenTypeT, ci_less >;
    
        static Id2RwT Id2RW;
        static Id2RwT::const_iterator last_Id2RW;
        
        if(Id2RW.empty())
        {
            Id2RW[std::string("And")] = tknAndRW;
            Id2RW[std::string("Array")] = tknArrayRW;
            Id2RW[std::string("As")] = tknAsRW;
            Id2RW[std::string("Assert")] = tknAssertRW;
            Id2RW[std::string("Begin")] = tknBeginRW;
            Id2RW[std::string("Boolean")] = tknBooleanRW;
            Id2RW[std::string("Declare")] = tknDeclareRW;
            Id2RW[std::string("Dictionary")] = tknDictionaryRW;
            Id2RW[std::string("Do")] = tknDoRW;
            Id2RW[std::string("Else")] = tknElseRW;
            Id2RW[std::string("End")] = tknEndRW;
            Id2RW[std::string("For")] = tknForRW;
            Id2RW[std::string("ForEach")] = tknForEachRW;
            Id2RW[std::string("Function")] = tknFunctionRW;
            Id2RW[std::string("If")] = tknIfRW;
            Id2RW[std::string("Import")] = tknImportRW;
            Id2RW[std::string("In")] = tknInRW;
            Id2RW[std::string("Integer")] = tknIntegerRW;
            Id2RW[std::string("Lambda")] = tknLambdaRW;
            Id2RW[std::string("Lock")] = tknLockRW;
            Id2RW[std::string("Locked")] = tknLockRW;   //  Treak 'locked' as a synonym for 'lock'.
            Id2RW[std::string("Not")] = tknNotRW;
            Id2RW[std::string("Of")] = tknOfRW;
            Id2RW[std::string("Otherwise")] = tknOtherwiseRW;
            Id2RW[std::string("Or")] = tknOrRW;
            Id2RW[std::string("Real")] = tknRealRW;
            Id2RW[std::string("Reference")] = tknReferenceRW;
            Id2RW[std::string("Repeat")] = tknRepeatRW;
            Id2RW[std::string("Return")] = tknReturnRW;
            Id2RW[std::string("Step")] = tknStepRW;
            Id2RW[std::string("String")] = tknStringRW;
            Id2RW[std::string("Structure")] = tknStructureRW;
            Id2RW[std::string("Switch")] = tknSwitchRW;
            Id2RW[std::string("Then")] = tknThenRW;
            Id2RW[std::string("To")] = tknToRW;
            Id2RW[std::string("Type")] = tknTypeRW;
            Id2RW[std::string("Until")] = tknUntilRW;
            Id2RW[std::string("While")] = tknWhileRW;
            Id2RW[std::string("Xor")] = tknXorRW;
            
            last_Id2RW = Id2RW.end();
        }
        
        const auto rw(Id2RW.find(id));
        
        if(last_Id2RW != rw)
        {
            setTokenType(rw->second);
        }
        
        else if(IsEqual(id, "True", CASE_INSENSITIVE)) 
        {
            createBooleanLitToken(true);
        }
        
        else if(IsEqual(id, "False", CASE_INSENSITIVE)) 
        {
            createBooleanLitToken(false);
        }
    
        else
        {
            if(accented)
            {
                id.insert(0, 1, '`');
            }
            
            createIdentifierToken(id);
        }
    }
    else
    {
        throw IllegalInputException("Unexpected input: Expecting an indentifier but only foud the accent '`'.");
    }
}

const dish::TokenT &dish::Tokenizer::Next()
{
    destroyToken();
    
    for(bool done(false); !done; )
    {
        done = true;
    
        skipWhitespace();

        int ch(mInput.Get());
        
        switch(ch)
        {
            case '+':
            {
                ch = mInput.Get();
                mInput.Unget(ch);
                
                if(!std::isdigit(ch))
                {
                    createPlusOpToken();
                }
                else
                {
                    buildNumericToken(POSITIVE);
                }
            } break;
            
            case '-':
            {
                ch = mInput.Get();
                mInput.Unget(ch);
                
                if(!std::isdigit(ch))
                {
                    createSubtractOpToken();
                }
                else
                {
                    buildNumericToken(NEGATIVE);
                }
            } break;
            
            case '*':
            {
                createMultiplyOpToken();
            } break;
            
            case '/':
            {
                createDivideOpToken();
            } break;
            
            case '%':
            {
                createModulusOpToken();
            } break;
            
            case '^':
            {
                createPowerOpToken();
            } break;
            
            case '<':
            {
                ch = mInput.Get();
                
                if('=' == ch)
                {
                    createLessThanEqualOpToken();
                }
                else
                {
                    createLessThanOpToken();
                    mInput.Unget(ch);
                }
            } break;
            
            case '=':
            {
                ch = mInput.Get();
                
                if('=' == ch)
                {
                    createEqualOpToken();
                }
                else
                {
                    createAssignmentOpToken();
                    mInput.Unget(ch);
                }
            } break;
            
            case '>':
            {
                ch = mInput.Get();
                
                if('=' == ch)
                {
                    createGreaterThanEqualOpToken();
                }
                else
                {
                    createGreaterThanOpToken();
                    mInput.Unget(ch);
                }
            } break;
            
            case '.':
            {
                createPeriodToken();
            } break;
            
            case ',':
            {
                createCommaToken();
            } break;
            
            case ';':
            {
                createSemiColonToken();
            } break;
            
            case ':':
            {
                createColonToken();
            } break;
            
            case '(':
            {
                createOpenParenthesisToken();
            } break;
            
            case ')':
            {
                createCloseParenthesisToken();
            } break;
            
            case '[':
            {
                createOpenSquareBraceToken();
            } break;
            
            case ']':
            {
                createCloseSquareBraceToken();
            } break;
            
            case '{':
            {
                createOpenCurlyBraceToken();
            } break;
            
            case '}':
            {
                createCloseCurlyBraceToken();
            } break;
            
            case '&':
            {
                createAmpersandToken();
            } break;
            
            case '\'':
            {
                buildLiteralStringToken(true);
            } break;
            
            case '\"':
            {
                buildLiteralStringToken(false);
            } break;
            
            case '#':
            {
                skipAllNotOf(EOLN_CHARACTERS);
                
                done = false;
            } break;
            
            case '!':
            {
                ch = mInput.Get();
                
                if('=' == ch)
                {
                    createNotEqualOpToken();
                }
                else
                {
                    std::stringstream message;
                    message << "Unexpected input: Expecting '=' but found '";
                    message << static_cast< char >(ch);
                    message << "'.";
                    
                    throw IllegalInputException(message.str());
                }
            } break;
            
            case '`':
            {
                buildIdentifierToken(ACCENTED);
            } break;
            
            default:
            {
                if(iInputStream::END_OF_INPUT != ch)
                {
                    if(std::isdigit(ch))
                    {
                        mInput.Unget(ch);
                        buildNumericToken(NOT_ACCENTED);
                    }
                    
                    else if(std::isalpha(ch))
                    {
                        mInput.Unget(ch);
                        buildIdentifierToken(NOT_ACCENTED);
                    }
                    
                    else
                    {
                        std::stringstream message;
                        message << "Unexpected input: '";
                        message << static_cast< char >(ch);
                        message << "'.";
                        
                        throw IllegalInputException(message.str());
                    }
                }
                else
                {
                    createNullToken();
                }
            }
            
        }
    }
    
    return This();
}

/******************************************************************************

    Global function definitions

 ******************************************************************************/
 
void dish::Print(const TokenTypeT &tkn, std::ostream &out)
{
    static std::map< TokenTypeT, std::string > TokenTypeStrings;
    static std::map< TokenTypeT, std::string >::const_iterator lastTokenTypeStrings;
    
    if(TokenTypeStrings.empty())
    {
        TokenTypeStrings[tknNull] = "tkntype: null";
        TokenTypeStrings[tknAddOp] = "tkntype: +";
        TokenTypeStrings[tknSubtractOp] = "tkntype: -";
        TokenTypeStrings[tknMultiplyOp] = "tkntype: *";
        TokenTypeStrings[tknDivideOp] = "tkntype: /";
        TokenTypeStrings[tknModulusOp] = "tkntype: %";
        TokenTypeStrings[tknPowerOp] = "tkntype: ^";
        TokenTypeStrings[tknLessThanOp] = "tkntype: <";
        TokenTypeStrings[tknLessThanEqualOp] = "tkntype: <=";
        TokenTypeStrings[tknEqualOp] = "tkntype: ==";
        TokenTypeStrings[tknNotEqualOp] = "tkntype: !=";
        TokenTypeStrings[tknGreaterThanEqualOp] = "tkntype: >=";
        TokenTypeStrings[tknGreaterThanOp] = "tkntype: >";
        TokenTypeStrings[tknAssignmentOp] = "tkntype: =";
        TokenTypeStrings[tknPeriod] = "tkntype: .";
        TokenTypeStrings[tknComma] = "tkntype: ,";
        TokenTypeStrings[tknSemiColon] = "tkntype: ;";
        TokenTypeStrings[tknColon] = "tkntype: :";
        TokenTypeStrings[tknOpenParenthesis] = "tkntype: (";
        TokenTypeStrings[tknCloseParenthesis] = "tkntype: )";
        TokenTypeStrings[tknOpenSquareBrace] = "tkntype: [";
        TokenTypeStrings[tknCloseSquareBrace] = "tkntype: ]";
        TokenTypeStrings[tknOpenCurlyBrace] = "tkntype: {";
        TokenTypeStrings[tknCloseCurlyBrace] = "tkntype: }";
        TokenTypeStrings[tknAmpersand] = "tkntype: &";
        TokenTypeStrings[tknAndRW] = "tkntype: and";
        TokenTypeStrings[tknArrayRW] = "tkntype: array";
        TokenTypeStrings[tknAsRW] = "tkntype: as";
        TokenTypeStrings[tknAssertRW] = "tkntype: assert";
        TokenTypeStrings[tknBeginRW] = "tkntype: begin";
        TokenTypeStrings[tknBooleanRW] = "tkntype: boolean";
        TokenTypeStrings[tknDeclareRW] = "tkntype: declare";
        TokenTypeStrings[tknDictionaryRW] = "tkntype: dictionary";
        TokenTypeStrings[tknDoRW] = "tkntype: do";
        TokenTypeStrings[tknElseRW] = "tkntype: else";
        TokenTypeStrings[tknEndRW] = "tkntype: end";
        TokenTypeStrings[tknForRW] = "tkntype: for";
        TokenTypeStrings[tknForEachRW] = "tkntype: foreach";
        TokenTypeStrings[tknFunctionRW] = "tkntype: function";
        TokenTypeStrings[tknIfRW] = "tkntype: if";
        TokenTypeStrings[tknImportRW] = "tkntype: import";
        TokenTypeStrings[tknInRW] = "tkntype: in";
        TokenTypeStrings[tknIntegerRW] = "tkntype: integer";
        TokenTypeStrings[tknLambdaRW] = "tkntype: lambda";
        TokenTypeStrings[tknLockRW] = "tkntype: lock";
        TokenTypeStrings[tknNotRW] = "tkntype: not";
        TokenTypeStrings[tknOfRW] = "tkntype: of";
        TokenTypeStrings[tknOtherwiseRW] = "tkntype: otherwise";
        TokenTypeStrings[tknOrRW] = "tkntype: or";
        TokenTypeStrings[tknRealRW] = "tkntype: real";
        TokenTypeStrings[tknReturnRW] = "tkntype: reference";
        TokenTypeStrings[tknReturnRW] = "tkntype: return";
        TokenTypeStrings[tknRepeatRW] = "tkntype: repeat";
        TokenTypeStrings[tknStepRW] = "tkntype: step";
        TokenTypeStrings[tknStringRW] = "tkntype: string";
        TokenTypeStrings[tknStructureRW] = "tkntype: structure";
        TokenTypeStrings[tknSwitchRW] = "tkntype: switch";
        TokenTypeStrings[tknThenRW] = "tkntype: then";
        TokenTypeStrings[tknToRW] = "tkntype: to";
        TokenTypeStrings[tknTypeRW] = "tkntype: type";
        TokenTypeStrings[tknUntilRW] = "tkntype: until";
        TokenTypeStrings[tknWhileRW] = "tkntype: while";
        TokenTypeStrings[tknXorRW] = "tkntype: xor";
        TokenTypeStrings[tknBooleanLit] = "tkntype: boolean lit";
        TokenTypeStrings[tknIntegerLit] = "tkntype: integer lit";
        TokenTypeStrings[tknRealLit] = "tkntype: real lit";
        TokenTypeStrings[tknStringLit] = "tkntype: string lit";
        TokenTypeStrings[tknIdentifier] = "tkntype: id";
        
        lastTokenTypeStrings = TokenTypeStrings.end();
    }
    
    const auto tknstr(TokenTypeStrings.find(tkn));
    
    if(lastTokenTypeStrings != tknstr)
    {
        out << tknstr->second;
    }
    else
    {
        out << "<unknown tkn type>";
    }
}
 
void dish::Print(const dish::TokenT &tkn, std::ostream &out)
{
    switch(tkn.Type)
    {
        case tknNull:
        {
            out << "tkn(null)";
        } break;
        
        case tknAddOp:
        {
            out << "tkn(+)";
        } break;
        
        case tknSubtractOp:
        {
            out << "tkn(-)";
        } break;
        
        case tknMultiplyOp:
        {
            out << "tkn(*)";
        } break;
        
        case tknDivideOp:
        {
            out << "tkn(/)";
        } break;
        
        case tknModulusOp:
        {
            out << "tkn(%)";
        } break;
        
        case tknPowerOp:
        {
            out << "tkn(^)";
        } break;
        
        case tknLessThanOp:
        {
            out << "tkn(<)";
        } break;
        
        case tknLessThanEqualOp:
        {
            out << "tkn(<=)";
        } break;
        
        case tknEqualOp:
        {
            out << "tkn(==)";
        } break;
        
        case tknNotEqualOp:
        {
            out << "tkn(!=)";
        } break;
        
        case tknGreaterThanEqualOp:
        {
            out << "tkn(>=)";
        } break;
        
        case tknGreaterThanOp:
        {
            out << "tkn(>)";
        } break;
        
        case tknAssignmentOp:
        {
            out << "tkn(=)";
        } break;
        
        case tknPeriod:
        {
            out << "tkn(.)";
        } break;
        
        case tknComma:
        {
            out << "tkn(,)";
        } break;
        
        case tknSemiColon:
        {
            out << "tkn(;)";
        } break;
        
        case tknColon:
        {
            out << "tkn(:)";
        } break;
        
        case tknOpenParenthesis:
        {
            out << "tkn('(')";
        } break;
        
        case tknCloseParenthesis:
        {
            out << "tkn(')')";
        } break;
        
        case tknOpenSquareBrace:
        {
            out << "tkn([)";
        } break;
        
        case tknCloseSquareBrace:
        {
            out << "tkn(])";
        } break;
        
        case tknOpenCurlyBrace:
        {
            out << "tkn({)";
        } break;
        
        case tknCloseCurlyBrace:
        {
            out << "tkn(})";
        } break;
        
        case tknAmpersand:
        {
            out << "tkn(&)";
        } break;
        
        case tknAndRW:
        {
            out << "tkn(RW: and)";
        } break;
        
        case tknArrayRW:
        {
            out << "tkn(RW: array)";
        } break;
        
        case tknAsRW:
        {
            out << "tkn(RW: as)";
        } break;
        
        case tknAssertRW:
        {
            out << "tkn(RW: assert)";
        } break;
        
        case tknBeginRW:
        {
            out << "tkn(RW: begin)";
        } break;
        
        case tknBooleanRW:
        {
            out << "tkn(RW: boolean)";
        } break;
        
        case tknDeclareRW:
        {
            out << "tkn(RW: declare)";
        } break;
        
        case tknDictionaryRW:
        {
            out << "tkn(RW: dictionary)";
        } break;
        
        case tknDoRW:
        {
            out << "tkn(RW: do)";
        } break;
        
        case tknElseRW:
        {
            out << "tkn(RW: else)";
        } break;
        
        case tknEndRW:
        {
            out << "tkn(RW: end)";
        } break;
        
        case tknForRW:
        {
            out << "tkn(RW: for)";
        } break;
        
        case tknForEachRW:
        {
            out << "tkn(RW: foreach)";
        } break;
        
        case tknFunctionRW:
        {
            out << "tkn(RW: function)";
        } break;
        
        case tknIfRW:
        {
            out << "tkn(RW: if)";
        } break;
        
        case tknImportRW:
        {
            out << "tkn(RW: import)";
        } break;
        
        case tknInRW:
        {
            out << "tkn(RW: in)";
        } break;
        
        case tknIntegerRW:
        {
            out << "tkn(RW: integer)";
        } break;
        
        case tknLambdaRW:
        {
            out << "tkn(RW: lambda)";
        } break;
        
        case tknLockRW:
        {
            out << "tkn(RW: lock)";
        } break;
        
        case tknNotRW:
        {
            out << "tkn(RW: not)";
        } break;
        
        case tknOfRW:
        {
            out << "tkn(RW: of)";
        } break;
        
        case tknOtherwiseRW:
        {
            out << "tkn(RW: otherwise)";
        } break;
        
        case tknOrRW:
        {
            out << "tkn(RW: or)";
        } break;
        
        case tknRealRW:
        {
            out << "tkn(RW: real)";
        } break;
        
        case tknReferenceRW:
        {
            out << "tkn(RW: reference)";
        } break;
        
        case tknRepeatRW:
        {
            out << "tkn(RW: repeat)";
        } break;
        
        case tknReturnRW:
        {
            out << "tkn(RW: return)";
        } break;
        
        case tknStepRW:
        {
            out << "tkn(RW: step)";
        } break;
        
        case tknStringRW:
        {
            out << "tkn(RW: string)";
        } break;
        
        case tknStructureRW:
        {
            out << "tkn(RW: structure)";
        } break;
        
        case tknSwitchRW:
        {
            out << "tkn(RW: switch)";
        } break;
        
        case tknThenRW:
        {
            out << "tkn(RW: then)";
        } break;
        
        case tknToRW:
        {
            out << "tkn(RW: to)";
        } break;
        
        case tknTypeRW:
        {
            out << "tkn(RW: type)";
        } break;
        
        case tknUntilRW:
        {
            out << "tkn(RW: until)";
        } break;
        
        case tknWhileRW:
        {
            out << "tkn(RW: while)";
        } break;
        
        case tknXorRW:
        {
            out << "tkn(RW: xor)";
        } break;
        
        case tknBooleanLit:
        {
            out << "tkn(boolean: ";
            out << (tkn.BooleanLit.Value ? "true" : "false");
            out << ")";
        } break;
        
        case tknIntegerLit:
        {
            out << "tkn(integer: ";
            out << tkn.IntegerLit.Value;
            out << ")";
        } break;
        
        case tknRealLit:
        {
            out << "tkn(real: ";
            out << tkn.RealLit.Value;
            out << ")";
        } break;
        
        case tknStringLit:
        {
            out << "tkn(string: \"";
            out << tkn.StringLit.Value;
            out << "\")";
        } break;
        
        case tknIdentifier:
        {
            out << "tkn(ID: \"";
            out << tkn.Identifier.Id;
            out << "\")";
        } break;
        
        default:
        {
            out << "<unknown tkn>";
        }
         
    }
}

