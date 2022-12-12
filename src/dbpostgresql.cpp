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

#include <cassert>
#include <sstream>

#include "dbpostgresql.h"

/******************************************************************************

    dish::PostgreSqlDatabaseConnection definitions

 ******************************************************************************/

void dish::PostgreSqlDatabaseConnection::checkConnectError(const std::string &msgtext)
{
    if(NULL != mConnection)
    {
        switch(PQstatus(mConnection))
        {
            case CONNECTION_OK:
            {
                return;
            }
            
            case CONNECTION_BAD:
            {
                std::stringstream message;
                message << msgtext;
                message << " (";
                message << mConnectionString;
                message << "): ";
                message << PQerrorMessage(mConnection);
                message << ".";
            
                throw DatabaseUnableToOpenConnectionException(message.str());
            }
        
            default:
            {
                std::stringstream message;
                message << msgtext;
                message << " (";
                message << mConnectionString;
                message << "): ";
                message << PQerrorMessage(mConnection);
                message << ".";
            
                throw DatabaseUnknownException(message.str());
            }
            
        }
        
        assert(false);
    }
    
    std::stringstream message;
    message << msgtext;
    message << " (";
    message << mConnectionString;
    message << ").";
                
    throw DatabaseUnableToOpenConnectionException(message.str());
}

void dish::PostgreSqlDatabaseConnection::checkQueryError(const std::string &msgtext)
{
    if(NULL != mResult)
    {
        switch(PQresultStatus(mResult))
        {
            case PGRES_TUPLES_OK:
            {
                return;
            }
        
            default:
            {
                std::stringstream message;
                message << "An unknown database error occurred: ";
                message << PQerrorMessage(mConnection);
                message << ".";
            
                throw DatabaseUnknownException(message.str());
            }
            
        }
        
        assert(false);
    }
    
    //  Error
}

dish::PostgreSqlDatabaseConnection::PostgreSqlDatabaseConnection(const dish::iDbConnection::ConnectionParams &conparams) : dish::DbConnection(),
    mConnection(NULL),
    mResult(NULL),
    mConnectionString()
{
    std::stringstream connstr;
    connstr << "host=" << conparams.GetHost();
    
    if(conparams.GetPort() > 0)
    {
        connstr << " port=" << conparams.GetPort();
    }
    
    if(!conparams.GetUserName().empty())
    {
        connstr << " user=" << conparams.GetUserName();
    }
    
    if(!conparams.GetPassword().empty())
    {
        connstr << " password=" << conparams.GetPassword();
    }
    
    if(!conparams.GetDatabaseName().empty())
    {
        connstr << " dbname=" << conparams.GetDatabaseName();
    }
    
    if(conparams.GetTimeout() >= 0)
    {
        connstr << " connect_timeout=" << conparams.GetTimeout();
    }

    mConnectionString = connstr.str();
    mConnection = PQconnectdb(mConnectionString.c_str());
    checkConnectError("Unable to open connection to database");
}

dish::PostgreSqlDatabaseConnection::~PostgreSqlDatabaseConnection()
{
    destroyResult();
    
    if(NULL != mConnection)
    {
        PQfinish(mConnection);
        mConnection = NULL;
    }
}

dish::IntegerT dish::PostgreSqlDatabaseConnection::ConnectionType() const
{
    return DbConnectionFactory::DB_CONNECTION_TYPE_POSTGRESQL;
}

Version dish::PostgreSqlDatabaseConnection::ServerVersion()
{
    //  Make sure the connection is open.
    checkConnectError("Connection to PostgreSQL server not open");
    
    //  Get the version of the server.
    const int version(PQserverVersion(mConnection));
    
    return Version(
        (version / 10000),
        (version / 100) % 100,
        version % 100
    );
}
 
dish::BooleanT dish::PostgreSqlDatabaseConnection::IsOpen()
{
    if(NULL != mConnection)
    {
        PGresult * const result(PQexec(mConnection, "SELECT 1"));
        const bool open(PGRES_TUPLES_OK == PQresultStatus(result));
        
        PQclear(result);
        
        return open;
    }

    return false;
}

std::shared_ptr< dish::iAtomic > dish::PostgreSqlDatabaseConnection::IssueQuery(const dish::StringT &query)
{
    //  Make sure the connection is open.
    checkConnectError("Connection to PostgreSQL server not open");
    
    //  Destroy the PostgreSQL result-set.
    destroyResult();

    //  Execute the query.
    mResult = PQexec(mConnection, query.c_str());
    checkQueryError("Error executing query");

    try
    {
        //  Create a result-set in dish-space.
        std::shared_ptr< DbResultSet > resultset(DbResultSet::MakeValue());
    
        //  Get the dimensions of the result-set.
        const int nrows(PQntuples(mResult));
        const int ncols(PQnfields(mResult));
        
        //  Add the column names from the query result to the dish-space result
        //  set.
        for(int col(0); col < ncols; ++col)
        {
            resultset->AddColumn(PQfname(mResult, col), col);
        }
        
        //  Iterare through the rows in the result-set, adding a row to the Dish
        //  result-set for each row in the MySQL result-set.
        for(int row(0); row < nrows; ++row)
        {
            //  Create a new row in dish-space.
            std::shared_ptr< DbRowValue > resultrow(resultset->MakeRow());
        
            //  Iterate through the columns in the result row.
            for(int col(0); col < ncols; ++col)
            {
                const char * const cell(PQgetvalue(mResult, row, col));
            
                if(NULL != cell)
                {
                    resultrow->Add(StringValue::MakeValue(cell));
                }
                else
                {
                    resultrow->Add(NullValue::MakeValue());
                }
            }
            
            //  Add the new dish-space row to the dish-space result-set.
            resultset->Add(resultrow);
        }
    
        //  Destroy the PostgreSQL result-set.
        destroyResult();
        
        //  Lock the result-set.
        resultset->Lock();
        
        return resultset;
    }
    
    catch(...)
    {
        //  Destroy the PostgreSQL result-set.
        destroyResult();
        
        throw;
    }
    
    assert(false);
}

