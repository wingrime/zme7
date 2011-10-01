include Makefile.inc
SHELL=bash

default: engine

engine : engine_lauch.cpp
	cd logging; $(MAKE) $(MFLAGS)
	cd core; $(MAKE) $(MFLAGS)
	$(SHELL) build.sh
	

clean : engine_lauch.cpp
	cd logging; $(MAKE) $(MFLAGS) clean
	cd core; $(MAKE) $(MFLAGS) clean
	$(RM) engine_lauch engine.o