/*==============================================================================

	TestApp.h

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

		bool init();

		void setup();

		void update();

		void draw();

		void cleanup();

		void keyPressed(SDLKey key, SDLMod mod);
		void keyReleased(SDLKey key, SDLMod mod);
		void mousePressed(int button, int x, int y);
		void mouseReleased(int button, int x, int y);

	protected:

		ClassTests test;

	private:

		int _currentRes;
		vector<SDL_Rect*> _resolutions;

		bool _blend;
		bool _smooth;
		bool _big;
};

#endif // TESTAPP_H
