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
#ifndef _CLIENT_STATUS_MESSAGE_HPP_
#define _CLIENT_STATUS_MESSAGE_HPP_

#include <Protocol/Message.hpp>

/**
 * This token is sended when we first connect to the server
 */
#define INITIAL_SPAWN_STATUS 0x00
/**
 * This token is sended when the player has died
 */
#define SPAWN_AFTER_DEATH_STATUS 0x01

/**
 * Encapsulate the packet '0xCD' that the client sends
 * to update the client status
 */
class ClientStatusMessage: public Message
{

public:

    /**
     * Construct a status message to send
     *
     * @param status 0 for First time or 1 to respawn after death
     */
    ClientStatusMessage(unsigned char status)
    {
        this->status = status;
    }

    /**
     * {@inheritDoc}
     */
    unsigned int getId()
    {
        return 0xCD;
    }

    /**
     * {@inheritDoc}
     */
    void write(MessageBuffer &out)
    {
        out << status;
    }
private:
    unsigned char status;
};

#endif // _CLIENT_STATUS_MESSAGE_HPP_
