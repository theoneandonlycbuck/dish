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

#include <stdint.h>

#include <cctype>
#include <map>
#include <sstream>
#include <vector>

#include "dishconfig.h"

#include "atomics.h"
#include "cmdln.h"

#ifdef LANG_LIB_DATABASE
#include "db.h"
#endif

#include "exception.h"

#ifdef LANG_LIB_GRAPH
#include "graph.h"
#endif

#include "inline.h"

#ifdef LANG_LIB_CORE
#include "langcore.h"
#endif

#ifdef LANG_LIB_DATABASE
#include "langdb.h"
#endif

#ifdef LANG_LIB_DEBUG
#include "langdebug.h"
#endif

#include "langerr.h"

#ifdef LANG_LIB_FILEIO
#include "langfile.h"
#endif

#ifdef LANG_LIB_FILESYS
#include "langfilesys.h"
#endif

#ifdef LANG_LIB_GRAPH
#include "langgraph.h"
#endif

#include "langid.h"
#include "langio.h"
#include "langmath.h"

#ifdef LANG_LIB_NETWORK
#include "langnet.h"
#endif

#ifdef LANG_LIB_REGULAR_EXPRESSION
#include "langregex.h"
#endif

#ifdef LANG_LIB_RS232
#include "langrs232.h"
#endif

#ifdef LANG_LIB_STRING
#include "langstr.h"
#endif

#ifdef LANG_LIB_DATETIME
#include "langtime.h"
#endif

#ifdef LANG_LIB_TEXTIO
#include "langtxtio.h"
#endif

#include "language.h"

#ifdef LANG_LIB_RS232
#include "rs232.h"
#endif

#ifdef LANG_LIB_TEXTIO
#include "textio.h"
#endif

#ifdef LANG_LIB_ZIP
#include "langzip.h"
#endif

#include "types.h"
#include "utility.h"
#include "version.h"

namespace
{

    ////////////////////////////////////////////////////////////////////////////
    
    INLINEC std::shared_ptr< dish::IntegerValue > CreateLockedInteger(const dish::IntegerT &value)
    {
        return dish::IntegerValue::MakeValue(value, dish::LOCKED);
    }
    
    INLINEC std::shared_ptr< dish::IntegerValue > CreateGraphColor(const int &red, const int &green, const int &blue)
    {
#ifdef LANG_LIB_GRAPH
        return CreateLockedInteger(
            static_cast< dish::IntegerT >(
                dish::GRAPH_MakeColorRGB(
                    static_cast< uint8_t >(red & 0x000000FF),
                    static_cast< uint8_t >(green & 0x000000FF),
                    static_cast< uint8_t >(blue & 0x000000FF)
                )
            )
        );
#else
        return CreateLockedInteger(static_cast< dish::IntegerT >(0));
#endif
    }
    
    ////////////////////////////////////////////////////////////////////////////

}

/******************************************************************************

    dish::LanguageSymbolTable class definitions

 ******************************************************************************/
 
void dish::LanguageSymbolTable::insert(const std::string &key, std::shared_ptr< dish::iAtomic > value) const
{
    if(dish::iAtomic::typeExecutable != value->Type())
    {
        mBase->Insert(key, value);
    }
    else
    {
        std::stringstream mangled_key;
        mangled_key << key;
        mangled_key << "_";
        mangled_key << value->NumParameters();
        
        mBase->Insert(mangled_key.str(), value);
    }
}

dish::LanguageSymbolTable::LanguageSymbolTable(const bool &profile, const int &maxdepth) : dish::iSymbolTable(),

    mBase(MakeSystemSymbolTable()),
    
    mStack(maxdepth),
    
    mProfile()

{
    assert(0 != mBase.get());
    
    if(profile)
    {
        mProfile.reset(new ExecutionProfile());
    }
    
    ///////////////
    
    insert(DISH_LANGID_InterpreterVersion, CreateVersionStructure(MAJOR_VERSION, MINOR_VERSION, REVISION_VERSION, LOCKED));
    insert(DISH_LANGID_LanguageVersion, CreateVersionStructure(LANG_MAJOR_VERSION, LANG_MINOR_VERSION, LANG_REVISION_VERSION, LOCKED));
    insert(DISH_LANGID_LibraryVersion, CreateVersionStructure(LIBRARY_MAJOR_VERSION, LIBRARY_MINOR_VERSION, LIBRARY_REVISION_VERSION, LOCKED));
    
#ifdef LANG_LIB_CORE

    insert(DISH_LANGID_IS_LIB_CORE, BooleanValue::MakeLockedValue(true));
    
    ///////////////
    
    insert(DISH_LANGID_NULL, NullValue::MakeValue());
    
    insert(DISH_LANGID_NOINDENT, CreateLockedInteger(-1));
    
    insert(DISH_LANGID_IsEntryPoint, IsEntryPointFunction::MakeValue());
    insert(DISH_LANGID_ReleaseCachedParseTreeNodes, ReleaseCachedParseTreeNodesFunction::MakeValue());
    
    insert(DISH_LANGID_VersionT, CreateVersionStructureType());
    insert(DISH_LANGID_MakeVersion, MakeVersionFunction::MakeValue());
    insert(DISH_LANGID_VersionLessThan, VersionLessThanFunction::MakeValue());
    insert(DISH_LANGID_VersionEqual, VersionEqualFunction::MakeValue());
    insert(DISH_LANGID_VersionAsString, VersionAsStringFunction::MakeValue());
    
    insert(DISH_LANGID_GetEnvironmentVariable, GetEnvironmentVariableFunction::MakeValue());

    insert(DISH_LANGID_Terminate, TerminateFunction::MakeValue());
    insert(DISH_LANGID_Sleep, SleepFunction::MakeValue());
    
    insert(DISH_LANGID_System, SystemFunction::MakeValue());
    insert(DISH_LANGID_Execute, ExecuteFunction::MakeValue());
    
    insert(DISH_LANGID_Copy, CopyFunction::MakeValue());
    insert(DISH_LANGID_Clone, CloneFunction::MakeValue());
    
    insert(DISH_LANGID_AsBoolean, AsBooleanFunction::MakeValue());
    insert(DISH_LANGID_AsInteger, AsIntegerFunction::MakeValue());
    insert(DISH_LANGID_AsReal, AsRealFunction::MakeValue());
    insert(DISH_LANGID_AsString, AsStringFunction::MakeValue());
    
    insert(DISH_LANGID_Append, AppendFunction::MakeValue());
    insert(DISH_LANGID_Insert, InsertFunction::MakeValue());
    
    insert(DISH_LANGID_Sort, SortFunction::MakeValue());
    insert(DISH_LANGID_Find, FindFunction::MakeValue());
    insert(DISH_LANGID_FindSorted, FindSortedFunction::MakeValue());
    insert(DISH_LANGID_Swap, SwapFunction::MakeValue());
    
    //  Add as a function and as a reference that can be passed without name-
    //  mangling.
    {
        std::shared_ptr< iAtomic > lessthan(CompareLessThanFunction::MakeValue());
    
        insert(DISH_LANGID_CompareLessThan, lessthan);
        mBase->Insert(DISH_LANGID_SORT_ASCENDING, CompareLessThanFunction::MakeValue());
    }
    
    //  Add as a function and as a reference that can be passed without name-
    //  mangling.
    {
        std::shared_ptr< iAtomic > greaterthan(CompareGreaterThanFunction::MakeValue());
    
        insert(DISH_LANGID_CompareGreaterThan, greaterthan);
        mBase->Insert(DISH_LANGID_SORT_DESCENDING, CompareGreaterThanFunction::MakeValue());
    }
    
    //  Add as a function and as a reference that can be passed without name-
    //  mangling.
    {
        std::shared_ptr< iAtomic > equal(CompareEqualFunction::MakeValue());
    
        insert(DISH_LANGID_CompareEqual, equal);
        mBase->Insert(DISH_LANGID_EQUAL, CompareEqualFunction::MakeValue());
    }
    
    insert(DISH_LANGID_IsLocked, IsLockedFunction::MakeValue());
    
    insert(DISH_LANGID_IsNull, IsNullFunction::MakeValue());
    insert(DISH_LANGID_IsType, IsTypeFunction::MakeValue());
    insert(DISH_LANGID_IsBoolean, IsBooleanFunction::MakeValue());
    insert(DISH_LANGID_IsInteger, IsIntegerFunction::MakeValue());
    insert(DISH_LANGID_IsReal, IsRealFunction::MakeValue());
    insert(DISH_LANGID_IsString, IsStringFunction::MakeValue());
    insert(DISH_LANGID_IsArray, IsArrayFunction::MakeValue());
    insert(DISH_LANGID_IsDictionary, IsDictionaryFunction::MakeValue());
    insert(DISH_LANGID_IsStructure, IsStructureFunction::MakeValue());
    insert(DISH_LANGID_IsFunction, IsFunctionFunction::MakeValue());
    
    insert(DISH_LANGID_StringAsNumeric, StringAsNumericFunction::MakeValue());
    
    insert(DISH_LANGID_TypeOf, TypeOfFunction::MakeValue());
    
    insert(DISH_LANGID_TypeId, TypeIdFunction::MakeValue());
    
    insert(DISH_LANGID_TYPEID_Null, CreateLockedInteger(static_cast< IntegerT >(iAtomic::typeNull)));
    insert(DISH_LANGID_TYPEID_Type, CreateLockedInteger(static_cast< IntegerT >(iAtomic::typeType)));
    insert(DISH_LANGID_TYPEID_Boolean, CreateLockedInteger(static_cast< IntegerT >(iAtomic::typeBoolean)));
    insert(DISH_LANGID_TYPEID_Integer, CreateLockedInteger(static_cast< IntegerT >(iAtomic::typeInteger)));
    insert(DISH_LANGID_TYPEID_Real, CreateLockedInteger(static_cast< IntegerT >(iAtomic::typeReal)));
    insert(DISH_LANGID_TYPEID_String, CreateLockedInteger(static_cast< IntegerT >(iAtomic::typeString)));
    insert(DISH_LANGID_TYPEID_Array, CreateLockedInteger(static_cast< IntegerT >(iAtomic::typeArray)));
    insert(DISH_LANGID_TYPEID_Dictionary, CreateLockedInteger(static_cast< IntegerT >(iAtomic::typeDictionary)));
    insert(DISH_LANGID_TYPEID_Structure, CreateLockedInteger(static_cast< IntegerT >(iAtomic::typeStructure)));
    insert(DISH_LANGID_TYPEID_Executable, CreateLockedInteger(static_cast< IntegerT >(iAtomic::typeExecutable)));
    
    insert(DISH_LANGID_RANGE_BOUNDARY_ERROR, CreateLockedInteger(static_cast< IntegerT >(iAtomic::rngbndError)));
    insert(DISH_LANGID_RANGE_BOUNDARY_CAP, CreateLockedInteger(static_cast< IntegerT >(iAtomic::rngbndCap)));
    insert(DISH_LANGID_RANGE_BOUNDARY_ROLLOVER, CreateLockedInteger(static_cast< IntegerT >(iAtomic::rngbndRollover)));
    
    #ifdef DISH_32BIT_ATOMICS
        insert(DISH_LANGID_USES_32BIT_ATOMICS, BooleanValue::MakeLockedValue(static_cast< BooleanT >(true)));
        insert(DISH_LANGID_USES_64BIT_ATOMICS, BooleanValue::MakeLockedValue(static_cast< BooleanT >(false)));
    #endif
    
    #ifdef DISH_64BIT_ATOMICS
        insert(DISH_LANGID_USES_32BIT_ATOMICS, BooleanValue::MakeLockedValue(static_cast< BooleanT >(false)));
        insert(DISH_LANGID_USES_64BIT_ATOMICS, BooleanValue::MakeLockedValue(static_cast< BooleanT >(true)));
    #endif
    
    insert(DISH_LANGID_BOOLEAN_MIN, BooleanValue::MakeLockedValue(BOOLEAN_MIN));
    insert(DISH_LANGID_BOOLEAN_MAX, BooleanValue::MakeLockedValue(BOOLEAN_MAX));
    insert(DISH_LANGID_INTEGER_MIN, CreateLockedInteger(INTEGER_MIN));
    insert(DISH_LANGID_INTEGER_MAX, CreateLockedInteger(INTEGER_MAX));
    insert(DISH_LANGID_INTEGER_EPS, CreateLockedInteger(INTEGER_EPS));
    insert(DISH_LANGID_REAL_MIN, RealValue::MakeValue(REAL_MIN, dish::LOCKED));
    insert(DISH_LANGID_REAL_MAX, RealValue::MakeValue(REAL_MAX, dish::LOCKED));
    insert(DISH_LANGID_REAL_EPS, RealValue::MakeValue(REAL_EPS, dish::LOCKED));
    
    insert(DISH_LANGID_MinimumFunction, MinimumFunction::MakeValue());
    insert(DISH_LANGID_MinimumFunction, Minimum2Function::MakeValue());
    insert(DISH_LANGID_MinimumFunction, Minimum3Function::MakeValue());
    insert(DISH_LANGID_MaximumFunction, MaximumFunction::MakeValue());
    insert(DISH_LANGID_MaximumFunction, Maximum2Function::MakeValue());
    insert(DISH_LANGID_MaximumFunction, Maximum3Function::MakeValue());
    
    insert(DISH_LANGID_IncFunction, IncFunction::MakeValue());
    insert(DISH_LANGID_IncFunction, Inc2Function::MakeValue());
    insert(DISH_LANGID_DecFunction, DecFunction::MakeValue());
    insert(DISH_LANGID_DecFunction, Dec2Function::MakeValue());
    
    insert(DISH_LANGID_ErrorT, CreateErrorStructureType());
    
    insert(DISH_LANGID_ERR_OK, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_Ok)));
    insert(DISH_LANGID_ERR_TERMINATE, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_Terminate)));
    insert(DISH_LANGID_ERR_ILLEGAL_CAST, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_IllegalCast)));
    insert(DISH_LANGID_ERR_VALUE_LOCKED, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_ValueLocked)));
    insert(DISH_LANGID_ERR_NO_SUCH_MEMBER, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_NoSuchMember)));
    insert(DISH_LANGID_ERR_DUPLICATE_SYMBOL, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_DuplicateSymbol)));
    insert(DISH_LANGID_ERR_NO_SUCH_SYMBOL, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_NoSuchSymbol)));
    insert(DISH_LANGID_ERR_DIVIDE_BY_ZERO, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_DivideByZero)));
    insert(DISH_LANGID_ERR_DOMAIN_ERROR, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_DomainError)));
    insert(DISH_LANGID_ERR_RANGE_ERROR, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_RangeError)));
    insert(DISH_LANGID_ERR_ILLEGAL_HANDLE, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_IllegalHandle)));
    insert(DISH_LANGID_ERR_ILLEGAL_VALUE, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_IllegalValue)));
    
    insert(DISH_LANGID_ERR_STACK_OVERFLOW_ERROR, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_StackOverflowError)));
    
    #ifdef LANG_LIB_FILEIO
        insert(DISH_LANGID_ERR_TOO_MANY_OPEN_FILES, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_TooManyOpenFiles)));
        insert(DISH_LANGID_ERR_UNABLE_TO_OPEN_FILE, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_UnableToOpenFile)));
        insert(DISH_LANGID_ERR_FILE_NOT_OPEN, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_FileNotOpen)));
        insert(DISH_LANGID_ERR_FILE_WRITE_ERROR, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_FileWriteError)));
        insert(DISH_LANGID_ERR_FILE_READ_ERROR, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_FileReadError)));
        insert(DISH_LANGID_ERR_FILE_READ_END_OF_FILE, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_FileReadEndOfFile)));
    #endif
    
    #ifdef LANG_LIB_NETWORK
        insert(DISH_LANGID_ERR_TOO_MANY_OPEN_SOCKETS, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_TooManyOpenSockets)));
        insert(DISH_LANGID_ERR_UNABLE_TO_OPEN_SOCKET, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_UnableToOpenSocket)));
        insert(DISH_LANGID_ERR_UNABLE_TO_CLOSE_SOCKET, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_UnableToCloseSocket)));
        insert(DISH_LANGID_ERR_NETWORK_INVALID_ADDRESS, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_NetworkInvalidAddress)));
        insert(DISH_LANGID_ERR_NETWORK_UNABLE_TO_CONNECT_TO_SERVER, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_NetworkUnableToConnectToServer)));
        insert(DISH_LANGID_ERR_NETWORK_SOCKET_NOT_OPEN, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_NetworkSocketNotOpen)));
        insert(DISH_LANGID_ERR_NETWORK_SOCKET_WRITE_ERROR, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_NetworkSocketWriteError)));
        insert(DISH_LANGID_ERR_NETWORK_SOCKET_READ_ERROR, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_NetworkSocketReadError)));
    #endif
    
    #ifdef LANG_LIB_MATH_MATRIX
        insert(DISH_LANGID_ERR_MATRIX_NOT_VALID_ERROR, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_MatrixInvalidError)));
        insert(DISH_LANGID_ERR_MATRIX_NOT_SQUARE_ERROR, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_MatrixNotSquareError)));
        insert(DISH_LANGID_ERR_ZERO_DETERMINANT_ERROR, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_ZeroDeterminantError)));
        insert(DISH_LANGID_ERR_MATRIX_DIMENSION_ERROR, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_MatrixDimensionError)));
    #endif
    
    #ifdef LANG_LIB_DATABASE
        insert(DISH_LANGID_ERR_DB_INVALID_CONNECTION_TYPE, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_DB_InvalidConnectionType)));
        insert(DISH_LANGID_ERR_DB_TOO_MANY_OPEN_CONNECTIONS, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_DB_TooManyOpenConnections)));
        insert(DISH_LANGID_ERR_DB_UNABLE_TO_OPEN_CONNECTION, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_DB_UnableToOpenConnection)));
        insert(DISH_LANGID_ERR_DB_CONNECTION_NOT_OPEN, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_DB_ConnectionNotOpen)));
        insert(DISH_LANGID_ERR_DB_CONNECTION_DROPPED, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_DB_ConnectionDropped)));
        insert(DISH_LANGID_ERR_DB_QUERY_ERROR, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_DB_QueryError)));
    #endif
    
    #ifdef LANG_LIB_RS232
        insert(DISH_LANGID_ERR_RS232_CONFIGURATION_NOT_SUPPORTED, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_RS232_ConfigurationNotSupported)));
        insert(DISH_LANGID_ERR_RS232_UNABLE_TO_OPEN_PORT, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_RS232_UnableToOpenPort)));
        insert(DISH_LANGID_ERR_RS232_PORT_NOT_OPEN, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_RS232_PortNotOpen)));
        insert(DISH_LANGID_ERR_RS232_WRITE_FAILURE, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_RS232_WriteFailure)));
        insert(DISH_LANGID_ERR_RS232_READ_FAILURE, CreateLockedInteger(static_cast< IntegerT >(ErrorCallbacks::ERR_RS232_ReadFailure)));
    #endif
    
    insert(DISH_LANGID_OnErrorPush, OnErrorPushFunction::MakeValue());
    insert(DISH_LANGID_OnErrorInvoke, OnErrorInvokeFunction::MakeValue());
    insert(DISH_LANGID_OnErrorPop, OnErrorPopFunction::MakeValue());

    insert(DISH_LANGID_Print, PrintFunction::MakeValue());
    insert(DISH_LANGID_Println, Println0Function::MakeValue());
    insert(DISH_LANGID_Println, PrintlnFunction::MakeValue());
    insert(DISH_LANGID_Newln, NewlnFunction::MakeValue());
    
    insert(DISH_LANGID_KeyPressed, KeyPressedFunction::MakeValue());
    insert(DISH_LANGID_Read, ReadFunction::MakeValue());
    insert(DISH_LANGID_ReadCh, ReadChFunction::MakeValue());
    insert(DISH_LANGID_ReadInteger, ReadIntegerFunction::MakeValue());
    insert(DISH_LANGID_ReadReal, ReadRealFunction::MakeValue());
    insert(DISH_LANGID_Readln, ReadlnFunction::MakeValue());
    
    insert(DISH_LANGID_SymbolOfFunctionFunction, SymbolOfFunctionFunction::MakeValue());
    insert(DISH_LANGID_SymbolExistsFunction, SymbolExistsFunction::MakeValue());
    
    insert(DISH_LANGID_IsExactlyEqual, IsExactlyEqualFunction::MakeValue());
    
#else

    insert(DISH_LANGID_IS_LIB_CORE, BooleanValue::MakeLockedValue(false));
    
#endif
    
    ///////////////
    
#ifdef LANG_LIB_FILEIO

    insert(DISH_LANGID_IS_LIB_FILEIO, BooleanValue::MakeLockedValue(true));
    
    ///////////////

    insert(DISH_LANGID_FILE_READ, CreateLockedInteger(static_cast< IntegerT >(FileList::fmRead)));
    insert(DISH_LANGID_FILE_WRITE, CreateLockedInteger(static_cast< IntegerT >(FileList::fmWrite)));
    insert(DISH_LANGID_FILE_WRITE_EX, CreateLockedInteger(static_cast< IntegerT >(FileList::fmExWrite)));
    insert(DISH_LANGID_FILE_APPEND, CreateLockedInteger(static_cast< IntegerT >(FileList::fmAppend)));
    
    insert(DISH_LANGID_MAX_OPEN_FILES, CreateLockedInteger(FileList::MAX_OPEN_FILES));
    
    insert(DISH_LANGID_FileOpen, FileOpenFunction::MakeValue());
    insert(DISH_LANGID_FileNumOpen, FileNumOpenFunction::MakeValue());
    insert(DISH_LANGID_FileWrite, FileWriteFunction::MakeValue());
    insert(DISH_LANGID_FileWriteln, FileWritelnFunction::MakeValue());
    insert(DISH_LANGID_FileReadText, FileReadTextFunction::MakeValue());
    insert(DISH_LANGID_FileReadBoolean, FileReadBooleanFunction::MakeValue());
    insert(DISH_LANGID_FileReadInteger, FileReadIntegerFunction::MakeValue());
    insert(DISH_LANGID_FileReadReal, FileReadRealFunction::MakeValue());
    insert(DISH_LANGID_FileReadln, FileReadlnFunction::MakeValue());
    insert(DISH_LANGID_FileEndOfFile, FileEndOfFileFunction::MakeValue());
    insert(DISH_LANGID_FileFlush, FileFlushFunction::MakeValue());
    insert(DISH_LANGID_FileClose, FileCloseFunction::MakeValue());
    
#else

    insert(DISH_LANGID_IS_LIB_FILEIO, BooleanValue::MakeLockedValue(false));
    
#endif
    
    ///////////////
    
#ifdef LANG_LIB_STRING

    insert(DISH_LANGID_IS_LIB_STRING, BooleanValue::MakeLockedValue(true));
    
    ///////////////

    insert(DISH_LANGID_CASE_SENSITIVE, BooleanValue::MakeLockedValue(true));
    insert(DISH_LANGID_CASE_INSENSITIVE, BooleanValue::MakeLockedValue(false));
    
    insert(DISH_LANGID_STRINVALID, CreateLockedInteger(STRINVALID));
    
    /*
        Dynamically build the strings containing digit-, lower-case-, upper-
        case-, printable-, punctuation-, and whitespace-characters for two
        reasons: (1) we will be certain to capture all of the character in each
        class (at least according to the C/C++ run-time library), and (b) ensure 
        the characters in the string are in increasing order by ASCII value
        (allowing the strings to be searched efficiantly).
    */
    {
        std::string strcntrl;
        std::string strdigit;
        std::string strlower;
        std::string strupper;
        std::string strprint;
        std::string strpunct;
        std::string strspace;
    
        for(int ch(0); ch < 256; ++ch)
        {
            const char character(static_cast< char >(ch));
            
            if(std::iscntrl(ch))
            {
                strcntrl.append(1, character);
            }
            
            if(std::isdigit(ch))
            {
                strdigit.append(1, character);
            }
            
            if(std::islower(ch))
            {
                strlower.append(1, character);
            }
            
            if(std::isupper(ch))
            {
                strupper.append(1, character);
            }
            
            if(std::isprint(ch))
            {
                strprint.append(1, character);
            }
            
            if(std::ispunct(ch))
            {
                strpunct.append(1, character);
            }
        
            if(std::isspace(ch))
            {
                strspace.append(1, character);
            }
        }
        
        insert(DISH_LANGID_STRCONTROLCHARS, StringValue::MakeValue(strcntrl, LOCKED));
        insert(DISH_LANGID_STRDIGITCHARS, StringValue::MakeValue(strdigit, LOCKED));
        insert(DISH_LANGID_STRLOWERCASECHARS, StringValue::MakeValue(strlower, LOCKED));
        insert(DISH_LANGID_STRUPPERCASECHARS, StringValue::MakeValue(strupper, LOCKED));
        insert(DISH_LANGID_STRPRINTABLECHARS, StringValue::MakeValue(strprint, LOCKED));
        insert(DISH_LANGID_STRPUNCTUATIONCHARS, StringValue::MakeValue(strpunct, LOCKED));
        insert(DISH_LANGID_STRWHITESPACECHARS, StringValue::MakeValue(strspace, LOCKED));
    }
    insert(DISH_LANGID_STREOLNCHARS, StringValue::MakeValue(EOLN_CHARACTERS, LOCKED));
    
    insert(DISH_LANGID_STRSINGLEQUOTE, StringValue::MakeValue("'", LOCKED));
    insert(DISH_LANGID_STRDOUBLEQUOTE, StringValue::MakeValue("\"", LOCKED));
    insert(DISH_LANGID_STRBACKSLASH, StringValue::MakeValue("\\", LOCKED));
    insert(DISH_LANGID_STRNEWLINE, StringValue::MakeValue("\n", LOCKED));
    
    insert(DISH_LANGID_STRSINGLE, BooleanValue::MakeValue(STRSINGLE, LOCKED));
    insert(DISH_LANGID_STRMULTIPLE, BooleanValue::MakeValue(STRMULTIPLE, LOCKED));
    insert(DISH_LANGID_Ord, OrdFunction::MakeValue());
    insert(DISH_LANGID_Ord, Ord2Function::MakeValue());
    insert(DISH_LANGID_Chr, ChrFunction::MakeValue());
    insert(DISH_LANGID_Chr, Chr2Function::MakeValue());
    
    insert(DISH_LANGID_BASE_2_DIGITS, StringValue::MakeValue(STR_BINARY_DIGITS, LOCKED));
    insert(DISH_LANGID_BASE_8_DIGITS, StringValue::MakeValue(STR_OCTAL_DIGITS, LOCKED));
    insert(DISH_LANGID_BASE_10_DIGITS, StringValue::MakeValue(STR_DECIMAL_DIGITS, LOCKED));
    insert(DISH_LANGID_BASE_16_DIGITS, StringValue::MakeValue(STR_HEXADECIMAL_DIGITS, LOCKED));
    insert(DISH_LANGID_IntegerToBaseString, IntegerToBaseStringFunction::MakeValue());
    insert(DISH_LANGID_BaseStringToInteger, BaseStringToIntegerFunction::MakeValue());
    
    insert(DISH_LANGID_ToUpperCase, ToUpperCaseFunction::MakeValue());
    insert(DISH_LANGID_ToLowerCase, ToLowerCaseFunction::MakeValue());
    
    insert(DISH_LANGID_IsUpperCase, IsUpperCaseFunction::MakeValue());
    insert(DISH_LANGID_IsLowerCase, IsLowerCaseFunction::MakeValue());
    insert(DISH_LANGID_IsControl, IsControlFunction::MakeValue());
    insert(DISH_LANGID_IsPrintable, IsPrintableFunction::MakeValue());
    insert(DISH_LANGID_IsWhitespace, IsWhitespaceFunction::MakeValue());
    insert(DISH_LANGID_IsPunctuation, IsPunctuationFunction::MakeValue());
    insert(DISH_LANGID_IsLetter, IsLetterFunction::MakeValue());
    insert(DISH_LANGID_IsDigit, IsDigitFunction::MakeValue());
    insert(DISH_LANGID_IsHexDigit, IsHexDigitFunction::MakeValue());
    
    insert(DISH_LANGID_LeftJustify, LeftJustifyFunction::MakeValue());
    insert(DISH_LANGID_RightJustify, RightJustifyFunction::MakeValue());
    insert(DISH_LANGID_CenterJustify, CenterJustifyFunction::MakeValue());
    
    insert(DISH_LANGID_StrLeft, LeftStringFunction::MakeValue());
    insert(DISH_LANGID_StrRight, RightStringFunction::MakeValue());
    insert(DISH_LANGID_StrMiddle, MiddleStringFunction::MakeValue());
    
    insert(DISH_LANGID_StrBeginsWith, StringBeginsWith2Function::MakeValue());
    insert(DISH_LANGID_StrBeginsWith, StringBeginsWith3Function::MakeValue());
    insert(DISH_LANGID_StrEndsWith, StringEndsWith2Function::MakeValue());
    insert(DISH_LANGID_StrEndsWith, StringEndsWith3Function::MakeValue());
    
    insert(DISH_LANGID_StrFind, StringFindFunction::MakeValue());
    insert(DISH_LANGID_StrFindNextOf, StringFindNextOfFunction::MakeValue());
    insert(DISH_LANGID_StrFindNextNotOf, StringFindNextNotOfFunction::MakeValue());
    insert(DISH_LANGID_StrFindLastOf, StringFindLastOfFunction::MakeValue());
    insert(DISH_LANGID_StrFindLastNotOf, StringFindLastNotOfFunction::MakeValue());
    
    insert(DISH_LANGID_StrTrimLeading, StringTrimLeadingFunction::MakeValue());
    insert(DISH_LANGID_StrTrimTrailing, StringTrimTrailingFunction::MakeValue());
    insert(DISH_LANGID_StrRemoveAllOf, StringRemoveAllOfFunction::MakeValue());
    insert(DISH_LANGID_StrRemoveAllNotOf, StringRemoveAllNotOfFunction::MakeValue());
    
    insert(DISH_LANGID_StrReplaceAll, StringReplaceAllFunction::MakeValue());
    insert(DISH_LANGID_StrReplaceAll, StringReplaceAllWithPosFunction::MakeValue());
    insert(DISH_LANGID_StrReplaceFirst, StringReplaceFirstFunction::MakeValue());
    insert(DISH_LANGID_StrReplaceFirst, StringReplaceFirstWithPosFunction::MakeValue());
    
    insert(DISH_LANGID_StrReplicate, StringReplicateFunction::MakeValue());
    
    insert(DISH_LANGID_StrReverse, StringReverseFunction::MakeValue());
    
#else

    insert(DISH_LANGID_IS_LIB_STRING, BooleanValue::MakeLockedValue(false));
    
#endif
    
    ///////////////
    
#ifdef LANG_LIB_DATETIME

    insert(DISH_LANGID_IS_LIB_DATETIME, BooleanValue::MakeLockedValue(true));
    
    ///////////////

    insert(DISH_LANGID_DateTimeT, CreateDateTimeStructureType());

    insert(DISH_LANGID_DaysOfTheWeek, CreateDaysOfTheWeekArray());
    insert(DISH_LANGID_Sunday, CreateLockedInteger(1));
    insert(DISH_LANGID_Monday, CreateLockedInteger(2));
    insert(DISH_LANGID_Tuesday, CreateLockedInteger(3));
    insert(DISH_LANGID_Wednesday, CreateLockedInteger(4));
    insert(DISH_LANGID_Thursday, CreateLockedInteger(5));
    insert(DISH_LANGID_Friday, CreateLockedInteger(6));
    insert(DISH_LANGID_Saturday, CreateLockedInteger(7));

    insert(DISH_LANGID_MonthsOfTheYear, CreateMonthsOfTheYearArray());
    insert(DISH_LANGID_January, CreateLockedInteger(1));
    insert(DISH_LANGID_February, CreateLockedInteger(2));
    insert(DISH_LANGID_March, CreateLockedInteger(3));
    insert(DISH_LANGID_April, CreateLockedInteger(4));
    insert(DISH_LANGID_May, CreateLockedInteger(5));
    insert(DISH_LANGID_June, CreateLockedInteger(6));
    insert(DISH_LANGID_July, CreateLockedInteger(7));
    insert(DISH_LANGID_August, CreateLockedInteger(8));
    insert(DISH_LANGID_September, CreateLockedInteger(9));
    insert(DISH_LANGID_October, CreateLockedInteger(10));
    insert(DISH_LANGID_November, CreateLockedInteger(11));
    insert(DISH_LANGID_December, CreateLockedInteger(12));

    insert(DISH_LANGID_DateTime, DateTimeFunction::MakeValue());
    insert(DISH_LANGID_DecomposeDateTimeValue, DecomposeDateTimeValueFunction::MakeValue());
    insert(DISH_LANGID_DecomposeUtcDateTimeValue, DecomposeUtcDateTimeValueFunction::MakeValue());
    insert(DISH_LANGID_ComposeDateTimeValue, ComposeDateTimeValueFunction::MakeValue());
    
    insert(DISH_LANGID_TimeZoneT, TimeZoneInfoFunction::MakeValue());
    insert(DISH_LANGID_TimeZoneInfo, TimeZoneInfoFunction::MakeValue());
    insert(DISH_LANGID_TimeZoneInfo, TimeZoneInfo1Function::MakeValue());
    
    insert(DISH_LANGID_Now, NowFunction::MakeValue());
    insert(DISH_LANGID_ElapsedSeconds, ElapsedSecondsFunction::MakeValue());
    
#else

    insert(DISH_LANGID_IS_LIB_DATETIME, BooleanValue::MakeLockedValue(false));
    
#endif
    
    ///////////////
    
#ifdef LANG_LIB_MATH_CORE

    insert(DISH_LANGID_IS_LIB_MATH_CORE, BooleanValue::MakeLockedValue(true));
    
    ///////////////

    insert(DISH_LANGID_IsFiniteNumberFunction, IsFiniteNumberFunction::MakeValue());
    insert(DISH_LANGID_IsInfiniteNumberFunction, IsInfiniteNumberFunction::MakeValue());
    insert(DISH_LANGID_IsNotANumberFunction, IsNotANumberFunction::MakeValue());
    insert(DISH_LANGID_IsNormalNumberFunction, IsNormalNumberFunction::MakeValue());
    
    insert(DISH_LANGID_IsOddFunction, IsOddFunction::MakeValue());
    insert(DISH_LANGID_IsEvenFunction, IsEvenFunction::MakeValue());
    
    insert(DISH_LANGID_AbsFunction, AbsFunction::MakeValue());
    insert(DISH_LANGID_WholeFunction, WholeFunction::MakeValue());
    insert(DISH_LANGID_FractionFunction, FractionFunction::MakeValue());
    insert(DISH_LANGID_SignOfFunction, SignOfFunction::MakeValue());
    
    insert(DISH_LANGID_SqrFunction, SqrFunction::MakeValue());
    insert(DISH_LANGID_SqrtFunction, SqrtFunction::MakeValue());
    insert(DISH_LANGID_CubeFunction, CubeFunction::MakeValue());
    insert(DISH_LANGID_CbrtFunction, CbrtFunction::MakeValue());
    
    insert(DISH_LANGID_LnFunction, LnFunction::MakeValue());
    insert(DISH_LANGID_LogFunction, LogFunction::MakeValue());
    insert(DISH_LANGID_LogFunction, Log2Function::MakeValue());
    insert(DISH_LANGID_ExpFunction, ExpFunction::MakeValue());
    
    insert(DISH_LANGID_RoundFunction, RoundFunction::MakeValue());
    insert(DISH_LANGID_FloorFunction, FloorFunction::MakeValue());
    insert(DISH_LANGID_CeilFunction, CeilFunction::MakeValue());
    
#else

    insert(DISH_LANGID_IS_LIB_MATH_CORE, BooleanValue::MakeLockedValue(false));
    
#endif
    
    ///////////////
    
#ifdef LANG_LIB_MATH_TRIG

    insert(DISH_LANGID_IS_LIB_MATH_TRIG, BooleanValue::MakeLockedValue(true));
    
    ///////////////

    insert(DISH_LANGID_PI, RealValue::MakeValue(PI, LOCKED));
    
    insert(DISH_LANGID_DegToRadFunction, DegToRadFunction::MakeValue());
    insert(DISH_LANGID_RadToDegFunction, RadToDegFunction::MakeValue());
    
    insert(DISH_LANGID_SinFunction, SinFunction::MakeValue());
    insert(DISH_LANGID_CosFunction, CosFunction::MakeValue());
    insert(DISH_LANGID_TanFunction, TanFunction::MakeValue());
    
    insert(DISH_LANGID_ArcSinFunction, ArcSinFunction::MakeValue());
    insert(DISH_LANGID_ArcCosFunction, ArcCosFunction::MakeValue());
    insert(DISH_LANGID_ArcTanFunction, ArcTanFunction::MakeValue());
    
    insert(DISH_LANGID_CotFunction, CotFunction::MakeValue());
    insert(DISH_LANGID_SecFunction, SecFunction::MakeValue());
    insert(DISH_LANGID_CscFunction, CscFunction::MakeValue());
    
    insert(DISH_LANGID_ArcCotFunction, ArcCotFunction::MakeValue());
    insert(DISH_LANGID_ArcSecFunction, ArcSecFunction::MakeValue());
    insert(DISH_LANGID_ArcCscFunction, ArcCscFunction::MakeValue());
    
#else

    insert(DISH_LANGID_IS_LIB_MATH_TRIG, BooleanValue::MakeLockedValue(false));
    
#endif
    
    ///////////////
    
#ifdef LANG_LIB_MATH_HYPERBOLIC

    insert(DISH_LANGID_IS_LIB_MATH_HYPERBOLIC, BooleanValue::MakeLockedValue(true));
    
    insert(DISH_LANGID_SinhFunction, SinhFunction::MakeValue());
    insert(DISH_LANGID_CoshFunction, CoshFunction::MakeValue());
    insert(DISH_LANGID_TanhFunction, TanhFunction::MakeValue());
    
    insert(DISH_LANGID_ArcSinhFunction, ArcSinhFunction::MakeValue());
    insert(DISH_LANGID_ArcCoshFunction, ArcCoshFunction::MakeValue());
    insert(DISH_LANGID_ArcTanhFunction, ArcTanhFunction::MakeValue());
    
    insert(DISH_LANGID_SechFunction, SechFunction::MakeValue());
    insert(DISH_LANGID_CschFunction, CschFunction::MakeValue());
    insert(DISH_LANGID_CothFunction, CothFunction::MakeValue());
    
    insert(DISH_LANGID_ArcSechFunction, ArcSechFunction::MakeValue());
    insert(DISH_LANGID_ArcCschFunction, ArcCschFunction::MakeValue());
    insert(DISH_LANGID_ArcCothFunction, ArcCothFunction::MakeValue());
    
#else

    insert(DISH_LANGID_IS_LIB_MATH_HYPERBOLIC, BooleanValue::MakeLockedValue(false));
    
#endif
    
    ///////////////
    
#ifdef LANG_LIB_MATH_COMPLEX

    insert(DISH_LANGID_IS_LIB_MATH_COMPLEX, BooleanValue::MakeLockedValue(true));
    
    ///////////////

    insert(DISH_LANGID_ComplexT, CreateVersionStructureType());
    
    insert(DISH_LANGID_ComplexCreateFunction, ImaginaryCreate1Function::MakeValue());
    insert(DISH_LANGID_ComplexCreateFunction, ImaginaryCreate2Function::MakeValue());
    
    insert(DISH_LANGID_ComplexToStringFunction, ImaginaryToStringFunction::MakeValue());
    
    insert(DISH_LANGID_ComplexIsEqualFunction, ImaginaryIsEqualFunction::MakeValue());
    insert(DISH_LANGID_ComplexIsNotEqualFunction, ImaginaryIsNotEqualFunction::MakeValue());
    
    insert(DISH_LANGID_ComplexAddFunction, ImaginaryAddFunction::MakeValue());
    insert(DISH_LANGID_ComplexSubtractFunction, ImaginarySubtractFunction::MakeValue());
    insert(DISH_LANGID_ComplexMultiplyFunction, ImaginaryMultiplyFunction::MakeValue());
    insert(DISH_LANGID_ComplexDivideFunction, ImaginaryDivideFunction::MakeValue());
    
    insert(DISH_LANGID_ComplexSqrFunction, ImaginarySqrFunction::MakeValue());
    insert(DISH_LANGID_ComplexSqrtFunction, ImaginarySqrtFunction::MakeValue());
    
    insert(DISH_LANGID_ComplexReciprocalFunction, ImaginaryReciprocalFunction::MakeValue());
    insert(DISH_LANGID_ComplexConjugateFunction, ImaginaryConjugateFunction::MakeValue());
    
#else

    insert(DISH_LANGID_IS_LIB_MATH_COMPLEX, BooleanValue::MakeLockedValue(false));
    
#endif
    
    ///////////////
    
#ifdef LANG_LIB_MATH_RANDOM

    insert(DISH_LANGID_IS_LIB_MATH_RANDOM, BooleanValue::MakeLockedValue(true));
    
    ///////////////

    insert(DISH_LANGID_RandomSeedFunction, RandomSeedFunction::MakeValue());
    
    insert(DISH_LANGID_RandomBooleanFunction, RandomBooleanFunction::MakeValue());
    
    insert(DISH_LANGID_RandomIntegerFunction, RandomIntegerFunction::MakeValue());
    insert(DISH_LANGID_RandomIntegerFunction, RandomInteger1Function::MakeValue());
    insert(DISH_LANGID_RandomIntegerFunction, RandomInteger2Function::MakeValue());
    
    insert(DISH_LANGID_RandomRealFunction, RandomRealFunction::MakeValue());
    insert(DISH_LANGID_RandomRealFunction, RandomReal1Function::MakeValue());
    insert(DISH_LANGID_RandomRealFunction, RandomReal2Function::MakeValue());
    
    insert(DISH_LANGID_RandomMaxFunction, RandomMaxFunction::MakeValue());
    
    insert(DISH_LANGID_RandomBitIntegerFunction, RandomBitIntegerFunction::MakeValue());
    
#else

    insert(DISH_LANGID_IS_LIB_MATH_RANDOM, BooleanValue::MakeLockedValue(false));
    
#endif
    
    ///////////////
    
#ifdef LANG_LIB_MATH_MATRIX

    insert(DISH_LANGID_IS_LIB_MATH_MATRIX, BooleanValue::MakeLockedValue(true));
    
    ///////////////

    insert(DISH_LANGID_CreateMatrixTFunction, CreateMatrixTFunction::MakeValue());
    insert(DISH_LANGID_CreateMatrixFunction, CreateMatrixFunction::MakeValue());
    insert(DISH_LANGID_MatrixValidateFunction, MatrixValidateFunction::MakeValue());
    insert(DISH_LANGID_MatrixNumRowsFunction, MatrixNumRowsFunction::MakeValue());
    insert(DISH_LANGID_MatrixNumColumnsFunction, MatrixNumColumnsFunction::MakeValue());
    insert(DISH_LANGID_MatrixIsSquareFunction, MatrixIsSquareFunction::MakeValue());
    insert(DISH_LANGID_MatrixInitializeFunction, MatrixInitialize1Function::MakeValue());
    insert(DISH_LANGID_MatrixInitializeFunction, MatrixInitialize2Function::MakeValue());
    insert(DISH_LANGID_MatrixRowSliceFunction, MatrixRowSliceFunction::MakeValue());
    insert(DISH_LANGID_MatrixColumnSliceFunction, MatrixColumnSliceFunction::MakeValue());
    insert(DISH_LANGID_MatrixTransposeFunction, MatrixTransposeFunction::MakeValue());
    insert(DISH_LANGID_MatrixDeterminantFunction, MatrixDeterminantFunction::MakeValue());
    insert(DISH_LANGID_MatrixInvertFunction, MatrixInvertFunction::MakeValue());
    insert(DISH_LANGID_MatrixAddFunction, MatrixAddFunction::MakeValue());
    insert(DISH_LANGID_MatrixSubtractFunction, MatrixSubtractFunction::MakeValue());
    insert(DISH_LANGID_MatrixMultiplyFunction, MatrixMultiplyFunction::MakeValue());
    insert(DISH_LANGID_MatrixEqualFunction, MatrixEqualFunction::MakeValue());
    insert(DISH_LANGID_MatrixAddRowFunction, MatrixAddRowFunction::MakeValue());
    insert(DISH_LANGID_MatrixAddColumnFunction, MatrixAddColumnFunction::MakeValue());
    insert(DISH_LANGID_MatrixToStringFunction, MatrixToStringFunction::MakeValue());
    
#else

    insert(DISH_LANGID_IS_LIB_MATH_MATRIX, BooleanValue::MakeLockedValue(false));
    
#endif
    
    ///////////////

#ifdef LANG_LIB_MATH_INTEGER

    insert(DISH_LANGID_IS_LIB_MATH_INTEGER, BooleanValue::MakeLockedValue(true));
    
    insert(DISH_LANGID_FactorialFunction, FactorialFunction::MakeValue());
    insert(DISH_LANGID_BinomialCoefficientFunction, BinomialCoefficientFunction::MakeValue());
    insert(DISH_LANGID_GreatestCommonDenomonatorFunction, GreatestCommonDenomonatorFunction::MakeValue());
    insert(DISH_LANGID_FibonacciFunction, FibonacciFunction::MakeValue());

#else

    insert(DISH_LANGID_IS_LIB_MATH_INTEGER, BooleanValue::MakeLockedValue(false));

#endif
    
    ///////////////
    
#ifdef LANG_LIB_TEXTIO

    insert(DISH_LANGID_IS_LIB_TEXTIO, BooleanValue::MakeLockedValue(true));
    
    ///////////////

    insert(DISH_LANGID_TEXTIO_COLOR_BLACK, CreateLockedInteger(COLOR_BLACK));
    insert(DISH_LANGID_TEXTIO_COLOR_RED, CreateLockedInteger(COLOR_RED));
    insert(DISH_LANGID_TEXTIO_COLOR_GREEN, CreateLockedInteger(COLOR_GREEN));
    insert(DISH_LANGID_TEXTIO_COLOR_YELLOW, CreateLockedInteger(COLOR_YELLOW));
    insert(DISH_LANGID_TEXTIO_COLOR_BLUE, CreateLockedInteger(COLOR_BLUE));
    insert(DISH_LANGID_TEXTIO_COLOR_MAGENTA, CreateLockedInteger(COLOR_MAGENTA));
    insert(DISH_LANGID_TEXTIO_COLOR_CYAN, CreateLockedInteger(COLOR_CYAN));
    insert(DISH_LANGID_TEXTIO_COLOR_WHITE, CreateLockedInteger(COLOR_WHITE));
    
    insert(DISH_LANGID_TEXTIO_ATTR_NORMAL, CreateLockedInteger(A_NORMAL));
    insert(DISH_LANGID_TEXTIO_ATTR_CHARTEXT, CreateLockedInteger(A_CHARTEXT));
    insert(DISH_LANGID_TEXTIO_ATTR_COLOR, CreateLockedInteger(A_COLOR));
    insert(DISH_LANGID_TEXTIO_ATTR_STANDOUT, CreateLockedInteger(A_STANDOUT));
    insert(DISH_LANGID_TEXTIO_ATTR_UNDERLINE, CreateLockedInteger(A_UNDERLINE));
    insert(DISH_LANGID_TEXTIO_ATTR_REVERSE, CreateLockedInteger(A_REVERSE));
    insert(DISH_LANGID_TEXTIO_ATTR_BLINK, CreateLockedInteger(A_BLINK));
    insert(DISH_LANGID_TEXTIO_ATTR_DIM, CreateLockedInteger(A_DIM));
    insert(DISH_LANGID_TEXTIO_ATTR_BOLD, CreateLockedInteger(A_BOLD));
    insert(DISH_LANGID_TEXTIO_ATTR_ALTCHARSET, CreateLockedInteger(A_ALTCHARSET));
    insert(DISH_LANGID_TEXTIO_ATTR_INVIS, CreateLockedInteger(A_INVIS));
    insert(DISH_LANGID_TEXTIO_ATTR_PROTECT, CreateLockedInteger(A_PROTECT));
    insert(DISH_LANGID_TEXTIO_ATTR_HORIZONTAL, CreateLockedInteger(A_HORIZONTAL));
    insert(DISH_LANGID_TEXTIO_ATTR_LEFT, CreateLockedInteger(A_LEFT));
    insert(DISH_LANGID_TEXTIO_ATTR_LOW, CreateLockedInteger(A_LOW));
    insert(DISH_LANGID_TEXTIO_ATTR_RIGHT, CreateLockedInteger(A_RIGHT));
    insert(DISH_LANGID_TEXTIO_ATTR_TOP, CreateLockedInteger(A_TOP));
    insert(DISH_LANGID_TEXTIO_ATTR_VERTICAL, CreateLockedInteger(A_VERTICAL));
    
    insert(DISH_LANGID_TEXTIO_KEY_CTRL_A, CreateLockedInteger(1));
    insert(DISH_LANGID_TEXTIO_KEY_CTRL_B, CreateLockedInteger(2));
    insert(DISH_LANGID_TEXTIO_KEY_CTRL_C, CreateLockedInteger(3));
    insert(DISH_LANGID_TEXTIO_KEY_CTRL_D, CreateLockedInteger(4));
    insert(DISH_LANGID_TEXTIO_KEY_CTRL_E, CreateLockedInteger(5));
    insert(DISH_LANGID_TEXTIO_KEY_CTRL_F, CreateLockedInteger(6));
    insert(DISH_LANGID_TEXTIO_KEY_CTRL_G, CreateLockedInteger(7));
    insert(DISH_LANGID_TEXTIO_KEY_CTRL_H, CreateLockedInteger(8));
    insert(DISH_LANGID_TEXTIO_KEY_CTRL_I, CreateLockedInteger(9));
    insert(DISH_LANGID_TEXTIO_KEY_CTRL_J, CreateLockedInteger(10));
    insert(DISH_LANGID_TEXTIO_KEY_CTRL_K, CreateLockedInteger(11));
    insert(DISH_LANGID_TEXTIO_KEY_CTRL_L, CreateLockedInteger(12));
    insert(DISH_LANGID_TEXTIO_KEY_CTRL_M, CreateLockedInteger(13));
    insert(DISH_LANGID_TEXTIO_KEY_CTRL_N, CreateLockedInteger(14));
    insert(DISH_LANGID_TEXTIO_KEY_CTRL_O, CreateLockedInteger(15));
    insert(DISH_LANGID_TEXTIO_KEY_CTRL_P, CreateLockedInteger(16));
    insert(DISH_LANGID_TEXTIO_KEY_CTRL_Q, CreateLockedInteger(17));
    insert(DISH_LANGID_TEXTIO_KEY_CTRL_R, CreateLockedInteger(18));
    insert(DISH_LANGID_TEXTIO_KEY_CTRL_S, CreateLockedInteger(19));
    insert(DISH_LANGID_TEXTIO_KEY_CTRL_T, CreateLockedInteger(20));
    insert(DISH_LANGID_TEXTIO_KEY_CTRL_U, CreateLockedInteger(21));
    insert(DISH_LANGID_TEXTIO_KEY_CTRL_V, CreateLockedInteger(22));
    insert(DISH_LANGID_TEXTIO_KEY_CTRL_W, CreateLockedInteger(23));
    insert(DISH_LANGID_TEXTIO_KEY_CTRL_X, CreateLockedInteger(24));
    insert(DISH_LANGID_TEXTIO_KEY_CTRL_Y, CreateLockedInteger(25));
    insert(DISH_LANGID_TEXTIO_KEY_CTRL_Z, CreateLockedInteger(26));
    insert(DISH_LANGID_TEXTIO_KEY_ESC, CreateLockedInteger(27));
    insert(DISH_LANGID_TEXTIO_KEY_DOWN, CreateLockedInteger(KEY_DOWN));
    insert(DISH_LANGID_TEXTIO_KEY_UP, CreateLockedInteger(KEY_UP));
    insert(DISH_LANGID_TEXTIO_KEY_LEFT, CreateLockedInteger(KEY_LEFT));
    insert(DISH_LANGID_TEXTIO_KEY_RIGHT, CreateLockedInteger(KEY_RIGHT));
    insert(DISH_LANGID_TEXTIO_KEY_HOME, CreateLockedInteger(KEY_HOME));
    insert(DISH_LANGID_TEXTIO_KEY_BACKSPACE, CreateLockedInteger(KEY_BACKSPACE));
    insert(DISH_LANGID_TEXTIO_KEY_F1, CreateLockedInteger(KEY_F(1)));
    insert(DISH_LANGID_TEXTIO_KEY_F2, CreateLockedInteger(KEY_F(2)));
    insert(DISH_LANGID_TEXTIO_KEY_F3, CreateLockedInteger(KEY_F(3)));
    insert(DISH_LANGID_TEXTIO_KEY_F4, CreateLockedInteger(KEY_F(4)));
    insert(DISH_LANGID_TEXTIO_KEY_F5, CreateLockedInteger(KEY_F(5)));
    insert(DISH_LANGID_TEXTIO_KEY_F6, CreateLockedInteger(KEY_F(6)));
    insert(DISH_LANGID_TEXTIO_KEY_F7, CreateLockedInteger(KEY_F(7)));
    insert(DISH_LANGID_TEXTIO_KEY_F8, CreateLockedInteger(KEY_F(8)));
    insert(DISH_LANGID_TEXTIO_KEY_F9, CreateLockedInteger(KEY_F(9)));
    insert(DISH_LANGID_TEXTIO_KEY_F10, CreateLockedInteger(KEY_F(10)));
    insert(DISH_LANGID_TEXTIO_KEY_F11, CreateLockedInteger(KEY_F(11)));
    insert(DISH_LANGID_TEXTIO_KEY_F12, CreateLockedInteger(KEY_F(12)));
    insert(DISH_LANGID_TEXTIO_KEY_DELETE_LINE, CreateLockedInteger(KEY_DL));
    insert(DISH_LANGID_TEXTIO_KEY_INSERT_LINE, CreateLockedInteger(KEY_IL));
    insert(DISH_LANGID_TEXTIO_KEY_DELETE_CHAR, CreateLockedInteger(KEY_DC));
    insert(DISH_LANGID_TEXTIO_KEY_INSERT_CHAR, CreateLockedInteger(KEY_IC));
    
    insert(DISH_LANGID_TEXTIO_Start, TEXTIO_StartFunction::MakeValue());
    insert(DISH_LANGID_TEXTIO_IsStarted, TEXTIO_IsStartedFunction::MakeValue());
    insert(DISH_LANGID_TEXTIO_Refresh, TEXTIO_RefreshFunction::MakeValue());
    insert(DISH_LANGID_TEXTIO_Clear, TEXTIO_ClearFunction::MakeValue());
    insert(DISH_LANGID_TEXTIO_End, TEXTIO_EndFunction::MakeValue());
    
    insert(DISH_LANGID_TEXTIO_GetXSize, TEXTIO_GetXSizeFunction::MakeValue());
    insert(DISH_LANGID_TEXTIO_GetYSize, TEXTIO_GetYSizeFunction::MakeValue());
    insert(DISH_LANGID_TEXTIO_MoveTo, TEXTIO_MoveToFunction::MakeValue());
    
    insert(DISH_LANGID_TEXTIO_AttrNormal, TEXTIO_AttrNormalFunction::MakeValue());
    insert(DISH_LANGID_TEXTIO_AttrGet, TEXTIO_AttrGetFunction::MakeValue());
    insert(DISH_LANGID_TEXTIO_AttrSet, TEXTIO_AttrSetFunction::MakeValue());
    insert(DISH_LANGID_TEXTIO_AttrOn, TEXTIO_AttrOnFunction::MakeValue());
    insert(DISH_LANGID_TEXTIO_AttrOff, TEXTIO_AttrOffFunction::MakeValue());
    insert(DISH_LANGID_TEXTIO_SetForegroundColor, TEXTIO_SetForegroundColorFunction::MakeValue());
    insert(DISH_LANGID_TEXTIO_GetForegroundColor, TEXTIO_GetForegroundColorFunction::MakeValue());
    insert(DISH_LANGID_TEXTIO_SetBackgroundColor, TEXTIO_SetBackgroundColorFunction::MakeValue());
    insert(DISH_LANGID_TEXTIO_GetBackgroundColor, TEXTIO_GetBackgroundColorFunction::MakeValue());
    insert(DISH_LANGID_TEXTIO_SetColor, TEXTIO_SetColorFunction::MakeValue());
    
    insert(DISH_LANGID_TEXTIO_VISIBLE, BooleanValue::MakeLockedValue(true));
    insert(DISH_LANGID_TEXTIO_INVISIBLE, BooleanValue::MakeLockedValue(false));
    insert(DISH_LANGID_TEXTIO_SetCursor, TEXTIO_SetCursorFunction::MakeValue());
    
#else

    insert(DISH_LANGID_IS_LIB_TEXTIO, BooleanValue::MakeLockedValue(false));
    
#endif
    
    ///////////////
    
#ifdef LANG_LIB_NETWORK

    insert(DISH_LANGID_IS_LIB_NETWORK, BooleanValue::MakeLockedValue(true));
    
    ///////////////

    insert(DISH_LANGID_MAX_OPEN_SOCKETS, CreateLockedInteger(SocketList::MAX_OPEN_SOCKETS));
    
    insert(DISH_LANGID_NETWORK_IPV4, CreateLockedInteger(static_cast< IntegerT >(SocketList::ipv4)));
    insert(DISH_LANGID_NETWORK_IPV6, CreateLockedInteger(static_cast< IntegerT >(SocketList::ipv6)));
    
    insert(DISH_LANGID_NetworkOpenClientSocket, NetworkOpenClientSocketFunction::MakeValue());
    insert(DISH_LANGID_NetworkOpenClientSocket, NetworkOpenClientSocket2Function::MakeValue());
    insert(DISH_LANGID_NetworkOpenClientSocket, NetworkOpenClientSocket3Function::MakeValue());
    
    insert(DISH_LANGID_NetworkOpenServerSocket, NetworkOpenServerSocketFunction::MakeValue());
    
    insert(DISH_LANGID_NetworkNumOpenSockets, NetworkNumOpenSocketsFunction::MakeValue());
    insert(DISH_LANGID_NetworkNumOpenClientSockets, NetworkNumOpenClientSocketsFunction::MakeValue());
    insert(DISH_LANGID_NetworkNumOpenServerSockets, NetworkNumOpenServerSocketsFunction::MakeValue());
    
    insert(DISH_LANGID_NetworkReadSocket, NetworkReadSocketFunction::MakeValue());
    insert(DISH_LANGID_NetworkWriteSocket, NetworkWriteSocketFunction::MakeValue());
    
    insert(DISH_LANGID_NetworkCloseSocket, NetworkCloseSocketFunction::MakeValue());
    insert(DISH_LANGID_NetworkCloseSocket, NetworkCloseSocket1Function::MakeValue());
    
#else

    insert(DISH_LANGID_IS_LIB_NETWORK, BooleanValue::MakeLockedValue(false));
    
#endif
    
    ///////////////
    
#ifdef LANG_LIB_FILESYS

    insert(DISH_LANGID_IS_LIB_FILESYS, BooleanValue::MakeLockedValue(true));
    
    ///////////////
    
    insert(DISH_LANGID_FileSysFileT, CreateFileSysFileT());
    insert(DISH_LANGID_FileSysDirT, CreateFileSysDirT());
    insert(DISH_LANGID_FileInfoT, CreateFileInfoT());
    
    insert(DISH_LANGID_FILESYS_NORECURSE, BooleanValue::MakeLockedValue(false));
    insert(DISH_LANGID_FILESYS_RECURSE, BooleanValue::MakeLockedValue(true));
    
    insert(DISH_LANGID_FILESYS_FileExistsFunction, FILESYS_FileExistsFunction::MakeValue());
    insert(DISH_LANGID_FILESYS_ReadLocation, FILESYS_ReadLocationFunction::MakeValue());
    insert(DISH_LANGID_FILESYS_ReadFiles, FILESYS_ReadFilesFunction::MakeValue());
    insert(DISH_LANGID_FILESYS_ReadDirectories, FILESYS_ReadDirectoriesFunction::MakeValue());
    insert(DISH_LANGID_FILESYS_GetFileInfo, FILESYS_GetFileInfoFunction::MakeValue());
    insert(DISH_LANGID_FILESYS_PrintPathTree, FILESYS_PrintPathTree1Function::MakeValue());
    insert(DISH_LANGID_FILESYS_PrintPathTree, FILESYS_PrintPathTreeFunction::MakeValue());
    
#else

    insert(DISH_LANGID_IS_LIB_FILESYS, BooleanValue::MakeLockedValue(false));
    
#endif
    
    ///////////////
    
#ifdef LANG_LIB_DATABASE

    insert(DISH_LANGID_IS_LIB_DATABASE, BooleanValue::MakeLockedValue(true));
    
    insert(
        DISH_LANGID_IS_LIB_DATABASE_MYSQL,
        BooleanValue::MakeLockedValue(
#ifdef MYSQLDB
            true
#else
            false
#endif
        )
    );
    
    insert(
        DISH_LANGID_IS_LIB_DATABASE_POSTGRESQL,
        BooleanValue::MakeLockedValue(
#ifdef POSTGRESQLDB
            true
#else
            false
#endif
        )
    );
    
    insert(DISH_LANGID_DB_ConnectionParametersT, CreateDbConnectionParametersType());
    
    insert(DISH_LANGID_DB_TYPE_MYSQL, CreateLockedInteger(DbConnectionFactory::DB_CONNECTION_TYPE_MYSQL));
    insert(DISH_LANGID_DB_TYPE_POSTGRESQL, CreateLockedInteger(DbConnectionFactory::DB_CONNECTION_TYPE_POSTGRESQL));
    
    insert(DISH_LANGID_DB_MAX_CONNECTIONS, CreateLockedInteger(DbConnectionFactory::DB_MAX_CONNECTIONS));
    
    insert(DISH_LANGID_DB_VALIDATE, BooleanValue::MakeLockedValue(true));
    insert(DISH_LANGID_DB_NO_VALIDATE, BooleanValue::MakeLockedValue(false));
    
    insert(DISH_LANGID_DB_MakeDefaultConnectionParameters, DbMakeDefaultConnectionParametersFunction::MakeValue());
    insert(DISH_LANGID_DB_MakeDefaultConnectionParameters, DbMakeDefaultConnectionParameters2Function::MakeValue());
    
    insert(DISH_LANGID_DB_OpenConnection, DbOpenConnectionFunction::MakeValue());
    insert(DISH_LANGID_DB_CloseConnection, DbCloseConnectionFunction::MakeValue());
    insert(DISH_LANGID_DB_CloseAllConnections, DbCloseAllConnectionsFunction::MakeValue());
    
    insert(DISH_LANGID_DB_IsOpen, DbNumOpenConnectionsFunction::MakeValue());
    insert(DISH_LANGID_DB_NumOpenConnections, DbNumOpenConnectionsFunction::MakeValue());
    insert(DISH_LANGID_DB_NumOpenConnections, DbNumOpenConnections1Function::MakeValue());
    
    insert(DISH_LANGID_DB_ServerVersion, DbServerVersionFunction::MakeValue());
    
    insert(DISH_LANGID_DB_IssueQuery, DbIssueQueryFunction::MakeValue());
    
#else

    insert(DISH_LANGID_IS_LIB_DATABASE, BooleanValue::MakeLockedValue(false));
    
    insert(DISH_LANGID_IS_LIB_DATABASE_MYSQL, BooleanValue::MakeLockedValue(false));
    insert(DISH_LANGID_IS_LIB_DATABASE_POSTGRESQL, BooleanValue::MakeLockedValue(false));
    
#endif
    
    ///////////////
    
#ifdef LANG_LIB_REGULAR_EXPRESSION

    insert(DISH_LANGID_IS_LIB_IS_REGEX, BooleanValue::MakeLockedValue(true));
    
    insert(DISH_LANGID_REGEX_MAX_REGEX, CreateLockedInteger(REGEX_MAX_NUM_HANDLES));
    
    insert(DISH_LANGID_REGEX_CreateFunction, CreateRegularExpressionFunction::MakeValue());
    insert(DISH_LANGID_REGEX_NumCreatedFunction, NumCreatedRegularExpressionFunction::MakeValue());
    insert(DISH_LANGID_REGEX_IsCreatedFunction, IsCreatedRegularExpressionFunction::MakeValue());
    insert(DISH_LANGID_REGEX_DestroyFunction, DestroyRegularExpressionFunction::MakeValue());
    insert(DISH_LANGID_REGEX_DestroyAllFunction, DestroyAllRegularExpressionFunction::MakeValue());
    
    insert(DISH_LANGID_REGEX_MatchFunction, MatchRegularExpressionFunction::MakeValue());
    insert(DISH_LANGID_REGEX_ReplaceNextFunction, ReplaceNextRegularExpressionFunction::MakeValue());
    insert(DISH_LANGID_REGEX_ReplaceAllFunction, ReplaceAllRegularExpressionFunction::MakeValue());
    
#else

    insert(DISH_LANGID_IS_LIB_IS_REGEX, BooleanValue::MakeLockedValue(false));

#endif
    
    ///////////////
    
#ifdef LANG_LIB_RS232

    insert(DISH_LANGID_IS_LIB_RS232, BooleanValue::MakeLockedValue(true));
    
    insert(DISH_LANGID_RS232_MAX_OPEN, CreateLockedInteger(RS232_MAX_NUM_HANDLES));
    
    ////
    
    insert(
        DISH_LANGID_RS232_BAUD_50, 
        CreateLockedInteger(
    #ifdef RS232_BAUDRATE_50_SUPPORTED
            static_cast< IntegerT >(RS232_BAUD_RATE_50)
    #else
            static_cast< IntegerT >(RS232_BAUD_RATE_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_BAUD_75, 
        CreateLockedInteger(
    #ifdef RS232_BAUDRATE_75_SUPPORTED
            static_cast< IntegerT >(RS232_BAUD_RATE_75)
    #else
            static_cast< IntegerT >(RS232_BAUD_RATE_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_BAUD_110, 
        CreateLockedInteger(
    #ifdef RS232_BAUDRATE_110_SUPPORTED
            static_cast< IntegerT >(RS232_BAUD_RATE_110)
    #else
            static_cast< IntegerT >(RS232_BAUD_RATE_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_BAUD_134, 
        CreateLockedInteger(
    #ifdef RS232_BAUDRATE_134_SUPPORTED
            static_cast< IntegerT >(RS232_BAUD_RATE_134)
    #else
            static_cast< IntegerT >(RS232_BAUD_RATE_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_BAUD_150, 
        CreateLockedInteger(
    #ifdef RS232_BAUDRATE_150_SUPPORTED
            static_cast< IntegerT >(RS232_BAUD_RATE_150)
    #else
            static_cast< IntegerT >(RS232_BAUD_RATE_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_BAUD_200, 
        CreateLockedInteger(
    #ifdef RS232_BAUDRATE_200_SUPPORTED
            static_cast< IntegerT >(RS232_BAUD_RATE_200)
    #else
            static_cast< IntegerT >(RS232_BAUD_RATE_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_BAUD_300, 
        CreateLockedInteger(
    #ifdef RS232_BAUDRATE_300_SUPPORTED
            static_cast< IntegerT >(RS232_BAUD_RATE_300)
    #else
            static_cast< IntegerT >(RS232_BAUD_RATE_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_BAUD_600, 
        CreateLockedInteger(
    #ifdef RS232_BAUDRATE_600_SUPPORTED
            static_cast< IntegerT >(RS232_BAUD_RATE_600)
    #else
            static_cast< IntegerT >(RS232_BAUD_RATE_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_BAUD_1200, 
        CreateLockedInteger(
    #ifdef RS232_BAUDRATE_1200_SUPPORTED
            static_cast< IntegerT >(RS232_BAUD_RATE_1200)
    #else
            static_cast< IntegerT >(RS232_BAUD_RATE_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_BAUD_1800, 
        CreateLockedInteger(
    #ifdef RS232_BAUDRATE_1800_SUPPORTED
            static_cast< IntegerT >(RS232_BAUD_RATE_1800)
    #else
            static_cast< IntegerT >(RS232_BAUD_RATE_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_BAUD_2400, 
        CreateLockedInteger(
    #ifdef RS232_BAUDRATE_2400_SUPPORTED
            static_cast< IntegerT >(RS232_BAUD_RATE_2400)
    #else
            static_cast< IntegerT >(RS232_BAUD_RATE_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_BAUD_9600, 
        CreateLockedInteger(
    #ifdef RS232_BAUDRATE_9600_SUPPORTED
            static_cast< IntegerT >(RS232_BAUD_RATE_9600)
    #else
            static_cast< IntegerT >(RS232_BAUD_RATE_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_BAUD_19200, 
        CreateLockedInteger(
    #ifdef RS232_BAUDRATE_19200_SUPPORTED
            static_cast< IntegerT >(RS232_BAUD_RATE_19200)
    #else
            static_cast< IntegerT >(RS232_BAUD_RATE_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_BAUD_38400, 
        CreateLockedInteger(
    #ifdef RS232_BAUDRATE_38400_SUPPORTED
            static_cast< IntegerT >(RS232_BAUD_RATE_38400)
    #else
            static_cast< IntegerT >(RS232_BAUD_RATE_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_BAUD_57600, 
        CreateLockedInteger(
    #ifdef RS232_BAUDRATE_57600_SUPPORTED
            static_cast< IntegerT >(RS232_BAUD_RATE_57600)
    #else
            static_cast< IntegerT >(RS232_BAUD_RATE_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_BAUD_115200, 
        CreateLockedInteger(
    #ifdef RS232_BAUDRATE_115200_SUPPORTED
            static_cast< IntegerT >(RS232_BAUD_RATE_115200)
    #else
            static_cast< IntegerT >(RS232_BAUD_RATE_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_BAUD_230400, 
        CreateLockedInteger(
    #ifdef RS232_BAUDRATE_230400_SUPPORTED
            static_cast< IntegerT >(RS232_BAUD_RATE_230400)
    #else
            static_cast< IntegerT >(RS232_BAUD_RATE_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_BAUD_460800, 
        CreateLockedInteger(
    #ifdef RS232_BAUDRATE_460800_SUPPORTED
            static_cast< IntegerT >(RS232_BAUD_RATE_460800)
    #else
            static_cast< IntegerT >(RS232_BAUD_RATE_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_BAUD_500000, 
        CreateLockedInteger(
    #ifdef RS232_BAUDRATE_500000_SUPPORTED
            static_cast< IntegerT >(RS232_BAUD_RATE_500000)
    #else
            static_cast< IntegerT >(RS232_BAUD_RATE_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_BAUD_576000, 
        CreateLockedInteger(
    #ifdef RS232_BAUDRATE_576000_SUPPORTED
            static_cast< IntegerT >(RS232_BAUD_RATE_576000)
    #else
            static_cast< IntegerT >(RS232_BAUD_RATE_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_BAUD_921600, 
        CreateLockedInteger(
    #ifdef RS232_BAUDRATE_921600_SUPPORTED
            static_cast< IntegerT >(RS232_BAUD_RATE_921600)
    #else
            static_cast< IntegerT >(RS232_BAUD_RATE_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_BAUD_1000000, 
        CreateLockedInteger(
    #ifdef RS232_BAUDRATE_1000000_SUPPORTED
            static_cast< IntegerT >(RS232_BAUD_RATE_1000000)
    #else
            static_cast< IntegerT >(RS232_BAUD_RATE_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_BAUD_1152000, 
        CreateLockedInteger(
    #ifdef RS232_BAUDRATE_1152000_SUPPORTED
            static_cast< IntegerT >(RS232_BAUD_RATE_1152000)
    #else
            static_cast< IntegerT >(RS232_BAUD_RATE_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_BAUD_1500000, 
        CreateLockedInteger(
    #ifdef RS232_BAUDRATE_1500000_SUPPORTED
            static_cast< IntegerT >(RS232_BAUD_RATE_1500000)
    #else
            static_cast< IntegerT >(RS232_BAUD_RATE_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_BAUD_2000000, 
        CreateLockedInteger(
    #ifdef RS232_BAUDRATE_2000000_SUPPORTED
            static_cast< IntegerT >(RS232_BAUD_RATE_2000000)
    #else
            static_cast< IntegerT >(RS232_BAUD_RATE_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_BAUD_2500000, 
        CreateLockedInteger(
    #ifdef RS232_BAUDRATE_2500000_SUPPORTED
            static_cast< IntegerT >(RS232_BAUD_RATE_2500000)
    #else
            static_cast< IntegerT >(RS232_BAUD_RATE_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_BAUD_3000000, 
        CreateLockedInteger(
    #ifdef RS232_BAUDRATE_3000000_SUPPORTED
            static_cast< IntegerT >(RS232_BAUD_RATE_3000000)
    #else
            static_cast< IntegerT >(RS232_BAUD_RATE_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_BAUD_3500000, 
        CreateLockedInteger(
    #ifdef RS232_BAUDRATE_3500000_SUPPORTED
            static_cast< IntegerT >(RS232_BAUD_RATE_3500000)
    #else
            static_cast< IntegerT >(RS232_BAUD_RATE_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_BAUD_4000000, 
        CreateLockedInteger(
    #ifdef RS232_BAUDRATE_4000000_SUPPORTED
            static_cast< IntegerT >(RS232_BAUD_RATE_4000000)
    #else
            static_cast< IntegerT >(RS232_BAUD_RATE_NULL)
    #endif
        )
    );
    
    insert(DISH_LANGID_RS232_BaudRateSupported, Rs232BaudRateSupportedFunction::MakeValue());
    
    ////
    
    insert(
        DISH_LANGID_RS232_DATA_BITS_5, 
        CreateLockedInteger(
    #ifdef RS232_DATABITS_5_SUPPORTED
            static_cast< IntegerT >(RS232_DATA_BITS_5)
    #else
            static_cast< IntegerT >(RS232_DATA_BITS_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_DATA_BITS_6, 
        CreateLockedInteger(
    #ifdef RS232_DATABITS_6_SUPPORTED
            static_cast< IntegerT >(RS232_DATA_BITS_6)
    #else
            static_cast< IntegerT >(RS232_DATA_BITS_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_DATA_BITS_7, 
        CreateLockedInteger(
    #ifdef RS232_DATABITS_7_SUPPORTED
            static_cast< IntegerT >(RS232_DATA_BITS_7)
    #else
            static_cast< IntegerT >(RS232_DATA_BITS_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_DATA_BITS_8, 
        CreateLockedInteger(
    #ifdef RS232_DATABITS_8_SUPPORTED
            static_cast< IntegerT >(RS232_DATA_BITS_8)
    #else
            static_cast< IntegerT >(RS232_DATA_BITS_NULL)
    #endif
        )
    );
    
    insert(DISH_LANGID_RS232_DataBitsSupported, Rs232DataBitsSupportedFunction::MakeValue());
    
    ////
    
    insert(
        DISH_LANGID_RS232_PARITY_NO, 
        CreateLockedInteger(
    #ifdef RS232_PARITY_NO_SUPPORTED
            static_cast< IntegerT >(RS232_PARITY_NO)
    #else
            static_cast< IntegerT >(RS232_PARITY_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_PARITY_ODD, 
        CreateLockedInteger(
    #ifdef RS232_PARITY_ODD_SUPPORTED
            static_cast< IntegerT >(RS232_PARITY_ODD)
    #else
            static_cast< IntegerT >(RS232_PARITY_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_PARITY_EVEN, 
        CreateLockedInteger(
    #ifdef RS232_PARITY_EVEN_SUPPORTED
            static_cast< IntegerT >(RS232_PARITY_EVEN)
    #else
            static_cast< IntegerT >(RS232_PARITY_NULL)
    #endif
        )
    );
    
    insert(DISH_LANGID_RS232_ParitySupported, Rs232ParitySupportedFunction::MakeValue());
    
    ////
    
    insert(
        DISH_LANGID_RS232_STOP_BITS_1, 
        CreateLockedInteger(
    #ifdef RS232_STOPBITS_1_SUPPORTED
            static_cast< IntegerT >(RS232_STOP_BITS_1)
    #else
            static_cast< IntegerT >(RS232_STOP_BITS_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_STOP_BITS_2, 
        CreateLockedInteger(
    #ifdef RS232_STOPBITS_2_SUPPORTED
            static_cast< IntegerT >(RS232_STOP_BITS_2)
    #else
            static_cast< IntegerT >(RS232_STOP_BITS_NULL)
    #endif
        )
    );
    
    insert(DISH_LANGID_RS232_StopBitsSupported, Rs232StopBitsSupportedFunction::MakeValue());
    
    ////
    
    insert(
        DISH_LANGID_RS232_FLOWCTRL_NONE, 
        CreateLockedInteger(
    #ifdef RS232_FLOWCONTROL_NONE_SUPPORTED
            static_cast< IntegerT >(RS232_FLOWCTRL_NONE)
    #else
            static_cast< IntegerT >(RS232_FLOWCTRL_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_FLOWCTRL_SOFTWARE, 
        CreateLockedInteger(
    #ifdef RS232_FLOWCONTROL_SOFTWARE_SUPPORTED
            static_cast< IntegerT >(RS232_FLOWCTRL_SOFTWARE)
    #else
            static_cast< IntegerT >(RS232_FLOWCTRL_NULL)
    #endif
        )
    );
    
    insert(
        DISH_LANGID_RS232_FLOWCTRL_HARDWARE, 
        CreateLockedInteger(
    #ifdef RS232_FLOWCONTROL_HARDWARE_SUPPORTED
            static_cast< IntegerT >(RS232_FLOWCTRL_HARDWARE)
    #else
            static_cast< IntegerT >(RS232_FLOWCTRL_NULL)
    #endif
        )
    );
    
    insert(DISH_LANGID_RS232_FlowControlSupported, Rs232FlowControlSupportedFunction::MakeValue());
    
    ////
    
    insert(DISH_LANGID_RS232_ConfigurationT, CreateRs232ConfigurationStructure());
    
    insert(DISH_LANGID_RS232_DefaultConfiguration, Rs232DefaultConfigurationFunction::MakeValue());
    
    insert(DISH_LANGID_RS232_MakeConfiguration, Rs232MakeConfiguration1Function::MakeValue());
    insert(DISH_LANGID_RS232_MakeConfiguration, Rs232MakeConfiguration4Function::MakeValue());
    insert(DISH_LANGID_RS232_MakeConfiguration, Rs232MakeConfiguration5Function::MakeValue());
    insert(DISH_LANGID_RS232_MakeConfiguration, Rs232MakeConfiguration6Function::MakeValue());
    
    insert(DISH_LANGID_RS232_Open, Rs232OpenFunction::MakeValue());
    insert(DISH_LANGID_RS232_NumOpen, Rs232NumOpenFunction::MakeValue());
    insert(DISH_LANGID_RS232_IsOpen, Rs232IsOpenFunction::MakeValue());
    insert(DISH_LANGID_RS232_Send, Rs232SendFunction::MakeValue());
    insert(DISH_LANGID_RS232_SendXON, Rs232SendXOnFunction::MakeValue());
    insert(DISH_LANGID_RS232_SendXOFF, Rs232SendXOffFunction::MakeValue());
    insert(DISH_LANGID_RS232_NumCharactersAvailable, Rs232NumCharactersAvailableFunction::MakeValue());
    insert(DISH_LANGID_RS232_Receive, Rs232ReceiveFunction::MakeValue());
    insert(DISH_LANGID_RS232_ReceiveTimeout, Rs232ReceiveTimeoutFunction::MakeValue());
    insert(DISH_LANGID_RS232_ReceiveNumCharacters, Rs232ReceiveNumCharacters2Function::MakeValue());
    insert(DISH_LANGID_RS232_ReceiveNumCharacters, Rs232ReceiveNumCharacters3Function::MakeValue());
    insert(DISH_LANGID_RS232_ReceiveSentinel, Rs232ReceiveSentinel2Function::MakeValue());
    insert(DISH_LANGID_RS232_ReceiveSentinel, Rs232ReceiveSentinel3Function::MakeValue());
    insert(DISH_LANGID_RS232_ReceiveSentinel, Rs232ReceiveSentinel4Function::MakeValue());
    insert(DISH_LANGID_RS232_Close, Rs232CloseFunction::MakeValue());
    insert(DISH_LANGID_RS232_CloseAll, Rs232CloseAllFunction::MakeValue());
    
#else

    insert(DISH_LANGID_IS_LIB_RS232, BooleanValue::MakeLockedValue(false));

#endif
    
    ///////////////

#ifdef LANG_LIB_DEBUG

    insert(DISH_LANGID_IS_LIB_DEBUG, BooleanValue::MakeLockedValue(true));
    
    insert(DISH_LANGID_DEBUG_PrintSymbolTable, DebugPrintSymbolTableFunction::MakeValue());
    insert(DISH_LANGID_DEBUG_PrintSymbolTable, DebugPrintSymbolTable1Function::MakeValue());
    
    insert(DISH_LANGID_DEBUG_PrintSymbolTableStats, DebugPrintSymbolTableStatsFunction::MakeValue());
    insert(DISH_LANGID_DEBUG_PrintSymbolTableStats, DebugPrintSymbolTableStats1Function::MakeValue());
    
    insert(DISH_LANGID_DEBUG_PrintParseTree, DebugPrintParseTreeFunction::MakeValue());
    insert(DISH_LANGID_DEBUG_PrintParseTree, DebugPrintParseTree2Function::MakeValue());
    
    insert(DISH_LANGID_DEBUG_PrintParseTreeNodeStats, DebugPrintParseTreeNodeStatsFunction::MakeValue());
    insert(DISH_LANGID_DEBUG_PrintParseTreeNodeStats, DebugPrintParseTreeNodeStats1Function::MakeValue());
    
    insert(DISH_LANGID_DEBUG_INFINITE_STACK_DEPTH, CreateLockedInteger(StackedSymbolTable::INFINITE_STACK_DEPTH));
    insert(DISH_LANGID_DEBUG_MAX_STACK_DEPTH, CreateLockedInteger(mStack.MaxDepth()));
    insert(DISH_LANGID_DEBUG_StackDepthFunction, DebugCurrentStackDepthFunction::MakeValue());
    
    insert(DISH_LANGID_DEBUG_DEFAULT_LOGFILE, StringValue::MakeValue("logfile.txt", LOCKED));
    insert(DISH_LANGID_DEBUG_Log, DebugLogFunction::MakeValue());

#else

    insert(DISH_LANGID_IS_LIB_DEBUG, BooleanValue::MakeLockedValue(false));

#endif
    
    ///////////////
    
#ifdef LANG_LIB_GRAPH

    insert(DISH_LANGID_IS_LIB_GRAPH, BooleanValue::MakeLockedValue(true));
    
    insert(DISH_LANGID_GRAPH_ContextT, GRAPH_CreateGraphicsContextType());
    insert(DISH_LANGID_GRAPH_CreateContext, GRAPH_CreateContext2Function::MakeValue());
    insert(DISH_LANGID_GRAPH_CreateContext, GRAPH_CreateContext3Function::MakeValue());
    insert(DISH_LANGID_GRAPH_CreateContext, GRAPH_CreateContext7Function::MakeValue());
    
    insert(DISH_LANGID_GRAPH_IntegerPointT, GRAPH_CreateIntegerPointType());
    insert(DISH_LANGID_GRAPH_RealPointT, GRAPH_CreateRealPointType());
    insert(DISH_LANGID_GRAPH_CreatePoint, GRAPH_CreatePointFunction::MakeValue());
    
    insert(DISH_LANGID_GRAPH_IntegerLineT, GRAPH_CreateIntegerLineType());
    insert(DISH_LANGID_GRAPH_RealLineT, GRAPH_CreateRealLineType());
    insert(DISH_LANGID_GRAPH_CreateLine, GRAPH_CreateLine2Function::MakeValue());
    insert(DISH_LANGID_GRAPH_CreateLine, GRAPH_CreateLine4Function::MakeValue());
    
    insert(DISH_LANGID_GRAPH_FILL_STYLE_SOLID, CreateLockedInteger(GRAPH_FillStyle_SOLID));
    insert(DISH_LANGID_GRAPH_FILL_STYLE_TILED, CreateLockedInteger(GRAPH_FillStyle_TILED));
    insert(DISH_LANGID_GRAPH_FILL_STYLE_OPAQUE_STIPPLED, CreateLockedInteger(GRAPH_FillStyle_OPAQUE_STIPPLED));
    insert(DISH_LANGID_GRAPH_FILL_STYLE_STIPPLED, CreateLockedInteger(GRAPH_FillStyle_STIPPLED));
    
    insert(DISH_LANGID_GRAPH_LINE_STYLE_SOLID, CreateLockedInteger(GRAPH_LineStyle_SOLID));
    insert(DISH_LANGID_GRAPH_LINE_STYLE_DASHED, CreateLockedInteger(GRAPH_LineStyle_DASHED));
    insert(DISH_LANGID_GRAPH_LINE_STYLE_DOUBLE_DASHED, CreateLockedInteger(GRAPH_LineStyle_DOUBLE_DASHED));
    
    insert(DISH_LANGID_GRAPH_LINE_CAP_NOT_LAST, CreateLockedInteger(GRAPH_LineCap_NOT_LAST));
    insert(DISH_LANGID_GRAPH_LINE_CAP_BUTT, CreateLockedInteger(GRAPH_LineCap_BUTT));
    insert(DISH_LANGID_GRAPH_LINE_CAP_ROUND, CreateLockedInteger(GRAPH_LineCap_ROUND));
    insert(DISH_LANGID_GRAPH_LINE_CAP_PROJECTING, CreateLockedInteger(GRAPH_LineCap_PROJECTING));
    
    insert(DISH_LANGID_GRAPH_LINE_JOIN_MITRE, CreateLockedInteger(GRAPH_LineJoin_MITRE));
    insert(DISH_LANGID_GRAPH_LINE_JOIN_ROUND, CreateLockedInteger(GRAPH_LineJoin_ROUND));
    insert(DISH_LANGID_GRAPH_LINE_JOIN_BEVEL, CreateLockedInteger(GRAPH_LineJoin_BEVEL));

    insert(DISH_LANGID_GRAPH_NOFILL, BooleanValue::MakeLockedValue(false));
    insert(DISH_LANGID_GRAPH_FILL, BooleanValue::MakeLockedValue(true));
        
    insert(DISH_LANGID_GRAPH_COLOR_BLACK, CreateGraphColor(0,0,0));
    insert(DISH_LANGID_GRAPH_COLOR_RED, CreateGraphColor(255,0,0));
    insert(DISH_LANGID_GRAPH_COLOR_GREEN, CreateGraphColor(0,128,0));
    insert(DISH_LANGID_GRAPH_COLOR_BLUE, CreateGraphColor(0,128,0));
    insert(DISH_LANGID_GRAPH_COLOR_LIGHT_RED, CreateGraphColor(230,211,211));
    insert(DISH_LANGID_GRAPH_COLOR_LIGHT_GREEN, CreateGraphColor(211,230,211));
    insert(DISH_LANGID_GRAPH_COLOR_LIGHT_BLUE, CreateGraphColor(211,211,230));
    insert(DISH_LANGID_GRAPH_COLOR_LIGHT_GRAY, CreateGraphColor(211,211,211));
    insert(DISH_LANGID_GRAPH_COLOR_DARK_GRAY, CreateGraphColor(169,169,169));
    insert(DISH_LANGID_GRAPH_COLOR_ORANGE, CreateGraphColor(255,165,0));
    insert(DISH_LANGID_GRAPH_COLOR_BROWN, CreateGraphColor(165,42,42));
    insert(DISH_LANGID_GRAPH_COLOR_YELLOW, CreateGraphColor(255,255,0));
    insert(DISH_LANGID_GRAPH_COLOR_PURPLE, CreateGraphColor(128,0,128));
    insert(DISH_LANGID_GRAPH_COLOR_CYAN, CreateGraphColor(0,255,255));
    insert(DISH_LANGID_GRAPH_COLOR_VIOLET, CreateGraphColor(238,130,238));
    insert(DISH_LANGID_GRAPH_COLOR_WHITE, CreateGraphColor(255,255,255));
    
    #ifdef LANG_LIB_GRAPH_ALL_COLORS
    
        insert(DISH_LANGID_IS_LIB_GRAPH_ALL_COLORS, BooleanValue::MakeLockedValue(true));
    
        insert(DISH_LANGID_GRAPH_COLOR_MAROON, CreateGraphColor(128,0,0));
        insert(DISH_LANGID_GRAPH_COLOR_DARK_RED, CreateGraphColor(139,0,0));
        insert(DISH_LANGID_GRAPH_COLOR_FIREBRICK, CreateGraphColor(178,34,34));
        insert(DISH_LANGID_GRAPH_COLOR_CRIMSON, CreateGraphColor(220,20,60));
        insert(DISH_LANGID_GRAPH_COLOR_TOMATO, CreateGraphColor(255,99,71));
        insert(DISH_LANGID_GRAPH_COLOR_CORAL, CreateGraphColor(255,127,80));
        insert(DISH_LANGID_GRAPH_COLOR_INDIAN_RED, CreateGraphColor(205,92,92));
        insert(DISH_LANGID_GRAPH_COLOR_LIGHT_CORAL, CreateGraphColor(240,128,128));
        insert(DISH_LANGID_GRAPH_COLOR_DARK_SALMON, CreateGraphColor(233,150,122));
        insert(DISH_LANGID_GRAPH_COLOR_SALMON, CreateGraphColor(250,128,114));
        insert(DISH_LANGID_GRAPH_COLOR_LIGHT_SALMON, CreateGraphColor(255,160,122));
        insert(DISH_LANGID_GRAPH_COLOR_ORANGE_RED, CreateGraphColor(255,69,0));
        insert(DISH_LANGID_GRAPH_COLOR_DARK_ORANGE, CreateGraphColor(255,140,0));
        insert(DISH_LANGID_GRAPH_COLOR_GOLD, CreateGraphColor(255,215,0));
        insert(DISH_LANGID_GRAPH_COLOR_DARK_GOLDEN_ROD, CreateGraphColor(184,134,11));
        insert(DISH_LANGID_GRAPH_COLOR_GOLDEN_ROD, CreateGraphColor(218,165,32));
        insert(DISH_LANGID_GRAPH_COLOR_PALE_GOLDEN_ROD, CreateGraphColor(238,232,170));
        insert(DISH_LANGID_GRAPH_COLOR_DARK_KHAKI, CreateGraphColor(189,183,107));
        insert(DISH_LANGID_GRAPH_COLOR_KHAKI, CreateGraphColor(240,230,140));
        insert(DISH_LANGID_GRAPH_COLOR_OLIVE, CreateGraphColor(128,128,0));
        insert(DISH_LANGID_GRAPH_COLOR_YELLOW_GREEN, CreateGraphColor(154,205,50));
        insert(DISH_LANGID_GRAPH_COLOR_DARK_OLIVE_GREEN, CreateGraphColor(85,107,47));
        insert(DISH_LANGID_GRAPH_COLOR_OLIVE_DRAB, CreateGraphColor(107,142,35));
        insert(DISH_LANGID_GRAPH_COLOR_LAWN_GREEN, CreateGraphColor(124,252,0));
        insert(DISH_LANGID_GRAPH_COLOR_CHART_REUSE, CreateGraphColor(127,255,0));
        insert(DISH_LANGID_GRAPH_COLOR_GREEN_YELLOW, CreateGraphColor(173,255,47));
        insert(DISH_LANGID_GRAPH_COLOR_DARK_GREEN, CreateGraphColor(0,100,0));
        insert(DISH_LANGID_GRAPH_COLOR_FOREST_GREEN, CreateGraphColor(34,139,34));
        insert(DISH_LANGID_GRAPH_COLOR_LIME, CreateGraphColor(0,255,0));
        insert(DISH_LANGID_GRAPH_COLOR_LIME_GREEN, CreateGraphColor(50,205,50));
        insert(DISH_LANGID_GRAPH_COLOR_PALE_GREEN, CreateGraphColor(152,251,152));
        insert(DISH_LANGID_GRAPH_COLOR_DARK_SEA_GREEN, CreateGraphColor(143,188,143));
        insert(DISH_LANGID_GRAPH_COLOR_MEDIUM_SPRING_GREEN, CreateGraphColor(0,250,154));
        insert(DISH_LANGID_GRAPH_COLOR_SPRING_GREEN, CreateGraphColor(0,255,127));
        insert(DISH_LANGID_GRAPH_COLOR_SEA_GREEN, CreateGraphColor(46,139,87));
        insert(DISH_LANGID_GRAPH_COLOR_MEDIUM_AQUA_MARINE, CreateGraphColor(102,205,170));
        insert(DISH_LANGID_GRAPH_COLOR_MEDIUM_SEA_GREEN, CreateGraphColor(60,179,113));
        insert(DISH_LANGID_GRAPH_COLOR_LIGHT_SEA_GREEN, CreateGraphColor(32,178,170));
        insert(DISH_LANGID_GRAPH_COLOR_DARK_SLATE_GRAY, CreateGraphColor(47,79,79));
        insert(DISH_LANGID_GRAPH_COLOR_TEAL, CreateGraphColor(0,128,128));
        insert(DISH_LANGID_GRAPH_COLOR_DARK_CYAN, CreateGraphColor(0,139,139));
        insert(DISH_LANGID_GRAPH_COLOR_AQUA, CreateGraphColor(0,255,255));
        insert(DISH_LANGID_GRAPH_COLOR_LIGHT_CYAN, CreateGraphColor(224,255,255));
        insert(DISH_LANGID_GRAPH_COLOR_DARK_TURQUOISE, CreateGraphColor(0,206,209));
        insert(DISH_LANGID_GRAPH_COLOR_TURQUOISE, CreateGraphColor(64,224,208));
        insert(DISH_LANGID_GRAPH_COLOR_MEDIUM_TURQUOISE, CreateGraphColor(72,209,204));
        insert(DISH_LANGID_GRAPH_COLOR_PALE_TURQUOISE, CreateGraphColor(175,238,238));
        insert(DISH_LANGID_GRAPH_COLOR_AQUA_MARINE, CreateGraphColor(127,255,212));
        insert(DISH_LANGID_GRAPH_COLOR_POWDER_BLUE, CreateGraphColor(176,224,230));
        insert(DISH_LANGID_GRAPH_COLOR_CADET_BLUE, CreateGraphColor(95,158,160));
        insert(DISH_LANGID_GRAPH_COLOR_STEEL_BLUE, CreateGraphColor(70,130,180));
        insert(DISH_LANGID_GRAPH_COLOR_CORN_FLOWER_BLUE, CreateGraphColor(100,149,237));
        insert(DISH_LANGID_GRAPH_COLOR_DEEP_SKY_BLUE, CreateGraphColor(0,191,255));
        insert(DISH_LANGID_GRAPH_COLOR_DODGER_BLUE, CreateGraphColor(30,144,255));
        insert(DISH_LANGID_GRAPH_COLOR_SKY_BLUE, CreateGraphColor(135,206,235));
        insert(DISH_LANGID_GRAPH_COLOR_LIGHT_SKY_BLUE, CreateGraphColor(135,206,250));
        insert(DISH_LANGID_GRAPH_COLOR_MIDNIGHT_BLUE, CreateGraphColor(25,25,112));
        insert(DISH_LANGID_GRAPH_COLOR_NAVY, CreateGraphColor(0,0,128));
        insert(DISH_LANGID_GRAPH_COLOR_DARK_BLUE, CreateGraphColor(0,0,139));
        insert(DISH_LANGID_GRAPH_COLOR_MEDIUM_BLUE, CreateGraphColor(0,0,205));
        insert(DISH_LANGID_GRAPH_COLOR_ROYAL_BLUE, CreateGraphColor(65,105,225));
        insert(DISH_LANGID_GRAPH_COLOR_BLUE_VIOLET, CreateGraphColor(138,43,226));
        insert(DISH_LANGID_GRAPH_COLOR_INDIGO, CreateGraphColor(75,0,130));
        insert(DISH_LANGID_GRAPH_COLOR_DARK_SLATE_BLUE, CreateGraphColor(72,61,139));
        insert(DISH_LANGID_GRAPH_COLOR_SLATE_BLUE, CreateGraphColor(106,90,205));
        insert(DISH_LANGID_GRAPH_COLOR_MEDIUM_SLATE_BLUE, CreateGraphColor(123,104,238));
        insert(DISH_LANGID_GRAPH_COLOR_MEDIUM_PURPLE, CreateGraphColor(147,112,219));
        insert(DISH_LANGID_GRAPH_COLOR_DARK_MAGENTA, CreateGraphColor(139,0,139));
        insert(DISH_LANGID_GRAPH_COLOR_DARK_VIOLET, CreateGraphColor(148,0,211));
        insert(DISH_LANGID_GRAPH_COLOR_DARK_ORCHID, CreateGraphColor(153,50,204));
        insert(DISH_LANGID_GRAPH_COLOR_MEDIUM_ORCHID, CreateGraphColor(186,85,211));
        insert(DISH_LANGID_GRAPH_COLOR_THISTLE, CreateGraphColor(216,191,216));
        insert(DISH_LANGID_GRAPH_COLOR_PLUM, CreateGraphColor(221,160,221));
        insert(DISH_LANGID_GRAPH_COLOR_MAGENTA, CreateGraphColor(255,0,255));
        insert(DISH_LANGID_GRAPH_COLOR_ORCHID, CreateGraphColor(218,112,214));
        insert(DISH_LANGID_GRAPH_COLOR_MEDIUM_VIOLET_RED, CreateGraphColor(199,21,133));
        insert(DISH_LANGID_GRAPH_COLOR_PALE_VIOLET_RED, CreateGraphColor(219,112,147));
        insert(DISH_LANGID_GRAPH_COLOR_DEEP_PINK, CreateGraphColor(255,20,147));
        insert(DISH_LANGID_GRAPH_COLOR_HOT_PINK, CreateGraphColor(255,105,180));
        insert(DISH_LANGID_GRAPH_COLOR_LIGHT_PINK, CreateGraphColor(255,182,193));
        insert(DISH_LANGID_GRAPH_COLOR_PINK, CreateGraphColor(255,192,203));
        insert(DISH_LANGID_GRAPH_COLOR_ANTIQUE_WHITE, CreateGraphColor(250,235,215));
        insert(DISH_LANGID_GRAPH_COLOR_BEIGE, CreateGraphColor(245,245,220));
        insert(DISH_LANGID_GRAPH_COLOR_BISQUE, CreateGraphColor(255,228,196));
        insert(DISH_LANGID_GRAPH_COLOR_BLANCHED_ALMOND, CreateGraphColor(255,235,205));
        insert(DISH_LANGID_GRAPH_COLOR_WHEAT, CreateGraphColor(245,222,179));
        insert(DISH_LANGID_GRAPH_COLOR_CORN_SILK, CreateGraphColor(255,248,220));
        insert(DISH_LANGID_GRAPH_COLOR_LEMON_CHIFFON, CreateGraphColor(255,250,205));
        insert(DISH_LANGID_GRAPH_COLOR_LIGHT_GOLDEN_ROD_YELLOW, CreateGraphColor(250,250,210));
        insert(DISH_LANGID_GRAPH_COLOR_LIGHT_YELLOW, CreateGraphColor(255,255,224));
        insert(DISH_LANGID_GRAPH_COLOR_SADDLE_BROWN, CreateGraphColor(139,69,19));
        insert(DISH_LANGID_GRAPH_COLOR_SIENNA, CreateGraphColor(160,82,45));
        insert(DISH_LANGID_GRAPH_COLOR_CHOCOLATE, CreateGraphColor(210,105,30));
        insert(DISH_LANGID_GRAPH_COLOR_PERN, CreateGraphColor(205,133,63));
        insert(DISH_LANGID_GRAPH_COLOR_SANDY_BROWN, CreateGraphColor(244,164,96));
        insert(DISH_LANGID_GRAPH_COLOR_BURLY_WOOD, CreateGraphColor(222,184,135));
        insert(DISH_LANGID_GRAPH_COLOR_TAN, CreateGraphColor(210,180,140));
        insert(DISH_LANGID_GRAPH_COLOR_ROSY_BROWN, CreateGraphColor(188,143,143));
        insert(DISH_LANGID_GRAPH_COLOR_MOCCASIN, CreateGraphColor(255,228,181));
        insert(DISH_LANGID_GRAPH_COLOR_NAVAJO_WHITE, CreateGraphColor(255,222,173));
        insert(DISH_LANGID_GRAPH_COLOR_PEACH_PUFF, CreateGraphColor(255,218,185));
        insert(DISH_LANGID_GRAPH_COLOR_MISTY_ROSE, CreateGraphColor(255,228,225));
        insert(DISH_LANGID_GRAPH_COLOR_LAVENDER_BLUSH, CreateGraphColor(255,240,245));
        insert(DISH_LANGID_GRAPH_COLOR_LINEN, CreateGraphColor(250,240,230));
        insert(DISH_LANGID_GRAPH_COLOR_OLD_LACE, CreateGraphColor(253,245,230));
        insert(DISH_LANGID_GRAPH_COLOR_PAPAYA_WHIP, CreateGraphColor(255,239,213));
        insert(DISH_LANGID_GRAPH_COLOR_SEA_SHELL, CreateGraphColor(255,245,238));
        insert(DISH_LANGID_GRAPH_COLOR_MINT_CREAM, CreateGraphColor(245,255,250));
        insert(DISH_LANGID_GRAPH_COLOR_SLATE_GRAY, CreateGraphColor(112,128,144));
        insert(DISH_LANGID_GRAPH_COLOR_LIGHT_SLATE_GRAY, CreateGraphColor(119,136,153));
        insert(DISH_LANGID_GRAPH_COLOR_LIGHT_SLATE_BLUE, CreateGraphColor(176,196,222));
        insert(DISH_LANGID_GRAPH_COLOR_LAVENDER, CreateGraphColor(230,230,250));
        insert(DISH_LANGID_GRAPH_COLOR_FLORAL_WHITE, CreateGraphColor(255,250,240));
        insert(DISH_LANGID_GRAPH_COLOR_ALICE_BLUE, CreateGraphColor(240,248,255));
        insert(DISH_LANGID_GRAPH_COLOR_GHOST_WHITE, CreateGraphColor(248,248,255));
        insert(DISH_LANGID_GRAPH_COLOR_HONEYDEW, CreateGraphColor(240,255,240));
        insert(DISH_LANGID_GRAPH_COLOR_IVORY, CreateGraphColor(255,255,240));
        insert(DISH_LANGID_GRAPH_COLOR_AZURE, CreateGraphColor(240,255,255));
        insert(DISH_LANGID_GRAPH_COLOR_SNOW, CreateGraphColor(255,250,250));
        insert(DISH_LANGID_GRAPH_COLOR_DIM_GRAY, CreateGraphColor(105,105,105));
        insert(DISH_LANGID_GRAPH_COLOR_GRAY, CreateGraphColor(128,128,128));
        insert(DISH_LANGID_GRAPH_COLOR_SILVER, CreateGraphColor(192,192,192));
        insert(DISH_LANGID_GRAPH_COLOR_GAINSBORO, CreateGraphColor(220,220,220));
        insert(DISH_LANGID_GRAPH_COLOR_WHITE_SMOKE, CreateGraphColor(245,245,245));
        
    #else
    
        insert(DISH_LANGID_IS_LIB_GRAPH_ALL_COLORS, BooleanValue::MakeLockedValue(false));

    #endif
    
    insert(DISH_LANGID_GRAPH_KEY_ESC, CreateLockedInteger(GRAPH_CHAR_ESC));
    insert(DISH_LANGID_GRAPH_KEY_DOWN, CreateLockedInteger(GRAPH_CHAR_DOWN));
    insert(DISH_LANGID_GRAPH_KEY_UP, CreateLockedInteger(GRAPH_CHAR_UP));
    insert(DISH_LANGID_GRAPH_KEY_LEFT, CreateLockedInteger(GRAPH_CHAR_LEFT));
    insert(DISH_LANGID_GRAPH_KEY_RIGHT, CreateLockedInteger(GRAPH_CHAR_RIGHT));
    insert(DISH_LANGID_GRAPH_KEY_HOME, CreateLockedInteger(GRAPH_CHAR_HOME));
    insert(DISH_LANGID_GRAPH_KEY_BACKSPACE, CreateLockedInteger(GRAPH_CHAR_BACKSPACE));
    insert(DISH_LANGID_GRAPH_KEY_F1, CreateLockedInteger(GRAPH_CHAR_F1));
    insert(DISH_LANGID_GRAPH_KEY_F2, CreateLockedInteger(GRAPH_CHAR_F2));
    insert(DISH_LANGID_GRAPH_KEY_F3, CreateLockedInteger(GRAPH_CHAR_F3));
    insert(DISH_LANGID_GRAPH_KEY_F4, CreateLockedInteger(GRAPH_CHAR_F4));
    insert(DISH_LANGID_GRAPH_KEY_F5, CreateLockedInteger(GRAPH_CHAR_F5));
    insert(DISH_LANGID_GRAPH_KEY_F6, CreateLockedInteger(GRAPH_CHAR_F6));
    insert(DISH_LANGID_GRAPH_KEY_F7, CreateLockedInteger(GRAPH_CHAR_F7));
    insert(DISH_LANGID_GRAPH_KEY_F8, CreateLockedInteger(GRAPH_CHAR_F8));
    insert(DISH_LANGID_GRAPH_KEY_F9, CreateLockedInteger(GRAPH_CHAR_F9));
    insert(DISH_LANGID_GRAPH_KEY_F10, CreateLockedInteger(GRAPH_CHAR_F10));
    insert(DISH_LANGID_GRAPH_KEY_F11, CreateLockedInteger(GRAPH_CHAR_F11));
    insert(DISH_LANGID_GRAPH_KEY_F12, CreateLockedInteger(GRAPH_CHAR_F12));
    insert(DISH_LANGID_GRAPH_KEY_DELETE, CreateLockedInteger(GRAPH_CHAR_DELETE));
    insert(DISH_LANGID_GRAPH_KEY_INSERT, CreateLockedInteger(GRAPH_CHAR_INSERT));
    
    insert(DISH_LANGID_GRAPH_EVENT_IDLE, CreateLockedInteger(static_cast< IntegerT >(GraphicsCallbacks::eventNull)));
    insert(DISH_LANGID_GRAPH_EVENT_REDRAW, CreateLockedInteger(static_cast< IntegerT >(GraphicsCallbacks::eventRedraw)));
    insert(DISH_LANGID_GRAPH_EVENT_RESIZE, CreateLockedInteger(static_cast< IntegerT >(GraphicsCallbacks::eventResize)));
    insert(DISH_LANGID_GRAPH_EVENT_KEY_PRESS, CreateLockedInteger(static_cast< IntegerT >(GraphicsCallbacks::eventKeyPress)));
    insert(DISH_LANGID_GRAPH_EVENT_KEY_RELEASE, CreateLockedInteger(static_cast< IntegerT >(GraphicsCallbacks::eventKeyRelease)));
    insert(DISH_LANGID_GRAPH_EVENT_BUTTON_PRESS, CreateLockedInteger(static_cast< IntegerT >(GraphicsCallbacks::eventButtonPress)));
    insert(DISH_LANGID_GRAPH_EVENT_BUTTON_RELEASE, CreateLockedInteger(static_cast< IntegerT >(GraphicsCallbacks::eventButtonRelease)));
    
    insert(DISH_LANGID_GRAPH_BUTTON_1, CreateLockedInteger(static_cast< IntegerT >(1)));
    insert(DISH_LANGID_GRAPH_BUTTON_2, CreateLockedInteger(static_cast< IntegerT >(2)));
    insert(DISH_LANGID_GRAPH_BUTTON_3, CreateLockedInteger(static_cast< IntegerT >(3)));
    insert(DISH_LANGID_GRAPH_BUTTON_4, CreateLockedInteger(static_cast< IntegerT >(4)));
    insert(DISH_LANGID_GRAPH_BUTTON_5, CreateLockedInteger(static_cast< IntegerT >(5)));
    
    insert(DISH_LANGID_GRAPH_EVENT_CONTINUE, BooleanValue::MakeLockedValue(GRAPH_EventProcessor::EVENT_CONTINUE));
    insert(DISH_LANGID_GRAPH_EVENT_TERMINATE, BooleanValue::MakeLockedValue(GRAPH_EventProcessor::EVENT_TERMINATE));
    
    insert(DISH_LANGID_GRAPH_Start, GRAPH_StartFunction::MakeValue());
    insert(DISH_LANGID_GRAPH_IsStarted, GRAPH_IsStartedFunction::MakeValue());
    insert(DISH_LANGID_GRAPH_End, GRAPH_EndFunction::MakeValue());
    
    insert(DISH_LANGID_GRAPH_IdleEventT, GRAPH_CreateIdleEventInfoT());
    insert(DISH_LANGID_GRAPH_RedrawEventT, GRAPH_CreateRedrawEventInfoT());
    insert(DISH_LANGID_GRAPH_ResizeEventT, GRAPH_CreateResizeEventInfoT());
    insert(DISH_LANGID_GRAPH_KeyPressEventT, GRAPH_CreateKeyEventInfoT());
    insert(DISH_LANGID_GRAPH_KeyReleaseEventT, GRAPH_CreateKeyEventInfoT());
    insert(DISH_LANGID_GRAPH_ButtonPressEventT, GRAPH_CreateButtonEventInfoT());
    insert(DISH_LANGID_GRAPH_ButtonReleaseEventT, GRAPH_CreateButtonEventInfoT());
    
    insert(DISH_LANGID_GRAPH_ProcessEvent, GRAPH_ProcessEventFunction::MakeValue());
    insert(DISH_LANGID_GRAPH_ProcessEvent, GRAPH_ProcessEvent1Function::MakeValue());
    
    insert(DISH_LANGID_GRAPH_EventLoop, GRAPH_EventLoopFunction::MakeValue());
    insert(DISH_LANGID_GRAPH_EventLoop, GRAPH_EventLoop1Function::MakeValue());
    
    insert(DISH_LANGID_GRAPH_PushEventProcessor, GRAPH_PushEventProcessorFunction::MakeValue());
    insert(DISH_LANGID_GRAPH_PopEventProcessor, GRAPH_PopEventProcessorFunction::MakeValue());
    
    insert(DISH_LANGID_GRAPH_Refresh, GRAPH_RefreshFunction::MakeValue());
    
    insert(DISH_LANGID_GRAPH_ApplyContext, GRAPH_ApplyContextFunction::MakeValue());
    
    insert(DISH_LANGID_GRAPH_MakeColor, GRAPH_MakeColorFunction::MakeValue());
    
    insert(DISH_LANGID_GRAPH_Clear, GRAPH_Clear1Function::MakeValue());
    insert(DISH_LANGID_GRAPH_Clear, GRAPH_Clear2Function::MakeValue());
    
    insert(DISH_LANGID_GRAPH_DrawPixel, GRAPH_DrawPixel2Function::MakeValue());
    insert(DISH_LANGID_GRAPH_DrawPixel, GRAPH_DrawPixel3Function::MakeValue());
    
    insert(DISH_LANGID_GRAPH_DrawLine, GRAPH_DrawLine2Function::MakeValue());
    insert(DISH_LANGID_GRAPH_DrawLine, GRAPH_DrawLine3Function::MakeValue());
    insert(DISH_LANGID_GRAPH_DrawLine, GRAPH_DrawLine5Function::MakeValue());
    
    insert(DISH_LANGID_GRAPH_DrawLines, GRAPH_DrawLinesFunction::MakeValue());
    
    insert(DISH_LANGID_GRAPH_DrawBox, GRAPH_DrawBox3Function::MakeValue());
    insert(DISH_LANGID_GRAPH_DrawBox, GRAPH_DrawBox4Function::MakeValue());
    insert(DISH_LANGID_GRAPH_DrawBox, GRAPH_DrawBox5Function::MakeValue());
    insert(DISH_LANGID_GRAPH_DrawBox, GRAPH_DrawBox6Function::MakeValue());
    
    insert(DISH_LANGID_GRAPH_DrawArc, GRAPH_DrawArc5Function::MakeValue());
    insert(DISH_LANGID_GRAPH_DrawArc, GRAPH_DrawArc6Function::MakeValue());
    insert(DISH_LANGID_GRAPH_DrawArc, GRAPH_DrawArc7Function::MakeValue());
    insert(DISH_LANGID_GRAPH_DrawArc, GRAPH_DrawArc8Function::MakeValue());
    
    insert(DISH_LANGID_GRAPH_GetFontList, GRAPH_GetFontList0Function::MakeValue());
    insert(DISH_LANGID_GRAPH_GetTextDimensions, GRAPH_GetTextDimensions3Function::MakeValue());
    insert(DISH_LANGID_GRAPH_GetTextDimensions, GRAPH_GetTextDimensions4Function::MakeValue());
    
    insert(DISH_LANGID_GRAPH_DrawText, GRAPH_DrawText2Function::MakeValue());
    insert(DISH_LANGID_GRAPH_DrawText, GRAPH_DrawText3Function::MakeValue());
    insert(DISH_LANGID_GRAPH_DrawText, GRAPH_DrawText4Function::MakeValue());
    
    insert(DISH_LANGID_GRAPH_DrawPolygon, GRAPH_DrawPolygon2Function::MakeValue());
    insert(DISH_LANGID_GRAPH_DrawPolygon, GRAPH_DrawPolygon3Function::MakeValue());
    
    insert(DISH_LANGID_GRAPH_MoveTo, GRAPH_MoveTo2Function::MakeValue());
    insert(DISH_LANGID_GRAPH_MoveTo, GRAPH_MoveTo3Function::MakeValue());
    
    insert(DISH_LANGID_GRAPH_LineTo, GRAPH_LineTo2Function::MakeValue());
    insert(DISH_LANGID_GRAPH_LineTo, GRAPH_LineTo3Function::MakeValue());
    
#else

    insert(DISH_LANGID_IS_LIB_GRAPH, BooleanValue::MakeLockedValue(false));

#endif

#ifdef LANG_LIB_ZIP

    insert(DISH_LANGID_IS_LIB_ZIP, BooleanValue::MakeLockedValue(true));
    
    insert(DISH_LANGID_Zip, Zip1Function::MakeValue());
    insert(DISH_LANGID_Zip, Zip2Function::MakeValue());
    insert(DISH_LANGID_Zip, Zip3Function::MakeValue());
    insert(DISH_LANGID_Zip, Zip4Function::MakeValue());
    insert(DISH_LANGID_Zip, Zip5Function::MakeValue());
    insert(DISH_LANGID_Zip, Zip6Function::MakeValue());
    insert(DISH_LANGID_Zip, Zip7Function::MakeValue());
    insert(DISH_LANGID_Zip, Zip8Function::MakeValue());
    insert(DISH_LANGID_Zip, Zip9Function::MakeValue());
    insert(DISH_LANGID_Zip, Zip10Function::MakeValue());
    
    insert(DISH_LANGID_ZipTogether, ZipTogether1Function::MakeValue());
    insert(DISH_LANGID_ZipTogether, ZipTogether2Function::MakeValue());
    insert(DISH_LANGID_ZipTogether, ZipTogether3Function::MakeValue());
    insert(DISH_LANGID_ZipTogether, ZipTogether4Function::MakeValue());
    insert(DISH_LANGID_ZipTogether, ZipTogether5Function::MakeValue());
    insert(DISH_LANGID_ZipTogether, ZipTogether6Function::MakeValue());
    insert(DISH_LANGID_ZipTogether, ZipTogether7Function::MakeValue());
    insert(DISH_LANGID_ZipTogether, ZipTogether8Function::MakeValue());
    insert(DISH_LANGID_ZipTogether, ZipTogether9Function::MakeValue());
    insert(DISH_LANGID_ZipTogether, ZipTogether10Function::MakeValue());
    insert(DISH_LANGID_ZipTogether, ZipTogether11Function::MakeValue());
    
    insert(DISH_LANGID_ZipValue, ZipValueFunction::MakeValue());
    
    {
        std::shared_ptr< ZipIncrement0Function > increment_by_0(ZipIncrement0Function::MakeValue());
        insert(DISH_LANGID_ZipIncrement, increment_by_0);
        insert(DISH_LANGID_ZipDecrement, increment_by_0);
        
        insert(DISH_LANGID_ZipIncrement, ZipIncrement1Function::MakeValue());
        insert(DISH_LANGID_ZipDecrement, ZipDecrement1Function::MakeValue());
    }

#else

    insert(DISH_LANGID_IS_LIB_ZIP, BooleanValue::MakeLockedValue(false));

#endif
    
    /*
        Push a symbol-table onto the stack. Which type of table is selected at
        compile-time.
    */
    mStack.Push(MakeSystemSymbolTable());
    
    ///////////////
    
    assert(!mStack.IsEmpty());
}

dish::LanguageSymbolTable::LanguageSymbolTable(const dish::LanguageSymbolTable &symtab, const dish::iSymbolTable::CloneT &type) : iSymbolTable(),
    mBase(),
    mStack(symtab.mStack.MaxDepth()),
    
    mProfile(symtab.mProfile)
{
    switch(type)
    {
        case cloneMinimal:
        {
            //  Reuse the base symbol table that holds the run-time library.
            mBase = symtab.mBase;
            
            /*
                Push a symbol-table onto the stack. Which type of table is 
                selected at compile-time. The statement is crafted in such a
                manner as to elicit a compile-time error if no, or more than
                one, selection is made.
            */
            mStack.Push(MakeSystemSymbolTable());
        } break;
        
        case cloneShallow:
        case cloneDeep:
        {
            //  Copy the base system symbol-table where the run-time library
            //  resides.
            mBase = MakeSystemSymbolTable();
            symtab.mBase->Load(*mBase, type);
            
            //  Copy the stack.
            symtab.mStack.Load(mStack, type);
        } break;
        
        default:
        {
            assert(false);
        }
        
    }
    
    assert(0 != mBase.get());
    assert(!mStack.IsEmpty());
}

std::shared_ptr< dish::iAtomic > dish::LanguageSymbolTable::LookupInBase(const std::string &key) const
{
    std::shared_ptr< iAtomic > value(mBase->Lookup(key));
    if(value)
    {
        return value;
    }
        
    std::stringstream message;
    message << "The symbol '";
    message << key;
    message << "' does not exist.";
    
    throw NoSuchSymbolException(message.str());
}

std::shared_ptr< dish::iSymbolTable > dish::LanguageSymbolTable::Clone(const dish::iSymbolTable::CloneT &type) const
{
    return std::shared_ptr< iSymbolTable >(new LanguageSymbolTable(*this, type));
}

void dish::LanguageSymbolTable::Shuffle()
{
    mBase->Shuffle();
    mStack.Shuffle();
}

void dish::LanguageSymbolTable::Push(std::shared_ptr< dish::iSymbolTable > table)
{
    assert(0 != table.get());

    mStack.Push(table);
}

void dish::LanguageSymbolTable::Push()
{
    mStack.Push();
}

void dish::LanguageSymbolTable::Pop()
{
    mStack.Pop();
}

bool dish::LanguageSymbolTable::IsEmpty() const
{
    return mStack.IsEmpty();
}

int dish::LanguageSymbolTable::Num() const
{
    return (mBase->Num() + mStack.Num());
}

bool dish::LanguageSymbolTable::Exists(const std::string &key) const
{
    if(!BeginsWith(key, '`'))
    {
        if(mStack.Exists(key))
        {
            return true;
        }
        
        return mBase->Exists(key);
    }
    
    return mBase->Exists(key.substr(1, std::string::npos));
}

void dish::LanguageSymbolTable::Insert(const std::string &key, std::shared_ptr< dish::iAtomic > value)
{
    if(!BeginsWith(key, '`'))
    {
        if(!mStack.IsEmpty())
        {
            mStack.Insert(key, value);
        }
        else
        {
            mBase->Insert(key, value);
        }
    }
    else
    {
        mBase->Insert(key.substr(1, std::string::npos), value);
    }
}

std::shared_ptr< dish::iAtomic > dish::LanguageSymbolTable::Lookup(const std::string &key) const
{
    if(!BeginsWith(key, '`'))
    {
        std::shared_ptr< iAtomic > value(mStack.Lookup(key));
        if(0 != value.get())
        {
            return value;
        }
        
        value = mBase->Lookup(key);
        if(0 != value.get())
        {
            return value;
        }
    }
    else
    {
        std::shared_ptr< iAtomic > value(mBase->Lookup(key.substr(1, std::string::npos)));
        if(0 != value.get())
        {
            return value;
        }
    }
        
    std::stringstream message;
    message << "The symbol '";
    message << key;
    message << "' does not exist.";
    
    throw NoSuchSymbolException(message.str());
}

void dish::LanguageSymbolTable::Load(dish::iSymbolTable &symtab, const dish::iSymbolTable::CloneT &type) const
{
    mBase->Load(symtab, type);
    mStack.Load(symtab, type);
}

void dish::LanguageSymbolTable::Clear()
{
    mStack.Clear();
    mBase->Clear();
}

void dish::LanguageSymbolTable::Histogram(std::ostream &out) const
{
    out << "Global Table:" << std::endl;
    out << std::endl;
    mStack.Histogram(out);
    
    out << std::endl;
    out << std::endl;
    out << std::endl;
    
    out << "System Table:" << std::endl;
    out << std::endl;
    mBase->Histogram(out);
}

void dish::LanguageSymbolTable::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << "Global Table:" << std::endl;
    out << std::endl;
    mStack.Print(out, indent + 4);
    
    out << std::endl;
    out << std::endl;
    out << std::endl;
    
    printIndent(out, indent);
    out << "System Table:" << std::endl;
    out << std::endl;
    mBase->Print(out, indent + 4);
}

