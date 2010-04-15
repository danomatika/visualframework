#include "TestApp.h"

TestApp::TestApp() : _currentRes(0)
{
    _resolutions = Graphics::getResolutions();
}

TestApp::~TestApp()
{
    //dtor
}

void TestApp::init()
{
    test.testLog();

    //test.startTestOscListener();
    //sleep(100);
    //test.testOscSender();
    //test.stopTestOscListener();

    test.startTestUdpListener();
    sleep(1);
    test.testUdpSender();
    test.stopTestUdpListener();

    //test.testXmlFile("../data/test.xml");
}

void TestApp::setup()
{
    setBackground(0x505050);
    setFrameRate(5);
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
            { }
			break;
			
		case SDLK_f:
                if(Graphics::toggleFullscreen())
                {
                    switch(Graphics::getMode())
                    {
                        case Graphics::WINDOW:
                            LOG << "Changed graphics mode to Window" << endl;
                            break;

                        case Graphics::FULLSCREEN:
                            LOG << "Changed graphics mode to Fullscreen" << endl;
                            break;
                    }
                }
            //}
            break;

        case SDLK_RIGHTBRACKET:
            // go up in resolution
            _currentRes++;
            if(_currentRes >= (int) _resolutions.size())
            {
                _currentRes = 0;
            }
            LOG << "Changing resolution: " << _currentRes << endl;
            Graphics::changeResolution(_resolutions[_currentRes]->w,
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
            Graphics::changeResolution(_resolutions[_currentRes]->w,
                                       _resolutions[_currentRes]->h);
            break;

        default:
            break;
    }
}
