ROOT=../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)


PROGS = pty1 ptyf_master ptyf_slave

all:	$(PROGS) 

pty1:	../main.o loop1.o ../driver.o $(LIBAPUE)
	$(CC) $(CFLAGS) -o $(ROOT)/bin/pty1 ../main.o loop1.o ../driver.o $(LDFLAGS) $(LDLIBS)

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $(ROOT)/bin/$@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(PROGS) $(MOREPROGS) $(TEMPFILES) *.o

include $(ROOT)/Make.libapue.inc
