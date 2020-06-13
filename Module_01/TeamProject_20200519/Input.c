#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>

struct studentList
{
	int leader;
	char company[20];
	char name[20];
	char email[20];
	char school[30];
	char major[60];

};


int main() {
	time_t t = time(NULL);
	printf("Time :%s\n", ctime(&t));
}