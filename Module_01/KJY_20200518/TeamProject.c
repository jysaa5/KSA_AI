#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

struct teamList
{
	int id;
	char team[80];
	char company[80];
};

int menu(void);
struct teamList* input(struct teamList*);
void sortingSelect(struct teamList*, int);
void printingList(struct teamList*, int);
void quickSorting(struct teamList*, int, int);

int main(void)
{
	int num;
	int select_num;

	// ������Ʈ ���� ����
	struct teamList list[10] = {
		{.id = 1, .team[0] = "horangnavi", .company[0] ="navilab"},
		{.id = 2, .team[1] = "machinegun", .company[1] = "5works"},
		{.id = 3, .team[2] = "megaton",.company[2] = "megazone"},
		{.id = 4, .team[3] = "dd", .company[3] = "vitec"},
		{.id = 5, .team[4] = "banana",.company[4] = "monkeysoft"},
		{.id = 6, .team[5] = "park123", .company[5] = "nurdbana"}
	};
	num = menu();
	switch (num)
	{
	case 0:
		num = menu();
		break;
	case 1:
		 list[sizeof(list)/sizeof(list[0])] = *input(list);
		break;
	case 2:

		printf("���Ͻô� �޴��� �������ּ���\n");
		printf("1. id�� ����\n");
		printf("2. �� �̸����� ����\n");
		printf("3. ȸ�� �̸����� ����\n");

		scanf("%d\n", &select_num);
		sortingSelect(list, select_num);
		//printing(sorted_list);
		break;

		/*case 3:
			printing(list);
			break;
		*/
	default:
		printf("1 �Ǵ� 2�� �Է����ּ���.\n");
		num = menu();
		break;
	};

	return 0;

}

int menu(void)
{
	int num = 0;
	printf("���Ͻô� �޴��� �������ּ���\n");
	printf("1. �Է�\n");
	printf("2. ����\n");
	//printf("3. ��ü ���\n");

	printf("���Ͻô� �޴��� �Է����ּ���\n");
	scanf("%d\n", &num);

	return num;
}

// ������ �Է�
struct teamList* input(struct teamList* list)
{
	struct teamList team_list[80];
	printf("�� �̸��� �Է��ϼ���: ");
	scanf("%s", &team_list->team);

	printf("ȸ�� �̸��� �Է��ϼ���: ");
	scanf("%s", &team_list->company);
	
	team_list[0].id = (sizeof(*list) / sizeof(list[0])) + 1;

	return team_list;
}


void sortingSelect(struct teamList* list, int select_num)
{
	int sort_num = 0;

	printf("���Ͻô� �޴��� �������ּ���\n");
	printf("1. �������� ����\n");
	printf("2. �������� ����\n");

	scanf("%d\n", &sort_num);

	return;
}

void quickSorting(struct teamList* list, int select_num, int sort_num)
{
	struct teamList team_list;
	int pivot;
	int start, end;

	//select pivot
	pivot = (sizeof(*list) / sizeof(list[0])) / 2;



	//select_num = 1
	//id�� �������� sorting




	//select_num = 2 or 3
	//���� ȸ�縦 �������� sorting




	printingList(list, sort_num);

	return;
}

void printingList(struct teamList* list, int sort_num)
{

	return 0;
}