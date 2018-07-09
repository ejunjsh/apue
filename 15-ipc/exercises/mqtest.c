#include "apue.h"
#include <sys/ipc.h>
#include <sys/msg.h>


int main() {
    int i;
    printf("First loop\n");
    for (i = 0; i < 5; ++i) {
        key_t key;
        int queue_id;
        /* Create a message queue.*/
        if((key = ftok("/dev/null", i))<0){
            err_sys("ftok error");
        }
        if((queue_id = msgget(key, IPC_CREAT | S_IWUSR | S_IRUSR))<0){
            err_sys("msgget error");
        }
        /* Print the queue identifier.*/
        printf("Queue ID: %d\n", queue_id);
        /* Delete the queue.*/
        if((msgctl(queue_id, IPC_RMID, NULL))<0){
             err_sys("msgctl error");
        }
    }

    printf("Second loop\n");
    char msg[] = "hello";
    for (i = 0; i < 5; ++i) {
        int queue_id;

        /* Create a message queue with a key IPC_PRIVATE.*/
        if((queue_id = msgget(IPC_PRIVATE, IPC_CREAT | S_IWUSR | S_IRUSR))<0){
            err_sys("msgget error");
        }
         /* Print the queue identifier.*/
        printf("Queue ID: %d\n", queue_id);
        /* Place a message on the queue.*/
        if((msgsnd(queue_id, msg, sizeof msg, 0))<0){
            err_sys("msgsnd error");
        }
    }

    return EXIT_SUCCESS;
}