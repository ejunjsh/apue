ROOT=../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)


PROGS = ttyraw

all:	$(PROGS) 

%:	%.c $(LIBAPUE)
		$(CC) $(CFLAGS) $@.c -o $(ROOT)/bin/$@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(PROGS) $(MOREPROGS) $(TEMPFILES) *.o

include $(ROOT)/Make.libapue.inc
