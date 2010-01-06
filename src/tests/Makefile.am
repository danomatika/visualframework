# visualframework tests

# programs to build
noinst_PROGRAMS = vftests

# lbin sources, headers here because we dont want to install them
vftests_SOURCES = ClassTests.h ClassTests.cpp \
                  TestApp.h TestApp.cpp testMain.cpp

# load externals variables
include $(top_srcdir)/externals/externals.mk

# include paths
vftests_CPPFLAGS = $(CXXFLAGS) \
        $(SDL_CFLAGS) -I../visualframework $(EXTERNALS_CFLAGS)

# libs to link
vftests_LDFLAGS = $(SDL_LIBS) $(SDL_GFX_LIBS)  $(SDL_NET_LIBS) \
        -L../visualframework -lvisualframework $(EXTERNALS_LIBS)

# move bin to bin folder after building
all-local:
	mkdir -p $(top_srcdir)/bin
	mv vftests $(top_srcdir)/bin/vftests

# clean bin
clean-local:
	rm -f $(top_srcdir)/bin/vftests
