# visualframework tests

# load externals variables
include $(top_srcdir)/externals/externals.mk

# programs to build
noinst_PROGRAMS = vftest

# bin sources, headers here because we dont want to install them
vftest_SOURCES = ClassTests.h ClassTests.cpp \
                  TestApp.h TestApp.cpp testMain.cpp
                  
# local libraries needed to build (builddir)
vftest_LDADD = -L$(top_builddir)/src/visualframework -lvisualframework \
				 $(EXTERNALS_LIBS)

# include paths
vftest_CPPFLAGS = $(CXXFLAGS) \
				   $(SDL_CFLAGS) $(SDL_gfx_CFLAGS) $(SDL_NET_CFLAGS) \
				   $(EXTERNALS_CFLAGS) -I$(top_srcdir)/src/visualframework

# libs to link
vftest_LDFLAGS = $(SDL_LIBS) $(SDL_gfx_LIBS) $(SDL_NET_LIBS)

