int*
f1(int val)
{
	int		num = 0;
	int		*ptr = &num;

	if (val == 0) {
		int		val;

		val = 5;
		ptr = &val;
	}
	return ptr;
}


main(void){
	int *c=f1(0);
	int a[100];
	for(int i=0;i<100;i++){
		a[i]=i;
	}
	printf("%d\n",*c+1);
}
