#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


struct string_a {
	char id[10];
};


int check(struct string_a**);



int main(void)
{
	struct string_a a[5] = {"aa", "bb", "cc", "dd", "ee"};
	struct string_a* pa[5] = { &a[0], &a[1], &a[2], &a[3], &a[4] };




	check(pa);



	return 0;
}

int check(struct string_a** pa)
{
	struct string_a list[5] = {"a"};

	for (int i = 0; i < 5; i++)
	{
		strcpy(list[i].id, (*pa[i]).id);
	}
	


	return 0;
}