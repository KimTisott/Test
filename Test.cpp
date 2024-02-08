#pragma warning(disable : 4996)

#include <iostream>
#include "A1.h"

int main()
{
    char fileName[5];
    printf("File Name: ");
    scanf("%s", fileName);

    short packetTotal = 0;
    printf("Packet Total: ");
    scanf("%d", &packetTotal);

    short packetOrder = 0;
    printf("Packet Order: ");
    scanf("%d", &packetOrder);

    char fileContent[50];
    printf("File Content: ");
    scanf("%s", fileContent);

    char* packet = packData(fileName, packetTotal, packetOrder, fileContent);
    printf("Packet: %s (%d)", packet, strlen(packet));

    return 0;
}