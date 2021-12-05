#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	if(argc != 3){
		printf("input error, example : <execute file> <cfile> <outfile>\n");
		exit(1);
	}

	char* cfile = argv[1];
	char* exefile = argv[2];

	if(execlp("gcc", "gcc", "-o", exefile, cfile, (char *)NULL) == -1){
        perror("execvp");
        exit(1);
    }

    
    return 0;
}

