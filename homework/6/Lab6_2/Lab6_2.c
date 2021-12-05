#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

void printPid(int, int);

int main(){
    pid_t pid1 = fork();
    pid_t pid2 = fork();

    if(pid1 == 0 && pid2 != 0){
        //자식 프로세스 1
        sleep(1);
        printf("First Child Process\n");
        printPid((int)getpid(), (int)getppid());
    }
    if(pid2 == 0 && pid1 != 0){
        //자식 프로세스 2
        printf("Second Child Process\n");
        printPid((int)getpid(), (int)getppid());
    }
    if(pid1 != 0 && pid2 != 0){
        //부모 프로세스i
        sleep(2);
        printf("My Child's PID: %d %d\n", (int)pid1, (int)pid2);
        printPid((int)getpid(), (int)getppid());
    }
    return 0;
}

void printPid(int pid, int ppid){
    printf("MyPid : %d\n", pid);
    printf("MyParent's pid : %d\n\n", ppid);
}
