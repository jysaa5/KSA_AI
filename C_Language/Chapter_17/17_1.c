#include <stdio.h>

struct student       
{
	int num;           
	double grade;      
};                      

int main(void)
{
	struct student s1;   

	s1.num = 2;         
	s1.grade = 2.7;      
	printf("�й� : %d\n", s1.num);       
	printf("���� : %.1lf\n", s1.grade);  

	return 0;
}