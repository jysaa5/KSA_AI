#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>  
#include "studentP.h"
#define MAX 1024


int menu()
{
	int num = 0;
	printf("원하시는 메뉴를 선택해주세요\n");
	printf("1. 조장 검색\n");
	printf("2. 회사명 검색\n");
	printf("3. 이름 검색\n");
	printf("4. Email 검색\n");
	printf("5. 학교 검색\n");
	printf("6. 전공 검색\n");
	scanf("%d", &num);

	return num;
}


// 함수 정의
// fileReading 함수: 파일을 읽는 함수
struct studentList* fileReading(void) {

	// 파일 포인터 
	FILE* fp;

	int index = 0, data = 0;

	// 원본 데이터 포인터
	char* inp;

	// 버퍼 사이즈
	int buf_size = MAX * MAX;

	// 포인터
	char* ptr;

	// 문자열이 들어갈 배열 포인터
	char* arry[MAX];

	struct studentList new_list = { NULL };

	struct studentList stack_list[100] = { NULL };

	int i = 0;

	// 파일 열기
	//fp = fopen("C:\\result\\studentListData.csv", "r");
	fp = fopen("C:\\result\\서울반 교육생 명단_한국표준협회.csv", "r");

	// 크기 동적 할당
	inp = malloc(buf_size);


	// fgets: 문자열 입력
	while (fgets(inp, buf_size, fp)) {

		// 함수로 arry 배열의 주소와 입력받은 스트링을 전달.
		new_list = retToken(arry, inp);
		stack_list[i] = new_list;
		i++;
	}

	
	fclose(fp);

	return stack_list;

}

// retToken 함수: 토큰을 기준으로 데이터 절단
struct studentList retToken(char* arry[], char* inp) {

	int i = 0;

	// strtok()을 이용하여 문자열을 ';' 토큰을 기준으로 자름
	// char* ptr = strtok(inp, ";");
	char* ptr = strtok(inp, "??,\n");

	char* line[MAX];
	line[0] = NULL;

	while (ptr != NULL) {

		arry[i] = ptr;
		if (i == 0 && (strcmp(ptr, "조장") != 0) && strcmp(ptr, "조장 여부") != 0) {
			line[0] = "조원";
			line[i + 1] = ptr;
		}
		else if (i == 0 && strcmp(ptr, "조장") == 0 || strcmp(ptr, "조장 여부") == 0) {
			line[i] = ptr;
		}
		else if (strcmp(line[0], "조원") == 0) {
			line[i + 1] = ptr;
		}
		else {
			line[i] = ptr;
		}

		ptr = strtok(NULL, "??,\n");

		i++;

	}

	return inputData(line);
}

// inputData 함수: 구조체에 데이터 저장
struct studentList inputData(char* line[]) {

	struct studentList new_list = { NULL };


	int j = 0;
	char* test[MAX];
	for (j = 0; j < 6; j++) {
		test[j] = line[j];

	}

	strcpy(new_list.leader, test[0]);
	strcpy(new_list.company, test[1]);
	strcpy(new_list.name, test[2]);
	strcpy(new_list.email, test[3]);
	strcpy(new_list.school, test[4]);
	strcpy(new_list.major, test[5]);

	/* strcpy(stack_list[j].leader, new_list.leader);
	 strcpy(stack_list[j].company, new_list.company);
	 strcpy(stack_list[j].name, new_list.name);
	 strcpy(stack_list[j].email, new_list.email);
	 strcpy(stack_list[j].school, new_list.school);
	 strcpy(stack_list[j].major, new_list.major);

	 j++;

	 if (j > 25) {

		 return *stack_list;

	 }
	 */
	return new_list;
}






void searchingLeader(struct studentList* student_list, int list_size, time_t t) {

	int count = 0;
	int i = 0;
	struct studentList data_list[100] = { NULL };

	while (i < list_size) {

		data_list[i] = (student_list)[i];
		i++;
	}

	for (int i = 0; i < list_size; i++) {

		if (strcmp(data_list[i].leader, "조장") == 0) {

			printf("%s %s %s %s %s %s\n", data_list[i].leader, data_list[i].company, data_list[i].name, data_list[i].email, data_list[i].school, data_list[i].major);
			count++;
		}
	}

	if (count == 0) {

		printf("결과가 없습니다.\n");
	}


	//파일 출력
	logFileWriting(data_list, t, count);
}

void searchingCompany(struct studentList* student_list, int list_size, char *input, time_t t) {

	int count = 0;
	int i = 0;
	struct studentList data_list[100] = { NULL };

	while (i < list_size) {

		data_list[i] = (student_list)[i];
		i++;
	}

	for (int i = 0; i < list_size; i++) {

		if (strcmp(data_list[i].company, input) == 0 ) {

			printf("%s %s %s %s %s %s\n", data_list[i].leader, data_list[i].company, data_list[i].name, data_list[i].email, data_list[i].school, data_list[i].major);
			count++;
		}
	}

	if (count == 0) {

		printf("결과가 없습니다.\n");
	}
		
	//파일 출력
	logFileWriting(data_list, t, count);
}

void searchingName(struct studentList* student_list, int list_size, char *input, time_t t) {

	int count = 0;
	int i = 0;
	struct studentList data_list[100] = { NULL };

	while (i < list_size) {

		data_list[i] = (student_list)[i];
		i++;
	}

	for (int i = 0; i < list_size; i++) {

		if (strcmp(data_list[i].name, input) == 0) {

			printf("%s %s %s %s %s %s\n", data_list[i].leader, data_list[i].company, data_list[i].name, data_list[i].email, data_list[i].school, data_list[i].major);
			count++;
		}
	}

	//파일 출력
	logFileWriting(data_list, t, count);
}

void searchingEmail(struct studentList* student_list, int list_size, char *input, time_t t) {

	int count = 0;
	int i = 0;
	struct studentList data_list[100] = { NULL };

	while (i < list_size) {

		data_list[i] = (student_list)[i];
		i++;
	}

	for (int i = 0; i < list_size; i++) {

		if (strcmp(data_list[i].email, input) == 0) {

			printf("%s %s %s %s %s %s\n", data_list[i].leader, data_list[i].company, data_list[i].name, data_list[i].email, data_list[i].school, data_list[i].major);
			count++;
		}
	}

	//파일 출력
	logFileWriting(data_list, t, count);
}

void searchingSchool(struct studentList* student_list, int list_size, char *input, time_t t) {

	int count = 0;
	int i = 0;
	struct studentList data_list[100] = { NULL };

	while (i < list_size) {

		data_list[i] = (student_list)[i];
		i++;
	}

	for (int i = 0; i < list_size; i++) {

		if (strcmp(data_list[i].school, input) == 0) {

			printf("%s %s %s %s %s %s\n", data_list[i].leader, data_list[i].company, data_list[i].name, data_list[i].email, data_list[i].school, data_list[i].major);
			count++;
		}
	}

	//파일 출력
	logFileWriting(data_list, t, count);
}

void searchingMajor(struct studentList* student_list, int list_size, char *input, time_t t) {

	int count = 0;
	int i = 0;
	struct studentList data_list[100] = { NULL };

	while (i < list_size) {

		data_list[i] = (student_list)[i];
		i++;
	}

	for (int i = 0; i < list_size; i++) {

		if (strcmp(data_list[i].major, input) == 0) {

			printf("%s %s %s %s %s %s\n", data_list[i].leader, data_list[i].company, data_list[i].name, data_list[i].email, data_list[i].school, data_list[i].major);
			count++;
		}
	}

	//파일 출력
	logFileWriting(data_list, t, count);
}



void logFileWriting(struct studentList *list, time_t time, int count)
{
	FILE* ofp;
	int i= 0;

	//출력할 파일
	ofp = fopen("C:\\result\\result.txt", "w");

	if (ofp == NULL)
	{
		printf("출력 파일을 열지 못했습니다\n");
	}


	//최상단 행
	//fprintf(ofp, "%3s%7s%5s%20s%20s%30s%20s", "팀원", "기업", "성함", "이메일", "학교", "전공");

	//파일에 list와 time 출력
	for (i = 0; i < count; i++)
	{
		fprintf(ofp, "%s %s %s %s %s %s %s\n", list[i].leader, list[i].company, list[i].name, list[i].email, list[i].school, list[i].major, ctime(&time));

	};

	fclose(ofp);


}
