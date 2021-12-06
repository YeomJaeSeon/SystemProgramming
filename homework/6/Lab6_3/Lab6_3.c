#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int countPrimeNumber(int, int);
void printCurrentTime();

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("input error, example : <execute file> <range number>\n");
        exit(1);
    }
    int range = atoi(argv[1]);

    printf("[Serial start]");
    printCurrentTime();

    printf("[Serial]");
    printf("found %d primes\n", countPrimeNumber(0, range));
    printf("[Serial End]");
    printCurrentTime();

    int half = range / 2;
    pid_t pid = fork();
    printf("[Parallel start]");
    printCurrentTime();
    if(pid == 0){
        //자식
        printf("[pid = %d]", (int)pid);
        printf("found %d prime numbers between(1 ~ %d)\n", countPrimeNumber(0, half), half);
        printf("[Proc.0 end]");
        printCurrentTime();
    }else{
        //부모
        printf("[pid = %d]", (int)pid);
        printf("found %d prime numbers between(%d ~ %d)\n", countPrimeNumber(half + 1, range), half + 1, range);
        printf("[Proc.%d end]", (int)pid);
        printCurrentTime();
    }


    return 0;
}

int countPrimeNumber(int start, int range){
    int count = 0;
    for(int i = (start > 2 ) ? start : 2; i <= range; i++){
        int isPrime = 0; // 0 : prime, -1 : prime아님
        for(int j = 2; j < i; j++){
            if(i % j == 0){
                isPrime = -1;
                break;
            }
        }
        if(isPrime == 0) count++;
    }
    return count;   
}

void printCurrentTime(){
    struct tm *tm;
    time_t t;
    time(&t);
    tm = localtime(&t);
    char week[7][3 + 1] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    char month[12][3 + 1] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    printf("%s %s %d %d:%d:%d %d\n", week[tm->tm_wday], month[tm->tm_mon], tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, tm->tm_year + 1900);
}
