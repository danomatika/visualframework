/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009
==============================================================================*/
#include "OscListener.h"

namespace visual {

OscListener::OscListener(int port) : Thread("OscListener"), _iPort(port)
{}

void OscListener::startListening()
{
    socket =
        new UdpListeningReceiveSocket(IpEndpointName(IpEndpointName::ANY_ADDRESS, _iPort), this);

    startThread();
}

void OscListener::stopListening()
{
    // stop osc listener
    socket->AsynchronousBreak();

    stopThread();

    // memory management
    delete socket;
    socket = NULL;

}

/* ***** Protected Functions ***** */

void OscListener::ProcessMessage(const osc::ReceivedMessage& m, const IpEndpointName& remoteEndpoint)
{
    try
    {
        // call the callback
        process(m, remoteEndpoint);
    }
    catch(osc::Exception& e)
    {
        LOG_ERROR << "OSCListener: error while parsing message: "
                  << "\"" << m.AddressPattern() << "\" on port "
                  << _iPort << ": \"" << e.what()<< "\"" << std::endl;
    }
}

void OscListener::run()
{
    socket->Run();
}

} // namespace
