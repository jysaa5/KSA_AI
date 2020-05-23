#define _CRT_SECURE_NO_WARNINGS
#define MAX 1024
#include <stdio.h>
#include <string.h>
#include <stdlib.h>  


struct studentList
{
	//int leader;
    char leader[20];
	char company[20];
	char name[20];
	char email[20];
	char school[30];
	char major[60];

};

// 함수 선언
// 파일 읽기
// 반환형: int
struct studentList *fileReading(void);

// 데이터 토큰 구별 후 저장  
// arry[]: 자른 데이터 저장 배열
// ptr: 포인터
// 반환형: int
//int retToken(char* arry[], char* ptr);
struct studentList retToken(char* arry[], char* ptr);

// 구조체에 데이터 저장
// 반환형: studentList의 포인터
struct studentList inputData(char arry[]);

// 전체 리스트 개수 반환


int main(void) {

    int k = 0;
    int list_size = 0;
    // 구조체 리스트 선언 -> 동적 할당을 어떻게 해야 할지? 
    struct studentList fileList[100] = {NULL};

    // 파일 읽기와 구조체에 저장
    for (k = 0; k < 100; k++) {
        fileList[k] = fileReading()[k];
    }

    //fileList->leader = inputData()
    for (k = 0; k < 25; k++) {
        printf("%s\n", fileList[k].leader);
        printf("%s\n", fileList[k].company);
        printf("%s\n", fileList[k].name);
        printf("%s\n", fileList[k].email);
        printf("%s\n", fileList[k].school);
        printf("%s\n", fileList[k].major);
    }

    while (strcmp(fileList[k].leader, NULL) != 0) {
        k++;
        list_size++;
    }

    printf("%d\n",sizeof(fileList)/ sizeof(fileList)[0]);
    printf("%d\n", list_size);
}


// 함수 정의
// fileReading 함수: 파일을 읽는 함수
struct studentList  *fileReading(void) {

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

    struct studentList stack_list[100] = {NULL};

    int i = 0;

    // 파일 열기
    fp = fopen("C:\\result\\studentListData.csv", "r");
    //fp = fopen("C:\\result\\서울반 교육생 명단_한국표준협회.csv", "r");

    // 크기 동적 할당
    inp = malloc(buf_size);


    // fgets: 문자열 입력
    while (fgets(inp, buf_size, fp)) {

        // 함수로 arry 배열의 주소와 입력받은 스트링을 전달. 
        //index = retToken(arry, inp);
        new_list  = retToken(arry, inp);
        stack_list[i] = new_list;
        i++;
    }

    //for (data = 0; data < index; data++) {

    //    printf("%s \n", arry[data]);

    //}
   
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
        if (i==0&&(strcmp(ptr, "조장") != 0) && strcmp(ptr, "조장 여부") != 0) {
            line[0] = "조원";
            line[i + 1] = ptr;
        }
        else if(i == 0 && strcmp(ptr, "조장") == 0 || strcmp(ptr, "조장 여부") == 0){
            line[i] = ptr;
        }
        else if (strcmp(line[0], "조원") == 0) {
            line[i+1] = ptr;
        }
        else {
            line[i] = ptr;
        }

        //line[i] = ptr;
        //ptr = strtok(NULL, ";");
        ptr = strtok(NULL, "??,\n");

        i++;

    }

    
    //if ((strcmp(line[0], "조장") != 0) && strcmp(line[0], "조장 여부") != 0) {
    //    for (int j = 0; j < 4; j++) {
    //        strcpy(line[5 - j], line[4 - j]);

    //    }
    //    strcpy(line[0], "조원");
    //}


    //inputData(line);
    //return i;
    return inputData(line);
}

// inputData 함수: 구조체에 데이터 저장
struct studentList inputData(char *line[]) {

    struct studentList new_list = {NULL};

    //struct studentList stack_list[100] = {NULL};

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

