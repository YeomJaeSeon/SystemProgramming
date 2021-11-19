#include <stdlib.h>
#include <stdio.h>

int main(void){
	char *val;

	val = getenv("TEST");
	if (val == NULL)
		printf("SHELL NOT DEFINED with env variable\n");
	else
		printf("SHELL = %s\n", val);

	return 0;
}
