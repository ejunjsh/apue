#include "apue.h"
#include <sys/socket.h>
#include <fcntl.h>


int main() {
    int pid, fd;
    int fdpair[2];

    if(socketpair(AF_UNIX, SOCK_STREAM, 0, fdpair)<0)
    {
        err_sys("socketpair error");
    }

    TELL_WAIT();

    if((pid = fork())<0){
        err_sys("fork error");
    }

    if (pid == 0) { /*child*/
        if((fd = open("/etc/passwd", O_RDONLY))<0){
            err_sys("open error");
        }

        if(send_fd(fdpair[0], fd)<0){
            err_sys("send_fd error");
        }

        WAIT_PARENT();
        if(lseek(fd, 10, SEEK_SET)<0){
            err_sys("lseek error");
        }
        TELL_PARENT(getppid());

        WAIT_PARENT();
        if(lseek(fd, 20, SEEK_SET)<0){
            err_sys("lseek error");
        }
        TELL_PARENT(getppid());

        return EXIT_SUCCESS;

    } else { /* parent*/
        if((fd = recv_fd(fdpair[1], write))<0){
            err_sys("recv_fd error");
        }
        printf("Parent: got fd: %d, seek: %lld\n", fd, (long long)lseek(fd, 0, SEEK_CUR));
        TELL_CHILD(pid);

        WAIT_CHILD();
        printf("Parent: seek after child changed it: %lld (should be 10)\n", (long long)lseek(fd, 0, SEEK_CUR));
        TELL_CHILD(pid);

        WAIT_CHILD();
        printf("Parent: seek after child changed it second time: %lld (should be 20)\n", (long long)lseek(fd, 0, SEEK_CUR));

        return EXIT_SUCCESS;
    }

}