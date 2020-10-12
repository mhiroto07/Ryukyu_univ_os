#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>

#define K 1024
#define SIZE 1024*100
main(int ac,char *av[]) 
{
    int i,j,count;
    char *pool = (char *)malloc(SIZE*K);
    int flag = atoi(av[1]);
    count = 0;
    j = 0;
    if (flag) {
    if (mlock((char *)((int)main ), 4096)) {
      perror("main mlock");
	exit(1);
    }
    if (mlock((char *)((int)pool ), SIZE*K)) {
      perror("pool mlock");
	exit(1);
    }
    }

    for(;;) {	
	for(i = 0; i < SIZE*K; i++) {
	    pool[i] = j++;
	}
	fprintf(stderr,"loop %5d\n",count++);
    }
}
