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

#include <sstream>

#include "db.h"
#include "langcore.h"
#include "langdb.h"

namespace
{

    const dish::StringT StructMemberID_HOST("Host");
    const dish::StringT StructMemberID_PORT("Port");
    const dish::StringT StructMemberID_USERNAME("UserName");
    const dish::StringT StructMemberID_PASSWORD("Password");
    const dish::StringT StructMemberID_DATABASENAME("DbName");
    const dish::StringT StructMemberID_TIMEOUT("Timeout");
    
    INLINE void ExtractDbConnectionParameters(dish::iDbConnection::ConnectionParams &conparams, std::shared_ptr< dish::iAtomic > structure)
    {
        conparams.SetHost(structure->Member(StructMemberID_HOST)->AsString());
        conparams.SetPort(structure->Member(StructMemberID_PORT)->AsInteger());
        conparams.SetUserName(structure->Member(StructMemberID_USERNAME)->AsString());
        conparams.SetPassword(structure->Member(StructMemberID_PASSWORD)->AsString());
        conparams.SetDatabaseName(structure->Member(StructMemberID_DATABASENAME)->AsString());
        conparams.SetTimeout(structure->Member(StructMemberID_TIMEOUT)->AsInteger());
    }

}

/******************************************************************************

    Database function definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::CreateDbConnectionParametersType()
{
    static std::shared_ptr< StructureTypeAtomic > structure;
    
    if(0 == structure.get())
    {
        std::shared_ptr< IntegerTypeAtomic > integer_type(IntegerTypeAtomic::MakeValue());
        std::shared_ptr< StringTypeAtomic > string_type(StringTypeAtomic::MakeValue());
    
        structure = StructureTypeAtomic::MakeValue();
        structure->Add(StructMemberID_HOST, string_type);
        structure->Add(StructMemberID_PORT, integer_type);
        structure->Add(StructMemberID_USERNAME, string_type);
        structure->Add(StructMemberID_PASSWORD, string_type);
        structure->Add(StructMemberID_DATABASENAME, string_type);
        structure->Add(StructMemberID_TIMEOUT, integer_type);
    }
    
    return structure;
}

/******************************************************************************

    dish::DbMakeDefaultConnectionParametersFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::DbMakeDefaultConnectionParametersFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    iDbConnection::ConnectionParams defaultparams;
    
    std::shared_ptr< iAtomic > connparams(getParam(symtab, "connparams"));
    connparams->Member(StructMemberID_HOST)->Assign(defaultparams.GetHost());
    connparams->Member(StructMemberID_PORT)->Assign(defaultparams.GetPort());
    connparams->Member(StructMemberID_USERNAME)->Assign(defaultparams.GetUserName());
    connparams->Member(StructMemberID_PASSWORD)->Assign(defaultparams.GetPassword());
    connparams->Member(StructMemberID_DATABASENAME)->Assign(defaultparams.GetDatabaseName());
    connparams->Member(StructMemberID_TIMEOUT)->Assign(defaultparams.GetTimeout());
    
    return connparams;
}

/******************************************************************************

    dish::DbMakeDefaultConnectionParameters2Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::DbMakeDefaultConnectionParameters2Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    std::shared_ptr< iAtomic > connparams(getParam(symtab, "connparams"));

    const IntegerT type(getParam(symtab, "type")->AsInteger());
    switch(type)
    {
        case _DB_CONNECTION_TYPE_MYSQL:
        {
            connparams->Member(StructMemberID_HOST)->Assign(StringValue::MakeValue("127.0.0.1"));
            connparams->Member(StructMemberID_PORT)->Assign(IntegerValue::MakeValue(0));
            connparams->Member(StructMemberID_USERNAME)->Assign(StringValue::MakeValue(""));
            connparams->Member(StructMemberID_PASSWORD)->Assign(StringValue::MakeValue(""));
            connparams->Member(StructMemberID_DATABASENAME)->Assign(StringValue::MakeValue(""));
            connparams->Member(StructMemberID_TIMEOUT)->Assign(IntegerValue::MakeValue(100));
        } break;
        
        case _DB_CONNECTION_TYPE_POSTGRESQL:
        {
            connparams->Member(StructMemberID_HOST)->Assign(StringValue::MakeValue("127.0.0.1"));
            connparams->Member(StructMemberID_PORT)->Assign(IntegerValue::MakeValue(0));
            connparams->Member(StructMemberID_USERNAME)->Assign(StringValue::MakeValue(""));
            connparams->Member(StructMemberID_PASSWORD)->Assign(StringValue::MakeValue(""));
            connparams->Member(StructMemberID_DATABASENAME)->Assign(StringValue::MakeValue(""));
            connparams->Member(StructMemberID_TIMEOUT)->Assign(IntegerValue::MakeValue(100));
        } break;
        
        default:
        {
            std::stringstream message;
            message << "Invalid connection type specified: ";
            message << type;
            message << ".";
        
            throw DatabaseInvalidConnectionTypeException(message.str());
        }
        
    }
    
    return connparams;
}

/******************************************************************************

    dish::DbOpenConnectionFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::DbOpenConnectionFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    iDbConnection::ConnectionParams conparams;
    ExtractDbConnectionParameters(conparams, getParam(symtab, "config"));

    return IntegerValue::MakeValue(
        DbConnectionFactory::Instance().OpenConnection(
            getParam(symtab, "type")->AsInteger(),
            conparams
        )
    );
}

/******************************************************************************

    dish::DbCloseConnectionFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::DbCloseConnectionFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const IntegerT handle(getParam(symtab, "handle")->AsInteger());

    DbConnectionFactory::Instance().CloseConnection(handle);

    return NullValue::MakeValue();
}

/******************************************************************************

    dish::DbCloseAllConnectionsFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::DbCloseAllConnectionsFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    DbConnectionFactory::Instance().CloseAllConnections();

    return NullValue::MakeValue();
}

/******************************************************************************

    dish::DbIsOpenFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::DbIsOpenFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return BooleanValue::MakeLockedValue(
        DbConnectionFactory::Instance().IsOpen(getParam(symtab, "handle")->AsInteger())
    );
}

/******************************************************************************

    dish::DbNumOpenConnectionsFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::DbNumOpenConnectionsFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return IntegerValue::MakeValue(
        DbConnectionFactory::Instance().NumOpenConnections()
    );
}

/******************************************************************************

    dish::DbNumOpenConnections1Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::DbNumOpenConnections1Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    return IntegerValue::MakeValue(
        DbConnectionFactory::Instance().NumOpenConnections(
            getParam(symtab, "validate")->AsBoolean()
        )
    );
}

/******************************************************************************

    dish::DbServerVersionFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::DbServerVersionFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const IntegerT handle(getParam(symtab, "handle")->AsInteger());

    return CreateVersionStructure(
        DbConnectionFactory::Instance()[handle].ServerVersion(),
        LOCKED
    );
}

/******************************************************************************

    dish::DbIssueQueryFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::DbIssueQueryFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const IntegerT handle(getParam(symtab, "handle")->AsInteger());
    
    return DbConnectionFactory::Instance()[handle].IssueQuery(getParam(symtab, "query")->AsString());
}

