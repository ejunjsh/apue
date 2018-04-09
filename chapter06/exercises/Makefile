ROOT=../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

ifeq "$(PLATFORM)" "freebsd"
  FMEMOPEN = fmemopen.o
else
	ifeq "$(PLATFORM)" "macos"
		FMEMOPEN = fmemopen.o
	else
		FMEMOPEN =
	endif
endif

all:	$(FMEMOPEN) getcharbug.o mysetbuf.o



clean:
	rm -f  $(TEMPFILES) *.o 

include $(ROOT)/Make.libapue.inc
