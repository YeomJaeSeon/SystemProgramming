//#include <sys/sysinfo.h> macos not found
#include <stdio.h>
#include <stdlib.h>

int main(void){
	struct info;

	while( sysinfo(&info) == -1){
		perror("sysinfo");
		exit(1);
	}

	printf("%ld\n", info.loads[0]);

	return 0;
}
