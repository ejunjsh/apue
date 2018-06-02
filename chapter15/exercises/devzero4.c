#include "apue.h"
#include <stdbool.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <semaphore.h>

#define NLOOPS      1000
#define SIZE        sizeof(long)    /* size of shared memory area */
#define SHM_MODE    0600


static int
update(long *ptr)
{
    fprintf(stderr, "Increasing %ld\n", *ptr);
    return((*ptr)++);   /* return value before increment */
}

int
main(void)
{
    int     shmid, i, counter;
    void    *area;
    pid_t   pid;
    sem_t   *child_sem, *parent_sem;

    if((shmid = shmget(IPC_PRIVATE, SIZE, SHM_MODE))<0){
        err_sys("shmget error");
    }
    if(((long)(area = shmat(shmid, 0, 0)))<0){
        err_sys("shmat error");
    }

    parent_sem = sem_open("parent", O_CREAT, S_IWUSR | S_IRUSR, 1);
    if(parent_sem==SEM_FAILED){
        err_sys("sem_open error");
    }
    child_sem = sem_open("child", O_CREAT, S_IWUSR | S_IRUSR, 0);
    if(child_sem==SEM_FAILED){
        err_sys("sem_open error");
    }

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid > 0) {           /* parent */
        for (i = 0; i < NLOOPS; i += 2) {
            /* Can parent run?*/
            if(sem_wait(parent_sem)<0){
                err_sys("sem_wait error");
            }

            if ((counter = update((long *)area)) != i)
                err_quit("parent: expected %d, got %d", i, counter);

            /* Allow child to run.*/
            if(sem_post(child_sem)<0){
                err_sys("sem_post error");
            }
        }
    } else {                        /* child */
        for (i = 1; i < NLOOPS + 1; i += 2) {
            /* Can child run?*/
            if(sem_wait(child_sem)<0){
                err_sys("sem_wait error");
            }

            if ((counter = update((long *)area)) != i)
                err_quit("child: expected %d, got %d", i, counter);

            /* Allow parent to run.*/
            if(sem_post(parent_sem)<0){
                err_sys("sem_post error");
            }
        }

        /* Remove semaphores.*/
        if(sem_close(parent_sem)<0){
            err_sys("sem_close error");
        }
        if(sem_unlink("parent")<0){
            err_sys("sem_unlink error");
        }
        if(sem_close(child_sem)<0){
            err_sys("sem_close error");
        }
        if(sem_unlink("child")<0){
            err_sys("sem_unlink error");
        }
    }

    exit(0);
}