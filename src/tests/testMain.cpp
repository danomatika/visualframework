#include <iostream>
#include <unistd.h>
#include <string>

#include <visualframework.h>

#include "TestApp.h"

using namespace std;
using namespace visual;

int main(int argc, char *argv[])
{
    LOG << "starting testMain" << endl;

    // initialize SDL context
    Graphics::init(800, 600, 24, Graphics::HARDWARE);

    // initialize app
    TestApp testApp;
    testApp.init();

    // set icon
    Graphics::setWindowIcon("../data/icon.bmp");

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
