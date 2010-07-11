/*==============================================================================

	ClassTests.h

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
#ifndef CLASSTESTS_H
#define CLASSTESTS_H

#include <visualframework/visualframework.h>

using namespace std;
using namespace visual;

class MyUdpReceiver : public UdpReceiver
{
	protected:
		void process(const uint8_t* data, unsigned int len);
};

class ClassTests
{
    public:

        ClassTests();

        virtual ~ClassTests();
        
        void setup();
        
        void update();

        void testLog();
        
        void testThread();

        void startTestUdpReceiver();

        void stopTestUdpReceiver();

        void testUdpSender();

        void testGraphicsPrimitives();
        
        void testImage(int x, int y);
        
        void testFont(int x, int y);

    private:

        MyUdpReceiver udpReceiver;
        
        Image image, imageAlpha, imagePixels;
        uint32_t pixels[8*8];	// pixel array
        Font font;

        PointList polygon;
        
        Timer testTimer;
};

#endif // CLASSTESTS_H
