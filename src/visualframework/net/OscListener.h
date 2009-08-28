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
    \class  OscObject
    \brief  derive this class to add to an OscListener

    set the processing function to match messages
**/
class OscObject
{
    friend class OscListener;

    protected:

        /// callback to implement, return true if message handled
        virtual bool processOscMessage(const osc::ReceivedMessage& m) = 0;
};

class OscObject;

/**
    \class  OscListener
    \brief  a threaded OSC listener

    set the processing function to match messages or add OscObjects
**/
class OscListener : public osc::OscPacketListener, protected Thread
{
    public:

        OscListener();
        virtual ~OscListener();

        /// calls setPort automatically
        OscListener(unsigned int port);

        /// setup the udp socket using the given port
        void setup(unsigned int port);

        /// start the listening thread, opens connection
        void startListening();

        /// stop the listening thread, closes connection
        void stopListening();

        void addObject(OscObject* object);
        void removeObject(OscObject* object);

        /// is the thread running?
        bool isListening() {return isThreadRunning();}

        /// get port num
        unsigned int getPort() {return _uiPort;}

    protected:

        /// callback, returns true if message handled
        virtual bool process(const osc::ReceivedMessage& m) {return false;}

    private:

        // virtual callback from oscpack
        virtual void ProcessMessage(const osc::ReceivedMessage& m,
                                    const IpEndpointName& remoteEndpoint);

        // thread main loop
        void run();

        bool _bSetup;
        unsigned int _uiPort;
        UdpListeningReceiveSocket* _socket;

        std::vector<OscObject*> _objectList;    /// list of osc objects
};

} // namespace

#endif // VISUAL_OSC_LISTENER_H
