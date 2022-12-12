#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>

#include "pldish.h"

namespace
{

    typedef struct
    {
        dish::StringT Name;
        dish::IntegerT Id;
        dish::RealT Salary;
        dish::BooleanT Management;
    } EmployeeT;
    
    EmployeeT Employee;
    
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

}

////////////////////////////////////////////////////////////////////////////////

class PLLanguageSymbolTable : public dish::LanguageSymbolTable
{
    public:
        PLLanguageSymbolTable();
    
};

PLLanguageSymbolTable::PLLanguageSymbolTable() : dish::LanguageSymbolTable()
{
    EmployeeCppReferenceType employee_type;

    insert("Employee", employee_type.Declare(&Employee));
}

////////////////////////////////////////////////////////////////////////////////

int main(const int argc, const char * const * const argv)
{
    Employee.Name = "";
    Employee.Id = 0;
    Employee.Salary = 0.0;
    Employee.Management = false;

    dish::DishMachine vm(
        std::shared_ptr< dish::LanguageSymbolTable >(new PLLanguageSymbolTable())
    );
    
    vm.Parse(
        "Employee.Name = 'Harvey Dent';"
        "Employee.Id = 1629217;"
        "Employee.Salary = 123456.78;"
        "Employee.Management = true;"
        "Println('1/3 = ' + 1.0 / 3.0);",
        dish::STRING_INPUT
    );
    
    std::cout << std::endl;
    
    std::cout.precision(15);
    std::cout << 
        Employee.Name << " (" << 
        Employee.Id << "), $" << 
        Employee.Salary << " " << 
        (Employee.Management ? "Management" : "Standard") << 
        std::endl;
    
    std::cout << std::endl;
    //vm.SymbolTable().Histogram(std::cout);
    //std::cout << std::endl;

    return 0;
}

