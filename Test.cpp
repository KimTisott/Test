#pragma warning(disable : 4996)

#include <iostream>
#include "A1.h"

int main()
{
 /*   char fileName[5];
    printf("File Name: ");
    scanf("%s", fileName);

    short packetTotal = 0;
    printf("Packet Total: ");
    scanf("%d", &packetTotal);

    short packetOrder = 0;
    printf("Packet Order: ");
    scanf("%d", &packetOrder);*/

    char fileContent[50];
    printf("File Content: ");
    scanf("%s", fileContent);

    //char* packet = packData(fileName, packetTotal, packetOrder, fileContent);

    // Call generateChecksum
    char* senderChecksum = generateChecksum(fileContent, 100);

    // Simulate receiving the checksum
    bool isChecksumEqual = checkChecksum(fileContent, senderChecksum, 100);

    if (isChecksumEqual)
    {
        printf("They are equal");
    }
    else {
        printf("They are NOT equal");
    }


    free(senderChecksum); // Free memory allocated by generateChecksum


    //printf("Packet: %s (%d)", packet, strlen(packet));

    return 0;
}