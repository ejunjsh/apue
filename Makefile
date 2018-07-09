DIRS = `ls | grep -`


all: bin
	for i in $(DIRS); do \
		(cd $$i && echo "making $$i" && $(MAKE) ) || exit 1; \
	done

clean:
	for i in $(DIRS); do \
		(cd $$i && echo "cleaning $$i" && $(MAKE) clean) || exit 1; \
	done
	rm -rf bin
	(cd lib && echo "cleaning lib" && $(MAKE) clean)

bin:
	mkdir bin
