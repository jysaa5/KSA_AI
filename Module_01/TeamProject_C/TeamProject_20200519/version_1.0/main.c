#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "studentP.h"

#define MAX 1024

void main(void)
{
	//input data
	int k = 0;
	int list_size = 0;
	// ����ü ����Ʈ ���� -> ���� �Ҵ��� ��� �ؾ� ����? 
	struct studentList student_list[100] = { NULL };

	// ���� �б�� ����ü�� ����
	for (k = 0; k < 100; k++) {
		student_list[k] = fileReading()[k];
	}

	//fileList->leader = inputData()
	for (k = 0; k < 25; k++) {
		printf("%s", student_list[k].leader);
		printf("%s", student_list[k].company);
		printf("%s", student_list[k].name);
		printf("%s", student_list[k].email);
		printf("%s", student_list[k].school);
		printf("%s", student_list[k].major);
		printf("\n");
	}

	k = 0;
	
	while (strcmp(student_list[k].leader, "") != 0) {
		k++;
		list_size++;
	}
	

	printf("%d\n", sizeof(student_list) / sizeof(student_list)[0]);
	//printf("%d\n", list_length);




	//search
	int select_num = 0;
	char input[60];
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

			printf("�˻��ϰ��� �ϴ� ȸ����� �Է����ּ���.\n");
			scanf("%s", &input);
			t = time(NULL);
			searchingCompany(student_list, list_size, input, t);
			break;

		case 3:

			printf("�˻��ϰ��� �ϴ� �̸��� �Է����ּ���.\n");
			scanf("%s", &input);
			t = time(NULL);
			searchingName(student_list, list_size, input, t);
			break;

		case 4:

			printf("�˻��ϰ��� �ϴ� E-mail�� �Է����ּ���.\n");
			scanf("%s", &input);
			t = time(NULL);
			searchingEmail(student_list, list_size, input, t);
			break;

		case 5:

			printf("�˻��ϰ��� �ϴ� �б��� �Է����ּ���.\n");
			scanf("%s", &input);
			t = time(NULL);
			searchingSchool(student_list, list_size, input, t);
			break;

		case 6:

			printf("�˻��ϰ��� �ϴ� ������ �Է����ּ���.\n");
			scanf("%s", &input);
			t = time(NULL);
			searchingMajor(student_list, list_size, input, t);
			break;


		default:

			select_num = menu();
			break;
		}
	}
	return 0;
	

	return 0;
}