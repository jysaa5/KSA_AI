#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ShlObj.h>
#include "teamF.h"
#pragma comment(lib, "Shell32.lib")


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

		case 3:
			fileWriting(list, list_size);
			break;

		default:
			printf("1 �Ǵ� 2�� �Է����ּ���.\n");
			all_select_num = menu();
			break;
		};
	}


	return 0;

}