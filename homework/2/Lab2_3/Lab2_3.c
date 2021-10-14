#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	if(argc > 3){
		perror("input argument error");
		exit(1);
	}

	char* inputFileName = argv[1];
	char* outputFileName = argv[2];
	FILE *fp;

	int fd;

	fd = open(inputFileName, O_RDONLY, 0444);
	if(fd == -1){
		perror("input open");
		exit(1);
	}
	
	char buf[3] = {0};
	ssize_t n;

	fp = fopen(outputFileName, "w");
	if(fp == NULL){
		perror("output file");
		exit(1);
	}


	while( (n = read(fd, buf, 3)) > 0){
		unsigned int value = buf[0] * 65536 + buf[1] * 256 + buf[2];
		fprintf(fp, "%u ", value);
	}

	close(fd);
	fclose(fp);
	return 0;
}
