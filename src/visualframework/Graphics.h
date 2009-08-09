/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009
==============================================================================*/
#ifndef VISUAL_GRAPHICS_H
#define VISUAL_GRAPHICS_H

#include <string>

#include <SDL/SDL.h>

#include "Color.h"

namespace visual {

class Graphics
{
    public:

        enum Mode {
            WINDOW = 0,
            FULLSCREEN = SDL_FULLSCREEN
        };

        enum Type {
            UNKOWN      = 0,
            SOFTWARE    = SDL_SWSURFACE,
            HARDWARE    = SDL_HWSURFACE
        };

        Graphics(int w, int h, int depth, Type type=HARDWARE);

        virtual ~Graphics();

        bool init();

        bool createWindow(std::string title);

        void inline setWindow()     {_mode = WINDOW;};
        void inline setFullscreen() {_mode = FULLSCREEN;};

        // global gets
        static const Type getType()     {return _type;}
        static SDL_Surface* getScreen() {return _screen;}
        static const int getWidth()     {return _iWidth;}
        static const int getHeight()    {return _iHeight;}
        static const int getDepth()     {return _iDepth;}

        // global color
        static void stroke(unsigned int color);
        static void fill(unsigned int color);

        static void noStroke();
        static void noFill();

        // global primitives
        static void point(int x, int y);
        static void line(int x1, int y1, int x2, int y2);
        static void rectangle(int x, int y, int w, int h);
        static void circle(int x, int y, int r);
        static void ellipse(int x, int y, int rx, int ry);
        static void triangle(int x1, int y1, int x2, int y2, int x3, int y3);
        static void character(int x, int y, char c);
        static void string(int x, int y, std::string line);

    protected:

    private:

        bool initSDL();

        bool initOpenGL();

        static SDL_Surface* _screen;   /// SDL draw surface

        static int _iWidth;         /// window width
        static int _iHeight;        /// window height
        static int _iDepth;         /// bit depth
        Uint32 _ui32VideoFlags;     /// sdl video mode flags
        Mode _mode;                 /// context mode, WINDOW or FULLSCREEN
        static Type _type;          /// context type
        std::string _sTitle;        /// window title

        // global color settings
        static Color _strokeColor;
        static Color _fillColor;
        static bool _bStroke;
        static bool _bFill;
};

} // namespace

#endif // VISUAL_GRAPHICS_H
