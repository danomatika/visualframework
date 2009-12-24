/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009
==============================================================================*/
#include "OscSender.h"

namespace visual {

OscSender::OscSender() :
    osc::OutboundPacketStream(_buffer, OSC_SENDER_BUFFER_SIZE),
    _socket(NULL), _sAddr(""), _uiPort(0)
{}

OscSender::OscSender(std::string addr, unsigned int port) :
    osc::OutboundPacketStream(_buffer, OSC_SENDER_BUFFER_SIZE),
    _socket(NULL), _sAddr(addr), _uiPort(port)
{
    setup(_sAddr, _uiPort);
}

void OscSender::send()
{
    if(_socket == NULL)
    {
        LOG_WARN << "OscSender: cannot send, socket not setup"<<std::endl;
        return;
    }

    _socket->Send(this->Data(), this->Size());
    Clear();
}

void OscSender::setup(std::string addr, unsigned int port)
{
    // dont rebuild object if the same address and port
    //if(_sAddr == addr && _uiPort == port)
    //    return;

    _sAddr = addr;
    _uiPort = port;

    if(_socket != NULL)
    {
        delete _socket;
    }

    _socket = new UdpTransmitSocket(IpEndpointName(_sAddr.c_str(), _uiPort));
}

} // namespace
