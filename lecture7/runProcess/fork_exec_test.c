#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
// fork만 하면 부모 프로세스의 메모리를 복제해서 같은 일을함.
// 자식 프로세스를 다른 일을 시키고 싶다면?
// A ->(fork : 독립적으로 실행) Parent
//   ->(fork: 독립적으로 실행) Child -> exec를 이용해서 다른 프로세스로 해당 메모리를 덮어버리자.

int main(void){
	pid_t pid;

	switch(pid = fork()){
		case -1:
			perror("fork");
			exit(1);
			break;
		case 0:
			printf("--> Child Process\n");
			if(execlp("ls", "ls", "-a", (char *)NULL) == -1){
				perror("execlp");
				exit(1);
			}
			exit(0);
			break;
		default:
			printf("--> Parent process - My PID: %d\n", (int)getpid());
			break;
	}

	return 0;
}
