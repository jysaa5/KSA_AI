#include <stdio.h>

void print_char(char ch, int count);    // �Լ� ����

int main(void)
{
	print_char('@', 5);                 // ���ڿ� ���ڸ� �ְ� �Լ� ȣ��

	return 0;
}

void print_char(char ch, int count)     // �Ű������� ������ ��ȯ���� ����.
{
	int i;

	for (i = 0; i < count; i++)         // i�� 0���� count-1���� ����, count�� �ݺ�
	{
		printf("%c", ch);               // �Ű����� ch�� ���� ���� ���
	}

	return;
}