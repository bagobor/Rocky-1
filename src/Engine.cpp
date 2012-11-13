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

#include <Engine.hpp>
#include <OGRE/OgreLogManager.h>

Engine::Engine() :
    username("Rocky"), session(worker)
{
}

Engine::~Engine()
{
    stop();
}

void Engine::start()
{
    LogManager::getSingletonPtr()->logManager("Starting engine with " + boost::thread::hardware_concurrency()
            + " threads");
    boost::asio::io_service::work work(worker);
    for (int i = 0, max = boost::thread::hardware_concurrency(); i < max; ++i)
    {
        threads.create_thread(
            boost::bind(
                static_cast<size_t (boost::asio::io_service:: *)()>(&boost::asio::io_service::run), &worker));
    }
    device.start("rocky_config.ini");
}

void Engine::stop()
{
    device.stop();
    worker.stop();
    threads.join_all();
}

void Engine::setUsername(std::string name)
{
    this->username = name;
}

std::string &Engine::getUsername()
{
    return username;
}

Session &Engine::getSession()
{
    return session;
}

Device &Engine::getDevice()
{
    return device;
}