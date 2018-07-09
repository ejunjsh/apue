ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS =	conf options 

.PHONY: exercises

all:	$(PROGS) exercises

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $(ROOT)/bin/$@ $(LDFLAGS) $(LDLIBS)

conf:	conf.c

conf.c:	makeconf.awk sysconf.sym pathconf.sym
	$(AWK) -f makeconf.awk >conf.c

sysconf.sym:	sysconf-lim.sym
	grep -v "^#" sysconf-lim.sym >sysconf.sym

pathconf.sym:	pathconf-lim.sym
	grep -v "^#" pathconf-lim.sym >pathconf.sym

options:	options.c

options.c:	makeopt.awk sysopt.sym pathopt.sym
	$(AWK) -f makeopt.awk >options.c

sysopt.sym:	sysconf-opt.sym
	grep -v "^#" sysconf-opt.sym >sysopt.sym

pathopt.sym:	pathconf-opt.sym
	grep -v "^#" pathconf-opt.sym >pathopt.sym

exercises:
	(cd $@ && $(MAKE))

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o conf.c options.c \
		pathconf.sym pathopt.sym sysconf.sym sysopt.sym
	
	(cd exercises && $(MAKE) clean)

include $(ROOT)/Make.libapue.inc
