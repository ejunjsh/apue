#include "apue.h"
#include <sys/socket.h>
#include <sys/un.h>


int main() {
    int s;
    char sockpath[] = "foo.socket";
    struct sockaddr_un un;

    unlink(sockpath);

    un.sun_family = AF_UNIX;
    strcpy(un.sun_path, sockpath);
    if((s = socket(AF_UNIX, SOCK_STREAM, 0))<0){
        err_sys("socket error");
    }
    if(bind(s, (struct sockaddr *)&un, sizeof(struct sockaddr_un))<0){
        err_sys("bind error");
    }

    struct stat buf;
    if(fstat(s, &buf)<0){
        err_sys("fstat error");
    }

    printf("ID of device containing file: %lld\n",       (long long)buf.st_dev);
    printf("inode number: %lld\n",                       (long long)buf.st_ino);
    printf("protection: %o\n",                           (unsigned int)buf.st_mode);
    printf("number of hard links: %lld\n",               (long long)buf.st_nlink);
    printf("user ID of owner: %lld\n",                   (long long)buf.st_uid);
    printf("group ID of owner: %lld\n",                  (long long)buf.st_gid);
    printf("device ID (if special file): %lld\n",        (long long)buf.st_rdev);
    printf("total size, in bytes: %lld\n",               (long long)buf.st_size);
    printf("blocksize for filesystem I/O: %lld\n",       (long long)buf.st_blksize);
    printf("number of 512B blocks allocated %lld\n",     (long long)buf.st_blocks);


    return EXIT_SUCCESS;
}