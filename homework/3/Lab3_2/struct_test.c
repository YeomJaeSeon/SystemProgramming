#include <stdio.h>

#define CLASSCNT 3

struct Grade{
	char* class;
	int score;
};

struct student{
	char *name;
	int age;
	struct Grade grade[CLASSCNT];
};

int main(void){
	struct student s1;
	struct Grade grade[CLASSCNT];

	grade[0].class = "수학";
	grade[0].score = 100;
	
	grade[1].class = "물리";
	grade[1].score = 99;

	grade[2].class = "역사";
	grade[2].score = 50;

	s1.name = "염재선";
	s1.age = 26;

	for(int i = 0; i < CLASSCNT; i++){
		s1.grade[i] = grade[i];
	}

	printf("이름 : %s\n", s1.name);
	printf("나이 : %d\n", s1.age);
	for(int i = 0; i < CLASSCNT; i++){
		printf("과목 : %s\n", s1.grade[i].class);
		printf("과목 점수 : %d\n", s1.grade[i].score);
	}
	return 0;
}
