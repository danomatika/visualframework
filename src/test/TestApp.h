#ifndef TESTAPP_H
#define TESTAPP_H

#include <visualframework.h>
#include "ClassTests.h"

using namespace std;
using namespace visual;

class TestApp : public Application
{
    public:

        TestApp();

        virtual ~TestApp();

        void init();

        void setup();

        void update();

        void draw();

        void cleanup();

        void keyPressed(SDLKey key, SDLMod mod);

    protected:

        ClassTests test;

    private:

        int _currentRes;
        vector<SDL_Rect*> _resolutions;
};

#endif // TESTAPP_H
