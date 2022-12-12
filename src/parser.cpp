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

#include <algorithm>
#include <cassert>
#include <sstream>
#include <vector>

#include "cmdln.h"
#include "exception.h"
#include "log.h"
#include "parser.h"

/******************************************************************************

    dish::Parser class definitions

 ******************************************************************************/
 
void dish::Parser::generateMismatchError(const TokenTypeT &found, const TokenTypeT &expecting, const std::string &locstr) const
{
    std::stringstream message;
    message << "Syntax error: Expecting ";
    Print(expecting, message);
    message << " but found ";
    Print(found, message);
    message << ".";
    
    throw SyntaxErrorException(mInput.LocationString(), message.str());
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::parseAddChain(std::shared_ptr< dish::iParseTreeNode > node)
{
    std::shared_ptr< AddOpChainParseTreeNode > addnode(
        mSuppressLocationInformation ? AddOpChainParseTreeNode::MakeValue(node) : AddOpChainParseTreeNode::MakeValue(mInput.LocationString(), node)
    );

    for(bool done(false); !done; )
    {
        switch(mTokenizer.This().Type)
        {
            case tknAddOp:
            {
                consume();
                
                std::shared_ptr< iParseTreeNode > op(ParseComparison());
                addnode->AddOperand(op);
            } break;
            
            case tknSubtractOp:
            {
                consume();
                
                std::shared_ptr< iParseTreeNode > op(ParseComparison());
                addnode->AddOperand(
                    NegateOpParseTreeNode::MakeValue(op)
                );
            } break;
            
            default:
            {
                done = true;
            }
            
        }
    }
    
    return addnode;
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::parseMulChain(std::shared_ptr< dish::iParseTreeNode > node)
{
    std::shared_ptr< MulOpChainParseTreeNode > mulnode(
        mSuppressLocationInformation ? MulOpChainParseTreeNode::MakeValue(node) : MulOpChainParseTreeNode::MakeValue(mInput.LocationString(), node)
    );

    for(bool done(false); !done; )
    {
        if(tknMultiplyOp == mTokenizer.This().Type)
        {
            consume();
            
            std::shared_ptr< iParseTreeNode > op(ParseFactor());
            mulnode->AddOperand(op);
        }
        else
        {
            done = true;
        }
    }
    
    return mulnode;
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::parseAndChain(std::shared_ptr< dish::iParseTreeNode > node)
{
    std::shared_ptr< AndOpChainParseTreeNode > andnode(
        mSuppressLocationInformation ? AndOpChainParseTreeNode::MakeValue(node) : AndOpChainParseTreeNode::MakeValue(mInput.LocationString(), node)
    );

    for(bool done(false); !done; )
    {
        if(tknAndRW == mTokenizer.This().Type)
        {
            consume();
            
            std::shared_ptr< iParseTreeNode > op(ParseComparison());
            andnode->AddOperand(op);
        }
        else
        {
            done = true;
        }
    }
    
    return andnode;
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::parseOrChain(std::shared_ptr< dish::iParseTreeNode > node)
{
    std::shared_ptr< OrOpChainParseTreeNode > ornode(
        mSuppressLocationInformation ? OrOpChainParseTreeNode::MakeValue(node) : OrOpChainParseTreeNode::MakeValue(mInput.LocationString(), node)
    );

    for(bool done(false); !done; )
    {
        if(tknOrRW == mTokenizer.This().Type)
        {
            consume();
            
            std::shared_ptr< iParseTreeNode > op(ParseComparison());
            ornode->AddOperand(op);
        }
        else
        {
            done = true;
        }
    }
    
    return ornode;
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::parseXorChain(std::shared_ptr< dish::iParseTreeNode > node)
{
    std::shared_ptr< XorOpChainParseTreeNode > xornode(
        mSuppressLocationInformation ? XorOpChainParseTreeNode::MakeValue(node) : XorOpChainParseTreeNode::MakeValue(mInput.LocationString(), node)
    );

    for(bool done(false); !done; )
    {
        if(tknXorRW == mTokenizer.This().Type)
        {
            consume();
            
            std::shared_ptr< iParseTreeNode > op(ParseComparison());
            xornode->AddOperand(op);
        }
        else
        {
            done = true;
        }
    }
    
    return xornode;
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::matchInList(dish::Parser::ExpressionListT &list, std::shared_ptr< dish::iParseTreeNode > node)
{
    if(mSuppressLocationInformation)
    {
        for(ExpressionListT::const_iterator i(list.begin()), last_i(list.end()); i != last_i; ++i)
        {
            if(node->IsEqual(**i))
            {
                return *i;
            }
        }
        
        list.push_back(node);
    }
    
    return node;
}
 
dish::Parser::Parser(const bool profile, const int maxdepth, const std::string &source, const bool finput, const bool suppressloc) :
    mSymbolTable(new LanguageSymbolTable(profile, maxdepth)),
    
    mInput(source, finput),
    mTokenizer(mInput),
    
    mSuppressLocationInformation(suppressloc),
    
    mExpressionList(),
    mDeclarationList()
{
#ifdef LIST_TYPE_PREFER_VECTOR
    mExpressionList.reserve(LIST_TYPE_PREFER_VECTOR);
    mDeclarationList.reserve(LIST_TYPE_PREFER_VECTOR);
#endif

    mTokenizer.Next();
}

dish::Parser::Parser(std::shared_ptr< LanguageSymbolTable > symtab, const std::string &source, const bool finput, const bool suppressloc) :
    mSymbolTable(symtab),
    
    mInput(source, finput),
    mTokenizer(mInput),
    
    mSuppressLocationInformation(suppressloc),
    
    mExpressionList(),
    mDeclarationList()
{
    assert(mSymbolTable);

#ifdef LIST_TYPE_PREFER_VECTOR
    mExpressionList.reserve(LIST_TYPE_PREFER_VECTOR);
    mDeclarationList.reserve(LIST_TYPE_PREFER_VECTOR);
#endif

    mTokenizer.Next();
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::ParseTerminalFollower(std::shared_ptr< dish::iParseTreeNode > base)
{
#ifdef TRACE
    TraceBlock trace("ParseTerminalFollower");
#endif

    switch(mTokenizer.This().Type)
    {
        //  Parse member access.
        case tknPeriod:
        {
            consume();
            
            match(tknIdentifier);
            if('`' != mTokenizer.This().Identifier.Id[0])
            {
                const std::string member(mTokenizer.This().Identifier.Id);
                consume();
            
                return ParseTerminalFollower(
                    mSuppressLocationInformation ? MemberParseTreeNode::MakeValue(base, member) : MemberParseTreeNode::MakeValue(mInput.LocationString(), base, member)
                );
            }
            
            std::stringstream message;
            message << "Syntax error: Access to members cannot be accented (";
            message << mTokenizer.This().Identifier.Id;
            message << ").";
            
            throw SyntaxErrorException(mInput.LocationString(), message.str());
        };
        
        //  Parse function call.
        case tknOpenParenthesis:
        {
            consume();
            
            FunctionCallParseTreeNode::ParameterListT param_list;
        
            if(!doesMatch(tknCloseParenthesis))
            {
                param_list.push_back(ParseExpression());
            
                for(bool done(false); !done; )
                {
                    switch(mTokenizer.This().Type)
                    {
                        case tknCloseParenthesis:
                        {
                            consume();
                            done = true;
                        } break;
                        
                        case tknComma:
                        {
                            consume();
                            param_list.push_back(ParseExpression());
                        } break;
                        
                        default:
                        {
                            std::stringstream message;
                            message << "Syntax error: Unexpected token ";
                            Print(mTokenizer.This().Type, message);
                            message << " is not valid in this context.";
                            
                            throw SyntaxErrorException(mInput.LocationString(), message.str());
                        }
                        
                    }
                }
            }
            else
            {
                consume();
            }
            
            if(typeid(IdentifierParseTreeNode) == typeid(*base))
            {
                std::stringstream mangled_id;
                mangled_id << dynamic_cast< IdentifierParseTreeNode & >(*base).Id();
                mangled_id << "_";
                mangled_id << param_list.size();
            
                return ParseTerminalFollower(
                    FunctionCallParseTreeNode::MakeValue(
                        mInput.LocationString(), 
                        mSuppressLocationInformation ? IdentifierParseTreeNode::MakeValue(mangled_id.str()) : IdentifierParseTreeNode::MakeValue(base->LocationString(), mangled_id.str()), 
                        param_list
                    )
                );
            }
            
            return ParseTerminalFollower(
                mSuppressLocationInformation ? FunctionCallParseTreeNode::MakeValue(base, param_list) : FunctionCallParseTreeNode::MakeValue(mInput.LocationString(), base, param_list)
            );
        };
        
        //  Parse array element access.
        case tknOpenSquareBrace:
        {
            //  Parse an array index.
            consume();
            
            std::shared_ptr< iParseTreeNode > index(ParseExpression());
            
            consume(tknCloseSquareBrace);
            
            return ParseTerminalFollower(
                mSuppressLocationInformation ? IndexParseTreeNode::MakeValue(base, index) : IndexParseTreeNode::MakeValue(mInput.LocationString(), base, index)
            );
        };
        
        //  We have a naked base.
        default:
        {
            //  Empty
        }
        
    }
    
    return base;
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::ParseArrayLiteral()
{
#ifdef TRACE
    TraceBlock trace("ParseArrayLiteral");
#endif

    consume(tknOpenCurlyBrace);

    std::shared_ptr< LiteralArrayParseTreeNode > node(
        mSuppressLocationInformation ? LiteralArrayParseTreeNode::MakeValue() : LiteralArrayParseTreeNode::MakeValue(mInput.LocationString())
    );
    
    if(!doesMatch(tknCloseCurlyBrace))
    {
        for(bool done(false); !done; )
        {
            node->Add(ParseExpression());
            
            if(doesMatch(tknComma))
            {
                consume();
            }
            else
            {
                done = true;
            }
        }
    }
    
    consume(tknCloseCurlyBrace);
    
    return node;
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::ParseTerminal()
{
#ifdef TRACE
    TraceBlock trace("ParseTerminal");
#endif

    switch(mTokenizer.This().Type)
    {
        case tknOpenCurlyBrace:
        {
            return ParseTerminalFollower(ParseArrayLiteral());
        };
    
        case tknIdentifier:
        {
            std::shared_ptr< IdentifierParseTreeNode > node(
                mSuppressLocationInformation ? IdentifierParseTreeNode::MakeValue(mTokenizer.This().Identifier.Id) : IdentifierParseTreeNode::MakeValue(mInput.LocationString(), mTokenizer.This().Identifier.Id)
            );
            consume();
            
            return ParseTerminalFollower(node);
        };
        
        case tknLambdaRW:
        {
            return ParseLambdaFunction();
        };
        
        case tknStringLit:
        {
            const StringT litval(mTokenizer.This().StringLit.Value);
        
            std::shared_ptr< LiteralParseTreeNode > node(
                mSuppressLocationInformation ? LiteralParseTreeNode::MakeValue(litval) : LiteralParseTreeNode::MakeValue(mInput.LocationString(), litval)
            );
            consume();
            
            return ParseTerminalFollower(node);
        };
        
        case tknRealLit:
        {
            const RealT litval(mTokenizer.This().RealLit.Value);
        
            std::shared_ptr< LiteralParseTreeNode > node(
                mSuppressLocationInformation ? LiteralParseTreeNode::MakeValue(litval) : LiteralParseTreeNode::MakeValue(mInput.LocationString(), litval)
            );
            consume();
            
            return ParseTerminalFollower(node);
        };
        
        case tknIntegerLit:
        {
            const IntegerT litval(mTokenizer.This().IntegerLit.Value);
        
            std::shared_ptr< LiteralParseTreeNode > node(
                mSuppressLocationInformation ? LiteralParseTreeNode::MakeValue(litval) : LiteralParseTreeNode::MakeValue(mInput.LocationString(), litval)
            );
            consume();
            
            return ParseTerminalFollower(node);
        };
        
        case tknBooleanLit:
        {
            std::shared_ptr< LiteralParseTreeNode > node(
                mSuppressLocationInformation ? LiteralParseTreeNode::MakeValue(mTokenizer.This().BooleanLit.Value) : LiteralParseTreeNode::MakeValue(mInput.LocationString(), mTokenizer.This().BooleanLit.Value)
            );
            consume();
            
            return ParseTerminalFollower(node);
        };
        
        default:
        {
            //  Empty
        }
        
    }
    
    std::stringstream message;
    message << "Syntax error: ";
    Print(mTokenizer.This().Type, message);
    message << " is not a valid terminal.";
    
    throw SyntaxErrorException(mInput.LocationString(), message.str());
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::ParseParenthesized()
{
#ifdef TRACE
    TraceBlock trace("ParseParenthesized");
#endif

    if(tknOpenParenthesis == mTokenizer.This().Type)
    {
        consume();
        
        std::shared_ptr< iParseTreeNode > node(ParseExpression());
        
        consume(tknCloseParenthesis);
        
        return node;
    }
    
    return ParseTerminal();
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::ParsePower()
{
#ifdef TRACE
    TraceBlock trace("ParsePower");
#endif

    std::shared_ptr< iParseTreeNode > node(ParseParenthesized());
    
    if(doesMatch(tknPowerOp))
    {
        consume();
                
        std::shared_ptr< iParseTreeNode > factor(ParseFactor());
        
        node = mSuppressLocationInformation ? PowOpParseTreeNode::MakeValue(node, factor) : PowOpParseTreeNode::MakeValue(mInput.LocationString(), node, factor);
    }
    
    return node;
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::ParseFactor()
{
#ifdef TRACE
    TraceBlock trace("ParseFactor");
#endif

    std::shared_ptr< dish::iParseTreeNode > node;

    switch(mTokenizer.This().Type)
    {
        case tknSubtractOp:
        {
            consume();
            
            std::shared_ptr< iParseTreeNode > opr(ParseFactor());
            
            node = mSuppressLocationInformation ? NegateOpParseTreeNode::MakeValue(opr) : NegateOpParseTreeNode::MakeValue(mInput.LocationString(), opr);
        } break;
        
        case tknNotRW:
        {
            consume();
            
            std::shared_ptr< iParseTreeNode > opr(ParseFactor());
            
            node = mSuppressLocationInformation ? NotOpParseTreeNode::MakeValue(opr) : NotOpParseTreeNode::MakeValue(mInput.LocationString(), opr);
        } break;
        
        default:
        {
            node = ParsePower();
        }
        
    }
    
    return node;
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::ParseTerm()
{
#ifdef TRACE
    TraceBlock trace("ParseTerm");
#endif

    std::shared_ptr< dish::iParseTreeNode > node(ParseFactor());
    
    for(bool done(false); !done; )
    {
        switch(mTokenizer.This().Type)
        {
            case tknMultiplyOp:
            {
                node = parseMulChain(node);
            } break;
            
            case tknDivideOp:
            {
                consume();
                
                std::shared_ptr< iParseTreeNode > factor(ParseFactor());
                
                node = mSuppressLocationInformation ? DivOpParseTreeNode::MakeValue(node, factor) : DivOpParseTreeNode::MakeValue(mInput.LocationString(), node, factor);
            } break;
            
            case tknModulusOp:
            {
                consume();
                
                std::shared_ptr< iParseTreeNode > factor(ParseFactor());
                
                node = mSuppressLocationInformation ? ModOpParseTreeNode::MakeValue(node, factor) : ModOpParseTreeNode::MakeValue(mInput.LocationString(), node, factor);
            } break;
            
            default:
            {
                done = true;
            }
            
        }
    }
    
    return node;
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::ParseComparison()
{
#ifdef TRACE
    TraceBlock trace("ParseComparison");
#endif

    std::shared_ptr< dish::iParseTreeNode > node(ParseTerm());
    
    for(bool done(false); !done; )
    {
        switch(mTokenizer.This().Type)
        {
            case tknLessThanOp:
            {
                consume();
                
                std::shared_ptr< iParseTreeNode > lhs(ParseTerm());
                
                node = mSuppressLocationInformation ? LessThanOpParseTreeNode::MakeValue(node, lhs) : LessThanOpParseTreeNode::MakeValue(mInput.LocationString(), node, lhs);
            } break;
            
            case tknLessThanEqualOp:
            {
                consume();
                
                std::shared_ptr< iParseTreeNode > lhs(ParseTerm());
                
                node = mSuppressLocationInformation ? LessThanEqualOpParseTreeNode::MakeValue(node, lhs) : LessThanEqualOpParseTreeNode::MakeValue(mInput.LocationString(), node, lhs);
            } break;
            
            case tknEqualOp:
            {
                consume();
                
                std::shared_ptr< iParseTreeNode > lhs(ParseTerm());
                
                node = mSuppressLocationInformation ? EqualOpParseTreeNode::MakeValue(node, lhs) : EqualOpParseTreeNode::MakeValue(mInput.LocationString(), node, lhs);
            } break;
            
            case tknNotEqualOp:
            {
                consume();
                
                std::shared_ptr< iParseTreeNode > lhs(ParseTerm());
                
                node = mSuppressLocationInformation ? NotEqualOpParseTreeNode::MakeValue(node, lhs) : NotEqualOpParseTreeNode::MakeValue(mInput.LocationString(), node, lhs);
            } break;
            
            case tknGreaterThanEqualOp:
            {
                consume();
                
                std::shared_ptr< iParseTreeNode > lhs(ParseTerm());
                
                node = mSuppressLocationInformation ? GreaterThanEqualOpParseTreeNode::MakeValue(node, lhs) : GreaterThanEqualOpParseTreeNode::MakeValue(mInput.LocationString(), node, lhs);
            } break;
            
            case tknGreaterThanOp:
            {
                consume();
                
                std::shared_ptr< iParseTreeNode > lhs(ParseTerm());
                
                node = mSuppressLocationInformation ? GreaterThanOpParseTreeNode::MakeValue(node, lhs) : GreaterThanOpParseTreeNode::MakeValue(mInput.LocationString(), node, lhs);
            } break;
            
            default:
            {
                done = true;
            }
            
        }
    }
    
    return node;
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::ParseExpr()
{
#ifdef TRACE
    TraceBlock trace("ParseExpr");
#endif

    std::shared_ptr< dish::iParseTreeNode > node(ParseComparison());
    
    for(bool done(false); !done; )
    {
        switch(mTokenizer.This().Type)
        {
            case tknAddOp:
            case tknSubtractOp:
            {
                node = parseAddChain(node);
            } break;
            
            case tknAndRW:
            {
                node = parseAndChain(node);
            } break;
            
            case tknOrRW:
            {
                node = parseOrChain(node);
            } break;
            
            case tknXorRW:
            {
                node = parseXorChain(node);
            } break;
            
            default:
            {
                done = true;
            }
            
        }
    }
    
    return node;
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::ParseExpression()
{
#ifdef TRACE
    TraceBlock trace("ParseExpression");
#endif

    std::shared_ptr< dish::iParseTreeNode > node(ParseExpr());

    if(doesMatch(tknAssignmentOp))
    {
        consume();
        
        std::shared_ptr< iParseTreeNode > lhs(ParseExpression());
        
        node = mSuppressLocationInformation ? AssignmentParseTreeNode::MakeValue(node, lhs) : AssignmentParseTreeNode::MakeValue(mInput.LocationString(), node, lhs);
    }
    
    return matchInList(mExpressionList, node);
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::ParseArray()
{
#ifdef TRACE
    TraceBlock trace("ParseArray");
#endif

    consume(tknArrayRW);
    consume(tknOpenSquareBrace);
    std::shared_ptr< iParseTreeNode > from(ParseExpression());
    consume(tknToRW);
    std::shared_ptr< iParseTreeNode > to(ParseExpression());
    consume(tknCloseSquareBrace);
    consume(tknOfRW);
    std::shared_ptr< iParseTreeNode > type(ParseType());
    
    return mSuppressLocationInformation ? ArrayTypeParseTreeNode::MakeValue(from, to, type) : ArrayTypeParseTreeNode::MakeValue(mInput.LocationString(), from, to, type);
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::ParseFunction()
{
#ifdef TRACE
    TraceBlock trace("ParseFunction");
#endif

    consume(tknFunctionRW);

    if(doesMatch(tknIdentifier))
    {
        const std::string id(mTokenizer.This().Identifier.Id);
        consume();
        
        consume(tknOpenParenthesis);
        
        iExecutableAtomic::ParamListT formalparams;
        
        if(!doesMatch(tknCloseParenthesis))
        {
            for(bool done(false); !done; )
            {
                bool ref(false);
                
                if(doesMatch(tknAmpersand))
                {
                    ref = true;
                    consume();
                }
            
                match(tknIdentifier, "ParseFunction");
                const std::string param(mTokenizer.This().Identifier.Id);
                consume();
            
                formalparams.push_back(std::make_pair(param, ref));
                
                if(doesMatch(tknComma))
                {
                    consume();
                }
                else
                {
                    done = true;
                }
            }
        }
        
        consume(tknCloseParenthesis);
        
        std::stringstream mangled_id;
        mangled_id << id;
        mangled_id << "_";
        mangled_id << formalparams.size();
        
        std::shared_ptr< iParseTreeNode > body(ParseStatement());
        
        return mSuppressLocationInformation ? DeclareFunctionParseTreeNode::MakeValue(mangled_id.str(), formalparams, body) : DeclareFunctionParseTreeNode::MakeValue(mInput.LocationString(), mangled_id.str(), formalparams, body);
    }
    
    std::stringstream message;
    message << "Syntax error: '";
    Print(mTokenizer.This().Type, message);
    message << "' is not a valid function identifier.";
    
    throw SyntaxErrorException(mInput.LocationString(), message.str());
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::ParseLambdaFunction()
{
#ifdef TRACE
    TraceBlock trace("ParseLambdaFunction");
#endif

    consume(tknLambdaRW);
    consume(tknOpenParenthesis);
    
    iExecutableAtomic::ParamListT formalparams;
    if(!doesMatch(tknCloseParenthesis))
    {
        for(bool done(false); !done; )
        {
            bool ref(false);
            
            if(doesMatch(tknAmpersand))
            {
                ref = true;
                consume();
            }
        
            match(tknIdentifier, "ParseLambdaFunction");
            const std::string param(mTokenizer.This().Identifier.Id);
            consume();
        
            formalparams.push_back(std::make_pair(param, ref));
            
            if(doesMatch(tknComma))
            {
                consume();
            }
            else
            {
                done = true;
            }
        }
    }
    
    consume(tknCloseParenthesis);
    
    std::shared_ptr< iParseTreeNode > body(ParseStatement());
    
    return mSuppressLocationInformation ? LambdaFunctionParseTreeNode::MakeValue(formalparams, body) : LambdaFunctionParseTreeNode::MakeValue(mInput.LocationString(), formalparams, body);
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::ParseStructure()
{
#ifdef TRACE
    TraceBlock trace("ParseStructure");
#endif

    consume(tknStructureRW);
    
    std::shared_ptr< StructureTypeParseTreeNode > node(
        mSuppressLocationInformation ? StructureTypeParseTreeNode::MakeValue() : StructureTypeParseTreeNode::MakeValue(mInput.LocationString())
    );
    
    while(!doesMatch(tknEndRW))
    {
        consume(tknDeclareRW);
        std::shared_ptr< iParseTreeNode > type(ParseType());
        consume(tknAsRW);
        match(tknIdentifier, "ParseStructure");
        const std::string id(mTokenizer.This().Identifier.Id);
        consume();
        
        consume(tknSemiColon);
        
        node->Add(id, type);
    }
    
    consume(tknEndRW);
    
    return node;
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::ParseType()
{
#ifdef TRACE
    TraceBlock trace("ParseType");
#endif

    switch(mTokenizer.This().Type)
    {
        case tknArrayRW:
        {
            return ParseArray();
        };
        
        case tknBooleanRW:
        {
            static std::shared_ptr< dish::iParseTreeNode > type(
                mSuppressLocationInformation ? BooleanTypeParseTreeNode::MakeValue() : BooleanTypeParseTreeNode::MakeValue(mInput.LocationString())
            );
            
            consume();
        
            return type;
        };
        
        case tknDictionaryRW:
        {
            static std::shared_ptr< dish::iParseTreeNode > type(
                mSuppressLocationInformation ? DictionaryTypeParseTreeNode::MakeValue() : DictionaryTypeParseTreeNode::MakeValue(mInput.LocationString())
            );
            
            consume();
        
            return type;
        };
        
        case tknFunctionRW:
        {
            return ParseFunction();
        };
        
        case tknIntegerRW:
        {
            consume();
            
            if(tknOpenParenthesis != mTokenizer.This().Type)
            {
                static std::shared_ptr< dish::iParseTreeNode > type(
                    mSuppressLocationInformation ? IntegerTypeParseTreeNode::MakeValue() : IntegerTypeParseTreeNode::MakeValue(mInput.LocationString())
                );
            
                return type;
            }
            else
            {
                consume();
                std::shared_ptr< dish::iParseTreeNode > minval(ParseExpression());
                
                consume(tknComma);
                std::shared_ptr< dish::iParseTreeNode > maxval(ParseExpression());
                
                std::shared_ptr< dish::iParseTreeNode > boundary;
                if(doesMatch(tknComma))
                {
                    consume();
                    boundary = ParseExpression();
                }
                else
                {
                    const IntegerT bound(static_cast< IntegerT >(iAtomic::rngbndError));
                    boundary = mSuppressLocationInformation ? LiteralParseTreeNode::MakeValue(bound) : LiteralParseTreeNode::MakeValue(mInput.LocationString(), bound);
                }
                assert(0 != boundary.get());
                
                consume(tknCloseParenthesis);
                
                return mSuppressLocationInformation ? RangedIntegerTypeParseTreeNode::MakeValue(minval, maxval, boundary) : RangedIntegerTypeParseTreeNode::MakeValue(mInput.LocationString(), minval, maxval, boundary);
            }
        };
          
        case tknRealRW:
        {
            static std::shared_ptr< dish::iParseTreeNode > type(
                mSuppressLocationInformation ? RealTypeParseTreeNode::MakeValue() : RealTypeParseTreeNode::MakeValue(mInput.LocationString())
            );
            
            consume();
        
            return type;
        };
        
        case tknStringRW:
        {
            static std::shared_ptr< dish::iParseTreeNode > type(
                mSuppressLocationInformation ? StringTypeParseTreeNode::MakeValue() : StringTypeParseTreeNode::MakeValue(mInput.LocationString())
            );
            
            consume();
        
            return type;
        };
        
        case tknStructureRW:
        {
            return ParseStructure();
        };
        
        case tknIdentifier:
        {
            return ParseTerminal();
        };
        
        default:
        {
            //  Empty
        }
        
    }
    
    std::stringstream message;
    message << "Syntax error: Unexpected '";
    Print(mTokenizer.This().Type, message);
    message << "' located in a type declaration.";
    
    throw SyntaxErrorException(mInput.LocationString(), message.str());
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::ParseReferece()
{
#ifdef TRACE
    TraceBlock trace("ParseReferece");
#endif

    consume(tknReferenceRW);

    match(tknIdentifier);
    const std::string id(mTokenizer.This().Identifier.Id);
    consume();
        
    if(doesMatch(tknAssignmentOp))
    {
        consume();
        
        std::shared_ptr< iParseTreeNode > lhs(ParseExpression());
    
        return mSuppressLocationInformation ? DeclareReferenceParseTreeNode::MakeValue(id, lhs) : DeclareReferenceParseTreeNode::MakeValue(mInput.LocationString(), id, lhs);
    }
    
    std::stringstream message;
    message << "Expecting an ID but found a ";
    Print(mTokenizer.This().Type, message);
    message << ". All references must be bound at declaration.";
    
    throw SyntaxErrorException(mInput.LocationString(), message.str()); 
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::ParseDeclaration()
{
#ifdef TRACE
    TraceBlock trace("ParseDeclaration");
#endif

    consume(tknDeclareRW);
    
    switch(mTokenizer.This().Type)
    {
        case tknFunctionRW:
        {
            return ParseFunction();
        };
        
        case tknReferenceRW:
        {
            std::shared_ptr< iParseTreeNode > node(ParseReferece());
            consume(tknSemiColon);
            
            return node;
        };
        
        case tknTypeRW:
        {
            consume();
        
            std::shared_ptr< iParseTreeNode > type(ParseType());
            
            consume(tknAsRW);
            
            match(tknIdentifier);
            const std::string id(mTokenizer.This().Identifier.Id);
            consume();
            
            std::shared_ptr< iParseTreeNode > node(mSuppressLocationInformation ? DeclareTypeParseTreeNode::MakeValue(type, id) : DeclareTypeParseTreeNode::MakeValue(mInput.LocationString(), type, id));
            consume(tknSemiColon);
            
            return node;
        };
        
        default:
        {
            std::shared_ptr< iParseTreeNode > type(ParseType());
            
            consume(tknAsRW);
            
            match(tknIdentifier);
            const std::string id(mTokenizer.This().Identifier.Id);
            consume();
            
            std::shared_ptr< iParseTreeNode > node(
                mSuppressLocationInformation ? DeclareParseTreeNode::MakeValue(type, id) : DeclareParseTreeNode::MakeValue(mInput.LocationString(), type, id)
            );
            node = matchInList(mDeclarationList, node);
            
            if(doesMatch(tknAssignmentOp))
            {
                consume();
                
                std::shared_ptr< iParseTreeNode > lhs(ParseExpression());
                
                node = mSuppressLocationInformation ? AssignmentParseTreeNode::MakeValue(node, lhs) : AssignmentParseTreeNode::MakeValue(mInput.LocationString(), node, lhs);
            }
            
            consume(tknSemiColon);
            
            return node;
        }
         
    }
    
    assert(false);
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::ParseLock()
{
#ifdef TRACE
    TraceBlock trace("ParseLock");
#endif

    consume(tknLockRW);

    if(doesMatch(tknIdentifier))
    {
        const std::string id(mTokenizer.This().Identifier.Id);
        consume();
        
        return mSuppressLocationInformation ? LockParseTreeNode::MakeValue(id) : LockParseTreeNode::MakeValue(mInput.LocationString(), id);
    }
    
    std::stringstream message;
    message << "Syntax error: Cannot lock a '";
    Print(mTokenizer.This().Type, message);
    message << "'.";
    
    throw SyntaxErrorException(mInput.LocationString(), message.str());
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::ParseStatementBlock()
{
#ifdef TRACE
    TraceBlock trace("ParseStatementBlock");
#endif

    consume(tknBeginRW);
    
    std::shared_ptr< StatementBlockParseTreeNode > block(
        mSuppressLocationInformation ? StatementBlockParseTreeNode::MakeValue() : StatementBlockParseTreeNode::MakeValue(mInput.LocationString())
    );
    
    while(!doesMatch(tknEndRW))
    {
        std::shared_ptr< dish::iParseTreeNode > stmt(ParseStatement());
        block->Add(stmt);
    }

    consume(tknEndRW);
    
    return block;
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::ParseIfThenElse()
{
#ifdef TRACE
    TraceBlock trace("ParseIfThenElse");
#endif

    consume(tknIfRW);
    std::shared_ptr< dish::iParseTreeNode > cond(ParseExpression());
    consume(tknThenRW);
    
    std::shared_ptr< dish::iParseTreeNode > ifblk(ParseStatement());
    
    if(doesMatch(tknElseRW))
    {
        consume();
        
        std::shared_ptr< dish::iParseTreeNode > elseblk(ParseStatement());
    
        return mSuppressLocationInformation ? IfStatementParseTreeNode::MakeValue(cond, ifblk, elseblk) : IfStatementParseTreeNode::MakeValue(mInput.LocationString(), cond, ifblk, elseblk);
    }
    
    return mSuppressLocationInformation ? IfStatementParseTreeNode::MakeValue(cond, ifblk) : IfStatementParseTreeNode::MakeValue(mInput.LocationString(), cond, ifblk);
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::ParseSwitch()
{
#ifdef TRACE
    TraceBlock trace("ParseSwitch");
#endif

    consume(tknSwitchRW);
    std::shared_ptr< iParseTreeNode > expr(ParseExpression());
    
    std::shared_ptr< SwitchStatementParseTreeNode > switch_statement(
        mSuppressLocationInformation ? SwitchStatementParseTreeNode::MakeValue(expr) : SwitchStatementParseTreeNode::MakeValue(mInput.LocationString(), expr)
    );
    
    for(bool done(false); !done; )
    {
        switch(mTokenizer.This().Type)
        {
            case tknEndRW:
            {
                consume();
                done = true;
            } break;
            
            case tknOtherwiseRW:
            {
                consume();
                consume(tknColon);
                
                std::shared_ptr< iParseTreeNode > stmt(ParseStatement());
                switch_statement->AddOtherwise(stmt);
            } break;
        
            default:
            {
                std::vector< std::shared_ptr< iParseTreeNode > > values;
            
                for(bool done(false); !done; )
                {
                    values.push_back(ParseExpression());
                    
                    if(doesMatch(tknComma))
                    {
                        consume();
                    }
                    else
                    {
                        done = true;
                    }
                }
                
                consume(tknColon);
                std::shared_ptr< dish::iParseTreeNode > body(ParseStatement());
                
                std::for_each(
                    values.begin(), values.end(),
                    [&](std::shared_ptr< iParseTreeNode > value)
                    {
                        switch_statement->AddCase(value, body);
                    }
                );
            }
            
        }
    }

    return switch_statement;
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::ParseForLoop()
{
#ifdef TRACE
    TraceBlock trace("ParseForLoop");
#endif

    consume(tknForRW);
    std::shared_ptr< dish::iParseTreeNode > id(ParseTerminal());
    consume(tknAssignmentOp);
    std::shared_ptr< dish::iParseTreeNode > from(ParseExpression());
    consume(tknToRW);
    std::shared_ptr< dish::iParseTreeNode > to(ParseExpression());
    
    if(doesMatch(tknStepRW))
    {
        consume();
        std::shared_ptr< dish::iParseTreeNode > step(ParseExpression());
        std::shared_ptr< dish::iParseTreeNode > body(ParseStatement());
        
        return mSuppressLocationInformation ? 
            ForLoopParseTreeNode::MakeValue(id, from, to, step, body) : 
            ForLoopParseTreeNode::MakeValue(mInput.LocationString(), id, from, to, step, body);
    }
    else
    {
        std::shared_ptr< dish::iParseTreeNode > body(ParseStatement());
    
        return mSuppressLocationInformation ? 
            ForLoopParseTreeNode::MakeValue(id, from, to, body) : 
            ForLoopParseTreeNode::MakeValue(mInput.LocationString(), id, from, to, body);
    }
    
    assert(false);
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::ParseForEachLoop()
{
#ifdef TRACE
    TraceBlock trace("ParseForEachLoop");
#endif

    consume(tknForEachRW);
    
    bool reference(false);
    if(doesMatch(tknAmpersand))
    {
        reference = true;
        consume();
    }
    
    match(tknIdentifier);
    const std::string id(mTokenizer.This().Identifier.Id);
    consume();
    
    consume(tknInRW);
    
    std::shared_ptr< dish::iParseTreeNode > collection(ParseTerminal());
    
    std::shared_ptr< dish::iParseTreeNode > body(ParseStatement());
    
    return mSuppressLocationInformation ? 
        ForEachLoopParseTreeNode::MakeValue(reference, id, collection, body) : 
        ForEachLoopParseTreeNode::MakeValue(mInput.LocationString(), reference, id, collection, body);
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::ParseWhileLoop()
{
#ifdef TRACE
    TraceBlock trace("ParseWhileLoop");
#endif

    consume(tknWhileRW);
    std::shared_ptr< dish::iParseTreeNode > condition(ParseExpression());
    consume(tknDoRW);
    
    std::shared_ptr< dish::iParseTreeNode > body(ParseStatement());
    
    return mSuppressLocationInformation ? 
        WhileLoopParseTreeNode::MakeValue(condition, body) : 
        WhileLoopParseTreeNode::MakeValue(mInput.LocationString(), condition, body);
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::ParseRepeatLoop()
{
#ifdef TRACE
    TraceBlock trace("ParseRepeatLoop");
#endif

    consume(tknRepeatRW);
    
    RepeatUntilLoopParseTreeNode::BodyT body;
    while(!doesMatch(tknUntilRW))
    {
        body.push_back(ParseStatement());
    }
    consume();
    
    std::shared_ptr< dish::iParseTreeNode > condition(ParseExpression());
    
    return mSuppressLocationInformation ? 
        RepeatUntilLoopParseTreeNode::MakeValue(body, condition) : 
        RepeatUntilLoopParseTreeNode::MakeValue(mInput.LocationString(), body, condition);
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::ParseReturn()
{
#ifdef TRACE
    TraceBlock trace("ParseReturn");
#endif

    consume(tknReturnRW);
    
    std::shared_ptr< dish::iParseTreeNode > retval(ParseExpression());
    
    return mSuppressLocationInformation ? ReturnParseTreeNode::MakeValue(retval) : ReturnParseTreeNode::MakeValue(mInput.LocationString(), retval);
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::ParseImport()
{
#ifdef TRACE
    TraceBlock trace("ParseImport");
#endif

    consume(tknImportRW);
    
    match(tknStringLit);
    const std::string fname(mTokenizer.This().StringLit.Value);
    consume();
    
    match(tknSemiColon);    //  Needed here to complete the statement but cannot 
                            //  be done in ParseStatement() because we will push
                            //  a new input stream onto the stack next.
    //mInput.PushFile(fname);
    mInput.PushFile(DishCommandLine::Instance().InputFileName(fname));
    consume();              //  Consume the semicolon token after we push the imported file onto the input stack.
    
    dish::Log::Instance().Writeln(dish::Log::logInfo, std::string("Importing ") + fname + "...");
    
    return mSuppressLocationInformation ? NullParseTreeNode::MakeValue() : NullParseTreeNode::MakeValue(mInput.LocationString());
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::ParseAssert()
{
#ifdef TRACE
    TraceBlock trace("ParseAssert");
#endif

    consume(tknAssertRW);
    consume(tknOpenParenthesis);
    
    std::shared_ptr< dish::iParseTreeNode > condition(ParseExpression());
    
    consume(tknCloseParenthesis);
    
    return mSuppressLocationInformation ? AssertParseTreeNode::MakeValue(condition) : AssertParseTreeNode::MakeValue(mInput.LocationString(), condition);
}

std::shared_ptr< dish::iParseTreeNode > dish::Parser::ParseStatement()
{
#ifdef TRACE
    TraceBlock trace("ParseStatement");
#endif

    std::shared_ptr< dish::iParseTreeNode > node;

    switch(mTokenizer.This().Type)
    {
        case tknSemiColon:
        {
            node = mSuppressLocationInformation ? NullParseTreeNode::MakeValue() : NullParseTreeNode::MakeValue(mInput.LocationString());
            consume(tknSemiColon);
        } break;
    
        case tknAssertRW:
        {
            node = ParseAssert();
            consume(tknSemiColon);
        } break;
    
        case tknBeginRW:
        {
            node = ParseStatementBlock();
            consume(tknSemiColon);
        } break;
        
        case tknDeclareRW:
        {
            node = ParseDeclaration();
            //  We do not consume the semicolon token here because it was
            //  already done when parsing the declaration statement.
        } break;
        
        case tknForRW:
        {
            node = ParseForLoop();
            //  We do not consume the semicolon token here because it was
            //  already done when parsing the for-loop.
        } break;
        
        case tknForEachRW:
        {
            node = ParseForEachLoop();
            //  We do not consume the semicolon token here because it was
            //  already done when parsing the for-loop.
        } break;
        
        case tknIfRW:
        {
            node = ParseIfThenElse();
            //  We do not consume the semicolon token here because it was
            //  already done when parsing the if-then-else statement.
        } break;
        
        case tknImportRW:
        {
            node = ParseImport();
            //  We do not consume the semicolon token here because it was
            //  already done when parsing the import statement.
        } break;
        
        case tknLockRW:
        {
            node = ParseLock();
            consume(tknSemiColon);
        } break;
        
        case tknRepeatRW:
        {
            node = ParseRepeatLoop();
            consume(tknSemiColon);
        } break;
        
        case tknReturnRW:
        {
            node = ParseReturn();
            consume(tknSemiColon);
        } break;
        
        case tknSwitchRW:
        {
            node = ParseSwitch();
            consume(tknSemiColon);
        } break;
        
        case tknWhileRW:
        {
            node = ParseWhileLoop();
            //  We do not consume the semicolon token here because it was
            //  already done when parsing the while-loop.
        } break;
    
        default:
        {
            node = ParseExpression();
            consume(tknSemiColon);
        }
        
    }
    
    assert(node);
    return node;
}

std::shared_ptr< dish::iAtomic > dish::Parser::Run()
{
    std::shared_ptr< iAtomic > ret = NullValue::MakeValue();   
    
    while(!mInput.Empty())
    {
        std::shared_ptr< iParseTreeNode > statement(ParseStatement());

        try
        {
            ret = statement->Execute(SymbolTable());
        }
        
        catch(dish::ReturnParseTreeNode::ReturnValueT e)
        {
            return e;
        }
        
        catch(IllegalCastException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_IllegalCast,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(ValueLockedException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_ValueLocked,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(NoSuchMemberException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_NoSuchMember,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(DuplicateSymbolException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_DuplicateSymbol,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(NoSuchSymbolException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_NoSuchSymbol,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(DivideByZeroException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_DivideByZero,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(DomainErrorException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_DomainError,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(RangeErrorException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_RangeError,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(IllegalHandleException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_IllegalHandle,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(IllegalValueException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_IllegalValue,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
    
#ifdef LANG_LIB_FILEIO
    
        catch(TooManyOpenFilesException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_TooManyOpenFiles,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(UnableToOpenFileException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_UnableToOpenFile,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(FileNotOpenException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_FileNotOpen,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(FileWriteErrorException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_FileWriteError,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(FileReadErrorException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_FileReadError,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
    
#endif

#ifdef LANG_LIB_NETWORK

        catch(TooManyOpenSocketsException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_TooManyOpenSockets,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(UnableToOpenSocketException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_UnableToOpenSocket,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(UnableToCloseSocketException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_UnableToCloseSocket,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(SocketInvalidAddressException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_NetworkInvalidAddress,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(SocketUnableToConnectToServerException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_NetworkUnableToConnectToServer,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(SocketNotOpenException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_NetworkSocketNotOpen,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(SocketWriteErrorException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_NetworkSocketWriteError,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(SocketReadErrorException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_NetworkSocketReadError,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
    
#endif

#ifdef LANG_LIB_MATH_MATRIX
    
        catch(MatrixNotValidException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_MatrixInvalidError,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(MatrixNotSquareException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_MatrixNotSquareError,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(ZeroDeterminantException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_ZeroDeterminantError,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(MatrixDimensionErrorException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_MatrixDimensionError,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(StackOverflowException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_StackOverflowError,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
    
#endif
    
#ifdef LANG_LIB_DATABASE
    
        catch(DatabaseInternalErrorException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_DB_InternalError,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(DatabaseInvalidConnectionTypeException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_DB_InvalidConnectionType,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(DatabaseInvalidHandleException &e)
        {
            ret = NullValue::MakeValue();
        
            //  Invoke the generic illegal-handle callback for an illegal
            //  database handle.
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_IllegalHandle,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(DatabaseTooManyOpenConnectionsException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_DB_TooManyOpenConnections,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(DatabaseUnableToOpenConnectionException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_DB_UnableToOpenConnection,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(DatabaseConnectionNotOpenException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_DB_ConnectionNotOpen,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(DatabaseConnectionDroppedException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_DB_ConnectionDropped,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(DatabaseQueryErrorException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_DB_QueryError,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(DatabaseUnknownException &e)
        {
            ret = NullValue::MakeValue();
        
            //  Invoke the internal-error handler for an unknown database error.
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_DB_InternalError,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
    
#endif

#ifdef LANG_LIB_RS232
    
        catch(Rs232BadConfigurationException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_RS232_ConfigurationNotSupported,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(Rs232UnableToOpenPortException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_RS232_UnableToOpenPort,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(Rs232PortNotOpenException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_RS232_PortNotOpen,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(Rs232WriteFailureException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_RS232_WriteFailure,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
        
        catch(Rs232ReadFailureException &e)
        {
            ret = NullValue::MakeValue();
        
            ErrorCallbacks::Instance().Invoke(
                ErrorCallbacks::ERR_RS232_ReadFailure,
                ErrorCallbacks::CallbackArg(statement->LocationString(), e.what()),
                SymbolTable()
            );
        }
    
#endif
    }
    
    return ret;
}

void dish::Parser::Validate()
{
    while(!mInput.Empty())
    {
        ParseStatement()->Validate(SymbolTable());
    }
}

void dish::Parser::PrintParseTree(std::ostream &out)
{
    while(!mInput.Empty())
    {
        out << "Statement: ";
        ParseStatement()->Print(out);
        out << std::endl;
        out << std::endl;
    }
}

std::string dish::Parser::LocationString() const
{
    std::stringstream output;
    
    output << Source();
    output << ", line ";
    output << Line();
    output << ", column ";
    output << Column();
    
    return output.str();
}

void dish::Parser::PrintRemainder(std::ostream &out)
{
    while(!mInput.Empty())
    {
        dish::Print(mTokenizer.This(), out);
        mTokenizer.Next();
        out << std::endl;
    }
}

dish::IntegerT dish::Parser::ReleaseCachedParseTreeNodes()
{
    IntegerT nodecount(0);

    nodecount += NumCachedExpressions();
    mExpressionList.clear();
#ifdef LIST_TYPE_PREFER_VECTOR
    mExpressionList.reserve(LIST_TYPE_PREFER_VECTOR);
#endif
    
    nodecount += NumCachedDeclarations();
    mDeclarationList.clear();
#ifdef LIST_TYPE_PREFER_VECTOR
    mDeclarationList.reserve(LIST_TYPE_PREFER_VECTOR);
#endif

    return nodecount;
}

