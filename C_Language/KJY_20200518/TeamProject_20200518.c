#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

// ����ü
struct teamList
{
	int id;
	char team[80];
	char company[80];
};


// �Լ� ����
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

	// �� ����Ʈ ���� ����
	struct teamList list[] = {
		{1,"horangnavi","navilab"},
		{2,"machinegun","5works"},
		{3,"megaton","megazone"},
		{4,"dd","vitec"},
		{5,"banana","monkeysoft"},
		{6,"park123","nurdbana"}
		,{0,NULL,NULL}
	};


	// ���ο� �߰�
	struct teamList newList;

	// ����Ʈ ����
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

			printf("���Ͻô� �޴��� �������ּ���\n");
			printf("1. id�� ����\n");
			printf("2. �� �̸����� ����\n");
			printf("3. ȸ�� �̸����� ����\n");

			scanf("%d", &select_num);
			sortingSelect(list, select_num, list_size);
			break;

		default:
			printf("1 �Ǵ� 2�� �Է����ּ���.\n");
			all_select_num = menu();
			break;
		};
	}
	return 0;

}

int menu(void)
{
	int num = 0;
	printf("���Ͻô� �޴��� �������ּ���\n");
	printf("1. �Է�\n");
	printf("2. ����\n");
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