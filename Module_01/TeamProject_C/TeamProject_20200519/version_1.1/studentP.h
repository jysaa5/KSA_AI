
//구조체 선언
struct studentList
{
	char leader[20];
	char company[20];
	char name[20];
	char email[50];
	char school[30];
	char major[60];

};


// 함수 선언
//input
int getFileSize(char* fir);
struct studentList fileLineReading(FILE* fp);
struct studentList retToken(char* ptr);
struct studentList inputData(char** line);
void menu(struct studentList* student_list, int list_size);
//search
void searchingLeader(struct studentList* student_list, int list_size, time_t t);
void searchingCompany(struct studentList* student_list, int list_size, char *input, time_t t);
void searchingName(struct studentList* student_list, int list_size, char *input, time_t t);
void searchingEmail(struct studentList* student_list, int list_size, char *input, time_t t);
void searchingSchool(struct studentList* student_list, int list_size, char *input, time_t t);
void searchingMajor(struct studentList* student_list, int list_size, char *input, time_t t);
void searchResultPrintf(struct studentList* result_list, int count);
//output
void fileWriting(struct studentList*, time_t, int);
