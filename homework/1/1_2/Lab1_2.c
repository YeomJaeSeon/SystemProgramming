#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void){
	int rfd, n;
	char fileName[256];
	char findString[256];
	size_t findStringLength;
	int start = 0;
	int correctCount = 0;
	clock_t startTime, endTime;
	int *arrayList = (int*)malloc(sizeof(int) * 10);

	scanf("%s", fileName);
	scanf("%s", findString);

	startTime = clock();

	findStringLength = strlen(findString);
	char buf[(int)strlen(findString)];

	rfd = open(fileName, O_RDONLY, 0444);
	if(rfd == -1){
		perror("read");
		exit(1);
	}

	while((n = read(rfd, buf, strlen(findString))) > 0){
		if(strcmp(findString, buf) == 0){
			printf("Compare %s : %s - MATCHED!!\n", findString ,buf);
			arrayList[correctCount] = lseek(rfd, 0, SEEK_CUR);
			correctCount++;
		}else{
			printf("Compare %s : %s\n", findString, buf);
		}
		lseek(rfd, ++start, SEEK_SET);
	}

	if(n == -1){
		perror("read");
		exit(1);
	}

	endTime = clock();
	printf("걸린 시간 : %lf\n", (float)(endTime - startTime) / CLOCKS_PER_SEC);
	for(int i = 0; i < correctCount; i++){
		printf("# of'%s' in the text file is %d\n", findString, arrayList[i]);
	}

	close(rfd);
	free(arrayList);

	return 0;
}
