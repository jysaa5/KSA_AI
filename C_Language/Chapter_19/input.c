#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

extern int count;                 // main.c ������ ���� ���� count ����
int total = 0;                    // ���� ���� ����

int input_data(void)
{
	int pos;                      // ��� ����

	while (1)
	{
		printf("��� �Է� : ");
		scanf("%d", &pos);        // ��� �Է�
		if (pos < 0) break;       // ������ �Է� ����
		count++;                  // ���� ����
		total += pos;             // �Է°��� ���� ���� total�� ����
	}

	return total;                 // ���� ���� total�� �� ��ȯ
}