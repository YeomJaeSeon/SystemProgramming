#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

int main(void){
	pid_t pid;

	switch(pid = fork()){
		case -1:
			perror("fork");
			exit(1);
			break;
		
		case 0:
			printf("Child process - MY PID : %d, My Parent's PID: %d\n",
					(int)getpid(), (int)getppid());
			break;
		default:
			printf("Parent process - My pid : %d, My Parent's PID: %d, "
					"MyChild'sPID: %d\n", (int)getpid(), (int)getppid(), (int)pid);
			break;
	}

	printf("End of fork\n");

	return 0;
}
