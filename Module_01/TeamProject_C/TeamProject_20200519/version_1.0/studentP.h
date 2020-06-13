
// 구조체 선언
struct studentList
{
	char leader[20];
	char company[20];
	char name[20];
	char email[20];
	char school[30];
	char major[60];

};


// 함수 선언
//input
struct studentList* fileReading(void);
struct studentList retToken(char* arry[], char* ptr);
struct studentList inputData(char arry[]);
//search
void searchingLeader(struct studentList* student_list, int list_size, time_t t);
void searchingCompany(struct studentList* student_list, int list_size, char *input, time_t t);
void searchingName(struct studentList* student_list, int list_size, char *input, time_t t);
void searchingEmail(struct studentList* student_list, int list_size, char *input, time_t t);
void searchingSchool(struct studentList* student_list, int list_size, char *input, time_t t);
void searchingMajor(struct studentList* student_list, int list_size, char *input, time_t t);
int menu();
//output
void logFileWriting(struct studentList*, time_t, int);
