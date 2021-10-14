#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	FILE *fp, *fp2;
	int n;
	if(argc > 3){
		perror("input error");
		exit(1);
	}

	char* inputFile = argv[1];
	char* outputFile = argv[2];

	fp = fopen(inputFile, "r");
	if(fp == NULL){
		perror("fopen r");
		exit(1);
	}

	fp2 = fopen(outputFile, "w");
	if(fp2 == NULL){
		perror("fopen w");
		exit(1);
	}

	while( (n = fgetc(fp)) > 0){
		if(n >= 'a' && n <= 'z'){
			//소문자
			n -= 32;
		}
		fputc(n, fp2);
	}

	fclose(fp);	
	fclose(fp2);

	return 0;
}
