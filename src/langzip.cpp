/*
    This file is part of the DISH programming language, Copyright 2014-2018 by 
    Chris Buck.
    
    DISH is free software for non-commercial use: you can redistribute it and/or
    modify it provided
    
        (1) The following Copyright notice is displayed at runtime:
    
            DISH programming language copyright (c) 2014-2018 by Chris Buck.
        
        (2) All source files duplicate this copyright statement in full.
        
    Commercial licenses can be negotiated by contacting Chris Buck at
    chrisbuck1220@hotmail.com.

    DISH is distributed in the hope that it will be useful, but WITHOUT ANY 
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS 
    FOR A PARTICULAR PURPOSE.
*/

#include <algorithm>
#include <cassert>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "exception.h"
#include "langzip.h"
#include "utility.h"

namespace
{

    ////////////////////////////////////////////////////////////////////////////
    
    const size_t NUM_ZIPPABLE(10);
    
    const std::string Names[NUM_ZIPPABLE] =
    {
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine",
        "ten"
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class ZipFunctionF : public dish::iAtomic
    {
        public:
        
            using ZipT = std::vector< std::pair< bool, std::shared_ptr< dish::iAtomic > > >;
    
        private:
            ZipT mValue;
            
            std::shared_ptr< dish::iAtomic > mStart;
            std::shared_ptr< dish::iAtomic > mFinish;
            std::shared_ptr< dish::iAtomic > mLength;
    
        protected:
            INLINE ZipFunctionF() : dish::iAtomic(), mValue(), mStart(), mFinish(), mLength() {};
            
        public:
            
            static INLINE std::shared_ptr< ZipFunctionF > MakeValue() { return std::shared_ptr< ZipFunctionF >(new ZipFunctionF()); };
            
            void AddZippable(std::shared_ptr< dish::iAtomic > zipval);
                
            //  From iAtomic
            
            virtual dish::iAtomic::TypeT Type() const throw();
            virtual std::shared_ptr< dish::iAtomic > Copy() const;
            
            virtual std::shared_ptr< dish::iAtomic > Member(const std::string &member) const;
            
            virtual std::shared_ptr< dish::iAtomic > Element(const dish::IntegerT &index) const;
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
            
    };
    
    void ZipFunctionF::AddZippable(std::shared_ptr< dish::iAtomic > zipval)
    {
        if(typeArray == zipval->Type())
        {
            bool recompute_length(false);
        
            std::shared_ptr< iAtomic > start(zipval->Member("start"));
            if((0 == mStart.get()) || (*start < *mStart))
            {
                mStart = start;
                recompute_length = true;
            }
            
            std::shared_ptr< iAtomic > finish(zipval->Member("finish"));
            if((0 == mFinish.get()) || (*finish > *mFinish))
            {
                mFinish = finish;
                recompute_length = true;
            }
            
            if(recompute_length)
            {
                static std::shared_ptr< dish::iAtomic > one(dish::IntegerValue::MakeValue(1, dish::LOCKED));
                
                mLength = (mFinish - mStart + one);
            }
        
            mValue.push_back(std::make_pair(true, zipval));
        }
        else
        {
            mValue.push_back(std::make_pair(false, zipval));
        }
    }
    
    dish::iAtomic::TypeT ZipFunctionF::Type() const throw()
    {
        return dish::iAtomic::typeArray;
    }
    
    std::shared_ptr< dish::iAtomic > ZipFunctionF::Copy() const
    {
        std::shared_ptr< ZipFunctionF > copy(MakeValue());
        
        std::for_each(
            mValue.begin(), mValue.end(),
            [&](const ZipT::value_type &value)
            {
                copy->AddZippable(value.second->Copy());
            }
        );
        
        return copy;
    }
    
    std::shared_ptr< dish::iAtomic > ZipFunctionF::Member(const std::string &member) const
    {
        if(dish::IsEqual("start", member, dish::CASE_INSENSITIVE))
        {
            assert(0 != mStart.get());
            return mStart;
        }
        
        else if(dish::IsEqual("finish", member, dish::CASE_INSENSITIVE))
        {
            assert(0 != mFinish.get());
            return mFinish;
        }
        
        else if(dish::IsEqual("length", member, dish::CASE_INSENSITIVE))
        {
            assert(0 != mLength.get());
            return mLength;
        }
        
        else if(dish::IsEqual("empty", member, dish::CASE_INSENSITIVE))
        {
            return dish::BooleanValue::MakeLockedValue(mValue.empty());
        }

        return iAtomic::Member(member);
    }
    
    std::shared_ptr< dish::iAtomic > ZipFunctionF::Element(const dish::IntegerT &index) const
    {
        std::shared_ptr< dish::ArrayValue > arrayof(dish::ArrayValue::MakeValue(1));
        std::shared_ptr< dish::StructureValue > element(dish::StructureValue::MakeValue());
    
        ZipT::size_type nvalues(mValue.size());
        assert(nvalues <= NUM_ZIPPABLE);
        
        for(ZipT::size_type i(0); i < nvalues; ++i)
        {
            try
            {
                std::shared_ptr< dish::iAtomic > tmp(mValue[i].second->Element(index));
                
                arrayof->Add(tmp);
                element->Add(Names[i], tmp);
            }
            
            catch(dish::IllegalIndexException &e)
            {
                std::shared_ptr< dish::iAtomic > null(dish::NullValue::MakeValue());
            
                arrayof->Add(null);
                element->Add(Names[i], null);
            }
        }
        
        element->Add("arrayof", arrayof);
        
        return element;
    }
    
    void ZipFunctionF::Print(std::ostream &out, const std::string::size_type &indent) const
    {
        printIndent(out, indent);
        out << "Zip(" << std::endl;
        
        ZipT::const_iterator i(mValue.begin());
        const ZipT::const_iterator last_i(mValue.begin());
        
        if(i != last_i)
        {
            i->second->Print(out, indent + 4);
            
            while(++i != last_i)
            {
                out << "," << std::endl;
                i->second->Print(out, indent + 4);
            }
        }
        else
        {
            printIndent(out, indent + 4);
            out << "<empty>";
        }
        
        printIndent(out, indent);
        out << ")";
    }

    ////////////////////////////////////////////////////////////////////////////
    
    class ZipTogetherFunctionF : public dish::iAtomic
    {
        public:
        
            using ZipT = std::vector< std::pair< dish::IntegerT, std::shared_ptr< dish::iAtomic > > >;
    
        private:
            const dish::IntegerT mStartIndex;
            dish::IntegerT mFinishIndex;
        
            ZipT mValue;
    
        protected:
            INLINE ZipTogetherFunctionF(const dish::IntegerT &start) : dish::iAtomic(), mStartIndex(start), mFinishIndex(start - 1), mValue() {};
            
        public:
            
            static INLINE std::shared_ptr< ZipTogetherFunctionF > MakeValue(const dish::IntegerT &start) { return std::shared_ptr< ZipTogetherFunctionF >(new ZipTogetherFunctionF(start)); };
            
            void AddZippable(std::shared_ptr< dish::iAtomic > zipval);
                
            //  From iAtomic
            
            virtual dish::iAtomic::TypeT Type() const throw();
            virtual std::shared_ptr< dish::iAtomic > Copy() const;
            
            virtual std::shared_ptr< dish::iAtomic > Member(const std::string &member) const;
            
            virtual std::shared_ptr< dish::iAtomic > Element(const dish::IntegerT &index) const;
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
            
    };
    
    void ZipTogetherFunctionF::AddZippable(std::shared_ptr< dish::iAtomic > zipval)
    {
        if(typeArray == zipval->Type())
        {
            const dish::IntegerT finish(zipval->Member("length")->AsInteger() + mStartIndex - 1);
            if(finish > mFinishIndex)
            {
                mFinishIndex = finish;
            }
            
            mValue.push_back(
                std::make_pair(
                    zipval->Member("start")->AsInteger() - mStartIndex,
                    zipval
                )
            );
        }
        else
        {
            mValue.push_back(std::make_pair(0, zipval));
        }
    }
    
    dish::iAtomic::TypeT ZipTogetherFunctionF::Type() const throw()
    {
        return dish::iAtomic::typeArray;
    }
    
    std::shared_ptr< dish::iAtomic > ZipTogetherFunctionF::Copy() const
    {
        std::shared_ptr< ZipTogetherFunctionF > copy(MakeValue(mStartIndex));
        
        std::for_each(
            mValue.begin(), mValue.end(),
            [&](const ZipT::value_type &value)
            {
                copy->AddZippable(value.second->Copy());
            }
        );
        
        return copy;
    }
    
    std::shared_ptr< dish::iAtomic > ZipTogetherFunctionF::Member(const std::string &member) const
    {
        if(dish::IsEqual("start", member, dish::CASE_INSENSITIVE))
        {
            return dish::IntegerValue::MakeValue(mStartIndex, dish::LOCKED);
        }
        
        else if(dish::IsEqual("finish", member, dish::CASE_INSENSITIVE))
        {
            return dish::IntegerValue::MakeValue(mFinishIndex, dish::LOCKED);
        }
        
        else if(dish::IsEqual("length", member, dish::CASE_INSENSITIVE))
        {
            return dish::IntegerValue::MakeValue(mFinishIndex - mStartIndex + 1, dish::LOCKED);
        }
        
        else if(dish::IsEqual("empty", member, dish::CASE_INSENSITIVE))
        {
            return dish::BooleanValue::MakeLockedValue(mFinishIndex < mStartIndex);
        }

        return iAtomic::Member(member);
    }
    
    std::shared_ptr< dish::iAtomic > ZipTogetherFunctionF::Element(const dish::IntegerT &index) const
    {
        std::shared_ptr< dish::ArrayValue > arrayof(dish::ArrayValue::MakeValue(1));
        std::shared_ptr< dish::StructureValue > element(dish::StructureValue::MakeValue());
    
        ZipT::size_type nvalues(mValue.size());
        assert(nvalues <= NUM_ZIPPABLE);
        
        for(ZipT::size_type i(0); i < nvalues; ++i)
        {
            try
            {
                std::shared_ptr< dish::iAtomic > tmp(mValue[i].second->Element(index + mValue[i].first));
                
                arrayof->Add(tmp);
                element->Add(Names[i], tmp);
            }
            
            catch(dish::IllegalIndexException &e)
            {
                std::shared_ptr< dish::iAtomic > null(dish::NullValue::MakeValue());
            
                arrayof->Add(null);
                element->Add(Names[i], null);
            }
        }
        
        element->Add("arrayof", arrayof);
        
        return element;
    }
    
    void ZipTogetherFunctionF::Print(std::ostream &out, const std::string::size_type &indent) const
    {
        printIndent(out, indent);
        out << "ZipTogether(" << std::endl;
        
        printIndent(out, indent + 4);
        out << mStartIndex << "," << std::endl;
        
        ZipT::const_iterator i(mValue.begin());
        const ZipT::const_iterator last_i(mValue.begin());
        
        if(i != last_i)
        {
            i->second->Print(out, indent + 4);
            
            while(++i != last_i)
            {
                out << "," << std::endl;
                i->second->Print(out, indent + 4);
            }
        }
        else
        {
            printIndent(out, indent + 4);
            out << "<empty>";
        }
        
        printIndent(out, indent);
        out << ")";
    }

    ////////////////////////////////////////////////////////////////////////////
    
    class ZipValueFunctionF : public dish::iAtomic
    {
        private:
            std::shared_ptr< dish::iAtomic > mValue;
    
        protected:
            INLINE ZipValueFunctionF(std::shared_ptr< dish::iAtomic > &value) : dish::iAtomic(), mValue(value) { assert(0 != mValue.get()); };
            
        public:
            
            static INLINE std::shared_ptr< ZipValueFunctionF > MakeValue(std::shared_ptr< dish::iAtomic > value) { return std::shared_ptr< ZipValueFunctionF >(new ZipValueFunctionF(value)); };
                
            //  From iAtomic
            
            virtual dish::iAtomic::TypeT Type() const throw();
            virtual std::shared_ptr< dish::iAtomic > Copy() const;
            
            virtual std::shared_ptr< dish::iAtomic > Element(const dish::IntegerT &index) const;
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
            
    };
    
    dish::iAtomic::TypeT ZipValueFunctionF::Type() const throw()
    {
        return dish::iAtomic::typeExecutable;
    }
    
    std::shared_ptr< dish::iAtomic > ZipValueFunctionF::Copy() const
    {
        return ZipValueFunctionF::MakeValue(mValue);
    }
    
    std::shared_ptr< dish::iAtomic > ZipValueFunctionF::Element(const dish::IntegerT &index) const
    {
        return mValue;
    }
    
    void ZipValueFunctionF::Print(std::ostream &out, const std::string::size_type &indent) const
    {
        printIndent(out, indent);
        out << "ZipValue(";
        mValue->Print(out, 0);
        out << ")";
    }
    
    ////////////////////////////////////////////////////////////////////////////
    
    class ZipIndexOffsetFunctionF : public dish::iAtomic
    {
        private:
            const dish::IntegerT mOffset;
    
        protected:
            INLINE ZipIndexOffsetFunctionF(const dish::IntegerT &offset) : dish::iAtomic(), mOffset(offset) {};
            
        public:
            
            static INLINE std::shared_ptr< ZipIndexOffsetFunctionF > MakeValue(const dish::IntegerT &offset) { return std::shared_ptr< ZipIndexOffsetFunctionF >(new ZipIndexOffsetFunctionF(offset)); };
                
            //  From iAtomic
            
            virtual dish::iAtomic::TypeT Type() const throw();
            virtual std::shared_ptr< dish::iAtomic > Copy() const;
            
            virtual std::shared_ptr< dish::iAtomic > Element(const dish::IntegerT &index) const;
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
            
    };
    
    dish::iAtomic::TypeT ZipIndexOffsetFunctionF::Type() const throw()
    {
        return dish::iAtomic::typeExecutable;
    }
    
    std::shared_ptr< dish::iAtomic > ZipIndexOffsetFunctionF::Copy() const
    {
        return ZipIndexOffsetFunctionF::MakeValue(mOffset);
    }
    
    std::shared_ptr< dish::iAtomic > ZipIndexOffsetFunctionF::Element(const dish::IntegerT &index) const
    {
        return dish::IntegerValue::MakeValue(index + mOffset, dish::LOCKED);
    }
    
    void ZipIndexOffsetFunctionF::Print(std::ostream &out, const std::string::size_type &indent) const
    {
        printIndent(out, indent);
        out << "ZipIndexOffset(";
        out << mOffset;
        out << ")";
    }
    
    ////////////////////////////////////////////////////////////////////////////

}

/******************************************************************************

    dish::Zip1Function class definition

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::Zip1Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< ZipFunctionF > value(ZipFunctionF::MakeValue());
    
    value->AddZippable(getParam(symtab, "arg1"));
    
    return value;
}

/******************************************************************************

    dish::Zip2Function class definition

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::Zip2Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< ZipFunctionF > value(ZipFunctionF::MakeValue());
    
    value->AddZippable(getParam(symtab, "arg1"));
    value->AddZippable(getParam(symtab, "arg2"));
    
    return value;
}

/******************************************************************************

    dish::Zip3Function class definition

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::Zip3Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< ZipFunctionF > value(ZipFunctionF::MakeValue());
    
    value->AddZippable(getParam(symtab, "arg1"));
    value->AddZippable(getParam(symtab, "arg2"));
    value->AddZippable(getParam(symtab, "arg3"));
    
    return value;
}

/******************************************************************************

    dish::Zip4Function class definition

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::Zip4Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< ZipFunctionF > value(ZipFunctionF::MakeValue());
    
    value->AddZippable(getParam(symtab, "arg1"));
    value->AddZippable(getParam(symtab, "arg2"));
    value->AddZippable(getParam(symtab, "arg3"));
    value->AddZippable(getParam(symtab, "arg4"));
    
    return value;
}

/******************************************************************************

    dish::Zip5Function class definition

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::Zip5Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< ZipFunctionF > value(ZipFunctionF::MakeValue());
    
    value->AddZippable(getParam(symtab, "arg1"));
    value->AddZippable(getParam(symtab, "arg2"));
    value->AddZippable(getParam(symtab, "arg3"));
    value->AddZippable(getParam(symtab, "arg4"));
    value->AddZippable(getParam(symtab, "arg5"));
    
    return value;
}

/******************************************************************************

    dish::Zip6Function class definition

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::Zip6Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< ZipFunctionF > value(ZipFunctionF::MakeValue());
    
    value->AddZippable(getParam(symtab, "arg1"));
    value->AddZippable(getParam(symtab, "arg2"));
    value->AddZippable(getParam(symtab, "arg3"));
    value->AddZippable(getParam(symtab, "arg4"));
    value->AddZippable(getParam(symtab, "arg5"));
    value->AddZippable(getParam(symtab, "arg6"));
    
    return value;
}

/******************************************************************************

    dish::Zip7Function class definition

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::Zip7Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< ZipFunctionF > value(ZipFunctionF::MakeValue());
    
    value->AddZippable(getParam(symtab, "arg1"));
    value->AddZippable(getParam(symtab, "arg2"));
    value->AddZippable(getParam(symtab, "arg3"));
    value->AddZippable(getParam(symtab, "arg4"));
    value->AddZippable(getParam(symtab, "arg5"));
    value->AddZippable(getParam(symtab, "arg6"));
    value->AddZippable(getParam(symtab, "arg7"));
    
    return value;
}

/******************************************************************************

    dish::Zip8Function class definition

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::Zip8Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< ZipFunctionF > value(ZipFunctionF::MakeValue());
    
    value->AddZippable(getParam(symtab, "arg1"));
    value->AddZippable(getParam(symtab, "arg2"));
    value->AddZippable(getParam(symtab, "arg3"));
    value->AddZippable(getParam(symtab, "arg4"));
    value->AddZippable(getParam(symtab, "arg5"));
    value->AddZippable(getParam(symtab, "arg6"));
    value->AddZippable(getParam(symtab, "arg7"));
    value->AddZippable(getParam(symtab, "arg8"));
    

    return value;
}

/******************************************************************************

    dish::Zip9Function class definition

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::Zip9Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< ZipFunctionF > value(ZipFunctionF::MakeValue());
    
    value->AddZippable(getParam(symtab, "arg1"));
    value->AddZippable(getParam(symtab, "arg2"));
    value->AddZippable(getParam(symtab, "arg3"));
    value->AddZippable(getParam(symtab, "arg4"));
    value->AddZippable(getParam(symtab, "arg5"));
    value->AddZippable(getParam(symtab, "arg6"));
    value->AddZippable(getParam(symtab, "arg7"));
    value->AddZippable(getParam(symtab, "arg8"));
    value->AddZippable(getParam(symtab, "arg9"));
    
    return value;
}

/******************************************************************************

    dish::Zip10Function class definition

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::Zip10Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< ZipFunctionF > value(ZipFunctionF::MakeValue());
    
    value->AddZippable(getParam(symtab, "arg1"));
    value->AddZippable(getParam(symtab, "arg2"));
    value->AddZippable(getParam(symtab, "arg3"));
    value->AddZippable(getParam(symtab, "arg4"));
    value->AddZippable(getParam(symtab, "arg5"));
    value->AddZippable(getParam(symtab, "arg6"));
    value->AddZippable(getParam(symtab, "arg7"));
    value->AddZippable(getParam(symtab, "arg8"));
    value->AddZippable(getParam(symtab, "arg9"));
    value->AddZippable(getParam(symtab, "arg10"));
    
    return value;
}

/******************************************************************************

    dish::ZipTogether1Function class definition

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::ZipTogether1Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< dish::iAtomic > arg1(getParam(symtab, "arg1"));
    if(dish::iAtomic::typeInteger == arg1->Type())
    {
        throw IllegalParameterException("At least one array is needed to zip.");
    }

    std::shared_ptr< ZipTogetherFunctionF > value(ZipTogetherFunctionF::MakeValue(1));
    
    value->AddZippable(arg1);
    
    return value;
}

/******************************************************************************

    dish::ZipTogether2Function class definition

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::ZipTogether2Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< ZipTogetherFunctionF > value;

    std::shared_ptr< dish::iAtomic > arg1(getParam(symtab, "arg1"));
    if(dish::iAtomic::typeInteger != arg1->Type())
    {
        value = ZipTogetherFunctionF::MakeValue(1);
        value->AddZippable(arg1);
    }
    else
    {
        value = ZipTogetherFunctionF::MakeValue(arg1->AsInteger());
    }
    
    value->AddZippable(getParam(symtab, "arg2"));
    
    assert(0 != value.get());
    return value;
}

/******************************************************************************

    dish::ZipTogether3Function class definition

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::ZipTogether3Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< ZipTogetherFunctionF > value;

    std::shared_ptr< dish::iAtomic > arg1(getParam(symtab, "arg1"));
    if(dish::iAtomic::typeInteger != arg1->Type())
    {
        value = ZipTogetherFunctionF::MakeValue(1);
        value->AddZippable(arg1);
    }
    else
    {
        value = ZipTogetherFunctionF::MakeValue(arg1->AsInteger());
    }
    
    value->AddZippable(getParam(symtab, "arg2"));
    value->AddZippable(getParam(symtab, "arg3"));
    
    assert(0 != value.get());
    return value;
}

/******************************************************************************

    dish::ZipTogether4Function class definition

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::ZipTogether4Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< ZipTogetherFunctionF > value;

    std::shared_ptr< dish::iAtomic > arg1(getParam(symtab, "arg1"));
    if(dish::iAtomic::typeInteger != arg1->Type())
    {
        value = ZipTogetherFunctionF::MakeValue(1);
        value->AddZippable(arg1);
    }
    else
    {
        value = ZipTogetherFunctionF::MakeValue(arg1->AsInteger());
    }
    
    value->AddZippable(getParam(symtab, "arg2"));
    value->AddZippable(getParam(symtab, "arg3"));
    value->AddZippable(getParam(symtab, "arg4"));
    
    assert(0 != value.get());
    return value;
}

/******************************************************************************

    dish::ZipTogether5Function class definition

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::ZipTogether5Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< ZipTogetherFunctionF > value;

    std::shared_ptr< dish::iAtomic > arg1(getParam(symtab, "arg1"));
    if(dish::iAtomic::typeInteger != arg1->Type())
    {
        value = ZipTogetherFunctionF::MakeValue(1);
        value->AddZippable(arg1);
    }
    else
    {
        value = ZipTogetherFunctionF::MakeValue(arg1->AsInteger());
    }
    
    value->AddZippable(getParam(symtab, "arg2"));
    value->AddZippable(getParam(symtab, "arg3"));
    value->AddZippable(getParam(symtab, "arg4"));
    value->AddZippable(getParam(symtab, "arg5"));
    
    assert(0 != value.get());
    return value;
}

/******************************************************************************

    dish::ZipTogether6Function class definition

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::ZipTogether6Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< ZipTogetherFunctionF > value;

    std::shared_ptr< dish::iAtomic > arg1(getParam(symtab, "arg1"));
    if(dish::iAtomic::typeInteger != arg1->Type())
    {
        value = ZipTogetherFunctionF::MakeValue(1);
        value->AddZippable(arg1);
    }
    else
    {
        value = ZipTogetherFunctionF::MakeValue(arg1->AsInteger());
    }
    
    value->AddZippable(getParam(symtab, "arg2"));
    value->AddZippable(getParam(symtab, "arg3"));
    value->AddZippable(getParam(symtab, "arg4"));
    value->AddZippable(getParam(symtab, "arg5"));
    value->AddZippable(getParam(symtab, "arg6"));
    
    assert(0 != value.get());
    return value;
}

/******************************************************************************

    dish::ZipTogether7Function class definition

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::ZipTogether7Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< ZipTogetherFunctionF > value;

    std::shared_ptr< dish::iAtomic > arg1(getParam(symtab, "arg1"));
    if(dish::iAtomic::typeInteger != arg1->Type())
    {
        value = ZipTogetherFunctionF::MakeValue(1);
        value->AddZippable(arg1);
    }
    else
    {
        value = ZipTogetherFunctionF::MakeValue(arg1->AsInteger());
    }
    
    value->AddZippable(getParam(symtab, "arg2"));
    value->AddZippable(getParam(symtab, "arg3"));
    value->AddZippable(getParam(symtab, "arg4"));
    value->AddZippable(getParam(symtab, "arg5"));
    value->AddZippable(getParam(symtab, "arg6"));
    value->AddZippable(getParam(symtab, "arg7"));
    
    assert(0 != value.get());
    return value;
}

/******************************************************************************

    dish::ZipTogether8Function class definition

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::ZipTogether8Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< ZipTogetherFunctionF > value;

    std::shared_ptr< dish::iAtomic > arg1(getParam(symtab, "arg1"));
    if(dish::iAtomic::typeInteger != arg1->Type())
    {
        value = ZipTogetherFunctionF::MakeValue(1);
        value->AddZippable(arg1);
    }
    else
    {
        value = ZipTogetherFunctionF::MakeValue(arg1->AsInteger());
    }
    
    value->AddZippable(getParam(symtab, "arg2"));
    value->AddZippable(getParam(symtab, "arg3"));
    value->AddZippable(getParam(symtab, "arg4"));
    value->AddZippable(getParam(symtab, "arg5"));
    value->AddZippable(getParam(symtab, "arg6"));
    value->AddZippable(getParam(symtab, "arg7"));
    value->AddZippable(getParam(symtab, "arg8"));
    
    assert(0 != value.get());
    return value;
}

/******************************************************************************

    dish::ZipTogether9Function class definition

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::ZipTogether9Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< ZipTogetherFunctionF > value;

    std::shared_ptr< dish::iAtomic > arg1(getParam(symtab, "arg1"));
    if(dish::iAtomic::typeInteger != arg1->Type())
    {
        value = ZipTogetherFunctionF::MakeValue(1);
        value->AddZippable(arg1);
    }
    else
    {
        value = ZipTogetherFunctionF::MakeValue(arg1->AsInteger());
    }
    
    value->AddZippable(getParam(symtab, "arg2"));
    value->AddZippable(getParam(symtab, "arg3"));
    value->AddZippable(getParam(symtab, "arg4"));
    value->AddZippable(getParam(symtab, "arg5"));
    value->AddZippable(getParam(symtab, "arg6"));
    value->AddZippable(getParam(symtab, "arg7"));
    value->AddZippable(getParam(symtab, "arg8"));
    value->AddZippable(getParam(symtab, "arg9"));
    
    assert(0 != value.get());
    return value;
}

/******************************************************************************

    dish::ZipTogether10Function class definition

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::ZipTogether10Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< ZipTogetherFunctionF > value;

    std::shared_ptr< dish::iAtomic > arg1(getParam(symtab, "arg1"));
    if(dish::iAtomic::typeInteger != arg1->Type())
    {
        value = ZipTogetherFunctionF::MakeValue(1);
        value->AddZippable(arg1);
    }
    else
    {
        value = ZipTogetherFunctionF::MakeValue(arg1->AsInteger());
    }
    
    value->AddZippable(getParam(symtab, "arg2"));
    value->AddZippable(getParam(symtab, "arg3"));
    value->AddZippable(getParam(symtab, "arg4"));
    value->AddZippable(getParam(symtab, "arg5"));
    value->AddZippable(getParam(symtab, "arg6"));
    value->AddZippable(getParam(symtab, "arg7"));
    value->AddZippable(getParam(symtab, "arg8"));
    value->AddZippable(getParam(symtab, "arg9"));
    value->AddZippable(getParam(symtab, "arg10"));
    
    assert(0 != value.get());
    return value;
}

/******************************************************************************

    dish::ZipTogether11Function class definition

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::ZipTogether11Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< dish::iAtomic > arg1(getParam(symtab, "arg1"));
    if(dish::iAtomic::typeInteger != arg1->Type())
    {
        throw IllegalParameterException(".");
    }
    
    std::shared_ptr< ZipTogetherFunctionF > value(ZipTogetherFunctionF::MakeValue(arg1->AsInteger()));
    
    value->AddZippable(getParam(symtab, "arg2"));
    value->AddZippable(getParam(symtab, "arg3"));
    value->AddZippable(getParam(symtab, "arg4"));
    value->AddZippable(getParam(symtab, "arg5"));
    value->AddZippable(getParam(symtab, "arg6"));
    value->AddZippable(getParam(symtab, "arg7"));
    value->AddZippable(getParam(symtab, "arg8"));
    value->AddZippable(getParam(symtab, "arg9"));
    value->AddZippable(getParam(symtab, "arg10"));
    value->AddZippable(getParam(symtab, "arg11"));
    
    assert(0 != value.get());
    return value;
}

/******************************************************************************

    dish::ZipValueFunction class definition

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::ZipValueFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return ZipValueFunctionF::MakeValue(getParam(symtab, "value"));
}

/******************************************************************************

    dish::ZipIncrement0Function class definition

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::ZipIncrement0Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    return ZipIndexOffsetFunctionF::MakeValue(0);
}

/******************************************************************************

    dish::ZipIncrement1Function class definition

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::ZipIncrement1Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    return ZipIndexOffsetFunctionF::MakeValue(getParam(symtab, "offset")->AsInteger());
}

/******************************************************************************

    dish::ZipDecrement1Function class definition

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::ZipDecrement1Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    return ZipIndexOffsetFunctionF::MakeValue(-(getParam(symtab, "offset")->AsInteger()));
}

