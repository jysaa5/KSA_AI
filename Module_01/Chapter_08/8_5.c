#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>            // ���ڿ� ���� �Լ� ������ ��Ƴ��� ��� ����

int main(void)
{
	char str1[80] = "cat";
	char str2[80];

	strcpy(str1, "tiger");     // str1 �迭�� "tiger" ����
	strcpy(str2, str1);        // str2 �迭�� str1 �迭�� ���ڿ� ����
	printf("%s, %s\n", str1, str2);

	return 0;
}