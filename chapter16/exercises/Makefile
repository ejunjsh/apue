ROOT=../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS =	byteorder socketstat ruptimed-mp ruptime-mp

all:	$(PROGS) 

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $(ROOT)/bin/$@ $(LDFLAGS) $(LDLIBS)

ruptimed-mp: 
	$(CC) $(CFLAGS) -o $(ROOT)/bin/ruptimed-mp ruptimed-mp.c ../initsrv2.o $(LDFLAGS) $(LDLIBS)

ruptime-mp: 
	$(CC) $(CFLAGS) -o $(ROOT)/bin/ruptime-mp ruptime-mp.c ../clconn2.o $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

include $(ROOT)/Make.libapue.inc
