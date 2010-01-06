# external libs variables

# directories to build (rel to top)
EXTERNALS_DIRS = oscpack tinyxml

# includes
EXTERNALS_CFLAGS = \
        -I$(top_srcdir)/externals/include \
        -I$(top_srcdir)/externals

# libs to link
EXTERNALS_LIBS = \
      -L$(top_srcdir)/externals/lib -loscpack -ltinyxml
