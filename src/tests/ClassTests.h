/*==============================================================================
    Copyright (c) Ars Electronica Futurelab, 2009.
    Dan Wilcox <Daniel.Wilcox@aec.at>
==============================================================================*/
#ifndef CLASSTESTS_H
#define CLASSTESTS_H

#include <visualframework.h>

using namespace std;
using namespace visual;

// convenience class
class OscReceiver : public OscListener
{
    protected:

        void process(const osc::ReceivedMessage& m,
                     const IpEndpointName& remoteEndpoint);
};

// convenience class
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

        void testLog();

        void testXmlFile(string file);

        void startTestOscListener();

        void stopTestOscListener();

        void testOscSender();

        void startTestUdpListener();

        void stopTestUdpListener();

        void testUdpSender();

        void testGraphicsPrimitives();

    private:

        OscReceiver oscListener;
        UdpReceiver udpListener;

        vector<Point> points;
};

#endif // CLASSTESTS_H
