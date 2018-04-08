#include <stdio.h>
#include <stdlib.h>

void mysetbuf(FILE *fp, char *buf)
{
    if (buf == NULL) {
        if (setvbuf(fp, buf, _IONBF, BUFSIZ) != 0) {
            perror("setvbuf error!");
            exit(-1);
        }
        printf("no buf\n");
    } else {
        if (fp == stderr) {
            if (setvbuf(fp, buf, _IONBF, BUFSIZ) != 0) {
                perror("setvbuf error!");
                exit(-1);
            }
            printf("no buf\n") ;
        }else if (fp == stdin || fp == stdout) {
            if (setvbuf(fp, buf, _IOLBF, BUFSIZ) != 0) {
                perror("setvbuf error!");
                exit(-1);
            }
            printf("line buf\n");
        } else {
            if (setvbuf(fp, buf, _IOFBF, BUFSIZ) != 0) {
                perror("setvbuf error!");
                exit(-1);
            }
            printf("full buf\n");
        }
    }
}