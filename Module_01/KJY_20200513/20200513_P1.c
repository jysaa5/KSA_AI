// scnaf���� �ذ�
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// if��
#define test 0

//int main(void) {
//	printf("Be happy!");
//	return 0;
//}

/*
int main() {

	int num = 100;
	printf("%d\n", num);
	return 0;
}
*/

/*
int main(void)
{

	printf("%d\n", 12);
	printf("%o\n", 12);
	printf("%x\n", 12);
	return 0;
}*/

/*
int main() {
	/*
	int num = 100;
	float fnum = 8.5;
	double dnum = 8.5;

	int arr1[5] = {0, };
	int arr2[5];
	*/
	/*
		char f1[6] = { 'a', 'p', 'p', 'l', 'e' };
		char f2[6] = "apple";
		char* str = "apple";

		f1[0] = 'A';

		//printf("%d\n", num);
		printf("%s\n", str);
		printf("%s\n", f1);

		return 0;
	}
	*/

	/*
	int main(void) {

		int age;
		double height;

		printf("���̿� Ű�� �Է��ϼ���: ");
		scanf_s("%d%lf", &age, &height);
		printf("���̴� %d��, Ű�� %.1lfcm \n", age, height);

		return 0;

	}
	*/

int main(void)
{
	char grade;              // ������ �Է��� ����
	char name[20];           // �̸��� �Է��� �迭

	printf("���� �Է� : ");
	scanf("%c", &grade);     // grade ������ ���� ���� �Է�
	// ���������
	getchar();
	printf("�̸� �Է� : ");
	scanf("%s", name);       // name �迭�� �̸� ���ڿ� �Է�, &�� ������� �ʴ´�.
	printf("%s�� ������ %c�Դϴ�.\n", name, grade);

	return 0;
}
/*
int main(void)
{
	int a = 5, b = 5;
	int pre, post;

	pre = (++a) * 3;
	post = (b++) * 3;

	printf("�ʱⰪ a = %d, b = %d\n", a, b);
	printf("������: (++a)*3 = %d, ������: (b++_) * 3 = % d\n", pre, post);

	return 0;

}
*/

/*
int main(void)
{
	int a = 10;
	int b = 12;
	int result = 0;

#if test

	printf("a&b: %d\n", a & b);
	printf("a^b :", "%d\n", a ^ b);
	printf("a | b : %d\n", a | b);
	printf("~a : %d\n", ~a);
	printf("a<<1 : %d\n", a << 1);
	printf("a>>2 : %d\n", a >> 2);

#else

	int result_add = a & b;
	int result_exor = a ^ b;
	int result_or = a | b;
	int result_not = ~a;
	int result_lshift = a << 1;
	int result_rshift = a >> 2;

	printf("a&b: %d\n", result_add);
	printf("a^b :", "%d\n", result_exor);
	printf("a | b : %d\n", result_or);
	printf("~a : %d\n", result_not);
	printf("a<<1 : %d\n", result_lshift);
	printf("a>>2 : %d\n", result_rshift);

#endif	return 0;


}
*/

