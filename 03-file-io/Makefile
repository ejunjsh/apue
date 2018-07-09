ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS =	fileflags hole mycat seek

.PHONY: exercises

all:	$(PROGS) setfl.o exercises

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $(ROOT)/bin/$@ $(LDFLAGS) $(LDLIBS)

exercises:
	(cd $@ && $(MAKE))

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o file.hole

	(cd exercises && $(MAKE) clean)

include $(ROOT)/Make.libapue.inc
