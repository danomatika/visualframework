/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009
==============================================================================*/
#ifndef VISUAL_OSC_SENDER_H
#define VISUAL_OSC_SENDER_H

#include "Net.h"

#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

#define OSC_SENDER_BUFFER_SIZE 1024

namespace visual {

/**
    \class  OscSender
    \brief  send OSC packets through buffer using << stream
**/
class OscSender : public osc::OutboundPacketStream
{
    public:

        OscSender(std::string addr="127.0.0.1", unsigned int port=8000);

        /// setup the socket address and port
        void setAddr(std::string addr, unsigned int port=8000);

        /// send the message
        void send();

        /// get the ip addr and port
        std::string getAddr()   {return _sAddr;}
        unsigned int getPort()  {return _uiPort;}

    private:

        UdpTransmitSocket* _socket;
        char _buffer[1024];

        std::string _sAddr;
        unsigned int _uiPort;
};

} // namespace

#endif // VISUAL_OSC_SENDER_H
