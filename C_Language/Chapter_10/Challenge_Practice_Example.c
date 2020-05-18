#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

// p.292
// 로또 번호 생성 프로그램

// 배열에 로또 번호를 입력하는 함수
void input_nums(int* lotto_nums);

// 배열에 저장된 값을 출력하는 함수
void print_nums(int* lotto_nums);


int main(void)
{
	// 로또 번호를 저장할 배열
	int lotto_nums[6] = { 0 };

	// 입력 함수 호출
	input_nums(lotto_nums);

	// 출력 함수 호출
	print_nums(lotto_nums);

	return 0;
}


void input_nums(int* lotto_nums)
{
	int num = 0;
	int cnt = 0;

	while (1) {

		printf("번호 입력:");
		scanf_s("%d", &num);

		for (int i = 0; i < 6; i++) {

			if (lotto_nums[i] == num) {

				printf("같은 번호가 있습니다!\n");
				break;

			}
			else if (lotto_nums[i] == 0) {

				lotto_nums[i] = num;
				cnt++;
				break;

			}
		}

		if (cnt == 6) {
			break;
		}
	}

}

void print_nums(int* lotto_nums)
{
	printf("로또 번호: ");
	for (int i = 0; i < 6; i++)
	{
		printf("%d\t", lotto_nums[i]);
	}
}