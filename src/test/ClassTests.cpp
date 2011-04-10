/*==============================================================================

	ClassTests.cpp

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
#include "ClassTests.h"

ClassTests::ClassTests()
{}

ClassTests::~ClassTests()
{}

void ClassTests::setup()
{
    // load points for polygon
    polygon.push_back(Point(0, 0));
    polygon.push_back(Point(100, 0));
    polygon.push_back(Point(50, 300));
    polygon.push_back(Point(0, 100));
    polygon.push_back(Point(50, 100));
	polygon.push_back(Point(25, 100));
	polygon.push_back(Point(25, 50));
	polygon.push_back(Point(50, 50));
	Point::scale(polygon, 1.5, 1.5);
	Point::translate(polygon, 400, 100);
	
	skew = 0.0f;
	scale = 0;
	rotate = 0;
	Graphics::rectMode(CORNER);

	// load image
	image.load(Util::toDataPath("testImage.jpg"));
    image.scale(0.5, 0.5);
    image.pixelate(5, 5);
    //image.resize(320, 240);
    
    // load alpha image
    imageAlpha.load(Util::toDataPath("testAlpha.png"));
    imageAlpha.scale(0.5, 0.5);
    imageAlpha.pixelate(5, 5);
	imageAlpha.rotate(90);
    
    // load image from pixel array
    for(int i = 0; i < 64; ++i)
    	pixels[i] = 0xFF00FF00;
    imagePixels.load(pixels, 8, 8);
    
    // load font
    font.load(Util::toDataPath("ATARCC__.TTF"), 25);
	
	drawTexture.allocate(100, 50);
	LOG << "draw texture: " << drawTexture << endl;
    
    // set initial timer
    testTimer.setAlarm(5000);
}

void ClassTests::update()
{
	if(testTimer.alarm())
    {
    	LOG << "Timer went off at " << Graphics::getMillis() << " millis" << endl;
        testTimer.setAlarm(5000);
    }
}

void ClassTests::testUtil()
{
	LOG << "Begin testUtil()" << endl;
	
	LOG << Util::toString(100) << " " << Util::toString(10234.232256785445, 5) << endl;
	
	LOG << "CWD: " << Util::getCWD() << endl;
	LOG << "absolute?: " << Util::isAbsolutePath("/usr/local") << endl;
	LOG << "relative?: " << !Util::isAbsolutePath("../../data") << endl;
	LOG << "dirname: " << Util::getDirPath("../data/example.xml") << endl;
	LOG << "basename: " << Util::getFileName("../data/example.xml") << endl;
	LOG << "to data path: " << Util::toDataPath("example.xml", true) << endl;
	LOG << "make absolute: " << Util::makeAbsolutePath("example.xml") << endl;
	Util::setDataPath("/usr/local/bin");
	LOG << "data path: " << Util::getDataPath() << endl;
	Util::setDataPath("../../data", true);
	LOG << "data path: " << Util::getDataPath() << endl;
	Util::setDataPath("../../data");
	LOG << "data path: " << Util::getDataPath() << endl << endl;
}

void ClassTests::testLog()
{
    LOG << "Begin testLog()" << endl;

    LOG << "This is a normal log message" << endl;
    LOG_DEBUG << "This is a debug log message" << endl;
    LOG_WARN << "This is a warning message" << endl;
    LOG_ERROR << "This is an error message" << endl << endl;
}

class MyThread : public Thread
{
	public:
		MyThread () : Thread("Test Thread") {}
    
	protected:    
        void run()
        {
        	while(threadIsRunning())
            {
            	LOG << "Thread ticks: " << Graphics::getMillis() << endl;
            	SDL_Delay(1000);
            }
        }
};

void ClassTests::testThread()
{
	MyThread thread;
    thread.start();
    SDL_Delay(5000);
    thread.stop();
}

void MyUdpReceiver::process(const uint8_t* data, unsigned int len)
{
    LOG << "UdpReceiver: Received message: '";

    for(unsigned int i = 0; i < len; ++i)
    {
        LOG << data[i];
    }
    LOG << "' len: " << len << endl;
}

void ClassTests::startTestUdpReceiver()
{
    LOG << "Starting UdpReceiver on port 8000" << endl;

    udpReceiver.setup(8000);
    udpReceiver.start();
    LOG << "    UdpReceiver is running? "
        << udpReceiver.isListening() << endl;
    LOG << endl;
}

void ClassTests::stopTestUdpReceiver()
{
    LOG << "Stopping UdpReceiver" << endl;
    udpReceiver.stop();
    LOG << "    UdpReceiver is running? "
        << udpReceiver.isListening() << endl;
    LOG << endl;
}

void ClassTests::testUdpSender()
{
    LOG << "Begin testUdpSender()" << endl;

    UdpSender sender("127.0.0.1", 8000);

    char* text1 = (char*) "hello world";
    LOG << "    sending string '" << text1 << "'" << endl;
    sender.send((uint8_t*) text1, strlen(text1)+1);
    sleep(2);

    char* text2 = (char*) "this is a string sent over udp ...";
    LOG << "len: " << strlen(text2)+1 << std::endl;

    UDPpacket* p;
    p = SDLNet_AllocPacket(1000);

    try
    {
        memcpy(p->data, text2, 35);//
        //strlen(text2)+1);
    }
    catch(std::exception& e)
    {
        LOG_ERROR << "UdpSender: memcpy failed to load packet: " << e.what() << std::endl;
        return;
    }

    p->len = strlen(text2)+1;
    LOG << "    sending string '" << text2 << "'" << endl;
    sender.send(p);
    sleep(2);
    SDLNet_FreePacket(p);

    LOG << endl;
}

void ClassTests::testGraphicsPrimitives()
{
	Graphics::push();
	Graphics::scale(scale, scale);
	Graphics::skew(skew, 0);
	Graphics::rotate(rotate);

    Graphics::stroke(0xFFFFFF);
    Graphics::point(25, 25);

    Graphics::stroke(0x0000FF);
    Graphics::line(50, 50, 300, 50);

    Graphics::noFill();
    Graphics::stroke(0xFF0000);
    Graphics::rectMode(CENTER);
    Graphics::rectangle(100, 150, 100, 100);

    Graphics::noStroke();
    Graphics::fill(0x00FF00);
    Graphics::triangle(250, 100, 250, 200, 350, 100);

    Graphics::stroke(0xFF00FF);
    Graphics::fill(0x333333);
    Graphics::circle(100, 300, 50);

	// draw a smooth ellipse
    Graphics::stroke(0xFFFF00);
    Graphics::fill(0xAAAAAA);
    Graphics::ellipse(300, 300, 50, 25);

    Graphics::stroke(0x00FFFF);
    Graphics::character(50, 400, '!');
    Graphics::stroke(0xFFFFFF);
    Graphics::string(100, 400, "this is a test string");

	// draw a thick-edged polygon
	Graphics::strokeWeight(3);
    Graphics::fill(0x888888);
    Graphics::noFill();
	Graphics::beginShape(QUADS);
		//Graphics::polygon(polygon);
		Graphics::vertices(polygon);
	Graphics::endShape();
	Graphics::stroke(0xFF0000);
	Graphics::beginShape(POINTS);
		//Graphics::polygon(polygon);
		Graphics::vertices(polygon);
	Graphics::endShape();
    Graphics::strokeWeight(1);
    
    // cross alpha rects
    Graphics::noStroke();
    Graphics::fill(Color(0xFF, 0, 0, 0x66));
    Graphics::rectangle(600, 50, 50, 50);
    Graphics::fill(Color(0, 0, 0xFF, 0x66));
    Graphics::rectangle(625, 75, 50, 50);
	
	Graphics::stroke(0xFF0000);
	Graphics::fill(0x999900);
	Graphics::arc(400, 25, 50, 0.0, 90.0);
	
	Graphics::bezier(85, 20, 10, 10, 90, 90, 15, 80);
	
	Graphics::pop();
}

void ClassTests::testDrawTexture()
{
	Graphics::rectMode(CORNER);
	drawTexture.fill(0xFF000000);
	Graphics::setDrawTexture(drawTexture);
		Graphics::fill(0x00FF00);
		Graphics::rectangle(0, 0, 50, 50);
		Graphics::stroke(0x0000FF);
		Graphics::strokeWeight(2);
		Graphics::line(10, 10, 30, 30);
		Graphics::strokeWeight(0);
		Graphics::stroke(0xFF0000);
		Graphics::noFill();
		Graphics::rectangle(0, 0, drawTexture.width()-1, drawTexture.height()-1);
		Graphics::stroke(0xFFFFFF);
		Graphics::string(10, 10, "draw tex");
	Graphics::clearDrawTexture();
	drawTexture.draw(Graphics::getWidth()-drawTexture.width()-10,
					 Graphics::getHeight()-drawTexture.height()-10);
}

void ClassTests::testImage(int x, int y)
{
	image.draw(x, y);
    imageAlpha.draw(x, y+image.width());
    imagePixels.draw(x+image.width(), y);
}

void ClassTests::testFont(int x, int y)
{
	// chars
	Graphics::fontMode(SOLID);	// fastest
    Graphics::stroke(Color(0xFF, 0x00, 0x00, 128));
	font.draw(x, y, 't');
    
    Graphics::fontMode(BLENDED);	// anti-aliased, slower
    Graphics::stroke(0x00FF00);
    font.draw(x+50, y, '2');
    
    Graphics::fontMode(SHADED);	// blended with a background fill
    Graphics::stroke(0x000FF);	// font foreground
    Graphics::fill(0x666666);	// font background
    Font::Stream(font, x+100, y) << '3';	// streamer 
    
    // strings
    Graphics::fontMode(SOLID);
    Graphics::stroke(0xFFFF00);
	font.draw(x, y+50, "this is some solid text");
    
    Graphics::fontMode(SHADED);
    Graphics::stroke(0x00FFFF);
    Graphics::fill(0x333333);
    Font::Stream(font, x, y+80) << "this is some shaded text";
    
    Graphics::fontMode(BLENDED);
    Graphics::stroke(0x00FF00);
    Font::Stream(font, x, y+110) << "this is some blended text";
}
