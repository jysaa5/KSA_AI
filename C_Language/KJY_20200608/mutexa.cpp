// mutexa.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//
#include <stdio.h>
#include <windows.h>


int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		printf("usage : %s mutex_name\n", argv[0]);
		exit(0);
	}
	printf("start of program\n");
	char mutex_name1[16] = { 0 };
	char mutex_name2[16] = { 0 };
	strcpy_s(mutex_name1, argv[1]);
	strcpy_s(mutex_name2, argv[2]);
	int i = 0;

	HANDLE hMutex1;
	hMutex1 = CreateMutex(NULL, TRUE, (LPCWSTR)mutex_name1);
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		printf("### MUTEX ALREADY_EXISTS ###, [%s] waiting..\n", mutex_name1);
		WaitForSingleObject(hMutex1, INFINITE);
		printf("### MUTEX ALREADY_EXISTS ###, [%s] allocation & starting..\n", mutex_name1);
	}
	printf("Created %s Mutex\n", mutex_name1);
	printf("working..");
	for (i = 0; i < 10; i++)
	{
		printf(".");
		Sleep(1000);
	}
	printf("\n");

	HANDLE hMutex2;
	hMutex2 = CreateMutex(NULL, TRUE, (LPCWSTR)mutex_name2);
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		printf("### MUTEX ALREADY_EXISTS ###, [%s] waiting..\n", mutex_name2);
		WaitForSingleObject(hMutex2, INFINITE);
		printf("### MUTEX ALREADY_EXISTS ###, [%s] allocation & starting..\n", mutex_name2);
	}
	printf("Created %s Mutex\n", mutex_name2);
	printf("working..");
	for (i = 0; i < 10; i++)
	{
		printf(".");
		Sleep(1000);
	}
	printf("\n");

	ReleaseMutex(hMutex2);
	printf("Release %s Mutex\n", mutex_name2);
	CloseHandle(hMutex2);

	ReleaseMutex(hMutex1);
	printf("Release %s Mutex\n", mutex_name1);
	CloseHandle(hMutex1);

	Sleep(5000);
	printf("end of program\n");

	return 0;
}




