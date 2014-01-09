visualframework
===============

a 2D graphics framework using SDL

Copyright (c) [Dan Wilcox](http://danomatika.com) 2009,2010

DESCRIPTION
-----------

visualframework is a C++ wrapper of various Simple Direct Media Layer (SDL) libraries into a slim, 2D graphics framework. It is meant to be used on low resource and embedded systems and should be as fast and minimal as possible, while being easy to use.

Provided functionality:

* 2D graphics primitives
* Image loading, drawing, and resizing
* TTF font rendering
* 2D vector (Point) 
* Thread
* Timer

This library was originally developed for the robotcowboy project, a wearable computer
music system using Pure Data in GNU/Linux. See <http://robotcowboy.com>

BUILD REQUIREMENTS
------------------

The following libraries are required:

* SDL
* SDL_gfx
* SDL_Image
* SDL_TTF

On Max OS X, they can be installed using macports: http://macports.org

* install the macport binary and setup the macports environment
  * go to the Terminal and install the libs:
      
	  sudo port install libsdl libsdl_gfx libsdl_image libsdl_ttf

BUILD AND INSTALLATION
----------------------

Build the library using: 

    ./configure
    make


Install the library (after building):

    sudo make install

This readme will also installed to your doc dir, something like $(prefix)/share/doc/rc-unitd.

USAGE
-----

Include visualframework.h and the visualframework folder (needed to find <vmmlib/vmmlib.h>).

Link to visualframework as the library should be compiled into "libvisualframework.a"

DEVELOPING
----------

A Premake4 script and IDE files can be found in the prj folder.  Premake4 can generate the IDE files from a given lua script.  Download Premake4 from <http://industriousone.com/premake>

You can enable a debug build using

    ./configure --enable-debug

I develop using an IDE, then update the autotools files when the sources are finished.  I run make dist-check to make sure the distributable package can be built successfully.

