#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	char ch;
	int i;

	for (i = 0; i < 3; i++)		// 3�� �ݺ�
	{
		scanf("%c", &ch);		// ���� �Է�
		printf("%c", ch);		// �Էµ� ���� ���
	}

	return 0;
}