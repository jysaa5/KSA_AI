#include <stdio.h>

int sum(int x, int y);       // sum �Լ� ���� : 186�ʿ��� �����մϴ�.

int main(void)               // main �Լ� ����
{
	int a = 10, b = 20;
	int result;              // �� ������ ���� ���(result)�� ������ ����

	result = sum(a, b);      // sum �Լ� ȣ��
	printf("result : %d\n", result);

	return 0;
}                            // main �Լ��� ��

int sum(int x, int y)        // sum �Լ� ���� ����
{
	int temp;                // �� ������ ���� ��� ������ ����

	temp = x + y;            // x�� y�� ���� temp�� ����

	return temp;             // temp�� ���� ��ȯ
}                            // sum �Լ��� ��