/*
    This file is part of the DISH programming language, Copyright 2014-2018 by 
    Chris Buck.
    
    DISH is free software for non-commercial use; you can redistribute it and/or
    modify it provided
    
        (1) The following Copyright notice is displayed at runtime and in any
            accompanying documentation:
    
            DISH programming language copyright (c) 2014-2018 by Chris Buck.
        
        (2) All source files duplicate this copyright statement in full.
        
    Commercial licenses can be negotiated by contacting Chris Buck at
    chrisbuck1220@hotmail.com.

    DISH is distributed in the hope that it will be useful, but WITHOUT ANY 
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS 
    FOR A PARTICULAR PURPOSE.
*/

#ifndef DISH_LANGID_H
#define DISH_LANGID_H

/******************************************************************************

    Version numbers
    
 ******************************************************************************/
 
#define DISH_LANGID_InterpreterVersion                          "InterpreterVersion"
#define DISH_LANGID_LanguageVersion                             "LanguageVersion"
#define DISH_LANGID_LibraryVersion                              "LibraryVersion"

/******************************************************************************

    Core run-time IDs.
    
 ******************************************************************************/

#define DISH_LANGID_IS_LIB_CORE                                 "IS_LIB_CORE"
 
#define DISH_LANGID_NULL                                        "NULL"
 
#define DISH_LANGID_NOINDENT                                    "NOINDENT"

#define DISH_LANGID_IsEntryPoint                                "IsEntryPoint"
#define DISH_LANGID_ReleaseCachedParseTreeNodes                 "ReleaseCachedParseTreeNodes"

#define DISH_LANGID_VersionT                                    "VersionT"
#define DISH_LANGID_MakeVersion                                 "MakeVersion"
#define DISH_LANGID_VersionLessThan                             "VersionLessThan"
#define DISH_LANGID_VersionEqual                                "VersionEqual"
#define DISH_LANGID_VersionAsString                             "VersionAsString"

#define DISH_LANGID_GetEnvironmentVariable                      "GetEnvironmentVariable"

#define DISH_LANGID_Terminate                                   "Terminate"
#define DISH_LANGID_Sleep                                       "Sleep"

#define DISH_LANGID_System                                      "System"
#define DISH_LANGID_Execute                                     "Execute"

#define DISH_LANGID_Copy                                        "Copy"
#define DISH_LANGID_Clone                                       "Clone"

#define DISH_LANGID_AsBoolean                                   "AsBoolean"
#define DISH_LANGID_AsInteger                                   "AsInteger"
#define DISH_LANGID_AsReal                                      "AsReal"
#define DISH_LANGID_AsString                                    "AsString"

#define DISH_LANGID_Append                                      "Append"
#define DISH_LANGID_Insert                                      "Insert"

#define DISH_LANGID_CompareLessThan                             "CompareLessThan"
#define DISH_LANGID_CompareGreaterThan                          "CompareGreaterThan"
#define DISH_LANGID_CompareEqual                                "CompareEqual"

#define DISH_LANGID_SORT_DESCENDING                             "SORT_DESCENDING"
#define DISH_LANGID_SORT_ASCENDING                              "SORT_ASCENDING"
#define DISH_LANGID_EQUAL                                       "EQUAL"

#define DISH_LANGID_Sort                                        "Sort"
#define DISH_LANGID_Find                                        "Find"
#define DISH_LANGID_FindSorted                                  "FindSorted"
#define DISH_LANGID_Swap                                        "Swap"

#define DISH_LANGID_IsLocked                                    "IsLocked"

#define DISH_LANGID_IsNull                                      "IsNull"
#define DISH_LANGID_IsType                                      "IsType"
#define DISH_LANGID_IsBoolean                                   "IsBoolean"
#define DISH_LANGID_IsInteger                                   "IsInteger"
#define DISH_LANGID_IsReal                                      "IsReal"
#define DISH_LANGID_IsString                                    "IsString"
#define DISH_LANGID_IsArray                                     "IsArray"
#define DISH_LANGID_IsDictionary                                "IsDictionary"
#define DISH_LANGID_IsStructure                                 "IsStructure"
#define DISH_LANGID_IsFunction                                  "IsFunction"

#define DISH_LANGID_StringAsNumeric                             "StringAsNumeric"

#define DISH_LANGID_TypeOf                                      "TypeOf"

#define DISH_LANGID_TypeId                                      "TypeId"
#define DISH_LANGID_TYPEID_Null                                 "TYPEID_Null"
#define DISH_LANGID_TYPEID_Type                                 "TYPEID_Type"
#define DISH_LANGID_TYPEID_Boolean                              "TYPEID_Boolean"
#define DISH_LANGID_TYPEID_Integer                              "TYPEID_Integer"
#define DISH_LANGID_TYPEID_Real                                 "TYPEID_Real"
#define DISH_LANGID_TYPEID_String                               "TYPEID_String"
#define DISH_LANGID_TYPEID_Array                                "TYPEID_Array"
#define DISH_LANGID_TYPEID_Dictionary                           "TYPEID_Dictionary"
#define DISH_LANGID_TYPEID_Structure                            "TYPEID_Structure"
#define DISH_LANGID_TYPEID_Executable                           "TYPEID_Executable"

#define DISH_LANGID_RANGE_BOUNDARY_ERROR                        "ERROR"
#define DISH_LANGID_RANGE_BOUNDARY_CAP                          "CAP"
#define DISH_LANGID_RANGE_BOUNDARY_ROLLOVER                     "ROLLOVER"

#define DISH_LANGID_USES_32BIT_ATOMICS                          "USES_32BIT_ATOMICS"
#define DISH_LANGID_USES_64BIT_ATOMICS                          "USES_64BIT_ATOMICS"

#define DISH_LANGID_BOOLEAN_MIN                                 "BooleanMin"
#define DISH_LANGID_BOOLEAN_MAX                                 "BooleanMax"
#define DISH_LANGID_INTEGER_MIN                                 "IntegerMin"
#define DISH_LANGID_INTEGER_MAX                                 "IntegerMax"
#define DISH_LANGID_INTEGER_EPS                                 "IntegerEps"
#define DISH_LANGID_REAL_MIN                                    "RealMin"
#define DISH_LANGID_REAL_MAX                                    "RealMax"
#define DISH_LANGID_REAL_EPS                                    "RealEps"

#define DISH_LANGID_ErrorT                                      "ErrorT"
#define DISH_LANGID_ERR_OK                                      "ERR_OK"
#define DISH_LANGID_ERR_TERMINATE                               "ERR_TERMINATE"
#define DISH_LANGID_ERR_ILLEGAL_CAST                            "ERR_ILLEGAL_CAST"
#define DISH_LANGID_ERR_VALUE_LOCKED                            "ERR_VALUE_LOCKED"
#define DISH_LANGID_ERR_NO_SUCH_MEMBER                          "ERR_NO_SUCH_MEMBER"
#define DISH_LANGID_ERR_DUPLICATE_SYMBOL                        "ERR_DUPLICATE_SYMBOL"
#define DISH_LANGID_ERR_NO_SUCH_SYMBOL                          "ERR_NO_SUCH_SYMBOL"
#define DISH_LANGID_ERR_DIVIDE_BY_ZERO                          "ERR_DIVIDE_BY_ZERO"
#define DISH_LANGID_ERR_DOMAIN_ERROR                            "ERR_DOMAIN_ERROR"
#define DISH_LANGID_ERR_RANGE_ERROR                             "ERR_RANGE_ERROR"
#define DISH_LANGID_ERR_ILLEGAL_HANDLE                          "ERR_ILLEGAL_HANDLE"
#define DISH_LANGID_ERR_ILLEGAL_VALUE                           "ERR_ILLEGAL_VALUE"
#define DISH_LANGID_ERR_TOO_MANY_OPEN_FILES                     "ERR_TOO_MANY_OPEN_FILES"
#define DISH_LANGID_ERR_UNABLE_TO_OPEN_FILE                     "ERR_UNABLE_TO_OPEN_FILE"
#define DISH_LANGID_ERR_FILE_NOT_OPEN                           "ERR_FILE_NOT_OPEN"
#define DISH_LANGID_ERR_FILE_WRITE_ERROR                        "ERR_FILE_WRITE_ERROR"
#define DISH_LANGID_ERR_FILE_READ_ERROR                         "ERR_FILE_READ_ERROR"
#define DISH_LANGID_ERR_FILE_READ_END_OF_FILE                   "ERR_FILE_READ_END_OF_FILE"
#define DISH_LANGID_ERR_TOO_MANY_OPEN_SOCKETS                   "ERR_TOO_MANY_OPEN_SOCKETS"
#define DISH_LANGID_ERR_UNABLE_TO_OPEN_SOCKET                   "ERR_UNABLE_TO_OPEN_SOCKET"
#define DISH_LANGID_ERR_UNABLE_TO_CLOSE_SOCKET                  "ERR_UNABLE_TO_CLOSE_SOCKET"
#define DISH_LANGID_ERR_NETWORK_INVALID_ADDRESS                 "ERR_NETWORK_INVALID_ADDRESS"
#define DISH_LANGID_ERR_NETWORK_UNABLE_TO_CONNECT_TO_SERVER     "ERR_NETWORK_UNABLE_TO_CONNECT_TO_SERVER"
#define DISH_LANGID_ERR_NETWORK_SOCKET_NOT_OPEN                 "ERR_NETWORK_SOCKET_NOT_OPEN"
#define DISH_LANGID_ERR_NETWORK_SOCKET_WRITE_ERROR              "ERR_NETWORK_SOCKET_WRITE_ERROR"
#define DISH_LANGID_ERR_NETWORK_SOCKET_READ_ERROR               "ERR_NETWORK_SOCKET_READ_ERROR"
#define DISH_LANGID_ERR_MATRIX_NOT_VALID_ERROR                  "ERR_MATRIX_NOT_VALID_ERROR"
#define DISH_LANGID_ERR_MATRIX_NOT_SQUARE_ERROR                 "ERR_MATRIX_NOT_SQUARE_ERROR"
#define DISH_LANGID_ERR_ZERO_DETERMINANT_ERROR                  "ERR_ZERO_DETERMINANT_ERROR"
#define DISH_LANGID_ERR_MATRIX_DIMENSION_ERROR                  "ERR_MATRIX_DIMENSION_ERROR"
#define DISH_LANGID_ERR_STACK_OVERFLOW_ERROR                    "ERR_STACK_OVERFLOW_ERROR"
#define DISH_LANGID_ERR_DB_INVALID_CONNECTION_TYPE              "ERR_DB_INVALID_CONNECTION_TYPE"
#define DISH_LANGID_ERR_DB_TOO_MANY_OPEN_CONNECTIONS            "ERR_DB_TOO_MANY_OPEN_CONNECTIONS"
#define DISH_LANGID_ERR_DB_UNABLE_TO_OPEN_CONNECTION            "ERR_DB_UNABLE_TO_OPEN_CONNECTION"
#define DISH_LANGID_ERR_DB_CONNECTION_NOT_OPEN                  "ERR_DB_CONNECTION_NOT_OPEN"
#define DISH_LANGID_ERR_DB_CONNECTION_DROPPED                   "ERR_DB_CONNECTION_DROPPED"
#define DISH_LANGID_ERR_DB_QUERY_ERROR                          "ERR_DB_QUERY_ERROR"
#define DISH_LANGID_ERR_RS232_CONFIGURATION_NOT_SUPPORTED       "ERR_RS232_CONFIGURATION_NOT_SUPPORTED"
#define DISH_LANGID_ERR_RS232_UNABLE_TO_OPEN_PORT               "ERR_RS232_UNABLE_TO_OPEN_PORT"
#define DISH_LANGID_ERR_RS232_PORT_NOT_OPEN                     "ERR_RS232_PORT_NOT_OPEN"
#define DISH_LANGID_ERR_RS232_WRITE_FAILURE                     "ERR_RS232_WRITE_FAILURE"
#define DISH_LANGID_ERR_RS232_READ_FAILURE                      "ERR_RS232_READ_FAILURE"

#define DISH_LANGID_OnErrorPush                                 "OnErrorPush"
#define DISH_LANGID_OnErrorInvoke                               "OnErrorInvoke"
#define DISH_LANGID_OnErrorPop                                  "OnErrorPop"

#define DISH_LANGID_Print                                       "Print"
#define DISH_LANGID_Println                                     "Println"
#define DISH_LANGID_Newln                                       "Newln"

#define DISH_LANGID_KeyPressed                                  "KeyPressed"
#define DISH_LANGID_Read                                        "Read"
#define DISH_LANGID_ReadCh                                      "ReadCh"
#define DISH_LANGID_ReadInteger                                 "ReadInteger"
#define DISH_LANGID_ReadReal                                    "ReadReal"
#define DISH_LANGID_Readln                                      "Readln"

#define DISH_LANGID_MinimumFunction                             "Minimum"
#define DISH_LANGID_MaximumFunction                             "Maximum"

#define DISH_LANGID_SymbolOfFunctionFunction                    "SymbolOfFunction"
#define DISH_LANGID_SymbolExistsFunction                        "SymbolExists"

#define DISH_LANGID_IsExactlyEqual                              "IsExactlyEqual"


/******************************************************************************

    File I/O run-time IDs.
    
 ******************************************************************************/
 
#define DISH_LANGID_IS_LIB_FILEIO                               "IS_LIB_FILEIO"

#define DISH_LANGID_FILE_READ                                   "FILE_READ"
#define DISH_LANGID_FILE_WRITE                                  "FILE_WRITE"
#define DISH_LANGID_FILE_WRITE_EX                               "FILE_WRITE_EX"
#define DISH_LANGID_FILE_APPEND                                 "FILE_APPEND"

#define DISH_LANGID_MAX_OPEN_FILES                              "MAX_OPEN_FILES"

#define DISH_LANGID_FileOpen                                    "FileOpen"
#define DISH_LANGID_FileNumOpen                                 "FileNumOpen"
#define DISH_LANGID_FileWrite                                   "FileWrite"
#define DISH_LANGID_FileWriteln                                 "FileWriteln"
#define DISH_LANGID_FileReadText                                "FileReadText"
#define DISH_LANGID_FileReadBoolean                             "FileReadBoolean"
#define DISH_LANGID_FileReadInteger                             "FileReadInteger"
#define DISH_LANGID_FileReadReal                                "FileReadReal"
#define DISH_LANGID_FileReadln                                  "FileReadln"
#define DISH_LANGID_FileEndOfFile                               "FileEndOfFile"
#define DISH_LANGID_FileFlush                                   "FileFlush"
#define DISH_LANGID_FileClose                                   "FileClose"


/******************************************************************************

    String run-time IDs.
    
 ******************************************************************************/
 
#define DISH_LANGID_IS_LIB_STRING                               "IS_LIB_STRING"
 
#define DISH_LANGID_CASE_SENSITIVE                              "CASE_SENSITIVE"
#define DISH_LANGID_CASE_INSENSITIVE                            "CASE_INSENSITIVE"

#define DISH_LANGID_STRINVALID                                  "STRINVALID"

#define DISH_LANGID_STRCONTROLCHARS                             "STRCONTROLCHARS"
#define DISH_LANGID_STRDIGITCHARS                               "STRDIGITCHARS"
#define DISH_LANGID_STRLOWERCASECHARS                           "STRLOWERCASECHARS"
#define DISH_LANGID_STRUPPERCASECHARS                           "STRUPPERCASECHARS"
#define DISH_LANGID_STRPRINTABLECHARS                           "STRPRINTABLECHARS"
#define DISH_LANGID_STRPUNCTUATIONCHARS                         "STRPUNCTUATIONCHARS"
#define DISH_LANGID_STRWHITESPACECHARS                          "STRWHITESPACECHARS"
#define DISH_LANGID_STREOLNCHARS                                "STREOLNCHARS"

#define DISH_LANGID_STRSINGLEQUOTE                              "STRSINGLEQUOTE"
#define DISH_LANGID_STRDOUBLEQUOTE                              "STRDOUBLEQUOTE"
#define DISH_LANGID_STRBACKSLASH                                "STRBACKSLASH"
#define DISH_LANGID_STRNEWLINE                                  "STRNEWLINE"

#define DISH_LANGID_STRSINGLE                                   "STRSINGLE"
#define DISH_LANGID_STRMULTIPLE                                 "STRMULTIPLE"
#define DISH_LANGID_Ord                                         "Ord"
#define DISH_LANGID_Chr                                         "Chr"

#define DISH_LANGID_BASE_2_DIGITS                               "BASE_2_DIGITS"
#define DISH_LANGID_BASE_8_DIGITS                               "BASE_8_DIGITS"
#define DISH_LANGID_BASE_10_DIGITS                              "BASE_10_DIGITS"
#define DISH_LANGID_BASE_16_DIGITS                              "BASE_16_DIGITS"
#define DISH_LANGID_IntegerToBaseString                         "IntegerToBaseString"
#define DISH_LANGID_BaseStringToInteger                         "BaseStringToInteger"

#define DISH_LANGID_ToUpperCase                                 "ToUpperCase"
#define DISH_LANGID_ToLowerCase                                 "ToLowerCase"

#define DISH_LANGID_IsUpperCase                                 "IsUpperCase"
#define DISH_LANGID_IsLowerCase                                 "IsLowerCase"
#define DISH_LANGID_IsControl                                   "IsControl"
#define DISH_LANGID_IsPrintable                                 "IsPrintable"
#define DISH_LANGID_IsWhitespace                                "IsWhitespace"
#define DISH_LANGID_IsPunctuation                               "IsPunctuation"
#define DISH_LANGID_IsLetter                                    "IsLetter"
#define DISH_LANGID_IsDigit                                     "IsDigit"
#define DISH_LANGID_IsHexDigit                                  "IsHexDigit"

#define DISH_LANGID_LeftJustify                                 "LeftJustify"
#define DISH_LANGID_RightJustify                                "RightJustify"
#define DISH_LANGID_CenterJustify                               "CenterJustify"

#define DISH_LANGID_StrLeft                                     "StrLeft"
#define DISH_LANGID_StrRight                                    "StrRight"
#define DISH_LANGID_StrMiddle                                   "StrMiddle"

#define DISH_LANGID_StrBeginsWith                               "StrBeginsWith"
#define DISH_LANGID_StrEndsWith                                 "StrEndsWith"

#define DISH_LANGID_StrFind                                     "StrFind"
#define DISH_LANGID_StrFindNextOf                               "StrFindNextOf"
#define DISH_LANGID_StrFindNextNotOf                            "StrFindNextNotOf"
#define DISH_LANGID_StrFindLastOf                               "StrFindLastOf"
#define DISH_LANGID_StrFindLastNotOf                            "StrFindLastNotOf"

#define DISH_LANGID_StrTrimLeading                              "StrTrimLeading"
#define DISH_LANGID_StrTrimTrailing                             "StrTrimTrailing"
#define DISH_LANGID_StrRemoveAllOf                              "StrRemoveAllOf"
#define DISH_LANGID_StrRemoveAllNotOf                           "StrRemoveAllNotOf"

#define DISH_LANGID_StrReplaceAll                               "StrReplaceAll"
#define DISH_LANGID_StrReplaceFirst                             "StrReplaceFirst"

#define DISH_LANGID_StrReplicate                                "StrReplicate"

#define DISH_LANGID_StrReverse                                  "StrReverse"


/******************************************************************************

    Date-Time run-time IDs.
    
 ******************************************************************************/
 
#define DISH_LANGID_IS_LIB_DATETIME                             "IS_LIB_DATETIME"

#define DISH_LANGID_DateTimeT                                   "DateTimeT"

#define DISH_LANGID_DaysOfTheWeek                               "DaysOfTheWeek"
#define DISH_LANGID_Sunday                                      "Sunday"
#define DISH_LANGID_Monday                                      "Monday"
#define DISH_LANGID_Tuesday                                     "Tuesday"
#define DISH_LANGID_Wednesday                                   "Wednesday"
#define DISH_LANGID_Thursday                                    "Thursday"
#define DISH_LANGID_Friday                                      "Friday"
#define DISH_LANGID_Saturday                                    "Saturday"

#define DISH_LANGID_MonthsOfTheYear                             "MonthsOfTheYear"
#define DISH_LANGID_January                                     "January"
#define DISH_LANGID_February                                    "February"
#define DISH_LANGID_March                                       "March"
#define DISH_LANGID_April                                       "April"
#define DISH_LANGID_May                                         "May"
#define DISH_LANGID_June                                        "June"
#define DISH_LANGID_July                                        "July"
#define DISH_LANGID_August                                      "August"
#define DISH_LANGID_September                                   "September"
#define DISH_LANGID_October                                     "October"
#define DISH_LANGID_November                                    "November"
#define DISH_LANGID_December                                    "December"

#define DISH_LANGID_DateTime                                    "DateTime"
#define DISH_LANGID_DecomposeDateTimeValue                      "DecomposeDateTimeValue"
#define DISH_LANGID_DecomposeUtcDateTimeValue                   "DecomposeUtcDateTimeValue"
#define DISH_LANGID_ComposeDateTimeValue                        "ComposeDateTimeValue"

#define DISH_LANGID_TimeZoneT                                   "TimeZoneT"
#define DISH_LANGID_TimeZoneInfo                                "TimeZoneInfo"

#define DISH_LANGID_Now                                         "Now"
#define DISH_LANGID_ElapsedSeconds                              "ElapsedSeconds"


/******************************************************************************

    Math run-time IDs.
    
 ******************************************************************************/
 
#define DISH_LANGID_IS_LIB_MATH_CORE                            "IS_LIB_MATH_CORE"
#define DISH_LANGID_IS_LIB_MATH_TRIG                            "IS_LIB_MATH_TRIG"
#define DISH_LANGID_IS_LIB_MATH_COMPLEX                         "IS_LIB_MATH_COMPLEX"
#define DISH_LANGID_IS_LIB_MATH_RANDOM                          "IS_LIB_MATH_RANDOM"
#define DISH_LANGID_IS_LIB_MATH_MATRIX                          "IS_LIB_MATH_MATRIX"
#define DISH_LANGID_IS_LIB_MATH_HYPERBOLIC                      "IS_LIB_MATH_HYPERBOLIC"
#define DISH_LANGID_IS_LIB_MATH_INTEGER                         "IS_LIB_MATH_INTEGER"

#define DISH_LANGID_IsFiniteNumberFunction                      "IsFiniteNumber"
#define DISH_LANGID_IsInfiniteNumberFunction                    "IsInfiniteNumber"
#define DISH_LANGID_IsNotANumberFunction                        "IsNotANumber"
#define DISH_LANGID_IsNormalNumberFunction                      "IsNormalNumber"

#define DISH_LANGID_IsOddFunction                               "IsOdd"
#define DISH_LANGID_IsEvenFunction                              "IsEven"

#define DISH_LANGID_AbsFunction                                 "Abs"
#define DISH_LANGID_WholeFunction                               "Whole"
#define DISH_LANGID_FractionFunction                            "Fraction"
#define DISH_LANGID_SignOfFunction                              "SignOf"
#define DISH_LANGID_IncFunction                                 "Inc"
#define DISH_LANGID_DecFunction                                 "Dec"
#define DISH_LANGID_SqrFunction                                 "Sqr"
#define DISH_LANGID_SqrtFunction                                "Sqrt"
#define DISH_LANGID_CubeFunction                                "Cube"
#define DISH_LANGID_CbrtFunction                                "Cbrt"

#define DISH_LANGID_DegToRadFunction                            "DegToRad"
#define DISH_LANGID_RadToDegFunction                            "RadToDeg"

#define DISH_LANGID_PI                                          "PI"

#define DISH_LANGID_SinFunction                                 "Sin"
#define DISH_LANGID_CosFunction                                 "Cos"
#define DISH_LANGID_TanFunction                                 "Tan"
#define DISH_LANGID_ArcSinFunction                              "ArcSin"
#define DISH_LANGID_ArcCosFunction                              "ArcCos"
#define DISH_LANGID_ArcTanFunction                              "ArcTan"

#define DISH_LANGID_CotFunction                                 "Cot"
#define DISH_LANGID_SecFunction                                 "Sec"
#define DISH_LANGID_CscFunction                                 "Csc"
#define DISH_LANGID_ArcCotFunction                              "ArcCot"
#define DISH_LANGID_ArcSecFunction                              "ArcSec"
#define DISH_LANGID_ArcCscFunction                              "ArcCsc"

#define DISH_LANGID_SinhFunction                                "Sinh"
#define DISH_LANGID_CoshFunction                                "Cosh"
#define DISH_LANGID_TanhFunction                                "Tanh"
#define DISH_LANGID_ArcSinhFunction                             "ArcSinh"
#define DISH_LANGID_ArcCoshFunction                             "ArcCosh"
#define DISH_LANGID_ArcTanhFunction                             "ArcTanh"

#define DISH_LANGID_CothFunction                                "Coth"
#define DISH_LANGID_SechFunction                                "Sech"
#define DISH_LANGID_CschFunction                                "Csch"
#define DISH_LANGID_ArcCothFunction                             "ArcCoth"
#define DISH_LANGID_ArcSechFunction                             "ArcSech"
#define DISH_LANGID_ArcCschFunction                             "ArcCsch"

#define DISH_LANGID_LnFunction                                  "Ln"
#define DISH_LANGID_LogFunction                                 "Log"
#define DISH_LANGID_ExpFunction                                 "Exp"
#define DISH_LANGID_RoundFunction                               "Round"
#define DISH_LANGID_FloorFunction                               "Floor"
#define DISH_LANGID_CeilFunction                                "Ceil"
#define DISH_LANGID_MinimumFunction                             "Minimum"
#define DISH_LANGID_MaximumFunction                             "Maximum"

#define DISH_LANGID_ComplexT                                    "ComplexT"
#define DISH_LANGID_ComplexCreateFunction                       "ComplexCreate"
#define DISH_LANGID_ComplexToStringFunction                     "ComplexToString"
#define DISH_LANGID_ComplexIsEqualFunction                      "ComplexIsEqual"
#define DISH_LANGID_ComplexIsNotEqualFunction                   "ComplexIsNotEqual"
#define DISH_LANGID_ComplexAddFunction                          "ComplexAdd"
#define DISH_LANGID_ComplexSubtractFunction                     "ComplexSubtract"
#define DISH_LANGID_ComplexMultiplyFunction                     "ComplexMultiply"
#define DISH_LANGID_ComplexDivideFunction                       "ComplexDivide"
#define DISH_LANGID_ComplexSqrFunction                          "ComplexSqr"
#define DISH_LANGID_ComplexSqrtFunction                         "ComplexSqrt"
#define DISH_LANGID_ComplexReciprocalFunction                   "ComplexReciprocal"
#define DISH_LANGID_ComplexConjugateFunction                    "ComplexConjugate"

#define DISH_LANGID_RandomSeedFunction                          "RandomSeed"
#define DISH_LANGID_RandomBooleanFunction                       "RandomBoolean"
#define DISH_LANGID_RandomIntegerFunction                       "RandomInteger"
#define DISH_LANGID_RandomRealFunction                          "RandomReal"
#define DISH_LANGID_RandomMaxFunction                           "RandomMax"
#define DISH_LANGID_RandomBitIntegerFunction                    "RandomBitInteger"

#define DISH_LANGID_CreateMatrixTFunction                       "CreateMatrixT"
#define DISH_LANGID_CreateMatrixFunction                        "CreateMatrix"
#define DISH_LANGID_MatrixValidateFunction                      "MatrixValidate"
#define DISH_LANGID_MatrixNumRowsFunction                       "MatrixNumRows"
#define DISH_LANGID_MatrixNumColumnsFunction                    "MatrixNumColumns"
#define DISH_LANGID_MatrixIsSquareFunction                      "MatrixIsSquare"
#define DISH_LANGID_MatrixInitializeFunction                    "MatrixInitialize"
#define DISH_LANGID_MatrixRowSliceFunction                      "MatrixRowSlice"
#define DISH_LANGID_MatrixColumnSliceFunction                   "MatrixColumnSlice"
#define DISH_LANGID_MatrixTransposeFunction                     "MatrixTranspose"
#define DISH_LANGID_MatrixDeterminantFunction                   "MatrixDeterminant"
#define DISH_LANGID_MatrixInvertFunction                        "MatrixInvert"
#define DISH_LANGID_MatrixAddFunction                           "MatrixAdd"
#define DISH_LANGID_MatrixSubtractFunction                      "MatrixSubtract"
#define DISH_LANGID_MatrixMultiplyFunction                      "MatrixMultiply"
#define DISH_LANGID_MatrixEqualFunction                         "MatrixIsEqual"
#define DISH_LANGID_MatrixAddRowFunction                        "MatrixAddRow"
#define DISH_LANGID_MatrixAddColumnFunction                     "MatrixAddColumn"
#define DISH_LANGID_MatrixToStringFunction                      "MatrixToString"

#define DISH_LANGID_FactorialFunction                           "Factorial"
#define DISH_LANGID_BinomialCoefficientFunction                 "BinomialCoefficient"
#define DISH_LANGID_GreatestCommonDenomonatorFunction           "GreatestCommonDenomonator"
#define DISH_LANGID_FibonacciFunction                           "Fibonacci"


/******************************************************************************

    Text I/O run-time IDs.
    
 ******************************************************************************/
 
#define DISH_LANGID_IS_LIB_TEXTIO                               "IS_LIB_TEXTIO"

#define DISH_LANGID_TEXTIO_COLOR_BLACK                          "TEXTIO_COLOR_BLACK"
#define DISH_LANGID_TEXTIO_COLOR_RED                            "TEXTIO_COLOR_RED"
#define DISH_LANGID_TEXTIO_COLOR_GREEN                          "TEXTIO_COLOR_GREEN"
#define DISH_LANGID_TEXTIO_COLOR_YELLOW                         "TEXTIO_COLOR_YELLOW"
#define DISH_LANGID_TEXTIO_COLOR_BLUE                           "TEXTIO_COLOR_BLUE"
#define DISH_LANGID_TEXTIO_COLOR_MAGENTA                        "TEXTIO_COLOR_MAGENTA"
#define DISH_LANGID_TEXTIO_COLOR_CYAN                           "TEXTIO_COLOR_CYAN"
#define DISH_LANGID_TEXTIO_COLOR_WHITE                          "TEXTIO_COLOR_WHITE"

#define DISH_LANGID_TEXTIO_ATTR_NORMAL                          "TEXTIO_ATTR_NORMAL"
#define DISH_LANGID_TEXTIO_ATTR_CHARTEXT                        "TEXTIO_ATTR_CHARTEXT"
#define DISH_LANGID_TEXTIO_ATTR_COLOR                           "TEXTIO_ATTR_COLOR"
#define DISH_LANGID_TEXTIO_ATTR_STANDOUT                        "TEXTIO_ATTR_STANDOUT"
#define DISH_LANGID_TEXTIO_ATTR_UNDERLINE                       "TEXTIO_ATTR_UNDERLINE"
#define DISH_LANGID_TEXTIO_ATTR_REVERSE                         "TEXTIO_ATTR_REVERSE"
#define DISH_LANGID_TEXTIO_ATTR_BLINK                           "TEXTIO_ATTR_BLINK"
#define DISH_LANGID_TEXTIO_ATTR_DIM                             "TEXTIO_ATTR_DIM"
#define DISH_LANGID_TEXTIO_ATTR_BOLD                            "TEXTIO_ATTR_BOLD"
#define DISH_LANGID_TEXTIO_ATTR_ALTCHARSET                      "TEXTIO_ATTR_ALTCHARSET"
#define DISH_LANGID_TEXTIO_ATTR_INVIS                           "TEXTIO_ATTR_INVIS"
#define DISH_LANGID_TEXTIO_ATTR_PROTECT                         "TEXTIO_ATTR_PROTECT"
#define DISH_LANGID_TEXTIO_ATTR_HORIZONTAL                      "TEXTIO_ATTR_HORIZONTAL"
#define DISH_LANGID_TEXTIO_ATTR_LEFT                            "TEXTIO_ATTR_LEFT"
#define DISH_LANGID_TEXTIO_ATTR_LOW                             "TEXTIO_ATTR_LOW"
#define DISH_LANGID_TEXTIO_ATTR_RIGHT                           "TEXTIO_ATTR_RIGHT"
#define DISH_LANGID_TEXTIO_ATTR_TOP                             "TEXTIO_ATTR_TOP"
#define DISH_LANGID_TEXTIO_ATTR_VERTICAL                        "TEXTIO_ATTR_VERTICAL"

#define DISH_LANGID_TEXTIO_KEY_CTRL_A                           "TEXTIO_KEY_CTRL_A"
#define DISH_LANGID_TEXTIO_KEY_CTRL_B                           "TEXTIO_KEY_CTRL_B"
#define DISH_LANGID_TEXTIO_KEY_CTRL_C                           "TEXTIO_KEY_CTRL_C"
#define DISH_LANGID_TEXTIO_KEY_CTRL_D                           "TEXTIO_KEY_CTRL_D"
#define DISH_LANGID_TEXTIO_KEY_CTRL_E                           "TEXTIO_KEY_CTRL_E"
#define DISH_LANGID_TEXTIO_KEY_CTRL_F                           "TEXTIO_KEY_CTRL_F"
#define DISH_LANGID_TEXTIO_KEY_CTRL_G                           "TEXTIO_KEY_CTRL_G"
#define DISH_LANGID_TEXTIO_KEY_CTRL_H                           "TEXTIO_KEY_CTRL_H"
#define DISH_LANGID_TEXTIO_KEY_CTRL_I                           "TEXTIO_KEY_CTRL_I"
#define DISH_LANGID_TEXTIO_KEY_CTRL_J                           "TEXTIO_KEY_CTRL_J"
#define DISH_LANGID_TEXTIO_KEY_CTRL_K                           "TEXTIO_KEY_CTRL_K"
#define DISH_LANGID_TEXTIO_KEY_CTRL_L                           "TEXTIO_KEY_CTRL_L"
#define DISH_LANGID_TEXTIO_KEY_CTRL_M                           "TEXTIO_KEY_CTRL_M"
#define DISH_LANGID_TEXTIO_KEY_CTRL_N                           "TEXTIO_KEY_CTRL_N"
#define DISH_LANGID_TEXTIO_KEY_CTRL_O                           "TEXTIO_KEY_CTRL_O"
#define DISH_LANGID_TEXTIO_KEY_CTRL_P                           "TEXTIO_KEY_CTRL_P"
#define DISH_LANGID_TEXTIO_KEY_CTRL_Q                           "TEXTIO_KEY_CTRL_Q"
#define DISH_LANGID_TEXTIO_KEY_CTRL_R                           "TEXTIO_KEY_CTRL_R"
#define DISH_LANGID_TEXTIO_KEY_CTRL_S                           "TEXTIO_KEY_CTRL_S"
#define DISH_LANGID_TEXTIO_KEY_CTRL_T                           "TEXTIO_KEY_CTRL_T"
#define DISH_LANGID_TEXTIO_KEY_CTRL_U                           "TEXTIO_KEY_CTRL_U"
#define DISH_LANGID_TEXTIO_KEY_CTRL_V                           "TEXTIO_KEY_CTRL_V"
#define DISH_LANGID_TEXTIO_KEY_CTRL_W                           "TEXTIO_KEY_CTRL_W"
#define DISH_LANGID_TEXTIO_KEY_CTRL_X                           "TEXTIO_KEY_CTRL_X"
#define DISH_LANGID_TEXTIO_KEY_CTRL_Y                           "TEXTIO_KEY_CTRL_Y"
#define DISH_LANGID_TEXTIO_KEY_CTRL_Z                           "TEXTIO_KEY_CTRL_Z"
#define DISH_LANGID_TEXTIO_KEY_ESC                              "TEXTIO_KEY_ESC"
#define DISH_LANGID_TEXTIO_KEY_DOWN                             "TEXTIO_KEY_DOWN"
#define DISH_LANGID_TEXTIO_KEY_UP                               "TEXTIO_KEY_UP"
#define DISH_LANGID_TEXTIO_KEY_LEFT                             "TEXTIO_KEY_LEFT"
#define DISH_LANGID_TEXTIO_KEY_RIGHT                            "TEXTIO_KEY_RIGHT"
#define DISH_LANGID_TEXTIO_KEY_HOME                             "TEXTIO_KEY_HOME"
#define DISH_LANGID_TEXTIO_KEY_BACKSPACE                        "TEXTIO_KEY_BACKSPACE"
#define DISH_LANGID_TEXTIO_KEY_F1                               "TEXTIO_KEY_F1"
#define DISH_LANGID_TEXTIO_KEY_F2                               "TEXTIO_KEY_F2"
#define DISH_LANGID_TEXTIO_KEY_F3                               "TEXTIO_KEY_F3"
#define DISH_LANGID_TEXTIO_KEY_F4                               "TEXTIO_KEY_F4"
#define DISH_LANGID_TEXTIO_KEY_F5                               "TEXTIO_KEY_F5"
#define DISH_LANGID_TEXTIO_KEY_F6                               "TEXTIO_KEY_F6"
#define DISH_LANGID_TEXTIO_KEY_F7                               "TEXTIO_KEY_F7"
#define DISH_LANGID_TEXTIO_KEY_F8                               "TEXTIO_KEY_F8"
#define DISH_LANGID_TEXTIO_KEY_F9                               "TEXTIO_KEY_F9"
#define DISH_LANGID_TEXTIO_KEY_F10                              "TEXTIO_KEY_F10"
#define DISH_LANGID_TEXTIO_KEY_F11                              "TEXTIO_KEY_F11"
#define DISH_LANGID_TEXTIO_KEY_F12                              "TEXTIO_KEY_F12"
#define DISH_LANGID_TEXTIO_KEY_DELETE_LINE                      "TEXTIO_KEY_DELETE_LINE"
#define DISH_LANGID_TEXTIO_KEY_INSERT_LINE                      "TEXTIO_KEY_INSERT_LINE"
#define DISH_LANGID_TEXTIO_KEY_DELETE_CHAR                      "TEXTIO_KEY_DELETE_CHAR"
#define DISH_LANGID_TEXTIO_KEY_INSERT_CHAR                      "TEXTIO_KEY_INSERT_CHAR"

#define DISH_LANGID_TEXTIO_Start                                "TEXTIO_Start"
#define DISH_LANGID_TEXTIO_IsStarted                            "TEXTIO_IsStarted"
#define DISH_LANGID_TEXTIO_Refresh                              "TEXTIO_Refresh"
#define DISH_LANGID_TEXTIO_Clear                                "TEXTIO_Clear"
#define DISH_LANGID_TEXTIO_End                                  "TEXTIO_End"

#define DISH_LANGID_TEXTIO_GetXSize                             "TEXTIO_GetXSize"
#define DISH_LANGID_TEXTIO_GetYSize                             "TEXTIO_GetYSize"
#define DISH_LANGID_TEXTIO_MoveTo                               "TEXTIO_MoveTo"

#define DISH_LANGID_TEXTIO_AttrNormal                           "TEXTIO_AttrNormal"
#define DISH_LANGID_TEXTIO_AttrGet                              "TEXTIO_AttrGet"
#define DISH_LANGID_TEXTIO_AttrSet                              "TEXTIO_AttrSet"
#define DISH_LANGID_TEXTIO_AttrOn                               "TEXTIO_AttrOn"
#define DISH_LANGID_TEXTIO_AttrOff                              "TEXTIO_AttrOff"
#define DISH_LANGID_TEXTIO_SetForegroundColor                   "TEXTIO_SetForegroundColor"
#define DISH_LANGID_TEXTIO_GetForegroundColor                   "TEXTIO_GetForegroundColor"
#define DISH_LANGID_TEXTIO_SetBackgroundColor                   "TEXTIO_SetBackgroundColor"
#define DISH_LANGID_TEXTIO_GetBackgroundColor                   "TEXTIO_GetBackgroundColor"
#define DISH_LANGID_TEXTIO_SetColor                             "TEXTIO_SetColor"

#define DISH_LANGID_TEXTIO_VISIBLE                              "TEXTIO_VISIBLE"
#define DISH_LANGID_TEXTIO_INVISIBLE                            "TEXTIO_INVISIBLE"
#define DISH_LANGID_TEXTIO_SetCursor                            "TEXTIO_SetCursor"


/******************************************************************************

    Network run-time IDs.
    
 ******************************************************************************/
 
#define DISH_LANGID_IS_LIB_NETWORK                              "IS_LIB_NETWORK"

#define DISH_LANGID_MAX_OPEN_SOCKETS                            "MAX_OPEN_SOCKETS"

#define DISH_LANGID_NETWORK_IPV4                                "NETWORK_IPV4"
#define DISH_LANGID_NETWORK_IPV6                                "NETWORK_IPV6"

#define DISH_LANGID_NetworkOpenClientSocket                     "NetworkOpenClientSocket"
#define DISH_LANGID_NetworkOpenServerSocket                     "NetworkOpenServerSocket"

#define DISH_LANGID_NetworkNumOpenSockets                       "NetworkNumOpenSockets"
#define DISH_LANGID_NetworkNumOpenClientSockets                 "NetworkNumOpenClientSockets"
#define DISH_LANGID_NetworkNumOpenServerSockets                 "NetworkNumOpenServerSockets"

#define DISH_LANGID_NetworkReadSocket                           "NetworkReadSocket"
#define DISH_LANGID_NetworkWriteSocket                          "NetworkWriteSocket"

#define DISH_LANGID_NetworkCloseSocket                          "NetworkCloseSocket"


/******************************************************************************

    File-sys run-time IDs.
    
 ******************************************************************************/
 
#define DISH_LANGID_IS_LIB_FILESYS                              "IS_LIB_FILESYS"

#define DISH_LANGID_FileSysFileT                                "FileSysFileT"
#define DISH_LANGID_FileSysDirT                                 "FileSysDirT"
#define DISH_LANGID_FileInfoT                                   "FileInfoT"

#define DISH_LANGID_FILESYS_NORECURSE                           "FILESYS_NORECURSE"
#define DISH_LANGID_FILESYS_RECURSE                             "FILESYS_RECURSE"

#define DISH_LANGID_FILESYS_FileExistsFunction                  "FILESYS_FileExistsFunction"
#define DISH_LANGID_FILESYS_ReadLocation                        "FILESYS_ReadLocation"
#define DISH_LANGID_FILESYS_ReadFiles                           "FILESYS_ReadFiles"
#define DISH_LANGID_FILESYS_ReadDirectories                     "FILESYS_ReadDirectories"
#define DISH_LANGID_FILESYS_GetFileInfo                         "FILESYS_GetFileInfo"
#define DISH_LANGID_FILESYS_PrintPathTree                       "FILESYS_PrintPathTree"


/******************************************************************************

    Database run-time IDs.
    
 ******************************************************************************/
 
#define DISH_LANGID_IS_LIB_DATABASE                             "IS_LIB_DATABASE"
#define DISH_LANGID_IS_LIB_DATABASE_MYSQL                       "IS_LIB_DATABASE_MYSQL"
#define DISH_LANGID_IS_LIB_DATABASE_POSTGRESQL                  "IS_LIB_DATABASE_POSTGRESQL"

#define DISH_LANGID_DB_TYPE_MYSQL                               "DB_TYPE_MYSQL"
#define DISH_LANGID_DB_TYPE_POSTGRESQL                          "DB_TYPE_POSTGRESQL"

#define DISH_LANGID_DB_MAX_CONNECTIONS                          "DB_MAX_CONNECTIONS"

#define DISH_LANGID_DB_VALIDATE                                 "DB_VALIDATE"
#define DISH_LANGID_DB_NO_VALIDATE                              "DB_NO_VALIDATE"

#define DISH_LANGID_DB_ConnectionParametersT                    "DB_ConnectionParametersT"

#define DISH_LANGID_DB_MakeDefaultConnectionParameters          "DB_MakeDefaultConnectionParameters"

#define DISH_LANGID_DB_OpenConnection                           "DB_OpenConnection"
#define DISH_LANGID_DB_CloseConnection                          "DB_CloseConnection"
#define DISH_LANGID_DB_CloseAllConnections                      "DB_CloseAllConnections"
#define DISH_LANGID_DB_IsOpen                                   "DB_IsOpen"
#define DISH_LANGID_DB_NumOpenConnections                       "DB_NumOpenConnections"

#define DISH_LANGID_DB_ServerVersion                            "DB_ServerVersion"

#define DISH_LANGID_DB_IssueQuery                               "DB_IssueQuery"


/******************************************************************************

    Regular-expression run-time IDs.
    
 ******************************************************************************/
 
#define DISH_LANGID_IS_LIB_IS_REGEX                             "IS_LIB_REGEX"

#define DISH_LANGID_REGEX_MAX_REGEX                             "REGEX_MAX_REGEX"

#define DISH_LANGID_REGEX_CreateFunction                        "REGEX_Create"
#define DISH_LANGID_REGEX_NumCreatedFunction                    "REGEX_NumCreated"
#define DISH_LANGID_REGEX_IsCreatedFunction                     "REGEX_IsCreated"
#define DISH_LANGID_REGEX_DestroyFunction                       "REGEX_Destroy"
#define DISH_LANGID_REGEX_DestroyAllFunction                    "REGEX_DestroyAll"

#define DISH_LANGID_REGEX_MatchFunction                         "REGEX_Match"
#define DISH_LANGID_REGEX_ReplaceNextFunction                   "REGEX_ReplaceNext"
#define DISH_LANGID_REGEX_ReplaceAllFunction                    "REGEX_ReplaceAll"


/******************************************************************************

    RS-232 run-time IDs.
    
 ******************************************************************************/
 
#define DISH_LANGID_IS_LIB_RS232                                "IS_LIB_RS232"

#define DISH_LANGID_RS232_MAX_OPEN                              "RS232_MAX_OPEN"

#define DISH_LANGID_RS232_BAUD_50                               "RS232_BAUD_50"
#define DISH_LANGID_RS232_BAUD_75                               "RS232_BAUD_75"
#define DISH_LANGID_RS232_BAUD_110                              "RS232_BAUD_110"
#define DISH_LANGID_RS232_BAUD_134                              "RS232_BAUD_134"
#define DISH_LANGID_RS232_BAUD_150                              "RS232_BAUD_150"
#define DISH_LANGID_RS232_BAUD_200                              "RS232_BAUD_200"
#define DISH_LANGID_RS232_BAUD_300                              "RS232_BAUD_300"
#define DISH_LANGID_RS232_BAUD_600                              "RS232_BAUD_600"
#define DISH_LANGID_RS232_BAUD_1200                             "RS232_BAUD_1200"
#define DISH_LANGID_RS232_BAUD_1800                             "RS232_BAUD_1800"
#define DISH_LANGID_RS232_BAUD_2400                             "RS232_BAUD_2400"
#define DISH_LANGID_RS232_BAUD_4800                             "RS232_BAUD_4800"
#define DISH_LANGID_RS232_BAUD_9600                             "RS232_BAUD_9600"
#define DISH_LANGID_RS232_BAUD_19200                            "RS232_BAUD_19200"
#define DISH_LANGID_RS232_BAUD_38400                            "RS232_BAUD_38400"
#define DISH_LANGID_RS232_BAUD_57600                            "RS232_BAUD_57600"
#define DISH_LANGID_RS232_BAUD_115200                           "RS232_BAUD_115200"
#define DISH_LANGID_RS232_BAUD_230400                           "RS232_BAUD_230400"
#define DISH_LANGID_RS232_BAUD_460800                           "RS232_BAUD_460800"
#define DISH_LANGID_RS232_BAUD_500000                           "RS232_BAUD_500000"
#define DISH_LANGID_RS232_BAUD_576000                           "RS232_BAUD_576000"
#define DISH_LANGID_RS232_BAUD_921600                           "RS232_BAUD_921600"
#define DISH_LANGID_RS232_BAUD_1000000                          "RS232_BAUD_1000000"
#define DISH_LANGID_RS232_BAUD_1152000                          "RS232_BAUD_1152000"
#define DISH_LANGID_RS232_BAUD_1500000                          "RS232_BAUD_1500000"
#define DISH_LANGID_RS232_BAUD_2000000                          "RS232_BAUD_2000000"
#define DISH_LANGID_RS232_BAUD_2500000                          "RS232_BAUD_2500000"
#define DISH_LANGID_RS232_BAUD_3000000                          "RS232_BAUD_3000000"
#define DISH_LANGID_RS232_BAUD_3500000                          "RS232_BAUD_3500000"
#define DISH_LANGID_RS232_BAUD_4000000                          "RS232_BAUD_4000000"

#define DISH_LANGID_RS232_DATA_BITS_5                           "RS232_DATA_BITS_5"
#define DISH_LANGID_RS232_DATA_BITS_6                           "RS232_DATA_BITS_6"
#define DISH_LANGID_RS232_DATA_BITS_7                           "RS232_DATA_BITS_7"
#define DISH_LANGID_RS232_DATA_BITS_8                           "RS232_DATA_BITS_8"

#define DISH_LANGID_RS232_PARITY_NO                             "RS232_PARITY_NO"
#define DISH_LANGID_RS232_PARITY_ODD                            "RS232_PARITY_ODD"
#define DISH_LANGID_RS232_PARITY_EVEN                           "RS232_PARITY_EVEN"
#define DISH_LANGID_RS232_PARITY_SPACE                          "RS232_PARITY_SPACE"

#define DISH_LANGID_RS232_STOP_BITS_1                           "RS232_STOP_BITS_1"
#define DISH_LANGID_RS232_STOP_BITS_2                           "RS232_STOP_BITS_2"

#define DISH_LANGID_RS232_FLOWCTRL_NONE                         "RS232_FLOWCTRL_NONE"
#define DISH_LANGID_RS232_FLOWCTRL_HARDWARE                     "RS232_FLOWCTRL_HARDWARE"
#define DISH_LANGID_RS232_FLOWCTRL_SOFTWARE                     "RS232_FLOWCTRL_SOFTWARE"

#define DISH_LANGID_RS232_BaudRateSupported                     "RS232_BaudRateSupported"
#define DISH_LANGID_RS232_DataBitsSupported                     "RS232_DataBitsSupported"
#define DISH_LANGID_RS232_ParitySupported                       "RS232_ParitySupported"
#define DISH_LANGID_RS232_StopBitsSupported                     "RS232_StopBitsSupported"
#define DISH_LANGID_RS232_FlowControlSupported                  "RS232_FlowControlSupported"

#define DISH_LANGID_RS232_ConfigurationT                        "RS232_ConfigurationT"
#define DISH_LANGID_RS232_DefaultConfiguration                  "RS232_DefaultConfiguration"
#define DISH_LANGID_RS232_MakeConfiguration                     "RS232_MakeConfiguration"

#define DISH_LANGID_RS232_Open                                  "RS232_Open"
#define DISH_LANGID_RS232_NumOpen                               "RS232_NumOpen"
#define DISH_LANGID_RS232_IsOpen                                "RS232_IsOpen"
#define DISH_LANGID_RS232_Send                                  "RS232_Send"
#define DISH_LANGID_RS232_SendXON                               "RS232_SendXOn"
#define DISH_LANGID_RS232_SendXOFF                              "RS232_SendXOff"
#define DISH_LANGID_RS232_NumCharactersAvailable                "RS232_NumCharactersAvailable"
#define DISH_LANGID_RS232_Receive                               "RS232_Receive"
#define DISH_LANGID_RS232_ReceiveTimeout                        "RS232_ReceiveTimeout"
#define DISH_LANGID_RS232_ReceiveNumCharacters                  "RS232_ReceiveNumCharacters"
#define DISH_LANGID_RS232_ReceiveSentinel                       "RS232_ReceiveSentinel"
#define DISH_LANGID_RS232_Close                                 "RS232_Close"
#define DISH_LANGID_RS232_CloseAll                              "RS232_CloseAll"


/******************************************************************************

    Debug run-time IDs.
    
 ******************************************************************************/
 
#define DISH_LANGID_IS_LIB_DEBUG                                "IS_LIB_DEBUG"
 
#define DISH_LANGID_DEBUG_PrintSymbolTable                      "DEBUG_PrintSymbolTable"
#define DISH_LANGID_DEBUG_PrintSymbolTableStats                 "DEBUG_PrintSymbolTableStats"

#define DISH_LANGID_DEBUG_PrintParseTree                        "DEBUG_PrintParseTree"

#define DISH_LANGID_DEBUG_PrintParseTreeNodeStats               "DEBUG_PrintParseTreeNodeStats"

#define DISH_LANGID_DEBUG_INFINITE_STACK_DEPTH                  "DEBUG_INFINITE_STACK_DEPTH"
#define DISH_LANGID_DEBUG_MAX_STACK_DEPTH                       "DEBUG_MAX_STACK_DEPTH"
#define DISH_LANGID_DEBUG_StackDepthFunction                    "DEBUG_CurrentStackDepth"

#define DISH_LANGID_DEBUG_DEFAULT_LOGFILE                       "DEBUG_DEFAULT_LOGFILE"
#define DISH_LANGID_DEBUG_Log                                   "DEBUG_Log"


/******************************************************************************

    Graphics run-time IDs.
    
 ******************************************************************************/
 
#define DISH_LANGID_IS_LIB_GRAPH                                "IS_LIB_GRAPH"
#define DISH_LANGID_IS_LIB_GRAPH_ALL_COLORS                     "IS_LIB_GRAPH_ALL_COLORS"

#define DISH_LANGID_GRAPH_ContextT                              "GRAPH_ContextT"
#define DISH_LANGID_GRAPH_CreateContext                         "GRAPH_CreateContext"

#define DISH_LANGID_GRAPH_IntegerPointT                         "GRAPH_IntegerPointT"
#define DISH_LANGID_GRAPH_RealPointT                            "GRAPH_RealPointT"
#define DISH_LANGID_GRAPH_CreatePoint                           "GRAPH_CreatePoint"

#define DISH_LANGID_GRAPH_IntegerLineT                          "GRAPH_IntegerLineT"
#define DISH_LANGID_GRAPH_RealLineT                             "GRAPH_RealLineT"
#define DISH_LANGID_GRAPH_CreateLine                            "GRAPH_CreateLine"

#define DISH_LANGID_GRAPH_FILL_STYLE_SOLID                      "GRAPH_FILL_STYLE_SOLID"
#define DISH_LANGID_GRAPH_FILL_STYLE_TILED                      "GRAPH_FILL_STYLE_TILED"
#define DISH_LANGID_GRAPH_FILL_STYLE_OPAQUE_STIPPLED            "GRAPH_FILL_STYLE_OPAQUE_STIPPLED"
#define DISH_LANGID_GRAPH_FILL_STYLE_STIPPLED                   "GRAPH_FILL_STYLE_STIPPLED"

#define DISH_LANGID_GRAPH_LINE_STYLE_SOLID                      "GRAPH_LINE_STYLE_SOLID"
#define DISH_LANGID_GRAPH_LINE_STYLE_DASHED                     "GRAPH_LINE_STYLE_DASHED"
#define DISH_LANGID_GRAPH_LINE_STYLE_DOUBLE_DASHED              "GRAPH_LINE_STYLE_DOUBLE_DASHED"

#define DISH_LANGID_GRAPH_LINE_CAP_NOT_LAST                     "GRAPH_LINE_CAP_NOT_LAST"
#define DISH_LANGID_GRAPH_LINE_CAP_BUTT                         "GRAPH_LINE_CAP_BUTT"
#define DISH_LANGID_GRAPH_LINE_CAP_ROUND                        "GRAPH_LINE_CAP_ROUND"
#define DISH_LANGID_GRAPH_LINE_CAP_PROJECTING                   "GRAPH_LINE_CAP_PROJECTING"

#define DISH_LANGID_GRAPH_LINE_JOIN_MITRE                       "GRAPH_LINE_JOIN_MITRE"
#define DISH_LANGID_GRAPH_LINE_JOIN_ROUND                       "GRAPH_LINE_JOIN_ROUND"
#define DISH_LANGID_GRAPH_LINE_JOIN_BEVEL                       "GRAPH_LINE_JOIN_BEVEL"

#define DISH_LANGID_GRAPH_NOFILL                                "GRAPH_NOFILL"
#define DISH_LANGID_GRAPH_FILL                                  "GRAPH_FILL"

#define DISH_LANGID_GRAPH_COLOR_MAROON                          "GRAPH_COLOR_MAROON"
#define DISH_LANGID_GRAPH_COLOR_DARK_RED                        "GRAPH_COLOR_DARK_RED"
#define DISH_LANGID_GRAPH_COLOR_BROWN                           "GRAPH_COLOR_BROWN"
#define DISH_LANGID_GRAPH_COLOR_FIREBRICK                       "GRAPH_COLOR_FIREBRICK"
#define DISH_LANGID_GRAPH_COLOR_CRIMSON                         "GRAPH_COLOR_CRIMSON"
#define DISH_LANGID_GRAPH_COLOR_LIGHT_RED                       "GRAPH_COLOR_LIGHT_RED"
#define DISH_LANGID_GRAPH_COLOR_RED                             "GRAPH_COLOR_RED"
#define DISH_LANGID_GRAPH_COLOR_TOMATO                          "GRAPH_COLOR_TOMATO"
#define DISH_LANGID_GRAPH_COLOR_CORAL                           "GRAPH_COLOR_CORAL"
#define DISH_LANGID_GRAPH_COLOR_INDIAN_RED                      "GRAPH_COLOR_INDIAN_RED"
#define DISH_LANGID_GRAPH_COLOR_LIGHT_CORAL                     "GRAPH_COLOR_LIGHT_CORAL"
#define DISH_LANGID_GRAPH_COLOR_DARK_SALMON                     "GRAPH_COLOR_DARK_SALMON"
#define DISH_LANGID_GRAPH_COLOR_SALMON                          "GRAPH_COLOR_SALMON"
#define DISH_LANGID_GRAPH_COLOR_LIGHT_SALMON                    "GRAPH_COLOR_LIGHT_SALMON"
#define DISH_LANGID_GRAPH_COLOR_ORANGE_RED                      "GRAPH_COLOR_ORANGE_RED"
#define DISH_LANGID_GRAPH_COLOR_DARK_ORANGE                     "GRAPH_COLOR_DARK_ORANGE"
#define DISH_LANGID_GRAPH_COLOR_ORANGE                          "GRAPH_COLOR_ORANGE"
#define DISH_LANGID_GRAPH_COLOR_GOLD                            "GRAPH_COLOR_GOLD"
#define DISH_LANGID_GRAPH_COLOR_DARK_GOLDEN_ROD                 "GRAPH_COLOR_DARK_GOLDEN_ROD"
#define DISH_LANGID_GRAPH_COLOR_GOLDEN_ROD                      "GRAPH_COLOR_GOLDEN_ROD"
#define DISH_LANGID_GRAPH_COLOR_PALE_GOLDEN_ROD                 "GRAPH_COLOR_PALE_GOLDEN_ROD"
#define DISH_LANGID_GRAPH_COLOR_DARK_KHAKI                      "GRAPH_COLOR_DARK_KHAKI"
#define DISH_LANGID_GRAPH_COLOR_KHAKI                           "GRAPH_COLOR_KHAKI"
#define DISH_LANGID_GRAPH_COLOR_OLIVE                           "GRAPH_COLOR_OLIVE"
#define DISH_LANGID_GRAPH_COLOR_YELLOW                          "GRAPH_COLOR_YELLOW"
#define DISH_LANGID_GRAPH_COLOR_YELLOW_GREEN                    "COLOR_YELLOW_GREEN"
#define DISH_LANGID_GRAPH_COLOR_DARK_OLIVE_GREEN                "COLOR_DARK_OLIVE_GREEN"
#define DISH_LANGID_GRAPH_COLOR_OLIVE_DRAB                      "GRAPH_COLOR_OLIVE_DRAB "
#define DISH_LANGID_GRAPH_COLOR_LAWN_GREEN                      "GRAPH_COLOR_LAWN_GREEN"
#define DISH_LANGID_GRAPH_COLOR_CHART_REUSE                     "GRAPH_COLOR_CHART_REUSE"
#define DISH_LANGID_GRAPH_COLOR_GREEN_YELLOW                    "GRAPH_COLOR_GREEN_YELLOW"
#define DISH_LANGID_GRAPH_COLOR_DARK_GREEN                      "GRAPH_COLOR_DARK_GREEN"
#define DISH_LANGID_GRAPH_COLOR_GREEN                           "GRAPH_COLOR_GREEN"
#define DISH_LANGID_GRAPH_COLOR_FOREST_GREEN                    "GRAPH_COLOR_FOREST_GREEN"
#define DISH_LANGID_GRAPH_COLOR_LIME                            "GRAPH_COLOR_LIME"
#define DISH_LANGID_GRAPH_COLOR_LIME_GREEN                      "GRAPH_COLOR_LIME_GREEN"
#define DISH_LANGID_GRAPH_COLOR_LIGHT_GREEN                     "GRAPH_COLOR_LIGHT_GREEN"
#define DISH_LANGID_GRAPH_COLOR_PALE_GREEN                      "GRAPH_COLOR_PALE_GREEN"
#define DISH_LANGID_GRAPH_COLOR_DARK_SEA_GREEN                  "GRAPH_COLOR_DARK_SEA_GREEN"
#define DISH_LANGID_GRAPH_COLOR_MEDIUM_SPRING_GREEN             "GRAPH_COLOR_MEDIUM_SPRING_GREEN"
#define DISH_LANGID_GRAPH_COLOR_SPRING_GREEN                    "GRAPH_COLOR_SPRING_GREEN"
#define DISH_LANGID_GRAPH_COLOR_SEA_GREEN                       "GRAPH_COLOR_SEA_GREEN"
#define DISH_LANGID_GRAPH_COLOR_MEDIUM_AQUA_MARINE              "GRAPH_COLOR_MEDIUM_AQUA_MARINE"
#define DISH_LANGID_GRAPH_COLOR_MEDIUM_SEA_GREEN                "GRAPH_COLOR_MEDIUM_SEA_GREEN"
#define DISH_LANGID_GRAPH_COLOR_LIGHT_SEA_GREEN                 "GRAPH_COLOR_LIGHT_SEA_GREEN"
#define DISH_LANGID_GRAPH_COLOR_DARK_SLATE_GRAY                 "GRAPH_COLOR_DARK_SLATE_GRAY"
#define DISH_LANGID_GRAPH_COLOR_TEAL                            "GRAPH_COLOR_TEAL"
#define DISH_LANGID_GRAPH_COLOR_DARK_CYAN                       "GRAPH_COLOR_DARK_CYAN"
#define DISH_LANGID_GRAPH_COLOR_AQUA                            "GRAPH_COLOR_AQUA"
#define DISH_LANGID_GRAPH_COLOR_CYAN                            "GRAPH_COLOR_CYAN"
#define DISH_LANGID_GRAPH_COLOR_LIGHT_CYAN                      "GRAPH_COLOR_LIGHT_CYAN"
#define DISH_LANGID_GRAPH_COLOR_DARK_TURQUOISE                  "GRAPH_COLOR_DARK_TURQUOISE"
#define DISH_LANGID_GRAPH_COLOR_TURQUOISE                       "GRAPH_COLOR_TURQUOISE"
#define DISH_LANGID_GRAPH_COLOR_MEDIUM_TURQUOISE                "GRAPH_COLOR_MEDIUM_TURQUOISE"
#define DISH_LANGID_GRAPH_COLOR_PALE_TURQUOISE                  "GRAPH_COLOR_PALE_TURQUOISE"
#define DISH_LANGID_GRAPH_COLOR_AQUA_MARINE                     "GRAPH_COLOR_AQUA_MARINE"
#define DISH_LANGID_GRAPH_COLOR_POWDER_BLUE                     "GRAPH_COLOR_POWDER_BLUE"
#define DISH_LANGID_GRAPH_COLOR_CADET_BLUE                      "GRAPH_COLOR_CADET_BLUE"
#define DISH_LANGID_GRAPH_COLOR_STEEL_BLUE                      "GRAPH_COLOR_STEEL_BLUE"
#define DISH_LANGID_GRAPH_COLOR_CORN_FLOWER_BLUE                "GRAPH_COLOR_CORN_FLOWER_BLUE"
#define DISH_LANGID_GRAPH_COLOR_DEEP_SKY_BLUE                   "GRAPH_COLOR_DEEP_SKY_BLUE"
#define DISH_LANGID_GRAPH_COLOR_DODGER_BLUE                     "GRAPH_COLOR_DODGER_BLUE"
#define DISH_LANGID_GRAPH_COLOR_LIGHT_BLUE                      "GRAPH_COLOR_LIGHT_BLUE"
#define DISH_LANGID_GRAPH_COLOR_SKY_BLUE                        "GRAPH_COLOR_SKY_BLUE"
#define DISH_LANGID_GRAPH_COLOR_LIGHT_SKY_BLUE                  "GRAPH_COLOR_LIGHT_SKY_BLUE"
#define DISH_LANGID_GRAPH_COLOR_MIDNIGHT_BLUE                   "GRAPH_COLOR_MIDNIGHT_BLUE"
#define DISH_LANGID_GRAPH_COLOR_NAVY                            "GRAPH_COLOR_NAVY"
#define DISH_LANGID_GRAPH_COLOR_DARK_BLUE                       "GRAPH_COLOR_DARK_BLUE"
#define DISH_LANGID_GRAPH_COLOR_MEDIUM_BLUE                     "GRAPH_COLOR_MEDIUM_BLUE"
#define DISH_LANGID_GRAPH_COLOR_BLUE                            "GRAPH_COLOR_BLUE"
#define DISH_LANGID_GRAPH_COLOR_ROYAL_BLUE                      "GRAPH_COLOR_ROYAL_BLUE"
#define DISH_LANGID_GRAPH_COLOR_BLUE_VIOLET                     "GRAPH_COLOR_BLUE_VIOLET"
#define DISH_LANGID_GRAPH_COLOR_INDIGO                          "GRAPH_COLOR_INDIGO"
#define DISH_LANGID_GRAPH_COLOR_DARK_SLATE_BLUE                 "GRAPH_COLOR_DARK_SLATE_BLUE"
#define DISH_LANGID_GRAPH_COLOR_SLATE_BLUE                      "GRAPH_COLOR_SLATE_BLUE"
#define DISH_LANGID_GRAPH_COLOR_MEDIUM_SLATE_BLUE               "GRAPH_COLOR_MEDIUM_SLATE_BLUE"
#define DISH_LANGID_GRAPH_COLOR_MEDIUM_PURPLE                   "GRAPH_COLOR_MEDIUM_PURPLE"
#define DISH_LANGID_GRAPH_COLOR_DARK_MAGENTA                    "GRAPH_COLOR_DARK_MAGENTA"
#define DISH_LANGID_GRAPH_COLOR_DARK_VIOLET                     "GRAPH_COLOR_DARK_VIOLET"
#define DISH_LANGID_GRAPH_COLOR_DARK_ORCHID                     "GRAPH_COLOR_DARK_ORCHID"
#define DISH_LANGID_GRAPH_COLOR_MEDIUM_ORCHID                   "GRAPH_COLOR_MEDIUM_ORCHID"
#define DISH_LANGID_GRAPH_COLOR_PURPLE                          "GRAPH_COLOR_PURPLE"
#define DISH_LANGID_GRAPH_COLOR_THISTLE                         "GRAPH_COLOR_THISTLE"
#define DISH_LANGID_GRAPH_COLOR_PLUM                            "GRAPH_COLOR_PLUM"
#define DISH_LANGID_GRAPH_COLOR_VIOLET                          "GRAPH_COLOR_VIOLET"
#define DISH_LANGID_GRAPH_COLOR_MAGENTA                         "GRAPH_COLOR_MAGENTA"
#define DISH_LANGID_GRAPH_COLOR_ORCHID                          "GRAPH_COLOR_ORCHID"
#define DISH_LANGID_GRAPH_COLOR_MEDIUM_VIOLET_RED               "GRAPH_COLOR_MEDIUM_VIOLET_RED"
#define DISH_LANGID_GRAPH_COLOR_PALE_VIOLET_RED                 "GRAPH_COLOR_PALE_VIOLET_RED"
#define DISH_LANGID_GRAPH_COLOR_DEEP_PINK                       "GRAPH_COLOR_DEEP_PINK"
#define DISH_LANGID_GRAPH_COLOR_HOT_PINK                        "GRAPH_COLOR_HOT_PINK"
#define DISH_LANGID_GRAPH_COLOR_LIGHT_PINK                      "GRAPH_COLOR_LIGHT_PINK"
#define DISH_LANGID_GRAPH_COLOR_PINK                            "GRAPH_COLOR_PINK"
#define DISH_LANGID_GRAPH_COLOR_ANTIQUE_WHITE                   "GRAPH_COLOR_ANTIQUE_WHITE"
#define DISH_LANGID_GRAPH_COLOR_BEIGE                           "GRAPH_COLOR_BEIGE"
#define DISH_LANGID_GRAPH_COLOR_BISQUE                          "GRAPH_COLOR_BISQUE"
#define DISH_LANGID_GRAPH_COLOR_BLANCHED_ALMOND                 "GRAPH_COLOR_BLANCHED_ALMOND"
#define DISH_LANGID_GRAPH_COLOR_WHEAT                           "GRAPH_COLOR_WHEAT"
#define DISH_LANGID_GRAPH_COLOR_CORN_SILK                       "GRAPH_COLOR_CORN_SILK"
#define DISH_LANGID_GRAPH_COLOR_LEMON_CHIFFON                   "GRAPH_COLOR_LEMON CHIFFON"
#define DISH_LANGID_GRAPH_COLOR_LIGHT_GOLDEN_ROD_YELLOW         "GRAPH_COLOR_LIGHT_GOLDEN_ROD_YELLOW"
#define DISH_LANGID_GRAPH_COLOR_LIGHT_YELLOW                    "GRAPH_COLOR_LIGHT_YELLOW"
#define DISH_LANGID_GRAPH_COLOR_SADDLE_BROWN                    "GRAPH_COLOR_SADDLE_BROWN"
#define DISH_LANGID_GRAPH_COLOR_SIENNA                          "GRAPH_COLOR_SIENNA"
#define DISH_LANGID_GRAPH_COLOR_CHOCOLATE                       "GRAPH_COLOR_CHOCOLATE"
#define DISH_LANGID_GRAPH_COLOR_PERN                            "GRAPH_COLOR_PERN"
#define DISH_LANGID_GRAPH_COLOR_SANDY_BROWN                     "GRAPH_COLOR_SANDY_BROWN"
#define DISH_LANGID_GRAPH_COLOR_BURLY_WOOD                      "GRAPH_COLOR_BURLY_WOOD"
#define DISH_LANGID_GRAPH_COLOR_TAN                             "GRAPH_COLOR_TAN"
#define DISH_LANGID_GRAPH_COLOR_ROSY_BROWN                      "GRAPH_COLOR_ROSY_BROWN"
#define DISH_LANGID_GRAPH_COLOR_MOCCASIN                        "GRAPH_COLOR_MOCCASIN"
#define DISH_LANGID_GRAPH_COLOR_NAVAJO_WHITE                    "GRAPH_COLOR_NAVAJO_WHITE"
#define DISH_LANGID_GRAPH_COLOR_PEACH_PUFF                      "GRAPH_COLOR_PEACH_PUFF"
#define DISH_LANGID_GRAPH_COLOR_MISTY_ROSE                      "GRAPH_COLOR_MISTY_ROSE"
#define DISH_LANGID_GRAPH_COLOR_LAVENDER_BLUSH                  "GRAPH_COLOR_LAVENDER_BLUSH"
#define DISH_LANGID_GRAPH_COLOR_LINEN                           "GRAPH_COLOR_LINEN"
#define DISH_LANGID_GRAPH_COLOR_OLD_LACE                        "GRAPH_COLOR_OLD_LACE"
#define DISH_LANGID_GRAPH_COLOR_PAPAYA_WHIP                     "GRAPH_COLOR_PAPAYA_WHIP"
#define DISH_LANGID_GRAPH_COLOR_SEA_SHELL                       "GRAPH_COLOR_SEA_SHELL"
#define DISH_LANGID_GRAPH_COLOR_MINT_CREAM                      "GRAPH_COLOR_MINT_CREAM"
#define DISH_LANGID_GRAPH_COLOR_SLATE_GRAY                      "GRAPH_COLOR_SLATE_GRAY"
#define DISH_LANGID_GRAPH_COLOR_LIGHT_SLATE_GRAY                "GRAPH_COLOR_LIGHT_SLATE_GRAY"
#define DISH_LANGID_GRAPH_COLOR_LIGHT_SLATE_BLUE                "GRAPH_COLOR_LIGHT_SLATE_BLUE"
#define DISH_LANGID_GRAPH_COLOR_LAVENDER                        "GRAPH_COLOR_LAVENDER"
#define DISH_LANGID_GRAPH_COLOR_FLORAL_WHITE                    "GRAPH_COLOR_FLORAL_WHITE"
#define DISH_LANGID_GRAPH_COLOR_ALICE_BLUE                      "GRAPH_COLOR_ALICE_BLUE"
#define DISH_LANGID_GRAPH_COLOR_GHOST_WHITE                     "GRAPH_COLOR_GHOST_WHITE"
#define DISH_LANGID_GRAPH_COLOR_HONEYDEW                        "GRAPH_COLOR_HONEYDEW"
#define DISH_LANGID_GRAPH_COLOR_IVORY                           "GRAPH_COLOR_IVORY"
#define DISH_LANGID_GRAPH_COLOR_AZURE                           "GRAPH_COLOR_AZURE"
#define DISH_LANGID_GRAPH_COLOR_SNOW                            "GRAPH_COLOR_SNOW"
#define DISH_LANGID_GRAPH_COLOR_BLACK                           "GRAPH_COLOR_BLACK"
#define DISH_LANGID_GRAPH_COLOR_DIM_GRAY                        "GRAPH_COLOR_DIM_GRAY"
#define DISH_LANGID_GRAPH_COLOR_GRAY                            "GRAPH_COLOR_GRAY"
#define DISH_LANGID_GRAPH_COLOR_DARK_GRAY                       "GRAPH_COLOR_DARK_GRAY"
#define DISH_LANGID_GRAPH_COLOR_SILVER                          "GRAPH_COLOR_SILVER"
#define DISH_LANGID_GRAPH_COLOR_LIGHT_GRAY                      "GRAPH_COLOR_LIGHT_GRAY"
#define DISH_LANGID_GRAPH_COLOR_GAINSBORO                       "GRAPH_COLOR_GAINSBORO"
#define DISH_LANGID_GRAPH_COLOR_WHITE_SMOKE                     "GRAPH_COLOR_WHITE_SMOKE"
#define DISH_LANGID_GRAPH_COLOR_WHITE                           "GRAPH_COLOR_WHITE"

#define DISH_LANGID_GRAPH_KEY_ESC                               "GRAPH_KEY_ESC"
#define DISH_LANGID_GRAPH_KEY_DOWN                              "GRAPH_KEY_DOWN"
#define DISH_LANGID_GRAPH_KEY_UP                                "GRAPH_KEY_UP"
#define DISH_LANGID_GRAPH_KEY_LEFT                              "GRAPH_KEY_LEFT"
#define DISH_LANGID_GRAPH_KEY_RIGHT                             "GRAPH_KEY_RIGHT"
#define DISH_LANGID_GRAPH_KEY_HOME                              "GRAPH_KEY_HOME"
#define DISH_LANGID_GRAPH_KEY_END                               "GRAPH_KEY_END"
#define DISH_LANGID_GRAPH_KEY_BACKSPACE                         "GRAPH_KEY_BACKSPACE"
#define DISH_LANGID_GRAPH_KEY_F1                                "GRAPH_KEY_F1"
#define DISH_LANGID_GRAPH_KEY_F2                                "GRAPH_KEY_F2"
#define DISH_LANGID_GRAPH_KEY_F3                                "GRAPH_KEY_F3"
#define DISH_LANGID_GRAPH_KEY_F4                                "GRAPH_KEY_F4"
#define DISH_LANGID_GRAPH_KEY_F5                                "GRAPH_KEY_F5"
#define DISH_LANGID_GRAPH_KEY_F6                                "GRAPH_KEY_F6"
#define DISH_LANGID_GRAPH_KEY_F7                                "GRAPH_KEY_F7"
#define DISH_LANGID_GRAPH_KEY_F8                                "GRAPH_KEY_F8"
#define DISH_LANGID_GRAPH_KEY_F9                                "GRAPH_KEY_F9"
#define DISH_LANGID_GRAPH_KEY_F10                               "GRAPH_KEY_F10"
#define DISH_LANGID_GRAPH_KEY_F11                               "GRAPH_KEY_F11"
#define DISH_LANGID_GRAPH_KEY_F12                               "GRAPH_KEY_F12"
#define DISH_LANGID_GRAPH_KEY_DELETE                            "GRAPH_KEY_DELETE"
#define DISH_LANGID_GRAPH_KEY_INSERT                            "GRAPH_KEY_INSERT"

#define DISH_LANGID_GRAPH_Start                                 "GRAPH_Start"
#define DISH_LANGID_GRAPH_IsStarted                             "GRAPH_IsStarted"
#define DISH_LANGID_GRAPH_End                                   "GRAPH_End"

#define DISH_LANGID_GRAPH_EVENT_IDLE                            "GRAPH_EVENT_IDLE"
#define DISH_LANGID_GRAPH_EVENT_REDRAW                          "GRAPH_EVENT_REDRAW"
#define DISH_LANGID_GRAPH_EVENT_RESIZE                          "GRAPH_EVENT_RESIZE"
#define DISH_LANGID_GRAPH_EVENT_KEY_PRESS                       "GRAPH_EVENT_KEY_PRESS"
#define DISH_LANGID_GRAPH_EVENT_KEY_RELEASE                     "GRAPH_EVENT_KEY_RELEASE"
#define DISH_LANGID_GRAPH_EVENT_BUTTON_PRESS                    "GRAPH_EVENT_BUTTON_PRESS"
#define DISH_LANGID_GRAPH_EVENT_BUTTON_RELEASE                  "GRAPH_EVENT_BUTTON_RELEASE"

#define DISH_LANGID_GRAPH_IdleEventT                            "GRAPH_IdleEventT"
#define DISH_LANGID_GRAPH_RedrawEventT                          "GRAPH_RedrawEventT"
#define DISH_LANGID_GRAPH_ResizeEventT                          "GRAPH_ResizeEventT"
#define DISH_LANGID_GRAPH_KeyPressEventT                        "GRAPH_KeyPressEventT"
#define DISH_LANGID_GRAPH_KeyReleaseEventT                      "GRAPH_KeyReleaseEventT"
#define DISH_LANGID_GRAPH_ButtonPressEventT                     "GRAPH_ButtonPressEventT"
#define DISH_LANGID_GRAPH_ButtonReleaseEventT                   "GRAPH_ButtonReleaseEventT"

#define DISH_LANGID_GRAPH_BUTTON_1                              "GRAPH_BUTTON_1"
#define DISH_LANGID_GRAPH_BUTTON_2                              "GRAPH_BUTTON_2"
#define DISH_LANGID_GRAPH_BUTTON_3                              "GRAPH_BUTTON_3"
#define DISH_LANGID_GRAPH_BUTTON_4                              "GRAPH_BUTTON_4"
#define DISH_LANGID_GRAPH_BUTTON_5                              "GRAPH_BUTTON_5"

#define DISH_LANGID_GRAPH_EVENT_CONTINUE                        "GRAPH_EVENT_CONTINUE"
#define DISH_LANGID_GRAPH_EVENT_TERMINATE                       "GRAPH_EVENT_TERMINATE"

#define DISH_LANGID_GRAPH_PushEventProcessor                    "GRAPH_PushEventProcessor"
#define DISH_LANGID_GRAPH_PopEventProcessor                     "GRAPH_PopEventProcessor"

#define DISH_LANGID_GRAPH_ProcessEvent                          "GRAPH_ProcessEvent"
#define DISH_LANGID_GRAPH_EventLoop                             "GRAPH_EventLoop"

#define DISH_LANGID_GRAPH_Refresh                               "GRAPH_Refresh"

#define DISH_LANGID_GRAPH_ApplyContext                          "GRAPH_ApplyContext"

#define DISH_LANGID_GRAPH_MakeColor                             "GRAPH_MakeColor"

#define DISH_LANGID_GRAPH_Clear                                 "GRAPH_Clear"

#define DISH_LANGID_GRAPH_DrawPixel                             "GRAPH_DrawPixel"
#define DISH_LANGID_GRAPH_DrawLine                              "GRAPH_DrawLine"
#define DISH_LANGID_GRAPH_DrawLines                             "GRAPH_DrawLines"

#define DISH_LANGID_GRAPH_DrawBox                               "GRAPH_DrawBox"
#define DISH_LANGID_GRAPH_DrawArc                               "GRAPH_DrawArc"

#define DISH_LANGID_GRAPH_DrawPolygon                           "GRAPH_DrawPolygon"

#define DISH_LANGID_GRAPH_GetFontList                           "GRAPH_GetFontList"
#define DISH_LANGID_GRAPH_GetTextDimensions                     "GRAPH_GetTextDimensions"
#define DISH_LANGID_GRAPH_DrawText                              "GRAPH_DrawText"

#define DISH_LANGID_GRAPH_MoveTo                                "GRAPH_MoveTo"
#define DISH_LANGID_GRAPH_LineTo                                "GRAPH_LineTo"


/******************************************************************************

    Zip run-time IDs.
    
 ******************************************************************************/
 
#define DISH_LANGID_IS_LIB_ZIP                                  "IS_LIB_ZIP"

#define DISH_LANGID_Zip                                         "Zip"
#define DISH_LANGID_ZipTogether                                 "ZipTogether"

#define DISH_LANGID_ZipValue                                    "ZipValue"
#define DISH_LANGID_ZipIncrement                                "ZipIncrement"
#define DISH_LANGID_ZipDecrement                                "ZipDecrement"


#endif

