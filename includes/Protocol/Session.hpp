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
#ifndef _SESSION_HPP_
#define _SESSION_HPP_

#include <Protocol/MessageHandler.hpp>
#include <Protocol/SessionSecureLayer.hpp>

/**
 * The message header len is 1 byte.
 */
#define MESSAGE_HEADER_LEN 1

/**
 * Define the default protocol
 */
#define DEFAULT_PROTOCOL 0x2F

/**
 * The states of the session
 */
enum SessionState
{
    /**
     * The session is connecting
     */
    CONNECTING = 0,
    /**
     * The session is waiting for the exchange message
     */
    EXCHANGE_KEY,
    /**
     * The session has received the login message
     */
    LOGGED,
    /**
     * The session is disconnected
     */
    DISCONNECTED
};

/**
 * Encapsulate the current client session regarding the remote
 * connection
 */
class Session
{
public:
    /**
     * Construct the session socket
     *
     * @param service the worker of the session, for pulling
     */
    Session(boost::asio::io_service &service);

    /**
     * Release and disconnect the socket upon destroy
     */
    ~Session();

    /**
     * Disconnect the session
     */
    void disconnect();

    /**
     * Connect to a remote address
     *
     * @param address the host address
     * @param port the port of the address
     * @param username the name of the user
     */
    void connect(std::string address, std::string port, std::string username);

    /**
     * Send a message to the server
     *
     * @param message the message to deliver
     */
    void send(Message &message);

    /**
     * Send an immediate message to the server
     *
     * @param message the message to deliver
     * @param immediate do we need to deliver the message right now?
     */
    void send(Message &message, bool immediate);

    /**
     * Gets the current session's state
     */
    SessionState getState();

    /**
     * Sets the current state of the session
     *
     * @param state the new state
     */
    void setState(SessionState state);

    /**
     * Sets the id of the protocol
     *
     * @param id the session protocol id
     */
    void setProtocol(unsigned int id);

    /**
     * Gets the authenticator of the session
     */
    SessionSecureLayer &getAuthenticator();
private:
    /**
     * Handle when the client connect to the server
     */
    void handleConnect(const boost::system::error_code &error,
                       boost::asio::ip::tcp::resolver::iterator endpointIterator);
    /**
     * Handle when the client receives data
     */
    void handleReceive(const boost::system::error_code &error);

    /**
     * Handle when the client writes data
     */
    void handleWrite(const boost::system::error_code &error);
protected:
    boost::asio::ip::tcp::socket socket;
    boost::asio::streambuf outgoing;

    SessionState state;
    SessionSecureLayer authenticator;
    MessageHandler protocol;

    unsigned int id;
    unsigned char lastMessageId;
    std::string username;
};

#endif // _SESSION_HPP_
