#include <stdio.h>

void add_ten(int* pa);       // �Ű������� ������ pa ����

int main(void)
{
	int a = 10;

	add_ten(&a);             // a�� �ּҸ� �μ��� �ش�.
	printf("a : %d\n", a);   // ������ a �� ���

	return 0;
}

void add_ten(int* pa)        // ������ pa�� a�� �ּҸ� �޴´�.
{
	*pa = *pa + 10;          // ������ pa�� ����Ű�� ������ �� 10 ����
}