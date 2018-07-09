ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS =	add2 add2stdio devzero myuclc pipe1 pipe2 pipe4 popen1 popen2 tshm pipe4stdio pipe4stdiolinebuf add2stdiolinebuf

.PHONY: exercises

all:	$(PROGS) popen.o slock.o tellwait.o exercises

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $(ROOT)/bin/$@ $(LDFLAGS) $(LDLIBS)

slock.o:	slock.c slock.h

exercises:
	(cd $@ && $(MAKE))

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

	(cd exercises && $(MAKE) clean)

include $(ROOT)/Make.libapue.inc
