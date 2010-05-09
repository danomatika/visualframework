/*==============================================================================

	Color.h

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
#ifndef VISUAL_COLOR_H
#define VISUAL_COLOR_H

#include <iostream>
#include <cassert>

namespace visual {

class Color
{
    public:

        union
        {
            struct
            {
                uint8_t	R, G, B, A;  // individual access
            };
            uint32_t rgba;     // single variable, 0xRRGGBBAA
            SDL_Color color;
        };

        Color() : R(255), G(255), B(255), A(255) {}

        Color(const uint8_t r, const uint8_t g, const uint8_t b) :
            R(r), G(g), B(b), A(255) {}

        Color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) :
            R(r), G(g), B(b), A(a) {}

        /// html style hex aka 0xFF00FF
        Color(const uint32_t color) : A(255)
        {
            set(color);
        }

        virtual ~Color() {}

        /// copy constructor
		Color(const Color& from)
		{
            R = from.R;
            G = from.G;
            B = from.B;
            A = from.A;
		}

        /// copy operator
        void operator =(const Color& from)
        {
            R = from.R;
            G = from.G;
            B = from.B;
            A = from.A;
        }

        /// attribute sets
        void set(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)
        {
            R = r;
            G = g;
            B = b;
            A = a;
        }
        void set(const uint8_t r, const uint8_t g, const uint8_t b)
        {
            R = r;
            G = g;
            B = b;
        }

        void set(const uint32_t color)
        {
            R = color >> 16;
            G = color >> 8;
            B = color;
        }
        
        /// get this color mapped to a surface's pxiel format
        uint32_t get(const SDL_Surface* surface)
        {
        	// surface should never be NULL
        	assert(surface);
            
            return SDL_MapRGBA(surface->format, R, G, B, A);
        }
        
        /// get this color as an SDL_color
        SDL_Color get()
        {
        	SDL_Color c = {R, G, B};
        	return c;
        }

		/// print this color's value via ostream
        friend std::ostream& operator<<(std::ostream& os, const Color& from)
        {
            os << "R: " << (int) from.R << " G: " << (int) from.G << " B: " << (int) from.B
               << " A: " << (int) from.A;
            return os;
        }
};

} // namespace

#endif // VISUAL_COLOR_H
