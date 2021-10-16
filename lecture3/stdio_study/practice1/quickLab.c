#include <stdio.h>
#include <stdlib.h>

int main(void){
	FILE *fp; //file pointer;

	if ((fp = fopen("hello.txt", "w")) == NULL){
		perror("fopen : hello.txt");
		exit(1);
	}
	
	fclose(fp);

	return 0;
}
