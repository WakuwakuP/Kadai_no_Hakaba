/* ごみみたいな処理のプログラム */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    char  name[100];
    char  number[100];
    int  year;
    int  month;
    int  day;
};

void set_student(struct student *person,char *name,char *number,int year,int month,int day);
void print_student(struct student *person);

int main(){
	struct student *studentA, *studentB, *studentC;

	studentA = (struct student *)malloc(sizeof(struct student));
	if(studentA == NULL)exit(1);
	studentB = (struct student *)malloc(sizeof(struct student));
	if(studentB == NULL)exit(1);
	studentC = (struct student *)malloc(sizeof(struct student));
	if(studentC == NULL)exit(1);

	set_student(studentA, "Handai Taro", "81234567", 85, 1, 1);
	set_student(studentB, "Handai Hanako", "87654321", 1985, 8, 3 );
	set_student(studentC, "Kougaku Ouri", "88888888", 1975, 1, 1 );

	print_student(studentA);
	print_student(studentB);
	print_student(studentC);

	return 0;
}

void set_student(struct student *person, char *name, char *number, int year, int month, int day){
	strcpy(person->name, name);
	strcpy(person->number, number);
	person->year = year;
	person->month = month;
	person->day = day;
}

void print_student(struct student *person){
	printf("Name  :%s\n", person->name);
	printf("Number:%s\n", person->number);
	printf("Birth:%04d/%02d/%02d\n\n", person->year, person->month, person->day);
}