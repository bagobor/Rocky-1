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
#ifndef _SESSION_SECURE_LAYER_HPP_
#define _SESSION_SECURE_LAYER_HPP_

#include <boost/network/protocol/http/client.hpp>

/**
 * Define the launcher version
 */
#define AUTHENTICATION_VERSION 0xD

/**
 * Define the address
 */
#define AUTHENTICATION_ADDRESS "https://login.minecraft.net?user=%s&password=%s&version=%d"

/**
 * List of possible response
 */
enum AuthenticationResponse
{
    /**
     * The website is offline
     */
    OFFLINE = 0,
    /**
     * If the client is outdated
     */
    OLD_VERSION,
    /**
     * The account is not premium
     */
    USER_NOT_PREMIUM,
    /**
     * Invalid username or password
     */
    BAD_LOGIN,	
    /**
     * Invalid post request
     */
    BAD_RESPONSE,
    /**
     * The user has logged
     */
    SUCCESFULL
};

/**
 * Encapsulate the class to authenticate the client into
 * a central login system and to use SSL on a socket
 */
class SessionSecureLayer
{
public:
    /**
     * Default constructor
     */
    SessionSecureLayer();

    /**
     * Send the authentication response
     *
     * @param username the name of the user
     * @param password the password provided
     */
    AuthenticationResponse getResponse(std::string username,
                                       std::string password);
    /**
     * Gets the case sensitive username of the player account
     */
    std::string &getUsername();

    /**
     * Gets the current id of the session
     */
    std::string &getSession();
private:
    std::string username;
    std::string session;
    boost::network::http::client client;
};

#endif // _SESSION_SECURE_LAYER_HPP_
