#include "siglist.h"
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handler_SIG(int _signo){
    printf("Received signal : %s\n", strsignal(_signo));
}

int main(void){
    sigset_t set;

    printf("Do Not Disturb mode on!\n");

    sigfillset(&set);
    sigdelset(&set, SIGKILL);
    sigdelset(&set, SIGSTOP);
    for (size_t i = 0; i < SIGLIST_LENGTH; i++){
        if(sigismember(&set, siglist[i].code))
            signal(siglist[i].code, handler_SIG);
    }


    sigprocmask(SIG_BLOCK, &set, (sigset_t *)NULL);
    
    sleep(20);
    printf("Do Not Disturb mode off!\n");
    sigprocmask(SIG_UNBLOCK, &set, (sigset_t *)NULL);
    
    return 0;
}
