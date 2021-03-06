#########################################
##### Prelude #####

AC_INIT([visualframework], [0.1.1], [danomatika@gmail.com], [visualframework], [https://github.com/danomatika/visualframework])
AC_CONFIG_SRCDIR([src/visualframework/visualframework.h])
AC_CONFIG_AUX_DIR([config])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

#########################################
##### Build Options #####

DEBUG_CXXFLAGS="-g -Wall -Werror -Wno-uninitialized -O0"
RELEASE_CXXFLAGS="-g -O2"

#########################################
##### Check for programs/libs #####

# check progs
AC_PROG_CXX
AC_PROG_RANLIB
AC_PROG_CC # <- for Sprig c sources

# using c++ compiler and linker
AC_LANG_CPLUSPLUS

# allow non-POSIX libs
AM_PROG_AR

# check for headers
AC_HEADER_STDC
AC_CHECK_HEADERS(sstream) # needed for tclap

AC_CHECK_HEADER([SDL/SDL_net.h],[],
	AC_MSG_ERROR([SDL_net headers not found]))

AC_CHECK_HEADER([SDL/SDL_ttf.h],[],
	AC_MSG_ERROR([SDL_ttf headers not found]))

# check for libs
AC_CHECK_LIB(SDL_net, SDLNet_UDP_Open,
	AC_SUBST(SDL_NET_LIBS, -lSDL_net),
	AC_MSG_ERROR([SDL_net library not found]))
	
AC_CHECK_LIB(SDL_ttf, TTF_OpenFont,
	AC_SUBST(SDL_TTF_LIBS, -lSDL_ttf),
	AC_MSG_ERROR([SDL_ttf library not found]))

# check for headers & libs
PKG_CHECK_MODULES(SDL, sdl >= 1.2,[],
	AC_MSG_ERROR([SDL library >= 1.2 not found]))
	
PKG_CHECK_MODULES(SDL_gfx, SDL_gfx >= 2.0.0 ,[],
	AC_MSG_ERROR([SDL_gfx library not found]))

PKG_CHECK_MODULES(SDL_image, SDL_image >= 1.2.0 ,[],
	AC_MSG_ERROR([SDL_image library not found]))

#########################################
##### Options #####

# debug build switch
# from http://www.bioinf.uni-freiburg.de/~mmann/HowTo/automake.html#debug
AC_MSG_CHECKING([whether to enable the debug build])
AC_ARG_ENABLE([debug],
	[AS_HELP_STRING([--enable-debug],
		[enable debug build (def=no)])],
	[enable_debug="$enableval"],
	[enable_debug=no])
AC_MSG_RESULT([$enable_debug])

if test x"$enable_debug" = x"yes"; then
	AC_DEFINE([DEBUG],[],[Debug Mode])
	CXXFLAGS="$DEBUG_CXXFLAGS"
else
	AC_DEFINE([NDEBUG],[],[Release Mode])
	CXXFLAGS="$RELEASE_CXXFLAGS"
fi

#########################################
##### Externals #####

# externals with configure scripts
AC_CONFIG_SUBDIRS()

#########################################
##### Output files #####

AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_FILES([
	Makefile
	data/Makefile
	src/Makefile
	src/visualframework/Makefile
	src/visualframework/vmmlib/Makefile
	src/test/Makefile
])
AC_OUTPUT

#########################################
##### Print a summary for the user #####

AC_MSG_RESULT([
	visualframework $VERSION is now configured

	Source directory:     $srcdir
	Installation prefix:  $prefix
	C++ compiler:         $CXX $CXXFLAGS
	Debug build:          $enable_debug
])
