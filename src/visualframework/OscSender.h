/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009
==============================================================================*/
#ifndef VISUAL_OSC_SENDER_H
#define VISUAL_OSC_SENDER_H

#include "Common.h"

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

        OscSender(std::string addr="127.0.0.1", int port=8000);

        /// send the message
        void send();

        /// set the address and port
        void setAddr(std::string addr, int port=8000);

    private:

        UdpTransmitSocket* _socket;
        char _buffer[1024];

        std::string _strAddr;
        int _iPort;
};

} // namespace

#endif // VISUAL_OSC_SENDER_H
