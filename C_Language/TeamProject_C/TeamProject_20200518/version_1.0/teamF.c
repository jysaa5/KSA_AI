#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "teamF.h"



int menu(void)
{
	int num = 0;
	printf("원하시는 메뉴를 선택해주세요\n");
	printf("1. 입력\n");
	printf("2. 정렬\n");
	printf("3. 파일 출력\n");
	printf("4. 파일 입력\n");
	scanf("%d", &num);
	printf("\n");



	return num;
}

// 데이터 입력
struct teamList* input(int list_size)
{
	struct teamList team_list[80];
	team_list[0].id = list_size + 1;
	printf("팀 이름을 입력하세요: ");
	scanf("%s", &team_list->team);

	printf("\n회사 이름을 입력하세요: ");
	scanf("%s", &team_list->company);

	//team_list[0].id = (sizeof(*list) / sizeof(list[0])) + 1;

	return team_list;
}


// 정렬 선택
void sortingSelect(struct teamList list[], int select_num, int list_size)
{
	int sort_num = 0;

	printf("원하시는 메뉴를 선택해주세요\n");
	printf("1. 오름차순 정렬\n");
	printf("2. 내림차순 정렬\n");

	scanf("%d", &sort_num);
	bubbleSorting(list, select_num, sort_num, list_size);


	return;
}


// 데이터 정렬
void bubbleSorting(struct teamList list[], int select_num, int sort_num, int list_size)
{
	struct teamList temp;

	if (select_num == 1)
	{
		//버블 정렬
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
		//버블 정렬
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
		//버블 정렬
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

// 데이터 출력
void printingList(struct teamList* list, int sort_num, int list_size)
{
	int i;

	if (sort_num == 1) //오름차순 정렬일때
	{
		for (i = 0; i < list_size; i++)
		{
			printf("%d%80s%80s\n", list[i].id, list[i].team, list[i].company);
		}
	}
	else if (sort_num == 2) // 내림차순 정렬일때
	{
		for (i = list_size - 1; i >= 0; i--)
		{
			printf("%d%80s%80s\n", list[i].id, list[i].team, list[i].company);
		}
	}
	else // 예외 처리
	{
		printf("잘못된 수를 입력하셨습니다.\n");
	}

	return 0;
}

//파일출력
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

void fileReading() {

	FILE* fp = NULL;

	fopen_s(&fp, "C:\\Users\\USER\\Desktop\\test.txt", "r");

	if (fp != NULL) {

		int id = 0;
		char team[80];
		char company[80];

		while (!feof(fp)) {

			fscanf(fp, "%d %s %s", &id, team, company);

			if (feof(fp)) {
				break;
			}

			printf("%d %s %s\n", id, team, company);
		}
	}

	fclose(fp);
}