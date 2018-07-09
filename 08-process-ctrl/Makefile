ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

ACCT=
ACCTFLAGS=
ifeq "$(PLATFORM)" "linux"
  ACCT=pracct
  ACCTFLAGS = -DHAS_AXSIG -DHAS_ACORE
endif
ifeq "$(PLATFORM)" "macos"
  ACCT=pracct
  ACCTFLAGS = -DHAS_AXSIG -DHAS_ACORE
endif
ifeq "$(PLATFORM)" "solaris"
  ACCT=pracct
  ACCTFLAGS = -DHAS_AC_STAT
endif

PROGS =	echoall exec1 exec2 fork1 fork2 nice pruids tellwait1 tellwait2 test1 times1 vfork1 wait1
MOREPROGS = systest1 systest3

.PHONY: exercises

all:	$(PROGS) $(MOREPROGS) system.o $(ACCT) exercises

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $(ROOT)/bin/$@ $(LDFLAGS) $(LDLIBS)

systest1:	system.o systest1.o $(LIBAPUE)
		$(CC) $(CFLAGS) -o $(ROOT)/bin/systest1 systest1.o system.o $(LDFLAGS) $(LDLIBS)

systest3:	system.o systest3.o $(LIBAPUE)
		$(CC) $(CFLAGS) -o $(ROOT)/bin/systest3 systest3.o system.o $(LDFLAGS) $(LDLIBS)

pracct:		pracct.c $(LIBAPUE)
		$(CC) $(CFLAGS) $(ACCTFLAGS) -o $(ROOT)/bin/pracct pracct.c $(LDFLAGS) $(LDLIBS)

exercises:
	(cd $@ && $(MAKE))

clean:  
	rm -f $(PROGS) $(MOREPROGS) $(TEMPFILES) *.o $(ACCT)
	(cd exercises && $(MAKE) clean)

include $(ROOT)/Make.libapue.inc
