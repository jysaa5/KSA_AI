#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>

struct studentList
{
	char leader[10];
	char company[20];
	char name[20];
	char email[20];
	char school[30];
	char major[60];

};

void searchingLeader(struct studentList *student_list, int list_size, time_t t);
void searchingCompany(struct studentList *student_list, int list_size, char input, time_t t);
void searchingName(struct studentList *student_list, int list_size, char input, time_t t);
void searchingEmail(struct studentList *student_list, int list_size, char input, time_t t);
void searchingSchool(struct studentList *student_list, int list_size, char input, time_t t);
void searchingMajor(struct studentList *student_list, int list_size, char input, time_t t);
int menu();


int main() {

	struct studentList student_list[] = {
		{"1", "a1", "a2", "a3", "a4", "a5"},
		{"1", "b1", "b2", "b3", "b4", "b5"},
		{"0", "a6", "a7", "a8", "a9", "a10"}
	};

	int select_num = 0;
	char input[60];
	int list_size = 2;
	time_t t;

	while (1) {

		select_num = menu();

		switch (select_num) {

		case 0:

			select_num = menu();
			break;

		case 1:
			t = time(NULL);
			searchingLeader(student_list, list_size, t);
			break;

		case 2:

			printf("검색하고자 하는 회사명을 입력해주세요.\n");
			scanf("%c", input);
			t = time(NULL);
			searchingCompany(student_list, list_size, input, t);
			break;

		case 3:
			
			printf("검색하고자 하는 이름을 입력해주세요.\n");
			scanf("%c", input);
			t = time(NULL);
			searchingName(student_list, list_size, input, t);
			break;

		case 4:

			printf("검색하고자 하는 E-mail을 입력해주세요.\n");
			scanf("%c", input);
			t = time(NULL);
			searchingEmail(student_list, list_size, input, t);
			break;

		case 5:

			printf("검색하고자 하는 학교를 입력해주세요.\n");
			scanf("%c", input);
			t = time(NULL);
			searchingSchool(student_list, list_size, input, t);
			break;
		
		case 6:

			printf("검색하고자 하는 전공을 입력해주세요.\n");
			scanf("%c", input);
			t = time(NULL);
			searchingMajor(student_list, list_size, input, t);
			break;


		default:

			select_num = menu();
			break;
		}
	}
	return 0;
}

int menu()
{
	int num = 0;
	printf("원하시는 메뉴를 선택해주세요\n");
	printf("1. 조장 검색\n");
	printf("2. 회사명 검색\n");
	printf("3. 이름 검색\n");
	printf("4. Email 검색\n");
	printf("5. 학교 검색\n");
	printf("6. 전공 검색\n");
	scanf("%d", &num);

	return num;
}

void searchingLeader(struct studentList *student_list, int list_size, time_t t) {

	int count = 0;

	for (int i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].leader, "1") == 0) {
			count++;
		}
	}

	struct studentList *result_list = (struct studentList*) malloc(sizeof(struct studentList) * count);
	
	for (int i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].leader, "1") == 0) {

			strcpy(result_list[i].leader, student_list[i].leader);
			strcpy(result_list[i].company, student_list[i].company);
			strcpy(result_list[i].name, student_list[i].name);
			strcpy(result_list[i].email, student_list[i].email);
			strcpy(result_list[i].school, student_list[i].school);
			strcpy(result_list[i].major, student_list[i].major);

		}
	}
	free(result_list);
}

void searchingCompany(struct studentList *student_list, int list_size, char input, time_t t) {

	int count = 0;

	for (int i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].company, input) == 0) {
			count++;
		}
	}

	struct studentList* result_list = (struct studentList*) malloc(sizeof(struct studentList) * count);

	for (int i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].company, input) == 0) {

			strcpy(result_list[i].leader, student_list[i].leader);
			strcpy(result_list[i].company, student_list[i].company);
			strcpy(result_list[i].name, student_list[i].name);
			strcpy(result_list[i].email, student_list[i].email);
			strcpy(result_list[i].school, student_list[i].school);
			strcpy(result_list[i].major, student_list[i].major);

		}
	}
	free(result_list);
}

void searchingName(struct studentList *student_list, int list_size, char input, time_t t) {

	int count = 0;

	for (int i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].name, input) == 0) {
			count++;
		}
	}

	struct studentList* result_list = (struct studentList*) malloc(sizeof(struct studentList) * count);

	for (int i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].name, input) == 0) {

			strcpy(result_list[i].leader, student_list[i].leader);
			strcpy(result_list[i].company, student_list[i].company);
			strcpy(result_list[i].name, student_list[i].name);
			strcpy(result_list[i].email, student_list[i].email);
			strcpy(result_list[i].school, student_list[i].school);
			strcpy(result_list[i].major, student_list[i].major);

		}
	}
	free(result_list);
}

void searchingEmail(struct studentList *student_list, int list_size, char input, time_t t) {

	int count = 0;

	for (int i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].email, input) == 0) {
			count++;
		}
	}

	struct studentList* result_list = (struct studentList*) malloc(sizeof(struct studentList) * count);

	for (int i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].email, input) == 0) {

			strcpy(result_list[i].leader, student_list[i].leader);
			strcpy(result_list[i].company, student_list[i].company);
			strcpy(result_list[i].name, student_list[i].name);
			strcpy(result_list[i].email, student_list[i].email);
			strcpy(result_list[i].school, student_list[i].school);
			strcpy(result_list[i].major, student_list[i].major);

		}
	}
	free(result_list);
}

void searchingSchool(struct studentList *student_list, int list_size, char input, time_t t) {

	int count = 0;

	for (int i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].school, input) == 0) {
			count++;
		}
	}

	struct studentList* result_list = (struct studentList*) malloc(sizeof(struct studentList) * count);

	for (int i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].school, input) == 0) {

			strcpy(result_list[i].leader, student_list[i].leader);
			strcpy(result_list[i].company, student_list[i].company);
			strcpy(result_list[i].name, student_list[i].name);
			strcpy(result_list[i].email, student_list[i].email);
			strcpy(result_list[i].school, student_list[i].school);
			strcpy(result_list[i].major, student_list[i].major);

		}
	}
	free(result_list);
}

void searchingMajor(struct studentList *student_list, int list_size, char input, time_t t) {

	int count = 0;

	for (int i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].major, input) == 0) {
			count++;
		}
	}

	struct studentList* result_list = (struct studentList*) malloc(sizeof(struct studentList) * count);

	for (int i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].major, input) == 0) {

			strcpy(result_list[i].leader, student_list[i].leader);
			strcpy(result_list[i].company, student_list[i].company);
			strcpy(result_list[i].name, student_list[i].name);
			strcpy(result_list[i].email, student_list[i].email);
			strcpy(result_list[i].school, student_list[i].school);
			strcpy(result_list[i].major, student_list[i].major);

		}
	}
	free(result_list);
}
