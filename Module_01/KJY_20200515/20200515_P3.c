#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

// 7��
int rec_func(int n);

void main(void)
{
	int r = 0;
	int num = 0;
	printf("���ڸ� �Է��ϼ���: ");
	scanf_s("%d", &num);
	r = rec_func(num);
	printf("%d", r);

}

int rec_func(int n)
{
	int result = 1;

	
	if (n == 1) {
		return 1;
	}

	return n+rec_func(n-1);
}

