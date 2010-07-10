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

class UdpReceiver : public UdpListener
{
    protected:

        void process(UDPpacket* packet);
};

class ClassTests
{
    public:

        ClassTests();

        virtual ~ClassTests();
        
        void setup();
        
        void update();

        void testLog();

        void startTestUdpListener();

        void stopTestUdpListener();

        void testUdpSender();

        void testGraphicsPrimitives();
        
        void testImage(int x, int y);
        
        void testFont(int x, int y);

    private:

        UdpReceiver udpListener;
        
        Image image, imageAlpha;
        Font font;

        PointList polygon;
        
        Timer testTimer;
};

#endif // CLASSTESTS_H
