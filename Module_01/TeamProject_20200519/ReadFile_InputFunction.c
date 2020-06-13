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

// �Լ� ����
// ���� �б�
// ��ȯ��: int
struct studentList *fileReading(void);

// ������ ��ū ���� �� ����  
// arry[]: �ڸ� ������ ���� �迭
// ptr: ������
// ��ȯ��: int
//int retToken(char* arry[], char* ptr);
struct studentList retToken(char* arry[], char* ptr);

// ����ü�� ������ ����
// ��ȯ��: studentList�� ������
struct studentList inputData(char arry[]);

// ��ü ����Ʈ ���� ��ȯ


int main(void) {

    int k = 0;
    int list_size = 0;
    // ����ü ����Ʈ ���� -> ���� �Ҵ��� ��� �ؾ� ����? 
    struct studentList fileList[100] = {NULL};

    // ���� �б�� ����ü�� ����
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


// �Լ� ����
// fileReading �Լ�: ������ �д� �Լ�
struct studentList  *fileReading(void) {

    // ���� ������ 
    FILE* fp;

    int index = 0, data = 0;

    // ���� ������ ������
    char* inp;

    // ���� ������
    int buf_size = MAX * MAX;

    // ������
    char* ptr;

    // ���ڿ��� �� �迭 ������
    char* arry[MAX];

    struct studentList new_list = { NULL };

    struct studentList stack_list[100] = {NULL};

    int i = 0;

    // ���� ����
    fp = fopen("C:\\result\\studentListData.csv", "r");
    //fp = fopen("C:\\result\\����� ������ ���_�ѱ�ǥ����ȸ.csv", "r");

    // ũ�� ���� �Ҵ�
    inp = malloc(buf_size);


    // fgets: ���ڿ� �Է�
    while (fgets(inp, buf_size, fp)) {

        // �Լ��� arry �迭�� �ּҿ� �Է¹��� ��Ʈ���� ����. 
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

// retToken �Լ�: ��ū�� �������� ������ ����
struct studentList retToken(char* arry[], char* inp) {

    int i = 0;

    // strtok()�� �̿��Ͽ� ���ڿ��� ';' ��ū�� �������� �ڸ�
    // char* ptr = strtok(inp, ";");
    char* ptr = strtok(inp, "??,\n");

    char* line[MAX];
    line[0] = NULL;

    while (ptr != NULL) {

        arry[i] = ptr;
        if (i==0&&(strcmp(ptr, "����") != 0) && strcmp(ptr, "���� ����") != 0) {
            line[0] = "����";
            line[i + 1] = ptr;
        }
        else if(i == 0 && strcmp(ptr, "����") == 0 || strcmp(ptr, "���� ����") == 0){
            line[i] = ptr;
        }
        else if (strcmp(line[0], "����") == 0) {
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

    
    //if ((strcmp(line[0], "����") != 0) && strcmp(line[0], "���� ����") != 0) {
    //    for (int j = 0; j < 4; j++) {
    //        strcpy(line[5 - j], line[4 - j]);

    //    }
    //    strcpy(line[0], "����");
    //}


    //inputData(line);
    //return i;
    return inputData(line);
}

// inputData �Լ�: ����ü�� ������ ����
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

