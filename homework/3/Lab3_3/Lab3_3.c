#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

#define ASCII 48

struct Split_Input{
	char *first;
	char *second;
};

int str2int(char* );
struct Split_Input mysplit(char*, char);
int strLength(char* );
char* reverseStr(char* );
char* makeStr(int );

//main
int main(int argc, char* argv[]){
	if(argc != 4){
		printf("input example : (execute file) (origin data file) (sampling step) (output file\n");
		exit(1);
	}
	
	char* targetDir = argv[1];
	char* step = argv[2];
	char* outputDir = argv[3];
	
	int sampling = str2int(step);
	
	DIR *dp;
	struct Split_Input s = mysplit(targetDir, '/');
	
	//s.first : prefix
	//s.second : input dir absolute path


	if( (dp = opendir(s.second)) == NULL){
		perror("opendir");
		exit(1);
	}

	struct dirent *dent;
	outputDir = strcat(s.second, outputDir);
	if( (mkdir(outputDir, 0755)) == -1){
		perror("mkdir");
		exit(1);
	}
      	char *onlyPrefixFile = strcat(outputDir, s.first);
	int start = 1;
	while( (dent = readdir(dp)) ){
		printf("gigigi\n");
		struct stat buf;
		char* fileName;
                fileName = dent->d_name;

		stat(fileName, &buf);
		printf("1: %s\n", fileName);
		if((strcmp(fileName, ".") == 0) || (strcmp(fileName, "..") == 0)) continue;
		printf("2: %s\n", fileName);
		
		//prefix까지 더함
		char *startChr = makeStr(start);
		printf("startChr : %s\n", startChr);
		
		start += sampling; // sampling 더하기
	}
	
	free(s.first);
	free(s.second);
	closedir(dp);
	
	return 0;
}

char* makeStr(int num){
	char* str = malloc (sizeof(char) * 3);
	str[0] = '0';
	str[1] = '0';
	str[2] = '0';

	int i = 2;
	while(num > 0){
		int v = num %= 10;
		char vch = (char)(v + ASCII);
		str[i--] = vch;
		num /= 10;
	}

	return str;
}
int strLength(char* str){
	int length = 0;
	int i = 0;
	while(str[i] != '\0'){
		length++;
		i++;
	}
	return length;
}

int str2int(char* step){
	int length = strLength(step);
	int sum = 0;
	
	int v = 1;
	for(int i = length - 1; i >= 0; i--){
		int char2int = (int)step[i] - ASCII;
		sum += v * char2int;
		v *= 10;
	}

	return sum;
}
struct Split_Input mysplit(char* str, char delix){
	int length = strLength(str);

	char first[100];
	int fi = 0;
	char second[100];
	int si = 0;
	int v = -1;
	for(int i = length - 1; i >= 0; i--){
		if(v == -1 && str[i] == delix){
			v = 1;
		}

		if(v == -1){
			first[fi++] = str[i];
		}else{
			second[si++] = str[i];
		}
	}
	first[fi] = '\0';
	second[si] = '\0';

	char* firstResult = reverseStr(first);
	char* secondResult = reverseStr(second);

	struct Split_Input s;
	s.first = firstResult;
	s.second = secondResult;
	
	return (s);
}

char* reverseStr(char* str){
	int length = strLength(str);
	char* reverse;
	reverse = malloc (sizeof (char) * length);

	for(int i = 0; i < length; i++){
		reverse[i] = str[length - 1 - i];
	}
	return reverse;
}
