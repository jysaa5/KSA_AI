#include<stdio.h>

// p.314

int main(void)
{
	// ���ڸ� �Է��� ����
	int ch;

	// �ҹ����� ������ �� ����
	int cnt = 0;

	ch = getchar();

	while (ch != '\n')
	{
		if ((97 <= ch) && (ch <= 122)) {

			cnt++;
		}
		ch = getchar();
	}

	printf("�ҹ����� ����: %d\n", cnt);

	return 0;
}