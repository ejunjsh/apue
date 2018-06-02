#include "apue.h"
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define NLOOPS      1000
#define SIZE        sizeof(long)    /* size of shared memory area */
#define SHM_MODE    0600

#define SEM_PARENT  0
#define SEM_CHILD   1


#if !(defined(__FreeBSD__) || defined(_DARWIN_C_SOURCE) || defined(__DragonFly__))
union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
};
#endif


static int
update(long *ptr)
{
    fprintf(stderr, "Increasing %ld\n", *ptr);
    return((*ptr)++);   /* return value before increment */
}

int
main(void)
{
    int     shmid, semid, i, counter;
    void    *area;
    pid_t   pid;
    struct sembuf ops[1];
    union semun semopts;

    if((shmid = shmget(IPC_PRIVATE, SIZE, SHM_MODE))<0){
        err_sys("shmget error");
    }
    if(((long)(area = shmat(shmid, 0, 0)))==0){
        err_sys("shmat error");
    }
    if((semid = semget(IPC_PRIVATE, 2, IPC_CREAT | S_IWUSR | S_IRUSR))<0){
        err_sys("semget error");
    }
    semopts.val = 1;
    if((semctl(semid, SEM_PARENT, SETVAL, semopts))<0){
        err_sys("semctl error");
    } /* Parent should run first.*/
    semopts.val = 0;
    if((semctl(semid, SEM_CHILD, SETVAL, semopts))<0){
        err_sys("semctl error");
    }

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid > 0) {           /* parent */
        ops[0].sem_flg = 0;
        for (i = 0; i < NLOOPS; i += 2) {

            /* Can parent run? */
            ops[0].sem_num = SEM_PARENT;
            ops[0].sem_op = -1;
            semop(semid, ops, 1);

            if ((counter = update((long *)area)) != i)
                err_quit("parent: expected %d, got %d", i, counter);

            /* Allow child to run.*/
            ops[0].sem_num = SEM_CHILD;
            ops[0].sem_op = 1;
            semop(semid, ops, 1);

        }
    } else {                        /* child */
        ops[0].sem_num = 0;
        ops[0].sem_flg = 0;
        for (i = 1; i < NLOOPS + 1; i += 2) {
            /* Can child run?*/
            ops[0].sem_num = SEM_CHILD;
            ops[0].sem_op = -1;
            semop(semid, ops, 1);

            if ((counter = update((long *)area)) != i)
                err_quit("child: expected %d, got %d", i, counter);

            /* Allow parent to run.*/
            ops[0].sem_num = SEM_PARENT;
            ops[0].sem_op = 1;
            semop(semid, ops, 1);
        }

        /* Remove semaphore and shared memory.*/
        if(semctl(semid, 0, IPC_RMID)<0){
            err_sys("semctl error");
        }
        if(shmctl(shmid, IPC_RMID, NULL)<0){
            err_sys("shmctl error");
        }
    }

    exit(0);
}