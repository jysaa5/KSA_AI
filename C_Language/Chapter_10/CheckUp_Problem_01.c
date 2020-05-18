#include <stdio.h>

// p.291 

void print_month(int*);

int main(void)
{
	int month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	print_month(month);

	return 0;

}

void print_month(int* mp)
{
	int i;
	int cnt = 0;
	for (i = 0; i < 12; i++)
	{
		printf("%5d", mp[i]);
		cnt++;
		if ((cnt >= 5) && (cnt % 5 == 0))
		{
			printf("\n");

		}

	}
}
