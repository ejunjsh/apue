#include "apue.h"

#define MAX_NAME_LEN 128
#define BUFSZ 128


int ptym_fd;


void slrd() {
    int n;
    char buf[BUFSZ] = { 0 };
    sleep(1);
    if((n = read(ptym_fd, buf, BUFSZ))<0)
    {
        err_sys("read error");
    }
    buf[n] = '\0';
    printf("got from child: %s\n", buf);
}


int main() {
    pid_t pid;
    char slave_name[MAX_NAME_LEN];
    struct winsize size = {
        3, 4
    };

    if((pid = pty_fork(&ptym_fd, slave_name, MAX_NAME_LEN, NULL, NULL))<0){
        err_sys("pty_fork error");
    }

    if (pid == 0) {  /* Child.*/
        execl("bin/ptyf_slave", "slave", (char*) 0);
        return EXIT_SUCCESS;

    } else {  /* Parent. */
        printf("hello from parent\n");

        slrd();

        /* send sigterm*/
        /* Doesn't work on Linux, failing with EINVAL*/
        if (ioctl(ptym_fd, TIOCSIG, SIGTERM) < 0) {
            err_sys("ioctl error");
        }
        slrd();
        
        /* change window size*/
        if(ioctl(ptym_fd, TIOCSWINSZ, &size)<0){
            
        }
        slrd();

        return EXIT_SUCCESS;
    }
}