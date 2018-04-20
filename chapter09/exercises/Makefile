ROOT=../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)


all:	setsid

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $(ROOT)/bin/$@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f  $(TEMPFILES) *.o 

include $(ROOT)/Make.libapue.inc
