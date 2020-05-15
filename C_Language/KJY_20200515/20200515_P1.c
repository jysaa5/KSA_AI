#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

// 5장
int main(void) 
{
	int a = 0;
	int b = 0;
	char op = 'A';
	int result = 0;

	printf("사칙연산 입력(정수): ");
	//scanf_s("%d%c%d", &a, &op, &b);
	scanf_s("%d", &a);
	scanf_s("%c", &op);
	scanf_s("%d", &b);

	switch (op)
	{
	case '+':
		result = a + b;
		printf("%d", a);
		printf("%c", op);
		printf("%d", b);
		printf("=");
		printf("%d", result);
		//printf("%d",result);
		break;

	case '-':
		result = a - b;
		printf("%d", a);
		printf("%c", op);
		printf("%d", b);
		printf("=");
		printf("%d", result);
		//printf("%d%c%d = %d", &a, &op, &b, &result);
		//printf("%d", result);
		break;

	case '*':
		result = a * b;
		printf("%d", a);
		printf("%c", op);
		printf("%d", b);
		printf("=");
		printf("%d", result);
		//printf("%d%c%d = %d", &a, &op, &b, &result);
		//printf("%d", result);
		break;

	case '/':
		result = a / b;
		printf("%d", a);
		printf("%c", op);
		printf("%d", b);
		printf("=");
		printf("%d", result);
		//printf("%d%c%d = %d", &a, &op, &b, &result);
		//printf("%d", result);
		break;
	}

	return 0;

}

