ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

ifeq "$(PLATFORM)" "solaris"
  EXTRALIBS=-lsocket -lnsl
endif

PROGS =	pty

.PHONY: exercises

all:	$(PROGS) exercises

pty:	main.o loop.o driver.o $(LIBAPUE)
	$(CC) $(CFLAGS) -o $(ROOT)/bin/pty main.o loop.o driver.o $(LDFLAGS) $(LDLIBS)

exercises:
	(cd $@ && $(MAKE))

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

	(cd exercises && $(MAKE) clean)

include $(ROOT)/Make.libapue.inc
