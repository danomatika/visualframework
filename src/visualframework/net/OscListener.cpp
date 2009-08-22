/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009
==============================================================================*/
#include "OscListener.h"

namespace visual {

OscListener::OscListener() :
    Thread("OscListener"), _bSetup(false), _uiPort(0), _socket(NULL)
{}

OscListener::OscListener(unsigned int port) :
    Thread("OscListener"), _bSetup(false), _socket(NULL)
{
    setup(port);
}

OscListener::~OscListener()
{
    // memory management
    if(_socket != NULL)
    {
        delete _socket;
        _socket = NULL;
    }
}

void OscListener::startListening()
{
    if(!_bSetup)
    {
        LOG_WARN << "OscListener: Cannot start thread, address not set" << std::endl;
        return;
    }

    startThread();
}

void OscListener::stopListening()
{
    if(!_bSetup)
        return;

    // stop osc listener
    _socket->AsynchronousBreak();
}

void OscListener::setup(unsigned int port)
{
    if(isThreadRunning())
    {
        LOG_WARN << "OscListener: Cannot set port while thread is running" << std::endl;
        return;
    }

    _uiPort = port;

    try
    {
        // clear old socket before trying to create a new one
        if(_socket != NULL)
        {
            delete _socket;
        }

        // create the new socket
        _socket = new UdpListeningReceiveSocket(
            IpEndpointName(IpEndpointName::ANY_ADDRESS, _uiPort), this);
    }
    catch(std::exception& e)
    {
        LOG_ERROR << "OscListener: Could not open socket on port "
                  << _uiPort<< ": " << e.what() << std::endl;
        return;
    }

    _bSetup = true;
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
                  << _uiPort << ": \"" << e.what()<< "\"" << std::endl;
    }
}

void OscListener::run()
{
    _socket->Run();
}

} // namespace
