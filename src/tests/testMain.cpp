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
    Graphics sdl(720, 480, 16, Graphics::HARDWARE);
    sdl.init();

    // set icon
    sdl.setWindowIcon("../data/icon.bmp");

    // open sdl window
    sdl.createWindow("visualframework test");
/*
    sleep(5);

    sdl.changeResolution(640, 480);

    sleep(5);

    sdl.changeResolution(1003, 334);

    sleep(5);

    sdl.changeResolution(720, 480);
*/
    // print out the available screen resolutions
    vector<SDL_Rect*> res = sdl.getResolutions();
    LOG << "Available resolutions:" << endl;
    for(unsigned int i = 0; i < res.size(); ++i)
    {
        LOG << "    " << res[i]->w << "x" << res[i]->h << endl;
    }
    LOG << endl;

    // init app
    TestApp testApp(sdl);
    testApp.setFrameRate(30);
    testApp.setup();

    // main app loop
    testApp.mainLoop();

    // cleanup after exit from loop
    testApp.cleanup();

    // all is well ;)
    LOG << "Exited cleanly" << endl;
    return 0;
}
