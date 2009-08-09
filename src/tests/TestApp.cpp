#include "TestApp.h"

TestApp::TestApp(Graphics& sdl) : _sdl(sdl), _currentRes(0)
{
    _resolutions = _sdl.getResolutions();
}

TestApp::~TestApp()
{
    //dtor
}

void TestApp::setup()
{
    _background.set(80, 80, 80);
    setFrameRate(5);

    test.testLog();

    test.startTestOscListener();
    sleep(1);
    test.testOscSender();
    test.stopTestOscListener();
    test.testXmlFile("../data/test.xml");
}

void TestApp::update()
{
}

void TestApp::draw()
{
    test.testGraphicsPrimitives();
}

void TestApp::cleanup()
{
}

void TestApp::keyPressed(SDLKey key, SDLMod mod)
{
    switch(key)
    {
        case SDLK_RETURN:
            // toggle fullscreen on ALT+ENTER
            if(mod & KMOD_ALT)
            {
                if(_sdl.toggleFullscreen())
                {
                    switch(_sdl.getMode())
                    {
                        case Graphics::WINDOW:
                            LOG << "Changed graphics mode to Window" << endl;
                            break;

                        case Graphics::FULLSCREEN:
                            LOG << "Changed graphics mode to Fullscreen" << endl;
                            break;
                    }
                }
            }
            break;

        case SDLK_RIGHTBRACKET:
            // go up in resolution
            _currentRes++;
            if(_currentRes >= (int) _resolutions.size())
            {
                _currentRes = 0;
            }
            LOG << "Changing resolution: " << _currentRes << endl;
            _sdl.changeResolution(_resolutions[_currentRes]->w,
                                      _resolutions[_currentRes]->h);
            break;

        case SDLK_LEFTBRACKET:
            // go down in resolution
            _currentRes--;
            if(_currentRes < 0)
            {
                _currentRes = _resolutions.size()-1;
            }
            LOG << "Changing resolution: " << _currentRes << endl;
            _sdl.changeResolution(_resolutions[_currentRes]->w,
                                      _resolutions[_currentRes]->h);
            break;

        default:
            break;
    }
}
