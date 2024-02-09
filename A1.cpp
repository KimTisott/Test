#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "A1.h"
#include "hash-library/md5.h"
#include "hash-library/md5.cpp"

int validateFilename(char* fileName)
{
    if (strlen(fileName) > kFileNameSize)
    {
        return FILENAME_TOOLONG;
    }

    for (int i = 0; i < sizeof(kInvalidFilenameChars); i++)
    {
        char invalidChar = kInvalidFilenameChars[i];
        if (strchr(fileName, invalidChar) != NULL)
        {
            return FILENAME_INVALIDCHARACTERS;
        }
    }
}

void packData(unsigned char packet[kPacketSize], char fileName[kFileNameSize], short packetTotal, short packetOrder, unsigned char fileContent[kFileContentSize])
{
    memcpy(packet + kUdpHeaderSize, fileName, kFileNameSize);
    memcpy(packet + kUdpHeaderSize + kFileNameSize, &packetTotal, kPacketTotalSize);
    memcpy(packet + kUdpHeaderSize + kFileNameSize + kPacketTotalSize, &packetOrder, kPacketOrderSize);
    memcpy(packet + kUdpHeaderSize + kFileNameSize + kPacketTotalSize + kPacketOrderSize, fileContent, kFileContentSize);
    char checksum[kChecksumSize + 1];
    generateChecksum(checksum, packet);
    checksum[kChecksumSize] = '\0';
    printf("Checksum: %s", checksum);
    memcpy(packet + kUdpHeaderSize + kFileNameSize + kPacketTotalSize + kPacketOrderSize + kFileContentSize, checksum, kChecksumSize);
}

void unpackData(unsigned char packet[kPacketSize], char fileName[kFileNameSize + 1], unsigned short *packetTotal, unsigned short *packetOrder, unsigned char fileContent[kFileContentSize], char checksum[kChecksumSize + 1])
{
    memcpy(fileName, packet + kUdpHeaderSize, kFileNameSize);
    fileName[kFileNameSize] = '\0';
    *packetTotal = packet[kUdpHeaderSize + kFileNameSize];
    *packetTotal += packet[kUdpHeaderSize + kFileNameSize + 1] << 8;
    *packetOrder = packet[kUdpHeaderSize + kFileNameSize + kPacketTotalSize];
    *packetOrder += packet[kUdpHeaderSize + kFileNameSize + kPacketTotalSize + 1] << 8;
    memcpy(fileContent, packet + kUdpHeaderSize + kFileNameSize + kPacketTotalSize + kPacketOrderSize, kFileContentSize);
    memcpy(checksum, packet + kUdpHeaderSize + kFileNameSize + kPacketTotalSize + kPacketOrderSize + kFileContentSize, kChecksumSize);
    checksum[kChecksumSize] = '\0';
}

void generateChecksum(char checksum[kChecksumSize], unsigned char packet[kPacketSize])
{
    MD5 md5;
    md5.add(packet, kPacketSize - kChecksumSize);
    memcpy(checksum, md5.getHash().c_str(), kChecksumSize);
}

int compareChecksum(char checksum[kChecksumSize], unsigned char packet[kPacketSize])
{
    char generatedChecksum[kChecksumSize];
    generateChecksum(generatedChecksum, packet);

    for (int i = 0; i < kChecksumSize; i++)
    {
        if (checksum[i] != generatedChecksum[i])
        {
            return 0;
        }
    }

    return 1;
}