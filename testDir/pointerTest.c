#include <stdio.h>

int main(void){
	int value = 100;
	int *valuePtr;
	valuePtr = &value;

	printf("valuePtr : %p\n", valuePtr);
	printf("*valuePtr : %d\n", *valuePtr);
	printf("value : %d\n", value);
	printf("&valuePtr : %p\n", &valuePtr);

	return 0;
}
