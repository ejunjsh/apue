ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

CLD =

ifeq "$(PLATFORM)" "linux"
  CLD = child
endif
ifeq "$(PLATFORM)" "solaris"
  CLD = child
endif

PROGS =	critical mask read1 read2 reenter sigtstp sigusr suspend1 suspend2
MOREPROGS = systest2 tsleep2

all:	$(PROGS) $(MOREPROGS) abort.o sleep1.o sleep2.o system.o $(CLD)

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $(ROOT)/bin/$@ $(LDFLAGS) $(LDLIBS)

tsleep2:	tsleep2.o sleep2.o $(LIBAPUE)
		$(CC) $(CFLAGS) -o $(ROOT)/bin/tsleep2 tsleep2.o sleep2.o $(LDFLAGS) $(LDLIBS)

systest2:	systest2.o system.o $(LIBAPUE)
		$(CC) $(CFLAGS) -o $(ROOT)/bin/systest2 systest2.o system.o $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(PROGS) $(MOREPROGS) $(TEMPFILES) *.o file.hole $(CLD)

include $(ROOT)/Make.libapue.inc
