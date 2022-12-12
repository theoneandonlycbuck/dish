#include <cstddef>
#include <iostream>
#include <memory>

#include "pldish.h"

namespace
{
    
    ////////////////////////////////////////////////////////////////////////////

    typedef struct
    {
        dish::StringT Name;
        dish::IntegerT Id;
        dish::RealT Salary;
        dish::BooleanT Management;
    } EmployeeT;
    
    class EmployeeCppReferenceType : public dish::StructureCppReferenceType
    {
        public:
            EmployeeCppReferenceType();
        
    };
    
    EmployeeCppReferenceType::EmployeeCppReferenceType() : dish::StructureCppReferenceType(sizeof(EmployeeT))
    { 
        AddStringMember("Name", offsetof(EmployeeT, Name));
        AddIntegerMember("Id", offsetof(EmployeeT, Id));
        AddRealMember("Salary", offsetof(EmployeeT, Salary));
        AddBooleanMember("Management", offsetof(EmployeeT, Management));
    }
    
    ////////////////////////////////////////////////////////////////////////////

    const dish::IntegerT NumElements(10);

    dish::BooleanT BooleanA[NumElements];
    dish::IntegerT IntegerA[NumElements];
    dish::RealT RealA[NumElements];
    dish::StringT StringA[NumElements];
    
    EmployeeT EmployeeA[NumElements];
    
    ////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////

class PLLanguageSymbolTable : public dish::LanguageSymbolTable
{
    public:
        PLLanguageSymbolTable();
    
};

PLLanguageSymbolTable::PLLanguageSymbolTable() : dish::LanguageSymbolTable()
{
    {
        dish::ArrayCppReferenceType type(NumElements, std::shared_ptr< dish::iCppReferenceType >(new dish::BooleanCppReferenceType()));
        insert("BooleanA", type.Declare(BooleanA));
    }
    
    {
        dish::ArrayCppReferenceType type(NumElements, std::shared_ptr< dish::iCppReferenceType >(new dish::IntegerCppReferenceType()));
        insert("IntegerA", type.Declare(IntegerA));
    }
    
    {
        dish::ArrayCppReferenceType type(NumElements, std::shared_ptr< dish::iCppReferenceType >(new dish::RealCppReferenceType()));
        insert("RealA", type.Declare(RealA));
    }
    
    {
        dish::ArrayCppReferenceType type(NumElements, std::shared_ptr< dish::iCppReferenceType >(new dish::StringCppReferenceType()));
        insert("StringA", type.Declare(StringA));
    }
    
    {
        dish::ArrayCppReferenceType type(NumElements, std::shared_ptr< dish::iCppReferenceType >(new EmployeeCppReferenceType()));
        insert("EmployeeA", type.Declare(EmployeeA));
    }
}

////////////////////////////////////////////////////////////////////////////////

int main(const int argc, const char * const * const argv)
{
    for(dish::IntegerT i(0); i < NumElements; ++i)
    {
        BooleanA[i] = false;
        IntegerA[i] = -1;
        RealA[i] = -1.0;
        StringA[i] = "";
    }

    dish::DishMachine vm(
        std::shared_ptr< dish::LanguageSymbolTable >(new PLLanguageSymbolTable())
    );
    
    vm.Parse(
        "declare integer as i;"
        ""
        "for i = BooleanA.start to BooleanA.finish"
        "    BooleanA[i] = true;"
        ""
        "for i = IntegerA.start to IntegerA.finish"
        "    IntegerA[i] = i;"
        ""
        "for i = RealA.start to RealA.finish"
        "    RealA[i] = i;"
        ""
        "for i = StringA.start to StringA.finish"
        "    StringA[i] = 'text' + i;"
        ""
        "for i = EmployeeA.start to EmployeeA.finish"
        "    begin"
        "        EmployeeA[i].Name = 'Harvey Dent';"
        "        EmployeeA[i].Id = 1629217;"
        "        EmployeeA[i].Salary = 123456.78;"
        "        EmployeeA[i].Management = true;"
        "    end;"
        ""
        "Assert(BooleanA.start == IntegerA.start);"
        "Assert(IntegerA.start == RealA.start);"
        "Assert(RealA.start == StringA.start);"
        "Assert(StringA.start == EmployeeA.start);"
        ""
        "Assert(BooleanA.finish == IntegerA.finish);"
        "Assert(IntegerA.finish == RealA.finish);"
        "Assert(RealA.finish == StringA.finish);"
        "Assert(StringA.finish == EmployeeA.finish);"
        ""
        "Println('dish:');"
        "for i = StringA.start to StringA.finish"
        "    Println('   ' + i + '.  ' + BooleanA[i] + '\\t' + IntegerA[i] + '\\t' + RealA[i] + '\\t' + StringA[i]);"
        ""
        "Newln();"
        ""
        "for i = StringA.start to StringA.finish"
        "    Println('   ' + i + '.  ' + EmployeeA[i].Name + ' (' + EmployeeA[i].Id + '), $' + EmployeeA[i].Salary + ', Mgmt: ' + EmployeeA[i].Management);"
        "",
        dish::STRING_INPUT
    );
    
    std::cout << std::endl;
    
    std::cout << "C++:" << std::endl;
    for(int i(0); i < NumElements; ++i)
    {
        std::cout << 
            "   " <<
            i << ".  " << 
            (BooleanA[i] ? "true" : "false") << "\t" << 
            IntegerA[i] << "\t" << 
            RealA[i] << "\t" << 
            StringA[i] << 
            std::endl;
    }
    
    std::cout << std::endl;
    
    std::cout.precision(15);
    for(int i(0); i < NumElements; ++i)
    {
        std::cout << 
            "   " <<
            i << ".  " << 
            EmployeeA[i].Name << " (" << 
            EmployeeA[i].Id << "), $" << 
            EmployeeA[i].Salary << " " << 
            (EmployeeA[i].Management ? "Management" : "Standard") << 
            std::endl;
    }
    
    std::cout << std::endl;
    //vm.SymbolTable().Histogram(std::cout);
    //std::cout << std::endl;

    return 0;
}

