#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

void swap(double *pa, double *pb);
void line_up(double *maxp, double *midp, double *minp);


// 9��
int main(void)
{
	double max, mid, min;

	printf("�Ǽ��� 3�� �Է�: ");
	scanf_s("%lf%lf%lf", &max, &mid, &min);
	line_up(&max, &mid, &min);
	printf("���ĵ� �� ���: %.1lf, %.1f, %.1f\n", max, mid, min);

	return 0;

}

// swap �Լ�: �� ���� �ڸ��� �����ϴ� �޼���
void swap(double *pa, double *pb)
{
	double temp;

	temp = *pa;
	*pa = *pb;
	*pb = temp;
}

// line_up �Լ�: ��� ��
void line_up(double *a, double *b, double *c)
{

	if (*a < *b) {
		swap(a, b);
	}

	if (*a < *c) {
		swap(a, c);
	}

	if (*b < *c) {
		swap(b, c);
	}

}