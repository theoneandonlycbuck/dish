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

#ifndef DISH_LANGNET_H
#define DISH_LANGNET_H

#include "dishconfig.h"

#include <memory>
#include <string>
#include <vector>

#include <netinet/in.h>
#include <stdint.h>

#include "atomics.h"
#include "inline.h"
#include "language.h"
#include "symtab.h"

namespace dish
{

    ////////////////////////////////////////////////////////////////////////////
    
    class SocketList
    {
        public:
        
            typedef enum
            {
                ipvNull = 0,
                
                ipv4,
                ipv6,
                
                ipvName
            } IpvT;
        
            class iNetworkConnection
            {
                public:
                    virtual ~iNetworkConnection() {};
                    
                    virtual void Open() = 0;
                    virtual bool IsOpen() const = 0;
                    virtual void Close() = 0;
                    
                    virtual bool IsClient() const = 0;
                    virtual bool IsServer() const = 0;
                    
                    virtual void Send(const std::string &str) = 0;
                    virtual std::string Receive(const int nbytes) = 0;
                    virtual std::string Receive(const std::string &sentinal) = 0;
                
            };
            
            class NetworkConnection : public iNetworkConnection
            {
                protected:
                    void send(const int &fd, const std::string &str);
                    std::string receive(const int &fd, const int nbytes);
                    std::string receive(const int &fd, const std::string &sentinal);
            
                public:
                    
                    //  From iNetworkConnection
                    
                    virtual void Open();
                    virtual bool IsOpen() const;
                    virtual void Close();
                    
                    virtual void Send(const std::string &str);
                    virtual std::string Receive(const int nbytes);
                    virtual std::string Receive(const std::string &sentinal);
                    
            };
        
            class ClientNetworkConnection : public NetworkConnection
            {
                private:
                    const IpvT mIpV;
                    const std::string mName;
                    const int mPort;
                    
                    int mAddressFamily;
                    int mSocketFD;
                    
                public:
                    ClientNetworkConnection(const int &port);
                    ClientNetworkConnection(const std::string &name, const int &port);
                    ClientNetworkConnection(const IpvT &ipv, const std::string &name, const int &port);
                    
                    virtual ~ClientNetworkConnection() { Close(); };
                    
                    //  From iNetworkConnection
                    
                    virtual void Open();
                    virtual bool IsOpen() const;
                    virtual void Close();
                    
                    virtual bool IsClient() const { return true; };
                    virtual bool IsServer() const { return false; };
                    
                    virtual void Send(const std::string &str);
                    virtual std::string Receive(const int nbytes);
                    virtual std::string Receive(const std::string &sentinal);
                
            };
        
            class ServerNetworkConnection : public NetworkConnection
            {
                private:
                    const int mPort;
                    
                    int mSocketFD;
                    int mConnectionFD;
                    
                    struct sockaddr_in mClientSocket;
                    socklen_t mClientSocketLength;
                
                public:
                
                    static const int NUM_QUEUED_CONNECTIONS;
                
                    ServerNetworkConnection(const int &port);
                    
                    virtual ~ServerNetworkConnection() { Close(); };
                    
                    //  From iNetworkConnection
                    
                    virtual void Open();
                    virtual bool IsOpen() const;
                    virtual void Close();
                    
                    virtual bool IsClient() const { return false; };
                    virtual bool IsServer() const { return true; };
                    
                    virtual void Send(const std::string &str);
                    virtual std::string Receive(const int nbytes);
                    virtual std::string Receive(const std::string &sentinal);
                
            };
        
            typedef std::vector< std::shared_ptr< iNetworkConnection > > SocketListT;
            
            static const SocketListT::size_type MAX_OPEN_SOCKETS;
    
        private:
            SocketListT mOpenSockets;
            IntegerT mNumOpenSockets;
        
        protected:
            INLINE SocketList() : mOpenSockets(MAX_OPEN_SOCKETS, 0), mNumOpenSockets(0) {};
        
        public:
            INLINE ~SocketList() { Close(); };
            
            static SocketList &Instance();
            
            IntegerT OpenClient(const int port);
            IntegerT OpenClient(const std::string &name, const int port);
            IntegerT OpenClient(const IpvT &ipv, const std::string &name, const int port);
            
            IntegerT OpenServer(const int port);
            
            bool IsOpen(const IntegerT &handle);
            
            const IntegerT &NumOpen() const { return mNumOpenSockets; };
            IntegerT NumOpenClient() const;
            IntegerT NumOpenServer() const;
            
            void Send(const IntegerT &handle, const StringT &data);
            
            StringT Receive(const IntegerT &handle, const IntegerT &nchars);
            StringT Receive(const IntegerT &handle, const StringT &delimiter);
            
            void Close(const IntegerT &handle);
            void Close();
        
    };

    ////////////////////////////////////////////////////////////////////////////
    
    class NetworkOpenClientSocketFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE NetworkOpenClientSocketFunction() : dish::ExecutableAtomic() { addParam("port", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< NetworkOpenClientSocketFunction > MakeValue() { return std::shared_ptr< NetworkOpenClientSocketFunction >(new NetworkOpenClientSocketFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class NetworkOpenClientSocket2Function : public dish::ExecutableAtomic
    {
        protected:
            INLINE NetworkOpenClientSocket2Function() : dish::ExecutableAtomic() { addParam("host", REFERENCE_PARAMETER); addParam("port", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< NetworkOpenClientSocket2Function > MakeValue() { return std::shared_ptr< NetworkOpenClientSocket2Function >(new NetworkOpenClientSocket2Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class NetworkOpenClientSocket3Function : public dish::ExecutableAtomic
    {
        protected:
            INLINE NetworkOpenClientSocket3Function() : dish::ExecutableAtomic() { addParam("ipv", REFERENCE_PARAMETER); addParam("host", REFERENCE_PARAMETER); addParam("port", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< NetworkOpenClientSocket3Function > MakeValue() { return std::shared_ptr< NetworkOpenClientSocket3Function >(new NetworkOpenClientSocket3Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class NetworkOpenServerSocketFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE NetworkOpenServerSocketFunction() : dish::ExecutableAtomic() { addParam("port", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< NetworkOpenServerSocketFunction > MakeValue() { return std::shared_ptr< NetworkOpenServerSocketFunction >(new NetworkOpenServerSocketFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class NetworkNumOpenSocketsFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE NetworkNumOpenSocketsFunction() : dish::ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< NetworkNumOpenSocketsFunction > MakeValue() { return std::shared_ptr< NetworkNumOpenSocketsFunction >(new NetworkNumOpenSocketsFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class NetworkNumOpenClientSocketsFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE NetworkNumOpenClientSocketsFunction() : dish::ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< NetworkNumOpenClientSocketsFunction > MakeValue() { return std::shared_ptr< NetworkNumOpenClientSocketsFunction >(new NetworkNumOpenClientSocketsFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class NetworkNumOpenServerSocketsFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE NetworkNumOpenServerSocketsFunction() : dish::ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< NetworkNumOpenServerSocketsFunction > MakeValue() { return std::shared_ptr< NetworkNumOpenServerSocketsFunction >(new NetworkNumOpenServerSocketsFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class NetworkReadSocketFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE NetworkReadSocketFunction() : dish::ExecutableAtomic() { addParam("handle", REFERENCE_PARAMETER); addParam("end", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< NetworkReadSocketFunction > MakeValue() { return std::shared_ptr< NetworkReadSocketFunction >(new NetworkReadSocketFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };
    
    class NetworkWriteSocketFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE NetworkWriteSocketFunction() : dish::ExecutableAtomic() { addParam("handle", REFERENCE_PARAMETER); addParam("data", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< NetworkWriteSocketFunction > MakeValue() { return std::shared_ptr< NetworkWriteSocketFunction >(new NetworkWriteSocketFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class NetworkCloseSocketFunction : public dish::ExecutableAtomic
    {
        protected:
            INLINE NetworkCloseSocketFunction() : dish::ExecutableAtomic() {};
            
        public:
            
            static INLINE std::shared_ptr< NetworkCloseSocketFunction > MakeValue() { return std::shared_ptr< NetworkCloseSocketFunction >(new NetworkCloseSocketFunction()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    class NetworkCloseSocket1Function : public dish::ExecutableAtomic
    {
        protected:
            INLINE NetworkCloseSocket1Function() : dish::ExecutableAtomic() { addParam("handle", REFERENCE_PARAMETER); };
            
        public:
            
            static INLINE std::shared_ptr< NetworkCloseSocket1Function > MakeValue() { return std::shared_ptr< NetworkCloseSocket1Function >(new NetworkCloseSocket1Function()); };
                
            //  From iAtomic
            
            virtual std::shared_ptr< iAtomic > Execute(LanguageSymbolTable &symtab) const;
                    
    };

    ////////////////////////////////////////////////////////////////////////////

}

#endif

