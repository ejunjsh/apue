#include "apue.h"

int sig2str(int signo, char *str);

int main(int argc, char *argv[]) {
    if (argc != 2)
		err_quit("usage: sig2str signo");
    char buf[32];
    sig2str(atoi(argv[1]), buf);
    printf("sig %s: %s\n",argv[1] ,buf);
    return 0;
}


int sig2str(int signo, char *str) {
    if (signo < 0 || signo > NSIG) {
        return -1;
    }
    
    /* It's up to the caller to make sure there is
     enough room in str for the return of strsignal
     (plus a null byte \0).*/
    strcpy(str, strsignal(signo));
    
    return 0;
}