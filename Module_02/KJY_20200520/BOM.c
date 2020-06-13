#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a = 99999;
    printf("Memory Allocation Order : ");
    printf("%02X ", ((unsigned char*)&a)[0]);
    printf("%02X ", ((unsigned char*)&a)[1]);
    printf("%02X ", ((unsigned char*)&a)[2]);
    printf("%02X ", ((unsigned char*)&a)[3]);
    printf("\n");
    return 0;
}