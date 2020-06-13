#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

// 퀴즈
int rec_func(int n) 
{
	printf("apple \n");
	//printf("%d \n", n);
	n = n - 1;
	if (n == 0) {
		return;
	}
	return rec_func(n);
}


int main(void)
{
	int num = 0;
	printf("숫자를 입력하세요: ");
	scanf_s("%d", &num);

	rec_func(num);

	return 0;
}