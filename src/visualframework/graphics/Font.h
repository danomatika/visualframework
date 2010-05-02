/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009
==============================================================================*/
#ifndef VISUAL_FONT_H
#define VISUAL_FONT_H

#include "Common.h"

#include <SDL/SDL_ttf.h>

#include <string>

namespace visual {

class Font
{
	public:
	
    	Font();
        Font(std::string filename, unsigned int size);
    	virtual ~Font();
        
        bool load(std::string filename, unsigned int size);
        
        void clear();
        
        bool isLoaded();
        
        /// draw characters
        void draw(const char c, const int x, const int y);
        
        /// draw strings
        void draw(const std::string& text, const int x, const int y);
        
        //const int width();
        //const int height();
        
        /// get the raw surface structure of the Font (contains pixels)
        //SDL_Surface* getSurface() {return _Font;}
        
        inline std::string getFilename() {return _filename;}
        
        static void initTTF();
        static void cleanupTTF();

    protected:
    	
        TTF_Font*	_font;
    	std::string	_filename;
};

} // namespace

#endif // VISUAL_FONT_H
