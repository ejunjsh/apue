#include "apue.h"
#include <poll.h>



int main() {
    int pid, pipe_in, pipe_out;
    int pipe_fds[2];

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
        return EXIT_SUCCESS;

    } else {  /* Parent.*/
        struct pollfd fds[1];

        if(close(pipe_out)<0){
            err_sys("pipe error");
        }

        fprintf(stderr, "Sleeping... ");
        sleep(5);
        fprintf(stderr, "Done.\n");

        fds[0].fd = pipe_in;
        fds[0].events = POLLIN | POLLOUT;


        if(poll(fds, 1, 0)<0){
            err_sys("poll error");
        }
        if (fds[0].revents & POLLIN)
            printf("Ready for reading\n");
        if (fds[0].revents & POLLOUT)
            printf("Ready for writing\n");
        if (fds[0].revents & POLLERR)
            printf("Poll error\n");
        if (fds[0].revents & POLLHUP)
            printf("POLLHUP\n");
        if (fds[0].revents & POLLNVAL)
            printf("POLLNVAL\n");

        return EXIT_SUCCESS;
    }
}