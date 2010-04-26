/*==============================================================================
    Copyright (c) Ars Electronica Futurelab, 2009.
    Dan Wilcox <Daniel.Wilcox@aec.at>
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
        
        Image image;
        Font font;

        PointList polygon;
        
        Timer testTimer;
};

#endif // CLASSTESTS_H
