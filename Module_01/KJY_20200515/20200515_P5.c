#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

void swap(double *pa, double *pb);
void line_up(double *maxp, double *midp, double *minp);


// 9장
int main(void)
{
	double max, mid, min;

	printf("실수값 3개 입력: ");
	scanf_s("%lf%lf%lf", &max, &mid, &min);
	line_up(&max, &mid, &min);
	printf("정렬된 값 출력: %.1lf, %.1f, %.1f\n", max, mid, min);

	return 0;

}

// swap 함수: 두 수의 자리를 스왑하는 메서드
void swap(double *pa, double *pb)
{
	double temp;

	temp = *pa;
	*pa = *pb;
	*pb = temp;
}

// line_up 함수: 대소 비교
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