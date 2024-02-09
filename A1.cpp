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
}

void unpackData(unsigned char packet[kPacketSize], char fileName[kFileNameSize], short packetTotal, short packetOrder, unsigned char fileContent[kFileContentSize])
{
    memcpy(fileName, packet + kUdpHeaderSize, kFileNameSize);
    packetTotal = packet[kUdpHeaderSize + kFileNameSize];
    packetOrder = packet[kUdpHeaderSize + kFileNameSize + kPacketTotalSize];
    memcpy(fileContent, packet + kUdpHeaderSize + kFileNameSize + kPacketTotalSize + kPacketOrderSize, kFileContentSize);
}

void generateChecksum(char checksum[kChecksumSize], unsigned char packet[kPacketSize])
{
    MD5 md5;
    md5.add(packet, kPacketSize);
    strncpy(checksum, md5.getHash().c_str(), kChecksumSize);
}

bool compareChecksum(char* input, char* sendChecksum, size_t sizeOfString)
{
    //char* resultChecksum = generateChecksum(input, sizeOfString); // Calculate the checksum
    //int result = memcmp(resultChecksum, sendChecksum, sizeOfString); // Compare the checksums
    //free(resultChecksum); // Free memory allocated by generateChecksum
    //if (result == 0)
    //{
    //    return true;
    //}
    //else
    //{
    //    return false; // Return true if checksums are equal, false otherwise
    //}
    return true;
}