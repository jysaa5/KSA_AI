#include <stdio.h>

int main(void)
{
	printf("apple이 저장된 시작 주소 값 : %p\n", "apple");    // 주소 값 출력
	printf("두 번째 문자의 주소 값 : %p\n", "apple" + 1);     // 주소 값 출력
	printf("첫 번째 문자 : %c\n", *"apple");                  // 간접 참조 연산
	printf("두 번째 문자 : %c\n", *("apple" + 1));            // 포인터 연산식
	printf("배열로 표현한 세 번째 문자 : %c\n", "apple"[2]);  // 배열 표현식

	return 0;
}