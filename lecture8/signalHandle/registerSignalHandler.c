#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler(int signo){
    printf("Caught SIGINT!\n");
    psignal(signo, "Received signal");
}

int main(void){
    //SIGINT signal이 발생하면 default로 프로세스는 terminate됐지만
    // signal handler를 등록해줌으로써, termiate되지가 않고, 내가 등록한 핸들러가 실행이된다.
    // ctrl z 로 해당 프로세스 백그라운드 실행 ->  kill -9 signal 호출하여 프로세스 끝내자
    if(signal(SIGINT, sigint_handler) == SIG_ERR){
        fprintf(stderr, "Cannot handle SIGINT!\n");
        exit(EXIT_FAILURE);
    }

    for(;;) pause();
    return 0;
}
