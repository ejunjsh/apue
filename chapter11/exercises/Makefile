ROOT=../..
PLATFORM=$(shell $(ROOT)/systype.sh)
EXTRALIBS=-pthread
include $(ROOT)/Make.defines.$(PLATFORM)


BAR =
ifeq "$(PLATFORM)" "linux"
  BAR = mybarrier
  EXTRALIBS=-pthread -lrt -lbsd
endif
ifeq "$(PLATFORM)" "freebsd"
  BAR = mybarrier
  EXTRALIBS=-pthread
endif
ifeq "$(PLATFORM)" "solaris"
  BAR = mybarrier
  EXTRALIBS=-lpthread -lrt
endif


all:	goodexit2  worker_queue $(BAR)

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $(ROOT)/bin/$@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f  $(TEMPFILES) *.o 

include $(ROOT)/Make.libapue.inc
