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
#include <Renderer/Device.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <OGRE/OgreLogManager.h>
 
Device::Device() :
    root(NULL), renderWindow(NULL)
{
}

Device::~Device()
{
}

void Device::start(std::string config)
{

    // We will handle the Ogre3D configuration
    root = new Ogre::Root("", "", "rocky_debug.txt");

    // We only enable OpenGL & DirectX 9.0
    root->loadPlugin("Plugin/RenderSystem_GL");
    root->loadPlugin("Plugin/RenderSystem_Direct3D");

    // Load the configuration of the device
    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini(config, pt);

    // Set the rendering method and start the root initialization
    std::string renderType = pt.get<std::string>("Device.Type");
    RenderSystem *renderSystem;
    if ( renderType == "OpenGL")
    {
        renderSystem = root->getRenderSystemByName("RenderSystem_GL");
    }
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    else if ( renderType == "DirectX")
    {
        renderSystem = root->getRenderSystemByName("RenderSystem_Direct3D"));
    }
#endif
    if (renderSystem == NULL)
    {
        throw "Sorry, no suitable renderer system was found in your system.";
    }

    LogManager::getSingletonPtr()->logManager("Using renderer: " + renderSystem);
    root->setRenderSystem(renderSystem);
    root->initialise(false, "Rocky Client", "");

    // Get the parameters for the window
    Ogre::NameValuePairList parameters;
    parameters["vsync"] = pt.get<std::string>("Parameter.Vsync");
    parameters["FSAA"] = pt.get<unsigned int>("Parameter.FullscreenAA");
    parameters["colourDepth"] = pt.get<unsigned int>("Parameter.ColourDepth");
    parameters["displayFrequency"] = pt.get<unsigned int>("Parameter.DisplayFrequency");

    // Create the current rendering window
    renderWindow = root->createRenderWindow("Rocky Client", pt.get<unsigned int>("Device.Width"),
                                            pt.get<unsigned int>("Device.Height"), pt.get<bool>("Device.Fullscreen"), &parameters);

    // Activate the root rendering
    root->startRendering();
}
