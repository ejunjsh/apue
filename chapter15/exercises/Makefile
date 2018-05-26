ROOT=../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS =	pipe21 pipe22 15.3 pipe41 selectpipein fifo1 mqtest

all:	$(PROGS) 

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $(ROOT)/bin/$@ $(LDFLAGS) $(LDLIBS)


clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

include $(ROOT)/Make.libapue.inc
