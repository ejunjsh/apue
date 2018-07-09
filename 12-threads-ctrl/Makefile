ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

TOUT =
ifeq "$(PLATFORM)" "freebsd"
  EXTRALIBS = -pthread
endif
ifeq "$(PLATFORM)" "linux"
  EXTRALIBS = -pthread
  TOUT = timeout.o
endif
ifeq "$(PLATFORM)" "solaris"
  EXTRALIBS = -lpthread
  TOUT = timeout.o
endif

PROGS =	atfork suspend

.PHONY: exercises

all:	$(PROGS) detach.o getenv1.o getenv2.o getenv3.o $(TOUT) exercises

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $(ROOT)/bin/$@ $(LDFLAGS) $(LDLIBS)

exercises:
	(cd $@ && $(MAKE))

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

	(cd exercises && $(MAKE) clean)

include $(ROOT)/Make.libapue.inc
