ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS =	orphan3

.PHONY: exercises

all:	$(PROGS) exercises

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $(ROOT)/bin/$@ $(LDFLAGS) $(LDLIBS)

exercises:
	(cd $@ && $(MAKE))

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

	(cd exercises && $(MAKE) clean)

include $(ROOT)/Make.libapue.inc
