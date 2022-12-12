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

#include <errmsg.h>

#include <cassert>
#include <cstdlib>
#include <sstream>

#include "dbmysql.h"
#include "version.h"

/******************************************************************************

    dish::MySqlDatabaseConnection definitions

 ******************************************************************************/
 
std::string dish::MySqlDatabaseConnection::formatError(const std::string &msgtext, const int errcode, const std::string &errmsg)
{
    std::stringstream message;
    message << msgtext;
    message << " (";
    message << errcode;
    message << "): ";
    message << errmsg;
    message << ".";
    
    return message.str();
}
 
void dish::MySqlDatabaseConnection::checkError(const int error)
{
    switch(error)
    {
        case 0:
        {
            return;
        }
    
        case CR_UNKNOWN_ERROR:
        {
            throw DatabaseUnknownException(
                formatError("An unknown database error occurred", error, mysql_error(&mConnection))
            );
        }
        
        case CR_SOCKET_CREATE_ERROR:
        case CR_CONNECTION_ERROR:
        case CR_CONN_HOST_ERROR:
        case CR_IPSOCK_ERROR:
        case CR_UNKNOWN_HOST:
        {
            throw DatabaseUnableToOpenConnectionException(
                formatError("An error connecting to database server occurred", error, mysql_error(&mConnection))
            );
        }
    
        case CR_SERVER_GONE_ERROR:
        {
            throw DatabaseConnectionDroppedException(
                formatError("The connection to the database server was dropped", error, mysql_error(&mConnection))
            );
        }
        
        case CR_VERSION_ERROR:
        case CR_OUT_OF_MEMORY:
        case CR_WRONG_HOST_INFO:
        {
            throw DatabaseInternalErrorException(
                formatError("An internal database error occurred", error, mysql_error(&mConnection))
            );
        }
        
        case CR_LOCALHOST_CONNECTION:
        case CR_TCP_CONNECTION:
        case CR_SERVER_HANDSHAKE_ERR:
        case CR_SERVER_LOST:
        {
            throw DatabaseConnectionDroppedException(
                formatError("An error connecting to database server occurred", error, mysql_error(&mConnection))
            );
        }
        
        case CR_COMMANDS_OUT_OF_SYNC:
        {
            throw DatabaseInternalErrorException(
                formatError("An internal database error occurred", error, mysql_error(&mConnection))
            );
        }
        
        case CR_NAMEDPIPE_CONNECTION:
        {
            throw DatabaseUnableToOpenConnectionException(
                formatError("An error connecting to database server occurred", error, mysql_error(&mConnection))
            );
        }
        
        case CR_NAMEDPIPEWAIT_ERROR:
        case CR_NAMEDPIPEOPEN_ERROR:
        case CR_NAMEDPIPESETSTATE_ERROR:
        {
            throw DatabaseConnectionDroppedException(
                formatError("An error connecting to database server occurred", error, mysql_error(&mConnection))
            );
        }
    
        case CR_CANT_READ_CHARSET:
        case CR_NET_PACKET_TOO_LARGE:
        {
            throw DatabaseInternalErrorException(
                formatError("An internal database error occurred", error, mysql_error(&mConnection))
            );
        }
    
        case CR_EMBEDDED_CONNECTION:
        {
            throw DatabaseUnableToOpenConnectionException(
                formatError("An error connecting to database server occurred", error, mysql_error(&mConnection))
            );
        }
    
        case CR_PROBE_SLAVE_STATUS:
        case CR_PROBE_SLAVE_HOSTS:
        {
            throw DatabaseInternalErrorException(
                formatError("An internal database error occurred", error, mysql_error(&mConnection))
            );
        }
    
        case CR_PROBE_SLAVE_CONNECT:
        case CR_PROBE_MASTER_CONNECT:
        case CR_SSL_CONNECTION_ERROR:
        {
            throw DatabaseUnableToOpenConnectionException(
                formatError("An error connecting to database server occurred", error, mysql_error(&mConnection))
            );
        }
    
        case CR_MALFORMED_PACKET:
        case CR_WRONG_LICENSE:
        case CR_NULL_POINTER:
        {
            throw DatabaseInternalErrorException(
                formatError("An internal database error occurred", error, mysql_error(&mConnection))
            );
        }
    
        case CR_NO_PREPARE_STMT:
        case CR_PARAMS_NOT_BOUND:
        case CR_DATA_TRUNCATED:
        case CR_NO_PARAMETERS_EXISTS:
        case CR_INVALID_PARAMETER_NO:
        case CR_INVALID_BUFFER_USE:
        case CR_UNSUPPORTED_PARAM_TYPE:
        {
            throw DatabaseQueryErrorException(
                formatError("A database query error occurred", error, mysql_error(&mConnection))
            );
        }
    
        case CR_SHARED_MEMORY_CONNECTION:
        case CR_SHARED_MEMORY_CONNECT_REQUEST_ERROR:
        case CR_SHARED_MEMORY_CONNECT_ANSWER_ERROR:
        case CR_SHARED_MEMORY_CONNECT_FILE_MAP_ERROR:
        case CR_SHARED_MEMORY_CONNECT_MAP_ERROR:
        {
            throw DatabaseUnableToOpenConnectionException(
                formatError("An error connecting to database server occurred", error, mysql_error(&mConnection))
            );
        }
    
        case CR_SHARED_MEMORY_FILE_MAP_ERROR:
        case CR_SHARED_MEMORY_MAP_ERROR:
        case CR_SHARED_MEMORY_EVENT_ERROR:
        case CR_SHARED_MEMORY_CONNECT_ABANDONED_ERROR:
        case CR_SHARED_MEMORY_CONNECT_SET_ERROR:
        {
            throw DatabaseConnectionDroppedException(
                formatError("An error connecting to database server occurred", error, mysql_error(&mConnection))
            );
        }
    
        case CR_CONN_UNKNOW_PROTOCOL:
        case CR_INVALID_CONN_HANDLE:
        //case CR_SECURE_AUTH:
        case CR_FETCH_CANCELED:
        {
            throw DatabaseInternalErrorException(
                formatError("An internal database error occurred", error, mysql_error(&mConnection))
            );
        }
    
        case CR_NO_DATA:
        case CR_NO_STMT_METADATA:
        case CR_NO_RESULT_SET:
        {
            throw DatabaseQueryErrorException(
                formatError("A database query error occurred", error, mysql_error(&mConnection))
            );
        }
    
        case CR_NOT_IMPLEMENTED:
        {
            throw DatabaseFeatureNotSupportedException(
                formatError("Feature not implemented", error, mysql_error(&mConnection))
            );
        }
    
        case CR_SERVER_LOST_EXTENDED:
        {
            throw DatabaseConnectionDroppedException(
                formatError("An error connecting to database server occurred", error, mysql_error(&mConnection))
            );
        }
    
        case CR_STMT_CLOSED:
        case CR_NEW_STMT_METADATA:
        {
            throw DatabaseQueryErrorException(
                formatError("A database query error occurred", error, mysql_error(&mConnection))
            );
        }
    
        case CR_ALREADY_CONNECTED:
        {
            throw DatabaseConnectionAlreadyOpenException(
                formatError("The database connection is already open", error, mysql_error(&mConnection))
            );
        }
    
        case CR_AUTH_PLUGIN_CANNOT_LOAD:
        {
            throw DatabaseInternalErrorException(
                formatError("An internal database error occurred", error, mysql_error(&mConnection))
            );
        }
        
        default:
        {
            std::stringstream message;
            message << "An unknown database error occurred: ";
            message << mysql_error(&mConnection);
            message << ".";
        
            throw DatabaseUnknownException(message.str());
        }
        
    }
    
    assert(false);
}

dish::MySqlDatabaseConnection::MySqlDatabaseConnection(const dish::iDbConnection::ConnectionParams &conparams) : dish::DbConnection(),
    mConnection()
{
    //  Initialize the MySQL connection object.
    mysql_init(&mConnection);
    
    //  Connect to the MySQL server.
    const MYSQL * const result(
        mysql_real_connect(
            &mConnection, 
            conparams.GetHost().c_str(), 
            conparams.GetUserName().c_str(), 
            conparams.GetPassword().c_str(), 
            conparams.GetDatabaseName().c_str(), 
            conparams.GetPort(), 
            NULL, 
            0
        )
    );
    
    //  Check for a connection-error.
    if(NULL == result)
    {
        throw DatabaseUnableToOpenConnectionException(
            formatError("Unable to open connection to database", mysql_errno(&mConnection), mysql_error(&mConnection))
        );
    }
}

dish::MySqlDatabaseConnection::~MySqlDatabaseConnection()
{
    mysql_close(&mConnection);
}

dish::IntegerT dish::MySqlDatabaseConnection::ConnectionType() const
{
    return DbConnectionFactory::DB_CONNECTION_TYPE_MYSQL;
}

Version dish::MySqlDatabaseConnection::ServerVersion()
{
    std::stringstream input(
        mysql_get_server_info(&mConnection)
    );
    
    int major;
    input >> major;
    
    input.get();
    
    int minor;
    input >> minor;
    
    input.get();
    
    int revision;
    input >> revision;
    
    return Version(major, minor, revision);
}
 
dish::BooleanT dish::MySqlDatabaseConnection::IsOpen()
{
    const int result(
        mysql_ping(&mConnection)
    );
    
    if(CR_SERVER_GONE_ERROR != result)
    {
        return (0 == result);
    }
    
    return false;
}

std::shared_ptr< dish::iAtomic > dish::MySqlDatabaseConnection::IssueQuery(const dish::StringT &query)
{
    //  Execute the query.
    checkError(
        mysql_query(&mConnection, query.c_str())
    );
    
    //  Get the result-set from the query.
    MYSQL_RES *result(mysql_store_result(&mConnection)); 
    
    //  Is there a result-set?
    if(NULL != result)
    {
        //  Yes, we have a result-set. Create a result-set in dish-space.
        std::shared_ptr< DbResultSet > resultset(DbResultSet::MakeValue());
        
        //  How many columns are in the result?
        const int ncolumns(mysql_num_fields(result));
        assert(ncolumns > 0);
        
        //  Add the column names from the query result to the dish-space result
        //  set.
        {
            const MYSQL_FIELD * const fields(mysql_fetch_fields(result));
        
            if(NULL != fields)
            {
                for(int col(0); col < ncolumns; ++col)
                {
                    resultset->AddColumn(fields[col].name, col);
                }
            }
        }
        
        //  Iterate through the ros in the result-set, adding a row to the Dish
        //  result-set for each row in the MySQL result-set.
        for(MYSQL_ROW row; (row = mysql_fetch_row(result)); )
        {
            //  Create a new row in dish-space.
            std::shared_ptr< DbRowValue > resultrow(resultset->MakeRow());
            
            //  Iterate through the columns in the MySQL row.
            for(int i(0); i < ncolumns; ++i)
            {
                if(NULL != row[i])
                {
                    resultrow->Add(StringValue::MakeValue(row[i]));
                }
                else
                {
                    resultrow->Add(NullValue::MakeValue());
                }
            }
            
            //  Add the new dish-space row to the dish-space result-set.
            resultset->Add(resultrow);
        }
        
        //  Destroy the MySQL result-set.
        mysql_free_result(result);
        
        //  Lock the result-set.
        resultset->Lock();
        
        return resultset;
    }
    
    //  No, should there have been?
    else if(0 == mysql_field_count(&mConnection))
    {
        //  No, return a null value.
        return NullValue::MakeValue();
    }

    //  Yes, something should have been returned; thow a run-time exception.
    throw DatabaseQueryErrorException(
        formatError("Query should have returned results but did not", mysql_errno(&mConnection), mysql_error(&mConnection))
    );
}

