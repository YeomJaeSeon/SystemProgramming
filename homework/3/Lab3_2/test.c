#include <stdio.h>

void print1(char[]);
void print2(char *);

int main(void){
	char arr[3] = {'a', 'b', 'c'};

	printf("&arr :%d\n", &arr[0]);
	printf("arr : %d\n", arr);

	print1(arr);
	print2(arr);
	return 0;
}

void print1(char arr[]){
	printf("print1 : %s\n", arr);
}

void print2(char* arr){
	printf("print2 : %s\n", arr);
}
