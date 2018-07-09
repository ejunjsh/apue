ROOT=..
EXTRALIBS=-pthread
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

BAR =
ifeq "$(PLATFORM)" "macos"
  TLOCK =
  EXTRALIBS=-pthread
else
  TLOCK = timedlock
endif
ifeq "$(PLATFORM)" "linux"
  BAR = barrier
  EXTRALIBS=-pthread -lrt -lbsd
endif
ifeq "$(PLATFORM)" "freebsd"
  BAR = barrier
  EXTRALIBS=-pthread
endif
ifeq "$(PLATFORM)" "solaris"
  BAR = barrier
  EXTRALIBS=-lpthread -lrt
endif

PROGS = badexit2 cleanup exitstatus threadid

.PHONY: exercises

all:	$(PROGS) condvar.o maketimeout.o mutex1.o mutex2.o mutex3.o rwlock.o $(TLOCK) $(BAR) exercises

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $(ROOT)/bin/$@ $(LDFLAGS) $(LDLIBS)

exercises:
	(cd $@ && $(MAKE))

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o $(TLOCK) $(BAR)
	(cd exercises && $(MAKE) clean)

include $(ROOT)/Make.libapue.inc
