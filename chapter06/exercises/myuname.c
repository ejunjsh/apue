#include"apue.h"
#include<sys/utsname.h>


int main(void)
{
	int n;
	struct utsname myuname;
	if((n=uname(&myuname))<0)
		err_sys("uname error");
	else
		printf("%s\t%s\t%s\t%s\t%s",myuname.sysname,myuname.nodename,myuname.version,myuname.release,myuname.machine);

	exit(0);
}