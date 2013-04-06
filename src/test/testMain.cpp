/*==============================================================================

	tesMain.cpp

	vftest: test cases for visualframework
  
	Copyright (C) 2009, 2010  Dan Wilcox <danomatika@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

==============================================================================*/
#include <iostream>
#include <unistd.h>
#include <string>

#include <visualframework/visualframework.h>

#include "TestApp.h"

using namespace std;
using namespace visual;

int main(int argc, char *argv[])
{
    LOG << "starting testMain" << endl;

	Util::setDataPath(Util::makeAbsolutePath(Util::getDirPath(Util::getExecutablePath())+"/../../data"));
	LOG << "Data path is " << Util::getDataPath() << endl;

    // initialize SDL context
    if(!Graphics::init(800, 600, 32, HARDWARE))
    	return EXIT_FAILURE;
        
    // initialize app
    TestApp testApp;
    testApp.init();

    // set icon
    LOG << Util::toDataPath("icon.bmp") << endl;
    Graphics::setWindowIcon(Util::toDataPath("icon.bmp"));

    // open sdl window
    Graphics::createWindow("visualframework test");
/*
    sleep(5);

    Graphics::changeResolution(640, 480);

    sleep(5);

    Graphics::changeResolution(1003, 334);

    sleep(5);

    Graphics::changeResolution(720, 480);
*/
    // print out the available screen resolutions
    vector<SDL_Rect*> res = Graphics::getResolutions();
    LOG << "Available resolutions:" << endl;
    for(unsigned int i = 0; i < res.size(); ++i)
    {
        LOG << "    " << res[i]->w << "x" << res[i]->h << endl;
    }
    LOG << endl;


    // setup sdl resources
    testApp.setup();

    // main app loop
    testApp.mainLoop();

    // cleanup after exit from loop
    testApp.cleanup();

    // all is well ;)
    LOG << "Exited cleanly" << endl;
    return 0;
}
