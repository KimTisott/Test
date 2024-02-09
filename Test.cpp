#pragma warning(disable : 4996)

#include <iostream>
#include "A1.h"

int main()
{
    char fileName[kFileContentSize];
    printf("File Name: ");
    scanf("%s", fileName);

    short packetTotal;
    printf("Packet Total: ");
    scanf("%hd", &packetTotal);

    short packetOrder = 0;
    printf("Packet Order: ");
    scanf("%hd", &packetOrder);

    unsigned char fileContent[kFileContentSize];
    printf("File Content: ");
    scanf("%s", fileContent);

    unsigned char packet[kPacketSize] = {};
    packData(packet, fileName, packetTotal, packetOrder, fileContent);
    char checksum[kChecksumSize] = {};
    generateChecksum(checksum, packet);
    printf("Checksum: %s", checksum);
    
    unpackData(packet, fileName, packetTotal, packetOrder, fileContent);

    printf("\nFile Name: %s", fileName);
    printf("\nPacket Total: %hd", packetTotal);
    printf("\nPacket Order: %hd", packetOrder);
    printf("\nFile Content: %s", fileContent);

    generateChecksum(checksum, packet);
    printf("\nChecksum: %s", checksum);

    return 0;
}