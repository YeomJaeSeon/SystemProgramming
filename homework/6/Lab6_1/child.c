#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	if(argc != 3){
		printf("input error, example: <execute file> <readFile> <writeFile>\n");
		exit(1);
	}

	char* rFile = argv[1];
	char* wFile = argv[2];

	FILE *rf;
	FILE *wf;

	if( (rf = fopen(rFile, "r")) == NULL){
		perror("file open");
		exit(1);
	}

	if( (wf = fopen(wFile, "w")) == NULL){
		perror("file open");
		exit(1);
	}

	int c;

	while((c = fgetc(rf)) != EOF){
		fputc(c, wf);
	}

	fclose(rf);
	fclose(wf);

	return 0;
}
