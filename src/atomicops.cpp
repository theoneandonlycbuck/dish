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

#include <cassert>
#include <sstream>

#include "atomics.h"
#include "exception.h"

namespace
{
    
    std::shared_ptr< dish::iAtomic > NegOp_TypeNotSupportedF(const dish::iAtomic &arg)
    {
        std::stringstream message;
        message << "Illegal operation: -<";
        message << TypeToString(arg.Type());
        message << ">.";
        
        throw dish::IllegalOperationException(message.str());
    }
    
    std::shared_ptr< dish::iAtomic > NegOp_IntegerF(const dish::iAtomic &arg)
    {
        return dish::IntegerValue::MakeValue(-arg.AsInteger());
    }
    
    std::shared_ptr< dish::iAtomic > NegOp_RealF(const dish::iAtomic &arg)
    {
        dish::ScopedCheckForError checkforerror;
    
        return dish::RealValue::MakeValue(-arg.AsReal());
    }
    
}
    
const dish::OneArgOpF dish::OpNeg_FuncTable[dish::iAtomic::typeNUM] = 
{
    NegOp_TypeNotSupportedF,        //  typeNull
    NegOp_TypeNotSupportedF,        //  typeType
    NegOp_IntegerF,                 //  typeBoolean
    NegOp_IntegerF,                 //  typeInteger
    NegOp_RealF,                    //  typeReal
    NegOp_TypeNotSupportedF,        //  typeString
    NegOp_TypeNotSupportedF,        //  typeArray
    NegOp_TypeNotSupportedF,        //  typeDictionary
    NegOp_TypeNotSupportedF,        //  typeStructure
    NegOp_TypeNotSupportedF         //  typeExecutable
};

////////////////////////////////////////////////////////////////////////////////

namespace
{
    
    std::shared_ptr< dish::iAtomic > OpAdd_TypeNotSupportedF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        std::stringstream message;
        message << "Illegal operation: <";
        message << TypeToString(arg1.Type());
        message << "> + <";
        message << TypeToString(arg2.Type());
        message << ">.";
                
        throw dish::IllegalOperationException(message.str());
    }
    
    std::shared_ptr< dish::iAtomic > OpAdd_IntegerIntegerF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        return dish::IntegerValue::MakeValue(arg1.AsInteger() + arg2.AsInteger());
    }
    
    std::shared_ptr< dish::iAtomic > OpAdd_RealRealF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        dish::ScopedCheckForError checkforerror;
                
        return dish::RealValue::MakeValue(arg1.AsReal() + arg2.AsReal());
    }
    
    std::shared_ptr< dish::iAtomic > OpAdd_StringStringF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        return dish::StringValue::MakeValue(arg1.AsString() + arg2.AsString());
    }

}
    
const dish::TwoArgOpF dish::OpAdd_FuncTable[dish::iAtomic::typeNUM][dish::iAtomic::typeNUM] =
{
    //  typeNull
    {
        OpAdd_TypeNotSupportedF,            //  typeNull
        OpAdd_TypeNotSupportedF,            //  typeType
        OpAdd_TypeNotSupportedF,            //  typeBoolean
        OpAdd_TypeNotSupportedF,            //  typeInteger
        OpAdd_TypeNotSupportedF,            //  typeReal
        OpAdd_TypeNotSupportedF,            //  typeString
        OpAdd_TypeNotSupportedF,            //  typeArray
        OpAdd_TypeNotSupportedF,            //  typeDictionary
        OpAdd_TypeNotSupportedF,            //  typeStructure
        OpAdd_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeType
    {
        OpAdd_TypeNotSupportedF,            //  typeNull
        OpAdd_TypeNotSupportedF,            //  typeType
        OpAdd_TypeNotSupportedF,            //  typeBoolean
        OpAdd_TypeNotSupportedF,            //  typeInteger
        OpAdd_TypeNotSupportedF,            //  typeReal
        OpAdd_TypeNotSupportedF,            //  typeString
        OpAdd_TypeNotSupportedF,            //  typeArray
        OpAdd_TypeNotSupportedF,            //  typeDictionary
        OpAdd_TypeNotSupportedF,            //  typeStructure
        OpAdd_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeBoolean
    {
        OpAdd_TypeNotSupportedF,            //  typeNull
        OpAdd_TypeNotSupportedF,            //  typeType
        OpAdd_IntegerIntegerF,              //  typeBoolean
        OpAdd_IntegerIntegerF,              //  typeInteger
        OpAdd_RealRealF,                    //  typeReal
        OpAdd_StringStringF,                //  typeString
        OpAdd_TypeNotSupportedF,            //  typeArray
        OpAdd_TypeNotSupportedF,            //  typeDictionary
        OpAdd_TypeNotSupportedF,            //  typeStructure
        OpAdd_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeInteger
    {
        OpAdd_TypeNotSupportedF,            //  typeNull
        OpAdd_TypeNotSupportedF,            //  typeType
        OpAdd_IntegerIntegerF,              //  typeBoolean
        OpAdd_IntegerIntegerF,              //  typeInteger
        OpAdd_RealRealF,                    //  typeReal
        OpAdd_StringStringF,                //  typeString
        OpAdd_TypeNotSupportedF,            //  typeArray
        OpAdd_TypeNotSupportedF,            //  typeDictionary
        OpAdd_TypeNotSupportedF,            //  typeStructure
        OpAdd_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeReal
    {
        OpAdd_TypeNotSupportedF,            //  typeNull
        OpAdd_TypeNotSupportedF,            //  typeType
        OpAdd_TypeNotSupportedF,            //  typeBoolean
        OpAdd_RealRealF,                    //  typeInteger
        OpAdd_RealRealF,                    //  typeReal
        OpAdd_StringStringF,                //  typeString
        OpAdd_TypeNotSupportedF,            //  typeArray
        OpAdd_TypeNotSupportedF,            //  typeDictionary
        OpAdd_TypeNotSupportedF,            //  typeStructure
        OpAdd_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeString
    {
        OpAdd_TypeNotSupportedF,            //  typeNull
        OpAdd_TypeNotSupportedF,            //  typeType
        OpAdd_StringStringF,                //  typeBoolean
        OpAdd_StringStringF,                //  typeInteger
        OpAdd_StringStringF,                //  typeReal
        OpAdd_StringStringF,                //  typeString
        OpAdd_TypeNotSupportedF,            //  typeArray
        OpAdd_TypeNotSupportedF,            //  typeDictionary
        OpAdd_TypeNotSupportedF,            //  typeStructure
        OpAdd_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeArray
    {
        OpAdd_TypeNotSupportedF,            //  typeNull
        OpAdd_TypeNotSupportedF,            //  typeType
        OpAdd_TypeNotSupportedF,            //  typeBoolean
        OpAdd_TypeNotSupportedF,            //  typeInteger
        OpAdd_TypeNotSupportedF,            //  typeReal
        OpAdd_TypeNotSupportedF,            //  typeString
        OpAdd_TypeNotSupportedF,            //  typeArray
        OpAdd_TypeNotSupportedF,            //  typeDictionary
        OpAdd_TypeNotSupportedF,            //  typeStructure
        OpAdd_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeDictionary
    {
        OpAdd_TypeNotSupportedF,            //  typeNull
        OpAdd_TypeNotSupportedF,            //  typeType
        OpAdd_TypeNotSupportedF,            //  typeBoolean
        OpAdd_TypeNotSupportedF,            //  typeInteger
        OpAdd_TypeNotSupportedF,            //  typeReal
        OpAdd_TypeNotSupportedF,            //  typeString
        OpAdd_TypeNotSupportedF,            //  typeArray
        OpAdd_TypeNotSupportedF,            //  typeDictionary
        OpAdd_TypeNotSupportedF,            //  typeStructure
        OpAdd_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeStructure
    {
        OpAdd_TypeNotSupportedF,            //  typeNull
        OpAdd_TypeNotSupportedF,            //  typeType
        OpAdd_TypeNotSupportedF,            //  typeBoolean
        OpAdd_TypeNotSupportedF,            //  typeInteger
        OpAdd_TypeNotSupportedF,            //  typeReal
        OpAdd_TypeNotSupportedF,            //  typeString
        OpAdd_TypeNotSupportedF,            //  typeArray
        OpAdd_TypeNotSupportedF,            //  typeDictionary
        OpAdd_TypeNotSupportedF,            //  typeStructure
        OpAdd_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeExecutable
    {
        OpAdd_TypeNotSupportedF,            //  typeNull
        OpAdd_TypeNotSupportedF,            //  typeType
        OpAdd_TypeNotSupportedF,            //  typeBoolean
        OpAdd_TypeNotSupportedF,            //  typeInteger
        OpAdd_TypeNotSupportedF,            //  typeReal
        OpAdd_TypeNotSupportedF,            //  typeString
        OpAdd_TypeNotSupportedF,            //  typeArray
        OpAdd_TypeNotSupportedF,            //  typeDictionary
        OpAdd_TypeNotSupportedF,            //  typeStructure
        OpAdd_TypeNotSupportedF             //  typeExecutable
    }
};

////////////////////////////////////////////////////////////////////////////////

namespace
{
    
    std::shared_ptr< dish::iAtomic > OpSub_TypeNotSupportedF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        std::stringstream message;
        message << "Illegal operation: <";
        message << TypeToString(arg1.Type());
        message << "> - <";
        message << TypeToString(arg2.Type());
        message << ">.";
                
        throw dish::IllegalOperationException(message.str());
    }
    
    std::shared_ptr< dish::iAtomic > OpSub_IntegerIntegerF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        return dish::IntegerValue::MakeValue(arg1.AsInteger() - arg2.AsInteger());
    }
    
    std::shared_ptr< dish::iAtomic > OpSub_RealRealF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        dish::ScopedCheckForError checkforerror;
    
        return dish::RealValue::MakeValue(arg1.AsReal() - arg2.AsReal());
    }

}
    
const dish::TwoArgOpF dish::OpSub_FuncTable[dish::iAtomic::typeNUM][dish::iAtomic::typeNUM] =
{
    //  typeNull
    {
        OpSub_TypeNotSupportedF,            //  typeNull
        OpSub_TypeNotSupportedF,            //  typeType
        OpSub_TypeNotSupportedF,            //  typeBoolean
        OpSub_TypeNotSupportedF,            //  typeInteger
        OpSub_TypeNotSupportedF,            //  typeReal
        OpSub_TypeNotSupportedF,            //  typeString
        OpSub_TypeNotSupportedF,            //  typeArray
        OpSub_TypeNotSupportedF,            //  typeDictionary
        OpSub_TypeNotSupportedF,            //  typeStructure
        OpSub_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeType
    {
        OpSub_TypeNotSupportedF,            //  typeNull
        OpSub_TypeNotSupportedF,            //  typeType
        OpSub_TypeNotSupportedF,            //  typeBoolean
        OpSub_TypeNotSupportedF,            //  typeInteger
        OpSub_TypeNotSupportedF,            //  typeReal
        OpSub_TypeNotSupportedF,            //  typeString
        OpSub_TypeNotSupportedF,            //  typeArray
        OpSub_TypeNotSupportedF,            //  typeDictionary
        OpSub_TypeNotSupportedF,            //  typeStructure
        OpSub_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeBoolean
    {
        OpSub_TypeNotSupportedF,            //  typeNull
        OpSub_TypeNotSupportedF,            //  typeType
        OpSub_IntegerIntegerF,              //  typeBoolean
        OpSub_IntegerIntegerF,              //  typeInteger
        OpSub_RealRealF,                    //  typeReal
        OpSub_IntegerIntegerF,              //  typeString
        OpSub_TypeNotSupportedF,            //  typeArray
        OpSub_TypeNotSupportedF,            //  typeDictionary
        OpSub_TypeNotSupportedF,            //  typeStructure
        OpSub_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeInteger
    {
        OpSub_TypeNotSupportedF,            //  typeNull
        OpSub_TypeNotSupportedF,            //  typeType
        OpSub_IntegerIntegerF,              //  typeBoolean
        OpSub_IntegerIntegerF,              //  typeInteger
        OpSub_RealRealF,                    //  typeReal
        OpSub_IntegerIntegerF,              //  typeString
        OpSub_TypeNotSupportedF,            //  typeArray
        OpSub_TypeNotSupportedF,            //  typeDictionary
        OpSub_TypeNotSupportedF,            //  typeStructure
        OpSub_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeReal
    {
        OpSub_TypeNotSupportedF,            //  typeNull
        OpSub_TypeNotSupportedF,            //  typeType
        OpSub_RealRealF,                    //  typeBoolean
        OpSub_RealRealF,                    //  typeInteger
        OpSub_RealRealF,                    //  typeReal
        OpSub_RealRealF,                    //  typeString
        OpSub_TypeNotSupportedF,            //  typeArray
        OpSub_TypeNotSupportedF,            //  typeDictionary
        OpSub_TypeNotSupportedF,            //  typeStructure
        OpSub_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeString
    {
        OpSub_TypeNotSupportedF,            //  typeNull
        OpSub_TypeNotSupportedF,            //  typeType
        OpSub_IntegerIntegerF,              //  typeBoolean
        OpSub_IntegerIntegerF,              //  typeInteger
        OpSub_RealRealF,                    //  typeReal
        OpSub_TypeNotSupportedF,            //  typeString
        OpSub_TypeNotSupportedF,            //  typeArray
        OpSub_TypeNotSupportedF,            //  typeDictionary
        OpSub_TypeNotSupportedF,            //  typeStructure
        OpSub_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeArray
    {
        OpSub_TypeNotSupportedF,            //  typeNull
        OpSub_TypeNotSupportedF,            //  typeType
        OpSub_TypeNotSupportedF,            //  typeBoolean
        OpSub_TypeNotSupportedF,            //  typeInteger
        OpSub_TypeNotSupportedF,            //  typeReal
        OpSub_TypeNotSupportedF,            //  typeString
        OpSub_TypeNotSupportedF,            //  typeArray
        OpSub_TypeNotSupportedF,            //  typeDictionary
        OpSub_TypeNotSupportedF,            //  typeStructure
        OpSub_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeDictionary
    {
        OpSub_TypeNotSupportedF,            //  typeNull
        OpSub_TypeNotSupportedF,            //  typeType
        OpSub_TypeNotSupportedF,            //  typeBoolean
        OpSub_TypeNotSupportedF,            //  typeInteger
        OpSub_TypeNotSupportedF,            //  typeReal
        OpSub_TypeNotSupportedF,            //  typeString
        OpSub_TypeNotSupportedF,            //  typeArray
        OpSub_TypeNotSupportedF,            //  typeDictionary
        OpSub_TypeNotSupportedF,            //  typeStructure
        OpSub_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeStructure
    {
        OpSub_TypeNotSupportedF,            //  typeNull
        OpSub_TypeNotSupportedF,            //  typeType
        OpSub_TypeNotSupportedF,            //  typeBoolean
        OpSub_TypeNotSupportedF,            //  typeInteger
        OpSub_TypeNotSupportedF,            //  typeReal
        OpSub_TypeNotSupportedF,            //  typeString
        OpSub_TypeNotSupportedF,            //  typeArray
        OpSub_TypeNotSupportedF,            //  typeDictionary
        OpSub_TypeNotSupportedF,            //  typeStructure
        OpSub_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeExecutable
    {
        OpSub_TypeNotSupportedF,            //  typeNull
        OpSub_TypeNotSupportedF,            //  typeType
        OpSub_TypeNotSupportedF,            //  typeBoolean
        OpSub_TypeNotSupportedF,            //  typeInteger
        OpSub_TypeNotSupportedF,            //  typeReal
        OpSub_TypeNotSupportedF,            //  typeString
        OpSub_TypeNotSupportedF,            //  typeArray
        OpSub_TypeNotSupportedF,            //  typeDictionary
        OpSub_TypeNotSupportedF,            //  typeStructure
        OpSub_TypeNotSupportedF             //  typeExecutable
    }
};

////////////////////////////////////////////////////////////////////////////////

namespace
{
    
    std::shared_ptr< dish::iAtomic > OpMul_TypeNotSupportedF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        std::stringstream message;
        message << "Illegal operation: <";
        message << TypeToString(arg1.Type());
        message << "> * <";
        message << TypeToString(arg2.Type());
        message << ">.";
                
        throw dish::IllegalOperationException(message.str());
    }
    
    std::shared_ptr< dish::iAtomic > OpMul_IntegerIntegerF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        return dish::IntegerValue::MakeValue(arg1.AsInteger() * arg2.AsInteger());
    }
    
    std::shared_ptr< dish::iAtomic > OpMul_RealRealF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        dish::ScopedCheckForError checkforerror;
    
        return dish::RealValue::MakeValue(arg1.AsReal() * arg2.AsReal());
    }

}
    
const dish::TwoArgOpF dish::OpMul_FuncTable[dish::iAtomic::typeNUM][dish::iAtomic::typeNUM] =
{
    //  typeNull
    {
        OpMul_TypeNotSupportedF,            //  typeNull
        OpMul_TypeNotSupportedF,            //  typeType
        OpMul_TypeNotSupportedF,            //  typeBoolean
        OpMul_TypeNotSupportedF,            //  typeInteger
        OpMul_TypeNotSupportedF,            //  typeReal
        OpMul_TypeNotSupportedF,            //  typeString
        OpMul_TypeNotSupportedF,            //  typeArray
        OpMul_TypeNotSupportedF,            //  typeDictionary
        OpMul_TypeNotSupportedF,            //  typeStructure
        OpMul_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeType
    {
        OpMul_TypeNotSupportedF,            //  typeNull
        OpMul_TypeNotSupportedF,            //  typeType
        OpMul_TypeNotSupportedF,            //  typeBoolean
        OpMul_TypeNotSupportedF,            //  typeInteger
        OpMul_TypeNotSupportedF,            //  typeReal
        OpMul_TypeNotSupportedF,            //  typeString
        OpMul_TypeNotSupportedF,            //  typeArray
        OpMul_TypeNotSupportedF,            //  typeDictionary
        OpMul_TypeNotSupportedF,            //  typeStructure
        OpMul_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeBoolean
    {
        OpMul_TypeNotSupportedF,            //  typeNull
        OpMul_TypeNotSupportedF,            //  typeType
        OpMul_IntegerIntegerF,              //  typeBoolean
        OpMul_IntegerIntegerF,              //  typeInteger
        OpMul_RealRealF,                    //  typeReal
        OpMul_IntegerIntegerF,              //  typeString
        OpMul_TypeNotSupportedF,            //  typeArray
        OpMul_TypeNotSupportedF,            //  typeDictionary
        OpMul_TypeNotSupportedF,            //  typeStructure
        OpMul_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeInteger
    {
        OpMul_TypeNotSupportedF,            //  typeNull
        OpMul_TypeNotSupportedF,            //  typeType
        OpMul_IntegerIntegerF,              //  typeBoolean
        OpMul_IntegerIntegerF,              //  typeInteger
        OpMul_RealRealF,                    //  typeReal
        OpMul_IntegerIntegerF,              //  typeString
        OpMul_TypeNotSupportedF,            //  typeArray
        OpMul_TypeNotSupportedF,            //  typeDictionary
        OpMul_TypeNotSupportedF,            //  typeStructure
        OpMul_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeReal
    {
        OpMul_TypeNotSupportedF,            //  typeNull
        OpMul_TypeNotSupportedF,            //  typeType
        OpMul_RealRealF,                    //  typeBoolean
        OpMul_RealRealF,                    //  typeInteger
        OpMul_RealRealF,                    //  typeReal
        OpMul_RealRealF,                    //  typeString
        OpMul_TypeNotSupportedF,            //  typeArray
        OpMul_TypeNotSupportedF,            //  typeDictionary
        OpMul_TypeNotSupportedF,            //  typeStructure
        OpMul_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeString
    {
        OpMul_TypeNotSupportedF,            //  typeNull
        OpMul_TypeNotSupportedF,            //  typeType
        OpMul_IntegerIntegerF,              //  typeBoolean
        OpMul_IntegerIntegerF,              //  typeInteger
        OpMul_RealRealF,                    //  typeReal
        OpMul_TypeNotSupportedF,            //  typeString
        OpMul_TypeNotSupportedF,            //  typeArray
        OpMul_TypeNotSupportedF,            //  typeDictionary
        OpMul_TypeNotSupportedF,            //  typeStructure
        OpMul_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeArray
    {
        OpMul_TypeNotSupportedF,            //  typeNull
        OpMul_TypeNotSupportedF,            //  typeType
        OpMul_TypeNotSupportedF,            //  typeBoolean
        OpMul_TypeNotSupportedF,            //  typeInteger
        OpMul_TypeNotSupportedF,            //  typeReal
        OpMul_TypeNotSupportedF,            //  typeString
        OpMul_TypeNotSupportedF,            //  typeArray
        OpMul_TypeNotSupportedF,            //  typeDictionary
        OpMul_TypeNotSupportedF,            //  typeStructure
        OpMul_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeDictionary
    {
        OpMul_TypeNotSupportedF,            //  typeNull
        OpMul_TypeNotSupportedF,            //  typeType
        OpMul_TypeNotSupportedF,            //  typeBoolean
        OpMul_TypeNotSupportedF,            //  typeInteger
        OpMul_TypeNotSupportedF,            //  typeReal
        OpMul_TypeNotSupportedF,            //  typeString
        OpMul_TypeNotSupportedF,            //  typeArray
        OpMul_TypeNotSupportedF,            //  typeDictionary
        OpMul_TypeNotSupportedF,            //  typeStructure
        OpMul_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeStructure
    {
        OpMul_TypeNotSupportedF,            //  typeNull
        OpMul_TypeNotSupportedF,            //  typeType
        OpMul_TypeNotSupportedF,            //  typeBoolean
        OpMul_TypeNotSupportedF,            //  typeInteger
        OpMul_TypeNotSupportedF,            //  typeReal
        OpMul_TypeNotSupportedF,            //  typeString
        OpMul_TypeNotSupportedF,            //  typeArray
        OpMul_TypeNotSupportedF,            //  typeDictionary
        OpMul_TypeNotSupportedF,            //  typeStructure
        OpMul_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeExecutable
    {
        OpMul_TypeNotSupportedF,            //  typeNull
        OpMul_TypeNotSupportedF,            //  typeType
        OpMul_TypeNotSupportedF,            //  typeBoolean
        OpMul_TypeNotSupportedF,            //  typeInteger
        OpMul_TypeNotSupportedF,            //  typeReal
        OpMul_TypeNotSupportedF,            //  typeString
        OpMul_TypeNotSupportedF,            //  typeArray
        OpMul_TypeNotSupportedF,            //  typeDictionary
        OpMul_TypeNotSupportedF,            //  typeStructure
        OpMul_TypeNotSupportedF             //  typeExecutable
    }
};

////////////////////////////////////////////////////////////////////////////////

namespace
{
    
    std::shared_ptr< dish::iAtomic > OpDiv_TypeNotSupportedF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        std::stringstream message;
        message << "Illegal operation: <";
        message << TypeToString(arg1.Type());
        message << "> / <";
        message << TypeToString(arg2.Type());
        message << ">.";
                
        throw dish::IllegalOperationException(message.str());
    }
    
    std::shared_ptr< dish::iAtomic > OpDiv_IntegerIntegerF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        return dish::IntegerValue::MakeValue(dish::Divide(arg1.AsInteger(), arg2.AsInteger()));
    }
    
    std::shared_ptr< dish::iAtomic > OpDiv_RealRealF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        return dish::RealValue::MakeValue(dish::Divide(arg1.AsReal(), arg2.AsReal()));
    }

}
    
const dish::TwoArgOpF dish::OpDiv_FuncTable[dish::iAtomic::typeNUM][dish::iAtomic::typeNUM] =
{
    //  typeNull
    {
        OpDiv_TypeNotSupportedF,            //  typeNull
        OpDiv_TypeNotSupportedF,            //  typeType
        OpDiv_TypeNotSupportedF,            //  typeBoolean
        OpDiv_TypeNotSupportedF,            //  typeInteger
        OpDiv_TypeNotSupportedF,            //  typeReal
        OpDiv_TypeNotSupportedF,            //  typeString
        OpDiv_TypeNotSupportedF,            //  typeArray
        OpDiv_TypeNotSupportedF,            //  typeDictionary
        OpDiv_TypeNotSupportedF,            //  typeStructure
        OpDiv_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeType
    {
        OpDiv_TypeNotSupportedF,            //  typeNull
        OpDiv_TypeNotSupportedF,            //  typeType
        OpDiv_TypeNotSupportedF,            //  typeBoolean
        OpDiv_TypeNotSupportedF,            //  typeInteger
        OpDiv_TypeNotSupportedF,            //  typeReal
        OpDiv_TypeNotSupportedF,            //  typeString
        OpDiv_TypeNotSupportedF,            //  typeArray
        OpDiv_TypeNotSupportedF,            //  typeDictionary
        OpDiv_TypeNotSupportedF,            //  typeStructure
        OpDiv_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeBoolean
    {
        OpDiv_TypeNotSupportedF,            //  typeNull
        OpDiv_TypeNotSupportedF,            //  typeType
        OpDiv_IntegerIntegerF,              //  typeBoolean
        OpDiv_IntegerIntegerF,              //  typeInteger
        OpDiv_RealRealF,                    //  typeReal
        OpDiv_IntegerIntegerF,              //  typeString
        OpDiv_TypeNotSupportedF,            //  typeArray
        OpDiv_TypeNotSupportedF,            //  typeDictionary
        OpDiv_TypeNotSupportedF,            //  typeStructure
        OpDiv_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeInteger
    {
        OpDiv_TypeNotSupportedF,            //  typeNull
        OpDiv_TypeNotSupportedF,            //  typeType
        OpDiv_IntegerIntegerF,              //  typeBoolean
        OpDiv_IntegerIntegerF,              //  typeInteger
        OpDiv_RealRealF,                    //  typeReal
        OpDiv_IntegerIntegerF,              //  typeString
        OpDiv_TypeNotSupportedF,            //  typeArray
        OpDiv_TypeNotSupportedF,            //  typeDictionary
        OpDiv_TypeNotSupportedF,            //  typeStructure
        OpDiv_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeReal
    {
        OpDiv_TypeNotSupportedF,            //  typeNull
        OpDiv_TypeNotSupportedF,            //  typeType
        OpDiv_RealRealF,                    //  typeBoolean
        OpDiv_RealRealF,                    //  typeInteger
        OpDiv_RealRealF,                    //  typeReal
        OpDiv_RealRealF,                    //  typeString
        OpDiv_TypeNotSupportedF,            //  typeArray
        OpDiv_TypeNotSupportedF,            //  typeDictionary
        OpDiv_TypeNotSupportedF,            //  typeStructure
        OpDiv_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeString
    {
        OpDiv_TypeNotSupportedF,            //  typeNull
        OpDiv_TypeNotSupportedF,            //  typeType
        OpDiv_IntegerIntegerF,              //  typeBoolean
        OpDiv_IntegerIntegerF,              //  typeInteger
        OpDiv_RealRealF,                    //  typeReal
        OpDiv_TypeNotSupportedF,            //  typeString
        OpDiv_TypeNotSupportedF,            //  typeArray
        OpDiv_TypeNotSupportedF,            //  typeDictionary
        OpDiv_TypeNotSupportedF,            //  typeStructure
        OpDiv_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeArray
    {
        OpDiv_TypeNotSupportedF,            //  typeNull
        OpDiv_TypeNotSupportedF,            //  typeType
        OpDiv_TypeNotSupportedF,            //  typeBoolean
        OpDiv_TypeNotSupportedF,            //  typeInteger
        OpDiv_TypeNotSupportedF,            //  typeReal
        OpDiv_TypeNotSupportedF,            //  typeString
        OpDiv_TypeNotSupportedF,            //  typeArray
        OpDiv_TypeNotSupportedF,            //  typeDictionary
        OpDiv_TypeNotSupportedF,            //  typeStructure
        OpDiv_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeDictionary
    {
        OpDiv_TypeNotSupportedF,            //  typeNull
        OpDiv_TypeNotSupportedF,            //  typeType
        OpDiv_TypeNotSupportedF,            //  typeBoolean
        OpDiv_TypeNotSupportedF,            //  typeInteger
        OpDiv_TypeNotSupportedF,            //  typeReal
        OpDiv_TypeNotSupportedF,            //  typeString
        OpDiv_TypeNotSupportedF,            //  typeArray
        OpDiv_TypeNotSupportedF,            //  typeDictionary
        OpDiv_TypeNotSupportedF,            //  typeStructure
        OpDiv_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeStructure
    {
        OpDiv_TypeNotSupportedF,            //  typeNull
        OpDiv_TypeNotSupportedF,            //  typeType
        OpDiv_TypeNotSupportedF,            //  typeBoolean
        OpDiv_TypeNotSupportedF,            //  typeInteger
        OpDiv_TypeNotSupportedF,            //  typeReal
        OpDiv_TypeNotSupportedF,            //  typeString
        OpDiv_TypeNotSupportedF,            //  typeArray
        OpDiv_TypeNotSupportedF,            //  typeDictionary
        OpDiv_TypeNotSupportedF,            //  typeStructure
        OpDiv_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeExecutable
    {
        OpDiv_TypeNotSupportedF,            //  typeNull
        OpDiv_TypeNotSupportedF,            //  typeType
        OpDiv_TypeNotSupportedF,            //  typeBoolean
        OpDiv_TypeNotSupportedF,            //  typeInteger
        OpDiv_TypeNotSupportedF,            //  typeReal
        OpDiv_TypeNotSupportedF,            //  typeString
        OpDiv_TypeNotSupportedF,            //  typeArray
        OpDiv_TypeNotSupportedF,            //  typeDictionary
        OpDiv_TypeNotSupportedF,            //  typeStructure
        OpDiv_TypeNotSupportedF             //  typeExecutable
    }
};

////////////////////////////////////////////////////////////////////////////////

namespace
{
    
    std::shared_ptr< dish::iAtomic > OpMod_TypeNotSupportedF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        std::stringstream message;
        message << "Illegal operation: <";
        message << TypeToString(arg1.Type());
        message << "> % <";
        message << TypeToString(arg2.Type());
        message << ">.";
                
        throw dish::IllegalOperationException(message.str());
    }
    
    std::shared_ptr< dish::iAtomic > OpMod_IntegerIntegerF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        return dish::IntegerValue::MakeValue(dish::Modulus(arg1.AsInteger(), arg2.AsInteger()));
    }
    
    std::shared_ptr< dish::iAtomic > OpMod_RealRealF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        return dish::RealValue::MakeValue(dish::Modulus(arg1.AsReal(), arg2.AsReal()));
    }

}
    
const dish::TwoArgOpF dish::OpMod_FuncTable[dish::iAtomic::typeNUM][dish::iAtomic::typeNUM] =
{
    //  typeNull
    {
        OpMod_TypeNotSupportedF,            //  typeNull
        OpMod_TypeNotSupportedF,            //  typeType
        OpMod_TypeNotSupportedF,            //  typeBoolean
        OpMod_TypeNotSupportedF,            //  typeInteger
        OpMod_TypeNotSupportedF,            //  typeReal
        OpMod_TypeNotSupportedF,            //  typeString
        OpMod_TypeNotSupportedF,            //  typeArray
        OpMod_TypeNotSupportedF,            //  typeDictionary
        OpMod_TypeNotSupportedF,            //  typeStructure
        OpMod_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeType
    {
        OpMod_TypeNotSupportedF,            //  typeNull
        OpMod_TypeNotSupportedF,            //  typeType
        OpMod_TypeNotSupportedF,            //  typeBoolean
        OpMod_TypeNotSupportedF,            //  typeInteger
        OpMod_TypeNotSupportedF,            //  typeReal
        OpMod_TypeNotSupportedF,            //  typeString
        OpMod_TypeNotSupportedF,            //  typeArray
        OpMod_TypeNotSupportedF,            //  typeDictionary
        OpMod_TypeNotSupportedF,            //  typeStructure
        OpMod_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeBoolean
    {
        OpMod_TypeNotSupportedF,            //  typeNull
        OpMod_TypeNotSupportedF,            //  typeType
        OpMod_IntegerIntegerF,              //  typeBoolean
        OpMod_IntegerIntegerF,              //  typeInteger
        OpMod_RealRealF,                    //  typeReal
        OpMod_IntegerIntegerF,              //  typeString
        OpMod_TypeNotSupportedF,            //  typeArray
        OpMod_TypeNotSupportedF,            //  typeDictionary
        OpMod_TypeNotSupportedF,            //  typeStructure
        OpMod_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeInteger
    {
        OpMod_TypeNotSupportedF,            //  typeNull
        OpMod_TypeNotSupportedF,            //  typeType
        OpMod_IntegerIntegerF,              //  typeBoolean
        OpMod_IntegerIntegerF,              //  typeInteger
        OpMod_RealRealF,                    //  typeReal
        OpMod_IntegerIntegerF,              //  typeString
        OpMod_TypeNotSupportedF,            //  typeArray
        OpMod_TypeNotSupportedF,            //  typeDictionary
        OpMod_TypeNotSupportedF,            //  typeStructure
        OpMod_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeReal
    {
        OpMod_TypeNotSupportedF,            //  typeNull
        OpMod_TypeNotSupportedF,            //  typeType
        OpMod_RealRealF,                    //  typeBoolean
        OpMod_RealRealF,                    //  typeInteger
        OpMod_RealRealF,                    //  typeReal
        OpMod_RealRealF,                    //  typeString
        OpMod_TypeNotSupportedF,            //  typeArray
        OpMod_TypeNotSupportedF,            //  typeDictionary
        OpMod_TypeNotSupportedF,            //  typeStructure
        OpMod_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeString
    {
        OpMod_TypeNotSupportedF,            //  typeNull
        OpMod_TypeNotSupportedF,            //  typeType
        OpMod_IntegerIntegerF,              //  typeBoolean
        OpMod_IntegerIntegerF,              //  typeInteger
        OpMod_RealRealF,                    //  typeReal
        OpMod_TypeNotSupportedF,            //  typeString
        OpMod_TypeNotSupportedF,            //  typeArray
        OpMod_TypeNotSupportedF,            //  typeDictionary
        OpMod_TypeNotSupportedF,            //  typeStructure
        OpMod_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeArray
    {
        OpMod_TypeNotSupportedF,            //  typeNull
        OpMod_TypeNotSupportedF,            //  typeType
        OpMod_TypeNotSupportedF,            //  typeBoolean
        OpMod_TypeNotSupportedF,            //  typeInteger
        OpMod_TypeNotSupportedF,            //  typeReal
        OpMod_TypeNotSupportedF,            //  typeString
        OpMod_TypeNotSupportedF,            //  typeArray
        OpMod_TypeNotSupportedF,            //  typeDictionary
        OpMod_TypeNotSupportedF,            //  typeStructure
        OpMod_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeDictionary
    {
        OpMod_TypeNotSupportedF,            //  typeNull
        OpMod_TypeNotSupportedF,            //  typeType
        OpMod_TypeNotSupportedF,            //  typeBoolean
        OpMod_TypeNotSupportedF,            //  typeInteger
        OpMod_TypeNotSupportedF,            //  typeReal
        OpMod_TypeNotSupportedF,            //  typeString
        OpMod_TypeNotSupportedF,            //  typeArray
        OpMod_TypeNotSupportedF,            //  typeDictionary
        OpMod_TypeNotSupportedF,            //  typeStructure
        OpMod_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeStructure
    {
        OpMod_TypeNotSupportedF,            //  typeNull
        OpMod_TypeNotSupportedF,            //  typeType
        OpMod_TypeNotSupportedF,            //  typeBoolean
        OpMod_TypeNotSupportedF,            //  typeInteger
        OpMod_TypeNotSupportedF,            //  typeReal
        OpMod_TypeNotSupportedF,            //  typeString
        OpMod_TypeNotSupportedF,            //  typeArray
        OpMod_TypeNotSupportedF,            //  typeDictionary
        OpMod_TypeNotSupportedF,            //  typeStructure
        OpMod_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeExecutable
    {
        OpMod_TypeNotSupportedF,            //  typeNull
        OpMod_TypeNotSupportedF,            //  typeType
        OpMod_TypeNotSupportedF,            //  typeBoolean
        OpMod_TypeNotSupportedF,            //  typeInteger
        OpMod_TypeNotSupportedF,            //  typeReal
        OpMod_TypeNotSupportedF,            //  typeString
        OpMod_TypeNotSupportedF,            //  typeArray
        OpMod_TypeNotSupportedF,            //  typeDictionary
        OpMod_TypeNotSupportedF,            //  typeStructure
        OpMod_TypeNotSupportedF             //  typeExecutable
    }
};

////////////////////////////////////////////////////////////////////////////////

namespace
{
    
    std::shared_ptr< dish::iAtomic > OpPow_TypeNotSupportedF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        std::stringstream message;
        message << "Illegal operation: <";
        message << TypeToString(arg1.Type());
        message << "> ^ <";
        message << TypeToString(arg2.Type());
        message << ">.";
                
        throw dish::IllegalOperationException(message.str());
    }
    
    std::shared_ptr< dish::iAtomic > OpPow_IntegerIntegerF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        return dish::IntegerValue::MakeValue(dish::Pow(arg1.AsInteger(), arg2.AsInteger()));
    }
    
    std::shared_ptr< dish::iAtomic > OpPow_RealRealF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        return dish::RealValue::MakeValue(dish::Pow(arg1.AsReal(), arg2.AsReal()));
    }

}

const dish::TwoArgOpF dish::OpPow_FuncTable[dish::iAtomic::typeNUM][dish::iAtomic::typeNUM] =
{
    //  typeNull
    {
        OpPow_TypeNotSupportedF,            //  typeNull
        OpPow_TypeNotSupportedF,            //  typeType
        OpPow_TypeNotSupportedF,            //  typeBoolean
        OpPow_TypeNotSupportedF,            //  typeInteger
        OpPow_TypeNotSupportedF,            //  typeReal
        OpPow_TypeNotSupportedF,            //  typeString
        OpPow_TypeNotSupportedF,            //  typeArray
        OpPow_TypeNotSupportedF,            //  typeDictionary
        OpPow_TypeNotSupportedF,            //  typeStructure
        OpPow_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeType
    {
        OpPow_TypeNotSupportedF,            //  typeNull
        OpPow_TypeNotSupportedF,            //  typeType
        OpPow_TypeNotSupportedF,            //  typeBoolean
        OpPow_TypeNotSupportedF,            //  typeInteger
        OpPow_TypeNotSupportedF,            //  typeReal
        OpPow_TypeNotSupportedF,            //  typeString
        OpPow_TypeNotSupportedF,            //  typeArray
        OpPow_TypeNotSupportedF,            //  typeDictionary
        OpPow_TypeNotSupportedF,            //  typeStructure
        OpPow_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeBoolean
    {
        OpPow_TypeNotSupportedF,            //  typeNull
        OpPow_TypeNotSupportedF,            //  typeType
        OpPow_IntegerIntegerF,              //  typeBoolean
        OpPow_IntegerIntegerF,              //  typeInteger
        OpPow_RealRealF,                    //  typeReal
        OpPow_IntegerIntegerF,              //  typeString
        OpPow_TypeNotSupportedF,            //  typeArray
        OpPow_TypeNotSupportedF,            //  typeDictionary
        OpPow_TypeNotSupportedF,            //  typeStructure
        OpPow_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeInteger
    {
        OpPow_TypeNotSupportedF,            //  typeNull
        OpPow_TypeNotSupportedF,            //  typeType
        OpPow_IntegerIntegerF,              //  typeBoolean
        OpPow_IntegerIntegerF,              //  typeInteger
        OpPow_RealRealF,                    //  typeReal
        OpPow_IntegerIntegerF,              //  typeString
        OpPow_TypeNotSupportedF,            //  typeArray
        OpPow_TypeNotSupportedF,            //  typeDictionary
        OpPow_TypeNotSupportedF,            //  typeStructure
        OpPow_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeReal
    {
        OpPow_TypeNotSupportedF,            //  typeNull
        OpPow_TypeNotSupportedF,            //  typeType
        OpPow_RealRealF,                    //  typeBoolean
        OpPow_RealRealF,                    //  typeInteger
        OpPow_RealRealF,                    //  typeReal
        OpPow_RealRealF,                    //  typeString
        OpPow_TypeNotSupportedF,            //  typeArray
        OpPow_TypeNotSupportedF,            //  typeDictionary
        OpPow_TypeNotSupportedF,            //  typeStructure
        OpPow_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeString
    {
        OpPow_TypeNotSupportedF,            //  typeNull
        OpPow_TypeNotSupportedF,            //  typeType
        OpPow_IntegerIntegerF,              //  typeBoolean
        OpPow_IntegerIntegerF,              //  typeInteger
        OpPow_RealRealF,                    //  typeReal
        OpPow_TypeNotSupportedF,            //  typeString
        OpPow_TypeNotSupportedF,            //  typeArray
        OpPow_TypeNotSupportedF,            //  typeDictionary
        OpPow_TypeNotSupportedF,            //  typeStructure
        OpPow_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeArray
    {
        OpPow_TypeNotSupportedF,            //  typeNull
        OpPow_TypeNotSupportedF,            //  typeType
        OpPow_TypeNotSupportedF,            //  typeBoolean
        OpPow_TypeNotSupportedF,            //  typeInteger
        OpPow_TypeNotSupportedF,            //  typeReal
        OpPow_TypeNotSupportedF,            //  typeString
        OpPow_TypeNotSupportedF,            //  typeArray
        OpPow_TypeNotSupportedF,            //  typeDictionary
        OpPow_TypeNotSupportedF,            //  typeStructure
        OpPow_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeDictionary
    {
        OpPow_TypeNotSupportedF,            //  typeNull
        OpPow_TypeNotSupportedF,            //  typeType
        OpPow_TypeNotSupportedF,            //  typeBoolean
        OpPow_TypeNotSupportedF,            //  typeInteger
        OpPow_TypeNotSupportedF,            //  typeReal
        OpPow_TypeNotSupportedF,            //  typeString
        OpPow_TypeNotSupportedF,            //  typeArray
        OpPow_TypeNotSupportedF,            //  typeDictionary
        OpPow_TypeNotSupportedF,            //  typeStructure
        OpPow_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeStructure
    {
        OpPow_TypeNotSupportedF,            //  typeNull
        OpPow_TypeNotSupportedF,            //  typeType
        OpPow_TypeNotSupportedF,            //  typeBoolean
        OpPow_TypeNotSupportedF,            //  typeInteger
        OpPow_TypeNotSupportedF,            //  typeReal
        OpPow_TypeNotSupportedF,            //  typeString
        OpPow_TypeNotSupportedF,            //  typeArray
        OpPow_TypeNotSupportedF,            //  typeDictionary
        OpPow_TypeNotSupportedF,            //  typeStructure
        OpPow_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeExecutable
    {
        OpPow_TypeNotSupportedF,            //  typeNull
        OpPow_TypeNotSupportedF,            //  typeType
        OpPow_TypeNotSupportedF,            //  typeBoolean
        OpPow_TypeNotSupportedF,            //  typeInteger
        OpPow_TypeNotSupportedF,            //  typeReal
        OpPow_TypeNotSupportedF,            //  typeString
        OpPow_TypeNotSupportedF,            //  typeArray
        OpPow_TypeNotSupportedF,            //  typeDictionary
        OpPow_TypeNotSupportedF,            //  typeStructure
        OpPow_TypeNotSupportedF             //  typeExecutable
    }
};

////////////////////////////////////////////////////////////////////////////////

namespace
{
    
    bool OpNot_TypeNotSupportedF(const dish::iAtomic &arg)
    {
        std::stringstream message;
        message << "Illegal operation: not <";
        message << TypeToString(arg.Type());
        message << ">.";
        
        throw dish::IllegalOperationException(message.str());
    }
    
    bool OpNot_BooleanF(const dish::iAtomic &arg)
    {
        return !arg.AsBoolean();
    }
    
}
    
const dish::OneArgBoolOpF dish::OpNot_FuncTable[dish::iAtomic::typeNUM] = 
{
    OpNot_TypeNotSupportedF,        //  typeNull
    OpNot_TypeNotSupportedF,        //  typeType
    OpNot_BooleanF,                 //  typeBoolean
    OpNot_BooleanF,                 //  typeInteger
    OpNot_BooleanF,                 //  typeReal
    OpNot_BooleanF,                 //  typeString
    OpNot_TypeNotSupportedF,        //  typeArray
    OpNot_TypeNotSupportedF,        //  typeDictionary
    OpNot_TypeNotSupportedF,        //  typeStructure
    OpNot_TypeNotSupportedF         //  typeExecutable
};

////////////////////////////////////////////////////////////////////////////////

namespace
{
    
    bool OpAnd_TypeNotSupportedF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        std::stringstream message;
        message << "Illegal operation: <";
        message << TypeToString(arg1.Type());
        message << "> and <";
        message << TypeToString(arg2.Type());
        message << ">.";
                
        throw dish::IllegalOperationException(message.str());
    }
    
    bool OpAnd_BooleanBooleanF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        return (arg1.AsBoolean() && arg2.AsBoolean());
    }

}
    
const dish::TwoArgBoolOpF dish::OpAnd_FuncTable[dish::iAtomic::typeNUM][dish::iAtomic::typeNUM] =
{
    //  typeNull
    {
        OpAnd_TypeNotSupportedF,            //  typeNull
        OpAnd_TypeNotSupportedF,            //  typeType
        OpAnd_TypeNotSupportedF,            //  typeBoolean
        OpAnd_TypeNotSupportedF,            //  typeInteger
        OpAnd_TypeNotSupportedF,            //  typeReal
        OpAnd_TypeNotSupportedF,            //  typeString
        OpAnd_TypeNotSupportedF,            //  typeArray
        OpAnd_TypeNotSupportedF,            //  typeDictionary
        OpAnd_TypeNotSupportedF,            //  typeStructure
        OpAnd_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeType
    {
        OpAnd_TypeNotSupportedF,            //  typeNull
        OpAnd_TypeNotSupportedF,            //  typeType
        OpAnd_TypeNotSupportedF,            //  typeBoolean
        OpAnd_TypeNotSupportedF,            //  typeInteger
        OpAnd_TypeNotSupportedF,            //  typeReal
        OpAnd_TypeNotSupportedF,            //  typeString
        OpAnd_TypeNotSupportedF,            //  typeArray
        OpAnd_TypeNotSupportedF,            //  typeDictionary
        OpAnd_TypeNotSupportedF,            //  typeStructure
        OpAnd_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeBoolean
    {
        OpAnd_TypeNotSupportedF,            //  typeNull
        OpAnd_TypeNotSupportedF,            //  typeType
        OpAnd_BooleanBooleanF,              //  typeBoolean
        OpAnd_BooleanBooleanF,              //  typeInteger
        OpAnd_BooleanBooleanF,              //  typeReal
        OpAnd_BooleanBooleanF,              //  typeString
        OpAnd_TypeNotSupportedF,            //  typeArray
        OpAnd_TypeNotSupportedF,            //  typeDictionary
        OpAnd_TypeNotSupportedF,            //  typeStructure
        OpAnd_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeInteger
    {
        OpAnd_TypeNotSupportedF,            //  typeNull
        OpAnd_TypeNotSupportedF,            //  typeType
        OpAnd_BooleanBooleanF,              //  typeBoolean
        OpAnd_BooleanBooleanF,              //  typeInteger
        OpAnd_BooleanBooleanF,              //  typeReal
        OpAnd_BooleanBooleanF,              //  typeString
        OpAnd_TypeNotSupportedF,            //  typeArray
        OpAnd_TypeNotSupportedF,            //  typeDictionary
        OpAnd_TypeNotSupportedF,            //  typeStructure
        OpAnd_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeReal
    {
        OpAnd_TypeNotSupportedF,            //  typeNull
        OpAnd_TypeNotSupportedF,            //  typeType
        OpAnd_BooleanBooleanF,              //  typeBoolean
        OpAnd_BooleanBooleanF,              //  typeInteger
        OpAnd_BooleanBooleanF,              //  typeReal
        OpAnd_BooleanBooleanF,              //  typeString
        OpAnd_TypeNotSupportedF,            //  typeArray
        OpAnd_TypeNotSupportedF,            //  typeDictionary
        OpAnd_TypeNotSupportedF,            //  typeStructure
        OpAnd_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeString
    {
        OpAnd_TypeNotSupportedF,            //  typeNull
        OpAnd_TypeNotSupportedF,            //  typeType
        OpAnd_BooleanBooleanF,              //  typeBoolean
        OpAnd_BooleanBooleanF,              //  typeInteger
        OpAnd_BooleanBooleanF,              //  typeReal
        OpAnd_BooleanBooleanF,              //  typeString
        OpAnd_TypeNotSupportedF,            //  typeArray
        OpAnd_TypeNotSupportedF,            //  typeDictionary
        OpAnd_TypeNotSupportedF,            //  typeStructure
        OpAnd_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeArray
    {
        OpAnd_TypeNotSupportedF,            //  typeNull
        OpAnd_TypeNotSupportedF,            //  typeType
        OpAnd_BooleanBooleanF,              //  typeBoolean
        OpAnd_BooleanBooleanF,              //  typeInteger
        OpAnd_BooleanBooleanF,              //  typeReal
        OpAnd_BooleanBooleanF,              //  typeString
        OpAnd_TypeNotSupportedF,            //  typeArray
        OpAnd_TypeNotSupportedF,            //  typeDictionary
        OpAnd_TypeNotSupportedF,            //  typeStructure
        OpAnd_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeDictionary
    {
        OpAnd_TypeNotSupportedF,            //  typeNull
        OpAnd_TypeNotSupportedF,            //  typeType
        OpAnd_TypeNotSupportedF,            //  typeBoolean
        OpAnd_TypeNotSupportedF,            //  typeInteger
        OpAnd_TypeNotSupportedF,            //  typeReal
        OpAnd_TypeNotSupportedF,            //  typeString
        OpAnd_TypeNotSupportedF,            //  typeArray
        OpAnd_TypeNotSupportedF,            //  typeDictionary
        OpAnd_TypeNotSupportedF,            //  typeStructure
        OpAnd_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeStructure
    {
        OpAnd_TypeNotSupportedF,            //  typeNull
        OpAnd_TypeNotSupportedF,            //  typeType
        OpAnd_TypeNotSupportedF,            //  typeBoolean
        OpAnd_TypeNotSupportedF,            //  typeInteger
        OpAnd_TypeNotSupportedF,            //  typeReal
        OpAnd_TypeNotSupportedF,            //  typeString
        OpAnd_TypeNotSupportedF,            //  typeArray
        OpAnd_TypeNotSupportedF,            //  typeDictionary
        OpAnd_TypeNotSupportedF,            //  typeStructure
        OpAnd_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeExecutable
    {
        OpAnd_TypeNotSupportedF,            //  typeNull
        OpAnd_TypeNotSupportedF,            //  typeType
        OpAnd_TypeNotSupportedF,            //  typeBoolean
        OpAnd_TypeNotSupportedF,            //  typeInteger
        OpAnd_TypeNotSupportedF,            //  typeReal
        OpAnd_TypeNotSupportedF,            //  typeString
        OpAnd_TypeNotSupportedF,            //  typeArray
        OpAnd_TypeNotSupportedF,            //  typeDictionary
        OpAnd_TypeNotSupportedF,            //  typeStructure
        OpAnd_TypeNotSupportedF             //  typeExecutable
    }
};

////////////////////////////////////////////////////////////////////////////////

namespace
{
    
    bool OpOr_TypeNotSupportedF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        std::stringstream message;
        message << "Illegal operation: <";
        message << TypeToString(arg1.Type());
        message << "> or <";
        message << TypeToString(arg2.Type());
        message << ">.";
                
        throw dish::IllegalOperationException(message.str());
    }
    
    bool OpOr_BooleanBooleanF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        return (arg1.AsBoolean() || arg2.AsBoolean());
    }

}
    
const dish::TwoArgBoolOpF dish::OpOr_FuncTable[dish::iAtomic::typeNUM][dish::iAtomic::typeNUM] =
{
    //  typeNull
    {
        OpOr_TypeNotSupportedF,             //  typeNull
        OpOr_TypeNotSupportedF,             //  typeType
        OpOr_TypeNotSupportedF,             //  typeBoolean
        OpOr_TypeNotSupportedF,             //  typeInteger
        OpOr_TypeNotSupportedF,             //  typeReal
        OpOr_TypeNotSupportedF,             //  typeString
        OpOr_TypeNotSupportedF,             //  typeArray
        OpOr_TypeNotSupportedF,             //  typeDictionary
        OpOr_TypeNotSupportedF,             //  typeStructure
        OpOr_TypeNotSupportedF              //  typeExecutable
    },
    
    //  typeType
    {
        OpOr_TypeNotSupportedF,             //  typeNull
        OpOr_TypeNotSupportedF,             //  typeType
        OpOr_TypeNotSupportedF,             //  typeBoolean
        OpOr_TypeNotSupportedF,             //  typeInteger
        OpOr_TypeNotSupportedF,             //  typeReal
        OpOr_TypeNotSupportedF,             //  typeString
        OpOr_TypeNotSupportedF,             //  typeArray
        OpOr_TypeNotSupportedF,             //  typeDictionary
        OpOr_TypeNotSupportedF,             //  typeStructure
        OpOr_TypeNotSupportedF              //  typeExecutable
    },
    
    //  typeBoolean
    {
        OpOr_TypeNotSupportedF,             //  typeNull
        OpOr_TypeNotSupportedF,             //  typeType
        OpOr_BooleanBooleanF,               //  typeBoolean
        OpOr_BooleanBooleanF,               //  typeInteger
        OpOr_BooleanBooleanF,               //  typeReal
        OpOr_BooleanBooleanF,               //  typeString
        OpOr_TypeNotSupportedF,             //  typeArray
        OpOr_TypeNotSupportedF,             //  typeDictionary
        OpOr_TypeNotSupportedF,             //  typeStructure
        OpOr_TypeNotSupportedF              //  typeExecutable
    },
    
    //  typeInteger
    {
        OpOr_TypeNotSupportedF,             //  typeNull
        OpOr_TypeNotSupportedF,             //  typeType
        OpOr_BooleanBooleanF,               //  typeBoolean
        OpOr_BooleanBooleanF,               //  typeInteger
        OpOr_BooleanBooleanF,               //  typeReal
        OpOr_BooleanBooleanF,               //  typeString
        OpOr_TypeNotSupportedF,             //  typeArray
        OpOr_TypeNotSupportedF,             //  typeDictionary
        OpOr_TypeNotSupportedF,             //  typeStructure
        OpOr_TypeNotSupportedF              //  typeExecutable
    },
    
    //  typeReal
    {
        OpOr_TypeNotSupportedF,             //  typeNull
        OpOr_TypeNotSupportedF,             //  typeType
        OpOr_BooleanBooleanF,               //  typeBoolean
        OpOr_BooleanBooleanF,               //  typeInteger
        OpOr_BooleanBooleanF,               //  typeReal
        OpOr_BooleanBooleanF,               //  typeString
        OpOr_TypeNotSupportedF,             //  typeArray
        OpOr_TypeNotSupportedF,             //  typeDictionary
        OpOr_TypeNotSupportedF,             //  typeStructure
        OpOr_TypeNotSupportedF              //  typeExecutable
    },
    
    //  typeString
    {
        OpOr_TypeNotSupportedF,             //  typeNull
        OpOr_TypeNotSupportedF,             //  typeType
        OpOr_BooleanBooleanF,               //  typeBoolean
        OpOr_BooleanBooleanF,               //  typeInteger
        OpOr_BooleanBooleanF,               //  typeReal
        OpOr_BooleanBooleanF,               //  typeString
        OpOr_TypeNotSupportedF,             //  typeArray
        OpOr_TypeNotSupportedF,             //  typeDictionary
        OpOr_TypeNotSupportedF,             //  typeStructure
        OpOr_TypeNotSupportedF              //  typeExecutable
    },
    
    //  typeArray
    {
        OpOr_TypeNotSupportedF,             //  typeNull
        OpOr_TypeNotSupportedF,             //  typeType
        OpOr_BooleanBooleanF,               //  typeBoolean
        OpOr_BooleanBooleanF,               //  typeInteger
        OpOr_BooleanBooleanF,               //  typeReal
        OpOr_BooleanBooleanF,               //  typeString
        OpOr_TypeNotSupportedF,             //  typeArray
        OpOr_TypeNotSupportedF,             //  typeDictionary
        OpOr_TypeNotSupportedF,             //  typeStructure
        OpOr_TypeNotSupportedF              //  typeExecutable
    },
    
    //  typeDictionary
    {
        OpOr_TypeNotSupportedF,             //  typeNull
        OpOr_TypeNotSupportedF,             //  typeType
        OpOr_TypeNotSupportedF,             //  typeBoolean
        OpOr_TypeNotSupportedF,             //  typeInteger
        OpOr_TypeNotSupportedF,             //  typeReal
        OpOr_TypeNotSupportedF,             //  typeString
        OpOr_TypeNotSupportedF,             //  typeArray
        OpOr_TypeNotSupportedF,             //  typeDictionary
        OpOr_TypeNotSupportedF,             //  typeStructure
        OpOr_TypeNotSupportedF              //  typeExecutable
    },
    
    //  typeStructure
    {
        OpOr_TypeNotSupportedF,             //  typeNull
        OpOr_TypeNotSupportedF,             //  typeType
        OpOr_TypeNotSupportedF,             //  typeBoolean
        OpOr_TypeNotSupportedF,             //  typeInteger
        OpOr_TypeNotSupportedF,             //  typeReal
        OpOr_TypeNotSupportedF,             //  typeString
        OpOr_TypeNotSupportedF,             //  typeArray
        OpOr_TypeNotSupportedF,             //  typeDictionary
        OpOr_TypeNotSupportedF,             //  typeStructure
        OpOr_TypeNotSupportedF              //  typeExecutable
    },
    
    //  typeExecutable
    {
        OpOr_TypeNotSupportedF,             //  typeNull
        OpOr_TypeNotSupportedF,             //  typeType
        OpOr_TypeNotSupportedF,             //  typeBoolean
        OpOr_TypeNotSupportedF,             //  typeInteger
        OpOr_TypeNotSupportedF,             //  typeReal
        OpOr_TypeNotSupportedF,             //  typeString
        OpOr_TypeNotSupportedF,             //  typeArray
        OpOr_TypeNotSupportedF,             //  typeDictionary
        OpOr_TypeNotSupportedF,             //  typeStructure
        OpOr_TypeNotSupportedF              //  typeExecutable
    }
};

////////////////////////////////////////////////////////////////////////////////

namespace
{
    
    bool OpXor_TypeNotSupportedF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        std::stringstream message;
        message << "Illegal operation: <";
        message << TypeToString(arg1.Type());
        message << "> xor <";
        message << TypeToString(arg2.Type());
        message << ">.";
                
        throw dish::IllegalOperationException(message.str());
    }
    
    bool OpXor_BooleanBooleanF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        return (arg1.AsBoolean() ^ arg2.AsBoolean());
    }

}
    
const dish::TwoArgBoolOpF dish::OpXor_FuncTable[dish::iAtomic::typeNUM][dish::iAtomic::typeNUM] =
{
    //  typeNull
    {
        OpXor_TypeNotSupportedF,            //  typeNull
        OpXor_TypeNotSupportedF,            //  typeType
        OpXor_TypeNotSupportedF,            //  typeBoolean
        OpXor_TypeNotSupportedF,            //  typeInteger
        OpXor_TypeNotSupportedF,            //  typeReal
        OpXor_TypeNotSupportedF,            //  typeString
        OpXor_TypeNotSupportedF,            //  typeArray
        OpXor_TypeNotSupportedF,            //  typeDictionary
        OpXor_TypeNotSupportedF,            //  typeStructure
        OpXor_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeType
    {
        OpXor_TypeNotSupportedF,            //  typeNull
        OpXor_TypeNotSupportedF,            //  typeType
        OpXor_TypeNotSupportedF,            //  typeBoolean
        OpXor_TypeNotSupportedF,            //  typeInteger
        OpXor_TypeNotSupportedF,            //  typeReal
        OpXor_TypeNotSupportedF,            //  typeString
        OpXor_TypeNotSupportedF,            //  typeArray
        OpXor_TypeNotSupportedF,            //  typeDicti { return OpXor_FuncTable[arg1.Type()][arg2.Type()](arg1, arg2); };onary
        OpXor_TypeNotSupportedF,            //  typeStructure
        OpXor_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeBoolean
    {
        OpXor_TypeNotSupportedF,            //  typeNull
        OpXor_TypeNotSupportedF,            //  typeType
        OpXor_BooleanBooleanF,              //  typeBoolean
        OpXor_BooleanBooleanF,              //  typeInteger
        OpXor_BooleanBooleanF,              //  typeReal
        OpXor_BooleanBooleanF,              //  typeString
        OpXor_TypeNotSupportedF,            //  typeArray
        OpXor_TypeNotSupportedF,            //  typeDictionary
        OpXor_TypeNotSupportedF,            //  typeStructure
        OpXor_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeInteger
    {
        OpXor_TypeNotSupportedF,            //  typeNull
        OpXor_TypeNotSupportedF,            //  typeType
        OpXor_BooleanBooleanF,              //  typeBoolean
        OpXor_BooleanBooleanF,              //  typeInteger
        OpXor_BooleanBooleanF,              //  typeReal
        OpXor_BooleanBooleanF,              //  typeString
        OpXor_TypeNotSupportedF,            //  typeArray
        OpXor_TypeNotSupportedF,            //  typeDictionary
        OpXor_TypeNotSupportedF,            //  typeStructure
        OpXor_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeReal
    {
        OpXor_TypeNotSupportedF,            //  typeNull
        OpXor_TypeNotSupportedF,            //  typeType
        OpXor_BooleanBooleanF,              //  typeBoolean
        OpXor_BooleanBooleanF,              //  typeInteger
        OpXor_BooleanBooleanF,              //  typeReal
        OpXor_BooleanBooleanF,              //  typeString
        OpXor_TypeNotSupportedF,            //  typeArray
        OpXor_TypeNotSupportedF,            //  typeDictionary
        OpXor_TypeNotSupportedF,            //  typeStructure
        OpXor_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeString
    {
        OpXor_TypeNotSupportedF,            //  typeNull
        OpXor_TypeNotSupportedF,            //  typeType
        OpXor_BooleanBooleanF,              //  typeBoolean
        OpXor_BooleanBooleanF,              //  typeInteger
        OpXor_BooleanBooleanF,              //  typeReal
        OpXor_BooleanBooleanF,              //  typeString
        OpXor_TypeNotSupportedF,            //  typeArray
        OpXor_TypeNotSupportedF,            //  typeDictionary
        OpXor_TypeNotSupportedF,            //  typeStructure
        OpXor_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeArray
    {
        OpXor_TypeNotSupportedF,            //  typeNull
        OpXor_TypeNotSupportedF,            //  typeType
        OpXor_BooleanBooleanF,              //  typeBoolean
        OpXor_BooleanBooleanF,              //  typeInteger
        OpXor_BooleanBooleanF,              //  typeReal
        OpXor_BooleanBooleanF,              //  typeString
        OpXor_TypeNotSupportedF,            //  typeArray
        OpXor_TypeNotSupportedF,            //  typeDictionary
        OpXor_TypeNotSupportedF,            //  typeStructure
        OpXor_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeDictionary
    {
        OpXor_TypeNotSupportedF,            //  typeNull
        OpXor_TypeNotSupportedF,            //  typeType
        OpXor_TypeNotSupportedF,            //  typeBoolean
        OpXor_TypeNotSupportedF,            //  typeInteger
        OpXor_TypeNotSupportedF,            //  typeReal
        OpXor_TypeNotSupportedF,            //  typeString
        OpXor_TypeNotSupportedF,            //  typeArray
        OpXor_TypeNotSupportedF,            //  typeDictionary
        OpXor_TypeNotSupportedF,            //  typeStructure
        OpXor_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeStructure
    {
        OpXor_TypeNotSupportedF,            //  typeNull
        OpXor_TypeNotSupportedF,            //  typeType
        OpXor_TypeNotSupportedF,            //  typeBoolean
        OpXor_TypeNotSupportedF,            //  typeInteger
        OpXor_TypeNotSupportedF,            //  typeReal
        OpXor_TypeNotSupportedF,            //  typeString
        OpXor_TypeNotSupportedF,            //  typeArray
        OpXor_TypeNotSupportedF,            //  typeDictionary
        OpXor_TypeNotSupportedF,            //  typeStructure
        OpXor_TypeNotSupportedF             //  typeExecutable
    },
    
    //  typeExecutable
    {
        OpXor_TypeNotSupportedF,            //  typeNull
        OpXor_TypeNotSupportedF,            //  typeType
        OpXor_TypeNotSupportedF,            //  typeBoolean
        OpXor_TypeNotSupportedF,            //  typeInteger
        OpXor_TypeNotSupportedF,            //  typeReal
        OpXor_TypeNotSupportedF,            //  typeString
        OpXor_TypeNotSupportedF,            //  typeArray
        OpXor_TypeNotSupportedF,            //  typeDictionary
        OpXor_TypeNotSupportedF,            //  typeStructure
        OpXor_TypeNotSupportedF             //  typeExecutable
    }
};
    
////////////////////////////////////////////////////////////////////////////////

namespace
{
    
    bool OpLessThan_TypeNotSupportedF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        std::stringstream message;
        message << "Illegal operation: <";
        message << TypeToString(arg1.Type());
        message << "> < <";
        message << TypeToString(arg2.Type());
        message << ">.";
                
        throw dish::IllegalOperationException(message.str());
    }
    
    bool OpLessThan_IntegerIntegerF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        return (arg1.AsInteger() < arg2.AsInteger());
    }
    
    bool OpLessThan_RealRealF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        return (arg1.AsReal() < arg2.AsReal());
    }
    
    bool OpLessThan_StringStringF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        return (arg1.AsString() < arg2.AsString());
    }

}
    
const dish::TwoArgBoolOpF dish::OpLessThan_FuncTable[dish::iAtomic::typeNUM][dish::iAtomic::typeNUM] =
{
    //  typeNull
    {
        OpLessThan_TypeNotSupportedF,       //  typeNull
        OpLessThan_TypeNotSupportedF,       //  typeType
        OpLessThan_TypeNotSupportedF,       //  typeBoolean
        OpLessThan_TypeNotSupportedF,       //  typeInteger
        OpLessThan_TypeNotSupportedF,       //  typeReal
        OpLessThan_TypeNotSupportedF,       //  typeString
        OpLessThan_TypeNotSupportedF,       //  typeArray
        OpLessThan_TypeNotSupportedF,       //  typeDictionary
        OpLessThan_TypeNotSupportedF,       //  typeStructure
        OpLessThan_TypeNotSupportedF        //  typeExecutable
    },
    
    //  typeType
    {
        OpLessThan_TypeNotSupportedF,       //  typeNull
        OpLessThan_TypeNotSupportedF,       //  typeType
        OpLessThan_TypeNotSupportedF,       //  typeBoolean
        OpLessThan_TypeNotSupportedF,       //  typeInteger
        OpLessThan_TypeNotSupportedF,       //  typeReal
        OpLessThan_TypeNotSupportedF,       //  typeString
        OpLessThan_TypeNotSupportedF,       //  typeArray
        OpLessThan_TypeNotSupportedF,       //  typeDictionary
        OpLessThan_TypeNotSupportedF,       //  typeStructure
        OpLessThan_TypeNotSupportedF        //  typeExecutable
    },
    
    //  typeBoolean
    {
        OpLessThan_TypeNotSupportedF,       //  typeNull
        OpLessThan_TypeNotSupportedF,       //  typeType
        OpLessThan_IntegerIntegerF,         //  typeBoolean
        OpLessThan_IntegerIntegerF,         //  typeInteger
        OpLessThan_RealRealF,               //  typeReal
        OpLessThan_StringStringF,           //  typeString
        OpLessThan_TypeNotSupportedF,       //  typeArray
        OpLessThan_TypeNotSupportedF,       //  typeDictionary
        OpLessThan_TypeNotSupportedF,       //  typeStructure
        OpLessThan_TypeNotSupportedF        //  typeExecutable
    },
    
    //  typeInteger
    {
        OpLessThan_TypeNotSupportedF,       //  typeNull
        OpLessThan_TypeNotSupportedF,       //  typeType
        OpLessThan_IntegerIntegerF,         //  typeBoolean
        OpLessThan_IntegerIntegerF,         //  typeInteger
        OpLessThan_RealRealF,               //  typeReal
        OpLessThan_StringStringF,           //  typeString
        OpLessThan_TypeNotSupportedF,       //  typeArray
        OpLessThan_TypeNotSupportedF,       //  typeDictionary
        OpLessThan_TypeNotSupportedF,       //  typeStructure
        OpLessThan_TypeNotSupportedF        //  typeExecutable
    },
    
    //  typeReal
    {
        OpLessThan_TypeNotSupportedF,       //  typeNull
        OpLessThan_TypeNotSupportedF,       //  typeType
        OpLessThan_RealRealF,               //  typeBoolean
        OpLessThan_RealRealF,               //  typeInteger
        OpLessThan_RealRealF,               //  typeReal
        OpLessThan_RealRealF,               //  typeString
        OpLessThan_TypeNotSupportedF,       //  typeArray
        OpLessThan_TypeNotSupportedF,       //  typeDictionary
        OpLessThan_TypeNotSupportedF,       //  typeStructure
        OpLessThan_TypeNotSupportedF        //  typeExecutable
    },
    
    //  typeString
    {
        OpLessThan_TypeNotSupportedF,       //  typeNull
        OpLessThan_TypeNotSupportedF,       //  typeType
        OpLessThan_StringStringF,           //  typeBoolean
        OpLessThan_StringStringF,           //  typeInteger
        OpLessThan_StringStringF,           //  typeReal
        OpLessThan_StringStringF,           //  typeString
        OpLessThan_TypeNotSupportedF,       //  typeArray
        OpLessThan_TypeNotSupportedF,       //  typeDictionary
        OpLessThan_TypeNotSupportedF,       //  typeStructure
        OpLessThan_TypeNotSupportedF        //  typeExecutable
    },
    
    //  typeArray
    {
        OpLessThan_TypeNotSupportedF,       //  typeNull
        OpLessThan_TypeNotSupportedF,       //  typeType
        OpLessThan_TypeNotSupportedF,       //  typeBoolean
        OpLessThan_TypeNotSupportedF,       //  typeInteger
        OpLessThan_TypeNotSupportedF,       //  typeReal
        OpLessThan_TypeNotSupportedF,       //  typeString
        OpLessThan_TypeNotSupportedF,       //  typeArray
        OpLessThan_TypeNotSupportedF,       //  typeDictionary
        OpLessThan_TypeNotSupportedF,       //  typeStructure
        OpLessThan_TypeNotSupportedF        //  typeExecutable
    },
    
    //  typeDictionary
    {
        OpLessThan_TypeNotSupportedF,       //  typeNull
        OpLessThan_TypeNotSupportedF,       //  typeType
        OpLessThan_TypeNotSupportedF,       //  typeBoolean
        OpLessThan_TypeNotSupportedF,       //  typeInteger
        OpLessThan_TypeNotSupportedF,       //  typeReal
        OpLessThan_TypeNotSupportedF,       //  typeString
        OpLessThan_TypeNotSupportedF,       //  typeArray
        OpLessThan_TypeNotSupportedF,       //  typeDictionary
        OpLessThan_TypeNotSupportedF,       //  typeStructure
        OpLessThan_TypeNotSupportedF        //  typeExecutable
    },
    
    //  typeStructure
    {
        OpLessThan_TypeNotSupportedF,       //  typeNull
        OpLessThan_TypeNotSupportedF,       //  typeType
        OpLessThan_TypeNotSupportedF,       //  typeBoolean
        OpLessThan_TypeNotSupportedF,       //  typeInteger
        OpLessThan_TypeNotSupportedF,       //  typeReal
        OpLessThan_TypeNotSupportedF,       //  typeString
        OpLessThan_TypeNotSupportedF,       //  typeArray
        OpLessThan_TypeNotSupportedF,       //  typeDictionary
        OpLessThan_TypeNotSupportedF,       //  typeStructure
        OpLessThan_TypeNotSupportedF        //  typeExecutable
    },
    
    //  typeExecutable
    {
        OpLessThan_TypeNotSupportedF,       //  typeNull
        OpLessThan_TypeNotSupportedF,       //  typeType
        OpLessThan_TypeNotSupportedF,       //  typeBoolean
        OpLessThan_TypeNotSupportedF,       //  typeInteger
        OpLessThan_TypeNotSupportedF,       //  typeReal
        OpLessThan_TypeNotSupportedF,       //  typeString
        OpLessThan_TypeNotSupportedF,       //  typeArray
        OpLessThan_TypeNotSupportedF,       //  typeDictionary
        OpLessThan_TypeNotSupportedF,       //  typeStructure
        OpLessThan_TypeNotSupportedF        //  typeExecutable
    }
};

////////////////////////////////////////////////////////////////////////////////

namespace
{
    
    bool OpLessThanOrEqual_TypeNotSupportedF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        std::stringstream message;
        message << "Illegal operation: <";
        message << TypeToString(arg1.Type());
        message << "> <= <";
        message << TypeToString(arg2.Type());
        message << ">.";
                
        throw dish::IllegalOperationException(message.str());
    }
    
    bool OpLessThanOrEqual_IntegerIntegerF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        return (arg1.AsInteger() <= arg2.AsInteger());
    }
    
    bool OpLessThanOrEqual_RealRealF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        const dish::RealT arg1_value(arg1.AsReal());
        const dish::RealT arg2_value(arg2.AsReal());
        
        return ((arg1_value <= arg2_value) || dish::IsEqual(arg1_value, arg2_value));
    }
    
    bool OpLessThanOrEqual_StringStringF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        return (arg1.AsString() <= arg2.AsString());
    }

}
    
const dish::TwoArgBoolOpF dish::OpLessThanOrEqual_FuncTable[dish::iAtomic::typeNUM][dish::iAtomic::typeNUM] =
{
    //  typeNull
    {
        OpLessThanOrEqual_TypeNotSupportedF,//  typeNull
        OpLessThanOrEqual_TypeNotSupportedF,//  typeType
        OpLessThanOrEqual_TypeNotSupportedF,//  typeBoolean
        OpLessThanOrEqual_TypeNotSupportedF,//  typeInteger
        OpLessThanOrEqual_TypeNotSupportedF,//  typeReal
        OpLessThanOrEqual_TypeNotSupportedF,//  typeString
        OpLessThanOrEqual_TypeNotSupportedF,//  typeArray
        OpLessThanOrEqual_TypeNotSupportedF,//  typeDictionary
        OpLessThanOrEqual_TypeNotSupportedF,//  typeStructure
        OpLessThanOrEqual_TypeNotSupportedF //  typeExecutable
    },
    
    //  typeType
    {
        OpLessThanOrEqual_TypeNotSupportedF,//  typeNull
        OpLessThanOrEqual_TypeNotSupportedF,//  typeType
        OpLessThanOrEqual_TypeNotSupportedF,//  typeBoolean
        OpLessThanOrEqual_TypeNotSupportedF,//  typeInteger
        OpLessThanOrEqual_TypeNotSupportedF,//  typeReal
        OpLessThanOrEqual_TypeNotSupportedF,//  typeString
        OpLessThanOrEqual_TypeNotSupportedF,//  typeArray
        OpLessThanOrEqual_TypeNotSupportedF,//  typeDictionary
        OpLessThanOrEqual_TypeNotSupportedF,//  typeStructure
        OpLessThanOrEqual_TypeNotSupportedF //  typeExecutable
    },
    
    //  typeBoolean
    {
        OpLessThanOrEqual_TypeNotSupportedF,//  typeNull
        OpLessThanOrEqual_TypeNotSupportedF,//  typeType
        OpLessThanOrEqual_IntegerIntegerF,  //  typeBoolean
        OpLessThanOrEqual_IntegerIntegerF,  //  typeInteger
        OpLessThanOrEqual_RealRealF,        //  typeReal
        OpLessThanOrEqual_StringStringF,    //  typeString
        OpLessThanOrEqual_TypeNotSupportedF,//  typeArray
        OpLessThanOrEqual_TypeNotSupportedF,//  typeDictionary
        OpLessThanOrEqual_TypeNotSupportedF,//  typeStructure
        OpLessThanOrEqual_TypeNotSupportedF //  typeExecutable
    },
    
    //  typeInteger
    {
        OpLessThanOrEqual_TypeNotSupportedF,//  typeNull
        OpLessThanOrEqual_TypeNotSupportedF,//  typeType
        OpLessThanOrEqual_IntegerIntegerF,  //  typeBoolean
        OpLessThanOrEqual_IntegerIntegerF,  //  typeInteger
        OpLessThanOrEqual_RealRealF,        //  typeReal
        OpLessThanOrEqual_StringStringF,    //  typeString
        OpLessThanOrEqual_TypeNotSupportedF,//  typeArray
        OpLessThanOrEqual_TypeNotSupportedF,//  typeDictionary
        OpLessThanOrEqual_TypeNotSupportedF,//  typeStructure
        OpLessThanOrEqual_TypeNotSupportedF //  typeExecutable
    },
    
    //  typeReal
    {
        OpLessThanOrEqual_TypeNotSupportedF,//  typeNull
        OpLessThanOrEqual_TypeNotSupportedF,//  typeType
        OpLessThanOrEqual_RealRealF,        //  typeBoolean
        OpLessThanOrEqual_RealRealF,        //  typeInteger
        OpLessThanOrEqual_RealRealF,        //  typeReal
        OpLessThanOrEqual_RealRealF,        //  typeString
        OpLessThanOrEqual_TypeNotSupportedF,//  typeArray
        OpLessThanOrEqual_TypeNotSupportedF,//  typeDictionary
        OpLessThanOrEqual_TypeNotSupportedF,//  typeStructure
        OpLessThanOrEqual_TypeNotSupportedF //  typeExecutable
    },
    
    //  typeString
    {
        OpLessThanOrEqual_TypeNotSupportedF,//  typeNull
        OpLessThanOrEqual_TypeNotSupportedF,//  typeType
        OpLessThanOrEqual_StringStringF,    //  typeBoolean
        OpLessThanOrEqual_StringStringF,    //  typeInteger
        OpLessThanOrEqual_StringStringF,    //  typeReal
        OpLessThanOrEqual_StringStringF,    //  typeString
        OpLessThanOrEqual_TypeNotSupportedF,//  typeArray
        OpLessThanOrEqual_TypeNotSupportedF,//  typeDictionary
        OpLessThanOrEqual_TypeNotSupportedF,//  typeStructure
        OpLessThanOrEqual_TypeNotSupportedF //  typeExecutable
    },
    
    //  typeArray
    {
        OpLessThanOrEqual_TypeNotSupportedF,//  typeNull
        OpLessThanOrEqual_TypeNotSupportedF,//  typeType
        OpLessThanOrEqual_TypeNotSupportedF,//  typeBoolean
        OpLessThanOrEqual_TypeNotSupportedF,//  typeInteger
        OpLessThanOrEqual_TypeNotSupportedF,//  typeReal
        OpLessThanOrEqual_TypeNotSupportedF,//  typeString
        OpLessThanOrEqual_TypeNotSupportedF,//  typeArray
        OpLessThanOrEqual_TypeNotSupportedF,//  typeDictionary
        OpLessThanOrEqual_TypeNotSupportedF,//  typeStructure
        OpLessThanOrEqual_TypeNotSupportedF //  typeExecutable
    },
    
    //  typeDictionary
    {
        OpLessThanOrEqual_TypeNotSupportedF,//  typeNull
        OpLessThanOrEqual_TypeNotSupportedF,//  typeType
        OpLessThanOrEqual_TypeNotSupportedF,//  typeBoolean
        OpLessThanOrEqual_TypeNotSupportedF,//  typeInteger
        OpLessThanOrEqual_TypeNotSupportedF,//  typeReal
        OpLessThanOrEqual_TypeNotSupportedF,//  typeString
        OpLessThanOrEqual_TypeNotSupportedF,//  typeArray
        OpLessThanOrEqual_TypeNotSupportedF,//  typeDictionary
        OpLessThanOrEqual_TypeNotSupportedF,//  typeStructure
        OpLessThanOrEqual_TypeNotSupportedF //  typeExecutable
    },
    
    //  typeStructure
    {
        OpLessThanOrEqual_TypeNotSupportedF,//  typeNull
        OpLessThanOrEqual_TypeNotSupportedF,//  typeType
        OpLessThanOrEqual_TypeNotSupportedF,//  typeBoolean
        OpLessThanOrEqual_TypeNotSupportedF,//  typeInteger
        OpLessThanOrEqual_TypeNotSupportedF,//  typeReal
        OpLessThanOrEqual_TypeNotSupportedF,//  typeString
        OpLessThanOrEqual_TypeNotSupportedF,//  typeArray
        OpLessThanOrEqual_TypeNotSupportedF,//  typeDictionary
        OpLessThanOrEqual_TypeNotSupportedF,//  typeStructure
        OpLessThanOrEqual_TypeNotSupportedF //  typeExecutable
    },
    
    //  typeExecutable
    {
        OpLessThanOrEqual_TypeNotSupportedF,//  typeNull
        OpLessThanOrEqual_TypeNotSupportedF,//  typeType
        OpLessThanOrEqual_TypeNotSupportedF,//  typeBoolean
        OpLessThanOrEqual_TypeNotSupportedF,//  typeInteger
        OpLessThanOrEqual_TypeNotSupportedF,//  typeReal
        OpLessThanOrEqual_TypeNotSupportedF,//  typeString
        OpLessThanOrEqual_TypeNotSupportedF,//  typeArray
        OpLessThanOrEqual_TypeNotSupportedF,//  typeDictionary
        OpLessThanOrEqual_TypeNotSupportedF,//  typeStructure
        OpLessThanOrEqual_TypeNotSupportedF //  typeExecutable
    }
};

////////////////////////////////////////////////////////////////////////////////

namespace
{
    
    bool OpEqual_TypeNotSupportedF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        std::stringstream message;
        message << "Illegal operation: <";
        message << TypeToString(arg1.Type());
        message << "> == <";
        message << TypeToString(arg2.Type());
        message << ">.";
                
        throw dish::IllegalOperationException(message.str());
    }
    
    bool OpEqual_IntegerIntegerF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        return (arg1.AsInteger() == arg2.AsInteger());
    }
    
    bool OpEqual_RealRealF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        return dish::IsEqual(arg1.AsReal(), arg2.AsReal());
    }
    
    bool OpEqual_StringStringF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        return (arg1.AsString() == arg2.AsString());
    }

}
    
const dish::TwoArgBoolOpF dish::OpEqual_FuncTable[dish::iAtomic::typeNUM][dish::iAtomic::typeNUM] =
{
    //  typeNull
    {
        OpEqual_TypeNotSupportedF,          //  typeNull
        OpEqual_TypeNotSupportedF,          //  typeType
        OpEqual_TypeNotSupportedF,          //  typeBoolean
        OpEqual_TypeNotSupportedF,          //  typeInteger
        OpEqual_TypeNotSupportedF,          //  typeReal
        OpEqual_TypeNotSupportedF,          //  typeString
        OpEqual_TypeNotSupportedF,          //  typeArray
        OpEqual_TypeNotSupportedF,          //  typeDictionary
        OpEqual_TypeNotSupportedF,          //  typeStructure
        OpEqual_TypeNotSupportedF           //  typeExecutable
    },
    
    //  typeType
    {
        OpEqual_TypeNotSupportedF,          //  typeNull
        OpEqual_TypeNotSupportedF,          //  typeType
        OpEqual_TypeNotSupportedF,          //  typeBoolean
        OpEqual_TypeNotSupportedF,          //  typeInteger
        OpEqual_TypeNotSupportedF,          //  typeReal
        OpEqual_TypeNotSupportedF,          //  typeString
        OpEqual_TypeNotSupportedF,          //  typeArray
        OpEqual_TypeNotSupportedF,          //  typeDictionary
        OpEqual_TypeNotSupportedF,          //  typeStructure
        OpEqual_TypeNotSupportedF           //  typeExecutable
    },
    
    //  typeBoolean
    {
        OpEqual_TypeNotSupportedF,          //  typeNull
        OpEqual_TypeNotSupportedF,          //  typeType
        OpEqual_IntegerIntegerF,            //  typeBoolean
        OpEqual_IntegerIntegerF,            //  typeInteger
        OpEqual_RealRealF,                  //  typeReal
        OpEqual_StringStringF,              //  typeString
        OpEqual_TypeNotSupportedF,          //  typeArray
        OpEqual_TypeNotSupportedF,          //  typeDictionary
        OpEqual_TypeNotSupportedF,          //  typeStructure
        OpEqual_TypeNotSupportedF           //  typeExecutable
    },
    
    //  typeInteger
    {
        OpEqual_TypeNotSupportedF,          //  typeNull
        OpEqual_TypeNotSupportedF,          //  typeType
        OpEqual_IntegerIntegerF,            //  typeBoolean
        OpEqual_IntegerIntegerF,            //  typeInteger
        OpEqual_RealRealF,                  //  typeReal
        OpEqual_StringStringF,              //  typeString
        OpEqual_TypeNotSupportedF,          //  typeArray
        OpEqual_TypeNotSupportedF,          //  typeDictionary
        OpEqual_TypeNotSupportedF,          //  typeStructure
        OpEqual_TypeNotSupportedF           //  typeExecutable
    },
    
    //  typeReal
    {
        OpEqual_TypeNotSupportedF,          //  typeNull
        OpEqual_TypeNotSupportedF,          //  typeType
        OpEqual_RealRealF,                  //  typeBoolean
        OpEqual_RealRealF,                  //  typeInteger
        OpEqual_RealRealF,                  //  typeReal
        OpEqual_RealRealF,                  //  typeString
        OpEqual_TypeNotSupportedF,          //  typeArray
        OpEqual_TypeNotSupportedF,          //  typeDictionary
        OpEqual_TypeNotSupportedF,          //  typeStructure
        OpEqual_TypeNotSupportedF           //  typeExecutable
    },
    
    //  typeString
    {
        OpEqual_TypeNotSupportedF,          //  typeNull
        OpEqual_TypeNotSupportedF,          //  typeType
        OpEqual_StringStringF,              //  typeBoolean
        OpEqual_StringStringF,              //  typeInteger
        OpEqual_StringStringF,              //  typeReal
        OpEqual_StringStringF,              //  typeString
        OpEqual_TypeNotSupportedF,          //  typeArray
        OpEqual_TypeNotSupportedF,          //  typeDictionary
        OpEqual_TypeNotSupportedF,          //  typeStructure
        OpEqual_TypeNotSupportedF           //  typeExecutable
    },
    
    //  typeArray
    {
        OpEqual_TypeNotSupportedF,          //  typeNull
        OpEqual_TypeNotSupportedF,          //  typeType
        OpEqual_TypeNotSupportedF,          //  typeBoolean
        OpEqual_TypeNotSupportedF,          //  typeInteger
        OpEqual_TypeNotSupportedF,          //  typeReal
        OpEqual_TypeNotSupportedF,          //  typeString
        OpEqual_TypeNotSupportedF,          //  typeArray
        OpEqual_TypeNotSupportedF,          //  typeDictionary
        OpEqual_TypeNotSupportedF,          //  typeStructure
        OpEqual_TypeNotSupportedF           //  typeExecutable
    },
    
    //  typeDictionary
    {
        OpEqual_TypeNotSupportedF,          //  typeNull
        OpEqual_TypeNotSupportedF,          //  typeType
        OpEqual_TypeNotSupportedF,          //  typeBoolean
        OpEqual_TypeNotSupportedF,          //  typeInteger
        OpEqual_TypeNotSupportedF,          //  typeReal
        OpEqual_TypeNotSupportedF,          //  typeString
        OpEqual_TypeNotSupportedF,          //  typeArray
        OpEqual_TypeNotSupportedF,          //  typeDictionary
        OpEqual_TypeNotSupportedF,          //  typeStructure
        OpEqual_TypeNotSupportedF           //  typeExecutable
    },
    
    //  typeStructure
    {
        OpEqual_TypeNotSupportedF,          //  typeNull
        OpEqual_TypeNotSupportedF,          //  typeType
        OpEqual_TypeNotSupportedF,          //  typeBoolean
        OpEqual_TypeNotSupportedF,          //  typeInteger
        OpEqual_TypeNotSupportedF,          //  typeReal
        OpEqual_TypeNotSupportedF,          //  typeString
        OpEqual_TypeNotSupportedF,          //  typeArray
        OpEqual_TypeNotSupportedF,          //  typeDictionary
        OpEqual_TypeNotSupportedF,          //  typeStructure
        OpEqual_TypeNotSupportedF           //  typeExecutable
    },
    
    //  typeExecutable
    {
        OpEqual_TypeNotSupportedF,          //  typeNull
        OpEqual_TypeNotSupportedF,          //  typeType
        OpEqual_TypeNotSupportedF,          //  typeBoolean
        OpEqual_TypeNotSupportedF,          //  typeInteger
        OpEqual_TypeNotSupportedF,          //  typeReal
        OpEqual_TypeNotSupportedF,          //  typeString
        OpEqual_TypeNotSupportedF,          //  typeArray
        OpEqual_TypeNotSupportedF,          //  typeDictionary
        OpEqual_TypeNotSupportedF,          //  typeStructure
        OpEqual_TypeNotSupportedF           //  typeExecutable
    }
};

////////////////////////////////////////////////////////////////////////////////

namespace
{
    
    bool OpNotEqual_TypeNotSupportedF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        std::stringstream message;
        message << "Illegal operation: <";
        message << TypeToString(arg1.Type());
        message << "> != <";
        message << TypeToString(arg2.Type());
        message << ">.";
                
        throw dish::IllegalOperationException(message.str());
    }
    
    bool OpNotEqual_IntegerIntegerF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        return (arg1.AsInteger() != arg2.AsInteger());
    }
    
    bool OpNotEqual_RealRealF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        return !dish::IsEqual(arg1.AsReal(), arg2.AsReal());
    }
    
    bool OpNotEqual_StringStringF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        return (arg1.AsString() != arg2.AsString());
    }

}

const dish::TwoArgBoolOpF dish::OpNotEqual_FuncTable[dish::iAtomic::typeNUM][dish::iAtomic::typeNUM] =
{
    //  typeNull
    {
        OpNotEqual_TypeNotSupportedF,       //  typeNull
        OpNotEqual_TypeNotSupportedF,       //  typeType
        OpNotEqual_TypeNotSupportedF,       //  typeBoolean
        OpNotEqual_TypeNotSupportedF,       //  typeInteger
        OpNotEqual_TypeNotSupportedF,       //  typeReal
        OpNotEqual_TypeNotSupportedF,       //  typeString
        OpNotEqual_TypeNotSupportedF,       //  typeArray
        OpNotEqual_TypeNotSupportedF,       //  typeDictionary
        OpNotEqual_TypeNotSupportedF,       //  typeStructure
        OpNotEqual_TypeNotSupportedF        //  typeExecutable
    },
    
    //  typeType
    {
        OpNotEqual_TypeNotSupportedF,       //  typeNull
        OpNotEqual_TypeNotSupportedF,       //  typeType
        OpNotEqual_TypeNotSupportedF,       //  typeBoolean
        OpNotEqual_TypeNotSupportedF,       //  typeInteger
        OpNotEqual_TypeNotSupportedF,       //  typeReal
        OpNotEqual_TypeNotSupportedF,       //  typeString
        OpNotEqual_TypeNotSupportedF,       //  typeArray
        OpNotEqual_TypeNotSupportedF,       //  typeDictionary
        OpNotEqual_TypeNotSupportedF,       //  typeStructure
        OpNotEqual_TypeNotSupportedF        //  typeExecutable
    },
    
    //  typeBoolean
    {
        OpNotEqual_TypeNotSupportedF,       //  typeNull
        OpNotEqual_TypeNotSupportedF,       //  typeType
        OpNotEqual_IntegerIntegerF,         //  typeBoolean
        OpNotEqual_IntegerIntegerF,         //  typeInteger
        OpNotEqual_RealRealF,               //  typeReal
        OpNotEqual_StringStringF,           //  typeString
        OpNotEqual_TypeNotSupportedF,       //  typeArray
        OpNotEqual_TypeNotSupportedF,       //  typeDictionary
        OpNotEqual_TypeNotSupportedF,       //  typeStructure
        OpNotEqual_TypeNotSupportedF        //  typeExecutable
    },
    
    //  typeInteger
    {
        OpNotEqual_TypeNotSupportedF,       //  typeNull
        OpNotEqual_TypeNotSupportedF,       //  typeType
        OpNotEqual_IntegerIntegerF,         //  typeBoolean
        OpNotEqual_IntegerIntegerF,         //  typeInteger
        OpNotEqual_RealRealF,               //  typeReal
        OpNotEqual_StringStringF,           //  typeString
        OpNotEqual_TypeNotSupportedF,       //  typeArray
        OpNotEqual_TypeNotSupportedF,       //  typeDictionary
        OpNotEqual_TypeNotSupportedF,       //  typeStructure
        OpNotEqual_TypeNotSupportedF        //  typeExecutable
    },
    
    //  typeReal
    {
        OpNotEqual_TypeNotSupportedF,       //  typeNull
        OpNotEqual_TypeNotSupportedF,       //  typeType
        OpNotEqual_RealRealF,               //  typeBoolean
        OpNotEqual_RealRealF,               //  typeInteger
        OpNotEqual_RealRealF,               //  typeReal
        OpNotEqual_RealRealF,               //  typeString
        OpNotEqual_TypeNotSupportedF,       //  typeArray
        OpNotEqual_TypeNotSupportedF,       //  typeDictionary
        OpNotEqual_TypeNotSupportedF,       //  typeStructure
        OpNotEqual_TypeNotSupportedF        //  typeExecutable
    },
    
    //  typeString
    {
        OpNotEqual_TypeNotSupportedF,       //  typeNull
        OpNotEqual_TypeNotSupportedF,       //  typeType
        OpNotEqual_StringStringF,           //  typeBoolean
        OpNotEqual_StringStringF,           //  typeInteger
        OpNotEqual_StringStringF,           //  typeReal
        OpNotEqual_StringStringF,           //  typeString
        OpNotEqual_TypeNotSupportedF,       //  typeArray
        OpNotEqual_TypeNotSupportedF,       //  typeDictionary
        OpNotEqual_TypeNotSupportedF,       //  typeStructure
        OpNotEqual_TypeNotSupportedF        //  typeExecutable
    },
    
    //  typeArray
    {
        OpNotEqual_TypeNotSupportedF,       //  typeNull
        OpNotEqual_TypeNotSupportedF,       //  typeType
        OpNotEqual_TypeNotSupportedF,       //  typeBoolean
        OpNotEqual_TypeNotSupportedF,       //  typeInteger
        OpNotEqual_TypeNotSupportedF,       //  typeReal
        OpNotEqual_TypeNotSupportedF,       //  typeString
        OpNotEqual_TypeNotSupportedF,       //  typeArray
        OpNotEqual_TypeNotSupportedF,       //  typeDictionary
        OpNotEqual_TypeNotSupportedF,       //  typeStructure
        OpNotEqual_TypeNotSupportedF        //  typeExecutable
    },
    
    //  typeDictionary
    {
        OpNotEqual_TypeNotSupportedF,       //  typeNull
        OpNotEqual_TypeNotSupportedF,       //  typeType
        OpNotEqual_TypeNotSupportedF,       //  typeBoolean
        OpNotEqual_TypeNotSupportedF,       //  typeInteger
        OpNotEqual_TypeNotSupportedF,       //  typeReal
        OpNotEqual_TypeNotSupportedF,       //  typeString
        OpNotEqual_TypeNotSupportedF,       //  typeArray
        OpNotEqual_TypeNotSupportedF,       //  typeDictionary
        OpNotEqual_TypeNotSupportedF,       //  typeStructure
        OpNotEqual_TypeNotSupportedF        //  typeExecutable
    },
    
    //  typeStructure
    {
        OpNotEqual_TypeNotSupportedF,       //  typeNull
        OpNotEqual_TypeNotSupportedF,       //  typeType
        OpNotEqual_TypeNotSupportedF,       //  typeBoolean
        OpNotEqual_TypeNotSupportedF,       //  typeInteger
        OpNotEqual_TypeNotSupportedF,       //  typeReal
        OpNotEqual_TypeNotSupportedF,       //  typeString
        OpNotEqual_TypeNotSupportedF,       //  typeArray
        OpNotEqual_TypeNotSupportedF,       //  typeDictionary
        OpNotEqual_TypeNotSupportedF,       //  typeStructure
        OpNotEqual_TypeNotSupportedF        //  typeExecutable
    },
    
    //  typeExecutable
    {
        OpNotEqual_TypeNotSupportedF,       //  typeNull
        OpNotEqual_TypeNotSupportedF,       //  typeType
        OpNotEqual_TypeNotSupportedF,       //  typeBoolean
        OpNotEqual_TypeNotSupportedF,       //  typeInteger
        OpNotEqual_TypeNotSupportedF,       //  typeReal
        OpNotEqual_TypeNotSupportedF,       //  typeString
        OpNotEqual_TypeNotSupportedF,       //  typeArray
        OpNotEqual_TypeNotSupportedF,       //  typeDictionary
        OpNotEqual_TypeNotSupportedF,       //  typeStructure
        OpNotEqual_TypeNotSupportedF        //  typeExecutable
    }
};

////////////////////////////////////////////////////////////////////////////////

namespace
{
    
    bool OpGreaterThanOrEqual_TypeNotSupportedF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        std::stringstream message;
        message << "Illegal operation: <";
        message << TypeToString(arg1.Type());
        message << "> >= <";
        message << TypeToString(arg2.Type());
        message << ">.";
                
        throw dish::IllegalOperationException(message.str());
    }
    
    bool OpGreaterThanOrEqual_IntegerIntegerF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        return (arg1.AsInteger() >= arg2.AsInteger());
    }
    
    bool OpGreaterThanOrEqual_RealRealF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        const dish::RealT arg1_value(arg1.AsReal());
        const dish::RealT arg2_value(arg2.AsReal());
        
        return ((arg1_value >= arg2_value) || dish::IsEqual(arg1_value, arg2_value));
    }
    
    bool OpGreaterThanOrEqual_StringStringF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        return (arg1.AsString() >= arg2.AsString());
    }

}
    
const dish::TwoArgBoolOpF dish::OpGreaterThanOrEqual_FuncTable[dish::iAtomic::typeNUM][dish::iAtomic::typeNUM] =
{
    //  typeNull
    {
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeNull
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeType
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeBoolean
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeInteger
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeReal
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeString
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeArray
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeDictionary
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeStructure
        OpGreaterThanOrEqual_TypeNotSupportedF //  typeExecutable
    },
    
    //  typeType
    {
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeNull
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeType
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeBoolean
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeInteger
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeReal
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeString
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeArray
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeDictionary
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeStructure
        OpGreaterThanOrEqual_TypeNotSupportedF //  typeExecutable
    },
    
    //  typeBoolean
    {
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeNull
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeType
        OpGreaterThanOrEqual_IntegerIntegerF,  //  typeBoolean
        OpGreaterThanOrEqual_IntegerIntegerF,  //  typeInteger
        OpGreaterThanOrEqual_RealRealF,        //  typeReal
        OpGreaterThanOrEqual_StringStringF,    //  typeString
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeArray
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeDictionary
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeStructure
        OpGreaterThanOrEqual_TypeNotSupportedF //  typeExecutable
    },
    
    //  typeInteger
    {
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeNull
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeType
        OpGreaterThanOrEqual_IntegerIntegerF,  //  typeBoolean
        OpGreaterThanOrEqual_IntegerIntegerF,  //  typeInteger
        OpGreaterThanOrEqual_RealRealF,        //  typeReal
        OpGreaterThanOrEqual_StringStringF,    //  typeString
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeArray
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeDictionary
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeStructure
        OpGreaterThanOrEqual_TypeNotSupportedF //  typeExecutable
    },
    
    //  typeReal
    {
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeNull
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeType
        OpGreaterThanOrEqual_RealRealF,        //  typeBoolean
        OpGreaterThanOrEqual_RealRealF,        //  typeInteger
        OpGreaterThanOrEqual_RealRealF,        //  typeReal
        OpGreaterThanOrEqual_RealRealF,        //  typeString
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeArray
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeDictionary
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeStructure
        OpGreaterThanOrEqual_TypeNotSupportedF //  typeExecutable
    },
    
    //  typeString
    {
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeNull
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeType
        OpGreaterThanOrEqual_StringStringF,    //  typeBoolean
        OpGreaterThanOrEqual_StringStringF,    //  typeInteger
        OpGreaterThanOrEqual_StringStringF,    //  typeReal
        OpGreaterThanOrEqual_StringStringF,    //  typeString
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeArray
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeDictionary
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeStructure
        OpGreaterThanOrEqual_TypeNotSupportedF //  typeExecutable
    },
    
    //  typeArray
    {
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeNull
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeType
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeBoolean
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeInteger
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeReal
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeString
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeArray
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeDictionary
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeStructure
        OpGreaterThanOrEqual_TypeNotSupportedF //  typeExecutable
    },
    
    //  typeDictionary
    {
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeNull
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeType
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeBoolean
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeInteger
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeReal
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeString
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeArray
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeDictionary
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeStructure
        OpGreaterThanOrEqual_TypeNotSupportedF //  typeExecutable
    },
    
    //  typeStructure
    {
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeNull
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeType
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeBoolean
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeInteger
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeReal
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeString
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeArray
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeDictionary
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeStructure
        OpGreaterThanOrEqual_TypeNotSupportedF //  typeExecutable
    },
    
    //  typeExecutable
    {
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeNull
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeType
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeBoolean
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeInteger
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeReal
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeString
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeArray
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeDictionary
        OpGreaterThanOrEqual_TypeNotSupportedF,//  typeStructure
        OpGreaterThanOrEqual_TypeNotSupportedF //  typeExecutable
    }
};

////////////////////////////////////////////////////////////////////////////////

namespace
{
    
    bool OpGreaterThan_TypeNotSupportedF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        std::stringstream message;
        message << "Illegal operation: <";
        message << TypeToString(arg1.Type());
        message << "> > <";
        message << TypeToString(arg2.Type());
        message << ">.";
                
        throw dish::IllegalOperationException(message.str());
    }
    
    bool OpGreaterThan_IntegerIntegerF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        return (arg1.AsInteger() > arg2.AsInteger());
    }
    
    bool OpGreaterThan_RealRealF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        return (arg1.AsReal() > arg2.AsReal());
    }
    
    bool OpGreaterThan_StringStringF(const dish::iAtomic &arg1, const dish::iAtomic &arg2)
    {
        return (arg1.AsString() > arg2.AsString());
    }

}
    
const dish::TwoArgBoolOpF dish::OpGreaterThan_FuncTable[dish::iAtomic::typeNUM][dish::iAtomic::typeNUM] =
{
    //  typeNull
    {
        OpGreaterThan_TypeNotSupportedF,    //  typeNull
        OpGreaterThan_TypeNotSupportedF,    //  typeType
        OpGreaterThan_TypeNotSupportedF,    //  typeBoolean
        OpGreaterThan_TypeNotSupportedF,    //  typeInteger
        OpGreaterThan_TypeNotSupportedF,    //  typeReal
        OpGreaterThan_TypeNotSupportedF,    //  typeString
        OpGreaterThan_TypeNotSupportedF,    //  typeArray
        OpGreaterThan_TypeNotSupportedF,    //  typeDictionary
        OpGreaterThan_TypeNotSupportedF,    //  typeStructure
        OpGreaterThan_TypeNotSupportedF     //  typeExecutable
    },
    
    //  typeType
    {
        OpGreaterThan_TypeNotSupportedF,    //  typeNull
        OpGreaterThan_TypeNotSupportedF,    //  typeType
        OpGreaterThan_TypeNotSupportedF,    //  typeBoolean
        OpGreaterThan_TypeNotSupportedF,    //  typeInteger
        OpGreaterThan_TypeNotSupportedF,    //  typeReal
        OpGreaterThan_TypeNotSupportedF,    //  typeString
        OpGreaterThan_TypeNotSupportedF,    //  typeArray
        OpGreaterThan_TypeNotSupportedF,    //  typeDictionary
        OpGreaterThan_TypeNotSupportedF,    //  typeStructure
        OpGreaterThan_TypeNotSupportedF     //  typeExecutable
    },
    
    //  typeBoolean
    {
        OpGreaterThan_TypeNotSupportedF,    //  typeNull
        OpGreaterThan_TypeNotSupportedF,    //  typeType
        OpGreaterThan_IntegerIntegerF,      //  typeBoolean
        OpGreaterThan_IntegerIntegerF,      //  typeInteger
        OpGreaterThan_RealRealF,            //  typeReal
        OpGreaterThan_StringStringF,        //  typeString
        OpGreaterThan_TypeNotSupportedF,    //  typeArray
        OpGreaterThan_TypeNotSupportedF,    //  typeDictionary
        OpGreaterThan_TypeNotSupportedF,    //  typeStructure
        OpGreaterThan_TypeNotSupportedF     //  typeExecutable
    },
    
    //  typeInteger
    {
        OpGreaterThan_TypeNotSupportedF,    //  typeNull
        OpGreaterThan_TypeNotSupportedF,    //  typeType
        OpGreaterThan_IntegerIntegerF,      //  typeBoolean
        OpGreaterThan_IntegerIntegerF,      //  typeInteger
        OpGreaterThan_RealRealF,            //  typeReal
        OpGreaterThan_StringStringF,        //  typeString
        OpGreaterThan_TypeNotSupportedF,    //  typeArray
        OpGreaterThan_TypeNotSupportedF,    //  typeDictionary
        OpGreaterThan_TypeNotSupportedF,    //  typeStructure
        OpGreaterThan_TypeNotSupportedF     //  typeExecutable
    },
    
    //  typeReal
    {
        OpGreaterThan_TypeNotSupportedF,    //  typeNull
        OpGreaterThan_TypeNotSupportedF,    //  typeType
        OpGreaterThan_RealRealF,            //  typeBoolean
        OpGreaterThan_RealRealF,            //  typeInteger
        OpGreaterThan_RealRealF,            //  typeReal
        OpGreaterThan_RealRealF,            //  typeString
        OpGreaterThan_TypeNotSupportedF,    //  typeArray
        OpGreaterThan_TypeNotSupportedF,    //  typeDictionary
        OpGreaterThan_TypeNotSupportedF,    //  typeStructure
        OpGreaterThan_TypeNotSupportedF     //  typeExecutable
    },
    
    //  typeString
    {
        OpGreaterThan_TypeNotSupportedF,    //  typeNull
        OpGreaterThan_TypeNotSupportedF,    //  typeType
        OpGreaterThan_StringStringF,        //  typeBoolean
        OpGreaterThan_StringStringF,        //  typeInteger
        OpGreaterThan_StringStringF,        //  typeReal
        OpGreaterThan_StringStringF,        //  typeString
        OpGreaterThan_TypeNotSupportedF,    //  typeArray
        OpGreaterThan_TypeNotSupportedF,    //  typeDictionary
        OpGreaterThan_TypeNotSupportedF,    //  typeStructure
        OpGreaterThan_TypeNotSupportedF     //  typeExecutable
    },
    
    //  typeArray
    {
        OpGreaterThan_TypeNotSupportedF,    //  typeNull
        OpGreaterThan_TypeNotSupportedF,    //  typeType
        OpGreaterThan_TypeNotSupportedF,    //  typeBoolean
        OpGreaterThan_TypeNotSupportedF,    //  typeInteger
        OpGreaterThan_TypeNotSupportedF,    //  typeReal
        OpGreaterThan_TypeNotSupportedF,    //  typeString
        OpGreaterThan_TypeNotSupportedF,    //  typeArray
        OpGreaterThan_TypeNotSupportedF,    //  typeDictionary
        OpGreaterThan_TypeNotSupportedF,    //  typeStructure
        OpGreaterThan_TypeNotSupportedF     //  typeExecutable
    },
    
    //  typeDictionary
    {
        OpGreaterThan_TypeNotSupportedF,    //  typeNull
        OpGreaterThan_TypeNotSupportedF,    //  typeType
        OpGreaterThan_TypeNotSupportedF,    //  typeBoolean
        OpGreaterThan_TypeNotSupportedF,    //  typeInteger
        OpGreaterThan_TypeNotSupportedF,    //  typeReal
        OpGreaterThan_TypeNotSupportedF,    //  typeString
        OpGreaterThan_TypeNotSupportedF,    //  typeArray
        OpGreaterThan_TypeNotSupportedF,    //  typeDictionary
        OpGreaterThan_TypeNotSupportedF,    //  typeStructure
        OpGreaterThan_TypeNotSupportedF     //  typeExecutable
    },
    
    //  typeStructure
    {
        OpGreaterThan_TypeNotSupportedF,    //  typeNull
        OpGreaterThan_TypeNotSupportedF,    //  typeType
        OpGreaterThan_TypeNotSupportedF,    //  typeBoolean
        OpGreaterThan_TypeNotSupportedF,    //  typeInteger
        OpGreaterThan_TypeNotSupportedF,    //  typeReal
        OpGreaterThan_TypeNotSupportedF,    //  typeString
        OpGreaterThan_TypeNotSupportedF,    //  typeArray
        OpGreaterThan_TypeNotSupportedF,    //  typeDictionary
        OpGreaterThan_TypeNotSupportedF,    //  typeStructure
        OpGreaterThan_TypeNotSupportedF     //  typeExecutable
    },
    
    //  typeExecutable
    {
        OpGreaterThan_TypeNotSupportedF,    //  typeNull
        OpGreaterThan_TypeNotSupportedF,    //  typeType
        OpGreaterThan_TypeNotSupportedF,    //  typeBoolean
        OpGreaterThan_TypeNotSupportedF,    //  typeInteger
        OpGreaterThan_TypeNotSupportedF,    //  typeReal
        OpGreaterThan_TypeNotSupportedF,    //  typeString
        OpGreaterThan_TypeNotSupportedF,    //  typeArray
        OpGreaterThan_TypeNotSupportedF,    //  typeDictionary
        OpGreaterThan_TypeNotSupportedF,    //  typeStructure
        OpGreaterThan_TypeNotSupportedF     //  typeExecutable
    }
};

////////////////////////////////////////////////////////////////////////////////

std::string dish::TypeToString(const dish::iAtomic::TypeT type)
{
    switch(type)
    {
        case dish::iAtomic::typeNull:
        {
            return "null";
        }
                
        case dish::iAtomic::typeType:
        {
            return "type";
        }
                
        case dish::iAtomic::typeBoolean:
        {
            return "boolean";
        }
                
        case dish::iAtomic::typeInteger:
        {
            return "integer";
        }
                
        case dish::iAtomic::typeReal:
        {
            return "real";
        }
                
        case dish::iAtomic::typeString:
        {
            return "string";
        }
                
        case dish::iAtomic::typeArray:
        {
            return "array";
        }
        
        case dish::iAtomic::typeDictionary:
        {
            return "dictionary";
        }
                
        case dish::iAtomic::typeStructure:
        {
            return "structure";
        }
                
        case dish::iAtomic::typeExecutable:
        {
            return "executable";
        }
                
        default:
        {
            //  Empty
        }
        
    }
    
    assert(false);  
}

////////////////////////////////////////////////////////////////////////////////

