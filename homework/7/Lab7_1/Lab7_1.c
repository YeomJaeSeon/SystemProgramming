#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int stopTime;
int currentTime = 0;

void alarm_handler();
void sigint_tstp_handler();
int main(int argc, char* argv[]){
    if(argc != 2){
        printf("input error : {executeFile} {stop time(seconds)}");
        exit(1);
    }
    //string -> int
    stopTime = atoi(argv[1]);
    
    //시그널 핸들러 등록
    signal(SIGALRM, alarm_handler);
    signal(SIGINT, sigint_tstp_handler);
    signal(SIGTSTP, sigint_tstp_handler);

    //알람 이벤트
    alarm(1);

    while(1){}

    return 0;
}
// SIGTSTP 핸들러
void sigint_tstp_handler(){
    printf("아직 움질일수 없습니다!\n");
}

// SIGINT SIGTSTP 디폴트 핸들러로 복구
void restoreSignalHandler(){
    signal(SIGINT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
}

// SIGALRM 핸들러
void alarm_handler(){
    printf("%d초 경과\n", ++currentTime);
    if(currentTime == stopTime){
        printf("시간정지 종료\n");
        printf("내가 시간을 %d초나 멈췄다!\n", currentTime);
        restoreSignalHandler();
        printf("이젠 CTRI-C, CTRI-Z가 활성화됨!\n");
    }else{
        alarm(1);
    }
}
