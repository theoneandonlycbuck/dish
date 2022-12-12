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

#ifndef DISH_LANGMATH_H
#define DISH_LANGMATH_H

#include "dishconfig.h"

#include <memory>

#include "atomics.h"
#include "inline.h"
#include "langid.h"
#include "symtab.h"

namespace dish
{

    ////////////////////////////////////////////////////////////////////////////
    
    class OneArgMathFunction : public dish::ExecutableAtomic
    {
        private:
            const std::string mFunctionName;
    
        protected:
            INLINE OneArgMathFunction(const std::string &fname) : dish::ExecutableAtomic(), mFunctionName(fname) { addParam(ArgumentName, REFERENCE_PARAMETER); };
            
            std::shared_ptr< iAtomic > generateArgumentError() const;
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const = 0;
            
        public:
            
            static const std::string ArgumentName;
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
#ifdef LANG_LIB_MATH_CORE

    ////////////////////////////////////////////////////////////////////////////

    class IsFiniteNumberFunction : public OneArgMathFunction
    {
        protected:
            INLINE IsFiniteNumberFunction() : OneArgMathFunction(DISH_LANGID_IsFiniteNumberFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< IsFiniteNumberFunction > MakeValue() { return std::shared_ptr< IsFiniteNumberFunction >(new IsFiniteNumberFunction()); };
                    
    };

    class IsInfiniteNumberFunction : public OneArgMathFunction
    {
        protected:
            INLINE IsInfiniteNumberFunction() : OneArgMathFunction(DISH_LANGID_IsInfiniteNumberFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< IsInfiniteNumberFunction > MakeValue() { return std::shared_ptr< IsInfiniteNumberFunction >(new IsInfiniteNumberFunction()); };
                    
    };
    
    class IsNotANumberFunction : public OneArgMathFunction
    {
        protected:
            INLINE IsNotANumberFunction() : OneArgMathFunction(DISH_LANGID_IsNotANumberFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< IsNotANumberFunction > MakeValue() { return std::shared_ptr< IsNotANumberFunction >(new IsNotANumberFunction()); };
                    
    };
    
    class IsNormalNumberFunction : public OneArgMathFunction
    {
        protected:
            INLINE IsNormalNumberFunction() : OneArgMathFunction(DISH_LANGID_IsNormalNumberFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< IsNormalNumberFunction > MakeValue() { return std::shared_ptr< IsNormalNumberFunction >(new IsNormalNumberFunction()); };
                    
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class IsOddFunction : public OneArgMathFunction
    {
        protected:
            INLINE IsOddFunction() : OneArgMathFunction(DISH_LANGID_IsOddFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< IsOddFunction > MakeValue() { return std::shared_ptr< IsOddFunction >(new IsOddFunction()); };
                    
    };
    
    class IsEvenFunction : public OneArgMathFunction
    {
        protected:
            INLINE IsEvenFunction() : OneArgMathFunction(DISH_LANGID_IsEvenFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< IsEvenFunction > MakeValue() { return std::shared_ptr< IsEvenFunction >(new IsEvenFunction()); };
                    
    };

    ////////////////////////////////////////////////////////////////////////////

    class AbsFunction : public OneArgMathFunction
    {
        protected:
            INLINE AbsFunction() : OneArgMathFunction(DISH_LANGID_AbsFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< AbsFunction > MakeValue() { return std::shared_ptr< AbsFunction >(new AbsFunction()); };
                    
    };
    
    class WholeFunction : public OneArgMathFunction
    {
        protected:
            INLINE WholeFunction() : OneArgMathFunction(DISH_LANGID_WholeFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< WholeFunction > MakeValue() { return std::shared_ptr< WholeFunction >(new WholeFunction()); };
                    
    };
    
    class FractionFunction : public OneArgMathFunction
    {
        protected:
            INLINE FractionFunction() : OneArgMathFunction(DISH_LANGID_FractionFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< FractionFunction > MakeValue() { return std::shared_ptr< FractionFunction >(new FractionFunction()); };
                    
    };

    class SignOfFunction : public OneArgMathFunction
    {
        protected:
            INLINE SignOfFunction() : OneArgMathFunction(DISH_LANGID_SignOfFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< SignOfFunction > MakeValue() { return std::shared_ptr< SignOfFunction >(new SignOfFunction()); };
                    
    };

    class SqrFunction : public OneArgMathFunction
    {
        protected:
            INLINE SqrFunction() : OneArgMathFunction(DISH_LANGID_SqrFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< SqrFunction > MakeValue() { return std::shared_ptr< SqrFunction >(new SqrFunction()); };
                    
    };

    class SqrtFunction : public OneArgMathFunction
    {
        protected:
            INLINE SqrtFunction() : OneArgMathFunction(DISH_LANGID_SqrtFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< SqrtFunction > MakeValue() { return std::shared_ptr< SqrtFunction >(new SqrtFunction()); };
                    
    };

    class CubeFunction : public OneArgMathFunction
    {
        protected:
            INLINE CubeFunction() : OneArgMathFunction(DISH_LANGID_CubeFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< CubeFunction > MakeValue() { return std::shared_ptr< CubeFunction >(new CubeFunction()); };
                    
    };

    class CbrtFunction : public OneArgMathFunction
    {
        protected:
            INLINE CbrtFunction() : OneArgMathFunction(DISH_LANGID_CbrtFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< CbrtFunction > MakeValue() { return std::shared_ptr< CbrtFunction >(new CbrtFunction()); };
                    
    };

    class LnFunction : public OneArgMathFunction
    {
        protected:
            INLINE LnFunction() : OneArgMathFunction(DISH_LANGID_LnFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< LnFunction > MakeValue() { return std::shared_ptr< LnFunction >(new LnFunction()); };
            
    };

    class LogFunction : public OneArgMathFunction
    {
        protected:
            INLINE LogFunction() : OneArgMathFunction(DISH_LANGID_LogFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< LogFunction > MakeValue() { return std::shared_ptr< LogFunction >(new LogFunction()); };
            
    };

    class Log2Function : public ExecutableAtomic
    {
        protected:
            INLINE Log2Function() : ExecutableAtomic() { addParam("x", REFERENCE_PARAMETER); addParam("base", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< Log2Function > MakeValue() { return std::shared_ptr< Log2Function >(new Log2Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    class ExpFunction : public OneArgMathFunction
    {
        protected:
            INLINE ExpFunction() : OneArgMathFunction(DISH_LANGID_ExpFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< ExpFunction > MakeValue() { return std::shared_ptr< ExpFunction >(new ExpFunction()); };
            
    };
    
    ////

    class RoundFunction : public OneArgMathFunction
    {
        protected:
            INLINE RoundFunction() : OneArgMathFunction(DISH_LANGID_RoundFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< RoundFunction > MakeValue() { return std::shared_ptr< RoundFunction >(new RoundFunction()); };
                    
    };

    class FloorFunction : public OneArgMathFunction
    {
        protected:
            INLINE FloorFunction() : OneArgMathFunction(DISH_LANGID_FloorFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< FloorFunction > MakeValue() { return std::shared_ptr< FloorFunction >(new FloorFunction()); };
                    
    };

    class CeilFunction : public OneArgMathFunction
    {
        protected:
            INLINE CeilFunction() : OneArgMathFunction(DISH_LANGID_CeilFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< CeilFunction > MakeValue() { return std::shared_ptr< CeilFunction >(new CeilFunction()); };
                    
    };

    ////////////////////////////////////////////////////////////////////////////
    
#endif

#ifdef LANG_LIB_MATH_TRIG

    ////////////////////////////////////////////////////////////////////////////

    extern const RealT PI;

    ////////////////////////////////////////////////////////////////////////////

    class DegToRadFunction : public OneArgMathFunction
    {
        protected:
            INLINE DegToRadFunction() : OneArgMathFunction(DISH_LANGID_DegToRadFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< DegToRadFunction > MakeValue() { return std::shared_ptr< DegToRadFunction >(new DegToRadFunction()); };
                    
    };

    class RadToDegFunction : public OneArgMathFunction
    {
        protected:
            INLINE RadToDegFunction() : OneArgMathFunction(DISH_LANGID_RadToDegFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< RadToDegFunction > MakeValue() { return std::shared_ptr< RadToDegFunction >(new RadToDegFunction()); };
                    
    };
    
    ////

    class SinFunction : public OneArgMathFunction
    {
        protected:
            INLINE SinFunction() : OneArgMathFunction(DISH_LANGID_SinFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< SinFunction > MakeValue() { return std::shared_ptr< SinFunction >(new SinFunction()); };
                    
    };

    class CosFunction : public OneArgMathFunction
    {
        protected:
            INLINE CosFunction() : OneArgMathFunction(DISH_LANGID_CosFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< CosFunction > MakeValue() { return std::shared_ptr< CosFunction >(new CosFunction()); };
                    
    };

    class TanFunction : public OneArgMathFunction
    {
        protected:
            INLINE TanFunction() : OneArgMathFunction(DISH_LANGID_TanFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< TanFunction > MakeValue() { return std::shared_ptr< TanFunction >(new TanFunction()); };
                    
    };

    class ArcSinFunction : public OneArgMathFunction
    {
        protected:
            INLINE ArcSinFunction() : OneArgMathFunction(DISH_LANGID_ArcSinFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< ArcSinFunction > MakeValue() { return std::shared_ptr< ArcSinFunction >(new ArcSinFunction()); };
                    
    };

    class ArcCosFunction : public OneArgMathFunction
    {
        protected:
            INLINE ArcCosFunction() : OneArgMathFunction(DISH_LANGID_ArcCosFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< ArcCosFunction > MakeValue() { return std::shared_ptr< ArcCosFunction >(new ArcCosFunction()); };
                    
    };

    class ArcTanFunction : public OneArgMathFunction
    {
        protected:
            INLINE ArcTanFunction() : OneArgMathFunction(DISH_LANGID_ArcTanFunction) {};
        
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< ArcTanFunction > MakeValue() { return std::shared_ptr< ArcTanFunction >(new ArcTanFunction()); };
                    
    };
    
    ////

    class CotFunction : public OneArgMathFunction
    {
        protected:
            INLINE CotFunction() : OneArgMathFunction(DISH_LANGID_CotFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< CotFunction > MakeValue() { return std::shared_ptr< CotFunction >(new CotFunction()); };
                    
    };

    class SecFunction : public OneArgMathFunction
    {
        protected:
            INLINE SecFunction() : OneArgMathFunction(DISH_LANGID_SecFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< SecFunction > MakeValue() { return std::shared_ptr< SecFunction >(new SecFunction()); };
                    
    };

    class CscFunction : public OneArgMathFunction
    {
        protected:
            INLINE CscFunction() : OneArgMathFunction(DISH_LANGID_CscFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< CscFunction > MakeValue() { return std::shared_ptr< CscFunction >(new CscFunction()); };
                    
    };

    class ArcCotFunction : public OneArgMathFunction
    {
        protected:
            INLINE ArcCotFunction() : OneArgMathFunction(DISH_LANGID_ArcCotFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< ArcCotFunction > MakeValue() { return std::shared_ptr< ArcCotFunction >(new ArcCotFunction()); };
                    
    };

    class ArcSecFunction : public OneArgMathFunction
    {
        protected:
            INLINE ArcSecFunction() : OneArgMathFunction(DISH_LANGID_ArcSecFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< ArcSecFunction > MakeValue() { return std::shared_ptr< ArcSecFunction >(new ArcSecFunction()); };
                    
    };

    class ArcCscFunction : public OneArgMathFunction
    {
        protected:
            INLINE ArcCscFunction() : OneArgMathFunction(DISH_LANGID_ArcCscFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< ArcCscFunction > MakeValue() { return std::shared_ptr< ArcCscFunction >(new ArcCscFunction()); };
                    
    };

    ////////////////////////////////////////////////////////////////////////////
    
#endif

#ifdef LANG_LIB_MATH_HYPERBOLIC

    ////////////////////////////////////////////////////////////////////////////

    class SinhFunction : public OneArgMathFunction
    {
        protected:
            INLINE SinhFunction() : OneArgMathFunction(DISH_LANGID_SinhFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< SinhFunction > MakeValue() { return std::shared_ptr< SinhFunction >(new SinhFunction()); };
                    
    };

    class CoshFunction : public OneArgMathFunction
    {
        protected:
            INLINE CoshFunction() : OneArgMathFunction(DISH_LANGID_CoshFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< CoshFunction > MakeValue() { return std::shared_ptr< CoshFunction >(new CoshFunction()); };
                    
    };

    class TanhFunction : public OneArgMathFunction
    {
        protected:
            INLINE TanhFunction() : OneArgMathFunction(DISH_LANGID_TanhFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< TanhFunction > MakeValue() { return std::shared_ptr< TanhFunction >(new TanhFunction()); };
                    
    };

    class ArcSinhFunction : public OneArgMathFunction
    {
        protected:
            INLINE ArcSinhFunction() : OneArgMathFunction(DISH_LANGID_ArcSinhFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< ArcSinhFunction > MakeValue() { return std::shared_ptr< ArcSinhFunction >(new ArcSinhFunction()); };
                    
    };

    class ArcCoshFunction : public OneArgMathFunction
    {
        protected:
            INLINE ArcCoshFunction() : OneArgMathFunction(DISH_LANGID_ArcCoshFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< ArcCoshFunction > MakeValue() { return std::shared_ptr< ArcCoshFunction >(new ArcCoshFunction()); };
                    
    };

    class ArcTanhFunction : public OneArgMathFunction
    {
        protected:
            INLINE ArcTanhFunction() : OneArgMathFunction(DISH_LANGID_ArcTanhFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< ArcTanhFunction > MakeValue() { return std::shared_ptr< ArcTanhFunction >(new ArcTanhFunction()); };
            
    };
    
    ////

    class SechFunction : public OneArgMathFunction
    {
        protected:
            INLINE SechFunction() : OneArgMathFunction(DISH_LANGID_SechFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< SechFunction > MakeValue() { return std::shared_ptr< SechFunction >(new SechFunction()); };
                    
    };

    class CschFunction : public OneArgMathFunction
    {
        protected:
            INLINE CschFunction() : OneArgMathFunction(DISH_LANGID_CschFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< CschFunction > MakeValue() { return std::shared_ptr< CschFunction >(new CschFunction()); };
                    
    };

    class CothFunction : public OneArgMathFunction
    {
        protected:
            INLINE CothFunction() : OneArgMathFunction(DISH_LANGID_CothFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< CothFunction > MakeValue() { return std::shared_ptr< CothFunction >(new CothFunction()); };
                    
    };

    class ArcSechFunction : public OneArgMathFunction
    {
        protected:
            INLINE ArcSechFunction() : OneArgMathFunction(DISH_LANGID_ArcSechFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< ArcSechFunction > MakeValue() { return std::shared_ptr< ArcSechFunction >(new ArcSechFunction()); };
                    
    };

    class ArcCschFunction : public OneArgMathFunction
    {
        protected:
            INLINE ArcCschFunction() : OneArgMathFunction(DISH_LANGID_ArcCschFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< ArcCschFunction > MakeValue() { return std::shared_ptr< ArcCschFunction >(new ArcCschFunction()); };
                    
    };

    class ArcCothFunction : public OneArgMathFunction
    {
        protected:
            INLINE ArcCothFunction() : OneArgMathFunction(DISH_LANGID_ArcCothFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< ArcCothFunction > MakeValue() { return std::shared_ptr< ArcCothFunction >(new ArcCothFunction()); };
                    
    };

    ////////////////////////////////////////////////////////////////////////////
    
#endif

#ifdef LANG_LIB_MATH_COMPLEX

    ////////////////////////////////////////////////////////////////////////////
    
    extern std::shared_ptr< iAtomic > CreateImaginaryStructureType();
    
    INLINEC std::shared_ptr< iAtomic > CreateImaginaryStructure(const RealT &r, const RealT &i)
    {
        std::shared_ptr< iAtomic > imaginary(CreateImaginaryStructureType()->Declare());
        imaginary->Member("r")->Assign(r);
        imaginary->Member("i")->Assign(i);
        
        return imaginary;
    }
    
    ////

    class ImaginaryCreate1Function : public dish::ExecutableAtomic
    {
        protected:
            INLINE ImaginaryCreate1Function() : dish::ExecutableAtomic() { addParam("r", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< ImaginaryCreate1Function > MakeValue() { return std::shared_ptr< ImaginaryCreate1Function >(new ImaginaryCreate1Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class ImaginaryCreate2Function : public dish::ExecutableAtomic
    {
        protected:
            INLINE ImaginaryCreate2Function() : dish::ExecutableAtomic() { addParam("r", REFERENCE_PARAMETER); addParam("i", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< ImaginaryCreate2Function > MakeValue() { return std::shared_ptr< ImaginaryCreate2Function >(new ImaginaryCreate2Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class ImaginaryToStringFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE ImaginaryToStringFunction() : dish::ExecutableAtomic() { addParam("arg", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< ImaginaryToStringFunction > MakeValue() { return std::shared_ptr< ImaginaryToStringFunction >(new ImaginaryToStringFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class ImaginaryIsEqualFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE ImaginaryIsEqualFunction() : dish::ExecutableAtomic() { addParam("lhs", REFERENCE_PARAMETER); addParam("rhs", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< ImaginaryIsEqualFunction > MakeValue() { return std::shared_ptr< ImaginaryIsEqualFunction >(new ImaginaryIsEqualFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class ImaginaryIsNotEqualFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE ImaginaryIsNotEqualFunction() : dish::ExecutableAtomic() { addParam("lhs", REFERENCE_PARAMETER); addParam("rhs", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< ImaginaryIsNotEqualFunction > MakeValue() { return std::shared_ptr< ImaginaryIsNotEqualFunction >(new ImaginaryIsNotEqualFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class ImaginaryAddFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE ImaginaryAddFunction() : dish::ExecutableAtomic() { addParam("arg1", REFERENCE_PARAMETER); addParam("arg2", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< ImaginaryAddFunction > MakeValue() { return std::shared_ptr< ImaginaryAddFunction >(new ImaginaryAddFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class ImaginarySubtractFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE ImaginarySubtractFunction() : dish::ExecutableAtomic() { addParam("arg1", REFERENCE_PARAMETER); addParam("arg2", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< ImaginarySubtractFunction > MakeValue() { return std::shared_ptr< ImaginarySubtractFunction >(new ImaginarySubtractFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class ImaginaryMultiplyFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE ImaginaryMultiplyFunction() : dish::ExecutableAtomic() { addParam("arg1", REFERENCE_PARAMETER); addParam("arg2", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< ImaginaryMultiplyFunction > MakeValue() { return std::shared_ptr< ImaginaryMultiplyFunction >(new ImaginaryMultiplyFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class ImaginaryDivideFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE ImaginaryDivideFunction() : dish::ExecutableAtomic() { addParam("arg1", REFERENCE_PARAMETER); addParam("arg2", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< ImaginaryDivideFunction > MakeValue() { return std::shared_ptr< ImaginaryDivideFunction >(new ImaginaryDivideFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class ImaginarySqrFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE ImaginarySqrFunction() : dish::ExecutableAtomic() { addParam("arg", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< ImaginarySqrFunction > MakeValue() { return std::shared_ptr< ImaginarySqrFunction >(new ImaginarySqrFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class ImaginarySqrtFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE ImaginarySqrtFunction() : dish::ExecutableAtomic() { addParam("arg", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< ImaginarySqrtFunction > MakeValue() { return std::shared_ptr< ImaginarySqrtFunction >(new ImaginarySqrtFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class ImaginaryReciprocalFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE ImaginaryReciprocalFunction() : dish::ExecutableAtomic() { addParam("arg", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< ImaginaryReciprocalFunction > MakeValue() { return std::shared_ptr< ImaginaryReciprocalFunction >(new ImaginaryReciprocalFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class ImaginaryConjugateFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE ImaginaryConjugateFunction() : dish::ExecutableAtomic() { addParam("arg", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< ImaginaryConjugateFunction > MakeValue() { return std::shared_ptr< ImaginaryConjugateFunction >(new ImaginaryConjugateFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////
    
#endif

#ifdef LANG_LIB_MATH_RANDOM

    ////////////////////////////////////////////////////////////////////////////

    class RandomSeedFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE RandomSeedFunction() : dish::ExecutableAtomic() { addParam("seed", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< RandomSeedFunction > MakeValue() { return std::shared_ptr< RandomSeedFunction >(new RandomSeedFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
                    
    };

    class RandomBooleanFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE RandomBooleanFunction() : dish::ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< RandomBooleanFunction > MakeValue() { return std::shared_ptr< RandomBooleanFunction >(new RandomBooleanFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    class RandomIntegerFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE RandomIntegerFunction() : dish::ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< RandomIntegerFunction > MakeValue() { return std::shared_ptr< RandomIntegerFunction >(new RandomIntegerFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    class RandomInteger1Function : public dish::ExecutableAtomic
    {
        protected:
            INLINE RandomInteger1Function() : dish::ExecutableAtomic() { addParam("max", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< RandomInteger1Function > MakeValue() { return std::shared_ptr< RandomInteger1Function >(new RandomInteger1Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    class RandomInteger2Function : public dish::ExecutableAtomic
    {
        protected:
            INLINE RandomInteger2Function() : dish::ExecutableAtomic() { addParam("min", REFERENCE_PARAMETER); addParam("max", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< RandomInteger2Function > MakeValue() { return std::shared_ptr< RandomInteger2Function >(new RandomInteger2Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    class RandomRealFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE RandomRealFunction() : dish::ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< RandomRealFunction > MakeValue() { return std::shared_ptr< RandomRealFunction >(new RandomRealFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    class RandomReal1Function : public dish::ExecutableAtomic
    {
        protected:
            INLINE RandomReal1Function() : dish::ExecutableAtomic() { addParam("max", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< RandomReal1Function > MakeValue() { return std::shared_ptr< RandomReal1Function >(new RandomReal1Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    class RandomReal2Function : public dish::ExecutableAtomic
    {
        protected:
            INLINE RandomReal2Function() : dish::ExecutableAtomic() { addParam("min", REFERENCE_PARAMETER); addParam("max", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< RandomReal2Function > MakeValue() { return std::shared_ptr< RandomReal2Function >(new RandomReal2Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    class RandomMaxFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE RandomMaxFunction() : dish::ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< RandomMaxFunction > MakeValue() { return std::shared_ptr< RandomMaxFunction >(new RandomMaxFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    class RandomBitIntegerFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE RandomBitIntegerFunction() : dish::ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< RandomBitIntegerFunction > MakeValue() { return std::shared_ptr< RandomBitIntegerFunction >(new RandomBitIntegerFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };
    
    const iRNG &RngInstance();
    const iRNG &RngInstance(const IntegerT &seed);

    ////////////////////////////////////////////////////////////////////////////
    
#endif

#ifdef LANG_LIB_MATH_MATRIX

    ////////////////////////////////////////////////////////////////////////////

    class CreateMatrixTFunction : public ExecutableAtomic
    {
        protected:
            INLINE CreateMatrixTFunction() : ExecutableAtomic() { addParam("m", REFERENCE_PARAMETER); addParam("n", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< CreateMatrixTFunction > MakeValue() { return std::shared_ptr< CreateMatrixTFunction >(new CreateMatrixTFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    class CreateMatrixFunction : public ExecutableAtomic
    {
        protected:
            INLINE CreateMatrixFunction() : ExecutableAtomic() { addParam("m", REFERENCE_PARAMETER); addParam("n", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< CreateMatrixFunction > MakeValue() { return std::shared_ptr< CreateMatrixFunction >(new CreateMatrixFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    class MatrixValidateFunction : public ExecutableAtomic
    {
        protected:
            INLINE MatrixValidateFunction() : ExecutableAtomic() { addParam("M", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< MatrixValidateFunction > MakeValue() { return std::shared_ptr< MatrixValidateFunction >(new MatrixValidateFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };
    
    ////////

    class MatrixNumRowsFunction : public ExecutableAtomic
    {
        protected:
            INLINE MatrixNumRowsFunction() : ExecutableAtomic() { addParam("M", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< MatrixNumRowsFunction > MakeValue() { return std::shared_ptr< MatrixNumRowsFunction >(new MatrixNumRowsFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    class MatrixNumColumnsFunction : public ExecutableAtomic
    {
        protected:
            INLINE MatrixNumColumnsFunction() : ExecutableAtomic() { addParam("M", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< MatrixNumColumnsFunction > MakeValue() { return std::shared_ptr< MatrixNumColumnsFunction >(new MatrixNumColumnsFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    class MatrixIsSquareFunction : public ExecutableAtomic
    {
        protected:
            INLINE MatrixIsSquareFunction() : ExecutableAtomic() { addParam("M", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< MatrixIsSquareFunction > MakeValue() { return std::shared_ptr< MatrixIsSquareFunction >(new MatrixIsSquareFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    class MatrixInitialize1Function : public ExecutableAtomic
    {
        protected:
            INLINE MatrixInitialize1Function() : ExecutableAtomic() { addParam("M", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< MatrixInitialize1Function > MakeValue() { return std::shared_ptr< MatrixInitialize1Function >(new MatrixInitialize1Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    class MatrixInitialize2Function : public ExecutableAtomic
    {
        protected:
            INLINE MatrixInitialize2Function() : ExecutableAtomic() { addParam("M", REFERENCE_PARAMETER); addParam("value", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< MatrixInitialize2Function > MakeValue() { return std::shared_ptr< MatrixInitialize2Function >(new MatrixInitialize2Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };
    
    ////////

    class MatrixRowSliceFunction : public ExecutableAtomic
    {
        protected:
            INLINE MatrixRowSliceFunction() : ExecutableAtomic() { addParam("M", REFERENCE_PARAMETER); addParam("row", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< MatrixRowSliceFunction > MakeValue() { return std::shared_ptr< MatrixRowSliceFunction >(new MatrixRowSliceFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    class MatrixColumnSliceFunction : public ExecutableAtomic
    {
        protected:
            INLINE MatrixColumnSliceFunction() : ExecutableAtomic() { addParam("M", REFERENCE_PARAMETER); addParam("col", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< MatrixColumnSliceFunction > MakeValue() { return std::shared_ptr< MatrixColumnSliceFunction >(new MatrixColumnSliceFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };
    
    ////////

    class MatrixTransposeFunction : public ExecutableAtomic
    {
        protected:
            INLINE MatrixTransposeFunction() : ExecutableAtomic() { addParam("M", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< MatrixTransposeFunction > MakeValue() { return std::shared_ptr< MatrixTransposeFunction >(new MatrixTransposeFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    class MatrixDeterminantFunction : public ExecutableAtomic
    {
        protected:
            INLINE MatrixDeterminantFunction() : ExecutableAtomic() { addParam("M", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< MatrixDeterminantFunction > MakeValue() { return std::shared_ptr< MatrixDeterminantFunction >(new MatrixDeterminantFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    class MatrixInvertFunction : public ExecutableAtomic
    {
        protected:
            INLINE MatrixInvertFunction() : ExecutableAtomic() { addParam("M", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< MatrixInvertFunction > MakeValue() { return std::shared_ptr< MatrixInvertFunction >(new MatrixInvertFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };
    
    ////////

    class MatrixAddFunction : public ExecutableAtomic
    {
        protected:
            INLINE MatrixAddFunction() : ExecutableAtomic() { addParam("arg1", REFERENCE_PARAMETER); addParam("arg2", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< MatrixAddFunction > MakeValue() { return std::shared_ptr< MatrixAddFunction >(new MatrixAddFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    class MatrixSubtractFunction : public ExecutableAtomic
    {
        protected:
            INLINE MatrixSubtractFunction() : ExecutableAtomic() { addParam("arg1", REFERENCE_PARAMETER); addParam("arg2", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< MatrixSubtractFunction > MakeValue() { return std::shared_ptr< MatrixSubtractFunction >(new MatrixSubtractFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    class MatrixMultiplyFunction : public ExecutableAtomic
    {
        protected:
            INLINE MatrixMultiplyFunction() : ExecutableAtomic() { addParam("arg1", REFERENCE_PARAMETER); addParam("arg2", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< MatrixMultiplyFunction > MakeValue() { return std::shared_ptr< MatrixMultiplyFunction >(new MatrixMultiplyFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };
    
    ////////

    class MatrixEqualFunction : public ExecutableAtomic
    {
        protected:
            INLINE MatrixEqualFunction() : ExecutableAtomic() { addParam("arg1", REFERENCE_PARAMETER); addParam("arg2", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< MatrixEqualFunction > MakeValue() { return std::shared_ptr< MatrixEqualFunction >(new MatrixEqualFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };
    
    ////////

    class MatrixAddRowFunction : public ExecutableAtomic
    {
        protected:
            INLINE MatrixAddRowFunction() : ExecutableAtomic() { addParam("dest", REFERENCE_PARAMETER); addParam("src", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< MatrixAddRowFunction > MakeValue() { return std::shared_ptr< MatrixAddRowFunction >(new MatrixAddRowFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    class MatrixAddColumnFunction : public ExecutableAtomic
    {
        protected:
            INLINE MatrixAddColumnFunction() : ExecutableAtomic() { addParam("dest", REFERENCE_PARAMETER); addParam("src", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< MatrixAddColumnFunction > MakeValue() { return std::shared_ptr< MatrixAddColumnFunction >(new MatrixAddColumnFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };
    
    ////////

    class MatrixToStringFunction : public ExecutableAtomic
    {
        protected:
            INLINE MatrixToStringFunction() : ExecutableAtomic() { addParam("M", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< MatrixToStringFunction > MakeValue() { return std::shared_ptr< MatrixToStringFunction >(new MatrixToStringFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    ////////////////////////////////////////////////////////////////////////////
    
#endif

#ifdef LANG_LIB_MATH_INTEGER

    ////////////////////////////////////////////////////////////////////////////

    class FactorialFunction : public OneArgMathFunction
    {
        protected:
            INLINE FactorialFunction() : OneArgMathFunction(DISH_LANGID_FactorialFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< FactorialFunction > MakeValue() { return std::shared_ptr< FactorialFunction >(new FactorialFunction()); };
                    
    };

    class BinomialCoefficientFunction : public ExecutableAtomic
    {
        protected:
            INLINE BinomialCoefficientFunction() : ExecutableAtomic() { addParam("n", REFERENCE_PARAMETER); addParam("i", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< BinomialCoefficientFunction > MakeValue() { return std::shared_ptr< BinomialCoefficientFunction >(new BinomialCoefficientFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    class GreatestCommonDenomonatorFunction : public ExecutableAtomic
    {
        protected:
            INLINE GreatestCommonDenomonatorFunction() : ExecutableAtomic() { addParam("a", REFERENCE_PARAMETER); addParam("b", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< GreatestCommonDenomonatorFunction > MakeValue() { return std::shared_ptr< GreatestCommonDenomonatorFunction >(new GreatestCommonDenomonatorFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
            
    };

    class FibonacciFunction : public OneArgMathFunction
    {
        protected:
            INLINE FibonacciFunction() : OneArgMathFunction(DISH_LANGID_FibonacciFunction) {};
        
            //  From OneArgMathFunction
            
            virtual std::shared_ptr< iAtomic > execute(std::shared_ptr< iAtomic > arg) const;
        
        public:
            
            static INLINE std::shared_ptr< FibonacciFunction > MakeValue() { return std::shared_ptr< FibonacciFunction >(new FibonacciFunction()); };
                    
    };

    ////////////////////////////////////////////////////////////////////////////
    
#endif

}

#endif

