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

#include <boost/program_options.hpp>
#include <Engine.hpp>

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR strCmdLine, INT iCmdSize)
#else
int main(int argc, char *argv[])
#endif
{
    boost::program_options::options_description description("Command Arguments.");
    description.add_options()
    ("help,h", "produce help message")
    ("protocol,p", boost::program_options::value<int>(), "set the networking protocol");
    boost::program_options::variables_map vm;
    try
    {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        std::vector<std::string> args = boost::program_options::split_winmain(strCmdLine);
        boost::program_options::store(boost::program_options::command_line_parser(args).options(description).run(), vm);
#else
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, description));
#endif
        boost::program_options::notify(vm);

        if ( vm.count("protocol") )
        {
            Engine::instance().getSession().setProtocol(vm["protocol"].as<unsigned int>());
        }
        if ( vm.count("help") )
        {
            std::cout << description << std::endl;
        }
        else
        {
            Engine::instance().start();
        }
    }
    catch ( std::exception &ex )
    {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        ::MessageBox(NULL, ex.what(), "An exception has ocurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
        std::cerr << "An exception has ocurred: " << ex.what() << std::endl;
#endif
    }
    return 0;
}

#ifdef __cplusplus
}
#endif