#include <iostream>
#include <memory>
#include <vector>

#include "pldish.h"

namespace
{

    std::vector< dish::IntegerT > IntegerA;
    std::vector< dish::RealT > RealA;
    std::vector< dish::StringT > StringA;

}

////////////////////////////////////////////////////////////////////////////////

class PLLanguageSymbolTable : public dish::LanguageSymbolTable
{
    public:
        PLLanguageSymbolTable();
    
};

PLLanguageSymbolTable::PLLanguageSymbolTable() : dish::LanguageSymbolTable()
{
    insert("IntegerA", dish::IntegerVectorCppReferenceValue::MakeValue(IntegerA));
    insert("RealA", dish::RealVectorCppReferenceValue::MakeValue(RealA));
    insert("StringA", dish::StringVectorCppReferenceValue::MakeValue(StringA));
}

////////////////////////////////////////////////////////////////////////////////

int main(const int argc, const char * const * const argv)
{
    for(dish::IntegerT i(0); i < 5; ++i)
    {
        IntegerA.push_back(-1);
        RealA.push_back(-1.0);
        StringA.push_back("");
    }

    dish::DishMachine vm(
        std::shared_ptr< dish::LanguageSymbolTable >(new PLLanguageSymbolTable())
    );
    
    vm.Parse(
        "Append(IntegerA, -1);"
        "Append(IntegerA, -1);"
        "Append(IntegerA, -1);"
        "Append(IntegerA, -1);"
        "Append(IntegerA, -1);"
        ""
        "Append(RealA, -1.0);"
        "Append(RealA, -1.0);"
        "Append(RealA, -1.0);"
        "Append(RealA, -1.0);"
        "Append(RealA, -1.0);"
        ""
        "Append(StringA, '***');"
        "Append(StringA, '***');"
        "Append(StringA, '***');"
        "Append(StringA, '***');"
        "Append(StringA, '***');"
        ""
        "declare integer as i;"
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
        "Assert(IntegerA.start == RealA.start);"
        "Assert(RealA.start == StringA.start);"
        ""
        "Assert(IntegerA.finish == RealA.finish);"
        "Assert(RealA.finish == StringA.finish);"
        ""
        "Println('dish:');"
        "for i = StringA.start to StringA.finish"
        "    Println('   ' + i + '.  ' + IntegerA[i] + '\\t' + RealA[i] + '\\t' + StringA[i]);",
        dish::STRING_INPUT
    );
    
    std::cout << std::endl;
    
    std::cout << "C++:" << std::endl;
    for(int i(0); i < IntegerA.size(); ++i)
    {
        std::cout << 
            "   " <<
            i << ".  " <<
            IntegerA[i] << "\t" << 
            RealA[i] << "\t" << 
            StringA[i] << 
            std::endl;
    }
    
    //std::cout << std::endl;
    //vm.SymbolTable().Histogram(std::cout);
    std::cout << std::endl;

    return 0;
}

