/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009

    SDL_net tutorial: http://gpwiki.org/index.php/SDL:Tutorial:Using_SDL_net
==============================================================================*/
#include "UdpSender.h"

#define UDP_SENDER_MAX_PACKET_LEN   1024

#include <exception>

namespace visual {

UdpSender::UdpSender() : _bSetup(false), _packet(NULL)
{
    if(!Net::isSetup())
    {
        Net::init();
    }
}

UdpSender::UdpSender(std::string addr, unsigned int port) :
    _bSetup(false), _packet(NULL)
{
    if(!Net::isSetup())
    {
        Net::init();
    }

    setAddr(addr, port);
}

UdpSender::~UdpSender()
{
    if(_bSetup)
    {
        if(_packet != NULL)
            SDLNet_FreePacket(_packet);

        SDLNet_UDP_Close(_socket);
    }
}

void UdpSender::setAddr(std::string addr, unsigned int port)
{
    _sAddr = addr;
    _uiPort = port;

    // free the existing socket
    if(_bSetup)
    {
        SDLNet_UDP_Close(_socket);
    }

    // try to open the socket
	if(!(_socket = SDLNet_UDP_Open(0)))
	{
		LOG_ERROR << "UdpSender: Could not open socket on port " << _uiPort << ": "
                  <<  SDLNet_GetError() << std::endl;
		return;
	}

	// Resolve server name
	if(SDLNet_ResolveHost(&_destination, _sAddr.c_str(), _uiPort) == -1)
	{
	    LOG_ERROR << "UdpSender: Could not resolve hostname " << _sAddr
                  << " on port " <<  _uiPort<< ": " << SDLNet_GetError() << std::endl;
		return;
	}
}

bool UdpSender::send(char* buffer, unsigned int length)
{
    if(buffer == NULL || _socket == NULL)
        return false;

    // allocate packet memory (if not allocated)
    if(_packet == NULL)
    {
        if(!(_packet = SDLNet_AllocPacket(UDP_SENDER_MAX_PACKET_LEN)))
        {
            LOG_ERROR << "UdpSender: Could not allocate packet:" << SDLNet_GetError() << std::endl;
            return false;
        }
    }

    _packet->address.host = _destination.host;
    _packet->address.port = _destination.port;

    unsigned int position = 0, numSend = 0;
    while(position < length)
    {
        // how many bytes to send?
        numSend = length - position;
        if(numSend > VISUAL_MAX_PACKET_LEN)
        {
            numSend = VISUAL_MAX_PACKET_LEN;
        }

        // load packet
        try
        {
            _packet->len = numSend;
            _packet->maxlen = VISUAL_MAX_PACKET_LEN;
            memcpy(_packet->data, buffer+position, numSend);
        }
        catch(std::exception& e)
        {
            LOG_ERROR << "UdpSender: memcpy failed to load packet: " << e.what() << std::endl;
            return false;
        }

        // send
		if(SDLNet_UDP_Send(_socket, -1, _packet) == 0)
		{
		    LOG_WARN << "UdpSender: Send error: " << SDLNet_GetError() << std::endl;
		    return false;
		}

		// move index position
		position += numSend;
	}

    return true;
}

} // namespace
