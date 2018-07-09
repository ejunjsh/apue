ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS =	strftime

.PHONY: exercises

all:	$(PROGS) getpwnam.o exercises

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $(ROOT)/bin/$@ $(LDFLAGS) $(LDLIBS)

exercises:
	(cd $@ && $(MAKE))

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

	(cd exercises && $(MAKE) clean)

include $(ROOT)/Make.libapue.inc
