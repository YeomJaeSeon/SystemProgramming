/**
 * Serial process 소수찾기 vs Parellel process 소수찾기
 *
 * 소수 찾아서, 하나의 파일에 출력하기
 *
 *
 * 풀이
 * 1. 입력된 processCnt - 1개의 자식 프로세스를 생성한다 (fork를 통해서 - 독립적으로 실행)
 * 2. 각각 범위를 나눠받아 소수를 찾고 .mid인 임시 파일에 찾은 소수를 출력한다.
 * 3. 마지막엔 outputFile에 순서대로 출력한다. (끝!)
 *
 * 병렬 프로그램이지만 결국 하나의 파일에 저장되야한다. 그런데 소스코드는 프로세스들끼리 독립적으로 실행되기에 임시 파일에 찾은 소수를 출력하는 것이 포인트이다
 * 그리고 걸린 시간을 측정하기 위해, waitpid를 통해 자식 프로세스가 모두 끝났는지 확인하는 로직이 필요하다. 즉 부모프로세스와 자식프로세스들 간에 동기화가 필요하다.
**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>

struct Number{
    int start;
    int end;
};

// 소수 찾는 함수
int countPrimes(int start, int end, FILE *fp){
    int count = 0;
    for(int i = (start > 2 ) ? start : 2; i <= end; i++){
        int isPrime = 0; // 0 : prime, -1 : prime아님
        for(int j = 2; j < i; j++){
            if(i % j == 0){
                isPrime = -1;
                break;
            }
        }
        if(isPrime == 0) {
            char text[100];
            sprintf(text, "%d ", i);
            fputs(text, fp);
            
            count++;
        }
    }
    return count;   
}
// 자식 프로세스들이 모두 끝났는지 확인하는 함수
int isNotFinished(pid_t * pids, int processCnt){
    int status;
    for(int i = 1; i < processCnt; i++){
        // pids에 저장된 pid를 가진 자식프로세스들이 끝났는지 확인하는 메서드
        if(waitpid(pids[i], &status, WNOHANG) == 0){
            //안끝나면 -1 리턴
            return -1;
        }
    }
    //다 끝나면 0 리턴   
    return 0;
}

int main(int argc, char* argv[]){
    if(argc != 5){
        printf("input err, example : <executeFile> <start num> <end num> <processCnt> <outputFile>");
        exit(1);
    }
    
    int start = atoi(argv[1]);
    int end = atoi(argv[2]);
    int processCnt = atoi(argv[3]);
    char* outputFile = argv[4];

    FILE *tmpFp[processCnt]; // 중간 파일
    FILE *wfp; // 최종 파일
    
    char c;

    // file open
    if( (wfp = fopen(outputFile, "w+")) == NULL){
        perror("fopen");
        exit(1);
    }

    // file open
    for(int i = 0; i < processCnt; i++){
        char text[100];
        sprintf(text, "%d.mid", i);
        if( (tmpFp[i] = fopen(text, "w+")) == NULL ){
            perror("fopen");
            exit(1);
        }
    }

    struct timeval startTime, endTime, gapTime; //시작시간, 끝나는 시간, 시간 차이
    gettimeofday(&startTime, NULL);

    // 동적 할당
    pid_t* pids = (pid_t *)malloc(sizeof(pid_t) * (processCnt - 1));
    struct Number* numbers = malloc(sizeof(struct Number) * (processCnt));
    for(int i = 0; i < processCnt - 1; i++){
        pids[i] = fork();
    }

    int chunkSize = (end - start) / processCnt;
    
    for(int i = 0; i < processCnt; i++){
        numbers[i].start = start;
        
        numbers[i].end = start + chunkSize > end ? end : start + chunkSize;
        start = start + chunkSize + 1;
    }
    
    int isParent = 0;
    for(int i = 0; i < processCnt - 1; i++){
        if(pids[i] == 0){
            isParent = -1;
            break;
        }
    }
    if(isParent == 0){
        //부모 프로세스
        printf("[P0]");
        printf("found %d primes\n", countPrimes(numbers[0].start, numbers[0].end, tmpFp[0]));
        if(processCnt == 1){
            rewind(tmpFp[0]);
            while( (c = fgetc(tmpFp[0])) != EOF){
                fputc(c, wfp);
            }

            gettimeofday(&endTime, NULL);

            float sec = (endTime.tv_sec - startTime.tv_sec) * 1000;
            float usec = (endTime.tv_usec - startTime.tv_usec) / 1000.0;

            printf("[Serial] %.2f ms\n", (sec + usec));
            
        }else{
            while(isNotFinished(pids, processCnt) == -1) continue;          
 

            for(int i = 0; i < processCnt; i++){
                rewind(tmpFp[i]);
                while( (c = fgetc(tmpFp[i])) != EOF ){
                 fputc(c, wfp);
              }
            }

            gettimeofday(&endTime, NULL);

            float sec = (endTime.tv_sec - startTime.tv_sec) * 1000;
            float usec = (endTime.tv_usec - startTime.tv_usec) / 1000.0;

            printf("[Parellel] %.2f ms\n", (sec + usec));
                       
        }
    }

    for(int i = 0; i < processCnt - 1; i++){
        //자식
        if(pids[i] == 0){
           int isAllNotZero = 0;
            for(int j = 0; j < processCnt - 1; j++){
                if(i == j) continue;
                if(pids[j] == 0){
                    isAllNotZero = -1;
                    break;
                }
            }
            if(isAllNotZero == 0){
                //자식 프로세스 하나
                printf("[P%d]", i + 1);
                printf("found %d primes\n", countPrimes(numbers[i + 1].start, numbers[i + 1].end, tmpFp[i + 1]));
            }
        }
    }

    for(int i = 0; i < processCnt; i++){
        fclose(tmpFp[i]);
    }
    fclose(wfp);

    free(numbers);
    free(pids);
    
    return 0;
}
