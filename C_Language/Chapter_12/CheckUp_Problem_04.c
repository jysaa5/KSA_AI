#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

// p.353

int main(void)
{
	char str[80] = "A";
	char strcp[80] = "A";

	printf("단어 입력: ");
	scanf("%s", str);

	if (strlen(str) <= 15) {

		strcpy(strcp, str, 5);

		if (strlen(str) > 5) {
			for (int i = 0; i < strlen(str) - 5; i++)
			{
				strcat(strcp, "*");
			}
		}

		printf("입력한 단어: %s, 생략한 단어: %s ", str, strcp);


	}

	return 0;
}