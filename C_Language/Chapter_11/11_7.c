#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int num, grade;           // �й��� ������ ������ ����

	printf("�й� �Է� : ");
	scanf("%d", &num);        // �й� �Է�
	getchar();                // ���ۿ� ���� �ִ� ���� ���� ����
	printf("���� �Է� : ");
	grade = getchar();        // ���� �Է�
	printf("�й� : %d, ���� : %c", num, grade);

	return 0;
}