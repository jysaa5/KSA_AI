#include <stdio.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS

// �ִ�
double max(double arr[]);

// �ּ�
double min(double arr[]);

// ���
double avg(double arr[]);

// ǥ������
double std(double arr[]);

// main �Լ�
int main(void)
{
	double arr[10] = {0};
	double stdNum = 0;
	for (int i = 0; i < 10; i++) 
	{
		printf("���ڸ� �Է��ϼ���: ");
		scanf_s("%lf", &arr[i]);
	
	}
	//double arr[10] = {1,2,3,4,5,6,7,8,9,10};
	printf("ǥ������: ");
	stdNum = std(arr);
	printf("%lf", stdNum);
	return 0;

}

// std: ǥ������ �Լ�
double std(double arr[])
{

	//double aResult = avg(arr);
	double aResult = 5;
	double result = 0;
	double dev[10];
	double pNum[10];

	double var = 0;

	for (int i = 0; i < 10; i++) {
	
		dev[i] = arr[i] - aResult;
		pNum[i] = pow(dev[i], 2);
		var += pNum[i]/10;
	
	}

	result = sqrt(var);

	return result;

}