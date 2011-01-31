/*==============================================================================

	Graphics.cpp

	visualframework: a simple 2d graphics framework
  
	Copyright (C) 2009, 2010  Dan Wilcox <danomatika@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

==============================================================================*/
#include "Graphics.h"

#include <algorithm>
#include <sstream>

#include "../Log.h"
#include <SDL/SDL_gfxPrimitives.h>
#include "sprig/sprig.h"

// sprig: http://www.sdltutorials.com/a-guide-to-graphics-with-sprig/

#define VISUAL_MAX_TRANSFORMS	5

namespace visual {

// ***** STATIC VARIABLES *****
SDL_Surface* Graphics::_screen  = NULL;

unsigned int Graphics::_iWidth           = 0;
unsigned int Graphics::_iHeight          = 0;
unsigned int Graphics::_iDepth           = 0;

uint32_t Graphics::_ui32VideoFlags  = 0;
GraphicsType Graphics::_type      = UNKNOWN;
GraphicsMode Graphics::_mode      = WINDOW;
std::string Graphics::_sTitle     = "";

Color Graphics::_strokeColor;
Color Graphics::_fillColor;
bool Graphics::_bStroke = true;
bool Graphics::_bFill   = true;

DrawMode Graphics::_rectMode = CORNER;
DrawMode Graphics::_imageMode = CORNER;
FontMode Graphics::_fontMode = SOLID;

uint8_t Graphics::_bezierDetail = 20;

std::vector<Graphics::Transform> Graphics::transforms;
std::vector<Point> Graphics::points;

bool Graphics::init(unsigned int w, unsigned int h, unsigned int depth, GraphicsType type)
{
    _iWidth = w;
    _iHeight = h;
    _iDepth = depth;
    _ui32VideoFlags = 0;
    _type = type;

    // initialize SDL video
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        LOG_ERROR << "Graphics: " << getLastError() << std::endl;
        return false;
    }

    // set proper flags for mode
    _ui32VideoFlags = _type|SDL_DOUBLEBUF|_mode;

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);
	
	// push the default transform
	push();

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

void Graphics::setWindowTitle(const std::string& title)
{
    _sTitle = title;
    SDL_WM_SetCaption(_sTitle.c_str(), NULL);
}

bool Graphics::setWindowIcon(const std::string& bitmapFile)
{
    SDL_Surface *icon = SDL_LoadBMP(bitmapFile.c_str());
    if(icon == NULL)
    {
        LOG_ERROR << "Graphics: " << getLastError() << std::endl;
        return false;
    }

    SDL_WM_SetIcon(icon, NULL);

    return true;
}

bool Graphics::createWindow(const std::string title)
{
	unsigned int bpp = SDL_VideoModeOK(_iWidth, _iHeight, _iDepth, _ui32VideoFlags);
	if(!bpp)
    {
    	LOG_ERROR << "Graphics: " << getLastError() << std::endl;
    	return false;
	}

	// clear?
    if(_screen)
        SDL_FreeSurface(_screen);

    // create a new window
    _screen = SDL_SetVideoMode(_iWidth, _iHeight, _iDepth, _ui32VideoFlags);
    if(!_screen)
    {
        LOG_ERROR << "Graphics: " << getLastError() << std::endl;
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
        throw WindowException();

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

bool Graphics::getShowMouseCursor()
{
	int state = SDL_ShowCursor(SDL_QUERY);
    if(state == SDL_ENABLE)
    	return true;
    return false;
}

void Graphics::showMouseCursor(bool show)
{
	if(show)
    	SDL_ShowCursor(SDL_ENABLE);
    else
    	SDL_ShowCursor(SDL_DISABLE);
}

void Graphics::toggleShowMouseCursor()
{
	int state = SDL_ShowCursor(SDL_QUERY);
    if(state == SDL_ENABLE)
    	SDL_ShowCursor(SDL_DISABLE);
    else
    	SDL_ShowCursor(SDL_ENABLE);
}

bool Graphics::changeResolution(const unsigned int w, const unsigned int h)
{
    if(_screen == NULL)
        throw WindowException();

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

void Graphics::clear(unsigned int color)
{
	clear(Color(color));
}

void Graphics::clear(Color& color)
{
	SDL_FillRect(_screen, NULL, color.get(_screen));
}

void Graphics::swap()
{	
	SDL_Flip(_screen);
}

// ***** global color *****
void Graphics::stroke(const unsigned int color)
{
    _strokeColor.set(color);
    _bStroke = true;
}

void Graphics::stroke(const Color& color)
{
    _strokeColor = color;
    _bStroke = true;
}

void Graphics::fill(const unsigned int color)
{
    _fillColor.set(color);
    _bFill = true;
}

void Graphics::fill(const Color& color)
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

void Graphics::strokeWeight(unsigned int weight)
{
	if(weight == 0)
    	return;
	SPG_PopThickness();
    SPG_PushThickness(weight);
}

void Graphics::smooth()
{
	SPG_PopAA();
    SPG_PushAA(true);
}

void Graphics::noSmooth()
{
    SPG_PopAA();
	SPG_PushAA(false);
}

void Graphics::blend()
{
	SPG_PopBlend();
	SPG_PushBlend(SPG_COMBINE_ALPHA);
}

void Graphics::noBlend()
{
	SPG_PopBlend();
	SPG_PushBlend(SPG_COPY_NO_ALPHA);
}

void Graphics::bezierDetail(const uint8_t detail)
{
	_bezierDetail = detail;
}

// ***** global primitives *****
void Graphics::point(const int x, const int y)
{
    if(_screen == NULL)
        throw WindowException();

	points.push_back(Point(x, y));
	applyTransform();

    if(_bStroke)
    {
        SPG_PixelBlend(_screen, points[0].x, points[0].y, _strokeColor.get(_screen), _strokeColor.A);
    }
	
	points.clear();
}

void Graphics::line(const int x1, const int y1, const int x2, const int y2)
{
    if(_screen == NULL)
        throw WindowException();

	points.push_back(Point(x1, y1));
	points.push_back(Point(x2, y2));
	applyTransform();

    if(_bStroke)
    {
        SPG_LineBlend(_screen, points[0].x, points[0].y, points[1].x, points[1].y,
			_strokeColor.get(_screen), _strokeColor.A);
    }
	
	points.clear();
}

void Graphics::rectangle(const int x, const int y, const int w, const int h)
{
    if(_screen == NULL)
        throw WindowException();

	points.push_back(Point());
	points.push_back(Point());

    if(_rectMode == CENTER)
    {
        points[0].x = x-w/2;
        points[1].x = x+w/2;
        points[0].y = y-h/2;
        points[1].y = y+h/2;
    }
    else
    {
        points[0].x = x;
        points[1].x = x+w;
        points[0].y = y;
        points[1].y = y+h;
    }
	
	applyTransform();
	
    if(_bFill)
    {
        SPG_RectFilledBlend(_screen, points[0].x, points[0].y, points[1].x, points[1].y,
			_fillColor.get(_screen), _fillColor.A);
    }

    if(_bStroke)
    {
        SPG_RectBlend(_screen, points[0].x, points[0].y, points[1].x, points[1].y,
			_strokeColor.get(_screen), _strokeColor.A);
    }
	
	points.clear();
}

void Graphics::circle(const int x, const int y, const int r)
{
    if(_screen == NULL)
        throw WindowException();

	points.push_back(Point(x, y));
	applyTransform();
	Transform& t = transforms.back();

    if(_bFill)
    {
        SPG_CircleFilledBlend(_screen, points[0].x, points[0].y, r*t.getScaleAvg(), _fillColor.get(_screen), _fillColor.A);
    }

    if(_bStroke)
    {
        SPG_CircleBlend(_screen, points[0].x, points[0].y, r*t.getScaleAvg(), _strokeColor.get(_screen), _strokeColor.A);
    }
	
	points.clear();
}

void Graphics::ellipse(const int x, const int y, const int rx, const int ry)
{
    if(_screen == NULL)
        throw WindowException();

	points.push_back(Point(x, y));
	applyTransform();
	Transform& t = transforms.back();

    if(_bFill)
    {
        SPG_EllipseFilledBlend(_screen, points[0].x, points[0].y, rx*t.getScaleX(), ry*t.getScaleY(),
			_fillColor.get(_screen), _fillColor.A);
    }

    if(_bStroke)
    {
        SPG_EllipseBlend(_screen, points[0].x, points[0].y, rx*t.getScaleX(), ry*t.getScaleY(),
			_strokeColor.get(_screen), _strokeColor.A);
    }
	
	points.clear();
}

void Graphics::triangle(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3)
{
    if(_screen == NULL)
        throw WindowException();

	points.push_back(Point(x1, y1));
	points.push_back(Point(x2, y2));
	points.push_back(Point(x3, y3));
	applyTransform();

    if(_bFill)
    {
        SPG_TrigonFilledBlend(_screen, points[0].x, points[0].y, points[1].x, points[1].y, points[2].x, points[2].y, 
			_fillColor.get(_screen), _fillColor.A);
    }

    if(_bStroke)
    {
        SPG_TrigonBlend(_screen, points[0].x, points[0].y, points[1].x, points[1].y, points[2].x, points[2].y,
			_strokeColor.get(_screen), _strokeColor.A);
    }
	
	points.clear();
}

void Graphics::polygon(const PointList& points)
{
    if(_screen == NULL)
        throw WindowException();

	Graphics::points = points;
	applyTransform();

    if(_bFill)
    {
        SPG_PolygonFilledBlend(_screen, Graphics::points.size(), (SPG_Point*) &Graphics::points[0], _fillColor.get(_screen), _fillColor.A);
    }

    if(_bStroke)
    {
        SPG_PolygonBlend(_screen, Graphics::points.size(), (SPG_Point*) &Graphics::points[0], _strokeColor.get(_screen), _strokeColor.A);
    }
}

void Graphics::arc(const int x, const int y, const float r, const float startAngle, const float endAngle)
{
	if(_screen == NULL)
        throw WindowException();
		
	points.push_back(Point(x, y));
	applyTransform();
	Transform& t = transforms.back();
		
	if(_bFill)
	{
		SPG_ArcFilledBlend(_screen, points[0].x, points[0].y, r*t.getScaleAvg(), startAngle, endAngle, _fillColor.get(_screen), _fillColor.A);
	}
	
	if(_bStroke)
	{
		SPG_ArcBlend(_screen, points[0].x, points[0].y, r*t.getScaleAvg(), startAngle, endAngle, _strokeColor.get(_screen), _strokeColor.A);
	}
	
	points.clear();
}

void Graphics::bezier(const int x, const int y, const int cx1, const int cx2, const int cy1, const int cy2, const int endX, const int endY)
{
	if(_screen == NULL)
        throw WindowException();
		
	if(_bStroke)
	{
		SPG_BezierBlend(_screen, x, y, cx1, cx2, cy1, cy2, endX, endY, _bezierDetail, _strokeColor.get(_screen), _strokeColor.A);
		SDL_UnlockSurface(_screen);
	}
}

void Graphics::character(const int x, const int y, const char c)
{
    if(_screen == NULL)
        throw WindowException();

    if(_bStroke)
    {
        characterRGBA(_screen, x, y, c,
        	_strokeColor.R, _strokeColor.G, _strokeColor.B, _strokeColor.A);
    }
}

void Graphics::string(const int x, const int y, const std::string& line)
{
    if(_screen == NULL)
        throw WindowException();

    if(_bStroke)
    {
        stringRGBA(_screen, x, y, line.c_str(),
        	_strokeColor.R, _strokeColor.G, _strokeColor.B, _strokeColor.A);
    }
}

void Graphics::surface(const int x, const int y, const SDL_Surface* surface)
{
	if(_screen == NULL)
        throw WindowException();
        
	assert(surface);	// surface should not be NULL

	SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = surface->w;
    dest.h = surface->h;
	
	SDL_BlitSurface((SDL_Surface*) surface, NULL, _screen, &dest);
	//SPG_Blit((SDL_Surface*) surface, NULL, _screen, &dest);	
}

void Graphics::quadtex(const SDL_Surface* surface, float sx, float sy, float sw, float sh,
												   float dx, float dy, float dw, float dh)
{
	for(int i = 0; i < 4; ++i)
		points.push_back(Point());
	
	if(_imageMode == CENTER)
    {
        points[0].set(dx-dw/2, dy-dh/2);		// UL
        points[1].set(points[0].x, dy+dh/2);	// DL
		points[2].set(dx+dw/2, dy+dy/2);		// DR
		points[3].set(points[2].x, points[0].y);// UR
    }
    else
    {
        points[0].set(dx, dy);		// UL
        points[1].set(dx, dy+dh);	// DL
		points[2].set(dx+dw, dy+dh);// DR
		points[3].set(dx+dw, dy);	// UR
    }
	
	// setup tex coords
	points[4].set(sx, sy);			// UL
	points[5].set(sx, sy+sh);		// DL
	points[6].set(sx+sw, sy+sh);	// DR
	points[7].set(sx+sw, sy);		// UR
	
	applyTransform();

	SPG_QuadTexPoints(_screen, (SPG_Point*) &Graphics::points[0],
					  (SDL_Surface*) surface,
					  (SPG_Point*) &Graphics::points[4]);
					  
	points.clear();
}

// ***** draw transforms *****
void Graphics::push()
{
	if(transforms.size() >= VISUAL_MAX_TRANSFORMS)
	{
		LOG_WARN << "Too many pushes" << std::endl;
		return;
	}
		
	Transform t;
	transforms.push_back(t);
}

void Graphics::pop()
{
	if(transforms.size() == 1)
	{
		transforms[0].clear();
		return;
	}
	
	transforms.erase(transforms.end());
}

void Graphics::popAll()
{
	transforms.clear();
	push();
}

void Graphics::scale(float x, float y)
{
	transforms.back().scale(x, y);
}

void Graphics::rotate(float angle)
{
	transforms.back().rotate(angle);
}

void Graphics::skew(float x, float y)
{
	transforms.back().skew(x, y);
}

void Graphics::translate(float x, float y)
{
	transforms.back().translate(x, y);
}

/* ***** global util ***** */

std::string Graphics::getLastError()
{
    return SDL_GetError();
}

unsigned int Graphics::getMillis()
{
    return SDL_GetTicks();
}

/* ***** PRIVATE ***** */

void Graphics::applyTransform()
{
	for(unsigned int i = 0; i < transforms.size(); ++i)
	{
		Transform& t = transforms[i];
		if(t.bScale)
			SPG_ScalePoints(points.size(), (SPG_Point*) &points[0], t.scaleX, t.scaleY);
		if(t.bRotate)
			SPG_RotatePoints(points.size(), (SPG_Point*) &points[0], t.rotateAngle);
		if(t.bSkew)
			SPG_SkewPoints(points.size(), (SPG_Point*) &points[0], t.skewX, t.skewY);
		if(t.bTranslate)
			SPG_TranslatePoints(points.size(), (SPG_Point*) &points[0], t.translateX, t.translateY);
	}
}

} // namespace
