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
#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

#include <OGRE/OgreRoot.h>

/**
 * Encapsulate the class for managing the windows and rendering states
 */
class Device
{
public:
    /**
     * Base constructor
     */
    Device();

    /**
     * Base destructor
     */
    ~Device();

    /**
     * Initialize the renderer
     *
     * @param config configuration file
     */
    void start(std::string config);

    /**
     * Stop the renderer
     */
    void stop();
protected:
    Ogre::Root *root;
    Ogre::RenderWindow *renderWindow;
    Ogre::Viewport* viewport;
};

#endif // _RENDERER_HPP_
