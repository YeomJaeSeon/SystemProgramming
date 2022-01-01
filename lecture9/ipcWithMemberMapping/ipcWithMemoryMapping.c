#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#define CHECK_MMAP_SUCCESS(_addr)\
if(_addr == MAP_FAILED){\
    perror("mmap");\
    exit(1);\
}

int main(int argc, char *argv[]){
    int fd;
    caddr_t addr;
    char fileName[255] = "input.dat";

    if(argc > 1) strcpy(fileName, argv[1]);

    if( (fd = open(fileName, O_RDWR)) == -1 ){
        perror("open");
        exit(1);
    }

    int pageSize = getpagesize();
    printf("pageSize : %d\n", pageSize);

    // addr: 할당된 메모리 주소, 즉 파일과 매핑된 메모리의 주소이다.
    addr = mmap(NULL, pageSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, (off_t)0);
    CHECK_MMAP_SUCCESS(addr);

    close(fd);

    // 자식 프로세스를 만드는데, 부모프로세스와 자식 프로세스는 각각의 메모리 region을 가지고 있다.(독립적인)
    // 그러나 두 메모리는 input.dat이라는 파일 하나와 매핑되어 있다.
    // 그래서 부모 프로세스가 input.dat 파일과 매핑된 메모리를 이용해 변경을 가하면 자식 프로세스도 볼수 있다.
    // 이렇게 두 프로세스는 매핑된 하나의 파일을 통해서 communication을 한다.
    // 이게 두 프로세스간의 inter process communication이다.
    int pid = 0;
    switch( pid = fork()){
        case -1:
            perror("fork");
            exit(1);
            break;
        case 0:
            printf("1. Child Process : addr=%s", addr);
            sleep(1);
            addr[0] = 'x';
            printf("2. Child Process : addr=%s", addr);
            sleep(2);
            printf("3. Child Process : addr=%s", addr);
            break;
        default:
            printf("1. Parent process : addr=%s", addr);
            sleep(2);
            printf("2. Parent process : addr=%s", addr);
            addr[1] = 'y';
            printf("3. Parent process : addr=%s", addr);
            break;
    }
    return 0;
} 
