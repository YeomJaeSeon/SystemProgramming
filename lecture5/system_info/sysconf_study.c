#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void){
	printf("clock Tick : %ld\n", sysconf(_SC_CLK_TCK));
	printf("max file open : %ld\n", sysconf(_SC_OPEN_MAX));
	return 0;
}
