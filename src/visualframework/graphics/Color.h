/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009
==============================================================================*/
#ifndef VISUAL_COLOR_H
#define VISUAL_COLOR_H

#include <iostream>

namespace visual {

class Color
{
    public:
        // struct and array for glColor calls
        union
        {
            struct
            {
                uint8_t  A, B, G, R;  // individual access
            };
            //uint8_t rgba[4];    // 4 value vector
            //uint8_t rgb[3];     // 3 value vector
            uint32_t rgba;     // single variable, 0xRRGGBBAA
        };

        Color() : A(255), B(255), G(255), R(255)  {}

        Color(uint8_t r, uint8_t g, uint8_t b) :
            A(255), B(b), G(g), R(r) {}

        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) :
            A(a), B(b), G(g), R(r) {}

        // html style hex aka 0xFF00FF
        Color(unsigned int color) : A(255)
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
        void operator =(Color& from)
        {
            R = from.R;
            G = from.G;
            B = from.B;
            A = from.A;
        }

        /// attribute sets
        void set(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
        {
            R = r;
            G = g;
            B = b;
            A = a;
        }
        void set(uint8_t r, uint8_t g, uint8_t b)
        {
            R = r;
            G = g;
            B = b;
        }

        void set(unsigned int color)
        {
            R = color >> 16;
            G = color >> 8;
            B = color;
        }

        friend std::ostream& operator<<(std::ostream& os, Color& from)
        {
            os << "R: " << (int) from.R << " G: " << (int) from.G << " B: " << (int) from.B
               << " A: " << (int) from.A;
            return os;
        }
};

} // namespace

#endif // VISUAL_COLOR_H
