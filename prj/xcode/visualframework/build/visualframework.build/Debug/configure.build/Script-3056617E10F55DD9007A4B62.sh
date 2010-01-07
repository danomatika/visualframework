#!/bin/sh
# export the dirs for MacPorts
export CPPFLAGS=-I/opt/local/include
export LDFLAGS=-L/opt/local/lib

# run the makefile
make -f Makefile-xcode $@

exit 0
