#include <stdio.h>
#include <string.h>

int main(void)
{
	char str1[80] = "pear";
	char str2[80] = "peach";

	printf("사전에 나중에 나오는 과일 이름 : ");
	if (strcmp(str1, str2) > 0)    // str1이 str2보다 크면(사전에 나중에 나오면)
		printf("%s\n", str1);      // str1 출력
	else                           // str1이 str2보다 크지 않으면
		printf("%s\n", str2);      // str2 출력

	return 0;
}