#include<stdio.h>
#define _CRT_SECURE_NO_WARNINGS

// 6장 
int main(void)
{
	int i, j= 1;
	int count = 0;
	int num = 0;

	printf("2이상의 정수를 입력하세요: ");

	scanf_s("%d", &num);

	for (i = 1; i <= num; i++) {
		
		for (j = 2; j < i; j++) {
		
			//나누어서 떨어지는 숫자가 있다면 제외
			if ((i % j) == 0) {

				break;
			}
		
		}

		if (i == j) {
			
			printf("%d\t", i);
			
			count++;

			if ((count % 5) == 0) {

				printf("\n");

			}
		}

	}

	//printf("\n1부터 1000 사이의 소수는 %d개이다. \n", count);

	return 0;

}// main 함수 종료