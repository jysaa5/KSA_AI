﻿// 소스 파일 – main.c
#include <stdio.h>           
#include "student.h"         

int main(void)
{
	Student a = { 315, "홍길동" };   

	printf("학번 : %d, 이름 : %s\n", a.num, a.name);  

	return 0;
}