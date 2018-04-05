#include "apue.h"
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int rfd, wfd, n;
	char buf;
	if (argc != 3)
	{
		printf("Usage: mycp file1 file2\n");
		exit(1);
	}	
	if ((rfd = open(argv[1], O_RDONLY)) < 0)
		err_sys("open file1");
	if ((wfd = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, FILE_MODE)) < 0)
		err_sys("open file2");
	while ((n=read(rfd, &buf, 1))>0)
	{
		if (buf == '\0')  
			continue;
		if (write(wfd, &buf, 1) < 0)
			err_sys("write");
	}
	if (n < 0)
		err_sys("read");
	
	exit(0);
}