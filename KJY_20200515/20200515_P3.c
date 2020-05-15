#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

// 7장
int rec_func(int n);

void main(void)
{
	int r = 0;
	int num = 0;
	printf("숫자를 입력하세요: ");
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

