#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>  
#include "studentP.h"

#define MAX 1024
#define COL 6
#define MAX_DATA_LEN 60


void menu(struct studentList* student_list, int list_size)
{
	//���� ����
	int select_num = 0;
	char input[MAX_DATA_LEN];
	time_t t[MAX];
	char ans = 0;
	int k = 1;
	int i = 0;


	//�޴� ����
	while (k) {

		//�޴� ����
		printf("���Ͻô� �޴��� �������ּ���\n");
		printf("1. ���� �˻�\n");
		printf("2. ȸ��� �˻�\n");
		printf("3. �̸� �˻�\n");
		printf("4. Email �˻�\n");
		printf("5. �б� �˻�\n");
		printf("6. ���� �˻�\n");
		scanf("%d", &select_num);
		getchar();



		switch (select_num) {

		case 1:
			t[i] = time(NULL);


			//�˻� �Լ�
			searchingLeader(student_list, list_size, t);

			break;

		case 2:
			//�˻��� ������ �Է¹ޱ�
			printf("\n�˻��ϰ��� �ϴ� ȸ����� �Է����ּ���.\n");
			scanf("%s", &input);
			getchar();
			t[i] = time(NULL);


			//�˻� �Լ�
			searchingCompany(student_list, list_size, input, t);

			break;

		case 3:
			//�˻��� ������ �Է¹ޱ�
			printf("\n�˻��ϰ��� �ϴ� �̸��� �Է����ּ���.\n");
			scanf("%s", &input);
			getchar();
			t[i] = time(NULL);


			//�˻� �Լ�
			searchingName(student_list, list_size, input, t);

			break;

		case 4:
			//�˻��� ������ �Է¹ޱ�
			printf("\n�˻��ϰ��� �ϴ� E-mail�� �Է����ּ���.\n");
			scanf("%s", &input);
			getchar();
			t[i] = time(NULL);


			//�˻� �Լ�
			searchingEmail(student_list, list_size, input, t);

			break;

		case 5:
			//�˻��� ������ �Է¹ޱ�
			printf("\n�˻��ϰ��� �ϴ� �б��� �Է����ּ���.\n");
			scanf("%s", &input);
			getchar();
			t[i] = time(NULL);


			//�˻� �Լ�
			searchingSchool(student_list, list_size, input, t);

			break;

		case 6:
			//�˻��� ������ �Է�
			printf("\n�˻��ϰ��� �ϴ� ������ �Է����ּ���.\n");
			scanf("%s", &input);
			getchar();
			t[i] = time(NULL);


			//�˻� �Լ�
			searchingMajor(student_list, list_size, input, t);

			break;

		default:
			break;
		}

		i++;

		//���α׷� ����
		printf("\n���α׷��� �����Ͻðڽ��ϱ�?(y/n) : ");
		ans = getchar();

		if (ans == 'y')
			k = 0;;

	}
}


//���� ���� ũ�⸦ ��ȯ�ϴ� �Լ�
int getFileSize(char* dir)
{
	//���� ����
	FILE* fp = fopen(dir, "r");
	char* str = 0;
	int buf_size = MAX * MAX;
	int line_count = 0;

	// ũ�� ���� �Ҵ�
	str = (char*)malloc(buf_size);

	//���� �Ҵ翡 ����� ���� ũ�� ����
	while (fgets(str, buf_size, fp)) {

		line_count++;

	}

	free(str);
	fclose(fp);
	return line_count;

}


// �Լ� ����
// fileReading �Լ�: ������ �д� �Լ�
struct studentList fileLineReading(FILE* fp) {

	//���� ����
	// ���� ������ ������
	char* str;
	int buf_size = MAX * MAX;
	char* ptr;
	int line_count = 0;
	int i = 0;


	// ũ�� ���� �Ҵ�
	str = (char*)malloc(buf_size);


	//��ȯ�� ������ ���
	struct studentList line;


	//���� ������ �а�, ��ū �Լ��� �߶�
	//����ü�� ����
	ptr = fgets(str, buf_size, fp);
	line = retToken(ptr);


	//�޸� ��ȯ
	free(str);

	return line;

}

// retToken �Լ�: ��ū�� �������� ������ ����
struct studentList retToken(char* ptr) {

	int i = 0;
	// strtok()�� �̿��Ͽ� ���ڿ��� ';' ��ū�� �������� �ڸ�
	// char* ptr = strtok(inp, ";");
	char* ptoken = strtok(ptr, "??,\n");
	char* line[COL] = { NULL };



	//��ū���� �߷��� �����͸�
	//����ü�� ����
	while (ptoken != NULL) {

		if (i == 0 && (strcmp(ptoken, "����") != 0) && strcmp(ptoken, "���� ����") != 0) {
			line[0] = "����";
			line[i + 1] = ptoken;
		}
		else if (i == 0 && strcmp(ptoken, "����") == 0 || strcmp(ptoken, "���� ����") == 0) {
			line[i] = ptoken;
		}
		else if (strcmp(line[0], "����") == 0) {
			line[i + 1] = ptoken;
		}
		else {
			line[i] = ptoken;
		}

		ptoken = strtok(NULL, "??,\"\n");

		i++;

	}



	return inputData(line);
}



// inputData �Լ�: ����ü�� ������ ����
struct studentList inputData(char** line) {


	struct studentList list_line;


	strcpy(list_line.leader, line[0]);
	strcpy(list_line.company, line[1]);
	strcpy(list_line.name, line[2]);
	strcpy(list_line.email, line[3]);
	strcpy(list_line.school, line[4]);
	strcpy(list_line.major, line[5]);


	return list_line;
}





//���� �˻� �Լ�
void searchingLeader(struct studentList* student_list, int list_size, time_t t) {

	//���� ����
	int count = 0;
	int i, j = 0;

	//�˻��� ������ count
	for (int i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].leader, "����") == 0) {
			count++;
		}
	}


	//�˻� ��� ũ�⿡ �´�
	//�޸� ���� �Ҵ�
	struct studentList* result_list = (struct studentList*) malloc(sizeof(struct studentList) * count);

	//�˻� ���
	//����ü�� ����
	for (i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].leader, "����") == 0) {

			strcpy(result_list[j].leader, student_list[i].leader);
			strcpy(result_list[j].company, student_list[i].company);
			strcpy(result_list[j].name, student_list[i].name);
			strcpy(result_list[j].email, student_list[i].email);
			strcpy(result_list[j].school, student_list[i].school);
			strcpy(result_list[j].major, student_list[i].major);

			j++;
		}
	}


	//�˻� ��� ���
	searchResultPrintf(result_list, count);


	//���� ���
	fileWriting(result_list, t, count);


	//�޸� ��ȯ
	free(result_list);
}



//��� �˻�
void searchingCompany(struct studentList* student_list, int list_size, char* input, time_t t) {

	//���� ����
	int count = 0;
	int i, j = 0;


	//�˻� ��� count
	for (int i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].company, input) == 0) {
			count++;
		}
	}


	//�˻� ��� ũ�⿡ �´�
	//�޸� ���� �Ҵ�
	struct studentList* result_list = (struct studentList*) malloc(sizeof(struct studentList) * count);

	//�˻� ���
	//����ü�� ����
	for (i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].company, input) == 0) {

			strcpy(result_list[j].leader, student_list[i].leader);
			strcpy(result_list[j].company, student_list[i].company);
			strcpy(result_list[j].name, student_list[i].name);
			strcpy(result_list[j].email, student_list[i].email);
			strcpy(result_list[j].school, student_list[i].school);
			strcpy(result_list[j].major, student_list[i].major);

			j++;
		}
	}


	//�˻� ��� ���
	searchResultPrintf(result_list, count);

	//���� ���
	fileWriting(result_list, t, count);

	//�޸� ��ȯ
	free(result_list);
}



//�̸� �˻�
void searchingName(struct studentList* student_list, int list_size, char* input, time_t t) {

	//���� ����
	int count = 0;
	int i, j = 0;


	//�˻� ��� count
	for (int i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].name, input) == 0) {
			count++;
		}
	}


	//�˻� ��� ũ�⿡ �´�
	//�޸� ���� �Ҵ�
	struct studentList* result_list = (struct studentList*) malloc(sizeof(struct studentList) * count);

	//�˻� ���
	//����ü�� ����
	for (i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].name, input) == 0) {

			strcpy(result_list[j].leader, student_list[i].leader);
			strcpy(result_list[j].company, student_list[i].company);
			strcpy(result_list[j].name, student_list[i].name);
			strcpy(result_list[j].email, student_list[i].email);
			strcpy(result_list[j].school, student_list[i].school);
			strcpy(result_list[j].major, student_list[i].major);

			j++;

		}
	}

	//�˻� ��� ���
	searchResultPrintf(result_list, count);

	//���� ���
	fileWriting(result_list, t, count);

	//�޸� ��ȯ
	free(result_list);
}


//�̸��� �˻� �Լ�
void searchingEmail(struct studentList* student_list, int list_size, char* input, time_t t) {

	//���� ����
	int count = 0;
	int i, j = 0;


	//�˻� ��� count
	for (int i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].email, input) == 0) {
			count++;
		}
	}


	//�˻� ��� ũ�⿡ �´�
	//�޸� ���� �Ҵ�
	struct studentList* result_list = (struct studentList*) malloc(sizeof(struct studentList) * count);

	//�˻� ���
	//����ü�� ����
	for (i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].email, input) == 0) {

			strcpy(result_list[j].leader, student_list[i].leader);
			strcpy(result_list[j].company, student_list[i].company);
			strcpy(result_list[j].name, student_list[i].name);
			strcpy(result_list[j].email, student_list[i].email);
			strcpy(result_list[j].school, student_list[i].school);
			strcpy(result_list[j].major, student_list[i].major);

			j++;
		}
	}

	//�˻� ��� ���
	searchResultPrintf(result_list, count);

	//���� ���
	fileWriting(result_list, t, count);

	//�޸� ��ȯ
	free(result_list);
}


//�б� �˻� �Լ�
void searchingSchool(struct studentList* student_list, int list_size, char* input, time_t t) {

	//���� ����
	int count = 0;
	int i, j = 0;

	//�˻� ��� count
	for (int i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].school, input) == 0) {
			count++;
		}
	}


	//�˻� ��� ũ�⿡ �´�
	//�޸� ���� �Ҵ�
	struct studentList* result_list = (struct studentList*) malloc(sizeof(struct studentList) * count);

	//�˻� ���
	//����ü�� ����
	for (i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].school, input) == 0) {

			strcpy(result_list[j].leader, student_list[i].leader);
			strcpy(result_list[j].company, student_list[i].company);
			strcpy(result_list[j].name, student_list[i].name);
			strcpy(result_list[j].email, student_list[i].email);
			strcpy(result_list[j].school, student_list[i].school);
			strcpy(result_list[j].major, student_list[i].major);

			j++;
		}
	}

	//�˻� ��� ���
	searchResultPrintf(result_list, count);

	//���� ���
	fileWriting(result_list, t, count);

	//�޸� ��ȯ
	free(result_list);
}



//���� �˻� �Լ�
void searchingMajor(struct studentList* student_list, int list_size, char* input, time_t t)
{
	//���� ����
	int count = 0;
	int i, j = 0;


	//�˻� ��� count
	for (int i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].major, input) == 0) {
			count++;
		}
	}


	//�˻� ��� ũ�⿡ �´�
	//�޸� ���� �Ҵ�
	struct studentList* result_list = (struct studentList*) malloc(sizeof(struct studentList) * count);

	//�˻� ���
	//����ü�� ����
	for (i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].major, input) == 0) {

			strcpy(result_list[j].leader, student_list[i].leader);
			strcpy(result_list[j].company, student_list[i].company);
			strcpy(result_list[j].name, student_list[i].name);
			strcpy(result_list[j].email, student_list[i].email);
			strcpy(result_list[j].school, student_list[i].school);
			strcpy(result_list[j].major, student_list[i].major);

			j++;
		}
	}


	//�˻� ��� ���
	searchResultPrintf(result_list, count);


	//���� ���
	fileWriting(result_list, t, count);


	//�޸� ��ȯ
	free(result_list);
}



//�˻� ��� ��� �Լ�
void searchResultPrintf(struct studentList* result_list, int count)
{
	//���� ����
	int i = 0;


	//�˻� ����� ����ϴ� �ݺ���
	printf("\n�˻� ��� �Դϴ�.\n\n");
	for (i; i < count; i++)
	{
		printf("%s ", result_list[i].leader);
		printf("%s ", result_list[i].company);
		printf("%s ", result_list[i].name);
		printf("%s ", result_list[i].email);
		printf("%s ", result_list[i].school);
		printf("%s\n", result_list[i].major);
	}
}



//���� ��� �Լ�
void fileWriting(struct studentList* list, time_t time, int count)
{
	//���� ����
	FILE* ofp;
	int i = 0;

	//����� ����
	ofp = fopen("C:\\result\\result.txt", "a");

	if (ofp == NULL)
	{
		printf("��� ������ ���� ���߽��ϴ�\n");
	}


	//�˻��� ����� �˻��ð���
	//���Ϸ� ���
	for (i = 0; i < count; i++)
	{
		fprintf(ofp, "%s ", list[i].leader);
		fprintf(ofp, "%s ", list[i].company);
		fprintf(ofp, "%s ", list[i].name);
		fprintf(ofp, "%s ", list[i].email);
		fprintf(ofp, "%s ", list[i].school);
		fprintf(ofp, "%s ", list[i].major);
		fprintf(ofp, "%s\n", ctime(&time));
	};

	//������ ��ȯ
	fclose(ofp);
}