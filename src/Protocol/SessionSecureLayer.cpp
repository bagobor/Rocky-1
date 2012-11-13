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

#include <Protocol/SessionSecureLayer.hpp>
#include <boost/format.hpp>

SessionSecureLayer::SessionSecureLayer() :
    username("default"), session("-")
{
}

AuthenticationResponse SessionSecureLayer::getResponse(std::string username,
        std::string password)
{
    std::string remoteAddress =
        str(boost::format(AUTHENTICATION_ADDRESS) % username % password % AUTHENTICATION_VERSION);
    boost::network::http::client::request request(remoteAddress);
    std::string response = body(client.get(request));

    if (response == "Old version")
    {
        return OLD_VERSION;
    }
    else if (response == "Bad response")
    {
        return BAD_RESPONSE;
    }
    else if (response == "Bad login")
    {
        return BAD_LOGIN;
    }
    else if (response == "User not premium")
    {
        return USER_NOT_PREMIUM;
    }

    std::vector<std::string> values;
    boost::split(values, response, boost::is_any_of(":"));
    if (values.size() != 0x5)
    {
        return BAD_RESPONSE;
    }
    username = values[0x2];
    session = values[0x3];

    return SUCCESFULL;
}

std::string &SessionSecureLayer::getUsername()
{
    return username;
}

std::string &SessionSecureLayer::getSession()
{
    return session;
}
