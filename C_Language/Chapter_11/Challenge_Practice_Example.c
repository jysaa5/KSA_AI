#include<stdio.h>

// p.315

int main(void)
{
	int ch = 0;
	int cnt = 0;
	int max = 0;

	while (1) {


		ch = getchar();

		if (ch == -1) {

			break;

		}

		if (ch != '\0') {

			while (ch != '\n')
			{
				if ((97 <= ch) && (ch <= 122)) {

					cnt++;
				}
				ch = getchar();
			}
		}

		if (max < cnt) {
			max = cnt;
		}
		cnt = 0;
	}

	printf("°¡Àå ±ä ´Ü¾îÀÇ ±æÀÌ: %d", max);

	return 0;
}