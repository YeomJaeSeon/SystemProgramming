#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void printPidAndPgid();

int main(int argc, char* argv[]){
	if(argc != 2){
		printf("correct format : {exeFile} {pgid of top}\n");
		exit(1);
	}

	int pgidOfTop = atoi(argv[1]);
	printPidAndPgid();
	
	// 같은 세션이 아니면 에러 남. 같은 세션의 프로세스의 pgid를 이용해야함
	if(setpgid(0 , pgidOfTop) == -1){
		perror("setpgid error");
		exit(1);
	}	
	printf("---------------\n");

	printPidAndPgid();
	while(1){} // 무한루프
	return 0;
}

void printPidAndPgid(){
	printf("PID : %d\n", (int)getpid());
	printf("PGID : %d\n", (int)getpgid(getpid()));
}
