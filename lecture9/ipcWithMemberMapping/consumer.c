#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
    int fd;
    char* addr;
    char fileName[255] = "map.dat";

    if(argc > 1) strcpy(fileName, argv[1]);
    if (( fd = open(fileName, O_RDWR)) == -1 ){
        perror("open");
        exit(1);
    }

    addr = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, fd, (off_t)0);

    close(fd);

    while(1){
        sleep(2);
        printf("%c\n", addr[0]);
    }

    return 0;
}
