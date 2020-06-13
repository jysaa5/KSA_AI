// scnaf에러 해결
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// if문
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

		printf("나이와 키를 입력하세요: ");
		scanf_s("%d%lf", &age, &height);
		printf("나이는 %d살, 키는 %.1lfcm \n", age, height);

		return 0;

	}
	*/

int main(void)
{
	char grade;              // 학점을 입력할 변수
	char name[20];           // 이름을 입력할 배열

	printf("학점 입력 : ");
	scanf("%c", &grade);     // grade 변수에 학점 문자 입력
	// 버퍼지우기
	getchar();
	printf("이름 입력 : ");
	scanf("%s", name);       // name 배열에 이름 문자열 입력, &를 사용하지 않는다.
	printf("%s의 학점은 %c입니다.\n", name, grade);

	return 0;
}
/*
int main(void)
{
	int a = 5, b = 5;
	int pre, post;

	pre = (++a) * 3;
	post = (b++) * 3;

	printf("초기값 a = %d, b = %d\n", a, b);
	printf("전위형: (++a)*3 = %d, 후위형: (b++_) * 3 = % d\n", pre, post);

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

