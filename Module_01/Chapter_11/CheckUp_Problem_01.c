#include <stdio.h>

// p.303

int main(void)
{

	char ch;

	printf("문자 입력: ");
	ch = getchar();
	printf("%c문자의 아스키 코드 값: %d", ch, ch);

	return 0;
}