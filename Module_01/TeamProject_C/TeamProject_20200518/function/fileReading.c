#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

void fileReading();

int main() {

	fileReading();
	return 0;
}

void fileReading() {

	FILE* fp = NULL;

	fopen_s(&fp, "C:\\Users\\RentalHub-L5\\Desktop\\test.txt", "r");

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