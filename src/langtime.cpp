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

#include <sys/time.h>

#include <cstdlib>
#include <ctime>

#include "langtime.h"

namespace
{

    std::shared_ptr< dish::iAtomic > CreateTimezoneStructure(const std::string &tzname, const int &tzoffset, const bool daylight)
    {
        static std::shared_ptr< dish::iAtomic > type(dish::CreateTimezoneStructureType());
        
        std::shared_ptr< dish::iAtomic > structure(type->Declare());
        structure->Member("Name")->Assign(tzname);
        structure->Member("Offset")->Assign(static_cast< dish::IntegerT >(tzoffset));
        structure->Member("DayightSavings")->Assign(static_cast< dish::BooleanT >(daylight));
        
        return structure;
    }

}

/******************************************************************************

    Function definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::CreateDateTimeStructureType()
{
    static std::shared_ptr< StructureTypeAtomic > structure;
    
    if(0 == structure.get())
    {
        std::shared_ptr< IntegerTypeAtomic > integer_type(IntegerTypeAtomic::MakeValue());
    
        structure = StructureTypeAtomic::MakeValue();
        structure->Add("Hour", integer_type);
        structure->Add("Minute", integer_type);
        structure->Add("Second", integer_type);
        structure->Add("Month", integer_type);
        structure->Add("Day", integer_type);
        structure->Add("Year", integer_type);
        structure->Add("DayOfWeek", integer_type);
    }

    return structure;
}

std::shared_ptr< dish::iAtomic > dish::CreateDaysOfTheWeekArray()
{
    std::shared_ptr< ArrayValue > array(
        ArrayValue::MakeValue(
            1, 7, StringTypeAtomic::MakeValue()
        )
    );
    
    array->Element(1)->Assign(std::string("Sunday"));
    array->Element(2)->Assign(std::string("Monday"));
    array->Element(3)->Assign(std::string("Tuesday"));
    array->Element(4)->Assign(std::string("Wednesday"));
    array->Element(5)->Assign(std::string("Thursday"));
    array->Element(6)->Assign(std::string("Friday"));
    array->Element(7)->Assign(std::string("Saturday"));
    
    array->Lock();
    
    return array;
}

std::shared_ptr< dish::iAtomic > dish::CreateMonthsOfTheYearArray()
{
    std::shared_ptr< ArrayValue > array(
        ArrayValue::MakeValue(
            1, 12, StringTypeAtomic::MakeValue()
        )
    );
    
    array->Element(1)->Assign(std::string("January"));
    array->Element(2)->Assign(std::string("February"));
    array->Element(3)->Assign(std::string("March"));
    array->Element(4)->Assign(std::string("April"));
    array->Element(5)->Assign(std::string("May"));
    array->Element(6)->Assign(std::string("June"));
    array->Element(7)->Assign(std::string("July"));
    array->Element(8)->Assign(std::string("August"));
    array->Element(9)->Assign(std::string("September"));
    array->Element(10)->Assign(std::string("October"));
    array->Element(11)->Assign(std::string("November"));
    array->Element(12)->Assign(std::string("December"));
    
    array->Lock();
    
    return array;
}
 
std::shared_ptr< dish::iAtomic > dish::CreateTimezoneStructureType()
{
    static std::shared_ptr< StructureTypeAtomic > structure;
    
    if(0 == structure.get())
    {
        structure = StructureTypeAtomic::MakeValue();
        structure->Add("Name", StringTypeAtomic::MakeValue());
        structure->Add("Offset", IntegerTypeAtomic::MakeValue());
        structure->Add("DayightSavings", BooleanTypeAtomic::MakeValue());
    }

    return structure;
}

/******************************************************************************

    dish::NowFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::NowFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    
    return IntegerValue::MakeValue(static_cast< IntegerT >(1000000 + tv.tv_usec));
}

/******************************************************************************

    dish::ElapsedSecondsFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::ElapsedSecondsFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const IntegerT start(getParam(symtab, "start")->AsInteger());
    const IntegerT finish(getParam(symtab, "finish")->AsInteger());

    return RealValue::MakeValue(
        (static_cast< long double >(finish) - static_cast< long double >(start)) / static_cast< long double >(1000000.0)
    );
}

/******************************************************************************

    dish::DateTimeFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::DateTimeFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return IntegerValue::MakeValue(static_cast< IntegerT >(std::time(NULL)));
}

/******************************************************************************

    dish::DecomposeDateTimeValueFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::DecomposeDateTimeValueFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const std::time_t encoded(static_cast< std::time_t >(getParam(symtab, "encoded")->AsInteger()));
    
    struct std::tm value = { 0 };
    localtime_r(&encoded, &value);
    
    static std::shared_ptr< iAtomic > decoded(CreateDateTimeStructureType()->Declare());
    decoded->Member("Hour")->Assign(static_cast< IntegerT >(value.tm_hour));
    decoded->Member("Minute")->Assign(static_cast< IntegerT >(value.tm_min));
    decoded->Member("Second")->Assign(static_cast< IntegerT >(value.tm_sec));
    decoded->Member("Month")->Assign(static_cast< IntegerT >(value.tm_mon) + 1);
    decoded->Member("Day")->Assign(static_cast< IntegerT >(value.tm_mday));
    decoded->Member("Year")->Assign(static_cast< IntegerT >(value.tm_year) + 1900);
    decoded->Member("DayOfWeek")->Assign(static_cast< IntegerT >(value.tm_wday) + 1);

    return decoded;
}

/******************************************************************************

    dish::DecomposeUtcDateTimeValueFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::DecomposeUtcDateTimeValueFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const std::time_t encoded(static_cast< std::time_t >(getParam(symtab, "encoded")->AsInteger()));
    
    struct std::tm value = { 0 };
    gmtime_r(&encoded, &value);
    
    static std::shared_ptr< iAtomic > decoded(CreateDateTimeStructureType()->Declare());
    decoded->Member("Hour")->Assign(static_cast< IntegerT >(value.tm_hour));
    decoded->Member("Minute")->Assign(static_cast< IntegerT >(value.tm_min));
    decoded->Member("Second")->Assign(static_cast< IntegerT >(value.tm_sec));
    decoded->Member("Month")->Assign(static_cast< IntegerT >(value.tm_mon) + 1);
    decoded->Member("Day")->Assign(static_cast< IntegerT >(value.tm_mday));
    decoded->Member("Year")->Assign(static_cast< IntegerT >(value.tm_year) + 1900);
    decoded->Member("DayOfWeek")->Assign(static_cast< IntegerT >(value.tm_wday) + 1);

    return decoded;
}

/******************************************************************************

    dish::ComposeDateTimeValueFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::ComposeDateTimeValueFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > decoded(getParam(symtab, "decoded"));
    
    struct std::tm value = { 0 };
    value.tm_sec = static_cast< int >(decoded->Member("Second")->AsInteger());
    value.tm_min = static_cast< int >(decoded->Member("Minute")->AsInteger());
    value.tm_hour = static_cast< int >(decoded->Member("Hour")->AsInteger());
    value.tm_mday = static_cast< int >(decoded->Member("Day")->AsInteger());
    value.tm_mon = static_cast< int >(decoded->Member("Month")->AsInteger() - 1);
    value.tm_year = static_cast< int >(decoded->Member("Year")->AsInteger() - 1900);

    return IntegerValue::MakeValue(static_cast< IntegerT >(std::mktime(&value)));
}

/******************************************************************************

    dish::TimeZoneInfoFunction class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::TimeZoneInfoFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const std::time_t encoded(std::time(NULL));

    struct std::tm value = { 0 };
    localtime_r(&encoded, &value);
    
    return CreateTimezoneStructure(
        value.tm_zone,
        static_cast< IntegerT >(value.tm_gmtoff),
        0 != daylight
    );
}

/******************************************************************************

    dish::TimeZoneInfo1Function class definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::TimeZoneInfo1Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    const std::time_t encoded(static_cast< std::time_t >(getParam(symtab, "encoded")->AsInteger()));

    struct std::tm value = { 0 };
    localtime_r(&encoded, &value);
    
    return CreateTimezoneStructure(
        value.tm_zone,
        static_cast< IntegerT >(value.tm_gmtoff),
        0 != daylight
    );
}

