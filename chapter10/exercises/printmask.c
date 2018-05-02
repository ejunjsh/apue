#include "apue.h"
#include <signal.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    sigset_t sigset;

    if (sigprocmask(0, NULL, &sigset) < 0) {
        err_sys("sigprocmask error");
    }

    int i;
    for (i = 0; i < NSIG; i++) {
        if (sigismember(&sigset, i))
            printf("%s ", sys_siglist[i]);
    }
    printf("\n");
    return 0;
}