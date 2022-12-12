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
#include <cstring>
#include <sstream>
#include <string>

#include <arpa/inet.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "langnet.h"
#include "utility.h"

namespace
{

    const int BUFFER_LEN(4096);
    
    std::string AddressFamilyToString(const int &af)
    {
        switch(af)
        {
            case AF_INET:
            {
                return "IPV4";
            };
            
            case AF_INET6:
            {
                return "IPV6";
            };
            
            default:
            {
            }
            
        }
        
        assert(false);
    }

}

/******************************************************************************

    dish::SocketList::NetworkConnection class definitions

 ******************************************************************************/

void dish::SocketList::NetworkConnection::send(const int &fd, const std::string &str)
{
    if(IsOpen())
    {
        const std::string::size_type nbytes(str.length());
    
        if(nbytes > 0)
        {
            const size_t result(write(fd, str.c_str(), nbytes));
            const int err(errno);
            
            if(result < static_cast< size_t >(nbytes))
            {
                std::stringstream message;
                message << "Error writing to socket";
                
                if(result >= 0)
                {
                    message << " (";
                    message << result;
                    message << " / ";
                    message << nbytes;
                    message << " sent).";
                }
                else
                {
                    char buffer[BUFFER_LEN] = { 0 };
                
                    message << ": ";
                    message << strerror_r(err, buffer, BUFFER_LEN - 1);
                    message << ".";
                }
            
                throw SocketWriteErrorException(message.str());
            }
        }
    }
    else
    {
        throw SocketNotOpenException("The socket is not open.");
    }
}

std::string dish::SocketList::NetworkConnection::receive(const int &fd, const int nbytes)
{
    if(IsOpen())
    {
        std::string str;

        for(bool done(false); !done; )
        {
            char buf[nbytes];
            std::memset(buf, '\0', nbytes);
        
            const size_t result(read(fd, buf, nbytes - str.length()));
            const int err(errno);
            
            if(result > 0)
            {
                str.append(buf, result);
                
                done = (static_cast< std::string::size_type >(nbytes) == str.length());
            }
            
            else if(result < 0)
            {
                char buffer[BUFFER_LEN] = { 0 };
                
                std::stringstream message;
                message << "Error reading from socket: ";
                message << strerror_r(err, buffer, BUFFER_LEN - 1);
                message << ".";
                
                throw SocketReadErrorException(message.str());
            }
            
            else
            {
                done = true;
            }
        }
        
        return str;
    }
    else
    {
        throw SocketNotOpenException("The socket is not open.");
    }
}

std::string dish::SocketList::NetworkConnection::receive(const int &fd, const std::string &sentinal)
{
    if(IsOpen())
    {
        std::string str;

        for(bool done(false); !done; )
        {
            char buf;
        
            const size_t result(read(fd, &buf, 1));
            const int err(errno);
            
            if(result > 0)
            {
                str.append(&buf, 1);
                
                done = EndsWith(str, sentinal, CASE_SENSITIVE);
            }
            
            else if(result < 0)
            {
                char buffer[BUFFER_LEN] = { 0 };
                
                std::stringstream message;
                message << "Error reading from socket: ";
                message << strerror_r(err, buffer, BUFFER_LEN - 1);
                message << ".";
                
                throw SocketReadErrorException(message.str());
            }
            
            else
            {
                done = true;
            }
        }
        
        return str;
    }
    else
    {
        throw SocketNotOpenException("The socket is not open.");
    }
}
                    
void dish::SocketList::NetworkConnection::Open()
{
    throw UnableToOpenSocketException("Unable to open socket (dish::SocketList::NetworkConnection::Open).");
}

bool dish::SocketList::NetworkConnection::IsOpen() const
{
    return false;
}

void dish::SocketList::NetworkConnection::Close()
{
    throw UnableToCloseSocketException("Unable to close socket (dish::SocketList::NetworkConnection::Close).");
}

void dish::SocketList::NetworkConnection::Send(const std::string &str)
{
    throw SocketWriteErrorException("Unable to write to socket (dish::SocketList::NetworkConnection::Send).");
}

std::string dish::SocketList::NetworkConnection::Receive(const int nbytes)
{
    throw SocketReadErrorException("Unable to receive from socket (dish::SocketList::NetworkConnection::Receive).");
}

std::string dish::SocketList::NetworkConnection::Receive(const std::string &sentinal)
{
    throw SocketReadErrorException("Unable to receive from socket (dish::SocketList::NetworkConnection::Receive).");
}

/******************************************************************************

    dish::SocketList::ClientNetworkConnection class definitions

 ******************************************************************************/

dish::SocketList::ClientNetworkConnection::ClientNetworkConnection(const int &port) : NetworkConnection(),
    mIpV(ipv4),
    mName("127.0.0.1"),
    
    mPort(port),
    
    mAddressFamily(AF_INET),
    mSocketFD(-1)
{
    assert(mPort >= 0);
}
 
dish::SocketList::ClientNetworkConnection::ClientNetworkConnection(const std::string &name, const int &port) : NetworkConnection(),
    mIpV(ipv4),
    mName(name),
    mPort(port),
    
    mAddressFamily(AF_INET),
    mSocketFD(-1)
{
    assert(mPort >= 0);
}
 
dish::SocketList::ClientNetworkConnection::ClientNetworkConnection(const IpvT &ipv, const std::string &name, const int &port) : NetworkConnection(),
    mIpV(ipv),
    mName(name),
    mPort(port),
    
    mAddressFamily(-1),
    mSocketFD(-1)
{
    assert(mPort >= 0);
    
    switch(mIpV)
    {
        case ipvNull:
        {
            assert(false);
        } break;
    
        case ipv4:
        {
            mAddressFamily = AF_INET;
        } break;
        
        case ipv6:
        {
            mAddressFamily = AF_INET6;
        } break;
        
        case ipvName:
        {
            assert(false);
        } break;
        
        default:
        {
            assert(false);
        }
        
    }
}

void dish::SocketList::ClientNetworkConnection::Open()
{
    //  Open the socket.
    {
        mSocketFD = socket(mAddressFamily, SOCK_STREAM, 0);
        const int err(errno);
        
        if(mSocketFD < 0)
        {
            char buffer[BUFFER_LEN] = { 0 };
        
            std::stringstream message;
            message << "Unable to open the socket: ";
            message << strerror_r(err, buffer, BUFFER_LEN - 1);
            message << ".";
        
            throw UnableToOpenSocketException(message.str());
        }
    }
    
    //  Populate the server connection information.
    struct sockaddr_in serveraddr = { 0 };
    serveraddr.sin_family = mAddressFamily;
    serveraddr.sin_port = htons(mPort);
    
    {
        const int result(
            inet_pton(
                mAddressFamily, 
                mName.c_str(), 
                &(serveraddr.sin_addr)
            )
        );
        const int err(errno);
        
        switch(result)
        {
            case -1:
            {
                char buffer[BUFFER_LEN] = { 0 };
        
                std::stringstream message;
                message << "An invalid ";
                message << AddressFamilyToString(mAddressFamily);
                message << " address was specified (";
                message << mName;
                message << "): ";
                message << strerror_r(err, buffer, BUFFER_LEN - 1);
                message << ".";
            
                throw SocketInvalidAddressException(message.str());
            };
            
            case 0:
            {
                char buffer[BUFFER_LEN] = { 0 };
        
                std::stringstream message;
                message << "An invalid ";
                message << AddressFamilyToString(mAddressFamily);
                message << " address was specified (";
                message << mName;
                message << "): ";
                message << strerror_r(err, buffer, BUFFER_LEN - 1);
                message << ".";
            
                throw SocketInvalidAddressException(message.str());
            };
            
            case 1:
            {
                //  Success!
            } break;
            
            default:
            {
                assert(false);
            }
        
        }
    }
    
    //  Connect to the server.
    {
        const int result(
            connect(
                mSocketFD,
                reinterpret_cast< struct sockaddr * >(&serveraddr),
                sizeof(serveraddr)
            )
        );
        const int err(errno);
        
        if(result < 0)
        {
            char buffer[BUFFER_LEN] = { 0 };
            
            std::stringstream message;
            message << "Unable to connect to server (";
            message << mName;
            message << "): ";
            message << strerror_r(err, buffer, BUFFER_LEN - 1);
            message << ".";
        
            throw SocketUnableToConnectToServerException(message.str());
        }
    }
}

bool dish::SocketList::ClientNetworkConnection::IsOpen() const
{
    return (mSocketFD >= 0);
}

void dish::SocketList::ClientNetworkConnection::Close()
{
    if(IsOpen())
    {
        if(0 != close(mSocketFD))
        {
            const int err(errno);
            char buffer[BUFFER_LEN] = { 0 };
            
            std::stringstream message;
            message << "Unable to close the socket: ";
            message << strerror_r(err, buffer, BUFFER_LEN - 1);
            message << ".";
        
            throw UnableToCloseSocketException(message.str());
        }
        
        mSocketFD = -1;
    }
}

void dish::SocketList::ClientNetworkConnection::Send(const std::string &str)
{
    send(mSocketFD, str);
}

std::string dish::SocketList::ClientNetworkConnection::Receive(const int nbytes)
{
    return receive(mSocketFD, nbytes);
}

std::string dish::SocketList::ClientNetworkConnection::Receive(const std::string &sentinal)
{
    return receive(mSocketFD, sentinal);
}

/******************************************************************************

    dish::SocketList::ServerNetworkConnection class definitions

 ******************************************************************************/
 
const int dish::SocketList::ServerNetworkConnection::NUM_QUEUED_CONNECTIONS(2);
 
dish::SocketList::ServerNetworkConnection::ServerNetworkConnection(const int &port) : NetworkConnection(),
    mPort(port),
    
    mSocketFD(-1),
    mConnectionFD(-1),
    
    mClientSocket(),
    mClientSocketLength(sizeof(struct sockaddr_in))
{
    assert(mPort >= 0);
}

void dish::SocketList::ServerNetworkConnection::Open()
{
    //  Open the socket.
    {
        mSocketFD = socket(AF_INET, SOCK_STREAM, 0);
        const int err(errno);
        
        if(mSocketFD < 0)
        {
            char buffer[BUFFER_LEN] = { 0 };
        
            std::stringstream message;
            message << "Unable to open the socket: ";
            message << strerror_r(err, buffer, BUFFER_LEN - 1);
            message << ".";
        
            throw UnableToOpenSocketException(message.str());
        }
    }
    
    //  Populate the server connection information.
    struct sockaddr_in serveraddr = { 0 };
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(mPort);
    
    //  Bind the socket to the port.
    {
        const int result(
            bind(
                mSocketFD,
                reinterpret_cast< struct sockaddr * >(&serveraddr),
                sizeof(serveraddr)
            )
        );
        const int err(errno);
        
        if(0 != result)
        {
            char buffer[BUFFER_LEN] = { 0 };
            
            std::stringstream message;
            message << "Unable to open server socket: ";
            message << strerror_r(err, buffer, BUFFER_LEN - 1);
            message << ".";
        
            throw UnableToOpenSocketException(message.str());
        }
    }
    
    //  Start listening for connections.
    {
        const int result(listen(mSocketFD, NUM_QUEUED_CONNECTIONS));
        const int err(errno);
        
        if(0 != result)
        {
            char buffer[BUFFER_LEN] = { 0 };
            
            std::stringstream message;
            message << "Unable to open server socket: ";
            message << strerror_r(err, buffer, BUFFER_LEN - 1);
            message << ".";
        
            throw UnableToOpenSocketException(message.str());
        } 
    }
    
    //  Accept the next incomming connection. This is a blocking call and the 
    //  Open() method will not return until a connection is accepted.
    {
        const int result(
            accept(
                mSocketFD, 
                reinterpret_cast< struct sockaddr * >(&mClientSocket), 
                &mClientSocketLength
            )
        );
        const int err(errno);
        
        if(result >= 0)
        {
            mConnectionFD = result;
        }
        else
        {
            char buffer[BUFFER_LEN] = { 0 };
            
            std::stringstream message;
            message << "Unable to open server socket: ";
            message << strerror_r(err, buffer, BUFFER_LEN - 1);
            message << ".";
        
            throw UnableToOpenSocketException(message.str());
        } 
    }
}

bool dish::SocketList::ServerNetworkConnection::IsOpen() const
{
    return (mConnectionFD >= 0);
}

void dish::SocketList::ServerNetworkConnection::Close()
{
    if(IsOpen())
    {
        if(0 != close(mConnectionFD))
        {
            const int err(errno);
            char buffer[BUFFER_LEN] = { 0 };
            
            std::stringstream message;
            message << "Unable to close the socket: ";
            message << strerror_r(err, buffer, BUFFER_LEN - 1);
            message << ".";
        
            throw UnableToCloseSocketException(message.str());
        }
        mConnectionFD = -1;
        
        if(0 != close(mSocketFD))
        {
            const int err(errno);
            char buffer[BUFFER_LEN] = { 0 };
            
            std::stringstream message;
            message << "Unable to close the socket: ";
            message << strerror_r(err, buffer, BUFFER_LEN - 1);
            message << ".";
        
            throw UnableToCloseSocketException(message.str());
        }
        mSocketFD = -1;
    }
}

void dish::SocketList::ServerNetworkConnection::Send(const std::string &str)
{
    send(mConnectionFD, str);
}

std::string dish::SocketList::ServerNetworkConnection::Receive(const int nbytes)
{
    return receive(mConnectionFD, nbytes);
}

std::string dish::SocketList::ServerNetworkConnection::Receive(const std::string &sentinal)
{
    return receive(mConnectionFD, sentinal);
}

/******************************************************************************

    dish::SocketList class definitions

 ******************************************************************************/

const dish::SocketList::SocketListT::size_type dish::SocketList::MAX_OPEN_SOCKETS(50);

dish::SocketList &dish::SocketList::Instance()
{
    static SocketList instance;
    
    return instance;
}

dish::IntegerT dish::SocketList::OpenClient(const int port)
{
    return OpenClient(ipv4, "127.0.0.1", port);
}

dish::IntegerT dish::SocketList::OpenClient(const std::string &name, const int port)
{
    return OpenClient(ipv4, name, port);
}

dish::IntegerT dish::SocketList::OpenClient(const IpvT &ipv, const std::string &name, const int port)
{
    assert(port > 0);

    for(SocketListT::size_type i(0), last_i(mOpenSockets.size()); i != last_i; ++i)
    {
        if(0 == mOpenSockets[i].get())
        {
            mOpenSockets[i].reset(new ClientNetworkConnection(ipv, name, port));
            mOpenSockets[i]->Open();
            
            ++mNumOpenSockets;
            
            return i;
        }
    }
    
    throw TooManyOpenSocketsException("Too many open sockets.");
}

dish::IntegerT dish::SocketList::OpenServer(const int port)
{
    assert(port > 0);

    for(SocketListT::size_type i(0), last_i(mOpenSockets.size()); i != last_i; ++i)
    {
        if(0 == mOpenSockets[i])
        {
            mOpenSockets[i].reset(new ServerNetworkConnection(port));
            mOpenSockets[i]->Open();
        
            ++mNumOpenSockets;
            
            return i;
        }
    }
    
    throw TooManyOpenSocketsException("Too many open sockets.");
}

bool dish::SocketList::IsOpen(const dish::IntegerT &handle)
{
    if(handle < static_cast< IntegerT >(mOpenSockets.size()))
    {
        if(0 != mOpenSockets[handle].get())
        {
            return mOpenSockets[handle]->IsOpen();
        }
    }
    
    return false;
}

dish::IntegerT dish::SocketList::NumOpenClient() const
{
    IntegerT count(0);

    std::for_each(
        mOpenSockets.begin(), mOpenSockets.end(),
        [&](const SocketListT::value_type &sock)
        {
            if(0 != sock.get())
            {
                if(sock->IsOpen())
                {
                    if(sock->IsClient())
                    {
                        ++count;
                    }
                }
            }
        }
    );
    
    return count;
}

dish::IntegerT dish::SocketList::NumOpenServer() const
{
    IntegerT count(0);

    std::for_each(
        mOpenSockets.begin(), mOpenSockets.end(),
        [&](const SocketListT::value_type &sock)
        {
            if(0 != sock.get())
            {
                if(sock->IsOpen())
                {
                    if(sock->IsServer())
                    {
                        ++count;
                    }
                }
            }
        }
    );
    
    return count;
}

void dish::SocketList::Send(const dish::IntegerT &handle, const dish::StringT &data)
{
    if(handle < static_cast< IntegerT >(mOpenSockets.size()))
    {
        if(0 != mOpenSockets[handle].get())
        {
            mOpenSockets[handle]->Send(data);
        }
        else
        {
            throw SocketNotOpenException("The socket is not open.");
        }
    }
    else
    {
        throw IllegalHandleException("Illegal handle.");
    }
}

dish::StringT dish::SocketList::Receive(const dish::IntegerT &handle, const dish::IntegerT &nchars)
{
    if(handle < static_cast< IntegerT >(mOpenSockets.size()))
    {
        if(0 != mOpenSockets[handle].get())
        {
            return mOpenSockets[handle]->Receive(nchars);
        }
        
        throw SocketNotOpenException("The socket is not open.");
    }
    
    throw IllegalHandleException("Illegal handle.");
}

dish::StringT dish::SocketList::Receive(const dish::IntegerT &handle, const dish::StringT &delimiter)
{
    if(handle < static_cast< IntegerT >(mOpenSockets.size()))
    {
        if(0 != mOpenSockets[handle].get())
        {
            return mOpenSockets[handle]->Receive(delimiter);
        }
        
        throw SocketNotOpenException("The socket is not open.");
    }
    else
    {
        throw IllegalHandleException("Illegal handle.");
    }
}

void dish::SocketList::Close(const dish::IntegerT &handle)
{
    //  Is the handle valid?
    if(handle < static_cast< IntegerT >(mOpenSockets.size()))
    {
        //  Does the socket object the handle refers to exist?
        if(0 != mOpenSockets[handle].get())
        {
            //  Close the socket.
            mOpenSockets[handle]->Close();
            
            //  Destroy the socket object.
            mOpenSockets[handle].reset();

            //  Decrease the number of open sockets.            
            --mNumOpenSockets;
        }
        else
        {
            throw SocketNotOpenException("The socket is not open.");
        }
    }
    else
    {
        throw IllegalHandleException("Illegal handle.");
    }
}

void dish::SocketList::Close()
{
    std::for_each(
        mOpenSockets.begin(), mOpenSockets.end(),
        [&](SocketListT::value_type &sock)
        {
            if(0 != sock.get())
            {
                sock->Close();
                sock.reset();
            }
        }
    );
    
    mNumOpenSockets = 0;
}

/******************************************************************************

    dish::NetworkOpenClientSocketFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::NetworkOpenClientSocketFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return IntegerValue::MakeValue( 
        SocketList::Instance().OpenClient(
            static_cast< int >(getParam(symtab, "port")->AsInteger())
        )
    );
}

/******************************************************************************

    dish::NetworkOpenClientSocket2Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::NetworkOpenClientSocket2Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    return IntegerValue::MakeValue( 
        SocketList::Instance().OpenClient(
            getParam(symtab, "host")->AsString(),
            static_cast< int >(getParam(symtab, "port")->AsInteger())
        )
    );
}

/******************************************************************************

    dish::NetworkOpenClientSocket3Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::NetworkOpenClientSocket3Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    return IntegerValue::MakeValue( 
        SocketList::Instance().OpenClient(
            static_cast< SocketList::IpvT >(getParam(symtab, "ipv")->AsInteger()),
            getParam(symtab, "host")->AsString(),
            static_cast< int >(getParam(symtab, "port")->AsInteger())
        )
    );
}

/******************************************************************************

    dish::NetworkOpenServerSocketFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::NetworkOpenServerSocketFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return IntegerValue::MakeValue( 
        SocketList::Instance().OpenServer(
            static_cast< int >(getParam(symtab, "port")->AsInteger())
        )
    );
}

/******************************************************************************

    dish::NetworkNumOpenSocketsFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::NetworkNumOpenSocketsFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return IntegerValue::MakeValue(SocketList::Instance().NumOpen());
}

/******************************************************************************

    dish::NetworkNumOpenClientSocketsFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::NetworkNumOpenClientSocketsFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return IntegerValue::MakeValue(SocketList::Instance().NumOpenClient());
}

/******************************************************************************

    dish::NetworkNumOpenServerSocketsFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::NetworkNumOpenServerSocketsFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    return IntegerValue::MakeValue(SocketList::Instance().NumOpenServer());
}

/******************************************************************************

    dish::NetworkReadSocketFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::NetworkReadSocketFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    const IntegerT handle(getParam(symtab, "handle")->AsInteger());
    std::shared_ptr< dish::iAtomic > end(getParam(symtab, "end"));
    
    switch(end->Type())
    {
        case iAtomic::typeInteger:
        {
            return StringValue::MakeValue(
                SocketList::Instance().Receive(handle, end->AsInteger())
            );
        }
        
        case iAtomic::typeString:
        {
            return StringValue::MakeValue(
                SocketList::Instance().Receive(handle, end->AsString())
            );
        }
        
        default:
        {
            //  Empty
        }
        
    }
    
    throw IllegalTypeException("The 'end' parameter is not of type integer or string.");
}

/******************************************************************************

    dish::NetworkWriteSocketFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::NetworkWriteSocketFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    SocketList::Instance().Send(
        getParam(symtab, "handle")->AsInteger(), 
        getParam(symtab, "data")->AsString()
    );
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::NetworkCloseSocketFunction class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::NetworkCloseSocketFunction::Execute(dish::LanguageSymbolTable &symtab) const
{
    SocketList::Instance().Close();
    
    return NullValue::MakeValue();
}

/******************************************************************************

    dish::NetworkCloseSocket1Function class definitions

 ******************************************************************************/

std::shared_ptr< dish::iAtomic > dish::NetworkCloseSocket1Function::Execute(dish::LanguageSymbolTable &symtab) const
{
    SocketList::Instance().Close(getParam(symtab, "handle")->AsInteger());
    
    return NullValue::MakeValue();
}

