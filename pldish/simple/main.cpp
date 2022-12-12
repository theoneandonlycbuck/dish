#include <iostream>
#include <memory>

#include "pldish.h"

namespace
{

    dish::RealT Scale(2.1);

}

////////////////////////////////////////////////////////////////////////////////

class PLFunction : public dish::ExecutableCppValue
{
    public:
        PLFunction() : dish::ExecutableCppValue() { AddParam("x", dish::REFERENCE_PARAMETER); AddParam("y", dish::REFERENCE_PARAMETER); };
        
        //  From iAtomic
        
        virtual std::shared_ptr< dish::iAtomic > Execute(dish::LanguageSymbolTable &symtab) const;
    
};

std::shared_ptr< dish::iAtomic > PLFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< dish::iAtomic > x(getParam(symtab, "x"));
    std::shared_ptr< dish::iAtomic > y(getParam(symtab, "y"));
    
    return call(symtab, "Sin", x * y);
}

////////////////////////////////////////////////////////////////////////////////

class PLLanguageSymbolTable : public dish::LanguageSymbolTable
{
    public:
        PLLanguageSymbolTable();
    
};

PLLanguageSymbolTable::PLLanguageSymbolTable() : dish::LanguageSymbolTable()
{
    insert("PLFunction", std::shared_ptr< dish::iAtomic >(new PLFunction()));
    insert("Scale", dish::RealCppReferenceValue::MakeValue(Scale));
}

////////////////////////////////////////////////////////////////////////////////

int main(const int argc, const char * const * const argv)
{
    dish::Parser parser(
        std::shared_ptr< dish::LanguageSymbolTable >(new PLLanguageSymbolTable()),
        "Println('F(PI, ' + Scale + ') = ' + PLFunction(PI, Scale));",
        dish::STRING_INPUT
    );
    
    std::cout << std::endl;
    
    parser.Run();
    
    std::cout << std::endl;
    //parser.SymbolTable().Histogram(std::cout);
    //std::cout << std::endl;

    return 0;
}

