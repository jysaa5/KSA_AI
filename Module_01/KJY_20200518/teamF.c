#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "teamF.h"



int menu(void)
{
	int num = 0;
	printf("���Ͻô� �޴��� �������ּ���\n");
	printf("1. �Է�\n");
	printf("2. ����\n");
	printf("3. ���� ���\n");
	scanf("%d", &num);
	printf("\n");



	return num;
}

// ������ �Է�
struct teamList* input(int list_size)
{
	struct teamList team_list[80];
	team_list[0].id = list_size + 1;
	printf("�� �̸��� �Է��ϼ���: ");
	scanf("%s", &team_list->team);

	printf("\nȸ�� �̸��� �Է��ϼ���: ");
	scanf("%s", &team_list->company);

	//team_list[0].id = (sizeof(*list) / sizeof(list[0])) + 1;

	return team_list;
}


// ���� ����
void sortingSelect(struct teamList list[], int select_num, int list_size)
{
	int sort_num = 0;

	printf("���Ͻô� �޴��� �������ּ���\n");
	printf("1. �������� ����\n");
	printf("2. �������� ����\n");

	scanf("%d", &sort_num);
	bubbleSorting(list, select_num, sort_num, list_size);


	return;
}


// ������ ����
void bubbleSorting(struct teamList list[], int select_num, int sort_num, int list_size)
{
	struct teamList temp;

	if (select_num == 1)
	{
		//���� ����
		for (int i = 0; i < list_size - 1; i++)
		{
			for (int j = 0; j < list_size - 1; j++)
			{
				if (list[j].id > list[j + 1].id)
				{
					temp = list[j];
					list[j] = list[j + 1];
					list[j + 1] = temp;
				}
			}
		}
	}
	else if (select_num == 2)
	{
		//���� ����
		for (int i = 0; i < list_size - 1; i++)
		{
			for (int j = 0; j < list_size - 1; j++)
			{
				if (strcmp(list[j].team, list[j + 1].team) > 0)
				{
					temp = list[j];
					list[j] = list[j + 1];
					list[j + 1] = temp;
				}
			}
		}
	}
	else if (select_num == 3)
	{
		//���� ����
		for (int i = 0; i < list_size - 1; i++)
		{
			for (int j = 0; j < list_size - 1; j++)
			{
				if (strcmp(list[j].company, list[j + 1].company) > 0)
				{
					temp = list[j];
					list[j] = list[j + 1];
					list[j + 1] = temp;
				}
			}
		}
	}




	printingList(list, sort_num, list_size);

	return;
}

// ������ ���
void printingList(struct teamList* list, int sort_num, int list_size)
{
	int i;

	if (sort_num == 1) //�������� �����϶�
	{
		for (i = 0; i < list_size; i++)
		{
			printf("%d%80s%80s\n", list[i].id, list[i].team, list[i].company);
		}
	}
	else if (sort_num == 2) // �������� �����϶�
	{
		for (i = list_size - 1; i >= 0; i--)
		{
			printf("%d%80s%80s\n", list[i].id, list[i].team, list[i].company);
		}
	}
	else // ���� ó��
	{
		printf("�߸��� ���� �Է��ϼ̽��ϴ�.\n");
	}

	return 0;
}

//�������
void fileWriting(struct teamList* list, int count) {

	FILE* fp = NULL;

	fopen_s(&fp, "C:\\Users\\USER\\Desktop\\test.txt", "a");

	if (fp == NULL) {

		printf("FILE OPEN ERROR\n");
		return;
	}

	for (int i = 0; i < count; i++) {

		fprintf(fp, "%d %80s %80s\n", list[i].id, list[i].team, list[i].company);
	}

	fclose(fp);
}