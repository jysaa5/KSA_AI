#include <stdio.h>

int main(void)
{
	// int�� ���� a ����
	int a;

	// 2���� int�� ���� b,c�� ���ÿ� ����
	int b, c;

	// 2���� int�� ���� b,c�� ���ÿ� ����
	double da;

	// char�� ���� ch ����
	char ch;

	// int�� ���� a�� ���� 10 ����
	a = 10;

	// int�� ���� b�� ���� a�� �� ����
	b = a;

	// int�� ���� c�� ���� a�� ���� ���� 20�� ���� �� ����
	c = a + 20;

	// double�� ���� da�� �Ǽ� 3.5 ����
	da = 3.5;       

	// char�� ���� ch�� ���� 'A' ����
	ch = 'A';        

	printf("���� a�� �� : %d\n", a);
	printf("���� b�� �� : %d\n", b);
	printf("���� c�� �� : %d\n", c);
	printf("���� da�� �� : %.1lf\n", da);
	printf("���� ch�� �� : %c\n", ch);

	return 0;
}