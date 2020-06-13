#include<stdio.h>
#include<math.h>
#define _CRT_SEVURE_NO_WARNINGS

// 팀 프로젝트: 10개의 실수를 입력 받아서 최대, 최소, 평균, 표준편차 함수를 구현한다.

// 함수 선언

// 입력된 실수의 최대값
double max(double arr[]);


// 입력된 실수의 최소값
double min(double arr[]);


// 입력된 실수의 평균값
double avg(double arr[], int);


// 입력된 실수의 표준편차
double std(double arr[], int);

int main(void)
{
	// 초기화
	double max_num, min_num, avg_num, std_num = 0;
	double arr[10] = {0};
	int i = 0;

	for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		printf("숫자를 입력하세요: ");
		scanf_s("%lf", &arr[i]);
	}

	double* p = &arr;
	int count = sizeof(arr) / sizeof(arr[0]);

	max_num = max(p);
	min_num = min(p);
	avg_num = avg(p, count);
	std_num = std(p, count);

	printf("max: %lf\n", max_num);
	printf("min: %lf\n", min_num);
	printf("avg: %lf\n", avg_num);
	printf("std: %lf\n", std_num);

	return 0;

}


// 최대갑 구하는 함수
double max(double* pointer) 
{
	// 초기화
	int i = 0;
	double max_value = pointer[0];

	for (i = 0; i < 10; i++) 
	{
		if (max_value < pointer[i])
		{
			max_value = pointer[i];
		}
	
	}
	return max_value;
}


// 최소값을 구하는 함수
double min(double* pointer)
{
	// 초기화
	double min_value = pointer[0];
	int i = 0;

	for (i = 0; i < 10; i++)
	{
		if (min_value > pointer[i])
		{
			min_value = pointer[i];
		}
	}
	return min_value;
}


// 평균값
double avg(double* p, int count)
{
	// 초기화
	double avg_value = 0;
	double sum = 0;
	int i = 0;

	for(i = 0; i<count; i++)
	{
		sum += p[i];
	}

	avg_value = sum / count;

	return avg_value;
}


// 표준편차
double std(double* pointer, int count)
{
	// 평균값
	double avg_value = 0;
	
	// 표준편차값
	double std_value = 0;
	
	// 편차
	double dev[10];
	
	// 제곱한 수 저장
	double pNum[10];

	// 분산
	double var = 0;

	int i = 0;

	avg_value = avg(pointer, count);


	for (i = 0; i < count; i++)
	{
		dev[i] = pointer[i] - avg_value;
		pNum[i] = pow(dev[i], 2);
		var += pNum[i];
	}

	var = var/count;

	// 분산의 루트값 = 표준편차
	std_value = sqrt(var);

	return std_value;

}