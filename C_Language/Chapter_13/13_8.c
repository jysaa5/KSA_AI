#include <stdio.h>

int* sum(int a, int b);   // int형 변수의 주소를 반환하는 함수 선언

int main(void)
{
	int* resp;            // 반환값을 저장할 포인터 resp(result pointer)

	resp = sum(10, 20);   // 반환된 주소는 resp에 저장
	printf("두 정수의 합 : %d\n", *resp);   // resp가 가리키는 변숫값 출력

	return 0;
}

int* sum(int a, int b)    // int형 변수의 주소를 반환하는 함수
{
	static int res;       // 정적 지역 변수

	res = a + b;          // 두 정수의 합을 res(result)에 저장

	return &res;          // 정적 지역 변수의 주소 반환
}