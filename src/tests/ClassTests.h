/*==============================================================================
    Copyright (c) Ars Electronica Futurelab, 2009.
    Dan Wilcox <Daniel.Wilcox@aec.at>
==============================================================================*/
#ifndef CLASSTESTS_H
#define CLASSTESTS_H

#include <visualframework.h>

using namespace std;
using namespace visual;

class ClassTests
{
    public:

        ClassTests();

        virtual ~ClassTests();

        void testLog();

        void testXmlFile(string file);

        static void processOSC(const osc::ReceivedMessage& m, const IpEndpointName& remoteEndpoint);

        void startTestOscListener();

        void stopTestOscListener();

        void testOscSender();

        void testGraphicsPrimitives();

    private:

        OscListener listener;

};

#endif // CLASSTESTS_H
