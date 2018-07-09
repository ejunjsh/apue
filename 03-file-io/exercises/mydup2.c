#include "apue.h"

#define	BUFFSIZE	4096

int mydup2(const int ofd, const int nfd) {

	if(ofd	== nfd) return ofd;

	int pid			= getpid();
	char *pathname	= malloc(sizeof(char) * 128);
	sprintf(pathname, "/proc/%d/fd/%d",pid, nfd);

	if(!access(pathname, F_OK)) close(nfd);

    free(pathname);

	int tmp;
	int max			= sysconf(_SC_OPEN_MAX);
	int fds[max], i = 0;

	if(max < nfd) return -1;
	do {
		tmp			= dup(ofd);
		if(tmp < 0) break;
		fds[i ++]	= tmp;
	} while(tmp < nfd);


	if(tmp == nfd) i --;
	while(i-- > 0) {
        close(fds[i]);
    }

	if(tmp != nfd) return -1;
	return nfd;
}

int main(int argc, char *argv[])
{
	int	newfd = 10;
    int newfd1=20;
	char buf[BUFFSIZE];
	int	n;

	if(mydup2(STDIN_FILENO, newfd)<0){
        err_sys("mydup2 error");
    }

    if(mydup2(STDOUT_FILENO, newfd1)<0){
        err_sys("mydup2 error");
    }

	while ((n = read(newfd, buf, BUFFSIZE)) > 0)
		if (write(newfd1, buf, n) != n)
			err_sys("write error");

	if (n < 0)
		err_sys("read error");

	exit(0);

}
