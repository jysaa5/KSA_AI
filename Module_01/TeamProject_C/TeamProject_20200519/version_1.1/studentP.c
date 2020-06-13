#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>  
#include "studentP.h"

#define MAX 1024
#define COL 6
#define MAX_DATA_LEN 60


void menu(struct studentList* student_list, int list_size)
{
	//변수 선언
	int select_num = 0;
	char input[MAX_DATA_LEN];
	time_t t[MAX];
	char ans = 0;
	int k = 1;
	int i = 0;


	//메뉴 실행
	while (k) {

		//메뉴 선택
		printf("원하시는 메뉴를 선택해주세요\n");
		printf("1. 조장 검색\n");
		printf("2. 회사명 검색\n");
		printf("3. 이름 검색\n");
		printf("4. Email 검색\n");
		printf("5. 학교 검색\n");
		printf("6. 전공 검색\n");
		scanf("%d", &select_num);
		getchar();



		switch (select_num) {

		case 1:
			t[i] = time(NULL);


			//검색 함수
			searchingLeader(student_list, list_size, t);

			break;

		case 2:
			//검색할 데이터 입력받기
			printf("\n검색하고자 하는 회사명을 입력해주세요.\n");
			scanf("%s", &input);
			getchar();
			t[i] = time(NULL);


			//검색 함수
			searchingCompany(student_list, list_size, input, t);

			break;

		case 3:
			//검색할 데이터 입력받기
			printf("\n검색하고자 하는 이름을 입력해주세요.\n");
			scanf("%s", &input);
			getchar();
			t[i] = time(NULL);


			//검색 함수
			searchingName(student_list, list_size, input, t);

			break;

		case 4:
			//검색할 데이터 입력받기
			printf("\n검색하고자 하는 E-mail을 입력해주세요.\n");
			scanf("%s", &input);
			getchar();
			t[i] = time(NULL);


			//검색 함수
			searchingEmail(student_list, list_size, input, t);

			break;

		case 5:
			//검색할 데이터 입력받기
			printf("\n검색하고자 하는 학교를 입력해주세요.\n");
			scanf("%s", &input);
			getchar();
			t[i] = time(NULL);


			//검색 함수
			searchingSchool(student_list, list_size, input, t);

			break;

		case 6:
			//검색할 데이터 입력
			printf("\n검색하고자 하는 전공을 입력해주세요.\n");
			scanf("%s", &input);
			getchar();
			t[i] = time(NULL);


			//검색 함수
			searchingMajor(student_list, list_size, input, t);

			break;

		default:
			break;
		}

		i++;

		//프로그램 종료
		printf("\n프로그램을 종료하시겠습니까?(y/n) : ");
		ans = getchar();

		if (ans == 'y')
			k = 0;;

	}
}


//파일 라인 크기를 반환하는 함수
int getFileSize(char* dir)
{
	//변수 선언
	FILE* fp = fopen(dir, "r");
	char* str = 0;
	int buf_size = MAX * MAX;
	int line_count = 0;

	// 크기 동적 할당
	str = (char*)malloc(buf_size);

	//동적 할당에 사용할 파일 크기 측정
	while (fgets(str, buf_size, fp)) {

		line_count++;

	}

	free(str);
	fclose(fp);
	return line_count;

}


// 함수 정의
// fileReading 함수: 파일을 읽는 함수
struct studentList fileLineReading(FILE* fp) {

	//변수 선언
	// 원본 데이터 포인터
	char* str;
	int buf_size = MAX * MAX;
	char* ptr;
	int line_count = 0;
	int i = 0;


	// 크기 동적 할당
	str = (char*)malloc(buf_size);


	//반환할 데이터 목록
	struct studentList line;


	//파일 한줄을 읽고, 토큰 함수로 잘라
	//구조체에 저장
	ptr = fgets(str, buf_size, fp);
	line = retToken(ptr);


	//메모리 반환
	free(str);

	return line;

}

// retToken 함수: 토큰을 기준으로 데이터 절단
struct studentList retToken(char* ptr) {

	int i = 0;
	// strtok()을 이용하여 문자열을 ';' 토큰을 기준으로 자름
	// char* ptr = strtok(inp, ";");
	char* ptoken = strtok(ptr, "??,\n");
	char* line[COL] = { NULL };



	//토큰으로 잘려진 데이터를
	//구조체에 저장
	while (ptoken != NULL) {

		if (i == 0 && (strcmp(ptoken, "조장") != 0) && strcmp(ptoken, "조장 여부") != 0) {
			line[0] = "조원";
			line[i + 1] = ptoken;
		}
		else if (i == 0 && strcmp(ptoken, "조장") == 0 || strcmp(ptoken, "조장 여부") == 0) {
			line[i] = ptoken;
		}
		else if (strcmp(line[0], "조원") == 0) {
			line[i + 1] = ptoken;
		}
		else {
			line[i] = ptoken;
		}

		ptoken = strtok(NULL, "??,\"\n");

		i++;

	}



	return inputData(line);
}



// inputData 함수: 구조체에 데이터 저장
struct studentList inputData(char** line) {


	struct studentList list_line;


	strcpy(list_line.leader, line[0]);
	strcpy(list_line.company, line[1]);
	strcpy(list_line.name, line[2]);
	strcpy(list_line.email, line[3]);
	strcpy(list_line.school, line[4]);
	strcpy(list_line.major, line[5]);


	return list_line;
}





//조장 검색 함수
void searchingLeader(struct studentList* student_list, int list_size, time_t t) {

	//변수 선언
	int count = 0;
	int i, j = 0;

	//검색한 데이터 count
	for (int i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].leader, "조장") == 0) {
			count++;
		}
	}


	//검색 결과 크기에 맞는
	//메모리 동적 할당
	struct studentList* result_list = (struct studentList*) malloc(sizeof(struct studentList) * count);

	//검색 결과
	//구조체에 저장
	for (i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].leader, "조장") == 0) {

			strcpy(result_list[j].leader, student_list[i].leader);
			strcpy(result_list[j].company, student_list[i].company);
			strcpy(result_list[j].name, student_list[i].name);
			strcpy(result_list[j].email, student_list[i].email);
			strcpy(result_list[j].school, student_list[i].school);
			strcpy(result_list[j].major, student_list[i].major);

			j++;
		}
	}


	//검색 결과 출력
	searchResultPrintf(result_list, count);


	//파일 출력
	fileWriting(result_list, t, count);


	//메모리 반환
	free(result_list);
}



//기업 검색
void searchingCompany(struct studentList* student_list, int list_size, char* input, time_t t) {

	//변수 선언
	int count = 0;
	int i, j = 0;


	//검색 결과 count
	for (int i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].company, input) == 0) {
			count++;
		}
	}


	//검색 결과 크기에 맞는
	//메모리 동적 할당
	struct studentList* result_list = (struct studentList*) malloc(sizeof(struct studentList) * count);

	//검색 결과
	//구조체에 저장
	for (i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].company, input) == 0) {

			strcpy(result_list[j].leader, student_list[i].leader);
			strcpy(result_list[j].company, student_list[i].company);
			strcpy(result_list[j].name, student_list[i].name);
			strcpy(result_list[j].email, student_list[i].email);
			strcpy(result_list[j].school, student_list[i].school);
			strcpy(result_list[j].major, student_list[i].major);

			j++;
		}
	}


	//검색 결과 출력
	searchResultPrintf(result_list, count);

	//파일 출력
	fileWriting(result_list, t, count);

	//메모리 반환
	free(result_list);
}



//이름 검색
void searchingName(struct studentList* student_list, int list_size, char* input, time_t t) {

	//변수 선언
	int count = 0;
	int i, j = 0;


	//검색 결과 count
	for (int i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].name, input) == 0) {
			count++;
		}
	}


	//검색 결과 크기에 맞는
	//메모리 동적 할당
	struct studentList* result_list = (struct studentList*) malloc(sizeof(struct studentList) * count);

	//검색 결과
	//구조체에 저장
	for (i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].name, input) == 0) {

			strcpy(result_list[j].leader, student_list[i].leader);
			strcpy(result_list[j].company, student_list[i].company);
			strcpy(result_list[j].name, student_list[i].name);
			strcpy(result_list[j].email, student_list[i].email);
			strcpy(result_list[j].school, student_list[i].school);
			strcpy(result_list[j].major, student_list[i].major);

			j++;

		}
	}

	//검색 결과 출력
	searchResultPrintf(result_list, count);

	//파일 출력
	fileWriting(result_list, t, count);

	//메모리 반환
	free(result_list);
}


//이메일 검색 함수
void searchingEmail(struct studentList* student_list, int list_size, char* input, time_t t) {

	//변수 선언
	int count = 0;
	int i, j = 0;


	//검색 결과 count
	for (int i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].email, input) == 0) {
			count++;
		}
	}


	//검색 결과 크기에 맞는
	//메모리 동적 할당
	struct studentList* result_list = (struct studentList*) malloc(sizeof(struct studentList) * count);

	//검색 결과
	//구조체에 저장
	for (i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].email, input) == 0) {

			strcpy(result_list[j].leader, student_list[i].leader);
			strcpy(result_list[j].company, student_list[i].company);
			strcpy(result_list[j].name, student_list[i].name);
			strcpy(result_list[j].email, student_list[i].email);
			strcpy(result_list[j].school, student_list[i].school);
			strcpy(result_list[j].major, student_list[i].major);

			j++;
		}
	}

	//검색 결과 출력
	searchResultPrintf(result_list, count);

	//파일 출력
	fileWriting(result_list, t, count);

	//메모리 반환
	free(result_list);
}


//학교 검색 함수
void searchingSchool(struct studentList* student_list, int list_size, char* input, time_t t) {

	//변수 선언
	int count = 0;
	int i, j = 0;

	//검색 결과 count
	for (int i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].school, input) == 0) {
			count++;
		}
	}


	//검색 결과 크기에 맞는
	//메모리 동적 할당
	struct studentList* result_list = (struct studentList*) malloc(sizeof(struct studentList) * count);

	//검색 결과
	//구조체에 저장
	for (i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].school, input) == 0) {

			strcpy(result_list[j].leader, student_list[i].leader);
			strcpy(result_list[j].company, student_list[i].company);
			strcpy(result_list[j].name, student_list[i].name);
			strcpy(result_list[j].email, student_list[i].email);
			strcpy(result_list[j].school, student_list[i].school);
			strcpy(result_list[j].major, student_list[i].major);

			j++;
		}
	}

	//검색 결과 출력
	searchResultPrintf(result_list, count);

	//파일 출력
	fileWriting(result_list, t, count);

	//메모리 반환
	free(result_list);
}



//전공 검색 함수
void searchingMajor(struct studentList* student_list, int list_size, char* input, time_t t)
{
	//변수 선언
	int count = 0;
	int i, j = 0;


	//검색 결과 count
	for (int i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].major, input) == 0) {
			count++;
		}
	}


	//검색 결과 크기에 맞는
	//메모리 동적 할당
	struct studentList* result_list = (struct studentList*) malloc(sizeof(struct studentList) * count);

	//검색 결과
	//구조체에 저장
	for (i = 0; i < list_size; i++) {

		if (strcmp(student_list[i].major, input) == 0) {

			strcpy(result_list[j].leader, student_list[i].leader);
			strcpy(result_list[j].company, student_list[i].company);
			strcpy(result_list[j].name, student_list[i].name);
			strcpy(result_list[j].email, student_list[i].email);
			strcpy(result_list[j].school, student_list[i].school);
			strcpy(result_list[j].major, student_list[i].major);

			j++;
		}
	}


	//검색 결과 출력
	searchResultPrintf(result_list, count);


	//파일 출력
	fileWriting(result_list, t, count);


	//메모리 반환
	free(result_list);
}



//검색 결과 출력 함수
void searchResultPrintf(struct studentList* result_list, int count)
{
	//변수 선언
	int i = 0;


	//검색 결과를 출력하는 반복문
	printf("\n검색 결과 입니다.\n\n");
	for (i; i < count; i++)
	{
		printf("%s ", result_list[i].leader);
		printf("%s ", result_list[i].company);
		printf("%s ", result_list[i].name);
		printf("%s ", result_list[i].email);
		printf("%s ", result_list[i].school);
		printf("%s\n", result_list[i].major);
	}
}



//파일 출력 함수
void fileWriting(struct studentList* list, time_t time, int count)
{
	//변수 선언
	FILE* ofp;
	int i = 0;

	//출력할 파일
	ofp = fopen("C:\\result\\result.txt", "a");

	if (ofp == NULL)
	{
		printf("출력 파일을 열지 못했습니다\n");
	}


	//검색한 결과와 검색시간을
	//파일로 출력
	for (i = 0; i < count; i++)
	{
		fprintf(ofp, "%s ", list[i].leader);
		fprintf(ofp, "%s ", list[i].company);
		fprintf(ofp, "%s ", list[i].name);
		fprintf(ofp, "%s ", list[i].email);
		fprintf(ofp, "%s ", list[i].school);
		fprintf(ofp, "%s ", list[i].major);
		fprintf(ofp, "%s\n", ctime(&time));
	};

	//포인터 반환
	fclose(ofp);
}