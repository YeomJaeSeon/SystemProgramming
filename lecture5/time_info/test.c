#include <stdio.h>

struct STUDENT{
	char* name;
	int grade;
};

int main(void){
	struct STUDENT student;

	student.name = "염재선";
	student.grade = 100;

	printf("%s %d\n", student.name, student.grade);
	printf("%d\n", &student.name);
	printf("%d\n", &student.grade);
	
	printf("%d\n", student);
	printf("주소 : %d\n", &student);
	
	int b = 10;
	int *a = &b;

	printf("==========\n");

	printf("%d\n", a);
	printf("%d\n", &b);
	
	printf("%d\n", a->b);
	return 0;
}
