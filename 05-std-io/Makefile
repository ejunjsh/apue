ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

ifeq "$(PLATFORM)" "linux"
  MEMSTR = memstr
else
  MEMSTR =
endif

.PHONY: exercises

PROGS =	buf fgetsfputs getcputc mkstemp tempfiles

all:	$(PROGS) $(MEMSTR) exercises

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $(ROOT)/bin/$@ $(LDFLAGS) $(LDLIBS)

exercises:
	(cd $@ && $(MAKE))

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o $(MEMSTR)

	(cd exercises && $(MAKE) clean)

include $(ROOT)/Make.libapue.inc
