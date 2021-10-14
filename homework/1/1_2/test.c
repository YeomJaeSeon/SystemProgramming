#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
	int *pointer;

	pointer = (int*)malloc(sizeof(int) * 5);
	pointer[10000] = 10;

	printf("%d\n", pointer[10000]);

	free(pointer);
	return 0;
}
