ROOT=../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)


all:	sigusr1 sig2str filecounter printmask readbigfile writebigfile

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $(ROOT)/bin/$@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f  $(TEMPFILES) *.o 

include $(ROOT)/Make.libapue.inc
