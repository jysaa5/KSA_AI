#include<stdio.h>

int main(void)
{
	// %d : 정수 출력
	printf("%d\n",10);

	// %lf : 소수점 이하 6자리까지 출력 
	printf("%lf\n", 3.4);

	// %.1lf : 소수점 이하 첫째 자리까지 출력 = 둘째 자리에서 반올림
	printf("%.1lf\n", 3.45);

	printf("%.10lf\n", 3.4);

	printf("%d과 %d의 합은 %d입니다.\n", 10, 20, 10 + 20);

	printf("%.1lf- %.1lf = %.1lf\n", 3.4, 1.2, 3.4 - 1.2);

	return 0;
}