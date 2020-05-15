#include <stdio.h>

int main(void)
{
	// \n : 줄을 바꿈 
	printf("Be happy\n");
	printf("12345678901234567890\n");
	
	// \t : 탭 위치로 이동 (tab 만큼 띄어쓰기)
	printf("My \t friend \n");

	// \b : t를 d로 바꾼다.
	printf("Goot\bd\tchance\n");

	// \r : C를 W로 바꾼다.
	// \a : 벨소리를 낸다.
	printf("Cow\rW\a\n");

	return 0;
}