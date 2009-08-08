#include "OscListener.h"

OscListener::OscListener(int port) : _listenThread(), _iPort(port)
{
    //_listenThread.socket = NULL;
    process_func_ptr = NULL;
}

void OscListener::startListening()
{
    _listenThread.socket =
        new UdpListeningReceiveSocket(IpEndpointName(IpEndpointName::ANY_ADDRESS, _iPort), this);

    _listenThread.startThread();
}

void OscListener::stopListening()
{
    // stop osc listener
    _listenThread.socket->AsynchronousBreak();

    // stop thread
    _listenThread.stopThread();

    // memory management
    delete _listenThread.socket;
    _listenThread.socket = NULL;

}

/* ***** Private Functions ***** */

void OscListener::ProcessMessage(const osc::ReceivedMessage& m, const IpEndpointName& remoteEndpoint)
{
    try
    {
        if(process_func_ptr != NULL)
        {
            process_func_ptr(m, remoteEndpoint);
        }
    }
    catch(osc::Exception& e)
    {
        LOG_ERROR << "OSCListener port " << _iPort << ": error while parsing message: \""
                  << m.AddressPattern() << "\" \"" << e.what()<< "\"" << std::endl;
    }
}
