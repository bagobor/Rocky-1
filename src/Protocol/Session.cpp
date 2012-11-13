/**
 * This file is part of Rocky.
 *
 * Copyright (c) 2012, VolumetricPixels <http://www.volumetricpixels.com/>
 * Rocky is licensed under the GNU Lesser General Public License.
 *
 * Rocky is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Rocky is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <Protocol/Session.hpp>
#include <Protocol/Message/HandshakeMessage.hpp>
#include <OGRE/OgreLogManager.h>

Session::Session(boost::asio::io_service &service) :
    socket(service), state(DISCONNECTED), id(DEFAULT_PROTOCOL), lastMessageId(-1), username("Rocky")
{
}

Session::~Session()
{
    disconnect();
}

void Session::connect(std::string address, std::string port,
                      std::string username)
{
    boost::asio::ip::tcp::resolver resolver(socket.get_io_service());
    boost::asio::ip::tcp::resolver::query query(address.c_str(), port.c_str());
    boost::asio::ip::tcp::resolver::iterator endpoint_iterator =
        resolver.resolve(query);
    boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;

    LogManager::getSingletonPtr()->logManager("Attempting to connect to "
            + endpoint.address() + ":" + endpoint.port());
    setState(CONNECTING);

    this->username = username;

    socket.async_connect(endpoint,
                         boost::bind(&Session::handleConnect, this,
                                     boost::asio::placeholders::error, endpoint_iterator));
}

void Session::disconnect()
{
    socket.close();
    setState(DISCONNECTED);
}

void Session::handleConnect(const boost::system::error_code &error,
                            boost::asio::ip::tcp::resolver::iterator endpointIterator)
{
    if (!error)
    {
        boost::asio::ip::tcp::endpoint endpoint = *endpointIterator;
        LogManager::getSingletonPtr()->logManager("Connected to " + endpoint.address()
                + ":" + endpoint.port());

        setState(EXCHANGE_KEY);
        HandshakeMessage handshakeMessage(id, username,
                                          endpoint.address().to_string(), endpoint.port());
        sendImmediate(handshakeMessage);
    }
    else if (++endpointIterator
             != boost::asio::ip::tcp::resolver::iterator())
    {
        LogManager::getSingletonPtr()->logManager("Connection failed -- retrying");
        socket.close();
        boost::asio::ip::tcp::endpoint endpoint = *endpointIterator;
        socket.async_connect(endpoint,
                             boost::bind(&Session::handleConnect, this,
                                         boost::asio::placeholders::error, endpointIterator));
    }
    else
    {
        LogManager::getSingletonPtr()->logManager("Connection failed: " + error.message());
        disconnect();
    }
}

void Session::handleReceive(const boost::system::error_code &error)
{
    if (!socket.is_open())
    {
        LogManager::getSingletonPtr()->logManager("Connection lost");
        return;
    }
    else if (error)
    {
        LogManager::getSingletonPtr()->logManager("Connection lost, received error: " + error.message());
        disconnect();
        return;
    }
    else if (outgoing.size())
    {
        boost::asio::async_write(socket, outgoing,
                                 boost::bind(&Session::handleReceive, this,
                                             boost::asio::placeholders::error));
        return;
    }

    // Read the message received
    MessageBuffer buffer(&socket);
    protocol.readMessage(buffer, lastMessageId);

    // Keep writing and reading from the TCP socket.
    if (outgoing.size())
    {
        boost::asio::async_write(socket, outgoing,
                                 boost::bind(&Session::handleWrite, this,
                                             boost::asio::placeholders::error));
    }
    else
    {
        boost::asio::async_read(socket, boost::asio::buffer(&lastMessageId, 1),
                                boost::bind(&Session::handleReceive, this,
                                            boost::asio::placeholders::error));
    }
}

void Session::handleWrite(const boost::system::error_code &error)
{
    if (!error)
    {
        boost::asio::async_read(socket, boost::asio::buffer(&lastMessageId, 1),
                                boost::bind(&Session::handleReceive, this,
                                            boost::asio::placeholders::error));
    }
    else
    {
        disconnect();
    }
}

void Session::send(Message &message)
{
    MessageBuffer out(&outgoing);
    protocol.writeMessage(out, message);
}

void Session::sendImmediate(Message &message)
{
    send(message);
    boost::asio::async_write(socket, outgoing,
                             boost::bind(&Session::handleWrite, this,
                                         boost::asio::placeholders::error));
}

SessionState Session::getState()
{
    return state;
}

void Session::setProtocol(unsigned int id)
{
    this->id = id;
}

void Session::setState(SessionState state)
{
    this->state = state;
}

SessionSecureLayer &Session::getAuthenticator()
{
    return authenticator;
}
