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
#include "OscObject.h"

namespace visual {

/**
    \class  OscListener
    \brief  a threaded OSC listener

    set the processing function to match messages or add OscObjects
**/
class OscListener : protected osc::OscPacketListener, protected Thread
{
    public:

        OscListener(std::string rootAddress="");
        virtual ~OscListener();

        /// calls setup automatically
        OscListener(unsigned int port, std::string rootAddress="");

        /* ***** SETUP ***** */

        /// setup the udp socket using the given port
        void setup(unsigned int port);

        /* ***** THREAD CONTROL ***** */

        /// start the listening thread, opens connection
        void startListening();

        /// stop the listening thread, closes connection
        void stopListening();

        /* ***** ATTACH OSC OBJECTS ***** */

        void addObject(OscObject* object);
        void removeObject(OscObject* object);

        /* ***** UTIL ***** */

        /// is the thread running?
        bool isListening() {return isThreadRunning();}

        /// get port num
        unsigned int getPort() {return _uiPort;}

        /// get/set the root address of this object
        inline void setOscRootAddress(std::string rootAddress) {oscRootAddress = rootAddress;}
        inline std::string& getOscRootAddress() {return oscRootAddress;}

        // ignore incoming messages?
        inline void ignoreMessages(bool yesno) {_bIgnoreMessages = yesno;}

    protected:

        /// callback, returns true if message handled
        virtual bool process(const osc::ReceivedMessage& m) {return false;}

        /// the root address of this object, aka something like "/root/test1/string2"
        std::string oscRootAddress;

    private:

        // virtual callback from oscpack
        virtual void ProcessMessage(const osc::ReceivedMessage& m,
                                    const IpEndpointName& remoteEndpoint);

        // thread main loop
        void run();

        bool _bSetup, _bIgnoreMessages;
        unsigned int _uiPort;
        UdpListeningReceiveSocket* _socket;

        std::vector<OscObject*> _objectList;    /// list of osc objects
};

} // namespace

#endif // VISUAL_OSC_LISTENER_H
