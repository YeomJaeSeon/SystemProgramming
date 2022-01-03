#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char* argv[]){
    if(argc != 3){
        printf("input error, example : {exefile} {.dat} {.txt}");
        exit(1);
    }

    char* datFile = argv[1];
    char* txtFile = argv[2];
    int txtFd, datFd;
    caddr_t txtAddr, datAddr;

    if( (txtFd = open(txtFile, O_RDONLY)) == -1 ){
        perror("open");
        exit(1);
    }
    if( (datFd = open(datFile, O_RDWR)) == -1 ){
        perror("open");
        exit(1);
    }

    txtAddr = mmap(NULL, getpagesize(), PROT_READ, MAP_SHARED, txtFd, (off_t)0);
    datAddr = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, datFd, (off_t)0);

    close(txtFd);
    close(datFd);
    int length = 0;
    while(1){
        if(txtAddr[length++] == '\0') break;
    }
    
    printf("txt length : %d\n", length);
    
   int i = 0;
    int j = 0;
    int pid = 0;
    char* parentStr;
    switch( pid = fork() ){
        case -1:
            perror("fork");
            exit(1);
            break;
        case 0:
            //자식
            while(1){
                if(txtAddr[i] == '\0') break;
                datAddr[i] = txtAddr[i];
                i++;
                sleep(1);
            }
            break;
        default:
            while(1){
                printf("도르마무 mapping을 하러 왔다.\n");
                printf("%s\n", datAddr);
                sleep(1);
                int isSame = 0;
                for(j =0; j < length; j++){
                    if(datAddr[j] != txtAddr[j]){
                        isSame = -1;
                        break;
                    }
                }
                if(isSame == 0) break;
                
            }
            printf("발동!\n");
            printf("도르마무를 물리쳤다!\n");
            break;
    }


    return 0;



}
