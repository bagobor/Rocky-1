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
#ifndef _KEEP_ALIVE_MESSAGE_HPP_
#define _KEEP_ALIVE_MESSAGE_HPP_

#include <Protocol/Message.hpp>

/**
 * Encapsulate the packet '0x00' that the server sends us
 * to check if the client is still alive.
 */
class KeepAliveMessage: public Message
{
public:
    /**
     * Constructor to read the message from the server
     */
    KeepAliveMessage()
    {
        this->aliveId = 0;
    }
    /**
     * Constructor to send the message to the server
     *
     * @param id the id response for the server
     */
    KeepAliveMessage(unsigned int id)
    {
        this->aliveId = id;
    }

    /**
     * {@inheritDoc}
     */
    unsigned int getId()
    {
        return 0x00;
    }

    /**
     * {@inheritDoc}
     */
    void write(MessageBuffer &out)
    {
        out << aliveId;
    }

    /**
     * {@inheritDoc}
     */
    void read(MessageBuffer &in)
    {
        in >> aliveId;
    }
public:

    /**
     * Gets the serial provided by the server
     */
    unsigned int getAliveId()
    {
        return aliveId;
    }

private:
    unsigned int aliveId;
};

#endif // _KEEP_ALIVE_MESSAGE_HPP_
