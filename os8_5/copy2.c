#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int ac,char *av[])
{
    int from = -1 ;
    int to = -1 ;
    caddr_t from_mmap,to_mmap;
    int *p;
    off_t i;
    off_t size,size1;
    int map = MAP_PRIVATE;
    struct stat sb;

    if(ac!=3)  {
    fprintf(stderr,"Usage: %s from_file to_file",av[0]);
    exit(0);
    } 
    if((from=open(av[1],O_RDONLY,0666))==0)  {
    fprintf(stderr,"can't open %s\n",av[1]);
    perror(NULL);
    }
    if( fstat(from, &sb)) {
    fprintf(stderr,"can't fstat %s\n",av[1]);
    }
    i=0;
    size = sb.st_size;
    from_mmap = mmap(NULL,size,PROT_READ,
        map,from,(off_t)0);
    if(from_mmap==(caddr_t)-1) {
    fprintf(stderr,"Can't mmap from\n");
    perror(NULL);
    exit(0);
    }
    if((to=open(av[2],O_CREAT|O_RDWR,0666))==0)  {
    fprintf(stderr,"can't open %s\n",av[2]);
    perror(NULL);
    }
    if(size==0) {
    exit(1);
    }
    lseek(to, size-sizeof(int),  0L);
    write(to,(&i),sizeof(int));
    map = MAP_SHARED;
    to_mmap = mmap(NULL,size,PROT_WRITE|PROT_READ,
        map,to,(off_t)0);
    if(to_mmap==(caddr_t)-1) {
    fprintf(stderr,"Can't mmap to\n");
    perror(NULL);
    exit(0);
    }
    memcpy(to_mmap,from_mmap,size);
    if (msync(to_mmap,size,MS_INVALIDATE)) {
    fprintf(stderr,"msync failure\n");
    exit(0);
    }
    ftruncate(to, size);

    return 1;
}


