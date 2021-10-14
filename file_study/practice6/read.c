#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/uio.h>

int main(void){
	int rfd, wfd, n;
	char buf[256];

	rfd = open("read.txt", O_RDONLY);
	if(rfd == -1){
		perror("open read.txt");
		exit(1);
	}

	wfd = open("write.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if(wfd == -1){
		perror("open write.txt");
		exit(1);
	}

	while((n = read(rfd, buf, 5)) > 0){
		printf("buf : %s\n", buf);
		if(write(wfd, buf, n) != n) perror("Write");
	}


	
	off_t curr = lseek(wfd, 0, SEEK_CUR);
	printf("curr point : %d\n", (int)curr);
	
	curr = lseek(wfd, -10, SEEK_END);
	printf("curr point : %d\n", (int)curr);
	
	printf("wfd : %d\n", wfd);

	n = read(wfd, buf, 10);
	if(n == -1){
		perror("read");
		exit(1);
	}
	printf("n : %d, buf : %s\n", n, buf);

	close(rfd);
	close(wfd);

	return 0;

}

