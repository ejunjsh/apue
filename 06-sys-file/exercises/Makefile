ROOT=../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)


ifeq "$(PLATFORM)" "linux"
  shadow = getpwsvr4
endif

ifeq "$(PLATFORM)" "solaris"
  shadow = getpwsvr4
endif

ifeq "$(PLATFORM)" "freebsd"
  shadow = getpw44bsd
endif

ifeq "$(PLATFORM)" "macos"
  shadow = getpw44bsd
endif

all:	mydate myuname $(shadow)

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $(ROOT)/bin/$@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f  $(TEMPFILES) *.o 

include $(ROOT)/Make.libapue.inc
