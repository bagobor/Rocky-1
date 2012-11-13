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
#ifndef _MESSAGE_HPP_
#define _MESSAGE_HPP_

#include <Protocol/MessageBuffer.hpp>

/**
 * Encapsulate a packet
 */
class Message
{
public:
    /**
     * Default destructor
     */
    virtual ~Message()
    {
    }

    /**
     * Gets the ID of the message
     */
    virtual unsigned int getId() = 0;

    /**
     * Store the message into an output stream
     *
     * @param out the output stream
     */
    virtual void write(MessageBuffer &out)
    {
    }

    /**
     * Gets the message from an input stream
     *
     * @param in the input stream
     */
    virtual void read(MessageBuffer &in)
    {
    }
};

#endif // _MESSAGE_HPP_
