#include "UdpListener.h"

namespace visual {

UdpListener::UdpListener(unsigned int port) : Thread("UdpListener", Thread::LOOP),
     _bSetup(false), _packet(NULL)
{
    if(!Net::isSetup())
    {
        Net::init();
    }

    setPort(port);
}

UdpListener::~UdpListener()
{}

void UdpListener::startListening()
{
    if(!_bSetup)
    {
        LOG_WARN << "UdpListener: Cannot start thread, port not set" << std::endl;
        return;
    }

    startThread();
}

void UdpListener::stopListening()
{
    if(!_bSetup)
        return;

    stopThread();
}

void UdpListener::setPort(unsigned int port)
{
    if(isThreadRunning())
    {
        LOG_WARN << "UdpListener: Cannot set port while thread is running" << std::endl;
        return;
    }

    // allocate packet memory (if not allocated)
    if(_packet == NULL)
    {
        if(!(_packet = SDLNet_AllocPacket(VISUAL_MAX_PACKET_LEN)))
        {
            LOG_ERROR << "UdpListener: Could not allocate packet:" << SDLNet_GetError() << std::endl;
            return;
        }
    }

    _uiPort = port;

    // free the existing socket
    if(_bSetup)
    {
        SDLNet_UDP_Close(_socket);
    }

    // try to open the socket
	if(!(_socket = SDLNet_UDP_Open(_uiPort)))
	{
		LOG_ERROR << "UdpListener: Could not open socket on port " << _uiPort << ": "
                  <<  SDLNet_GetError() << std::endl;
		return;
	}

    _bSetup = true;
}

/* ***** Protected Functions ***** */

void UdpListener::run()
{
    // handle packets ...
    if(SDLNet_UDP_Recv(_socket, _packet))
    {
        process((char*) _packet->data, _packet->len);
    }

    usleep(10000);   // dont eat the cpu
}

} // namespace
