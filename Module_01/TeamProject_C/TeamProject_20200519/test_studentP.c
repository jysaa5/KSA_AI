#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>  
#include "studentP.h"
#define MAX 1024


int menu()
{
	int num = 0;
	printf("���Ͻô� �޴��� �������ּ���\n");
	printf("1. ���� �˻�\n");
	printf("2. ȸ��� �˻�\n");
	printf("3. �̸� �˻�\n");
	printf("4. Email �˻�\n");
	printf("5. �б� �˻�\n");
	printf("6. ���� �˻�\n");
	scanf("%d", &num);

	return num;
}


// �Լ� ����
// fileReading �Լ�: ������ �д� �Լ�
struct studentList* fileReading(void) {

	// ���� ������ 
	FILE* fp;

	int index = 0, data = 0;

	// ���� ������ ������
	char* inp;

	// ���� ������
	int buf_size = MAX * MAX;

	// ������
	char* ptr;

	// ���ڿ��� �� �迭 ������
	char* arry[MAX];

	struct studentList new_list = { NULL };

	struct studentList stack_list[100] = { NULL };

	int i = 0;

	// ���� ����
	//fp = fopen("C:\\result\\studentListData.csv", "r");
	fp = fopen("C:\\result\\����� ������ ���_�ѱ�ǥ����ȸ.csv", "r");

	// ũ�� ���� �Ҵ�
	inp = malloc(buf_size);


	// fgets: ���ڿ� �Է�
	while (fgets(inp, buf_size, fp)) {

		// �Լ��� arry �迭�� �ּҿ� �Է¹��� ��Ʈ���� ����.
		new_list = retToken(arry, inp);
		stack_list[i] = new_list;
		i++;
	}

	
	fclose(fp);

	return stack_list;

}

// retToken �Լ�: ��ū�� �������� ������ ����
struct studentList retToken(char* arry[], char* inp) {

	int i = 0;

	// strtok()�� �̿��Ͽ� ���ڿ��� ';' ��ū�� �������� �ڸ�
	// char* ptr = strtok(inp, ";");
	char* ptr = strtok(inp, "??,\n");

	char* line[MAX];
	line[0] = NULL;

	while (ptr != NULL) {

		arry[i] = ptr;
		if (i == 0 && (strcmp(ptr, "����") != 0) && strcmp(ptr, "���� ����") != 0) {
			line[0] = "����";
			line[i + 1] = ptr;
		}
		else if (i == 0 && strcmp(ptr, "����") == 0 || strcmp(ptr, "���� ����") == 0) {
			line[i] = ptr;
		}
		else if (strcmp(line[0], "����") == 0) {
			line[i + 1] = ptr;
		}
		else {
			line[i] = ptr;
		}

		ptr = strtok(NULL, "??,\n");

		i++;

	}

	return inputData(line);
}

// inputData �Լ�: ����ü�� ������ ����
struct studentList inputData(char* line[]) {

	struct studentList new_list = { NULL };


	int j = 0;
	char* test[MAX];
	for (j = 0; j < 6; j++) {
		test[j] = line[j];

	}

	strcpy(new_list.leader, test[0]);
	strcpy(new_list.company, test[1]);
	strcpy(new_list.name, test[2]);
	strcpy(new_list.email, test[3]);
	strcpy(new_list.school, test[4]);
	strcpy(new_list.major, test[5]);

	/* strcpy(stack_list[j].leader, new_list.leader);
	 strcpy(stack_list[j].company, new_list.company);
	 strcpy(stack_list[j].name, new_list.name);
	 strcpy(stack_list[j].email, new_list.email);
	 strcpy(stack_list[j].school, new_list.school);
	 strcpy(stack_list[j].major, new_list.major);

	 j++;

	 if (j > 25) {

		 return *stack_list;

	 }
	 */
	return new_list;
}






void searchingLeader(struct studentList* student_list, int list_size, time_t t) {

	int count = 0;
	int i = 0;
	struct studentList data_list[100] = { NULL };

	while (i < list_size) {

		data_list[i] = (student_list)[i];
		i++;
	}

	for (int i = 0; i < list_size; i++) {

		if (strcmp(data_list[i].leader, "����") == 0) {

			printf("%s %s %s %s %s %s\n", data_list[i].leader, data_list[i].company, data_list[i].name, data_list[i].email, data_list[i].school, data_list[i].major);
			count++;
		}
	}

	if (count == 0) {

		printf("����� �����ϴ�.\n");
	}


	//���� ���
	logFileWriting(data_list, t, count);
}

void searchingCompany(struct studentList* student_list, int list_size, char *input, time_t t) {

	int count = 0;
	int i = 0;
	struct studentList data_list[100] = { NULL };

	while (i < list_size) {

		data_list[i] = (student_list)[i];
		i++;
	}

	for (int i = 0; i < list_size; i++) {

		if (strcmp(data_list[i].company, input) == 0 ) {

			printf("%s %s %s %s %s %s\n", data_list[i].leader, data_list[i].company, data_list[i].name, data_list[i].email, data_list[i].school, data_list[i].major);
			count++;
		}
	}

	if (count == 0) {

		printf("����� �����ϴ�.\n");
	}
		
	//���� ���
	logFileWriting(data_list, t, count);
}

void searchingName(struct studentList* student_list, int list_size, char *input, time_t t) {

	int count = 0;
	int i = 0;
	struct studentList data_list[100] = { NULL };

	while (i < list_size) {

		data_list[i] = (student_list)[i];
		i++;
	}

	for (int i = 0; i < list_size; i++) {

		if (strcmp(data_list[i].name, input) == 0) {

			printf("%s %s %s %s %s %s\n", data_list[i].leader, data_list[i].company, data_list[i].name, data_list[i].email, data_list[i].school, data_list[i].major);
			count++;
		}
	}

	//���� ���
	logFileWriting(data_list, t, count);
}

void searchingEmail(struct studentList* student_list, int list_size, char *input, time_t t) {

	int count = 0;
	int i = 0;
	struct studentList data_list[100] = { NULL };

	while (i < list_size) {

		data_list[i] = (student_list)[i];
		i++;
	}

	for (int i = 0; i < list_size; i++) {

		if (strcmp(data_list[i].email, input) == 0) {

			printf("%s %s %s %s %s %s\n", data_list[i].leader, data_list[i].company, data_list[i].name, data_list[i].email, data_list[i].school, data_list[i].major);
			count++;
		}
	}

	//���� ���
	logFileWriting(data_list, t, count);
}

void searchingSchool(struct studentList* student_list, int list_size, char *input, time_t t) {

	int count = 0;
	int i = 0;
	struct studentList data_list[100] = { NULL };

	while (i < list_size) {

		data_list[i] = (student_list)[i];
		i++;
	}

	for (int i = 0; i < list_size; i++) {

		if (strcmp(data_list[i].school, input) == 0) {

			printf("%s %s %s %s %s %s\n", data_list[i].leader, data_list[i].company, data_list[i].name, data_list[i].email, data_list[i].school, data_list[i].major);
			count++;
		}
	}

	//���� ���
	logFileWriting(data_list, t, count);
}

void searchingMajor(struct studentList* student_list, int list_size, char *input, time_t t) {

	int count = 0;
	int i = 0;
	struct studentList data_list[100] = { NULL };

	while (i < list_size) {

		data_list[i] = (student_list)[i];
		i++;
	}

	for (int i = 0; i < list_size; i++) {

		if (strcmp(data_list[i].major, input) == 0) {

			printf("%s %s %s %s %s %s\n", data_list[i].leader, data_list[i].company, data_list[i].name, data_list[i].email, data_list[i].school, data_list[i].major);
			count++;
		}
	}

	//���� ���
	logFileWriting(data_list, t, count);
}



void logFileWriting(struct studentList *list, time_t time, int count)
{
	FILE* ofp;
	int i= 0;

	//����� ����
	ofp = fopen("C:\\result\\result.txt", "w");

	if (ofp == NULL)
	{
		printf("��� ������ ���� ���߽��ϴ�\n");
	}


	//�ֻ�� ��
	//fprintf(ofp, "%3s%7s%5s%20s%20s%30s%20s", "����", "���", "����", "�̸���", "�б�", "����");

	//���Ͽ� list�� time ���
	for (i = 0; i < count; i++)
	{
		fprintf(ofp, "%s %s %s %s %s %s %s\n", list[i].leader, list[i].company, list[i].name, list[i].email, list[i].school, list[i].major, ctime(&time));

	};

	fclose(ofp);


}
