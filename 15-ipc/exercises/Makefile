ROOT=../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

ifeq "$(PLATFORM)" "freebsd"
  EXTRALIBS = -pthread
endif
ifeq "$(PLATFORM)" "linux"
  EXTRALIBS = -pthread
endif
ifeq "$(PLATFORM)" "solaris"
  EXTRALIBS = -lpthread
endif

PROGS =	pipe21 pipe22 15.3 pipe41 selectpipein selectpipeout pollpipein pollpipeout fifo1 mqtest devzero1 devzero2 devzero3 devzero4

all:	$(PROGS) 

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $(ROOT)/bin/$@ $(LDFLAGS) $(LDLIBS)


clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

include $(ROOT)/Make.libapue.inc
