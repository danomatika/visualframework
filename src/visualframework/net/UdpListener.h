#ifndef VISUAL_UDP_LISTENER_H
#define VISUAL_UDP_LISTENER_H

#include "Net.h"
#include "../Thread.h"

#include <SDL/SDL_net.h>

namespace visual {

/**
    \class  UdpListener
    \brief  a threaded UDP listener

    set the processing function to process incoming bytes
**/
class UdpListener : protected Thread
{
    public:

        /// calls setPort automatically
        UdpListener(unsigned int port=8000);

        virtual ~UdpListener();

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
        virtual void process(char* buffer, unsigned int length) = 0;

    private:

        // thread main loop
        void run();

        bool _bSetup;

        unsigned int _uiPort;
        std::string _sAddr;

        UDPsocket   _socket;
        UDPpacket*  _packet;
};

} // namespace

#endif // VISUAL_UDP_LISTENER_H
