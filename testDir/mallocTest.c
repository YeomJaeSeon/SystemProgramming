#include <stdlib.h>
#include <stdio.h>

int main(){
	printf("동적할당 기본\n");

	int number1 = 100;
	int *number1Ptr;

	number1Ptr = &number1;

	int* number2 = malloc(sizeof(int));

	printf("%p\n", number1Ptr); // 메모리 스택에 할당
	printf("%p\n", number2); // 메모리 힙에 할당(동작할당하면 메모리중 힙에 할당됨

	printf("%d\n", *number1Ptr);
	printf("%d\n", *number2);
	*number2 = 200;
	printf("%d\n", *number2);

	free(number2);
	return 0;
}
