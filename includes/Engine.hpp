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
#ifndef _ENGINE_HPP_
#define _ENGINE_HPP_

#include <boost/thread.hpp>
#include <OGRE/OgreSingleton.h>
#include <Protocol/Session.hpp>
#include <Renderer/Device.hpp>

/**
 * Encapsulate the core class for the game
 */
class Engine: public Ogre::Singleton<Engine>
{
public:
    /**
     * Base class of the engine
     */
    Engine();

    /**
     * Called to release every memory allocated by the engine
     */
    ~Engine();

    /**
     * Start the engine
     */
    void start();

    /**
     * Stop the engine from running
     */
    void stop();

    /**
     * Sets the name of the user
     *
     * @param name the name of the user
     */
    void setUsername(std::string name);

    /**
     * Gets the name of the user
     */
    std::string &getUsername();

    /**
     * Gets the session of the engine. The session is the thing
     * that communicate with the remote server.
     */
    Session &getSession();

    /**
     * Gets the renderer of the engine. The renderer is the thing
     * that renders and keep track of the client ui.
     */
    Device &getDevice();
protected:
    std::string username;
    Session session;
    Device device;

    boost::asio::io_service worker;
    boost::thread_group threads;
};

#endif // _ENGINE_HPP_
