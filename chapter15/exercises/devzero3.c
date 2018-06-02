#include "apue.h"
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define NLOOPS      1000
#define SIZE        sizeof(long)    /* size of shared memory area */
#define SHM_MODE    0600


static int
update(long *ptr)
{
    fprintf(stderr, "%d: Increasing %ld\n", getpid(), *ptr);
    return((*ptr)++);   /* return value before increment */
}

int
main(int argc, char *argv[])
{
    int     shmid, fd, i, counter;
    void    *area;
    pid_t   pid;

    if((shmid = shmget(IPC_PRIVATE, SIZE, SHM_MODE))<0){
        err_sys("shmget error");
    }
    if(((long)(area = shmat(shmid, 0, 0)))<0){
        err_sys("shmat error");
    }

    if((fd = open("README.md", O_RDWR))<0){
        err_sys("open error");
    }

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid > 0) {           /* parent */
        for (i = 0; i < NLOOPS; i += 2) {
            
            while(1){
                writew_lock(fd, 0, SEEK_SET, 1);
                if(*((long *)area)%2)
                un_lock(fd, 0, SEEK_SET, 1);
                else
                break;
            }

            if ((counter = update((long *)area)) != i)
                err_quit("parent: expected %d, got %d", i, counter);

            
            un_lock(fd, 0, SEEK_SET, 1);
            
        }
    } else {                        /* child */
        for (i = 1; i < NLOOPS + 1; i += 2) {
            
            while(1){
                writew_lock(fd, 0, SEEK_SET, 1);
                if(*((long *)area)%2)
                break;
                else
                un_lock(fd, 0, SEEK_SET, 1);
            }

            if ((counter = update((long *)area)) != i)
                err_quit("child: expected %d, got %d", i, counter);

            un_lock(fd, 0, SEEK_SET, 1);

        }
    }

    exit(0);
}