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

#include <algorithm>
#include <cassert>
#include <sstream>

#include "db.h"

#ifdef MYSQLDB
#include "dbmysql.h"
#endif

#ifdef POSTGRESQLDB
#include "dbpostgresql.h"
#endif

/******************************************************************************

    dish::DbResultSet::ContainsMethod definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::DbResultSet::ContainsMethod::Execute(dish::LanguageSymbolTable &symtab) const
{
    const auto &thisval(thisValue().mColNameIndexMap);

    return BooleanValue::MakeLockedValue(thisval.end() != thisval.find(getParam(symtab, "str")->AsString()));
}

/******************************************************************************

    dish::DbResultSet definitions

 ******************************************************************************/
 
dish::DbResultSet::~DbResultSet()
{
    //  Delete the rows before the col-name-index maps because each row 
    //  maintains references to the maps. This ensures that any object with such
    //  a reference is destroyed before the maps are destroyed (remember kids:
    //  safety first!).
    clear();
}

void dish::DbResultSet::AddColumn(const StringT &colname, const IntegerT &index)
{
    if(!IsLocked())
    {
        mColNameIndexMap[colname] = index;
    }
    else
    {
        throw ValueLockedException("Cannot modify a locked value.");
    }
}

std::shared_ptr< dish::DbRowValue > dish::DbResultSet::MakeRow()
{
    return DbRowValue::MakeValue(mColNameIndexMap);
}

std::shared_ptr< dish::iAtomic > dish::DbResultSet::Member(const std::string &member) const
{
    if(IsEqual("contains", member, CASE_INSENSITIVE))
    {
        if(0 == mContainsF.get())
        {
            mContainsF = ContainsMethod::MakeValue(*this);
        }
        
        return mContainsF;
    }
    
    else if(IsEqual("count", member, CASE_INSENSITIVE))
    {
        return IntegerValue::MakeValue(mColNameIndexMap.size(), LOCKED);
    }
    
    else if(IsEqual("empty", member, CASE_INSENSITIVE))
    {
        return BooleanValue::MakeValue(mColNameIndexMap.empty(), LOCKED);
    }
    
    else if(IsEqual("keys", member, CASE_INSENSITIVE))
    {
        return Keys();
    }
    
    return ArrayValue::Member(member);
}

std::shared_ptr< dish::iAtomic > dish::DbResultSet::Keys() const
{
    std::shared_ptr< iAtomic > keys(ArrayValue::MakeValue(0));
    
    std::for_each(
        mColNameIndexMap.begin(), mColNameIndexMap.end(),
        [&](const ColNameIndexT::value_type &elem)
        {
            keys->Add(StringValue::MakeValue(elem.first));
        }
    );
    
    keys->Lock();
    
    return keys;
}

std::shared_ptr< dish::iAtomic > dish::DbResultSet::Lookup(const dish::StringT &key) const
{
    std::shared_ptr< iAtomic > column(ArrayValue::MakeValue(0));
    
    for(IntegerT i(Member("start")->AsInteger()), last_i(Member("finish")->AsInteger()); i <= last_i; ++i)
    {
        column->Add(ArrayValue::Element(i)->Lookup(key));
    }
    
    return column;
}

void dish::DbResultSet::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    out << "ResultSet" << std::endl;
    
    printIndent(out, indent);
    out << "[" << std::endl;
    
    for(IntegerT i(Member("start")->AsInteger()), last_i(Member("finish")->AsInteger()); i <= last_i; ++i)
    {
        printIndent(out, indent + 4);
        out << i << " : ";
        Element(i)->Print(out, 0);
        out << std::endl;
    }
    
    printIndent(out, indent);
    out << "]";
}

/******************************************************************************

    dish::DbRowValue::ContainsMethod definitions

 ******************************************************************************/
 
std::shared_ptr< dish::iAtomic > dish::DbRowValue::ContainsMethod::Execute(dish::LanguageSymbolTable &symtab) const
{
    const auto &thisval(thisValue().mColNameIndexMap);

    return BooleanValue::MakeLockedValue(thisval.end() != thisval.find(getParam(symtab, "str")->AsString()));
}

/******************************************************************************

    dish::DbRowValue definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::DbRowValue::Member(const std::string &member) const
{
    if(IsEqual("contains", member, CASE_INSENSITIVE))
    {
        if(0 == mContainsF.get())
        {
            mContainsF = ContainsMethod::MakeValue(*this);
        }
        
        return mContainsF;
    }
    
    else if(IsEqual("count", member, CASE_INSENSITIVE))
    {
        return IntegerValue::MakeValue(mColNameIndexMap.size(), LOCKED);
    }
    
    else if(IsEqual("empty", member, CASE_INSENSITIVE))
    {
        return BooleanValue::MakeValue(mColNameIndexMap.empty(), LOCKED);
    }
    
    else if(IsEqual("keys", member, CASE_INSENSITIVE))
    {
        return Keys();
    }
    
    return ArrayValue::Member(member);
}

std::shared_ptr< dish::iAtomic > dish::DbRowValue::Keys() const
{
    std::shared_ptr< iAtomic > keys(ArrayValue::MakeValue(0));
    
    std::for_each(
        mColNameIndexMap.begin(), mColNameIndexMap.end(),
        [&](const DbResultSet::ColNameIndexT::value_type &elem)
        {
            keys->Add(StringValue::MakeValue(elem.first));
        }
    );
    
    return keys;
}

std::shared_ptr< dish::iAtomic > dish::DbRowValue::Lookup(const dish::StringT &key) const
{
    const DbResultSet::ColNameIndexT::const_iterator elem(mColNameIndexMap.find(key));
    
    if(mColNameIndexMap.end() != elem)
    {
        return ArrayValue::Element(elem->second);
    }
    
    return NullValue::MakeValue();
}

void dish::DbRowValue::Print(std::ostream &out, const std::string::size_type &indent) const
{
    printIndent(out, indent);
    
    bool first(true);
    for(IntegerT i(Member("start")->AsInteger()), last_i(Member("finish")->AsInteger()); i <= last_i; ++i)
    {
        if(!first)
        {
            out << ", ";
        }
        
        out << Element(i)->AsString();
        
        first = false;
    }
}

/******************************************************************************

    dish::iDbConnection::ConnectionParams definitions

 ******************************************************************************/
 
dish::iDbConnection::ConnectionParams::ConnectionParams() :
    mHost(), 
    mPort(), 
    mUserName(), 
    mPassword(), 
    mDatabaseName(), 
    mTimeout()
{
    SetHost("127.0.0.1");
    SetPort(0);
    SetUserName("");
    SetPassword("");
    SetDatabaseName("");
    SetTimeout(100);
}

dish::iDbConnection::ConnectionParams::ConnectionParams(
    const dish::StringT &host,
    const dish::IntegerT &port,
    const dish::StringT &uname,
    const dish::StringT &passwd,
    const dish::StringT &dbname,
    const dish::IntegerT &timeout) :
        mHost(),
        mPort(),
        mUserName(),
        mPassword(),
        mDatabaseName(),
        mTimeout()
{
    SetHost(host);
    SetPort(port);
    SetUserName(uname);
    SetPassword(passwd);
    SetDatabaseName(dbname);
    SetTimeout(timeout);
}

dish::iDbConnection::ConnectionParams::ConnectionParams(const dish::iDbConnection::ConnectionParams &params) :
    mHost(),
    mPort(),
    mUserName(),
    mPassword(),
    mDatabaseName(),
    mTimeout()
{
    SetHost(params.mHost);
    SetPort(params.mPort);
    SetUserName(params.mUserName);
    SetPassword(params.mPassword);
    SetDatabaseName(params.mDatabaseName);
    SetTimeout(params.mTimeout);
}

const dish::iDbConnection::ConnectionParams &dish::iDbConnection::ConnectionParams::operator=(const dish::iDbConnection::ConnectionParams &rhs)
{
    SetHost(rhs.mHost);
    SetPort(rhs.mPort);
    SetUserName(rhs.mUserName);
    SetPassword(rhs.mPassword);
    SetDatabaseName(rhs.mDatabaseName);
    SetTimeout(rhs.mTimeout);
    
    return *this;
}

/******************************************************************************

    dish::DbConnection definitions

 ******************************************************************************/
 
dish::IntegerT dish::DbConnection::ConnectionType() const
{
    throw DatabaseFeatureNotSupportedException("Feature not supported by the database connection: ConnectionType.");
}

Version dish::DbConnection::ServerVersion()
{
    throw DatabaseFeatureNotSupportedException("Feature not supported by the database connection: ServerVersion.");
}

dish::BooleanT dish::DbConnection::IsOpen()
{
    throw DatabaseFeatureNotSupportedException("Feature not supported by the database connection: IsOpen."); 
}

std::shared_ptr< dish::iAtomic > dish::DbConnection::IssueQuery(const dish::StringT &query)
{
    throw DatabaseFeatureNotSupportedException("Feature not supported by the database connection: IssueQuery.");
}

/******************************************************************************

    dish::DbConnectionFactory definitions

 ******************************************************************************/

const dish::IntegerT dish::DbConnectionFactory::DB_CONNECTION_TYPE_MYSQL(_DB_CONNECTION_TYPE_MYSQL);
const dish::IntegerT dish::DbConnectionFactory::DB_CONNECTION_TYPE_POSTGRESQL(_DB_CONNECTION_TYPE_POSTGRESQL);

const dish::IntegerT dish::DbConnectionFactory::DB_MAX_CONNECTIONS(10);

dish::IntegerT dish::DbConnectionFactory::findAvailableHandle() const
{
    for(ConnectionListT::size_type i(0), last_i(mConnections.size()); i < last_i; ++i)
    {
        if(0 == mConnections[i].get())
        {
            return static_cast< dish::IntegerT >(i);
        }
    }
    
    throw DatabaseTooManyOpenConnectionsException("Too many open database connections.");
}

dish::IntegerT dish::DbConnectionFactory::OpenConnection(const dish::IntegerT &type, const dish::iDbConnection::ConnectionParams &conparams)
{
    const IntegerT handle(findAvailableHandle());
    
    switch(type)
    {
    
#ifdef MYSQLDB
        case _DB_CONNECTION_TYPE_MYSQL:
        {
            mConnections[handle].reset(new MySqlDatabaseConnection(conparams));
        } break;
#endif

#ifdef POSTGRESQLDB
        case _DB_CONNECTION_TYPE_POSTGRESQL:
        {
            mConnections[handle].reset(new PostgreSqlDatabaseConnection(conparams));
        } break;
#endif

        default:
        {
            std::stringstream message;
            message << "Invalid connection type specified: ";
            message << type;
            message << ".";
        
            throw DatabaseInvalidConnectionTypeException(message.str());
        }
    
    }
    
    return (handle + 1);
}

bool dish::DbConnectionFactory::IsOpen(const dish::IntegerT &handle)
{
    const IntegerT adjhandle(handle - 1);

    if((adjhandle >= 0) && (adjhandle < static_cast< IntegerT >(mConnections.size())))
    {
        if(0 != mConnections[adjhandle].get())
        {
            return mConnections[adjhandle]->IsOpen();
        }
        
        return false;
    }

    std::stringstream message;
    message << "Invalid database-connection handle specified: ";
    message << handle;
    message << ".";
    
    throw DatabaseInvalidHandleException(message.str());
}

dish::IntegerT dish::DbConnectionFactory::NumOpenConnections(const dish::BooleanT &validate)
{
    IntegerT num(0);

    std::for_each(
        mConnections.begin(), mConnections.end(),
        [&](ConnectionListT::value_type &connection)
        {
            if(0 != connection.get())
            {
                if(validate)
                {
                    if(connection->IsOpen())
                    {
                        ++num;
                    }
                }
                else
                {
                    ++num;
                }
            }
        }
    );
    
    return num;
}

dish::iDbConnection &dish::DbConnectionFactory::operator[](const dish::IntegerT &handle)
{
    const IntegerT adjhandle(handle - 1);
    
    if((adjhandle >= 0) && (adjhandle < static_cast< IntegerT >(mConnections.size())))
    {
        if(0 != mConnections[adjhandle].get())
        {
            return *mConnections[adjhandle];
        }

        std::stringstream message;
        message << "Database-connection not open: handle ";
        message << handle;
        message << ".";
        
        throw DatabaseConnectionNotOpenException(message.str());
    }

    std::stringstream message;
    message << "Invalid database-connection handle specified: ";
    message << handle;
    message << ".";
    
    throw DatabaseInvalidHandleException(message.str());
}

void dish::DbConnectionFactory::CloseConnection(const dish::IntegerT &handle)
{
    const IntegerT adjhandle(handle - 1);
    
    if((adjhandle >= 0) && (adjhandle < static_cast< IntegerT >(mConnections.size())))
    {
        if(0 != mConnections[adjhandle].get())
        {
            mConnections[adjhandle].reset();
        }
        else
        {
            std::stringstream message;
            message << "Database-connection not open: handle ";
            message << handle;
            message << ".";
            
            throw DatabaseConnectionNotOpenException(message.str());
        }
    }
    else
    {
        std::stringstream message;
        message << "Invalid database-connection handle specified: ";
        message << handle;
        message << ".";
        
        throw DatabaseInvalidHandleException(message.str());
    }
}

void dish::DbConnectionFactory::CloseAllConnections()
{
    std::for_each(
        mConnections.begin(), mConnections.end(),
        [](ConnectionListT::value_type &connection)
        {
            connection.reset();
        }
    );
}

dish::DbConnectionFactory &dish::DbConnectionFactory::Instance()
{
    static DbConnectionFactory instance;
    
    return instance;
}

