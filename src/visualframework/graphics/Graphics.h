/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009
==============================================================================*/
#ifndef VISUAL_GRAPHICS_H
#define VISUAL_GRAPHICS_H

#include <string>
#include <vector>

#include <SDL/SDL.h>

#include "Color.h"

namespace visual {

class Point
{
    public:

        Point(int x, int y)
            {this->x = x; this->y = y;}

        int x;
        int y;
};

class Graphics
{
    public:

        enum Mode {
            WINDOW = 0,
            FULLSCREEN = SDL_FULLSCREEN
        };

        enum Type {
            UNKNOWN     = 0,
            SOFTWARE    = SDL_SWSURFACE,
            HARDWARE    = SDL_HWSURFACE
        };

        /// init sdl graphics
        static bool init(unsigned int w, unsigned int h, unsigned int depth, Type type=HARDWARE);

        /// set screen mode before creating window
        static void inline setWindow()     {_mode = WINDOW;}
        static void inline setFullscreen() {_mode = FULLSCREEN;}

        /// set the window's title text
        static void setWindowTitle(std::string title);

        /// set the window's icon
        static bool setWindowIcon(std::string bitmap);

        /// create the actual sdl draw surface
        static bool createWindow(std::string title="");

        /// toggles between fullscreen and window,
        /// automatically destroys and recreates draw surface
        static bool toggleFullscreen();

        /// get available fullscreen video resolutions (descending order)
        /// note: do not free any of the SDL_Rect pointers
        static std::vector<SDL_Rect*> getResolutions();

        /// change the window/screen resolution
        /// automatically destroys and recreates draw surface
        static bool changeResolution(unsigned int w, unsigned int h);

        /// get the current vode mode as a string
        static std::string getModeString();

        // global gets
        static const Type getType()     {return _type;}
        static const Mode getMode()     {return _mode;}
        static SDL_Surface* getScreen() {return _screen;}
        static const unsigned int getWidth()     {return _iWidth;}
        static const unsigned int getHeight()    {return _iHeight;}
        static const unsigned int getDepth()     {return _iDepth;}

        // global color
        static void stroke(unsigned int color);
        static void stroke(Color& color);
        static void fill(unsigned int color);
        static void fill(Color& color);

        static void noStroke();
        static void noFill();

        // global primitive draw options
        enum RectMode
        {
            CENTER,
            CORNER
        };
        // affects rectangles
        static void rectMode(RectMode mode) {_rectMode = mode;}

        // global primitives
        static void point(int x, int y);
        static void line(int x1, int y1, int x2, int y2);
        static void rectangle(int x, int y, int w, int h, RectMode mode=CENTER);
        static void circle(int x, int y, int r);
        static void ellipse(int x, int y, int rx, int ry);
        static void triangle(int x1, int y1, int x2, int y2, int x3, int y3);
        static void polygon(std::vector<Point> points);
        static void character(int x, int y, char c);
        static void string(int x, int y, std::string line);

        // global utils
        static std::string getLastError();
        static unsigned int getMillis();

    private:

        Graphics() {}                       // cannot create
        Graphics(const Graphics& from) {}   // not copyable
        virtual ~Graphics() {}              // cannot destroy
        void operator =(Color& from) {}     // not copyable

        static SDL_Surface* _screen;   /// SDL draw surface

        static unsigned int _iWidth;    /// window width
        static unsigned int _iHeight;   /// window height
        static unsigned int _iDepth;    /// bit depth

        static uint32_t _ui32VideoFlags;/// sdl video mode flags
        static Mode _mode;              /// context mode, WINDOW or FULLSCREEN
        static Type _type;              /// context type
        static std::string _sTitle;     /// window title

        // global color settings
        static Color _strokeColor;
        static Color _fillColor;
        static bool _bStroke;
        static bool _bFill;

        static RectMode _rectMode;

        static std::string _error;  /// error string
};

} // namespace

#endif // VISUAL_GRAPHICS_H
