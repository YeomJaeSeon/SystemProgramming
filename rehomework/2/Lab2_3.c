#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	if(argc != 3){
		printf("./Lab2_3.out <input> <output>\n");
		exit(1);
	}

	int fd;
	FILE *fp;
	char* inputFile = argv[1];
	char* outputFile = argv[2];

	fd = open(inputFile, O_RDONLY, 0444);
	if(fd == -1){
		perror("open");
		exit(1);
	}
	
	fp = fopen(outputFile, "w");
	if(fp == NULL){
		printf("fopen error");
		exit(1);
	}

	ssize_t n;
	char buf[3] = { 0 };

	while( (n = read(fd, buf, 3) ) > 0){
		unsigned int value = buf[0] * 65536 + buf[1] * 256 + buf[2];

		fprintf(fp, "%u ", value);
	}	

	close(fd);
	fclose(fp);

	return 0;
}
