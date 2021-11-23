#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
        if(argc != 3){
                printf("input example : {executeFile} {studentId} {outputFileName}");
        }

        char* studentId = argv[1];
        char* dbFile = "/Users/professor/grade.db";
        char* outputFile = argv[2];
	
	printf("studentId : %s\n", studentId);
	printf("outputfilie : %s\n", outputFile);	

        uid_t uid, euid; //ruid, euid
	uid_t temp;
        FILE* rfp, * wfp;

        uid = getuid(); // student uid
        euid = geteuid(); // professor uid
        printf("uid = %d, euid = %d\n", (int)uid, (int)euid);


        if((rfp = fopen(dbFile, "r")) == NULL){
                perror("fopenError");
                exit(1);
        }

	int studentNumber = 0;
	char grade[10];
	
        while(!feof(rfp)){
		fscanf(rfp, "%d %s", &studentNumber, grade);
		if(studentNumber == atoi(studentId)){
			printf("my grade = %s\n", grade);
			setuid(getuid());
			printf("uid = %d, euid = %d\n", getuid(), geteuid());
			if((wfp = fopen(outputFile, "w")) == NULL){
				perror("fopen : Write File");
				exit(1);
			}
			fprintf(wfp, "%s\n", grade);
			printf("Write the grade to %s\n", outputFile);
			fclose(wfp);
			break;
		}
	}
	fclose(rfp);
        return 0;
}
