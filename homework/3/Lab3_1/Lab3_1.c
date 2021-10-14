#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/errno.h>
#include <stdlib.h>

extern int errno;

void printFileMode(char* file, int readPermission);

int main(int argc, char* argv[]){
	if(argc != 3){
		printf("input example : {execute file} {target file1} {target file2}\n");
		exit(1);
	}

	struct stat buf1;
	struct stat buf2;
	char* file1 = argv[1];
	char* file2 = argv[2];

	int permission;
	
	stat(file1, &buf1);
	stat(file2, &buf2);

	unsigned int file1Size = (unsigned int)buf1.st_size;
	unsigned int file2Size = (unsigned int)buf2.st_size;

	if(file1Size > file2Size){
		printf("%s is bigger\n", file1);
		permission = access(file1, R_OK);
		printFileMode(file1, permission);

	}else if(file1Size < file2Size){
		printf("%s is bigger\n", file2);
		permission = access(file2, R_OK);
		printFileMode(file2, permission);
	}else{
		printf("두 파일의 사이즈가 같습니다.\n");
	}

	
	return 0;
}

void printFileMode(char *file, int readPermission){
	if(readPermission == 0){
		printf("%s : Read permission is permitted\n", file);
	}else if(readPermission == -1 && errno == EACCES){
		printf("%s : Read permission is not permitted\n", file);
	}
}
