#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int age;                  // ���̸� ������ ����
	char name[20];            // �̸��� ������ �迭

	printf("���� �Է� : ");
	scanf("%d", &age);        // scanf �Լ��� ���� �Է�

	printf("�̸� �Է� : ");
	gets(name);               // gets �Լ��� �̸� �Է�
	printf("���� : %d, �̸� : %s\n", age, name);

	return 0;
}