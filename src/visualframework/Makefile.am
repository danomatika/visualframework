# visualframework

# load externals variables
include $(top_srcdir)/externals/externals.mk

# the library to build, dont install just link to execs
noinst_LIBRARIES = libvisualframework.a

# libs sources, headers here because we dont want to install them
libvisualframework_a_SOURCES = \
        visualframework.h \
        Application.h \
        Application.cpp \
            graphics/Color.h \
            graphics/Graphics.h \
            graphics/Graphics.cpp \
        Common.h \
        Log.h \
            net/Net.h \
            net/Net.cpp \
            net/OscListener.h \
            net/OscListener.cpp \
            net/OscObject.h \
            net/OscObject.cpp \
            net/OscSender.h \
            net/OscSender.cpp \
            net/UdpListener.h \
            net/UdpListener.cpp \
            net/UdpSender.h \
            net/UdpSender.cpp \
        Thread.h \
        Thread.cpp

# include paths
AM_CPPFLAGS = \
        $(CXXFLAGS) $(SDL_CFLAGS) $(SDL_GFX_CFLAGS) $(SDL_NET_CFLAGS) \
        $(EXTERNALS_CFLAGS)


# libs to link
AM_LDFLAGS = \
    $(SDL_LIBS) $(SDL_GFX_LIBS)  $(SDL_NET_LIBS) $(EXTERNALS_LIBS)
