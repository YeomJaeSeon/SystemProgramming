#include <stdio.h>

int main(void){
	char *ptr;
	char ch = 'a';

	ptr = &ch;
	printf("ptr : %p\n", ptr);
	printf("*ptr : %c\n", *ptr);
	printf("ch : %c\n", ch);
	printf("&ch : %p\n", &ch);
	printf("&ptr : %p\n", &ptr);

	return 0;
}

