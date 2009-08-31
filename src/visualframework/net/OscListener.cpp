/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009
==============================================================================*/
#include "OscListener.h"

#include <algorithm>

namespace visual {

OscListener::OscListener(std::string rootAddress) :
    Thread("OscListener"), oscRootAddress(rootAddress),
     _bSetup(false), _bIgnoreMessages(false), _uiPort(0), _socket(NULL)
{}

OscListener::OscListener(unsigned int port, std::string rootAddress) :
     Thread("OscListener"), oscRootAddress(rootAddress),
    _bSetup(false), _bIgnoreMessages(false), _socket(NULL)
{
    setup(port);
}

OscListener::~OscListener()
{
    // memory management
    if(_socket != NULL)
    {
        delete _socket;
        _socket = NULL;
    }

    _objectList.clear();
}

void OscListener::setup(unsigned int port)
{
    if(isThreadRunning())
    {
        LOG_WARN << "OscListener: Cannot set port while thread is running" << std::endl;
        return;
    }

    _uiPort = port;

    try
    {
        // clear old socket before trying to create a new one
        if(_socket != NULL)
        {
            delete _socket;
        }

        // create the new socket
        _socket = new UdpListeningReceiveSocket(
            IpEndpointName(IpEndpointName::ANY_ADDRESS, _uiPort), this);
    }
    catch(std::exception& e)
    {
        LOG_ERROR << "OscListener: Could not open socket on port "
                  << _uiPort<< ": " << e.what() << std::endl;
        return;
    }

    _bSetup = true;
}

void OscListener::startListening()
{
    if(!_bSetup)
    {
        LOG_WARN << "OscListener: Cannot start thread, address not set" << std::endl;
        return;
    }

    startThread();
}

void OscListener::stopListening()
{
    if(!_bSetup)
        return;

    // stop osc listener
    _socket->AsynchronousBreak();

    // reset ignore
    _bIgnoreMessages = false;
}

void OscListener::addObject(OscObject* object)
{
    if(object == NULL)
    {
        LOG_WARN << "OscListener: Cannot add NULL object" << std::endl;
        return;
    }

    _objectList.push_back(object);
}

void OscListener::removeObject(OscObject* object)
{
    if(object == NULL)
    {
        LOG_WARN << "OscListener: Cannot remove NULL object" << std::endl;
        return;
    }

    // find object in list and remove it
    std::vector<OscObject*>::iterator iter;
    iter = find(_objectList.begin(), _objectList.end(), object);
    if(iter != _objectList.end())
    {
        _objectList.erase(iter);
    }
}

/* ***** Protected Functions ***** */

void OscListener::ProcessMessage(const osc::ReceivedMessage& m, const IpEndpointName& remoteEndpoint)
{
    // ignore any incoming messages?
    if(_bIgnoreMessages)
        return;

    try
    {
        // call any attached objects
        std::vector<OscObject*>::iterator iter;
        for(iter = _objectList.begin(); iter != _objectList.end(); iter++)
        {
            // try to process message
            if((*iter) != NULL)
            {
                if((*iter)->processOsc(m))
                    return;
            }
            else    // bad object, so erase it
            {
                _objectList.erase(iter);
                LOG_WARN << "OscListner: removed NULL object" <<std::endl;
            }
        }

        // user callback
        if(process(m))
            return;

        LOG_DEBUG << "OscListener: unhandled message \"" << m.AddressPattern()
            << "\" with type tag \"" << m.TypeTags() << "\"" << std::endl;
    }
    catch(osc::Exception& e)
    {
        LOG_ERROR << "OSCListener: error while parsing message: "
                  << "\"" << m.AddressPattern() << "\" on port "
                  << _uiPort << ": \"" << e.what()<< "\"" << std::endl;
    }
}

void OscListener::run()
{
    // start thread receiving loop
    _socket->Run();
}

} // namespace
