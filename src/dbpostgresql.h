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

#ifndef DISH_DB_POSTGRESQL_H
#define DISH_DB_POSTGRESQL_H

#include "dishconfig.h"

#include <libpq-fe.h>

#include "atomics.h"
#include "db.h"
#include "inline.h"
#include "types.h"

namespace dish
{

    class PostgreSqlDatabaseConnection : public DbConnection
    {
        private:
            PGconn *mConnection;
            PGresult *mResult;
            
            StringT mConnectionString;
            
        protected:
            void checkConnectError(const std::string &msgtext);
            void checkQueryError(const std::string &msgtext);
            
            INLINE void destroyResult() { if(NULL != mResult) { PQclear(mResult); mResult = NULL; } };
        
        public:
            PostgreSqlDatabaseConnection(const iDbConnection::ConnectionParams &conparams);
            virtual ~PostgreSqlDatabaseConnection();
        
            //  From iDbConnection
            
            virtual IntegerT ConnectionType() const;
            
            virtual Version ServerVersion();
            
            virtual BooleanT IsOpen();
            
            virtual std::shared_ptr< iAtomic > IssueQuery(const StringT &query);
        
    };

}

#endif

