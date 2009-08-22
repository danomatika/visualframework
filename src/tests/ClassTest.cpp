/*==============================================================================
    Copyright (c) Ars Electronica Futurelab, 2009.
    Dan Wilcox <Daniel.Wilcox@aec.at>
==============================================================================*/
#include "ClassTests.h"

ClassTests::ClassTests()
{
    // load points for ploygon
    points.push_back(Point(400, 100));
    points.push_back(Point(500, 100));
    points.push_back(Point(450, 400));
    points.push_back(Point(400, 200));
    points.push_back(Point(450, 200));
}

ClassTests::~ClassTests()
{}

void ClassTests::testLog()
{
    LOG << "Begin testLog()" << endl;

    LOG << "This is a normal log message" << endl;
    LOG_DEBUG << "This is a debug log message" << endl;
    LOG_WARN << "This is a warning message" << endl;
    LOG_ERROR << "This is an error message" << endl << endl;
}

void ClassTests::testXmlFile(string file)
{
    LOG << "Begin testXmlFile()" << endl;

    TiXmlDocument xmlDoc;
    TiXmlElement* xml = Xml::loadFile(&xmlDoc, file);
    if(xml == NULL)
    {
        LOG << "    Failed to load \"" << file << "\"" << endl;
        return;
    }
    LOG << "    Loaded \"" << file << "\"" << endl;

    // check if the root is correct
    if(xml->ValueStr() != "poetry")
    {
        LOG << "    Doc Root \"" << xml->ValueStr() << "\" != \"poetry\"" << endl;
        return;
    }

    // just print whatever children are there
    TiXmlElement* child = xml->FirstChildElement();
    while(child != NULL)
    {
        LOG << child->ValueStr() << ": " << child->GetText() << endl;
        child = child->NextSiblingElement();
    }

    LOG << endl;
}

void OscReceiver::process(const osc::ReceivedMessage& m, const IpEndpointName& remoteEndpoint)
{
    LOG << "OscListener: Received OSC message to osc addr \"" << m.AddressPattern()
        << "\" with type tag \"" << m.TypeTags() << "\"" << endl;
/*
    osc::ReceivedMessageArgumentIterator argItr = m.ArgumentsBegin();
    osc::ReceivedMessageArgument arg = argItr;

    if((string) m.AddressPattern() == "/test" && (string) m.TypeTags() == "if")
    {
        int i = &arg;
        arg++;
        float f = *arg;
        LOG << "/test i:" << i << " f: " << f << endl;
    }
*/
}

void ClassTests::startTestOscListener()
{
    LOG << "Starting OscListener on port 7000" << endl;

    oscListener.setup(7000);
    oscListener.startListening();
    LOG << "    OscListener is running? "
        << oscListener.isListening() << endl;
    LOG << endl;
}

void ClassTests::stopTestOscListener()
{
    LOG << "Stopping OscListener" << endl;
    oscListener.stopListening();
    LOG << endl;
}

void ClassTests::testOscSender()
{
    LOG << "Begin testOscSender()" << endl;

    OscSender sender("127.0.0.1", 7000);

    LOG << "    sending /test1 10 1 hello" << endl;

    sender << osc::BeginMessage( "/test1" )
           << 10 << 1 << "hello" << osc::EndMessage;
    sender.send();
    sleep(2);

    LOG << "    sending /test2 1 world" << endl;
    sender << osc::BeginMessage( "/test2" )
           << 1 << "world" << osc::EndMessage;
    sender.send();
    sleep(2);

    LOG << endl;
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
    Graphics::polygon(points);
}
