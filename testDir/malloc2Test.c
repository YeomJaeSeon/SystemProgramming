//입력되는 정수 크기의 동적할당 int배열 만들고 할당 해제하기
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	if(argc != 2){
		printf("input error");
		exit(0);
	}

	int size = atoi(argv[1]);

	int* arr;
	arr = (int *)malloc(sizeof(int) * size);

	for(int i = 1; i <= size; i++){
		arr[i - 1] = i;
	}

	for(int i = 0; i < size; i++){
		printf("%d\n", arr[i]);
	}

	free(arr);

	return 0;
}
