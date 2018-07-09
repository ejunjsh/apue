#include "apue.h"
#include <assert.h>
#include <sys/select.h>

#define BFSZ 128

static void
sig_pipe(int signo)
{
	printf("SIGPIPE caught\n");
	exit(1);
}

int main() {
    int pid, pipe_in, pipe_out;
    int pipe_fds[2];
    char msg[] = "hello!";

    if (signal(SIGPIPE, sig_pipe) == SIG_ERR)
		err_sys("signal error");

    if(pipe(pipe_fds)<0){
        err_sys("pipe error");
    }
    pipe_out = pipe_fds[0];
    pipe_in = pipe_fds[1];

    if((pid = fork())<0){
        err_sys("fork error");
    }

    if (pid == 0) {  /* Child.*/
        if(close(pipe_in)<0){
            err_sys("close error");
        }
        if(close(pipe_out)<0){
            err_sys("close error");
        }
        /* sleep(5); */
        return EXIT_SUCCESS;
    } else {  /* Parent.*/
        fd_set readfds, writefds, exceptfds;

        if(close(pipe_out)<0){
            err_sys("close error");
        }

        sleep(1);

        FD_ZERO(&readfds);
        FD_SET(pipe_in, &readfds);
        FD_ZERO(&writefds);
        FD_SET(pipe_in, &writefds);
        FD_ZERO(&exceptfds);
        FD_SET(pipe_in, &exceptfds);

        if(select(pipe_in + 1, &readfds, &writefds, &exceptfds, NULL)<0){
            err_sys("select error");
        }
        if (FD_ISSET(pipe_in, &readfds))
            printf("Ready for reading\n");
        if (FD_ISSET(pipe_in, &writefds))
            printf("Ready for writing\n");
        if (FD_ISSET(pipe_in, &exceptfds))
            printf("Exception\n");

        assert(write(pipe_in, msg, sizeof msg) == sizeof msg);

        /* fprintf(stderr, "Exiting child\n"); */
        if(close(pipe_in)<0){
            err_sys("close error");
        }
        return EXIT_SUCCESS;

    }
}