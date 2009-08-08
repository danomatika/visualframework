#include "Graphics.h"

#include "Log.h"
#include <SDL/SDL_gfxPrimitives.h>

// statics
SDL_Surface* Graphics::_screen = NULL;
Graphics::Type Graphics::_type = Graphics::UNKOWN;
int Graphics::_iWidth = 0;
int Graphics::_iHeight = 0;
int Graphics::_iDepth = 0;
Color Graphics::_strokeColor;
Color Graphics::_fillColor;
bool Graphics::_bStroke = true;
bool Graphics::_bFill = true;

Graphics::Graphics(int w, int h, int depth, Type type)
{
    _iWidth = w;
    _iHeight = h;
    _iDepth = depth;
    _ui32VideoFlags = 0;
    _type = type;
    _mode = WINDOW;
}

Graphics::~Graphics()
{
    //dtor
}

bool Graphics::init()
{
    // initialize SDL video
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        LOG_ERROR << "Unable to init SDL Video: %s" << SDL_GetError() << std::endl;
        return false;
    }

    LOG << "Setting: ";
    switch(_type)
    {
        case SOFTWARE:
            LOG << "SDL_SWSURFACE";
            break;
        case HARDWARE:
            LOG << "SDL_HWSURFACE";
            break;
    }
    LOG << " " << _iWidth << "x" << _iHeight << "@" << _iDepth << "bit ";
    switch(_mode)
    {
        case WINDOW:
            LOG << "window";
            break;
        case FULLSCREEN:
            LOG << "fullscreen";
            break;
    }
    LOG << std::endl;

    // set proper flags for mode
    _ui32VideoFlags = _type|SDL_DOUBLEBUF|_mode;

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    return true;
}

bool Graphics::createWindow(std::string title)
{
    // create a new window
    _screen = SDL_SetVideoMode(_iWidth, _iHeight, _iDepth, _ui32VideoFlags);
    if(!_screen)
    {
        LOG_ERROR << "Unable to set video: " << SDL_GetError() << std::endl;
        return false;
    }

    _sTitle = title;
    SDL_WM_SetCaption(_sTitle.c_str(), NULL);

    return true;
}

// ***** global color *****
void Graphics::stroke(unsigned int color)
{
    uint8_t r = color >> 16;
    uint8_t g = color >> 8;
    uint8_t b = color;

    _strokeColor.set(r, g, b);
    _bStroke = true;
}

void Graphics::fill(unsigned int color)
{
    uint8_t r = color >> 16;
    uint8_t g = color >> 8;
    uint8_t b = color;

    _fillColor.set(r, g, b);
    _bFill = true;
}

void Graphics::noStroke()
{
    _bStroke = false;
}

void Graphics::noFill()
{
    _bFill = false;
}

// ***** global primitives *****
void Graphics::point(int x, int y)
{
    if(_bStroke)
    {
        pixelColor(_screen, x, y, _strokeColor.rgba);
    }
}

void Graphics::line(int x1, int y1, int x2, int y2)
{
    if(_bStroke)
    {
        lineColor(_screen, x1, y1, x2, y2, _strokeColor.rgba);
    }
}

void Graphics::rectangle(int x, int y, int w, int h)
{
    int x1 = x-w/2;
    int x2 = x+w/2;
    int y1 = y-h/2;
    int y2 = y+h/2;

    if(_bFill)
    {
        boxColor(_screen, x1, y1, x2, y2, _fillColor.rgba);
    }

    if(_bStroke)
    {
        rectangleColor(_screen, x1, y1, x2, y2, _strokeColor.rgba);
    }
}

void Graphics::circle(int x, int y, int r)
{
    if(_bFill)
    {
        filledCircleColor(_screen, x, y, r, _fillColor.rgba);
    }

    if(_bStroke)
    {
        circleColor(_screen, x, y, r, _strokeColor.rgba);
    }
}

void Graphics::ellipse(int x, int y, int rx, int ry)
{
    if(_bFill)
    {
        filledEllipseColor(_screen, x, y, rx, ry, _fillColor.rgba);
    }

    if(_bStroke)
    {
        ellipseColor(_screen, x, y, rx, ry, _strokeColor.rgba);
    }
}

void Graphics::triangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
    if(_bFill)
    {
        filledTrigonColor(_screen, x1, y1, x2, y2, x3, y3, _fillColor.rgba);
    }

    if(_bStroke)
    {
        trigonColor(_screen, x1, y1, x2, y2, x3, y3, _strokeColor.rgba);
    }
}

void Graphics::character(int x, int y, char c)
{
    if(_bStroke)
    {
        characterColor(_screen, x, y, c, _strokeColor.rgba);
    }
}

void Graphics::string(int x, int y, std::string line)
{
    if(_bStroke)
    {
        stringColor(_screen, x, y, line.c_str(), _strokeColor.rgba);
    }
}
