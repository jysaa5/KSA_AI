#include <stdio.h>

int main(void)
{
	int ch;                    // �Է� ���ڸ� ������ ����

	ch = getchar();            // �Լ��� ��ȯ�ϴ� ���ڸ� �ٷ� ����
	printf("�Է��� ���� : ");
	putchar(ch);               // �Է��� ���� ���
	putchar('\n');             // ���� ���� ���

	return 0;
}