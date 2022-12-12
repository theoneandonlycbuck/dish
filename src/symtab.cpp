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

#include <stdint.h>

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <sstream>

#include "atomics.h"
#include "exception.h"
#include "symtab.h"
#include "utility.h"

////////////////////////////////////////////////////////////////////////////////


#if not defined(SYMTAB_HASH_FUNC_WHOLE_ID) and not defined(SYMTAB_HASH_FUNC_PARTIAL_ID) and not defined(SYMTAB_HASH_FUNC_MULTI_BYTE) and not defined(SYMTAB_HASH_FUNC_HASHED_WHOLE_ID) and not defined(SYMTAB_HASH_FUNC_HASHED_PARTIAL_ID)
#warning One of SYMTAB_HASH_FUNC_WHOLE_ID, SYMTAB_HASH_FUNC_PARTIAL_ID, SYMTAB_HASH_FUNC_HASHED_WHOLE_ID, SYMTAB_HASH_FUNC_HASHED_PARTIAL_ID, or SYMTAB_HASH_FUNC_MULTI_BYTE should be defined to determine the behavior of the hash-function in the hashed-table.
#endif


////////////////////////////////////////////////////////////////////////////////

namespace
{

    const int TBL_HEIGHT(74);

}

/******************************************************************************

    dish::SymbolTable class definitions

 ******************************************************************************/
 
void dish::SymbolTable::Push(std::shared_ptr< dish::iSymbolTable > table)
{
    throw IllegalOperationException("dish::SymbolTable::Push(table)");
}

void dish::SymbolTable::Push()
{
    throw IllegalOperationException("dish::SymbolTable::Push()");
}

void dish::SymbolTable::Pop()
{
    throw IllegalOperationException("dish::SymbolTable::Pop()");
}

bool dish::SymbolTable::IsEmpty() const
{
    throw IllegalOperationException("dish::SymbolTable::IsEmpty()");
}

/******************************************************************************

    dish::SingleSymbolTable class definitions

 ******************************************************************************/
 
dish::IntegerT dish::SingleSymbolTable::LookupCount(0);
            
std::shared_ptr< dish::iSymbolTable > dish::SingleSymbolTable::Clone(const dish::iSymbolTable::CloneT &type) const
{
    switch(type)
    {
        case cloneMinimal:
        case cloneShallow:
        {
            return MakeValue(mId, mValue);
        } break;
        
        case cloneDeep:
        {
            return MakeValue(mId, mValue->Clone());
        } break;
        
        default:
        {
            assert(false);
        }
        
    }
}

void dish::SingleSymbolTable::Shuffle()
{
    //  Empty
}

int dish::SingleSymbolTable::Num() const
{
    return 1;
}

bool dish::SingleSymbolTable::Exists(const std::string &key) const
{
    ++LookupCount;

    return (key == mId);
}

void dish::SingleSymbolTable::Insert(const std::string &key, std::shared_ptr< dish::iAtomic > value)
{
    throw IllegalOperationException("Insert operation not supported by SingleSymbolTable.");
}

std::shared_ptr< dish::iAtomic > dish::SingleSymbolTable::Lookup(const std::string &key) const
{
    ++LookupCount;

    return (key == mId) ? mValue : std::shared_ptr< iAtomic >(0);
}

void dish::SingleSymbolTable::Load(dish::iSymbolTable &symtab, const dish::iSymbolTable::CloneT &type) const
{
    throw IllegalOperationException("Load operation not supported by SingleSymbolTable.");
}

void dish::SingleSymbolTable::Clear()
{
    throw IllegalOperationException("Clear operation not supported by SingleSymbolTable.");
}

void dish::SingleSymbolTable::Histogram(std::ostream &out) const
{
    const int max(Num());
    const int num(Num());
    
    int len(static_cast< double >(TBL_HEIGHT) * static_cast< double >(num) / static_cast< double >(max) + 0.5);
    if(num > 0)
    {
        if(0 == len)
        {
            len = 1;
        }
    }
    
    out << num;
    if(num < 1000)
    {
        out << " ";
        
        if(num < 100)
        {
            out << " ";
            
            if(num < 10)
            {
                out << " ";
            }
        }
    }
    
    out << "|";
    if(len > 0)
    {
        out << std::string(len, '>');
    }
    out << std::endl;
}

void dish::SingleSymbolTable::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << mId << std::endl;
}

/******************************************************************************

    dish::BasicSymbolTable class definitions

 ******************************************************************************/
 
dish::IntegerT dish::BasicSymbolTable::LookupCount(0);

dish::BasicSymbolTable::BasicSymbolTable(const dish::BasicSymbolTable &table, const dish::iSymbolTable::CloneT &type) : SymbolTable(),
    mTable()
{
    switch(type)
    {
        case cloneMinimal:
        case cloneShallow:
        {
            mTable.insert(table.mTable.begin(), table.mTable.end());
        } break;
        
        case cloneDeep:
        {
            std::for_each(
                table.mTable.begin(), table.mTable.end(),
                [&](const TableT::value_type &value)
                {
                    mTable[value.first] = value.second->Clone();
                }
            );
        } break;
        
        default:
        {
            assert(false);
        }
        
    }
}

std::shared_ptr< dish::iSymbolTable > dish::BasicSymbolTable::Clone(const dish::iSymbolTable::CloneT &type) const
{
    return std::shared_ptr< BasicSymbolTable >(new BasicSymbolTable(*this, type));
}
 
void dish::BasicSymbolTable::Shuffle()
{
    using KeyValueT = std::vector< std::pair< std::string, std::shared_ptr< iAtomic > > >;
    
    static uint32_t rseed(static_cast< uint32_t >(time(NULL)));
    
    const KeyValueT::size_type npairs(mTable.size());
    
    KeyValueT keyvalues;
    keyvalues.reserve(npairs);
    
    //  Retrieve the key-value pairs from the table.
    std::for_each(
        mTable.begin(), mTable.end(),
        [&](const TableT::value_type &elem)
        {
            keyvalues.push_back(std::make_pair(elem.first, elem.second));
        }
    );
    assert(npairs == keyvalues.size());
    
    //  Shuffle the key-value pairs. The goal is to randomize the order in
    //  which the pairs are re-inserted into the table, which is a binary tree
    //  of some sort and a randomized insertion order is almost certainly
    //  preferable. Besides, that is the whole point of this method :)
    if(npairs > 1)
    {
        for(KeyValueT::size_type i(0); i != npairs; ++i)
        {
            KeyValueT::size_type j;
        
            do
            {
                rseed = (1103515245 * rseed) + 12345;
                j = rseed % npairs;
            } while(i == j);
            
            std::swap(keyvalues[i], keyvalues[j]);
        }
    }
    assert(npairs == keyvalues.size());

    //  Clean out the symbol table.
    mTable.clear();
    
    //  Reinsert each key-value pair back into the symbol table.
    std::for_each(
        keyvalues.begin(), keyvalues.end(),
        [&](const KeyValueT::value_type &elem)
        {
            Insert(elem.first, elem.second);
        }
    );
    assert(npairs == mTable.size());
}
 
int dish::BasicSymbolTable::Num() const
{
    return static_cast< int >(mTable.size());
}

bool dish::BasicSymbolTable::Exists(const std::string &key) const
{
    ++LookupCount;

    return (mTable.end() != mTable.find(key));
}

void dish::BasicSymbolTable::Insert(const std::string &key, std::shared_ptr< dish::iAtomic > value)
{
    if(!mTable.insert(std::make_pair(key, value)).second)
    {
        std::stringstream message;
        message << "The symbol '";
        message << key;
        message << "' already exists.";
        
        throw DuplicateSymbolException(message.str());
    }
}

std::shared_ptr< dish::iAtomic > dish::BasicSymbolTable::Lookup(const std::string &key) const
{
    ++LookupCount;

    const TableT::const_iterator elem(mTable.find(key));
    
    if(mTable.end() != elem)
    {
        return elem->second;
    }
    
    return std::shared_ptr< iAtomic >(0);
}

void dish::BasicSymbolTable::Load(dish::iSymbolTable &symtab, const dish::iSymbolTable::CloneT &type) const
{
    switch(type)
    {
        case cloneMinimal:
        case cloneShallow:
        {
            std::for_each(
                mTable.begin(), mTable.end(),
                [&](const TableT::value_type &value)
                {
                    symtab.Insert(value.first, value.second);
                }
            );
        } break;
        
        case cloneDeep:
        {
            std::for_each(
                mTable.begin(), mTable.end(),
                [&](const TableT::value_type &value)
                {
                    symtab.Insert(value.first, value.second->Clone());
                }
            );
        } break;
        
        default:
        {
            assert(false);
        }
        
    }
}

void dish::BasicSymbolTable::Clear()
{
    mTable.clear();
}

void dish::BasicSymbolTable::Histogram(std::ostream &out) const
{
    const int max(Num());
    const int num(Num());
    
    int len(static_cast< double >(TBL_HEIGHT) * static_cast< double >(num) / static_cast< double >(max) + 0.5);
    if(num > 0)
    {
        if(0 == len)
        {
            len = 1;
        }
    }
    
    out << num;
    if(num < 1000)
    {
        out << " ";
        
        if(num < 100)
        {
            out << " ";
            
            if(num < 10)
            {
                out << " ";
            }
        }
    }
    
    out << "|";
    if(len > 0)
    {
        out << std::string(len, '>');
    }
    out << std::endl;
}

void dish::BasicSymbolTable::Print(std::ostream &out, const std::string::size_type &indent) const
{
    std::for_each(
        mTable.begin(), mTable.end(),
        [&](const TableT::value_type &value)
        {
            printIndent(out, indent);
            out << value.first << std::endl;
        }
    );
}

/******************************************************************************

    dish::HashedSymbolTable class definitions

 ******************************************************************************/
 
dish::IntegerT dish::HashedSymbolTable::LookupCount(0);
 
const dish::HashedSymbolTable::TableT::size_type dish::HashedSymbolTable::TABLE_SIZE(19);

namespace
{

#ifdef SYMTAB_HASH_FUNC_PARTIAL_ID
        
    const uint32_t CRCTBL[256] = {
        0x00000000, 0x0183AF29, 0x03075E52, 0x0284F17B, 0x060EBCA4, 0x078D138D, 0x0509E2F6, 0x048A4DDF, 
        0x0C1D7948, 0x0D9ED661, 0x0F1A271A, 0x0E998833, 0x0A13C5EC, 0x0B906AC5, 0x09149BBE, 0x08973497, 
        0x183AF290, 0x19B95DB9, 0x1B3DACC2, 0x1ABE03EB, 0x1E344E34, 0x1FB7E11D, 0x1D331066, 0x1CB0BF4F, 
        0x14278BD8, 0x15A424F1, 0x1720D58A, 0x16A37AA3, 0x1229377C, 0x13AA9855, 0x112E692E, 0x10ADC607, 
        0x3075E520, 0x31F64A09, 0x3372BB72, 0x32F1145B, 0x367B5984, 0x37F8F6AD, 0x357C07D6, 0x34FFA8FF, 
        0x3C689C68, 0x3DEB3341, 0x3F6FC23A, 0x3EEC6D13, 0x3A6620CC, 0x3BE58FE5, 0x39617E9E, 0x38E2D1B7, 
        0x284F17B0, 0x29CCB899, 0x2B4849E2, 0x2ACBE6CB, 0x2E41AB14, 0x2FC2043D, 0x2D46F546, 0x2CC55A6F, 
        0x24526EF8, 0x25D1C1D1, 0x275530AA, 0x26D69F83, 0x225CD25C, 0x23DF7D75, 0x215B8C0E, 0x20D82327, 
        0x60EBCA40, 0x61686569, 0x63EC9412, 0x626F3B3B, 0x66E576E4, 0x6766D9CD, 0x65E228B6, 0x6461879F, 
        0x6CF6B308, 0x6D751C21, 0x6FF1ED5A, 0x6E724273, 0x6AF80FAC, 0x6B7BA085, 0x69FF51FE, 0x687CFED7, 
        0x78D138D0, 0x795297F9, 0x7BD66682, 0x7A55C9AB, 0x7EDF8474, 0x7F5C2B5D, 0x7DD8DA26, 0x7C5B750F, 
        0x74CC4198, 0x754FEEB1, 0x77CB1FCA, 0x7648B0E3, 0x72C2FD3C, 0x73415215, 0x71C5A36E, 0x70460C47, 
        0x509E2F60, 0x511D8049, 0x53997132, 0x521ADE1B, 0x569093C4, 0x57133CED, 0x5597CD96, 0x541462BF, 
        0x5C835628, 0x5D00F901, 0x5F84087A, 0x5E07A753, 0x5A8DEA8C, 0x5B0E45A5, 0x598AB4DE, 0x58091BF7, 
        0x48A4DDF0, 0x492772D9, 0x4BA383A2, 0x4A202C8B, 0x4EAA6154, 0x4F29CE7D, 0x4DAD3F06, 0x4C2E902F, 
        0x44B9A4B8, 0x453A0B91, 0x47BEFAEA, 0x463D55C3, 0x42B7181C, 0x4334B735, 0x41B0464E, 0x4033E967, 
        0xC1D79480, 0xC0543BA9, 0xC2D0CAD2, 0xC35365FB, 0xC7D92824, 0xC65A870D, 0xC4DE7676, 0xC55DD95F, 
        0xCDCAEDC8, 0xCC4942E1, 0xCECDB39A, 0xCF4E1CB3, 0xCBC4516C, 0xCA47FE45, 0xC8C30F3E, 0xC940A017, 
        0xD9ED6610, 0xD86EC939, 0xDAEA3842, 0xDB69976B, 0xDFE3DAB4, 0xDE60759D, 0xDCE484E6, 0xDD672BCF, 
        0xD5F01F58, 0xD473B071, 0xD6F7410A, 0xD774EE23, 0xD3FEA3FC, 0xD27D0CD5, 0xD0F9FDAE, 0xD17A5287, 
        0xF1A271A0, 0xF021DE89, 0xF2A52FF2, 0xF32680DB, 0xF7ACCD04, 0xF62F622D, 0xF4AB9356, 0xF5283C7F, 
        0xFDBF08E8, 0xFC3CA7C1, 0xFEB856BA, 0xFF3BF993, 0xFBB1B44C, 0xFA321B65, 0xF8B6EA1E, 0xF9354537, 
        0xE9988330, 0xE81B2C19, 0xEA9FDD62, 0xEB1C724B, 0xEF963F94, 0xEE1590BD, 0xEC9161C6, 0xED12CEEF, 
        0xE585FA78, 0xE4065551, 0xE682A42A, 0xE7010B03, 0xE38B46DC, 0xE208E9F5, 0xE08C188E, 0xE10FB7A7, 
        0xA13C5EC0, 0xA0BFF1E9, 0xA23B0092, 0xA3B8AFBB, 0xA732E264, 0xA6B14D4D, 0xA435BC36, 0xA5B6131F, 
        0xAD212788, 0xACA288A1, 0xAE2679DA, 0xAFA5D6F3, 0xAB2F9B2C, 0xAAAC3405, 0xA828C57E, 0xA9AB6A57, 
        0xB906AC50, 0xB8850379, 0xBA01F202, 0xBB825D2B, 0xBF0810F4, 0xBE8BBFDD, 0xBC0F4EA6, 0xBD8CE18F, 
        0xB51BD518, 0xB4987A31, 0xB61C8B4A, 0xB79F2463, 0xB31569BC, 0xB296C695, 0xB01237EE, 0xB19198C7, 
        0x9149BBE0, 0x90CA14C9, 0x924EE5B2, 0x93CD4A9B, 0x97470744, 0x96C4A86D, 0x94405916, 0x95C3F63F, 
        0x9D54C2A8, 0x9CD76D81, 0x9E539CFA, 0x9FD033D3, 0x9B5A7E0C, 0x9AD9D125, 0x985D205E, 0x99DE8F77, 
        0x89734970, 0x88F0E659, 0x8A741722, 0x8BF7B80B, 0x8F7DF5D4, 0x8EFE5AFD, 0x8C7AAB86, 0x8DF904AF, 
        0x856E3038, 0x84ED9F11, 0x86696E6A, 0x87EAC143, 0x83608C9C, 0x82E323B5, 0x8067D2CE, 0x81E47DE7
    };
            
#endif

#ifdef SYMTAB_HASH_FUNC_MULTI_BYTE

    INLINEC uint32_t Sum8_32(const char * const ptr)
    {
        return static_cast< uint32_t >(*reinterpret_cast< const uint8_t * >(ptr));
    }

    INLINEC uint32_t Sum16_32(const char * const ptr)
    {
        return static_cast< uint32_t >(*reinterpret_cast< const uint16_t * >(ptr));
    }

    INLINEC uint32_t Sum32_32(const char * const ptr)
    {
        return static_cast< uint32_t >(*reinterpret_cast< const uint32_t * >(ptr));
    }
    
#endif

    INLINEC dish::HashedSymbolTable::TableT::size_type h(const std::string &key)
    {
        uint32_t hashval(0);
        
#ifdef SYMTAB_HASH_FUNC_WHOLE_ID
        
        std::for_each(
            key.begin(), key.end(),
            [&](const std::string::value_type &elem)
            {
                hashval += static_cast< uint32_t >(elem);
            }
        );
        
#endif

#ifdef SYMTAB_HASH_FUNC_PARTIAL_ID

        {     
            const std::string::size_type key_size(key.length());
            
            switch(key_size)
            {
                case 4:
                {
                    hashval += static_cast< uint32_t >(key[3]);
                }
                
                case 3:
                {
                    hashval += static_cast< uint32_t >(key[2]);
                }
                
                case 2:
                {
                    hashval += static_cast< uint32_t >(key[1]);
                }
                
                case 1:
                {
                    hashval += static_cast< uint32_t >(key[0]);
                }
                
                case 0:
                {
                    //  Empty
                } break;
                
                default:
                {
#ifdef SYMTAB_HASH_FUNC_PARTIAL_ID_SPREAD
                    /*
                        The hash-function uses the first, middle, 3/4, and last ASCII
                        values of the string. So:
                        
                            ID: 0123456789
                                ^    ^ ^ ^
                        This scheme assumes that the last half of a key value will be
                        more evenly distributed that the first half of the key. This is
                        assumed to be the case because developers tend to use a common 
                        prefix for identifiers in a package, Str and TEXTIO_ are
                        examples of this from the langage's run-time library.
                    */
                    hashval += static_cast< uint32_t >(key[key_size - 1]);
                    hashval += static_cast< uint32_t >(key[3 * key_size / 4]);
                    hashval += static_cast< uint32_t >(key[key_size / 2]);
                    hashval += static_cast< uint32_t >(key[0]);
#else
                    /*
                        The hash-function uses the first, last, last-1, and last-2 ASCII
                        values of the string. So:
                        
                            ID: 0123456789
                                ^      ^^^
                                
                    */
                    
                    hashval += static_cast< uint32_t >(key[0]);
                    
                    hashval += static_cast< uint32_t >(key[key_size - 3]);
                    hashval += static_cast< uint32_t >(key[key_size - 2]);
                    hashval += static_cast< uint32_t >(key[key_size - 1]);
#endif
                }
                
            }
        }
        
#endif
        
#ifdef SYMTAB_HASH_FUNC_HASHED_WHOLE_ID
        
        std::for_each(
            key.begin(), key.end(),
            [&](const std::string::value_type &elem)
            {
                hashval = CRCTBL[static_cast< uint8_t >(elem ^ (hashval >> 24))] ^ (hashval << 8);
            }
        );
        
#endif

#ifdef SYMTAB_HASH_FUNC_HASHED_PARTIAL_ID

        {     
            const std::string::size_type key_size(key.length());
            
            switch(key_size)
            {
                case 4:
                {
                    hashval = CRCTBL[static_cast< uint8_t >(key[3] ^ (hashval >> 24))] ^ (hashval << 8);
                }
                
                case 3:
                {
                    hashval = CRCTBL[static_cast< uint8_t >(key[2] ^ (hashval >> 24))] ^ (hashval << 8);
                }
                
                case 2:
                {
                    hashval = CRCTBL[static_cast< uint8_t >(key[1] ^ (hashval >> 24))] ^ (hashval << 8);
                }
                
                case 1:
                {
                    hashval = CRCTBL[static_cast< uint8_t >(key[0] ^ (hashval >> 24))] ^ (hashval << 8);
                }
                
                case 0:
                {
                    //  Empty
                } break;
                
                default:
                {
#ifdef SYMTAB_HASH_FUNC_PARTIAL_ID_SPREAD
                    /*
                        The hash-function uses the first, middle, 3/4, and last ASCII
                        values of the string. So:
                        
                            ID: 0123456789
                                ^    ^ ^ ^
                        This scheme assumes that the last half of a key value will be
                        more evenly distributed that the first half of the key. This is
                        assumed to be the case because developers tend to use a common 
                        prefix for identifiers in a package, Str and TEXTIO_ are
                        examples of this from the langage's run-time library.
                    */
                    hashval = CRCTBL[static_cast< uint8_t >(key[key_size - 1] ^ (hashval >> 24))] ^ (hashval << 8);
                    hashval = CRCTBL[static_cast< uint8_t >(key[3 * key_size / 4] ^ (hashval >> 24))] ^ (hashval << 8);
                    hashval = CRCTBL[static_cast< uint8_t >(key[key_size / 2] ^ (hashval >> 24))] ^ (hashval << 8);
                    hashval = CRCTBL[static_cast< uint8_t >(key[0] ^ (hashval >> 24))] ^ (hashval << 8);
#else
                    /*
                        The hash-function uses the first, last, last-1, and last-2 ASCII
                        values of the string. So:
                        
                            ID: 0123456789
                                ^      ^^^
                                
                    */
                    hashval = CRCTBL[static_cast< uint8_t >(key[key_size - 3] ^ (hashval >> 24))] ^ (hashval << 8);
                    hashval = CRCTBL[static_cast< uint8_t >(key[key_size - 2] ^ (hashval >> 24))] ^ (hashval << 8);
                    hashval = CRCTBL[static_cast< uint8_t >(key[key_size - 1] ^ (hashval >> 24))] ^ (hashval << 8);
                    hashval = CRCTBL[static_cast< uint8_t >(key[0] ^ (hashval >> 24))] ^ (hashval << 8);
#endif
                }
                
            }
        }
        
#endif

#ifdef SYMTAB_HASH_FUNC_MULTI_BYTE
        
        {
            std::string::size_type key_size(key.length());
            const char *ptr(key.c_str());
            
            while(key_size >= 4)
            {
                hashval += Sum32_32(ptr);
                
                key_size -= 4;
                ptr += 4;
            }
            
            switch(key_size)
            {
                case 0:
                {
                    //  Empty.
                } break;
                
                case 1:
                {
                    hashval += Sum8_32(ptr);
                } break;
                
                case 2:
                {
                    hashval += Sum16_32(ptr);
                } break;
                
                case 3:
                {
                    hashval += (Sum16_32(ptr) + Sum8_32(ptr + 2));
                } break;
                
                default:
                {
                    assert(false);
                }
                
            }
        }

#endif

        return static_cast< dish::HashedSymbolTable::TableT::size_type >(hashval) % dish::HashedSymbolTable::TABLE_SIZE;
    }

}

dish::HashedSymbolTable::HashedSymbolTable(const dish::HashedSymbolTable &table, const dish::iSymbolTable::CloneT &type) : SymbolTable(), 
    mTable(TABLE_SIZE)
{
    TableT::iterator dest_i(mTable.begin());
    const TableT::iterator dest_last_i(mTable.end());
    
    TableT::const_iterator src_i(table.mTable.begin());
    const TableT::const_iterator src_last_i(table.mTable.end());
    
    while((dest_i != dest_last_i) && (src_i != src_last_i))
    {
        (src_i++)->Load(*dest_i++, type);
    }
    
    assert(dest_i == dest_last_i);
    assert(src_i == src_last_i);
}

std::shared_ptr< dish::iSymbolTable > dish::HashedSymbolTable::Clone(const dish::iSymbolTable::CloneT &type) const
{
    return std::shared_ptr< HashedSymbolTable >(new HashedSymbolTable(*this, type));
}

void dish::HashedSymbolTable::Shuffle()
{
    std::for_each(
        mTable.begin(), mTable.end(),
        [](TableT::value_type &value)
        {
            value.Shuffle();
        }
    );
}

int dish::HashedSymbolTable::Num() const
{
    int count(0);
    
    std::for_each(
        mTable.begin(), mTable.end(),
        [&count](const TableT::value_type &val)
        {
            count += val.Num();
        }
    );
    
    return count;
}

bool dish::HashedSymbolTable::Exists(const std::string &key) const
{
    ++LookupCount;
    
    return mTable[h(key)].Exists(key);
}


void dish::HashedSymbolTable::Insert(const std::string &key, std::shared_ptr< dish::iAtomic > value)
{
    mTable[h(key)].Insert(key, value);
}

std::shared_ptr< dish::iAtomic > dish::HashedSymbolTable::Lookup(const std::string &key) const
{
    ++LookupCount;
    
    return mTable[h(key)].Lookup(key);
}

void dish::HashedSymbolTable::Load(dish::iSymbolTable &symtab, const dish::iSymbolTable::CloneT &type) const
{
    std::for_each(
        mTable.begin(), mTable.end(),
        [&](const TableT::value_type &value)
        {
            value.Load(symtab, type);
        }
    );
}

void dish::HashedSymbolTable::Clear()
{
    std::for_each(
        mTable.begin(), mTable.end(),
        [](TableT::value_type &val)
        {
            val.Clear();
        }
    ); 
}

void dish::HashedSymbolTable::Histogram(std::ostream &out) const
{
    const int HEIGHT(75);

    int max(0);
    int min(mTable.front().Num());
    int sum(0);

    //  Compute basic statistics.
    std::for_each(
        mTable.begin(), mTable.end(),
        [&](const TableT::value_type &val)
        {
            const int num(val.Num());
            
            sum += num;
        
            if(num > max)
            {
                max = num;
            }
            
            if(num < min)
            {
                min = num;
            }
        }
    );
    
    //  Print the histogram.
    std::for_each(
        mTable.begin(), mTable.end(),
        [&](const TableT::value_type &val)
        {
            const int num(val.Num());
            
            int len(static_cast< double >(HEIGHT) * static_cast< double >(num) / static_cast< double >(max) + 0.5);
            if(num > 0)
            {
                if(0 == len)
                {
                    len = 1;
                }
            }
            
            out << num;
            if(num < 1000)
            {
                out << " ";
                
                if(num < 100)
                {
                    out << " ";
                    
                    if(num < 10)
                    {
                        out << " ";
                    }
                }
            }
            
            out << "|";
            if(len > 0)
            {
                out << std::string(len, '>');
            }
            out << std::endl;
        }
    );
    
    const int len(static_cast< double >(HEIGHT) * static_cast< double >(sum) / mTable.size() / static_cast< double >(max) + 0.5);
    out << "Avg.|";
    if(len > 0)
    {
        out << std::string(len, ' ');
    }
    out << "^" << std::endl;
    
    //  Compute the median value.
    double median(0.0);
    {
        std::vector< int > sizes;
        
        //  Fill a vector with the table sizes.
        std::for_each(
            mTable.begin(), mTable.end(),
            [&](const TableT::value_type &val)
            {
                sizes.push_back(val.Num());
            }
        );
        
        //  Sort the vector.
        std::sort(sizes.begin(), sizes.end());
        
        //  Select the median value.
        const auto mid(sizes.size() / 2);
        median = static_cast< double >(sizes[mid]);
        if(0 == sizes.size())
        {
            
            median += static_cast< double >(sizes[mid + 1]);
            median /= 2.0;
        }
    }
    
    //  Print basic statistics.
    out << "----+" << std::endl;
    out << Num() << std::endl;
    out << std::endl;
    out << " Maximum Table Size: " << max << std::endl;
    out << " Minimum Table Size: " << min << std::endl;
    out << "  Table Size Spread: " << (max - min) << std::endl;
    out << "        Table Ratio: " << (static_cast< double >(max) / static_cast< double >(min)) << std::endl;
    out << " Average Table Size: " << (static_cast< double >(sum) / mTable.size()) << std::endl;
    out << "  Median Table Size: " << median << std::endl;
}

void dish::HashedSymbolTable::Print(std::ostream &out, const std::string::size_type &indent) const
{
    std::for_each(
        mTable.begin(), mTable.end(),
        [&](const TableT::value_type &value)
        {
            const int num(value.Num());
            
            printIndent(out, indent);
            out << num;
            if(num < 1000)
            {
                out << " ";
                
                if(num < 100)
                {
                    out << " ";
                    
                    if(num < 10)
                    {
                        out << " ";
                    }
                }
            }
            out << ":" << std::endl;
        
            value.Print(out, indent + 4);
            out << std::endl;
        }
    );
}

/******************************************************************************

    dish::StackedSymbolTable class definitions

 ******************************************************************************/

const int dish::StackedSymbolTable::INFINITE_STACK_DEPTH(0);

#ifdef RECYCLE_SYMBOL_TABLES

const dish::StackedSymbolTable::RecycleListT::size_type dish::StackedSymbolTable::RESERVED_RECYCLE_BIN_DEPTH(10);
const dish::StackedSymbolTable::RecycleListT::size_type dish::StackedSymbolTable::MAXIMUM_RECYCLE_BIN_DEPTH(50);

dish::StackedSymbolTable::StackedSymbolTable(const dish::StackedSymbolTable &symtab, const dish::iSymbolTable::CloneT &type) : SymbolTable(),
    mStack(),
    mRecycleBin(), 
    mMaximumStackDepth(symtab.mMaximumStackDepth),
    mMaximumStackDepthAttained(0)
{
    mRecycleBin.reserve(RESERVED_RECYCLE_BIN_DEPTH);
    
    switch(type)
    {
        case cloneMinimal:
        {
            for(TableT::const_iterator i(symtab.mStack.begin()), last_i(symtab.mStack.end()); i != last_i; ++i)
            {
                mStack.push_back(*i);
            }
        } break;
        
        case cloneShallow:
        {
            for(TableT::const_iterator i(symtab.mStack.begin()), last_i(symtab.mStack.end()); i != last_i; ++i)
            {
                mStack.push_back((*i)->Clone(cloneShallow));
            }
        } break;
        
        case cloneDeep:
        {
            for(TableT::const_iterator i(symtab.mStack.begin()), last_i(symtab.mStack.end()); i != last_i; ++i)
            {
                mStack.push_back((*i)->Clone(cloneDeep));
            }
        } break;
        
        default:
        {
            assert(false);
        }
        
    }
}

#else

dish::StackedSymbolTable::StackedSymbolTable(const dish::StackedSymbolTable &symtab, const dish::iSymbolTable::CloneT &type) : SymbolTable(),
    mStack(),
    mMaximumStackDepth(symtab.mMaximumStackDepth),
    mMaximumStackDepthAttained(0)
{
    switch(type)
    {
        case cloneMinimal:
        {
            mStack.assign(symtab.mStack.begin(), symtab.mStack.end());
        } break;
        
        case cloneShallow:
            //  Fall-through
        case cloneDeep:
        {
            for(TableT::const_iterator i(symtab.mStack.begin()), last_i(symtab.mStack.end()); i != last_i; ++i)
            {
                mStack.push_back((*i)->Clone(type));
            }
        } break;
        
        default:
        {
            assert(false);
        }
        
    }
}

#endif

std::shared_ptr< dish::iSymbolTable > dish::StackedSymbolTable::Clone(const dish::iSymbolTable::CloneT &type) const
{
    return std::shared_ptr< StackedSymbolTable >(new StackedSymbolTable(*this, type));
}
 
void dish::StackedSymbolTable::Shuffle()
{
    std::for_each(
        mStack.begin(), mStack.end(),
        [](TableT::value_type &value)
        {
            value->Shuffle();
        }
    );
}

void dish::StackedSymbolTable::Push(std::shared_ptr< iSymbolTable > table)
{
    assert(table);
    
    mStack.push_back(table);
    checkStackSize();
}

void dish::StackedSymbolTable::Push()
{
#ifdef RECYCLE_SYMBOL_TABLES

    //  Do we have a recycled table?
    if(!mRecycleBin.empty())
    {
        //  Yes; recycle the table by pushing it onto the stack.
        mStack.push_back(mRecycleBin.back());
        
        //  And remove the recycles table from the recycling bin.
        mRecycleBin.pop_back();
    }
    else
    {
        //  No; Create a new table and push it onto the stack.
        mStack.push_back(BasicSymbolTable::MakeValue());
    }
    
#else

    mStack.push_back(BasicSymbolTable::MakeValue());

#endif
    
    checkStackSize();
}

void dish::StackedSymbolTable::Pop()
{
    assert(!mStack.empty());
    
#ifdef RECYCLE_SYMBOL_TABLES

    //  Are we going to recycle the symbol-table we pop off the stack?
    if((0 >= MAXIMUM_RECYCLE_BIN_DEPTH) || (mRecycleBin.size() < MAXIMUM_RECYCLE_BIN_DEPTH))
    {
        //  Yes; get the table being popped off the stack.
        std::shared_ptr< iSymbolTable > table(mStack.back());
        
        //  Clear the table's contents.
        table->Clear();
        
        //  Add the table to the recycling bin.
        mRecycleBin.push_back(table);
    }
    
#endif
    
    //  Pop the table off the stack.
    mStack.pop_back();
}

bool dish::StackedSymbolTable::IsEmpty() const
{
    return mStack.empty();
}

int dish::StackedSymbolTable::Num() const
{
    int count(0);
    
    std::for_each(
        mStack.begin(), mStack.end(),
        [&](const TableT::value_type &val)
        {
            count += val->Num();
        }
    );
    
    return count;
}

bool dish::StackedSymbolTable::Exists(const std::string &key) const
{
    for(TableT::const_reverse_iterator tbl_i(mStack.rbegin()), last_tbl_i(mStack.rend()); tbl_i != last_tbl_i; ++tbl_i)
    {
        if((*tbl_i)->Exists(key))
        {
            return true;
        }
    }

    return false;
}

void dish::StackedSymbolTable::Insert(const std::string &key, std::shared_ptr< dish::iAtomic > value)
{
    assert(!mStack.empty());
    assert(value);
    
    mStack.back()->Insert(key, value);
}

std::shared_ptr< dish::iAtomic > dish::StackedSymbolTable::Lookup(const std::string &key) const
{
    for(TableT::const_reverse_iterator tbl_i(mStack.rbegin()), last_tbl_i(mStack.rend()); last_tbl_i != tbl_i; ++tbl_i)
    {
        std::shared_ptr< dish::iAtomic > value((*tbl_i)->Lookup(key));
        if(value)
        {
            return value;
        }
    }

    return std::shared_ptr< iAtomic >(0);
}

void dish::StackedSymbolTable::Load(dish::iSymbolTable &symtab, const dish::iSymbolTable::CloneT &type) const
{
    for(TableT::const_iterator i(mStack.begin()), last_i(mStack.end()); i != last_i; ++i)
    {
        symtab.Push((*i)->Clone(type));
    }
}

void dish::StackedSymbolTable::Clear()
{
    while(mStack.size() > 1)
    {
        Pop();
    }
    
    mStack.back()->Clear();
}

void dish::StackedSymbolTable::Histogram(std::ostream &out) const
{
    std::for_each(
        mStack.rbegin(), mStack.rend(),
        [&](const TableT::value_type &val)
        {
            out << "----" << std::endl;
            val->Histogram(out);
        }
    );
}

void dish::StackedSymbolTable::Print(std::ostream &out, const std::string::size_type &indent) const
{
    out << std::endl;
    printIndent(out, indent);
    out << "<----------------------------------------------------------------------------->" << std::endl;
    out << std::endl;

    std::for_each(
        mStack.rbegin(), mStack.rend(),
        [&](const TableT::value_type &value)
        {
            value->Print(out, indent + 4);
    
            out << std::endl;
            printIndent(out, indent);
            out << "<----------------------------------------------------------------------------->" << std::endl;
            out << std::endl;
        }
    );
}

