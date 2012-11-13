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
#ifndef _MESSAGE_HANDLER_HPP_
#define _MESSAGE_HANDLER_HPP_

#include <Protocol/Message.hpp>

/**
 * Encapsulate the protocol decode, encoder and handler for every packet
 * in the game
 */
class MessageHandler
{
public:
    /**
     * Reads a message that was sended by the remote connection
     *
     * @param in the buffer to read the message data
     * @param id the id of the message
     */
    void readMessage(MessageBuffer &in, unsigned int id);
    /**
     * Writes a message to the remote connection
     *
     * @param out the buffer to store the message data
     * @param message the message to send
     */
    void writeMessage(MessageBuffer &out, Message &message);
};

#endif // _MESSAGE_HANDLER_HPP_
