#include "apue.h"
#include <fcntl.h>
#include <sys/socket.h>

#define MAX_FDS_LEN 1024


void send_fds(int sockfd, int fds[], int fds_len) {
    struct msghdr   msg = { 0 };
    struct cmsghdr  *cmsg;
    int             fds_size = sizeof(int) * fds_len;
    char            buf[CMSG_SPACE(fds_size)];
    struct iovec    iov[1];
    int             iov_buf[1];

    iov_buf[0] = fds_len;

    iov[0].iov_base = iov_buf;
    iov[0].iov_len  = sizeof iov_buf;
    msg.msg_iov     = iov;
    msg.msg_iovlen  = 1;

    msg.msg_control = buf;
    msg.msg_controllen = sizeof buf;

    cmsg = CMSG_FIRSTHDR(&msg);
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_len = CMSG_LEN(fds_size);

    memcpy(CMSG_DATA(cmsg), fds, fds_size); 

    msg.msg_controllen = cmsg->cmsg_len;

    printf("my_send_fd: about to send fds:");
    for (int i = 0; i < fds_len; ++i) printf(" %d", fds[i]);
    printf("\n");
    if(sendmsg(sockfd, &msg, 0)<0){
        err_sys("sendmsg error");
    }
    printf("my_send_fd: send\n");
}


void recv_fds(int sockfd, int **fds, int *fds_len) {
    struct msghdr   msg = { 0 };
    struct cmsghdr  *cmsg = malloc(CMSG_LEN(sizeof(int) * MAX_FDS_LEN));
    if (cmsg == NULL)
        err_quit("malloc error");
    struct iovec    iov[1];
    int             iov_buf[1];

    iov[0].iov_base = iov_buf;
    iov[0].iov_len  = sizeof(iov_buf);
    msg.msg_iov     = iov;
    msg.msg_iovlen  = 1;
    msg.msg_name    = NULL;
    msg.msg_namelen = 0;

    msg.msg_control = cmsg;
    msg.msg_controllen = CMSG_LEN(sizeof(int) * MAX_FDS_LEN);

    printf("my_recv_fd: about to recieve fd\n");
    if(recvmsg(sockfd, &msg, 0)<0){
        err_sys("recvmsg error");
    }
    printf("my_recv_fd: recieved\n");
    cmsg = CMSG_FIRSTHDR(&msg);
    *fds = (int *)CMSG_DATA(cmsg);
    *fds_len = iov_buf[0];
}


int main() {
    int pid;
    int fds[3];
    int spair[2];

    if (fd_pipe(spair) < 0) {
        err_sys("fd_pipe error");
    }
    if((pid = fork())<0){
        err_sys("fork error");
    }
    if (pid == 0) {  /* Child*/
        if((fds[0] = open("/etc/passwd", O_RDONLY))<0){
            err_sys("open error");
        }
        if(lseek(fds[0], 5, SEEK_SET)<0){
            err_sys("lseek error");
        }
        if((fds[1] = open("/etc/group", O_RDONLY))<0){
            err_sys("open error");
        }
        if(lseek(fds[1], 10, SEEK_SET)<0){
            err_sys("lseek error");
        }
        if((fds[2] = open("/bin/sh", O_RDONLY))<0){
            err_sys("open error");
        }
        if(lseek(fds[2], 20, SEEK_SET)<0){
            err_sys("lseek error");
        }
        send_fds(spair[0], fds, 3);
        return EXIT_SUCCESS;
    } else {  /* Parent.*/
        int *fds;
        int fds_len;
        recv_fds(spair[1], &fds, &fds_len);
        printf("parent: got fds:");
        for (int i = 0; i < fds_len; ++i) {
            printf(" %d (fp=%lld)", fds[i], (long long)lseek(fds[i], 0, SEEK_CUR));
        }
        printf("\n");
        return EXIT_SUCCESS;
    }
}