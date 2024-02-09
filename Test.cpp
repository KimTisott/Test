#pragma warning(disable : 4996)

#include <iostream>
#include "A1.h"

int main()
{
    char iFileName[kFileNameSize + 1];
    printf("File Name: ");
    scanf("%s", iFileName);

    unsigned short iPacketTotal;
    printf("Packet Total: ");
    scanf("%hd", &iPacketTotal);

    unsigned short iPacketOrder;
    printf("Packet Order: ");
    scanf("%hd", &iPacketOrder);

    unsigned char iFileContent[kFileContentSize];
    printf("File Content: ");
    scanf("%s", iFileContent);

    unsigned char iPacket[kPacketSize];
    packData(iPacket, iFileName, iPacketTotal, iPacketOrder, iFileContent);
    
    char oFileName[kFileNameSize + 1];
    unsigned short oPacketTotal = 0;
    unsigned short oPacketOrder = 0;
    unsigned char oFileContent[kFileContentSize];
    char oChecksum[kChecksumSize + 1];
    unpackData(iPacket, oFileName, &oPacketTotal, &oPacketOrder, oFileContent, oChecksum);

    printf("\nFile Name: %s", oFileName);
    printf("\nPacket Total: %hd", oPacketTotal);
    printf("\nPacket Order: %hd", oPacketOrder);
    printf("\nFile Content: %s", oFileContent);
    printf("\nChecksum: %s", oChecksum);

    printf("\nOK: %d", compareChecksum(oChecksum, iPacket));

    return 0;
}