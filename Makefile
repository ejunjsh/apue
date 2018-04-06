DIRS = chapter01 \
chapter02 chapter02/exercises \
chapter03 chapter03/exercises \
chapter04 chapter04/exercises \
chapter05



all: bin
	for i in $(DIRS); do \
		(cd $$i && echo "making $$i" && $(MAKE) ) || exit 1; \
	done

clean:
	for i in $(DIRS); do \
		(cd $$i && echo "cleaning $$i" && $(MAKE) clean) || exit 1; \
	done
	rm -rf bin

bin:
	mkdir bin
