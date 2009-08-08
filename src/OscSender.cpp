#include "OscSender.h"

OscSender::OscSender(std::string addr, int port) :
    osc::OutboundPacketStream(_buffer, OSC_SENDER_BUFFER_SIZE),
    _strAddr(addr), _iPort(port)
{
    _socket = new UdpTransmitSocket(IpEndpointName(_strAddr.c_str(), _iPort));
}

void OscSender::send()
{
    _socket->Send(this->Data(), this->Size());
    Clear();
}

void OscSender::setAddr(std::string addr, int port)
{
    // dont rebuild object if the same address and port
    if(_strAddr == addr && _iPort == port)
        return;

    _strAddr = addr;
    _iPort = port;
    delete _socket;
    _socket = new UdpTransmitSocket(IpEndpointName(_strAddr.c_str(), _iPort));
}
