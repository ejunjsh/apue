ROOT=../..
PLATFORM=$(shell $(ROOT)/systype.sh)
EXTRALIBS=-pthread
include $(ROOT)/Make.defines.$(PLATFORM)


all:	goodexit2  worker_queue

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $(ROOT)/bin/$@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f  $(TEMPFILES) *.o 

include $(ROOT)/Make.libapue.inc
