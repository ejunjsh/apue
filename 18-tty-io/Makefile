ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS =	csize settty t_getpass t_isatty t_raw t_ttyname winch

.PHONY: exercises

all:	$(PROGS) ctermid.o getpass.o isatty.o ttyname.o exercises

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $(ROOT)/bin/$@ $(LDFLAGS) $(LDLIBS)

exercises:
	(cd $@ && $(MAKE))

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

	(cd exercises && $(MAKE) clean)

include $(ROOT)/Make.libapue.inc
