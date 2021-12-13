#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// 0 : 형, 1 : 아우
int order = 1;

void printMsg();
void givenFinish();

int main(void){
    printf("형님 먼저\n");
    // SIGINT 시그널 핸들러 등록
    signal(SIGINT, printMsg);
    // SIGTSTP 시그널 핸들러 등록
    signal(SIGTSTP, givenFinish);
    while(1){}
    return 0;
}
void givenFinish(){
    if(order == 0){
        printf("알았어 형님\n");
    }else if(order == 1){
        printf("알았어 아우\n");
    }
    exit(0);
}
void printMsg(){
    order = order == 0 ? 1 : 0;
    if(order == 0){
        printf("아우 먼저\n");    
    }else if(order == 1){
        printf("형님 먼저\n");
    }
}
