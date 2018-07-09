ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

ifeq "$(PLATFORM)" "solaris"
  EXTRALIBS = -lsocket -lnsl
endif

PROGS = ruptime ruptimed ruptimed-fd ruptimed-dg
MOREPROGS = findsvc ruptime-dg

.PHONY: exercises

all:	$(PROGS) $(MOREPROGS) clconn.o clconn2.o initsrv1.o initsrv2.o 

%:	%.c $(LIBAPUE)
		$(CC) $(CFLAGS) $@.c -o $(ROOT)/bin/$@ $(LDFLAGS) $(LDLIBS)

ruptime:	ruptime.o clconn2.o $(LIBAPUE)
		$(CC) $(CFLAGS) -o $(ROOT)/bin/ruptime ruptime.o clconn2.o $(LDFLAGS) $(LDLIBS)

ruptimed:	ruptimed.o initsrv2.o $(LIBAPUE)
		$(CC) $(CFLAGS) -o $(ROOT)/bin/ruptimed ruptimed.o initsrv2.o $(LDFLAGS) $(LDLIBS)

ruptimed-fd:	ruptimed-fd.o initsrv2.o $(LIBAPUE)
		$(CC) $(CFLAGS) -o $(ROOT)/bin/ruptimed-fd ruptimed-fd.o initsrv2.o $(LDFLAGS) $(LDLIBS)

ruptimed-dg:	ruptimed-dg.o initsrv2.o $(LIBAPUE)
		$(CC) $(CFLAGS) -o $(ROOT)/bin/ruptimed-dg ruptimed-dg.o initsrv2.o $(LDFLAGS) $(LDLIBS)

exercises:
	(cd $@ && $(MAKE))

clean:
	rm -f $(PROGS) $(MOREPROGS) $(TEMPFILES) *.o

	(cd exercises && $(MAKE) clean)

include $(ROOT)/Make.libapue.inc
