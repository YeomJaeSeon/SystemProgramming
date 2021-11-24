#include <sys/types.h>
#include <sys/times.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	if(argc != 3){
		printf("correct execute format : {exeFile} {targetFile} {copyFile}");
		exit(1);
	}

	char* targetFile = argv[1];
	char* copyFile = argv[2];
	time_t t;
	struct tms mytms;
	clock_t t1, t2;

	if(( t1 = times(&mytms) ) == -1){
		perror("times 1");
		exit(1);
	}

	int rfd = open(targetFile, O_RDONLY);

	if(rfd == -1){
		perror("open");
		exit(1);
	}

	int wfd = open(copyFile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if(wfd == -1){
		perror("open");
		exit(1);
	}

	int readSize;
	char buffer[12];
	while( (readSize = read(rfd, buffer, 12)) > 0){
		time(&t);

		if(write(wfd, buffer, readSize) != readSize){
			perror("write");
			exit(1);
		}
	}
	if(readSize == -1){
		perror("read");
		exit(1);
	}

	if( (t2 = times(&mytms)) == -1){
		perror("times 2 ");
		exit(1);
	}

	printf("Real time : %.2f sec\n", (double)(t2 - t1) / sysconf(_SC_CLK_TCK));
	printf("User time : %.2f sec\n", (double)mytms.tms_utime / sysconf(_SC_CLK_TCK));
	printf("System time : %.2f sec\n", (double)mytms.tms_stime / sysconf(_SC_CLK_TCK));
	

	close(rfd);
	close(wfd);
	
	double sum = (double)mytms.tms_utime / sysconf(_SC_CLK_TCK) * 100 + (double)mytms.tms_stime / sysconf(_SC_CLK_TCK) * 200;

	printf("사용료는 %d입니다.\n", (int)sum);
	return 0;
}


