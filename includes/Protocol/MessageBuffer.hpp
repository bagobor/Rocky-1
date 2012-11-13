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
#ifndef _MESSAGE_BUFFER_HPP_
#define _MESSAGE_BUFFER_HPP_

#include <boost/asio.hpp>

/**
 * Encapsulate the buffer for the protocol messages. The protocol
 * uses Big Endianess.
 */
class MessageBuffer
{
public:
    /**
     * Constructor as an output stream.
     *
     * @param buffer the buffer that will contain the data
     */
    MessageBuffer(boost::asio::streambuf *buffer);
    /**
     * Constructor as an input stream.
     *
     * @param socket the socket to fetch the data from
     */
    MessageBuffer(boost::asio::ip::tcp::socket *socket);

    /**
     * Writes an unsigned character (8 Bits)
     */
    MessageBuffer &operator <<(unsigned char value);

    /**
     * Writes a boolean (8 Bits)
     */
    MessageBuffer &operator <<(bool value);

    /**
     * Writes an unsigned short (16 Bits)
     */
    MessageBuffer &operator <<(unsigned short value);

    /**
     * Writes an unsigned integer (32 Bits)
     */
    MessageBuffer &operator <<(unsigned int value);

    /**
     * Writes an unsigned long (64 Bits)
     */
    MessageBuffer &operator <<(unsigned long value);

    /**
     * Writes a float (32 Bits)
     */
    MessageBuffer &operator <<(float value);

    /**
     * Writes a double (64 Bits)
     */
    MessageBuffer &operator <<(double value);

    /**
     * Writes a UTF-16 string
     */
    MessageBuffer &operator <<(std::string &value);

    /**
     * Reads an array of bytes (16 Bits + length of the array)
     */
    MessageBuffer &operator >>(unsigned char **value);

    /**
     * Reads an unsigned character (8 Bits)
     */
    MessageBuffer &operator >>(unsigned char &value);

    /**
     * Reads a boolean (8 Bits)
     */
    MessageBuffer &operator >>(bool &value);

    /**
     * Reads an unsigned short (16 Bits)
     */
    MessageBuffer &operator >>(unsigned short &value);

    /**
     * Reads an array of integers (8 Bits * length + 32 Bits * value)
     */
    MessageBuffer &operator >>(unsigned int **value);

    /**
     * Reads an unsigned int (32 Bits)
     */
    MessageBuffer &operator >>(unsigned int &value);

    /**
     * Reads an unsigned long (64 Bits)
     */
    MessageBuffer &operator >>(unsigned long &value);

    /**
     * Reads a float (32 Bits)
     */
    MessageBuffer &operator >>(float &value);

    /**
     * Reads a double (64 Bits)
     */
    MessageBuffer &operator >>(double &value);

    /**
     * Reads an UTF-16 String
     */
    MessageBuffer &operator >>(std::string &value);
private:
    boost::asio::streambuf *output;
    boost::asio::ip::tcp::socket *socket;
};

#endif // _MESSAGE_BUFFER_HPP_
