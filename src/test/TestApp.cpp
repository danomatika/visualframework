/*==============================================================================

	TestApp.cpp

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
#include "TestApp.h"

TestApp::TestApp() : _currentRes(0)
{
    _resolutions = Graphics::getResolutions();
}

TestApp::~TestApp()
{}

void TestApp::init()
{
    test.testLog();

    //test.startTestUdpListener();
    //sleep(1);
    //test.testUdpSender();
    //test.stopTestUdpListener();
}

void TestApp::setup()
{
    setBackground(0x505050);
    setFrameRate(15);
    
    test.setup();
}

void TestApp::update()
{
	test.update();
	LOG << "fps: " << getFrameRate() << endl;
}

void TestApp::draw()
{
    test.testGraphicsPrimitives();
    test.testImage(500, 200);
    test.testFont(50, 450);
}

void TestApp::cleanup()
{}

void TestApp::keyPressed(SDLKey key, SDLMod mod)
{
	LOG_DEBUG << "key pressed: " << key << endl;

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
                        case WINDOW:
                            LOG << "Changed graphics mode to Window" << endl;
                            break;

                        case FULLSCREEN:
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
