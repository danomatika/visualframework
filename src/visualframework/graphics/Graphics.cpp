/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009
==============================================================================*/
#include "Graphics.h"

#include <algorithm>
#include <sstream>

#include "../Log.h"
#include <SDL/SDL_gfxPrimitives.h>

namespace visual {

// ***** STATIC VARIABLES *****
SDL_Surface* Graphics::_screen  = NULL;

unsigned int Graphics::_iWidth           = 0;
unsigned int Graphics::_iHeight          = 0;
unsigned int Graphics::_iDepth           = 0;

uint32_t Graphics::_ui32VideoFlags  = 0;
Graphics::Type Graphics::_type      = Graphics::UNKNOWN;
Graphics::Mode Graphics::_mode      = Graphics::WINDOW;
std::string Graphics::_sTitle       = "";

Color Graphics::_strokeColor;
Color Graphics::_fillColor;
bool Graphics::_bStroke = true;
bool Graphics::_bFill   = true;

Graphics::RectMode Graphics::_rectMode = CENTER;

std::string Graphics::_error = "";

// ***** LOCAL VARIABLES *****
int _x1, _y1, _x2, _y2; // computed rectangle points

#define MAX_POLY_POINTS  512
Sint16 _vx[MAX_POLY_POINTS], _vy[MAX_POLY_POINTS];    // point int buffers for polygon()


bool Graphics::init(unsigned int w, unsigned int h, unsigned int depth, Type type)
{
    _iWidth = w;
    _iHeight = h;
    _iDepth = depth;
    _ui32VideoFlags = 0;
    _type = type;

    // initialize SDL video
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        LOG_ERROR << "Unable to init SDL Video: %s" << SDL_GetError() << std::endl;
        return false;
    }

    // set proper flags for mode
    _ui32VideoFlags = _type|SDL_DOUBLEBUF|_mode;

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    return true;
}

// sort resolutions by area in descending order
bool cmpRes(SDL_Rect* a, SDL_Rect* b )
{
    int areaA = a->w*a->h;
    int areaB = b->w*b->h;
    return areaA < areaB;
}

std::vector<SDL_Rect*> Graphics::getResolutions()
{
    // get available fullscreen modes
    SDL_Rect** modes;
    std::vector<SDL_Rect*> resolutions;
    modes = SDL_ListModes(NULL, SDL_FULLSCREEN|_type);

    // check if there are any modes available
    if(modes == (SDL_Rect**)0)
    {
        LOG_WARN << "No resolutions available!" << std::endl;
    }

    // check if our resolution is restricted
    if(modes == (SDL_Rect**)-1)
    {
        LOG << "All resolutions available" << std::endl;
    }

    else
    {
        for(int i=0; modes[i] != NULL; ++i)
        {
            resolutions.push_back(modes[i]);
        }
    }

    // sort into descending order
    std::sort(resolutions.begin(), resolutions.end(), cmpRes);

    return resolutions;
}

void Graphics::setWindowTitle(std::string title)
{
    _sTitle = title;
    SDL_WM_SetCaption(_sTitle.c_str(), NULL);
}

bool Graphics::setWindowIcon(std::string bitmap)
{
    SDL_Surface *icon = SDL_LoadBMP(bitmap.c_str());
    if(icon == NULL)
    {
        LOG_ERROR << "Unable to load window icon \"" << bitmap << "\": "
                  << SDL_GetError() << std::endl;
        return false;
    }

    SDL_WM_SetIcon(icon, NULL);

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

    LOG << "Setting: " << getModeString() << std::endl;

    if(title != "")
    {
        _sTitle = title;
        SDL_WM_SetCaption(_sTitle.c_str(), NULL);
    }

    return true;
}

bool Graphics::toggleFullscreen()
{
    if(_screen == NULL)
    {
        LOG_ERROR << "Unable to toggle fullscreen: window does not exist" << std::endl;
        return false;
    }

    SDL_FreeSurface(_screen);

    switch(_mode)
    {
        case WINDOW:
            _mode = FULLSCREEN;
            break;

        case FULLSCREEN:
            _mode = WINDOW;
            break;
    }

    // set proper flags for mode
    _ui32VideoFlags = _type|SDL_DOUBLEBUF|_mode;

    return createWindow(_sTitle);
}

bool Graphics::changeResolution(unsigned int w, unsigned int h)
{
    if(_screen == NULL)
    {
        LOG_ERROR << "Unable to change resolution: window does not exist" << std::endl;
        return false;
    }

    SDL_FreeSurface(_screen);

    // set new resolution
    _iWidth = w;
    _iHeight = h;

    return createWindow(_sTitle);
}

std::string Graphics::getModeString()
{
    std::ostringstream stream;

    switch(_type)
    {
        case SOFTWARE:
            stream << "SDL_SWSURFACE";
            break;
        case HARDWARE:
            stream << "SDL_HWSURFACE";
            break;
    }
    stream << " " << _iWidth << "x" << _iHeight << "@" << _iDepth << "bit ";
    switch(_mode)
    {
        case WINDOW:
            stream << "window";
            break;
        case FULLSCREEN:
            stream << "fullscreen";
            break;
    }

    return stream.str();
}

// ***** global color *****
void Graphics::stroke(unsigned int color)
{
    _strokeColor.set(color);
    _bStroke = true;
}

void Graphics::stroke(Color& color)
{
    _strokeColor = color;
    _bStroke = true;
}

void Graphics::fill(unsigned int color)
{
    _fillColor.set(color);
    _bFill = true;
}

void Graphics::fill(Color& color)
{
    _fillColor = color;
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
    if(_screen == NULL)
    {
        LOG_ERROR << "Graphics::point: Window not setup yet" << std::endl;
        return;
    }

    if(_bStroke)
    {
        pixelColor(_screen, x, y, _strokeColor.rgba);
    }
}

void Graphics::line(int x1, int y1, int x2, int y2)
{
    if(_screen == NULL)
    {
        LOG_ERROR << "Graphics::line: Window not setup yet" << std::endl;
        return;
    }

    if(_bStroke)
    {
        lineColor(_screen, x1, y1, x2, y2, _strokeColor.rgba);
    }
}

void Graphics::rectangle(int x, int y, int w, int h, RectMode mode)
{
    if(_screen == NULL)
    {
        LOG_ERROR << "Graphics::rectangle: Window not setup yet" << std::endl;
        return;
    }

    _rectMode = mode;
    if(mode == CENTER)
    {
        _x1 = x-w/2;
        _x2 = x+w/2;
        _y1 = y-h/2;
        _y2 = y+h/2;
    }
    else
    {
        _x1 = x;
        _x2 = x+w;
        _y1 = y;
        _y2 = y+h;
    }

    if(_bFill)
    {
        boxColor(_screen, _x1, _y1, _x2, _y2, _fillColor.rgba);
    }

    if(_bStroke)
    {
        rectangleColor(_screen, _x1, _y1, _x2, _y2, _strokeColor.rgba);
    }
}

void Graphics::circle(int x, int y, int r)
{
    if(_screen == NULL)
    {
        LOG_ERROR << "Graphics::circle: Window not setup yet" << std::endl;
        return;
    }

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
    if(_screen == NULL)
    {
        LOG_ERROR << "Graphics::ellipse: Window not setup yet" << std::endl;
        return;
    }

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
    if(_screen == NULL)
    {
        LOG_ERROR << "Graphics::triangle: Window not setup yet" << std::endl;
        return;
    }

    if(_bFill)
    {
        filledTrigonColor(_screen, x1, y1, x2, y2, x3, y3, _fillColor.rgba);
    }

    if(_bStroke)
    {
        trigonColor(_screen, x1, y1, x2, y2, x3, y3, _strokeColor.rgba);
    }
}

void Graphics::polygon(std::vector<Point> points)
{
    if(_screen == NULL)
    {
        LOG_ERROR << "Graphics::polygon: Window not setup yet" << std::endl;
        return;
    }

    // load point vector into int buffers
    for(unsigned int i = 0; i < points.size() && i < MAX_POLY_POINTS; i++)
    {
        Point& p = points.at(i);
        _vx[i] = p.x;
        _vy[i] = p.y;
    }

    if(_bFill)
    {
        filledPolygonColor(_screen, _vx, _vy, points.size(), _fillColor.rgba);
    }

    if(_bStroke)
    {
        polygonColor(_screen, _vx, _vy, points.size(), _strokeColor.rgba);
    }
}

void Graphics::character(int x, int y, char c)
{
    if(_screen == NULL)
    {
        LOG_ERROR << "Graphics::character: Window not setup yet" << std::endl;
        return;
    }

    if(_bStroke)
    {
        characterColor(_screen, x, y, c, _strokeColor.rgba);
    }
}

void Graphics::string(int x, int y, std::string line)
{
    if(_screen == NULL)
    {
        LOG_ERROR << "Graphics::string: Window not setup yet" << std::endl;
        return;
    }

    if(_bStroke)
    {
        stringColor(_screen, x, y, line.c_str(), _strokeColor.rgba);
    }
}

std::string Graphics::getLastError()
{
    _error = SDL_GetError();
    SDL_ClearError();
    return _error;
}

unsigned int Graphics::getMillis()
{
    return SDL_GetTicks();
}

} // namespace
