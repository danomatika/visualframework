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

#include <sstream>

TestApp::TestApp() : _currentRes(0)
{
    _resolutions = Graphics::getResolutions();
	_blend = true;
	_smooth = false;
	_big = false;
}

TestApp::~TestApp()
{}

bool TestApp::init()
{
    test.testLog();
	test.testUtil();

	//test.testThread();

    //test.startTestUdpReceiver();
    //sleep(1);
    //test.testUdpSender();
    //test.stopTestUdpReceiver();

	return true;
}

void TestApp::setup()
{
	setBackground(0x505050);
    setFrameRate(25);
    
    test.setup();
}

void TestApp::update()
{
	test.update();
}

void TestApp::draw()
{

    test.testGraphicsPrimitives();
    test.testImage(550, 200);
    test.testFont(50, 450);
    
    // fps display
    stringstream stream;
    stream << getFrameRate();
    Graphics::stroke(0xFFFFFF);
    Graphics::string(12, 12, stream.str());

    // draw a rect if the mouse cursor is off
    if(!Graphics::getShowMouseCursor())
    {
    	Graphics::noStroke();
        if(bMousePressed && mouseButton > 0)
        	Graphics::fill(0xFFFFFF);
        else
    		Graphics::fill(0xFFFF00);
        Graphics::rectMode(CENTER);
        Graphics::rectangle(mouseX, mouseY, 20, 20);
    }
}

void TestApp::cleanup()
{}

void TestApp::keyPressed(SDLKey key, SDLMod mod)
{
	LOG_DEBUG << "key pressed: " << key << endl;

    switch(key)
    {
    	//	default key handling:
        //  	- Escape : exit mainloop
        //		- Alt+Enter : toggle fullscreen
                                                                            
        case 'q':
            exitMainLoop();	// stop the mainloop programmatically
            break;
            
        case 'm':
        	Graphics::toggleShowMouseCursor();
            LOG << "Show mouse cursor is: " << Graphics::getShowMouseCursor() << endl;
            break;
			
		case 's':
			_smooth = !_smooth;
			LOG << "Smooth: " << _smooth << endl;
			if(_smooth)
				Graphics::smooth();
			else
				Graphics::noSmooth();
			break;
			
		case 'b':
			_blend = !_blend;
			LOG << "Blend: " << _blend << endl;
			if(_blend)
				Graphics::blend();
			else
				Graphics::noBlend();
			break;
			
		case ' ':
			_big = !_big;
			if(_big)
			{
				Graphics::push();
				Graphics::scale(1.25, 1.25);
			}
			else
			{
				Graphics::pop();
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

void TestApp::keyReleased(SDLKey key, SDLMod mod)
{
	LOG_DEBUG << "key released: " << key << endl;
}

void TestApp::mousePressed(int button, int x, int y)
{
	LOG << "mouse button pressed: " << button << endl;
}

void TestApp::mouseReleased(int button, int x, int y)
{
	LOG << "mouse button released: " << button << endl;
}
