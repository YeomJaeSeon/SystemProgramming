#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#define CHECK_MMAP_SUCCESS(_addr)       \
if(_addr == MAP_FAILED){                \
    perror("mmap");                     \
    exit(1);                            \
}                                       

#define printAddrs(msg)                 \
{                                       \
    printf("%s\n", msg);                \
    printf("addr1 = %s", addr1);        \
    printf("addr2 = %s", addr2);        \
}                                       

int main(int argc,char *argv[]){
    int fd;
    caddr_t addr1, addr2;

    char fileName[255] = "input.dat";

    if(argc > 1) strcpy(fileName, argv[1]);

    if( (fd = open(fileName, O_RDWR)) == -1){
        perror("open");
        exit(1);
    }

    int pageSize = getpagesize();
    
    //flag는 SHARED로 메모리와 파일을 매핑
    addr1 = mmap(NULL, pageSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, (off_t)0);
    CHECK_MMAP_SUCCESS(addr1);
    //addr1 메모리 주소에 매핑되는 파일은 offset은 0으로 처음부터, 길이는 pageSize만큼을 매핑한다.(offset은 page크기의 배수여야한다. - pagingSystem에서 파일은 페이지로 나누어지는데, offset이 배수가 아니면 페이지하나가 온전하게 메모리에 매핑되지가 않는다.)

    //flag는 PRIVATE으로 메모리와 파일을 매핑
    addr2 = mmap(NULL, pageSize, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, (off_t)0);
    CHECK_MMAP_SUCCESS(addr2);

    close(fd);

    printf("%s", addr1);

    //addr1은 메모리에 쓰면 매핑된 파일에도 써짐(SHARED)
    addr1[0] = '1'; printAddrs("After addr1[0]=1");
    //addr2는 메모리에 쓰면 파일에 써지는게 아닌 사본에 써짐(PRIVATE)
    addr2[0] = '2'; printAddrs("After addr2[0]=2");
    //addr1은 메모리에 써도, addr2는 이제 사본을 바라보고 있기에, 다른 값이 출력된다.
    addr1[0] = '3'; printAddrs("After addr1[0]=3");

    execlp("cat", "cat", fileName, NULL);

    return 0;
}
