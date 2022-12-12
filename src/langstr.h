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

#ifndef DISH_LANGSTR_H
#define DISH_LANGSTR_H

#include "dishconfig.h"

#include <memory>

#include "atomics.h"
#include "inline.h"
#include "language.h"
#include "types.h"

namespace dish
{

    ////////////////////////////////////////////////////////////////////////////
    
    extern const IntegerT STRINVALID;
    
    extern const BooleanT STRSINGLE;
    extern const BooleanT STRMULTIPLE;
    
    extern const StringT STR_BINARY_DIGITS;
    extern const StringT STR_OCTAL_DIGITS;
    extern const StringT STR_DECIMAL_DIGITS;
    extern const StringT STR_HEXADECIMAL_DIGITS;
    
    ////////////////////////////////////////////////////////////////////////////

    class OrdFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE OrdFunction() : dish::ExecutableAtomic() { addParam("str", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< OrdFunction > MakeValue() { return std::shared_ptr< OrdFunction >(new OrdFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class Ord2Function : public dish::ExecutableAtomic
    {
        protected:
            INLINE Ord2Function() : dish::ExecutableAtomic() { addParam("str", REFERENCE_PARAMETER); addParam("single", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< Ord2Function > MakeValue() { return std::shared_ptr< Ord2Function >(new Ord2Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class ChrFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE ChrFunction() : dish::ExecutableAtomic() { addParam("ch", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< ChrFunction > MakeValue() { return std::shared_ptr< ChrFunction >(new ChrFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class Chr2Function : public dish::ExecutableAtomic
    {
        protected:
            INLINE Chr2Function() : dish::ExecutableAtomic() { addParam("array", REFERENCE_PARAMETER); addParam("single", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< Chr2Function > MakeValue() { return std::shared_ptr< Chr2Function >(new Chr2Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////

    class IntegerToBaseStringFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE IntegerToBaseStringFunction() : dish::ExecutableAtomic() { addParam("num", REFERENCE_PARAMETER); addParam("chars", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< IntegerToBaseStringFunction > MakeValue() { return std::shared_ptr< IntegerToBaseStringFunction >(new IntegerToBaseStringFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class BaseStringToIntegerFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE BaseStringToIntegerFunction() : dish::ExecutableAtomic() { addParam("str", REFERENCE_PARAMETER); addParam("chars", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< BaseStringToIntegerFunction > MakeValue() { return std::shared_ptr< BaseStringToIntegerFunction >(new BaseStringToIntegerFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////

    class ToUpperCaseFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE ToUpperCaseFunction() : dish::ExecutableAtomic() { addParam("arg", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< ToUpperCaseFunction > MakeValue() { return std::shared_ptr< ToUpperCaseFunction >(new ToUpperCaseFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class ToLowerCaseFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE ToLowerCaseFunction() : dish::ExecutableAtomic() { addParam("arg", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< ToLowerCaseFunction > MakeValue() { return std::shared_ptr< ToLowerCaseFunction >(new ToLowerCaseFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class IsUpperCaseFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE IsUpperCaseFunction() : dish::ExecutableAtomic() { addParam("arg", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< IsUpperCaseFunction > MakeValue() { return std::shared_ptr< IsUpperCaseFunction >(new IsUpperCaseFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class IsLowerCaseFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE IsLowerCaseFunction() : dish::ExecutableAtomic() { addParam("arg", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< IsLowerCaseFunction > MakeValue() { return std::shared_ptr< IsLowerCaseFunction >(new IsLowerCaseFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class IsControlFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE IsControlFunction() : dish::ExecutableAtomic() { addParam("arg", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< IsControlFunction > MakeValue() { return std::shared_ptr< IsControlFunction >(new IsControlFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class IsPrintableFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE IsPrintableFunction() : dish::ExecutableAtomic() { addParam("arg", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< IsPrintableFunction > MakeValue() { return std::shared_ptr< IsPrintableFunction >(new IsPrintableFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class IsWhitespaceFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE IsWhitespaceFunction() : dish::ExecutableAtomic() { addParam("arg", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< IsWhitespaceFunction > MakeValue() { return std::shared_ptr< IsWhitespaceFunction >(new IsWhitespaceFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class IsPunctuationFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE IsPunctuationFunction() : dish::ExecutableAtomic() { addParam("arg", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< IsPunctuationFunction > MakeValue() { return std::shared_ptr< IsPunctuationFunction >(new IsPunctuationFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class IsLetterFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE IsLetterFunction() : dish::ExecutableAtomic() { addParam("arg", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< IsLetterFunction > MakeValue() { return std::shared_ptr< IsLetterFunction >(new IsLetterFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class IsDigitFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE IsDigitFunction() : dish::ExecutableAtomic() { addParam("arg", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< IsDigitFunction > MakeValue() { return std::shared_ptr< IsDigitFunction >(new IsDigitFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class IsHexDigitFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE IsHexDigitFunction() : dish::ExecutableAtomic() { addParam("arg", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< IsHexDigitFunction > MakeValue() { return std::shared_ptr< IsHexDigitFunction >(new IsHexDigitFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////

    class LeftJustifyFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE LeftJustifyFunction() : dish::ExecutableAtomic() { addParam("width", dish::REFERENCE_PARAMETER); addParam("str", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< LeftJustifyFunction > MakeValue() { return std::shared_ptr< LeftJustifyFunction >(new LeftJustifyFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class RightJustifyFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE RightJustifyFunction() : dish::ExecutableAtomic() { addParam("width", dish::REFERENCE_PARAMETER); addParam("str", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< RightJustifyFunction > MakeValue() { return std::shared_ptr< RightJustifyFunction >(new RightJustifyFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class CenterJustifyFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE CenterJustifyFunction() : dish::ExecutableAtomic() { addParam("width", dish::REFERENCE_PARAMETER); addParam("str", dish::REFERENCE_PARAMETER); };
        
        public:
            
            static INLINE std::shared_ptr< CenterJustifyFunction > MakeValue() { return std::shared_ptr< CenterJustifyFunction >(new CenterJustifyFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////

    class LeftStringFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE LeftStringFunction() : dish::ExecutableAtomic() { addParam("str", dish::REFERENCE_PARAMETER); addParam("n", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< LeftStringFunction > MakeValue() { return std::shared_ptr< LeftStringFunction >(new LeftStringFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class RightStringFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE RightStringFunction() : dish::ExecutableAtomic() { addParam("str", dish::REFERENCE_PARAMETER); addParam("n", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< RightStringFunction > MakeValue() { return std::shared_ptr< RightStringFunction >(new RightStringFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class MiddleStringFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE MiddleStringFunction() : dish::ExecutableAtomic() { addParam("str", dish::REFERENCE_PARAMETER); addParam("start", dish::REFERENCE_PARAMETER); addParam("n", dish::REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< MiddleStringFunction > MakeValue() { return std::shared_ptr< MiddleStringFunction >(new MiddleStringFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////

    class StringBeginsWith2Function : public ExecutableAtomic
    {
        protected:
            INLINE StringBeginsWith2Function() : dish::ExecutableAtomic() { addParam("str", REFERENCE_PARAMETER); addParam("substr", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< StringBeginsWith2Function > MakeValue() { return std::shared_ptr< StringBeginsWith2Function >(new StringBeginsWith2Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class StringBeginsWith3Function : public ExecutableAtomic
    {
        protected:
            INLINE StringBeginsWith3Function() : dish::ExecutableAtomic() { addParam("str", REFERENCE_PARAMETER); addParam("substr", REFERENCE_PARAMETER); addParam("case_sensitive", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< StringBeginsWith3Function > MakeValue() { return std::shared_ptr< StringBeginsWith3Function >(new StringBeginsWith3Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class StringEndsWith2Function : public ExecutableAtomic
    {
        protected:
            INLINE StringEndsWith2Function() : dish::ExecutableAtomic() { addParam("str", REFERENCE_PARAMETER); addParam("substr", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< StringEndsWith2Function > MakeValue() { return std::shared_ptr< StringEndsWith2Function >(new StringEndsWith2Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class StringEndsWith3Function : public ExecutableAtomic
    {
        protected:
            INLINE StringEndsWith3Function() : dish::ExecutableAtomic()
            {
                addParam("str", REFERENCE_PARAMETER);
                addParam("substr", REFERENCE_PARAMETER);
                addParam("case_sensitive", REFERENCE_PARAMETER);
            }
            
        public:
            
            static INLINE std::shared_ptr< StringEndsWith3Function > MakeValue() { return std::shared_ptr< StringEndsWith3Function >(new StringEndsWith3Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////

    class StringFindFunction : public ExecutableAtomic
    {
        protected:
            INLINE StringFindFunction() : dish::ExecutableAtomic()
            {
                addParam("searchstr", REFERENCE_PARAMETER);
                addParam("substr", REFERENCE_PARAMETER);
                addParam("pos", REFERENCE_PARAMETER);
                addParam("case_sensitive", REFERENCE_PARAMETER);
            }
            
        public:
            
            static INLINE std::shared_ptr< StringFindFunction > MakeValue() { return std::shared_ptr< StringFindFunction >(new StringFindFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class StringFindNextOfFunction : public ExecutableAtomic
    {
        protected:
            INLINE StringFindNextOfFunction() : dish::ExecutableAtomic()
            {
                addParam("searchstr", REFERENCE_PARAMETER);
                addParam("searchchars", REFERENCE_PARAMETER);
                addParam("pos", REFERENCE_PARAMETER);
                addParam("case_sensitive", REFERENCE_PARAMETER);
            }
            
        public:
            
            static INLINE std::shared_ptr< StringFindNextOfFunction > MakeValue() { return std::shared_ptr< StringFindNextOfFunction >(new StringFindNextOfFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class StringFindNextNotOfFunction : public ExecutableAtomic
    {
        protected:
            INLINE StringFindNextNotOfFunction() : dish::ExecutableAtomic()
            {
                addParam("searchstr", REFERENCE_PARAMETER);
                addParam("searchchars", REFERENCE_PARAMETER);
                addParam("pos", REFERENCE_PARAMETER);
                addParam("case_sensitive", REFERENCE_PARAMETER);
            }
            
        public:
            
            static INLINE std::shared_ptr< StringFindNextNotOfFunction > MakeValue() { return std::shared_ptr< StringFindNextNotOfFunction >(new StringFindNextNotOfFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class StringFindLastOfFunction : public ExecutableAtomic
    {
        protected:
            INLINE StringFindLastOfFunction() : dish::ExecutableAtomic()
            {
                addParam("searchstr", REFERENCE_PARAMETER);
                addParam("searchchars", REFERENCE_PARAMETER);
                addParam("pos", REFERENCE_PARAMETER);
                addParam("case_sensitive", REFERENCE_PARAMETER);
            }
            
        public:
            
            static INLINE std::shared_ptr< StringFindLastOfFunction > MakeValue() { return std::shared_ptr< StringFindLastOfFunction >(new StringFindLastOfFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class StringFindLastNotOfFunction : public ExecutableAtomic
    {
        protected:
            INLINE StringFindLastNotOfFunction() : dish::ExecutableAtomic()
            {
                addParam("searchstr", REFERENCE_PARAMETER);
                addParam("searchchars", REFERENCE_PARAMETER);
                addParam("pos", REFERENCE_PARAMETER);
                addParam("case_sensitive", REFERENCE_PARAMETER);
            }
            
        public:
            
            static INLINE std::shared_ptr< StringFindLastNotOfFunction > MakeValue() { return std::shared_ptr< StringFindLastNotOfFunction >(new StringFindLastNotOfFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////

    class StringTrimLeadingFunction : public ExecutableAtomic
    {
        protected:
            INLINE StringTrimLeadingFunction() : dish::ExecutableAtomic() { addParam("str", REFERENCE_PARAMETER); addParam("chars", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< StringTrimLeadingFunction > MakeValue() { return std::shared_ptr< StringTrimLeadingFunction >(new StringTrimLeadingFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class StringTrimTrailingFunction : public ExecutableAtomic
    {
        protected:
            INLINE StringTrimTrailingFunction() : dish::ExecutableAtomic() { addParam("str", REFERENCE_PARAMETER); addParam("chars", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< StringTrimTrailingFunction > MakeValue() { return std::shared_ptr< StringTrimTrailingFunction >(new StringTrimTrailingFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class StringRemoveAllOfFunction : public ExecutableAtomic
    {
        protected:
            INLINE StringRemoveAllOfFunction() : dish::ExecutableAtomic() { addParam("str", REFERENCE_PARAMETER); addParam("chars", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< StringRemoveAllOfFunction > MakeValue() { return std::shared_ptr< StringRemoveAllOfFunction >(new StringRemoveAllOfFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class StringRemoveAllNotOfFunction : public ExecutableAtomic
    {
        protected:
            INLINE StringRemoveAllNotOfFunction() : dish::ExecutableAtomic() { addParam("str", REFERENCE_PARAMETER); addParam("chars", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< StringRemoveAllNotOfFunction > MakeValue() { return std::shared_ptr< StringRemoveAllNotOfFunction >(new StringRemoveAllNotOfFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////

    class StringReplaceAllFunction : public ExecutableAtomic
    {
        protected:
            INLINE StringReplaceAllFunction() : dish::ExecutableAtomic() 
            { 
                addParam("str", REFERENCE_PARAMETER);
                addParam("target", REFERENCE_PARAMETER);
                addParam("replace", REFERENCE_PARAMETER);
                addParam("casesensitive", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< StringReplaceAllFunction > MakeValue() { return std::shared_ptr< StringReplaceAllFunction >(new StringReplaceAllFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class StringReplaceAllWithPosFunction : public ExecutableAtomic
    {
        protected:
            INLINE StringReplaceAllWithPosFunction() : dish::ExecutableAtomic() 
            { 
                addParam("str", REFERENCE_PARAMETER);
                addParam("pos", REFERENCE_PARAMETER);
                addParam("target", REFERENCE_PARAMETER);
                addParam("replace", REFERENCE_PARAMETER);
                addParam("casesensitive", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< StringReplaceAllWithPosFunction > MakeValue() { return std::shared_ptr< StringReplaceAllWithPosFunction >(new StringReplaceAllWithPosFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class StringReplaceFirstFunction : public ExecutableAtomic
    {
        protected:
            INLINE StringReplaceFirstFunction() : dish::ExecutableAtomic() 
            { 
                addParam("str", REFERENCE_PARAMETER);
                addParam("target", REFERENCE_PARAMETER);
                addParam("replace", REFERENCE_PARAMETER);
                addParam("casesensitive", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< StringReplaceFirstFunction > MakeValue() { return std::shared_ptr< StringReplaceFirstFunction >(new StringReplaceFirstFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class StringReplaceFirstWithPosFunction : public ExecutableAtomic
    {
        protected:
            INLINE StringReplaceFirstWithPosFunction() : dish::ExecutableAtomic() 
            { 
                addParam("str", REFERENCE_PARAMETER);
                addParam("pos", REFERENCE_PARAMETER);
                addParam("target", REFERENCE_PARAMETER);
                addParam("replace", REFERENCE_PARAMETER);
                addParam("casesensitive", REFERENCE_PARAMETER);
            };
            
        public:
            
            static INLINE std::shared_ptr< StringReplaceFirstWithPosFunction > MakeValue() { return std::shared_ptr< StringReplaceFirstWithPosFunction >(new StringReplaceFirstWithPosFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////

    class StringReplicateFunction : public ExecutableAtomic
    {
        protected:
            INLINE StringReplicateFunction() : dish::ExecutableAtomic() { addParam("n", REFERENCE_PARAMETER); addParam("str", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< StringReplicateFunction > MakeValue() { return std::shared_ptr< StringReplicateFunction >(new StringReplicateFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////

    class StringReverseFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE StringReverseFunction() : dish::ExecutableAtomic() { addParam("str", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< StringReverseFunction > MakeValue() { return std::shared_ptr< StringReverseFunction >(new StringReverseFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////

}

#endif

