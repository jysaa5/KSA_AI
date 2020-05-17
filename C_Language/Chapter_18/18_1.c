#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	FILE* fp;              

	fp = fopen("a.txt", "r");   
	if (fp == NULL)            
	{
		printf("파일이 열리지 않았습니다.\n");   
		return 1;                  
	}
	printf("파일이 열렸습니다.\n");
	fclose(fp);                      

	return 0;
}