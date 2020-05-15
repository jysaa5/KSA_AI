#include <stdio.h>

int main(void)
{
	unsigned int a;

	// 큰 양수 저장
	a = 4294967295;        

	// %d로 출력
	printf("%d\n", a);    

	// 음수 저장
	a = -1;              

	// %u로 출력
	printf("%u\n", a);     

	return 0;
}