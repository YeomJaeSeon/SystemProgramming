#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <time.h>

#define ON_TIMER { startTime = clock(); }
#define OFF_TIMER { endTime = clock(); }
#define MAX_CHUNK_SIZE 2048

int str2int(char* str);
void printTimer(int startTime, int endTime, double nProcessExecuteTime);

int main(int argc, char* argv[]){
	clock_t startTime, endTime;
	int rfd, wfd, chunkSize, n;
	char buf[MAX_CHUNK_SIZE];
	char copyTargetName[2000];
	double nProcessExecuteTime;

	if(argc > 4){
		printf("Proper Example : ./exeFile input output chunkSize\n");
		exit(0);
	}

	chunkSize = str2int(argv[3]);
	chunkSize = (MAX_CHUNK_SIZE < chunkSize ? MAX_CHUNK_SIZE : chunkSize);

	printf("Copy %s to %s (chunk size = %d)\n", argv[1], argv[2], chunkSize);

	rfd = open(argv[1], O_RDWR, 0644);
	wfd = open(argv[2], O_CREAT | O_RDWR, 0644);

	if(rfd == -1){
		perror("open");
		exit(1);
	}
	if(wfd == -1){
		perror("open");
		exit(1);
	}

	ON_TIMER;

	while((n = read(rfd, buf, chunkSize)) > 0){
		if(write(wfd, buf, n) != n){
			perror("write");
			exit(1);
		}
	}
	if(n == -1){
		perror("read");
		exit(1);
	}


	OFF_TIMER;
	printTimer(startTime, endTime, nProcessExecuteTime);

	close(rfd);
	close(wfd);
	
	return 0;
}

int str2int(char* str){
	int val = str[0] - '0';
	int i = 1;
	printf("val : %d\n", val);
	printf("%d\n", '0');
	while(str[i] != '\0'){
		val *= 10;
		val += str[i] - '0';
		i++;
	}

	return val;
}

void printTimer(int startTime, int endTime, double nProcessExecuteTime){
	nProcessExecuteTime = ( (double)(endTime - startTime) ) / CLOCKS_PER_SEC;
	printf("It takes %f seconds\n", nProcessExecuteTime);
}
