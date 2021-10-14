#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	if(argc > 4){
		perror("argv");
		exit(1);
	}

	char* abin = argv[1];
	char* bbin = argv[2];
	char* outputFile = argv[3];

	FILE *fp;

	fp = fopen(abin, "rb");
	if(fp == NULL){
		perror("fopen abin");
		exit(1);
	}
	
	FILE *fp2;
	fp2 = fopen(bbin, "rb");
	if(fp2 == NULL){
		perror("fopen bbin");
		exit(1);
	}

	FILE *fp3;
	fp3 = fopen(outputFile, "wb");
	if(fp3 == NULL){
		perror("fopen wb");
		exit(1);
	}

	size_t n1, n2;
	char arr1[1] = {0};
	char arr2[1] = {0};

	while(1){
		int isFpFinish = 1;
		int isFp2Finish = 1;

		n1 = fread(arr1, sizeof(char), 1, fp); //abin으로 부터 읽음

		if(n1 == 0) isFpFinish = -1;
		else{
			if(arr1[0] >= 0 && arr1[0] <= 9){
				//숫자면
				fseek(fp2, arr1[0], SEEK_CUR);
			}else{
				//문자면
				fwrite(arr1, sizeof(char), 1, fp3);
			}
		}

		n2 = fread(arr2, sizeof(char), 1, fp2);
		
		if(n2 == 0) isFp2Finish = -1;
		else{
			if(arr2[0] >= 0 && arr2[0] <= 9){
				//숫자면
				fseek(fp, arr2[0], SEEK_CUR);
			}else{
				//문자면
				fwrite(arr2, sizeof(char), 1, fp3);
			}
			
		}
		if(isFpFinish == -1 && isFp2Finish == -1) break; 
	}

	fclose(fp);
	fclose(fp2);
	fclose(fp3);

	return 0;
}

