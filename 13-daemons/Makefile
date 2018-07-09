ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

.PHONY: exercises

all:	init.o reread.o reread2.o single.o exercises

exercises:
	(cd $@ && $(MAKE))

clean:
	rm -f $(TEMPFILES) *.o

	(cd exercises && $(MAKE) clean)
