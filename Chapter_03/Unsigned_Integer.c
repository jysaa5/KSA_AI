#include <stdio.h>

int main(void)
{
	unsigned int a;

	// ū ��� ����
	a = 4294967295;        

	// %d�� ���
	printf("%d\n", a);    

	// ���� ����
	a = -1;              

	// %u�� ���
	printf("%u\n", a);     

	return 0;
}