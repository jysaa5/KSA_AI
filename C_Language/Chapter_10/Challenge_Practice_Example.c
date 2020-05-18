#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

// p.292
// �ζ� ��ȣ ���� ���α׷�

// �迭�� �ζ� ��ȣ�� �Է��ϴ� �Լ�
void input_nums(int* lotto_nums);

// �迭�� ����� ���� ����ϴ� �Լ�
void print_nums(int* lotto_nums);


int main(void)
{
	// �ζ� ��ȣ�� ������ �迭
	int lotto_nums[6] = { 0 };

	// �Է� �Լ� ȣ��
	input_nums(lotto_nums);

	// ��� �Լ� ȣ��
	print_nums(lotto_nums);

	return 0;
}


void input_nums(int* lotto_nums)
{
	int num = 0;
	int cnt = 0;

	while (1) {

		printf("��ȣ �Է�:");
		scanf_s("%d", &num);

		for (int i = 0; i < 6; i++) {

			if (lotto_nums[i] == num) {

				printf("���� ��ȣ�� �ֽ��ϴ�!\n");
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
	printf("�ζ� ��ȣ: ");
	for (int i = 0; i < 6; i++)
	{
		printf("%d\t", lotto_nums[i]);
	}
}