#include "apue.h"
#include <sys/select.h>

#define BFSZ 128


int main() {
    int pid, pipe_in, pipe_out;
    int pipe_fds[2];
    char msg[] = "hello!";
    char buf[BFSZ];

    if(pipe(pipe_fds)<0){
        err_sys("pipe error");
    }

    pipe_out = pipe_fds[0];
    pipe_in = pipe_fds[1];

    if((pid = fork())<0){
        err_sys("fork error");
    }

    if (pid == 0) {  /* Child.*/
        if(close(pipe_out)<0){
            err_sys("close error");
        }

        if(write(pipe_in, msg, sizeof msg)<0){
            err_sys("write error");
        }

        if(close(pipe_in)<0){
            err_sys("close error");
        }
        return EXIT_SUCCESS;

    } else {  /* Parent.*/
        fd_set readfds, writefds, exceptfds;

        if(close(pipe_in)<0){
            err_sys("close error");
        }

        fprintf(stderr, "Sleeping... ");
        sleep(5);
        fprintf(stderr, "Done.\n");

        FD_ZERO(&readfds);
        FD_SET(pipe_out, &readfds);
        FD_ZERO(&writefds);
        FD_SET(pipe_out, &writefds);
        FD_ZERO(&exceptfds);
        FD_SET(pipe_out, &exceptfds);

        if(select(pipe_out + 1, &readfds, &writefds, &exceptfds, NULL)<0){
            err_sys("select error");
        }
        if (FD_ISSET(pipe_out, &readfds))
            printf("Ready for reading\n");
        if (FD_ISSET(pipe_out, &writefds))
            printf("Ready for writing\n");
        if (FD_ISSET(pipe_out, &exceptfds))
            printf("Exception\n");

        if(read(pipe_out, buf, BFSZ)<0){
            err_sys("read error");
        }
        fprintf(stderr, "Got from child: %s\n", buf);
        return EXIT_SUCCESS;
    }
}