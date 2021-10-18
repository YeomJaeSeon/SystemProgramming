#include <sys/time.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

char *format = "%m월 %d일 %a %l:%M %p";
char *array[] = {"GMT", "KST", "JST", "CST", "MST", "BRT", "CEST", "EAT", "AEST"};
struct TIMEZ{
	char* name;
	int diff;
};
int isSame(char*, char*);
int main(int argc, char* argv[]){
	if(argc != 2){
		printf("input error : (execute file) (timezone)");
		exit(1);		
	}

	char* targetZone = argv[1];
	char buf[256];
	struct tm *tm;
	time_t t;

	int isNotEqual = -1;
	for(int i = 0; i < 9; i++){
		if(isSame(targetZone, array[i]) == 0){
			isNotEqual = 0;
			break;
		}
	}

	if(isNotEqual == -1){
		printf("there are not input timezone");
		exit(1);
	}
	printf("is same!!\n");
	
	struct TIMEZ list[9];
	for(int i = 0; i < 9; i++){
		struct TIMEZ t;
		t.name = array[i];
		list[i] = t;
	}	
	list[0].diff = 0;
	list[1].diff = 9;
	list[2].diff = 9;
	list[3].diff = 8;
	list[4].diff = -7;
	list[5].diff = -3;
	list[6].diff = 2;
	list[7].diff = 3;
	list[8].diff = 10;
	
	int select = -1;
	for(int i = 0; i < 9; i++){
		if(isSame(list[i].name, targetZone) == 0){
			select = i;
			break;
		}
	}


	time(&t);
	t += (3600 * 9);
	tm = gmtime(&t);
	strftime(buf, sizeof(buf), format, tm);
	
	printf("%s [%s]\n", "KST", buf);
	
	time(&t);
	t += (3600 * list[select].diff);
	tm = gmtime(&t);
	//buf reinitialize
	for(int i = 0; i < 256; i++){
		buf[i] = ' ';
	}

	strftime(buf, sizeof(buf), format, tm);
	printf("%s [%s]\n", targetZone, buf);
	
	return 0;

}
int getLength(char *a){
	int i = 0;
	while(a[i] != '\0'){
		i++;
	}

	return i;
}

int isSame(char* a, char* b){
	int alength = getLength(a);
	int blength = getLength(b);

	if(alength != blength) return -1;

	for(int i = 0; i < alength; i++){
		if(a[i] != b[i]) return -1;
	}

	return 0;
}
