/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009
==============================================================================*/
#include "Net.h"

namespace visual {

bool Net::_bSetup = false;
std::string Net::_error = "";

bool Net::init()
{
    if(_bSetup)
        return true;    // already setup

    if(SDLNet_Init() < 0)
    {
        LOG_ERROR << "Net: Could not init SDL_net: " << SDLNet_GetError() << std::endl;
        return false;
    }

    _bSetup = true;

    return false;
}

void Net::quit()
{
    if(!_bSetup)
        return;     // not setup

    SDLNet_Quit();
}

std::string Net::getError()
{
    _error = SDLNet_GetError();
    return _error;
}

} // namespace
