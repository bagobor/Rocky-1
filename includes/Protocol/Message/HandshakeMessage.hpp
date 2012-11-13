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
#ifndef _HANDSHAKE_MESSAGE_HPP_
#define _HANDSHAKE_MESSAGE_HPP_

#include <Protocol/Message.hpp>

/**
 * Encapsulate the packet '0x02' that the client sends
 * to inform the server of its information
 */
class HandshakeMessage: public Message
{

public:

    /**
     * Constructs handshake message to send to the server
     *
     * @param protocolVersion The client's protocol version
     * @param username The player's username
     * @param host Client's host
     * @param port The port being used
     */
    HandshakeMessage(unsigned char protocolVersion, std::string username,
                     std::string host, unsigned int port)
    {

        this->protocolVersion = protocolVersion;
        this->username = username;
        this->host = host;
        this->port = port;
    }

    /**
     * {@inheritDoc}
     */
    unsigned int getId()
    {
        return 0x02;
    }

    /**
     * {@inheritDoc}
     */
    void write(MessageBuffer &out)
    {
        out << protocolVersion;
        out << username;
        out << host;
        out << port;
    }

private:
    unsigned char protocolVersion;
    std::string username;
    std::string host;
    unsigned int port;
};

#endif // _HANDSHAKE_MESSAGE_HPP_
