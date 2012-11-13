#!/bin/sh
svn co http://svn.boost.org/svn/boost/trunk boost
cd boost
./bootstrap
./b2
sudo ./b2 install
hg clone http://bitbucket.org/sinbad/ogre/
cd ogre
mkdir build
cd build
cmake ..
make
sudo make install

