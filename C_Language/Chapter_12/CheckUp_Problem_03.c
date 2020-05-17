#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

// p.352
int main(void)
{
	char str[80];
	strcpy(str, "wine");
	strcat(str, "apple");
	strncpy(str, "pear", 1);
	printf("%s, %d\n", str, strlen(str));

	return 0;
}
