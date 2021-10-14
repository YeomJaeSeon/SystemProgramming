#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/uio.h>

int main(void){
	int fd;
	int targetFd;

	fd = open("jaeseon.txt", O_RDONLY);
	if(fd == -1){
		perror("open jaeseon");
		exit(1);
	}
	printf("jaese fd : %d\n", fd);

	targetFd = open("copy.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if(targetFd == -1){
		perror("open copy");
		exit(1);
	}
	printf("target fd : %d\n", targetFd);

	int n; // 파일에서 읽은 byte size
	char buf[256]; //읽은내용 저장할 버퍼
	
	while((n = read(fd, buf, 6)) > 0){
		if(write(targetFd, buf, n) != n) perror("write");	
		}
	if(n == -1)
		perror("read");


	close(fd);
	close(targetFd);

	return 0;
}
