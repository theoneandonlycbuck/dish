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
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <sstream>

#include "exception.h"
#include "langid.h"
#include "langmath.h"
#include "langtxtio.h"
#include "types.h"
#include "utility.h"

namespace
{

    ////////////////////////////////////////////////////////////////////////////

    class Matrix
    {
        private:
        
            static const dish::IntegerT VALUE_INVALID;
        
            static const bool SKIP_INITIALIZATION;
            
            static std::shared_ptr< dish::iAtomic > REAL_TYPE;
        
            std::shared_ptr< dish::iAtomic > mMatrix;
            
            mutable dish::IntegerT mNumRows;
            mutable dish::IntegerT mNumCols;
            
        protected:
            INLINE Matrix(const dish::IntegerT &m, const dish::IntegerT &n, const bool &dummy) : mMatrix(), mNumRows(m), mNumCols(n)
            {
                assert(mNumRows > 0);
                assert(mNumCols > 0);
                
                mMatrix = dish::ArrayValue::MakeValue(
                    1, 
                    mNumRows, 
                    dish::ArrayTypeAtomic::MakeValue(1, mNumCols, REAL_TYPE)
                );
            }
        
            INLINE std::shared_ptr< dish::iAtomic > element(const dish::IntegerT &m, const dish::IntegerT &n) const { return mMatrix->Element(m)->Element(n); };
        
        public:
            INLINE Matrix(std::shared_ptr< dish::iAtomic > matrix) : mMatrix(matrix), mNumRows(VALUE_INVALID), mNumCols(VALUE_INVALID) 
                { assert(mMatrix); if(!Validate()) { throw dish::MatrixNotValidException(); } };
            
            INLINE Matrix(const dish::IntegerT &m, const dish::IntegerT &n) : mMatrix(), mNumRows(m), mNumCols(n)
            {
                assert(mNumRows > 0);
                assert(mNumCols > 0);
                
                mMatrix = dish::ArrayValue::MakeValue(
                    1, 
                    mNumRows, 
                    dish::ArrayTypeAtomic::MakeValue(1, mNumCols, REAL_TYPE)
                );
                
                //  If the matrix is square initialize it to an identity matrix.
                if(mNumRows == mNumCols)
                {
                    std::shared_ptr< dish::iAtomic > one(dish::RealValue::MakeValue(1.0));
                
                    for(dish::IntegerT i(1); i <= mNumRows; ++i)
                    {
                        mMatrix->Element(i)->Element(i)->Assign(one);
                    }
                }
            }
            
            INLINE Matrix(const Matrix &M) : mMatrix(M.mMatrix), mNumRows(M.mNumRows), mNumCols(M.mNumCols) { assert(mMatrix); };
            
            INLINE const Matrix &operator=(const Matrix &rhs) { mMatrix = rhs.mMatrix; mNumRows = rhs.mNumRows; mNumCols = rhs.mNumCols; return *this; };
            
            INLINE std::shared_ptr< dish::iAtomic > Raw() const { return mMatrix; };
            
            bool Validate() const;
            
            dish::IntegerT NumRows() const;
            dish::IntegerT NumCols() const;
            
            INLINE bool IsSquare() const { return (NumRows() == NumCols()); };
            
            INLINE void SetElement(const dish::IntegerT &m, const dish::IntegerT &n, const dish::RealT &value) { element(m, n)->Assign(value); };
            INLINE void SetElement(const dish::IntegerT &m, const dish::IntegerT &n, std::shared_ptr< dish::iAtomic > value) { assert(value); element(m, n)->Assign(value); };
            INLINE dish::RealT Element(const dish::IntegerT &m, const dish::IntegerT &n) const { return element(m, n)->AsReal(); };
            
            dish::RealT Determinant() const;
            
            INLINE Matrix Invert() const
            {
                const dish::RealT det(Determinant());
                
                if(!dish::IsZero(det))
                {
                    const dish::IntegerT nrows(NumRows());
                    const dish::IntegerT ncols(NumCols());
                
                    Matrix invert(nrows, ncols, SKIP_INITIALIZATION);
                    
                    for(dish::IntegerT m(1); m <= nrows; ++m)
                    {
                        for(dish::IntegerT n(1); n <= ncols; ++n)
                        {
                            invert.SetElement(
                                m,
                                n,
                                Element(m, n) / det
                            );
                        }
                    }
                    
                    return invert;
                }
                
                throw dish::ZeroDeterminantException("The matrix cannot be inverted.");
            }
            
            INLINE void AddRow(const Matrix &M)
            {
                assert(IsSquare());
                
                const dish::IntegerT nrows(NumRows());
                const dish::IntegerT ncols(NumCols());
                
                //  Invalidate the number-of-rows.
                mNumRows = -1;
                
                //  Add each row of M to this matrix.
                for(dish::IntegerT m(1); m <= nrows; ++m)
                {
                    std::shared_ptr< dish::iAtomic > row(
                        dish::ArrayValue::MakeValue(1, ncols, REAL_TYPE)
                    );
                    
                    for(dish::IntegerT n(1); n <= ncols; ++n)
                    {
                        row->Element(n)->Assign(M.Element(m, n));
                    }
                    
                    mMatrix->Add(row);
                }
            }
            
            INLINE void AddColumn(const Matrix &M)
            {
                assert(IsSquare());
                
                const dish::IntegerT nrows(NumRows());
                const dish::IntegerT ncols(NumCols());
                
                //  Invalidate the number-of-columns.
                mNumCols = -1;
                
                //  Add each column of M to this matrix.
                for(dish::IntegerT m(1); m <= nrows; ++m)
                {
                    std::shared_ptr< dish::iAtomic > elem(mMatrix->Element(m));
                
                    for(dish::IntegerT n(1); n <= ncols; ++n)
                    {
                        elem->Add(dish::RealValue::MakeValue(M.Element(m, n)));
                    }
                }
            }
        
    };
    
    ////
    
    std::shared_ptr< dish::iAtomic > Matrix::REAL_TYPE(dish::RealTypeAtomic::MakeValue());
 
    const dish::IntegerT Matrix::VALUE_INVALID(-1);
    
    const bool Matrix::SKIP_INITIALIZATION(false);
    
    dish::IntegerT Matrix::NumRows() const
    {
        if(mNumRows <= 0)
        {
            mNumRows = mMatrix->Member("length")->AsInteger();
            assert(mNumRows > 0);
        }
        
        return mNumRows;
    }
    
    dish::IntegerT Matrix::NumCols() const
    {
        if(mNumCols <= 0)
        {
            mNumCols = mMatrix->Element(1)->Member("length")->AsInteger();
            assert(mNumCols > 0);
        }
        
        return mNumCols;
    }

    bool Matrix::Validate() const
    {
        if(1 == mMatrix->Member("start")->AsInteger())
        {
            const dish::IntegerT last_m(mMatrix->Member("length")->AsInteger());
            dish::IntegerT last_n(-1);
        
            if(last_m > 0)
            {
                for(dish::IntegerT m(1); m <= last_m; ++m)
                {
                    std::shared_ptr< dish::iAtomic > slice(mMatrix->Element(1));
                    assert(slice);
            
                    if(1 == slice->Member("start")->AsInteger())
                    {
                        const dish::IntegerT this_n(slice->Member("length")->AsInteger());
                    
                        if(this_n > 0)
                        {
                            if((last_n < 0) || (last_n == this_n))
                            {
                                last_n = this_n;
                            }
                            else
                            {
                                return false;
                            }
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
        
        return true;
    }

    dish::RealT Matrix::Determinant() const
    {
        if(IsSquare())
        {
            const dish::IntegerT nrows(NumRows());
            assert(nrows > 1);
            
            switch(nrows)
            {
                case 2:
                {
                    /*
                            |a  b|
                        M = |c  d|
                        
                        det(M) = a*d - b*c
                    */
                    const dish::RealT a(Element(1, 1));
                    const dish::RealT b(Element(1, 2));
                    const dish::RealT c(Element(2, 1));
                    const dish::RealT d(Element(2, 2));
                    
                    return ((a * d) - (b * c));
                }
                
                case 3:
                {
                    /*
                            |a  b  c|
                        M = |d  e  f|
                            |g  h  i|
                        
                        det(M) = a*e*i + b*f*g + c*d*h - c*e*g - b*d*i - a*f*h
                    */
                    const dish::RealT a(Element(1, 1));
                    const dish::RealT b(Element(1, 2));
                    const dish::RealT c(Element(1, 3));
                    
                    const dish::RealT d(Element(2, 1));
                    const dish::RealT e(Element(2, 2));
                    const dish::RealT f(Element(2, 3));
                    
                    const dish::RealT g(Element(3, 1));
                    const dish::RealT h(Element(3, 2));
                    const dish::RealT i(Element(3, 3));
                    
                    return (
                        (a * e * i) + (b * f * g) + (c * d * h) - 
                        (c * e * g) - (b * d * i) - (a * f * h)
                    );
                }
                
                default:
                {
                    dish::RealT sign(-1.0);
                    dish::RealT det(0.0);
                
                    for(dish::IntegerT i(1); i <= nrows; ++i)
                    {
                        //  Subdivide this M...
                        Matrix subM(nrows - 1, nrows - 1, SKIP_INITIALIZATION);

                        for(dish::IntegerT m(2); m <= nrows; ++m)
                        {
                            dish::IntegerT n;
                            
                            for(n = 1; n < i; ++n)
                            {
                                subM.SetElement(m - 1, n, element(m, n));
                            }
                            
                            for(++n; n <= nrows; ++n)
                            {
                                subM.SetElement(m - 1, n - 1, element(m, n));
                            }
                        }
                        
                        //  Contribute this iteration to the determinant calculation...
                        sign = -sign;
                        det += sign * Element(1, i) * subM.Determinant();
                    }
                    
                    return det;
                }
                
            }
        
            assert(false);
        }
        
        throw dish::MatrixNotSquareException("Can only calculate the determinant of a square matrix.");
    }

    ////////////////////////////////////////////////////////////////////////////

}

/******************************************************************************

    dish::OneArgMathFunction class definitions

 ******************************************************************************/
 
const std::string dish::OneArgMathFunction::ArgumentName("x");
 
std::shared_ptr< dish::iAtomic > dish::OneArgMathFunction::generateArgumentError() const
{
    std::stringstream message;
    message << "Cannot cast to a numeric value in function '";
    message << mFunctionName;
    message << "'.";

    throw IllegalCastException(message.str());
}
 
std::shared_ptr< dish::iAtomic > dish::OneArgMathFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > arg(getParam(symtab, ArgumentName));
    
    switch(arg->Type())
    {
        case typeBoolean:
        case typeInteger:
        case typeReal:
        case typeString:
        {
            return execute(arg);
        }
        
        case typeArray:
        {
            const IntegerT start(arg->Member("start")->AsInteger());
            const IntegerT finish(arg->Member("finish")->AsInteger());
            
            std::shared_ptr< iAtomic > ret(ArrayValue::MakeValue(start));
            
            for(IntegerT i(start); i <= finish; ++i)
            {
                std::shared_ptr< iAtomic > elem(arg->Element(i));
                
                switch(elem->Type())
                {
                    case typeBoolean:
                    case typeInteger:
                    case typeReal:
                    case typeString:
                    {
                        ret->Add(execute(elem));
                    } break;
                    
                    default:
                    {
                        return generateArgumentError();
                    }
                    
                }
            }
            
            return ret;
        }
        
        default:
        {
            //  Empty
        }
        
    }
    
    return generateArgumentError();
}

#ifdef LANG_LIB_MATH_CORE

/******************************************************************************

    dish::IsFiniteFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::IsFiniteNumberFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    return BooleanValue::MakeLockedValue(std::isfinite(arg->AsReal()));
}

/******************************************************************************

    dish::IsInfiniteNumberFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::IsInfiniteNumberFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    return BooleanValue::MakeLockedValue(std::isinf(arg->AsReal()));
}

/******************************************************************************

    dish::IsNotANumberFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::IsNotANumberFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    return BooleanValue::MakeLockedValue(std::isnan(arg->AsReal()));
}

/******************************************************************************

    dish::IsOddFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::IsOddFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    return BooleanValue::MakeLockedValue(0 != (arg->AsInteger() % 2));
}

/******************************************************************************

    dish::IsEvenFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::IsEvenFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    return BooleanValue::MakeLockedValue(0 == (arg->AsInteger() % 2));
}

/******************************************************************************

    dish::IsNormalNumberFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::IsNormalNumberFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    return BooleanValue::MakeLockedValue(std::isnormal(arg->AsReal()));
}

/******************************************************************************

    dish::AbsFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::AbsFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    switch(arg->Type())
    {
        case typeBoolean:
        case typeInteger:
        {
            const IntegerT value(arg->AsInteger());
        
            return IntegerValue::MakeValue((value >= 0) ? value : -value, LOCKED);
        }
        
        case typeReal:
        case typeString:
        {
            RealT value(arg->AsReal());
            {
                ScopedCheckForError checkforerror;
                value = std::fabs(value);
            }
        
            return RealValue::MakeValue(value, LOCKED);
        }
        
        default:
        {
            //  Empty
        }
        
    }

    return generateArgumentError();
}

/******************************************************************************

    dish::WholeFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::WholeFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    switch(arg->Type())
    {
        case typeBoolean:
        case typeInteger:
        {
            return IntegerValue::MakeValue(arg->AsInteger(), LOCKED);
        }
        
        case typeReal:
        case typeString:
        {
            return RealValue::MakeValue(
                static_cast< RealT >(static_cast< IntegerT >(arg->AsReal())), 
                LOCKED
            );
        }
        
        default:
        {
            //  Empty
        }
        
    }

    return generateArgumentError();
}

/******************************************************************************

    dish::FractionFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::FractionFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    switch(arg->Type())
    {
        case typeBoolean:
        case typeInteger:
        {
            return RealValue::MakeValue(0.0, LOCKED);
        }
        
        case typeReal:
        case typeString:
        {
            const RealT argval(arg->AsReal());
        
            return RealValue::MakeValue(
                argval - static_cast< RealT >(static_cast< IntegerT >(argval)), 
                LOCKED
            );
        }
        
        default:
        {
            //  Empty
        }
        
    }

    return generateArgumentError();
}

/******************************************************************************

    dish::SignOfFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::SignOfFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    switch(arg->Type())
    {
        case typeBoolean:
        case typeInteger:
        {
            const IntegerT value(arg->AsInteger());
            
            if(value > 0)
            {
                return IntegerValue::MakeValue(1, LOCKED);
            }
            
            else if(value < 0)
            {
                return IntegerValue::MakeValue(-1, LOCKED);
            }
            
            else
            {
                return IntegerValue::MakeValue(0, LOCKED);
            }
        }
        
        case typeReal:
        case typeString:
        {
            const RealT value(arg->AsReal());
            
            if(value > 0.0)
            {
                return RealValue::MakeValue(1.0, LOCKED);
            }
            
            else if(value < 0.0)
            {
                return RealValue::MakeValue(-1.0, LOCKED);
            }
            
            else
            {
                return RealValue::MakeValue(0.0, LOCKED);
            }
        }
        
        default:
        {
            //  Empty
        }
        
    }

    return generateArgumentError();
}

/******************************************************************************

    dish::SqrFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::SqrFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    switch(arg->Type())
    {
        case typeBoolean:
        case typeInteger:
        {
            const IntegerT argval(arg->AsInteger());
        
            return IntegerValue::MakeValue(argval * argval, LOCKED);
        }
        
        case typeReal:
        case typeString:
        {
            const RealT argval(arg->AsReal());
        
            return RealValue::MakeValue(argval * argval, LOCKED);
        }
        
        default:
        {
            //  Empty
        }
        
    }

    return generateArgumentError();
}

/******************************************************************************

    dish::SqrtFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::SqrtFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    RealT value(arg->AsReal());
    {
        ScopedCheckForError checkforerror;
        value = std::sqrt(value);
    }

    return RealValue::MakeValue(value, LOCKED);
}

/******************************************************************************

    dish::CubeFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::CubeFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    switch(arg->Type())
    {
        case typeBoolean:
        case typeInteger:
        {
            const IntegerT argval(arg->AsInteger());
        
            return IntegerValue::MakeValue(argval * argval * argval, LOCKED);
        }
        
        case typeReal:
        case typeString:
        {
            const RealT argval(arg->AsReal());
        
            return RealValue::MakeValue(argval * argval * argval, LOCKED);
        }
        
        default:
        {
            //  Empty
        }
        
    }

    return generateArgumentError();
}

/******************************************************************************

    dish::CbrtFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::CbrtFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    RealT value(arg->AsReal());
    {
        ScopedCheckForError checkforerror;
        value = std::cbrt(value);
    }

    return RealValue::MakeValue(value, LOCKED);
}

/******************************************************************************

    dish::LnFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::LnFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    RealT value(arg->AsReal());
    {
        ScopedCheckForError checkforerror;
        value = std::log(value);
    }

    return RealValue::MakeValue(value, LOCKED);
}

/******************************************************************************

    dish::LogFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::LogFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    RealT value(arg->AsReal());
    {
        ScopedCheckForError checkforerror;
        value = std::log10(value);
    }

    return RealValue::MakeValue(value, LOCKED);
}

/******************************************************************************

    dish::Log2Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::Log2Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    const RealT x(getParam(symtab, "x")->AsReal());
    const RealT base(getParam(symtab, "base")->AsReal());
    
    if((x > 0.0) && (base > 0.0))
    {
        RealT xvalue;
        {
            ScopedCheckForError checkforerror;
            xvalue = std::log10(x);
        }
        
        RealT basevalue;
        {
            ScopedCheckForError checkforerror;
            basevalue = std::log10(base);
        }

        return RealValue::MakeValue(Divide(xvalue, basevalue), LOCKED);
    }
    
    throw DomainErrorException("Domain error.");
}

/******************************************************************************

    dish::ExpFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::ExpFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    RealT value(arg->AsReal());
    {
        ScopedCheckForError checkforerror;
        value = std::exp(value);
    }

    return RealValue::MakeValue(value, LOCKED);
}

/******************************************************************************

    dish::RoundFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::RoundFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    const RealT argval(arg->AsReal());

    return RealValue::MakeValue(
        static_cast< IntegerT >((argval >= 0.0) ? (argval + 0.5) : (argval - 0.5)),
        LOCKED
    );
}

/******************************************************************************

    dish::FloorFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::FloorFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);
    
    RealT value(arg->AsReal());
    {
        ScopedCheckForError checkforerror;
        value = std::floor(value);
    }

    return RealValue::MakeValue(value, LOCKED);
}

/******************************************************************************

    dish::CeilFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::CeilFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    RealT value(arg->AsReal());
    {
        ScopedCheckForError checkforerror;
        value = std::ceil(value);
    }

    return RealValue::MakeValue(value, LOCKED);
}

#endif

#ifdef LANG_LIB_MATH_TRIG

/******************************************************************************

    Global trigonometric definitions

 ******************************************************************************/

const dish::RealT dish::PI(std::acos(-1.0));

/******************************************************************************

    dish::DegToRadFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::DegToRadFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    return RealValue::MakeValue(PI * arg->AsReal() / static_cast< RealT >(180.0), LOCKED);
}

/******************************************************************************

    dish::RadToDegFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::RadToDegFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    return RealValue::MakeValue(static_cast< RealT >(180.0) * arg->AsReal() / PI, LOCKED);
}

/******************************************************************************

    dish::SinFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::SinFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    RealT value(arg->AsReal());
    {
        ScopedCheckForError checkforerror;
        value = std::sin(value);
    }

    return RealValue::MakeValue(value, LOCKED);
}

/******************************************************************************

    dish::CosFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::CosFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    RealT value(arg->AsReal());
    {
        ScopedCheckForError checkforerror;
        value = std::cos(value);
    }

    return RealValue::MakeValue(value, LOCKED);
}

/******************************************************************************

    dish::TanFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::TanFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    RealT value(arg->AsReal());
    {
        ScopedCheckForError checkforerror;
        value = std::tan(value);
    }

    return RealValue::MakeValue(value, LOCKED);
}

/******************************************************************************

    dish::ArcSinFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::ArcSinFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    RealT value(arg->AsReal());
    {
        ScopedCheckForError checkforerror;
        value = std::asin(value);
    }

    return RealValue::MakeValue(value, LOCKED);
}

/******************************************************************************

    dish::ArcCosFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::ArcCosFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    RealT value(arg->AsReal());
    {
        ScopedCheckForError checkforerror;
        value = std::acos(value);
    }

    return RealValue::MakeValue(value, LOCKED);
}

/******************************************************************************

    dish::ArcTanFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::ArcTanFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    RealT value(arg->AsReal());
    {
        ScopedCheckForError checkforerror;
        value = std::atan(value);
    }

    return RealValue::MakeValue(value, LOCKED);
}

/******************************************************************************

    dish::CotFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::CotFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    RealT value(arg->AsReal());
    {
        ScopedCheckForError checkforerror;
        value = std::tan(value);
    }

    return RealValue::MakeValue(Divide(1.0, value), LOCKED);
}

/******************************************************************************

    dish::SecFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::SecFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    RealT value(arg->AsReal());
    {
        ScopedCheckForError checkforerror;
        value = std::cos(value);
    }

    return RealValue::MakeValue(Divide(1.0, value), LOCKED);
}

/******************************************************************************

    dish::CscFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::CscFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    RealT value(arg->AsReal());
    {
        ScopedCheckForError checkforerror;
        value = std::sin(value);
    }

    return RealValue::MakeValue(Divide(1.0, value), LOCKED);
}

/******************************************************************************

    dish::ArcCotFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::ArcCotFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    const RealT argval(arg->AsReal());

    RealT value((argval * argval) + 1.0);
    {
        ScopedCheckForError checkforerror;
        value = std::sqrt(value);
    }
    
    value = Divide(argval, value);
    {
        ScopedCheckForError checkforerror;
        value = std::asin(value);
    }

    return RealValue::MakeValue(
        ((argval >= 0.0) ? 0.5 : -0.5) * PI - value,
        LOCKED
    );
}

/******************************************************************************

    dish::ArcSecFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::ArcSecFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    const RealT argval(arg->AsReal());
    
    if((argval < -1.0) || (argval > 1.0))
    {
        RealT value((argval * argval) - 1.0);
        {
            ScopedCheckForError checkforerror;
            value = std::sqrt(value);
        }
        
        {
            ScopedCheckForError checkforerror;
            value = std::atan(value);
        }
    
        if(argval > 1.0)
        {
            return RealValue::MakeValue(value, LOCKED);
        }
        
        else if(argval < -1.0)
        {
            return RealValue::MakeValue(PI - value, LOCKED);
        }
    }

    throw DomainErrorException("Domain error.");
}

/******************************************************************************

    dish::ArcCscFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::ArcCscFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    const RealT argval(arg->AsReal());
    
    if((argval < -1.0) || (argval > 1.0))
    {
        RealT value((argval * argval) - 1.0);
        {
            ScopedCheckForError checkforerror;
            value = std::sqrt(value);
        }
        
        value = Divide(value, argval);
        {
            ScopedCheckForError checkforerror;
            value = std::acos(value);
        }
    
        if(argval > 1.0)
        {
            return RealValue::MakeValue(value, LOCKED);
        }
        
        else if(argval < -1.0)
        {
            return RealValue::MakeValue(-value, LOCKED);
        }
    }

    throw DomainErrorException("Domain error.");
}

#endif

#ifdef LANG_LIB_MATH_HYPERBOLIC

/******************************************************************************

    dish::SinhFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::SinhFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    RealT value(arg->AsReal());
    {
        ScopedCheckForError checkforerror;
        value = std::sinh(value);
    }

    return RealValue::MakeValue(value, LOCKED);
}

/******************************************************************************

    dish::CoshFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::CoshFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    RealT value(arg->AsReal());
    {
        ScopedCheckForError checkforerror;
        value = std::cosh(value);
    }

    return RealValue::MakeValue(value, LOCKED);
}

/******************************************************************************

    dish::TanhFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::TanhFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    RealT value(arg->AsReal());
    {
        ScopedCheckForError checkforerror;
        value = std::tanh(value);
    }

    return RealValue::MakeValue(value, LOCKED);
}

/******************************************************************************

    dish::ArcSinhFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::ArcSinhFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    RealT value(arg->AsReal());
    {
        ScopedCheckForError checkforerror;
        value = std::asinh(value);
    }

    return RealValue::MakeValue(value, LOCKED);
}

/******************************************************************************

    dish::ArcCoshFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::ArcCoshFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    RealT value(arg->AsReal());
    {
        ScopedCheckForError checkforerror;
        value = std::acosh(value);
    }

    return RealValue::MakeValue(value, LOCKED);
}

/******************************************************************************

    dish::ArcTanhFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::ArcTanhFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    RealT value(arg->AsReal());
    {
        ScopedCheckForError checkforerror;
        value = std::atanh(value);
    }

    return RealValue::MakeValue(value, LOCKED);
}

/******************************************************************************

    dish::SechFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::SechFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    RealT denom(arg->AsReal());
    {
        ScopedCheckForError checkforerror;
        denom = std::cosh(denom);
    }
    
    if(!IsZero(denom))
    {
        return RealValue::MakeValue(Divide(1.0, denom), LOCKED);
    }
    
    throw DomainErrorException("Domain error.");
}

/******************************************************************************

    dish::CschFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::CschFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    RealT denom(arg->AsReal());
    {
        ScopedCheckForError checkforerror;
        denom = std::sinh(denom);
    }
    
    if(!IsZero(denom))
    {
        return RealValue::MakeValue(Divide(1.0, denom), LOCKED);
    }

    throw DomainErrorException("Domain error.");
}

/******************************************************************************

    dish::CothFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::CothFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    RealT denom(arg->AsReal());
    {
        ScopedCheckForError checkforerror;
        denom = std::sinh(denom);
    }
    
    if(IsZero(denom))
    {
        throw DomainErrorException("Domain error.");
    }
    
    RealT numer(arg->AsReal());
    {
        ScopedCheckForError checkforerror;
        numer = std::cosh(numer);
    }

    return RealValue::MakeValue(Divide(numer, denom), LOCKED);
}

/******************************************************************************

    dish::ArcSechFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::ArcSechFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    const RealT tmp(Divide(1.0, arg->AsReal()));

    RealT tmp1(tmp - 1.0);
    {
        ScopedCheckForError checkforerror;
        tmp1 = std::sqrt(tmp1);
    }

    RealT tmp2(tmp + 1.0);
    {
        ScopedCheckForError checkforerror;
        tmp2 = std::sqrt(tmp2);
    }
    
    RealT value(tmp1 * tmp2 + tmp);
    {
        ScopedCheckForError checkforerror;
        value = std::log(value);
    }

    return RealValue::MakeValue(value, LOCKED);
}

/******************************************************************************

    dish::ArcCschFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::ArcCschFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    const RealT argval(arg->AsReal());
    const RealT tmp(Divide(1.0, argval * argval));

    RealT value(tmp + 1.0);
    {
        ScopedCheckForError checkforerror;
        value = std::sqrt(value);
    }
    
    value += Divide(1.0, argval);
    
    {
        ScopedCheckForError checkforerror;
        value = std::log(value);
    }

    return RealValue::MakeValue(value, LOCKED);
}

/******************************************************************************

    dish::ArcCothFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::ArcCothFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    assert(arg);

    const RealT tmp(Divide(1.0, arg->AsReal()));
    
    RealT tmp1(tmp + 1.0);
    {
        ScopedCheckForError checkforerror;
        tmp1 = std::log(tmp1);
    }
    
    RealT tmp2;
    {
        ScopedCheckForError checkforerror;
        tmp2 = std::log(1.0 - tmp);
    }

    return RealValue::MakeValue((tmp1 - tmp2) / 2.0, LOCKED);
}

#endif

#ifdef LANG_LIB_MATH_COMPLEX

/******************************************************************************

    dish::Language-Imaginary function definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::CreateImaginaryStructureType()
{
    static std::shared_ptr< StructureTypeAtomic > structure;
    
    if(0 == structure.get())
    {
        std::shared_ptr< RealTypeAtomic > real_type(RealTypeAtomic::MakeValue());
    
        structure = StructureTypeAtomic::MakeValue();
        structure->Add("r", real_type);
        structure->Add("i", real_type);
    }

    return structure;
}

namespace
{

    INLINEC void ArgToComplex(std::shared_ptr< dish::iAtomic > arg, dish::RealT &r, dish::RealT &i)
    {
        assert(arg);
    
        switch(arg->Type())
        {
            case dish::iAtomic::typeBoolean:
            case dish::iAtomic::typeInteger:
            case dish::iAtomic::typeReal:
            case dish::iAtomic::typeString:
            {
                r = arg->AsReal();
                i = 0.0;
            } break;
            
            case dish::iAtomic::typeStructure:
            {
                r = arg->Member("r")->AsReal();
                i = arg->Member("i")->AsReal();
            } break;
            
            default:
            {
                throw dish::IllegalCastException("Cannot cast argument to a complex number.");
            }
            
        }
    }

}

/******************************************************************************

    dish::ImaginaryCreate1Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::ImaginaryCreate1Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    return CreateImaginaryStructure(
        getParam(symtab, "r")->AsReal(), 
        0.0
    );
}

/******************************************************************************

    dish::ImaginaryCreate2Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::ImaginaryCreate2Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    return CreateImaginaryStructure(
        getParam(symtab, "r")->AsReal(), 
        getParam(symtab, "i")->AsReal()
    );
}

/******************************************************************************

    dish::ImaginaryToStringFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::ImaginaryToStringFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > arg(getParam(symtab, "arg"));

    std::stringstream out;
    out << "(";
    out << arg->Member("r")->AsReal();
    out << " + ";
    out << arg->Member("i")->AsReal();
    out << "i)";
    
    return StringValue::MakeValue(out.str());
}

/******************************************************************************

    dish::ImaginaryIsEqualFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::ImaginaryIsEqualFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    RealT lhs_r;
    RealT lhs_i;
    ArgToComplex(getParam(symtab, "lhs"), lhs_r, lhs_i);
    
    RealT rhs_r;
    RealT rhs_i;
    ArgToComplex(getParam(symtab, "rhs"), rhs_r, rhs_i);

    return BooleanValue::MakeLockedValue(IsEqual(lhs_r, rhs_r) && IsEqual(lhs_i, rhs_i));
}

/******************************************************************************

    dish::ImaginaryIsNotEqualFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::ImaginaryIsNotEqualFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    RealT lhs_r;
    RealT lhs_i;
    ArgToComplex(getParam(symtab, "lhs"), lhs_r, lhs_i);
    
    RealT rhs_r;
    RealT rhs_i;
    ArgToComplex(getParam(symtab, "rhs"), rhs_r, rhs_i);

    return BooleanValue::MakeLockedValue((!IsEqual(lhs_r, rhs_r)) || (!IsEqual(lhs_i, rhs_i)));
}

/******************************************************************************

    dish::ImaginaryAddFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::ImaginaryAddFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    RealT a;
    RealT b;
    ArgToComplex(getParam(symtab, "arg1"), a, b);
    
    RealT c;
    RealT d;
    ArgToComplex(getParam(symtab, "arg2"), c, d);

    return CreateImaginaryStructure(a + c, b + d);
}

/******************************************************************************

    dish::ImaginarySubtractFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::ImaginarySubtractFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    RealT a;
    RealT b;
    ArgToComplex(getParam(symtab, "arg1"), a, b);
    
    RealT c;
    RealT d;
    ArgToComplex(getParam(symtab, "arg2"), c, d);

    return CreateImaginaryStructure(a - c, b - d);
}

/******************************************************************************

    dish::ImaginaryMultiplyFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::ImaginaryMultiplyFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    RealT a;
    RealT b;
    ArgToComplex(getParam(symtab, "arg1"), a, b);
    
    RealT c;
    RealT d;
    ArgToComplex(getParam(symtab, "arg2"), c, d);

    return CreateImaginaryStructure(
        (a * c) - (b * d),
        (b * c) + (a * d)
    );
}

/******************************************************************************

    dish::ImaginaryDivideFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::ImaginaryDivideFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    RealT a;
    RealT b;
    ArgToComplex(getParam(symtab, "arg1"), a, b);
    
    RealT c;
    RealT d;
    ArgToComplex(getParam(symtab, "arg2"), c, d);
    
    const RealT denom((c * c) + (d * d));

    return CreateImaginaryStructure(
        Divide((a * c) + (b * d), denom),
        Divide((b * c) - (a * d), denom)
    );
}

/******************************************************************************

    dish::ImaginarySqrtFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::ImaginarySqrtFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    RealT r;
    RealT i;
    ArgToComplex(getParam(symtab, "arg"), r, i);
    
    if(!IsZero(i))
    {
        RealT tmp((r * r) + (i * i));
        {
            ScopedCheckForError checkforerror;
            tmp = std::sqrt(tmp);
        }
        
        RealT realval(0.5 * (r + tmp));
        {
            ScopedCheckForError checkforerror;
            realval = std::sqrt(realval);
        }
        
        RealT imagval(SignOf(i) * 0.5 * (tmp - r));
        {
            ScopedCheckForError checkforerror;
            imagval = std::sqrt(imagval);
        }
    
        return CreateImaginaryStructure(realval, imagval);
    }
    
    {
        ScopedCheckForError checkforerror;
        r = std::sqrt(r);
    }
    
    return CreateImaginaryStructure(r, 0.0);
}

/******************************************************************************

    dish::ImaginarySqrFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::ImaginarySqrFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    RealT r;
    RealT i;
    ArgToComplex(getParam(symtab, "arg"), r, i);
    
    return CreateImaginaryStructure((r * r) - (i * i), (2.0 * r * i));
}

/******************************************************************************

    dish::ImaginaryReciprocalFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::ImaginaryReciprocalFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    RealT r;
    RealT i;
    ArgToComplex(getParam(symtab, "arg"), r, i);
    
    const RealT denom((r * r) + (i * i));
    
    return CreateImaginaryStructure(
        Divide(r, denom),
        Divide(i, denom)
    );
}

/******************************************************************************

    dish::ImaginaryConjugateFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::ImaginaryConjugateFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    RealT r;
    RealT i;
    ArgToComplex(getParam(symtab, "arg"), r, i);
    
    return CreateImaginaryStructure(r, -i);
}

#endif

#ifdef LANG_LIB_MATH_RANDOM

namespace
{

    std::unique_ptr< dish::iRNG > RandomNumberGenerator(
        new dish::RNG(static_cast< dish::IntegerT >(std::time(NULL)))
    );
    
}

/******************************************************************************

    dish::RandomSeedFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::RandomSeedFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const IntegerT seed_value(getParam(symtab, "seed")->AsInteger());
    RandomNumberGenerator.reset(new RNG(seed_value));
    
    return IntegerValue::MakeValue(seed_value, LOCKED);
}

/******************************************************************************

    dish::RandomBooleanFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::RandomBooleanFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    assert(RandomNumberGenerator);

    return BooleanValue::MakeLockedValue(0 != (**RandomNumberGenerator % 2));
}

/******************************************************************************

    dish::RandomIntegerFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::RandomIntegerFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    assert(RandomNumberGenerator);

    return IntegerValue::MakeValue(**RandomNumberGenerator & 0x7FFFFFFFFFFFFFFF, LOCKED);
}

/******************************************************************************

    dish::RandomInteger1Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::RandomInteger1Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    assert(RandomNumberGenerator);

    return IntegerValue::MakeValue(
        (**RandomNumberGenerator & 0x7FFFFFFFFFFFFFFF) % getParam(symtab, "max")->AsInteger(),
        LOCKED
    );
}

/******************************************************************************

    dish::RandomInteger2Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::RandomInteger2Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    assert(RandomNumberGenerator);
    
    const IntegerT min(getParam(symtab, "min")->AsInteger());
    const IntegerT delta(getParam(symtab, "max")->AsInteger() - min + 1);

    return IntegerValue::MakeValue(
        ((**RandomNumberGenerator & 0x7FFFFFFFFFFFFFFF) % delta) + min,
        LOCKED
    );
}

/******************************************************************************

    dish::RandomRealFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::RandomRealFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    assert(RandomNumberGenerator);
    
    static const long double denom(static_cast< long double >(RandomNumberGenerator->Maximum()));
    
    const long double numer(static_cast< long double >(**RandomNumberGenerator));

    return RealValue::MakeValue(static_cast< RealT >(Divide(numer, denom)), LOCKED);
}

/******************************************************************************

    dish::RandomReal1Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::RandomReal1Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    assert(RandomNumberGenerator);
    
    static const long double denom(static_cast< long double >(RandomNumberGenerator->Maximum()));
    
    const long double numer(static_cast< long double >(**RandomNumberGenerator));
    const long double max(static_cast< long double >(getParam(symtab, "max")->AsReal()));

    return RealValue::MakeValue(static_cast< RealT >(Divide((numer * max), denom)), LOCKED);
}

/******************************************************************************

    dish::RandomReal2Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::RandomReal2Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    assert(RandomNumberGenerator);
    
    static const long double denom(static_cast< long double >(RandomNumberGenerator->Maximum()));
    
    const long double numer(static_cast< long double >(**RandomNumberGenerator));
    
    const long double min(static_cast< long double >(getParam(symtab, "min")->AsReal()));
    const long double delta(static_cast< long double >(getParam(symtab, "max")->AsReal()) - min);

    return RealValue::MakeValue(static_cast< RealT >(delta * Divide(numer, denom) + min), LOCKED);
}

/******************************************************************************

    dish::RandomMaxFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::RandomMaxFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    assert(RandomNumberGenerator);
    
    static std::shared_ptr< iAtomic > max(
        IntegerValue::MakeValue(
            static_cast< IntegerT >(RandomNumberGenerator->Maximum() & 0x7FFFFFFFFFFFFFFF),
            LOCKED
        )
    );

    return max;
}

/******************************************************************************

    dish::RandomBitIntegerFunction class definitions

 ******************************************************************************/

/*
    This function exists to create the most random 63-bit, signed integer value
    possible. It is widely held that the low-order bit in a pseudo-random number
    is the most random bit in the value, so we will construct an integer out of
    the low-order bits of 63 subsequest random integers from the current random 
    number generator's sequence.
*/
std::shared_ptr< dish::iAtomic > dish::RandomBitIntegerFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    assert(RandomNumberGenerator);
    
    IntegerT value(**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    //  Only 7 bits here because IntegerT is assumed to be a signed integer.
    
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    value = (value << 1) + (**RandomNumberGenerator % 2);
    
    return IntegerValue::MakeValue(value & 0x7FFFFFFFFFFFFFFF, LOCKED);
}

/******************************************************************************

    Random-number-generator function definitions

 ******************************************************************************/

const dish::iRNG &dish::RngInstance()
{
    return *RandomNumberGenerator;
}

const dish::iRNG &dish::RngInstance(const dish::IntegerT &seed)
{
    if(seed > 0)
    {
        RandomNumberGenerator.reset(new dish::RNG(seed));
    }
    
    return *RandomNumberGenerator;
}

#endif

#ifdef LANG_LIB_MATH_MATRIX

/******************************************************************************

    dish::CreateMatrixTFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::CreateMatrixTFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const IntegerT m(getParam(symtab, "m")->AsInteger());
    const IntegerT n(getParam(symtab, "n")->AsInteger());

    if((m > 0) && (n > 0))
    {
        return ArrayTypeAtomic::MakeValue(
            1,
            m,
            ArrayTypeAtomic::MakeValue(1, n, RealTypeAtomic::MakeValue())
        );
    }
    
    std::stringstream message;
    message << "Matrix dimensions must be >= 0 (";
    message << m;
    message << ", ";
    message << n;
    message << ").";

    throw IllegalIndexException(message.str());
}

/******************************************************************************

    dish::CreateMatrixFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::CreateMatrixFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const IntegerT m(getParam(symtab, "m")->AsInteger());
    const IntegerT n(getParam(symtab, "n")->AsInteger());

    if((m > 0) && (n > 0))
    {
        Matrix M(m, n);
        
        return M.Raw();
    }
    
    std::stringstream message;
    message << "Matrix dimensions must be >= 0 (";
    message << m;
    message << ", ";
    message << n;
    message << ").";

    throw IllegalIndexException(message.str());
}

/******************************************************************************

    dish::MatrixValidateFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::MatrixValidateFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    Matrix M(getParam(symtab, "M"));
    
    return BooleanValue::MakeLockedValue(M.Validate());
}

/******************************************************************************

    dish::MatrixNumRowsFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::MatrixNumRowsFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    Matrix M(getParam(symtab, "M"));

    return IntegerValue::MakeValue(M.NumRows());
}

/******************************************************************************

    dish::MatrixNumColumnsFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::MatrixNumColumnsFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    Matrix M(getParam(symtab, "M"));

    return IntegerValue::MakeValue(M.NumCols());
}

/******************************************************************************

    dish::MatrixIsSquareFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::MatrixIsSquareFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    Matrix M(getParam(symtab, "M"));

    return BooleanValue::MakeLockedValue(M.IsSquare());
}

/******************************************************************************

    dish::MatrixInitialize1Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::MatrixInitialize1Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    Matrix M(getParam(symtab, "M"));
    
    if(M.IsSquare())
    {
        for(IntegerT m(1); m <= M.NumRows(); ++m)
        {
            for(IntegerT n(1); n <= M.NumCols(); ++n)
            {
                M.SetElement(m, n, (m != n) ? RealValue::MakeValue(0.0) : RealValue::MakeValue(1.0));
            }
        }
    }
    else
    {
        for(IntegerT m(1); m <= M.NumRows(); ++m)
        {
            for(IntegerT n(1); n <= M.NumCols(); ++n)
            {
                M.SetElement(m, n, RealValue::MakeValue(0.0));
            }
        }
    }
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::MatrixInitialize2Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::MatrixInitialize2Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    Matrix M(getParam(symtab, "M"));
    std::shared_ptr< iAtomic > value(getParam(symtab, "value"));
    
    for(IntegerT m(1); m <= M.NumRows(); ++m)
    {
        for(IntegerT n(1); n <= M.NumCols(); ++n)
        {
            M.SetElement(m, n, value->Clone());
        }
    }
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::MatrixRowSliceFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::MatrixRowSliceFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    Matrix M(getParam(symtab, "M"));
    const IntegerT row(getParam(symtab, "row")->AsInteger());

    Matrix slice(1, M.NumCols());
    
    for(IntegerT n(1); n <= M.NumCols(); ++n)
    {
        slice.SetElement(1, n, RealValue::MakeValue(M.Element(row, n)));
    }
    
    return slice.Raw();
}

/******************************************************************************

    dish::MatrixColumnSliceFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::MatrixColumnSliceFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    Matrix M(getParam(symtab, "M"));
    const IntegerT col(getParam(symtab, "col")->AsInteger());

    Matrix slice(M.NumRows(), 1);
    
    for(IntegerT m(1); m <= M.NumRows(); ++m)
    {
        slice.SetElement(m, 1, RealValue::MakeValue(M.Element(m, col)));
    }

    return slice.Raw();
}

/******************************************************************************

    dish::MatrixTransposeFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::MatrixTransposeFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    Matrix M(getParam(symtab, "M"));
    Matrix N(M.NumCols(), M.NumRows());
    
    for(IntegerT m(1); m <= M.NumRows(); ++m)
    {
        for(IntegerT n(1); n <= M.NumCols(); ++n)
        {
            N.SetElement(n, m, RealValue::MakeValue(M.Element(m, n)));
        }
    }

    return N.Raw();
}

/******************************************************************************

    dish::MatrixDeterminantFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::MatrixDeterminantFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    Matrix M(getParam(symtab, "M"));
    
    return RealValue::MakeValue(M.Determinant());
}

/******************************************************************************

    dish::MatrixInvertFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::MatrixInvertFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    Matrix M(getParam(symtab, "M"));
    
    return M.Invert().Raw();
}

/******************************************************************************

    dish::MatrixAddFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::MatrixAddFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    Matrix arg1(getParam(symtab, "arg1"));
    Matrix arg2(getParam(symtab, "arg2"));
    
    const IntegerT nrows(arg1.NumRows());
    const IntegerT ncols(arg1.NumCols());
    
    if((nrows == arg2.NumRows()) && (ncols == arg2.NumCols()))
    {
        Matrix tmp(nrows, ncols);
        
        for(IntegerT m(1); m <= nrows; ++m)
        {
            for(IntegerT n(1); n <= ncols; ++n)
            {
                tmp.SetElement(
                    m, n, RealValue::MakeValue(arg1.Element(m, n) + arg2.Element(m, n))
                );
            }
        }
        
        return tmp.Raw();
    }
    
    throw MatrixDimensionErrorException("The dimensions of the argument mitrices differ.");
}

/******************************************************************************

    dish::MatrixSubtractFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::MatrixSubtractFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    Matrix arg1(getParam(symtab, "arg1"));
    Matrix arg2(getParam(symtab, "arg2"));
    
    const IntegerT nrows(arg1.NumRows());
    const IntegerT ncols(arg1.NumCols());
    
    if((nrows == arg2.NumRows()) && (ncols == arg2.NumCols()))
    {
        Matrix tmp(nrows, ncols);
        
        for(IntegerT m(1); m <= nrows; ++m)
        {
            for(IntegerT n(1); n <= ncols; ++n)
            {
                tmp.SetElement(
                    m, n, RealValue::MakeValue(arg1.Element(m, n) - arg2.Element(m, n))
                );
            }
        }
        
        return tmp.Raw();
    }
    
    throw MatrixDimensionErrorException("The dimensions of the argument mitrices differ.");
}

/******************************************************************************

    dish::MatrixMultiplyFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::MatrixMultiplyFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > arg1(getParam(symtab, "arg1"));
    std::shared_ptr< iAtomic > arg2(getParam(symtab, "arg2"));

    switch(arg1->Type())
    {
        case typeInteger:
        case typeReal:
        case typeString:
        {
            if(typeArray == arg2->Type())
            {
                const RealT arg1_value(arg1->AsReal());
                Matrix arg2M(arg2);
                
                const IntegerT nrows(arg2M.NumRows());
                const IntegerT ncols(arg2M.NumCols());
                Matrix product(nrows, ncols);
    
                for(IntegerT m(1); m <= nrows; ++m)
                {
                    for(IntegerT n(1); n <= ncols; ++n)
                    {
                        product.SetElement(m, n, RealValue::MakeValue(arg1_value * arg2M.Element(m, n)));
                    }
                }
                
                return product.Raw();
            }
            
            throw MatrixDimensionErrorException("At least one argument must be a matrix.");
        };
        
        case typeArray:
        {
            switch(arg2->Type())
            {
                case typeInteger:
                case typeReal:
                case typeString:
                {
                    Matrix arg1M(arg1);
                    const RealT arg2_value(arg2->AsReal());
                    
                    const IntegerT nrows(arg1M.NumRows());
                    const IntegerT ncols(arg1M.NumCols());
                    Matrix product(nrows, ncols);
        
                    for(IntegerT m(1); m <= nrows; ++m)
                    {
                        for(IntegerT n(1); n <= ncols; ++n)
                        {
                            product.SetElement(m, n, RealValue::MakeValue(arg1M.Element(m, n) * arg2_value));
                        }
                    }
                    
                    return product.Raw();
                };
                
                case typeArray:
                {
                    Matrix arg1M(arg1);
                    Matrix arg2M(arg2);
                    
                    const IntegerT nrows(arg1M.NumRows());
                    const IntegerT ncols(arg2M.NumCols());
                    Matrix product(nrows, ncols);
                    
                    for(IntegerT m(1); m <= nrows; ++m)
                    {
                        for(IntegerT n(1); n <= ncols; ++n)
                        {
                            RealT tmp(0.0);
                            
                            for(IntegerT i(1); i <= nrows; ++i)
                            {
                                tmp += arg1M.Element(m, i) * arg2M.Element(i, n);
                            }
                            
                            product.SetElement(m, n, RealValue::MakeValue(tmp));
                        }
                    }
                    
                    return product.Raw();
                };
                
                default:
                {
                    //  Empty
                }
                
            }
            
            throw MatrixDimensionErrorException("At least one argument must be a matrix.");
        };
        
        default:
        {
            //  Empty
        }
        
    }
    
    throw MatrixDimensionErrorException("Matrix-multiplication valid only on integer, real, and matrix arguments.");
}

/******************************************************************************

    dish::MatrixEqualFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::MatrixEqualFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    Matrix arg1(getParam(symtab, "arg1"));
    Matrix arg2(getParam(symtab, "arg2"));
    
    bool equal(
        (arg1.NumRows() == arg2.NumRows()) && (arg1.NumCols() == arg2.NumCols())
    );
    
    if(equal)
    {
        const IntegerT last_m(arg1.NumRows());
        for(IntegerT m(1); equal && (m <= last_m); ++m)
        {
            const IntegerT last_n(arg1.NumCols());
            for(IntegerT n(1); equal && (n <= last_n); ++n)
            {
                if(!IsEqual(arg1.Element(m, n), arg2.Element(m, n)))
                {
                    equal = false;
                }
            }
        }
        
    }

    return BooleanValue::MakeLockedValue(equal);
}

/******************************************************************************

    dish::MatrixAddRowFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::MatrixAddRowFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    Matrix dest(getParam(symtab, "dest"));
    Matrix src(getParam(symtab, "src"));
    
    if(dest.NumCols() == src.NumCols())
    {
        dest.AddRow(src);
        
        return dest.Raw();
    }
    
    throw MatrixDimensionErrorException("The 'src' and 'dest' matrix dimensions are incompatible.");
}

/******************************************************************************

    dish::MatrixAddColumnFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::MatrixAddColumnFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    Matrix dest(getParam(symtab, "dest"));
    Matrix src(getParam(symtab, "src"));
    
    if(dest.NumRows() == src.NumRows())
    {
        dest.AddColumn(src);
        
        return dest.Raw();
    }
    
    throw MatrixDimensionErrorException("The 'src' and 'dest' matrix dimensions are incompatible.");
}

/******************************************************************************

    dish::MatrixToStringFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::MatrixToStringFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    Matrix M(getParam(symtab, "M"));
    
    std::stringstream out;
    
    const IntegerT last_m(M.NumRows());
    for(IntegerT m(1); m <= last_m; ++m)
    {
        out << "[  ";
    
        const IntegerT last_n(M.NumCols());
        for(IntegerT n(1); n <= last_n; ++n)
        {
            out << M.Element(m, n);
            out << "  ";
        }
        
        out << "]";
        out << std::endl;
    }
    
    return StringValue::MakeValue(out.str());
}

#endif

#ifdef LANG_LIB_MATH_INTEGER

/******************************************************************************

    dish::FactorialFunction class definitions

 ******************************************************************************/
 
namespace
{

    INLINEC dish::IntegerT product(dish::IntegerT min, const dish::IntegerT &max)
    {
        dish::IntegerT prod(1);
        
        while(min <= max)
        {
            prod *= min++;
        }
        
        return prod;
    }
    
    INLINEC dish::IntegerT factorial(const dish::IntegerT &x)
    {
        if(x >= 0)
        {
            switch(x)
            {
                case 0:
                case 1:
                {
                    return 1;
                }
                
                case 2:
                {
                    return 2 * 1;
                }
                
                case 3:
                {
                    return 3 * 2 * 1;
                }
                
                case 4:
                {
                    return 4 * 3 * 2 * 1;
                }
                
                case 5:
                {
                    return 5 * 4 * 3 * 2 * 1;
                }
                
                case 6:
                {
                    return 6 * 5 * 4 * 3 * 2 * 1;
                }
                
                case 7:
                {
                    return 7 * 6 * 5 * 4 * 3 * 2 * 1;
                }
                
                case 8:
                {
                    return 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1;
                }
                
                case 9:
                {
                    return 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1;
                }
                
                case 10:
                {
                    return 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1;
                }
                
                default:
                {
                    return (10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1) * product(11, x);
                }
            }
        }
        
        assert(false);
    }

}
 
std::shared_ptr< dish::iAtomic > dish::FactorialFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    const IntegerT argval(arg->AsInteger());
    
    if(argval >= 0)
    {
        return IntegerValue::MakeValue(factorial(argval), LOCKED);
    }
    
    throw DomainErrorException("Domain error.");
}

/******************************************************************************

    dish::BinomialCoefficientFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::BinomialCoefficientFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const IntegerT n(getParam(symtab, "n")->AsInteger());
    const IntegerT i(getParam(symtab, "i")->AsInteger());
    
    if((i >= 0) && (n >= i))
    {
        if(n <= 10)
        {
            return IntegerValue::MakeValue(Divide(factorial(n), factorial(i) * factorial(n - i)), LOCKED);
        }
        else
        {
            const IntegerT tmp(n - i);

            return IntegerValue::MakeValue(
                (tmp >= i) ? Divide(product(tmp + 1, n), factorial(i)) : Divide(product(i + 1, n), factorial(tmp)), 
                LOCKED
            );
        }
    }
    
    throw DomainErrorException("Domain error.");
}

/******************************************************************************

    dish::GreatestCommonDenomonatorFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::GreatestCommonDenomonatorFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    IntegerT a(getParam(symtab, "a")->AsInteger());
    IntegerT b(getParam(symtab, "b")->AsInteger());
    
    if((a > 0) && (b > 0))
    {
        while(0 != b)
        {
            const dish::IntegerT tmp(b);
            b = a % b;
            a = tmp;
        }
        
        return IntegerValue::MakeValue(a, LOCKED);
    }
    
    throw DomainErrorException("Domain error.");
}

/******************************************************************************

    dish::FibonacciFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::FibonacciFunction::execute(std::shared_ptr< dish::iAtomic > arg) const
{
    IntegerT argval(arg->AsInteger());
    
    if(argval >= 0)
    {
        switch(argval)
        {
            case 0:
            case 1:
            {
                return IntegerValue::MakeValue(1, LOCKED);
            }
            
            default:
            {
                IntegerT x_2(1);
                IntegerT x_1(1);
                IntegerT x(2);
                
                while(argval-- > 2)
                {
                    x_2 = x_1;
                    x_1 = x;
                    
                    x = x_1 + x_2;
                }
                
                return IntegerValue::MakeValue(x, LOCKED);
            }
            
        }
    }
    
    throw DomainErrorException("Domain error.");
}

#endif


