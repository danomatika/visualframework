/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009
==============================================================================*/
#ifndef VISUAL_OSC_LISTENER_H
#define VISUAL_OSC_LISTENER_H

#include <osc/OscReceivedElements.h>
#include <osc/OscPacketListener.h>
#include <ip/UdpSocket.h>

#include "Net.h"
#include "../Thread.h"

namespace visual {

/**
    \class  OscListener
    \brief  a threaded OSC listener

    set the processing function to match messages
**/
class OscListener : public osc::OscPacketListener, protected Thread
{
    public:

        /// calls setPort automatically
        OscListener(unsigned int port=7000);

        ~OscListener();

        /// setup the udp socket using the given port
        void setPort(unsigned int port);

        /// start the listening thread, opens connection
        void startListening();

        /// stop the listening thread, closes connection
        void stopListening();

        /// is the thread running?
        bool isListening() {return isThreadRunning();}

        /// get port num
        unsigned int getPort() {return _uiPort;}

    protected:

        /// callback to implement
        virtual void process(const osc::ReceivedMessage& m,
                             const IpEndpointName& remoteEndpoint) = 0;

    private:

        // virtual callback from oscpack
        virtual void ProcessMessage(const osc::ReceivedMessage& m,
                                    const IpEndpointName& remoteEndpoint);

        // thread main loop
        void run();

        bool _bSetup;
        unsigned int _uiPort;
        UdpListeningReceiveSocket* _socket;
};

} // namespace

#endif // VISUAL_OSC_LISTENER_H
