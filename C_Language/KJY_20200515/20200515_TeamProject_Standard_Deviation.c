#include <stdio.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS

// 최대
double max(double arr[]);

// 최소
double min(double arr[]);

// 평균
double avg(double arr[]);

// 표준편차
double std(double arr[]);

// main 함수
int main(void)
{
	double arr[10] = {0};
	double stdNum = 0;
	for (int i = 0; i < 10; i++) 
	{
		printf("숫자를 입력하세요: ");
		scanf_s("%lf", &arr[i]);
	
	}
	//double arr[10] = {1,2,3,4,5,6,7,8,9,10};
	printf("표준편차: ");
	stdNum = std(arr);
	printf("%lf", stdNum);
	return 0;

}

// std: 표준편차 함수
double std(double arr[])
{

	//double aResult = avg(arr);
	double avg_value = 5;
	double std_value = 0;
	double dev[10];
	double pNum[10];

	double var = 0;

	for (int i = 0; i < 10; i++) {
	
		dev[i] = arr[i] - avg_value;
		pNum[i] = pow(dev[i], 2);
		var += pNum[i];
	
	}

	var = var / 10;

	std_value = sqrt(var);

	return std_value;

}