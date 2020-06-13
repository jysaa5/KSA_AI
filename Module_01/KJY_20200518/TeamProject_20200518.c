#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

// 구조체
struct teamList
{
	int id;
	char team[80];
	char company[80];
};


// 함수 선언
int menu(void);
struct teamList* input(int);
void sortingSelect(struct teamList[], int);
void printingList(struct teamList*, int, int);
void bubbleSorting(struct teamList[], int, int, int);




int main(void) {

	int all_select_num = 0;
	int select_num = 0;
	int list_size = 0;
	int i = 0;
	char newTeam[20];

	// 팀 리스트 개수 수정
	struct teamList list[] = {
		{1,"horangnavi","navilab"},
		{2,"machinegun","5works"},
		{3,"megaton","megazone"},
		{4,"dd","vitec"},
		{5,"banana","monkeysoft"},
		{6,"park123","nurdbana"}
		,{0,NULL,NULL}
	};


	// 새로운 추가
	struct teamList newList;

	// 리스트 길이
	while (list[i].id != 0) {
		i++;
		list_size++;
	}

	while (1) {

		all_select_num = menu();
		//all_select_num = menu();

		switch (all_select_num) {

		case 0:
			all_select_num = menu();
			break;

		case 1:
			newList = *input(list_size);
			list[list_size].id = newList.id;
			strcpy(list[list_size].team, newList.team);
			strcpy(list[list_size].company, newList.company);
			printf("\n");
			list_size++;
			break;

		case 2:

			printf("원하시는 메뉴를 선택해주세요\n");
			printf("1. id로 정렬\n");
			printf("2. 팀 이름으로 정렬\n");
			printf("3. 회사 이름으로 정렬\n");

			scanf("%d", &select_num);
			sortingSelect(list, select_num, list_size);
			break;

		default:
			printf("1 또는 2를 입력해주세요.\n");
			all_select_num = menu();
			break;
		};
	}
	return 0;

}

int menu(void)
{
	int num = 0;
	printf("원하시는 메뉴를 선택해주세요\n");
	printf("1. 입력\n");
	printf("2. 정렬\n");
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