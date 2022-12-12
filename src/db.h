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

#ifndef DISH_DB_H
#define DISH_DB_H

#include "dishconfig.h"

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "atomics.h"
#include "exception.h"
#include "inline.h"
#include "types.h"
#include "version.h"

namespace dish
{

    ////////////////////////////////////////////////////////////////////////////
    
    class DbRowValue;

    ////////////////////////////////////////////////////////////////////////////
    
    class DbResultSet : public ArrayValue
    {
        public:
            
            class ContainsMethod : public ExecutableAtomic
            {
                private:
                    const DbResultSet &mThis;
                    
                protected:
                    INLINE const DbResultSet &thisValue() const { return mThis; };
                    
                    INLINE ContainsMethod(const DbResultSet &this_ref) : ExecutableAtomic(), mThis(this_ref) { addParam("str", dish::REFERENCE_PARAMETER); };
                
                public:
                
                    static INLINE std::shared_ptr< ContainsMethod > MakeValue(const DbResultSet &this_ref) { return std::shared_ptr< ContainsMethod >(new ContainsMethod(this_ref)); };
                    
                    //  From iAtomic
                    
                    virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                
            };
        
            using ColNameIndexT = std::map< StringT, IntegerT >;
    
        private:
            ColNameIndexT mColNameIndexMap;
            
            mutable std::shared_ptr< iAtomic > mContainsF;
    
        public:
            INLINE DbResultSet() : ArrayValue(0), mColNameIndexMap(), mContainsF() {};
            virtual ~DbResultSet();
            
            void AddColumn(const StringT &colname, const IntegerT &index);
            
            std::shared_ptr< DbRowValue > MakeRow();
            
            static INLINE std::shared_ptr< DbResultSet > MakeValue() { return std::shared_ptr< DbResultSet >(new DbResultSet()); };
            
            //  From ArrayValue
            
            virtual std::shared_ptr< iAtomic > Member(const std::string &member) const;
            
            virtual std::shared_ptr< iAtomic > Keys() const;
            
            virtual std::shared_ptr< iAtomic > Lookup(const StringT &key) const;
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class DbRowValue : public ArrayValue
    {
        public:
            
            class ContainsMethod : public ExecutableAtomic
            {
                private:
                    const DbRowValue &mThis;
                    
                    mutable std::shared_ptr< iAtomic > mContainsF;
                    
                protected:
                    INLINE const DbRowValue &thisValue() const { return mThis; };
                    
                    INLINE ContainsMethod(const DbRowValue &this_ref) : ExecutableAtomic(), mThis(this_ref) { addParam("str", dish::REFERENCE_PARAMETER); };
                
                public:
                
                    static INLINE std::shared_ptr< ContainsMethod > MakeValue(const DbRowValue &this_ref) { return std::shared_ptr< ContainsMethod >(new ContainsMethod(this_ref)); };
                    
                    //  From iAtomic
                    
                    virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                
            };
    
        private:
            const DbResultSet::ColNameIndexT &mColNameIndexMap;
            
            mutable std::shared_ptr< iAtomic > mContainsF;
    
        public:
            INLINE DbRowValue(const DbResultSet::ColNameIndexT &colnmindex) : ArrayValue(0), mColNameIndexMap(colnmindex), mContainsF() {};
            
            static INLINE std::shared_ptr< DbRowValue > MakeValue(const DbResultSet::ColNameIndexT &colnmindex) { return std::shared_ptr< DbRowValue >(new DbRowValue(colnmindex)); };
            
            //  From ArrayValue
            
            virtual std::shared_ptr< iAtomic > Member(const std::string &member) const;
            
            virtual std::shared_ptr< iAtomic > Keys() const;
            
            virtual std::shared_ptr< iAtomic > Lookup(const StringT &key) const;
            
            virtual void Print(std::ostream &out, const std::string::size_type &indent = 0) const;
        
    };

    ////////////////////////////////////////////////////////////////////////////

    class iDbConnection
    {
        public:
            
            class ConnectionParams
            {
                private:
                    StringT mHost;
                    IntegerT mPort;
                    
                    StringT mUserName;
                    StringT mPassword;
                    
                    StringT mDatabaseName;
                    
                    IntegerT mTimeout;
                    
                public:
                    ConnectionParams();
                    ConnectionParams(const StringT &host, const IntegerT &port, const StringT &uname, const StringT &passwd, const StringT &dbname, const IntegerT &timeout);
                    ConnectionParams(const ConnectionParams &params);
                
                    const ConnectionParams &operator=(const ConnectionParams &rhs);
                    
                    INLINE const StringT &GetHost() const { return mHost; };
                    INLINE void SetHost(const StringT &host) { mHost = (!host.empty()) ? host : "127.0.0.1"; };
                    
                    INLINE const IntegerT &GetPort() const { return mPort; };
                    INLINE void SetPort(const IntegerT &port) { mPort = (port >= 0) ? port : 0; };
                    
                    INLINE const StringT &GetUserName() const { return mUserName; };
                    INLINE void SetUserName(const StringT &uname) { mUserName = uname; };
                    
                    INLINE const StringT &GetPassword() const { return mPassword; };
                    INLINE void SetPassword(const StringT &passwd) { mPassword = passwd; };
                    
                    INLINE const StringT &GetDatabaseName() const { return mDatabaseName; };
                    INLINE void SetDatabaseName(const StringT &dbname) { mDatabaseName = dbname; };
                    
                    INLINE const IntegerT &GetTimeout() const { return mTimeout; };
                    INLINE void SetTimeout(const IntegerT &timeout) { mTimeout = (timeout >= 0) ? timeout : 0; };
                
            };
            
            virtual ~iDbConnection() {};
            
            virtual IntegerT ConnectionType() const = 0;
            
            virtual Version ServerVersion() = 0;
            
            virtual BooleanT IsOpen() = 0;
            
            virtual std::shared_ptr< iAtomic > IssueQuery(const StringT &query) = 0;
        
    };
    
    class DbConnection : public iDbConnection
    {
        public:
            INLINE DbConnection() : iDbConnection() {};
        
            //  From iDbConnection
            
            virtual IntegerT ConnectionType() const;
            
            virtual Version ServerVersion();
            
            virtual BooleanT IsOpen();
            
            virtual std::shared_ptr< iAtomic > IssueQuery(const StringT &query);
            
    };

    ////////////////////////////////////////////////////////////////////////////
    
    #define _DB_CONNECTION_TYPE_MYSQL       0
    #define _DB_CONNECTION_TYPE_POSTGRESQL  1
    
    class DbConnectionFactory
    {
        public:
        
            using ConnectionListT = std::vector< std::shared_ptr< iDbConnection > >;
            
            static const IntegerT DB_CONNECTION_TYPE_MYSQL;
            static const IntegerT DB_CONNECTION_TYPE_POSTGRESQL;
            
            static const IntegerT DB_MAX_CONNECTIONS;
    
        private:
            ConnectionListT mConnections;
        
        protected:
            INLINE DbConnectionFactory() : mConnections() { mConnections.resize(DB_MAX_CONNECTIONS); };
            
            IntegerT findAvailableHandle() const;
        
        public:
        
            IntegerT OpenConnection(const IntegerT &type, const iDbConnection::ConnectionParams &conparams);
            
            bool IsOpen(const IntegerT &handle);
            IntegerT NumOpenConnections(const BooleanT &validate = true);
            
            iDbConnection &operator[](const IntegerT &handle);
            
            void CloseConnection(const IntegerT &handle);
            void CloseAllConnections();
            
            static DbConnectionFactory &Instance();
        
    };

    ////////////////////////////////////////////////////////////////////////////

}

#endif

