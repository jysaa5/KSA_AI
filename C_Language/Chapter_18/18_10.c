#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	FILE* fp;                       // ���� ������
	int age;                        // ���� ���� ����
	char name[20];                  // �̸� ���� �迭

	fp = fopen("a.txt", "r");       // ���� ����

	fscanf(fp, "%d", &age);         // ���� �Է�
	fgets(name, sizeof(name), fp);  // �̸� �Է�

	printf("���� : %d, �̸� : %s", age, name);  // �Է� ������ ���
	fclose(fp);                     // ���� ����

	return 0;
}