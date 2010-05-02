/*==============================================================================
    Copyright (c) Ars Electronica Futurelab, 2009.
    Dan Wilcox <Daniel.Wilcox@aec.at>
==============================================================================*/
#include "ClassTests.h"

ClassTests::ClassTests()
{}

ClassTests::~ClassTests()
{}

void ClassTests::setup()
{
    // load points for polygon
    polygon.push_back(Point(400, 100));
    polygon.push_back(Point(500, 100));
    polygon.push_back(Point(450, 400));
    polygon.push_back(Point(400, 200));
    polygon.push_back(Point(450, 200));

	// load image
	image.load("../data/testImage.jpg");
    image.scale(0.5, 0.5);
    image.pixelate(5, 5);
    //image.resize(320, 240);
    
    // load font
    font.load("../data/ATARCC__.TTF", 25);
    
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

void ClassTests::testLog()
{
    LOG << "Begin testLog()" << endl;

    LOG << "This is a normal log message" << endl;
    LOG_DEBUG << "This is a debug log message" << endl;
    LOG_WARN << "This is a warning message" << endl;
    LOG_ERROR << "This is an error message" << endl << endl;
}

void UdpReceiver::process(UDPpacket* packet)
{
    LOG << "UdpListener: Received message: '";

    for(int i = 0; i < packet->len; i++)
    {
        LOG << packet->data[i];
    }

    LOG << "' len: " << packet->len << endl;
}

void ClassTests::startTestUdpListener()
{
    LOG << "Starting UdpListener on port 8000" << endl;

    udpListener.setup(8000);
    udpListener.startListening();
    LOG << "    UdpListener is running? "
        << udpListener.isListening() << endl;
    LOG << endl;
}

void ClassTests::stopTestUdpListener()
{
    LOG << "Stopping UdpListener" << endl;
    udpListener.stopListening();
    LOG << "    UdpListener is running? "
        << udpListener.isListening() << endl;
    LOG << endl;
}

void ClassTests::testUdpSender()
{
    LOG << "Begin testUdpSender()" << endl;

    UdpSender sender("127.0.0.1", 8000);

    char* text1 = (char*) "hello world";
    LOG << "    sending string '" << text1 << "'" << endl;
    sender.send(text1, strlen(text1)+1);
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
    //Net::freePacket(p);
    sleep(2);

    LOG << endl;
}

void ClassTests::testGraphicsPrimitives()
{
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

    Graphics::stroke(0xFFFF00);
    Graphics::fill(0xAAAAAA);
    Graphics::ellipse(300, 300, 50, 25);

    Graphics::stroke(0x00FFFF);
    Graphics::character(50, 400, '!');
    Graphics::stroke(0xFFFFFF);
    Graphics::string(100, 400, "this is a test string");

    Graphics::fill(0x888888);
    //Graphics::noFill();
    Graphics::polygon(polygon);
}

void ClassTests::testImage(int x, int y)
{
	image.draw(x, y);
}

void ClassTests::testFont(int x, int y)
{
	// chars
	Graphics::fontMode(SOLID);	// fastest
    Graphics::stroke(0xFF0000);
	font.draw('t', x, y);
    
    Graphics::fontMode(BLENDED);	// anti-aliased, slower
    Graphics::stroke(0x00FF00);
    font.draw('2', x+50, y);
    
    Graphics::fontMode(SHADED);	// blended with a background fill
    Graphics::stroke(0x000FF);	// font foreground
    Graphics::fill(0x666666);	// font background
    font.draw('3', x+100, y); 
    
    // strings
    Graphics::fontMode(SOLID);
    Graphics::stroke(0xFFFF00);
	font.draw("this is some solid text", x, y+50);
    
    Graphics::fontMode(SHADED);
    Graphics::stroke(0x00FFFF);
    Graphics::fill(0x333333);
    font.draw("this is some shaded text", x, y+80);
    
    Graphics::fontMode(BLENDED);
    Graphics::stroke(0x00FF00);
    font.draw("this is some blended text", x, y+110);
}
