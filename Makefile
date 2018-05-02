DIRS = chapter01 \
chapter02 chapter02/exercises \
chapter03 chapter03/exercises \
chapter04 chapter04/exercises \
chapter05 chapter05/exercises \
chapter06 chapter06/exercises \
chapter07 chapter07/exercises \
chapter08 chapter08/exercises \
chapter09 chapter09/exercises \
chapter10 chapter10/exercises \
chapter11 chapter11/exercises


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
