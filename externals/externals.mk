# external libs variables

# directories to build (rel to top)
EXTERNALS_DIRS = externals/oscpack \
                 externals/tinyxml

# includes
EXTERNALS_CFLAGS = \
         -I$(top_srcdir)/externals/oscpack \
         -I$(top_srcdir)/externals/tclap \
         -I$(top_srcdir)/externals/tinyxml/src \
         -I$(top_srcdir)/externals

# libs to link
EXTERNALS_LIBS = \
     -L$(top_srcdir)/externals/oscpack -loscpack \
     -L$(top_srcdir)/externals/tinyxml/src -ltinyxml
