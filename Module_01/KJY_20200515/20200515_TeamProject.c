#include<stdio.h>
#include<math.h>
#define _CRT_SEVURE_NO_WARNINGS

// �� ������Ʈ: 10���� �Ǽ��� �Է� �޾Ƽ� �ִ�, �ּ�, ���, ǥ������ �Լ��� �����Ѵ�.

// �Լ� ����

// �Էµ� �Ǽ��� �ִ밪
double max(double arr[]);


// �Էµ� �Ǽ��� �ּҰ�
double min(double arr[]);


// �Էµ� �Ǽ��� ��հ�
double avg(double arr[], int);


// �Էµ� �Ǽ��� ǥ������
double std(double arr[], int);

int main(void)
{
	// �ʱ�ȭ
	double max_num, min_num, avg_num, std_num = 0;
	double arr[10] = {0};
	int i = 0;

	for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		printf("���ڸ� �Է��ϼ���: ");
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


// �ִ방 ���ϴ� �Լ�
double max(double* pointer) 
{
	// �ʱ�ȭ
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


// �ּҰ��� ���ϴ� �Լ�
double min(double* pointer)
{
	// �ʱ�ȭ
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


// ��հ�
double avg(double* p, int count)
{
	// �ʱ�ȭ
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


// ǥ������
double std(double* pointer, int count)
{
	// ��հ�
	double avg_value = 0;
	
	// ǥ��������
	double std_value = 0;
	
	// ����
	double dev[10];
	
	// ������ �� ����
	double pNum[10];

	// �л�
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

	// �л��� ��Ʈ�� = ǥ������
	std_value = sqrt(var);

	return std_value;

}