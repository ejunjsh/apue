#include "apue.h"
#include <stdio.h>
#include <stdlib.h>


void greeter() {
    printf("hello\n");
}

void greeter1() {
    printf("world\n");
}

typedef void (*Exitfunc)(void);

int my_atexit(Exitfunc func) {
    return atexit(func);
}

int main() {
    if (my_atexit(greeter1) != 0) {
        err_sys("atexit");
    };

    if (my_atexit(greeter) != 0) {
        err_sys("atexit");
    };
}