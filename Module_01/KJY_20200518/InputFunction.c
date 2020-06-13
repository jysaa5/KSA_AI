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
//void sortingSelect(struct teamList*, int);
//void printingList(struct teamList*, int);
//void quickSorting(struct teamList*, int, int);



int main(void) {

	int all_select_num = 0;
	int select_num = 0;
	int list_size = 0;
	int i = 0;
	char newTeam[20];

	// 팀 리스트 개수 수정
	struct teamList list[20] = {
		{1,"horangnavi","navilab"},
		{2,"machinegun","5works"},
		{3,"megaton","megazone"},
		{4,"dd","vitec"},
		{5,"banana","monkeysoft"},
		{6,"park123","nurdbana"}
		,{0,NULL,NULL}
	};



	struct teamList newList;

	// 리스트 길이
	while (list[i].id != 0) {
		i++;
		list_size++;
	}
	all_select_num = menu();

	switch (all_select_num) {

	case 0:
		all_select_num = menu();
		break;

	case 1:
		//list[sizeof(list) / sizeof(list[0])] = *input(list);
		newList = *input(list_size);
		list[list_size].id = newList.id;
		strcpy(list[list_size].team, newList.team);
		strcpy(list[list_size].company, newList.company);
		//*list[list_size].team = newList.team;
		//*list[list_size].company = *newList.company;


		break;

	case 2:

		printf("원하시는 메뉴를 선택해주세요\n");
		printf("1. id로 정렬\n");
		printf("2. 팀 이름으로 정렬\n");
		printf("3. 회사 이름으로 정렬\n");

		scanf("%d", &select_num);
		//sortingSelect(list, select_num);
		//printing(sorted_list);
		break;

		/*case 3:
			printing(list);
			break;
		*/
	default:
		printf("1 또는 2를 입력해주세요.\n");
		all_select_num = menu();
		break;
	};

	return 0;

}

int menu(void)
{
	int num = 0;
	printf("원하시는 메뉴를 선택해주세요\n");
	printf("1. 입력\n");
	printf("2. 정렬\n");
	//printf("3. 전체 출력\n");
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