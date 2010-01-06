
# load externals variables
include externals.mk

# dirs to delve into
SUBDIRS = $(EXTERNALS_DIRS)

# populate include and lib dirs
all-local:
	@echo "  ==== populating include and lib dirs ===="
	mkdir -p include
	mkdir -p lib
	
	ln -fs ../oscpack/osc include
	ln -fs ../oscpack/ip include
	cp oscpack/lib* lib
	
	ln -fs ../tinyxml/src ./include/tinyxml
	cp tinyxml/src/lib* lib
	
	ln -fs ../tclap include/tclap
	ln -fs ../vmmlib include
    
# clean the dirs
clean-local:
	@echo "  ==== cleaning include and lib dirs ===="
	rm -fR include
	rm -fR lib
