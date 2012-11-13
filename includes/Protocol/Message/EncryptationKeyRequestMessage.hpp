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
#ifndef _ENCRYPTATION_KEY_REQUEST_MESSAGE_HPP_
#define _ENCRYPTATION_KEY_REQUEST_MESSAGE_HPP_

#include <Protocol/Message.hpp>

/**
 * Encapsulate the packet '0xFD' that the server sends
 * for requestion the authentication key
 */
class EncryptationKeyRequestMessage: public Message
{
public:

    /**
     * Destructor of the class to release allocated memory
     */
    ~EncryptationKeyRequestMessage()
    {
        if ( keyArray != NULL )
        {
            delete keyArray;
        }
        if ( verifyToken != NULL )
        {
            delete verifyToken;
        }
    }

    /**
     * {@inheritDoc}
     */
    unsigned int getId()
    {
        return 0xFD;
    }

    /**
     * {@inheritDoc}
     */
    void read(MessageBuffer &in)
    {
        in >> id;
        in >> &keyArray;
        in >> &verifyToken;
    }

    /**
     * Gets the server id
     */
    std::string *getServerId()
    {
        return &id;
    }

    /**
     * Gets the public key
     */
    unsigned char *getKey()
    {
        return keyArray;
    }

    /**
     * Gets the verify token
     */
    unsigned char *getVerifyToken()
    {
        return verifyToken;
    }
private:
    std::string id;
    unsigned char *keyArray;
    unsigned char *verifyToken;
};

#endif // _ENCRYPTATION_KEY_REQUEST_MESSAGE_HPP_
