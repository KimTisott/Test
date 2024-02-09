#pragma warning(disable : 4996)

#include <iostream>
#include "A1.h"

int main()
{
    char *fileName = (char*)malloc(5);
    printf("File Name: ");
    scanf("%s", fileName);

    short packetTotal = 0;
    printf("Packet Total: ");
    scanf("%d", &packetTotal);

    short packetOrder = 0;
    printf("Packet Order: ");
    scanf("%d", &packetOrder);

    char *fileContent = (char*)malloc(5);
    printf("File Content: ");
    scanf("%s", fileContent);

    char* packet = packData(fileName, packetTotal, packetOrder, fileContent, 5);
    for (int i = 0; i < 100; i++)
    {
        printf("p[%d]: %c\n", i, packet[i]);
    }

    return 0;
}