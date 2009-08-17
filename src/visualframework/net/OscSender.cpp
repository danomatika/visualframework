/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009
==============================================================================*/
#include "OscSender.h"

namespace visual {

OscSender::OscSender(std::string addr, unsigned int port) :
    osc::OutboundPacketStream(_buffer, OSC_SENDER_BUFFER_SIZE),
    _sAddr(addr), _uiPort(port)
{
    _socket = new UdpTransmitSocket(IpEndpointName(_sAddr.c_str(), _uiPort));
}

void OscSender::send()
{
    _socket->Send(this->Data(), this->Size());
    Clear();
}

void OscSender::setAddr(std::string addr, unsigned int port)
{
    // dont rebuild object if the same address and port
    if(_sAddr == addr && _uiPort == port)
        return;

    _sAddr = addr;
    _uiPort = port;
    delete _socket;
    _socket = new UdpTransmitSocket(IpEndpointName(_sAddr.c_str(), _uiPort));
}

} // namespace
