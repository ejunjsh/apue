ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

ifeq "$(PLATFORM)" "linux"
	ZAP = zap
else
	ZAP =
endif

.PHONY: exercises

PROGS =	access cdpwd changemod devrdev filetype mycd umask unlink $(ZAP)
MOREPROGS = ftw8

all:	$(PROGS) $(MOREPROGS) exercises

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $(ROOT)/bin/$@ $(LDFLAGS) $(LDLIBS)

ftw8:	ftw8.c $(LIBAPUE)
	$(CC) $(CFLAGS) $(NAMEMAX) ftw8.c -o $(ROOT)/bin/ftw8 $(LDFLAGS) $(LDLIBS)

exercises:
	(cd $@ && $(MAKE))

clean:
	rm -f $(PROGS) $(MOREPROGS) $(TEMPFILES) *.o $(ZAP)

	(cd exercises && $(MAKE) clean)

include $(ROOT)/Make.libapue.inc
