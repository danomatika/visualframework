#ifndef OSCLISTENER_H
#define OSCLISTENER_H

#include <osc/OscReceivedElements.h>
#include <osc/OscPacketListener.h>
#include <ip/UdpSocket.h>

#include <SDL/SDL_thread.h>

#include "Common.h"
#include "Thread.h"

/**
    \class  OscListener
    \brief  a threaded OSC listener

    set the processing fucntion to match messages
**/
class OscListener : public osc::OscPacketListener
{
    public:

        OscListener(int port=7000);

        /// set processing function
        void processFunc(void (*func)(const osc::ReceivedMessage& m,
                                      const IpEndpointName& remoteEndpoint))
            {process_func_ptr = func;}

        /// start the listening thread, opens connection
        void startListening();

        /// stop the listening thread, closes connection
        void stopListening();

        /// is the thread running?
        bool isListening() {return _listenThread.isThreadRunning();}

        /// get port num
        int getPort() {return _iPort;}

        /// set port num
        void setPort(int port) {_iPort = port;}


    protected:

        /// virtual callback from oscpack
        virtual void ProcessMessage(const osc::ReceivedMessage& m,
                                    const IpEndpointName& remoteEndpoint);

    private:

        // convenience thread class
        class ListenThread : public Thread
        {
            public:
                ListenThread() : Thread("OscListener") {}
                UdpListeningReceiveSocket* socket;
            private:
                void run()
                {
                    socket->Run();
                }
        } _listenThread;

        /// processing function pointer
        void (*process_func_ptr)(const osc::ReceivedMessage&, const IpEndpointName&);

        int _iPort;
};

#endif // OSCLISTENER_H
