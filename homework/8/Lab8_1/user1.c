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

int main(){
    int fd;
    caddr_t addr1;
    char buf[15] = {0};

    if( (fd = open("firstMessage.dat", O_RDWR | O_CREAT, 0644)) == -1){
        perror("open");
        exit(1);
    }
    // fd 가 가르키는 파일 크기가 0 byte면 mmap시 bus error 오류 뜬다.
    buf[0] = '1';
    write(fd, buf, 10);

    int pageSize = getpagesize();
    // firstMessage.dat 파일과 매핑된 메모리 주소 - addr1
    addr1 = mmap(NULL, pageSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, (off_t)0);
    CHECK_MMAP_SUCCESS(addr1);
    
    close(fd);

    printf("[발신]");
    scanf("%s", addr1);
 
    if(strlen(addr1) > 15){
        printf("15글자 초과해서 메시지 보낼수 없음.");
        exit(1);
    }
    addr1[(int)strlen(addr1)] = '%';
    addr1[(int)strlen(addr1) + 1] = '\0';

    msync(addr1, pageSize, MS_SYNC);

    while(1){
        if( (fd = open("secondMessage.dat", O_RDONLY)) != -1 ) {
            addr1 = mmap(NULL, getpagesize(), PROT_READ, MAP_SHARED, fd, (off_t)0);
            if(addr1[strlen(addr1) - 1] == '%') break;
            close(fd);
        }
        sleep(1);
    }
    close(fd);
 
    char message[15];

    strcpy(message, addr1);
    message[(int)strlen(message) - 1] = '\0';
    printf("[수신]%s\n", message);

    execlp("rm", "rm", "-f", "secondMessage.dat", NULL);
    return 0;
}

