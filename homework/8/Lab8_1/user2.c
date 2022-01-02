#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

int main(){
    int fd;
    caddr_t addr1;
    
    while(1){
        if( (fd = open("firstMessage.dat", O_RDONLY)) != -1 ) {
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
    
    
    if( (fd = open("secondMessage.dat", O_RDWR | O_CREAT, 0644)) == -1 ){
        perror("open");
        exit(1);
    }
    
    char buf[15] = {0};

    buf[0] = '1';
    write(fd, buf, 10);

    addr1 = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, fd, (off_t)0);

    close(fd);

    printf("[발신]");
    scanf("%s", addr1);

    if(strlen(addr1) > 15){
        printf("15글자 초과해서 메시지 보낼수 없음");
        exit(1);
    }

    addr1[(int)strlen(addr1)] = '%';
    addr1[(int)strlen(addr1) + 1] = '\0';

    msync(addr1, getpagesize(), MS_SYNC);

    execlp("rm", "rm", "-f", "firstMessage.dat", NULL);

    return 0;


}
