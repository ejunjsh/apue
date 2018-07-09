#include <unistd.h>
#include <time.h>
#include <sys/select.h>
#include <stdio.h>

unsigned
sleep(unsigned seconds)
{
	int n;
	unsigned slept;
	time_t start, end;
	struct timeval tv;

	tv.tv_sec = seconds;
	tv.tv_usec = 0;
	time(&start);
	n = select(0, NULL, NULL, NULL, &tv);
	if (n == 0)
		return(0);
	time(&end);
	slept = end - start;
	if (slept >= seconds)
		return(0);
	return(seconds - slept);
}

int 
main(void){
    time_t start,end;
    time(&start);
    printf("start sleep 10, time is %ld \n",start);
    sleep(10);
    time(&end);
    printf("end sleep 10, time is %ld \n",end);
    return 0;
}