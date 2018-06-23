ROOT=../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

MOREPROGS=devzero4
ifeq "$(PLATFORM)" "linux"
  MOREPROGS=
endif

PROGS =	pipe21 pipe22 15.3 pipe41 selectpipein selectpipeout pollpipein pollpipeout fifo1 mqtest devzero1 devzero2 devzero3 $(MOREPROGS)

all:	$(PROGS) 

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $(ROOT)/bin/$@ $(LDFLAGS) $(LDLIBS)


clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

include $(ROOT)/Make.libapue.inc
