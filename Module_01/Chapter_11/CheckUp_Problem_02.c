#include<stdio.h>

// p.314

int main(void)
{
	// 문자를 입력할 변수
	int ch;

	// 소문자의 개수를 셀 변수
	int cnt = 0;

	ch = getchar();

	while (ch != '\n')
	{
		if ((97 <= ch) && (ch <= 122)) {

			cnt++;
		}
		ch = getchar();
	}

	printf("소문자의 개수: %d\n", cnt);

	return 0;
}