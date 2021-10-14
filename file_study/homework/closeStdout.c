#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int fileOpen(void) {
	int fd = 0;
	fd = open("hello.txt", O_RDWR);
	if(fd == -1){
		perror("file open");
		exit(1);
	}

	return fd;
}

int main(void){
	int fd = 0;
	fd = fileOpen();
	printf("fd : %d\n", fd);
	close(fd);

	close(1);

	fd = fileOpen();
	printf("fd : %d\n", fd);
	close(fd);

	return 0;
}
