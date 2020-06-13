#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

void fileWriting(struct teamList* list, int count);

struct teamList
{
	int id;
	char team[80];
	char company[80];
};

int main() {

	int count = 0;
	int i = 0;

	struct teamList list[20] = {
		{1,"horangnavi","navilab"},
		{2,"machinegun","5works"},
		{3,"megaton","megazone"},
		{4,"dd","vitec"},
		{5,"banana","monkeysoft"},
		{6,"park123","nurdbana"},
		{0, NULL, NULL}
	};
	
	while (list[i].id != 0) {
		count++;
		i++;
	};

	fileWriting(list, count);
	return 0;
}

void fileWriting(struct teamList* list, int count) {

	FILE* fp = NULL;

	fopen_s(&fp, "C:\\Users\\RentalHub-L5\\Desktop\\test.txt", "a");

	if (fp == NULL) {

		printf("FILE OPEN ERROR\n");
		return;
	}

	for (int i = 0; i < count; i++) {

		fprintf(fp, "%d %80s %80s\n", list[i].id, list[i].team, list[i].company);
	}

	fclose(fp);
}