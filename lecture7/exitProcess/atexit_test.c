#include <stdlib.h>
#include <stdio.h>

void cleanup1(void){
	printf("Cleanup1 is called.\n");
}

void cleanup2(void){
	printf("Cleanup2 is called.\n");
}

int main(void){
	printf("main function start\n");
	atexit(cleanup1);
	atexit(cleanup2);
	// cleanup2 -> cleanup1 (역순)
	printf("exit start\n");
	exit(0);
}
