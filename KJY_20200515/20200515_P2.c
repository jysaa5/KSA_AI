#include<stdio.h>
#define _CRT_SECURE_NO_WARNINGS

// 6�� 
int main(void)
{
	int i, j= 1;
	int count = 0;
	int num = 0;

	printf("2�̻��� ������ �Է��ϼ���: ");

	scanf_s("%d", &num);

	for (i = 1; i <= num; i++) {
		
		for (j = 2; j < i; j++) {
		
			//����� �������� ���ڰ� �ִٸ� ����
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

	//printf("\n1���� 1000 ������ �Ҽ��� %d���̴�. \n", count);

	return 0;

}// main �Լ� ����