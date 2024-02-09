#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "A1.h"

const char kPacketSeparator = '|';
const char kInvalidFilenameChars[] = { '\\', '/', ':', '*', '?', '"', '<', '>', '|' };
const int kFilenameSize = 50;
const int kPacketSize = 1024; // 1KB

void concatenate(unsigned char* left, unsigned char* right, size_t size)
{
    memcpy(left, right, size);
}

void concatenate(unsigned char* left, size_t offset, unsigned char* right, size_t size)
{
    concatenate(left + offset, right, size);
}

int validateFilename(char* fileName)
{
    if (strlen(fileName) > kFilenameSize)
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

char* packData(char* fileName, short packetTotal, short packetOrder, char* fileContent, size_t fileContentSize)
{
    char* packet = (char*)malloc(kPacketSize);

    if (packet != NULL)
    {
        //concatenate(packet, 0, fileName, kFilenameSize);
        
    }

    return packet;
}

void unpackData(char* packet, char* fileName, short packetTotal, short packetOrder, char* fileContent)
{
    fileName = packet;
    packet += kFilenameSize + sizeof(kPacketSeparator);
    packetTotal = atoi(packet);
    packet += sizeof(packetTotal) + sizeof(kPacketSeparator);
    packetOrder = atoi(packet);
    packet += sizeof(packetOrder) + sizeof(kPacketSeparator);
    fileContent = packet;
}