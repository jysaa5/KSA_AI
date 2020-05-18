
struct teamList
{
	int id;
	char team[80];
	char company[80];
};

int menu(void);
struct teamList* input(int);
void sortingSelect(struct teamList[], int, int);
void printingList(struct teamList*, int, int);
void bubbleSorting(struct teamList[], int, int, int);
void fileWriting(struct teamList* list, int count);
//void fileReading();