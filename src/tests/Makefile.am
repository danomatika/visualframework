# visualframework tests

# programs to build
noinst_PROGRAMS = vftests

# lbin sources, headers here because we dont want to install them
vftests_SOURCES = ClassTests.h ClassTests.cpp \
                  TestApp.h TestApp.cpp testMain.cpp

# load externals variables
include $(top_srcdir)/externals/externals.mk

# include paths
vftests_CPPFLAGS = $(CXXFLAGS) $(SDL_CFLAGS) $(SDL_GFX_CFLAGS)  $(SDL_NET_CFLAGS) \
         -I../visualframework $(EXTERNALS_CFLAGS)

# libs to link
vftests_LDFLAGS = $(SDL_LIBS) $(SDL_GFX_LIBS)  $(SDL_NET_LIBS) \
        -L../visualframework -lvisualframework $(EXTERNALS_LIBS)
