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

        Graphics(unsigned int w, unsigned int h, unsigned int depth, Type type=HARDWARE);

        virtual ~Graphics();

        /// init sdl
        bool init();

        /// set screen mode before creating window
        void inline setWindow()     {_mode = WINDOW;}
        void inline setFullscreen() {_mode = FULLSCREEN;}

        /// set the window's title text
        void setWindowTitle(std::string title);

        /// set the window's icon
        bool setWindowIcon(std::string bitmap);

        /// create the actual sdl draw surface
        bool createWindow(std::string title="");

        /// toggles between fullscreen and window,
        /// automatically destroys and recreates draw surface
        bool toggleFullscreen();

        /// get available fullscreen video resolutions (descending order)
        /// note: do not free any of the SDL_Rect pointers
        std::vector<SDL_Rect*> getResolutions();

        /// change the window/screen resolution
        /// automatically destroys and recreates draw surface
        bool changeResolution(unsigned int w, unsigned int h);

        /// get the current vode mode as a string
        std::string getModeString();

        // global gets
        static const Type getType()     {return _type;}
        static const Mode getMode()     {return _mode;}
        static SDL_Surface* getScreen() {return _screen;}
        static const unsigned int getWidth()     {return _iWidth;}
        static const unsigned int getHeight()    {return _iHeight;}
        static const unsigned int getDepth()     {return _iDepth;}

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

        // global utils
        static std::string getLastError();

    protected:

    private:

        static SDL_Surface* _screen;   /// SDL draw surface

        static unsigned int _iWidth;         /// window width
        static unsigned int _iHeight;        /// window height
        static unsigned int _iDepth;         /// bit depth
        uint32_t _ui32VideoFlags;   /// sdl video mode flags
        static Mode _mode;          /// context mode, WINDOW or FULLSCREEN
        static Type _type;          /// context type
        std::string _sTitle;        /// window title

        // global color settings
        static Color _strokeColor;
        static Color _fillColor;
        static bool _bStroke;
        static bool _bFill;

        static std::string _error;  /// error string
};

} // namespace

#endif // VISUAL_GRAPHICS_H
