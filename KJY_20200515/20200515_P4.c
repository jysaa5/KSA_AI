#include<stdio.h>
#define _CRT_SECURE_NO_WARNINGS

// 8��
int main(void)
{
	char str1[80] = {""};
	//char str2[100];
	printf("���� �Է�: ");
	gets(str1);


	for (int i = 0; i < sizeof(str1); i++) 
	{
		char c; 
		c = str1[i];
		if ( c >= 'A' && c <= 'Z') {
			c = c + 32;
			str1[i] = c;
		}
	}

	puts("�ٲ� ����: ");
	puts(str1);


	return 0;
}