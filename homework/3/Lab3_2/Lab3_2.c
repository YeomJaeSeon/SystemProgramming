#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

const int MODE[9] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};

void checkPer(struct stat ,char[], int);

int main(void){
	DIR *dp;
	struct dirent *dent;

	if( (dp = opendir("./")) == NULL){
		perror("opendir: current dir ");
		exit(1);
	}

	while( (dent = readdir(dp))){

		char* fileName;
		struct stat buf;
		fileName = dent->d_name;
		stat(fileName, &buf);	
		printf("%d\n", S_ISREG(buf.st_mode));
		if(S_ISREG(buf.st_mode) == 0) continue; // 일반파일 아니면 continue
		
		// 파일 권한
		char perChar[11];
		perChar[0] = '-';
				
		for(int i = 0; i < 9; i++){
			checkPer(buf, perChar, i);
		}
		
		perChar[10] = '\0';

		printf("%s   ", perChar);
		
		printf("%u   ", buf.st_nlink);
		
		printf("%lld   ", buf.st_size);
	
		time_t time;

		time = buf.st_mtime;
	
		struct tm* timeInfo;
		timeInfo = localtime(&time);
		int month= timeInfo->tm_mon + 1;
		int day = timeInfo->tm_mday;

		int hour = timeInfo->tm_hour;
		int min = timeInfo->tm_min;
		printf("%d %d %d:%d ", month, day, hour, min);
		printf("%s \n", fileName);

	}

	closedir(dp);
	
	return 0;
}

void checkPer(struct stat buf ,char perChar[], int i){
	int kind;

	kind = MODE[i] & buf.st_mode;
	
	if(kind == MODE[i]){
		if(i % 3 == 0)
			perChar[i + 1] = 'r';
		else if(i % 3 == 1)
			perChar[i + 1] = 'w';
		else if(i % 3 == 2)
			perChar[i + 1] = 'x';
	}else{
		perChar[i + 1] = '-';
	}

}
