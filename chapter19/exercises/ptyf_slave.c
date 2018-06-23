#include "apue.h"


void sig_handler(int signum) {
    fprintf(stderr, "Slave: got %s signal\n", strsignal(signum));
    if (signum == SIGWINCH) {
        struct winsize size;
        if(ioctl(STDIN_FILENO, TIOCGWINSZ, (char *) &size)<0){
            err_sys("ioctl error");
        }
        printf("window size: %d rows, %d columns\n", size.ws_row, size.ws_col);
    }
}


int main() {
    printf("hello from child\n");

    struct sigaction act;
    act.sa_handler = sig_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    if(sigaction(SIGTERM, &act, NULL)<0){
        err_sys("sigaction error");
    }
    if(sigaction(SIGWINCH, &act, NULL)<0){
        err_sys("sigaction error");
    }

    while(1)
        pause();

    return EXIT_SUCCESS;
}