#include <stdio.h>

int main(void)
{
	char fruit[20] = "strawberry";               // char 배열 선언과 문자열 초기화

	printf("딸기 : %s\n", fruit);                // 배열명으로 저장된 문자열 출력
	printf("딸기쨈 : %s %s\n", fruit, "jam");    // 문자열 상수를 직접 %s로 출력

	return 0;
}