# visualframework tests

# programs to build
noinst_PROGRAMS = vftest

# bin sources, headers here because we dont want to install them
vftest_SOURCES = ClassTests.h ClassTests.cpp \
				  TestApp.h TestApp.cpp testMain.cpp
				  
# local libraries needed to build (builddir)
vftest_LDADD = -L$(top_builddir)/src/visualframework -lvisualframework

# include paths
vftest_CPPFLAGS = $(CXXFLAGS) \
				   $(SDL_CFLAGS) $(SDL_gfx_CFLAGS) $(SDL_NET_CFLAGS) $(SDL_TTF_CFLAGS) \
				   $(SDL_image_CFLAGS) -I$(top_srcdir)/src -I$(top_srcdir)/src/visualframework

# libs to link
vftest_LDFLAGS = $(SDL_LIBS) $(SDL_gfx_LIBS) $(SDL_NET_LIBS) $(SDL_TTF_LIBS) $(SDL_image_LIBS)

