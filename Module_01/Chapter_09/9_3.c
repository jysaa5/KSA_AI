#include <stdio.h>

int main(void)
{
	int a = 10, b = 15, total;      // ���� ����� �ʱ�ȭ
	double avg;                     // ����� ������ ����
	int* pa, * pb;                  // ������ ���� ����
	int* pt = &total;               // ������ ����� �ʱ�ȭ
	double* pg = &avg;              // double�� ������ ����� �ʱ�ȭ

	pa = &a;                        // ������ pa�� ���� a�� �ּ� ����
	pb = &b;                        // ������ pb�� ���� b�� �ּ� ����

	*pt = *pa + *pb;                // a ���� b ���� ���� total�� ����
	*pg = *pt / 2.0;                // total ���� 2�� ���� ���� avg�� ����

	printf("�� ������ �� : %d, %d\n", *pa, *pb);   // a ���� b �� ���
	printf("�� ������ �� : %d\n", *pt);            // total �� ���
	printf("�� ������ ��� : %.1lf\n", *pg);       // avg �� ���

	return 0;
}