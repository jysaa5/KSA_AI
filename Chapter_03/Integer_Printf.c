#include <stdio.h>

int main(void)
{
	// short���� �ִ� �ʱ�ȭ
	short sh = 32767;                     

	// int���� �ִ� �ʱ�ȭ
	int in = 2147483647;       

	// long���� �ִ� �ʱ�ȭ
	long ln = 2147483647;              

	// ���� ū �� �ʱ�ȭ
	long long lln = 123451234512345; 

	printf("short�� ���� ��� : %d\n", sh);
	printf("int�� ���� ��� : %d\n", in);
	printf("long�� ���� ��� : %ld\n", ln);

	// long long���� lld�� ���
	printf("long long�� ���� ��� : %lld\n", lln);   


	return 0;
}