#include <stdio.h>

struct score		// ����ü ����
{
	int kor;		// ���� ������ ������ ���
	int eng;		// ���� ����
	int math;		// ���� ����
};

int main(void)
{
	struct score yuni = { 90, 80, 70 };   // ����ü ���� ����� �ʱ�ȭ
	struct score* ps = &yuni;             // ����ü �����Ϳ� �ּ� ����

	printf("���� : %d\n", (*ps).kor);     // ����ü �����ͷ� ��� ����
	printf("���� : %d\n", ps->eng);       // -> ������ ���
	printf("���� : %d\n", ps->math);

	return 0;
}