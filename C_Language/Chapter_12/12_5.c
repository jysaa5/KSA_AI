#include <stdio.h>
// ���߿� �Է��� �����Դϴ�.

int main(void)
{
	char str[80];

	printf("������ ���Ե� ���ڿ� �Է� : ");
	fgets(str, sizeof(str), stdin);              // ���ڿ� �Է�
	// ���߿� �Է��� �����Դϴ�.
	printf("�Էµ� ���ڿ��� %s�Դϴ�\n", str);   // ���ڿ� ���

	return 0;
}