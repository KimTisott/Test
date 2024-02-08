#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "A1.h"

const char* kPacketSeparator = "|";
const char kInvalidFilenameChars[] = { '\\', '/', ':', '*', '?', '"', '<', '>', '|' };
const int kFilenameSize = 50;
const int kPacketSize = 500;
const int kNumericBase = 10;

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

char* packData(char* fileName, short packetTotal, short packetOrder, char* fileContent)
{
    char* packet;

    strcpy(packet, fileName);

    strcat(packet, kPacketSeparator);

    sprintf(packet, "%d", packetTotal);

    strcat(packet, kPacketSeparator);

    sprintf(packet, "%d", packetOrder);

    strcat(packet, kPacketSeparator);

    strcat(packet, fileContent);

    return packet;
}

void unpackData(char* packet, char* fileName, int packetTotal, int packetOrder, char* fileContent)
{
    char* token = NULL;
    for (int i = 0; i < 4; i++)
    {
        token = strtok(packet, kPacketSeparator);
        if (token != NULL)
        {
            switch (i)
            {
                case 0:
                {
                    strcpy(fileName, token);
                }
                case 1:
                {
                    packetTotal = atoi(token);
                }
                case 2:
                {
                    packetOrder = atoi(token);
                }
                case 3:
                {
                    strcpy(fileContent, token);
                }
            }
        }
    }
}