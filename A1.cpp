#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "A1.h"
#include "hash-library/md5.h"
#include "hash-library/md5.cpp"

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

char* generateChecksum(char* input,size_t sizeOfString)
{
    char* checkSum = (char*)malloc(sizeOfString + 1); // Allocate space for null-terminator
    if (checkSum == NULL) {
        // Handle allocation failure
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
 
    MD5 md5;
   /* char str[10] = "HELOLO";*/
    md5.add(input, sizeOfString);
        
    strncpy(checkSum, md5.getHash().c_str(), sizeOfString); // Use strncpy for safer copying
    checkSum[sizeOfString] = '\0'; // Null-terminate the string
    return checkSum;
}


bool checkChecksum(char* input, char* sendChecksum, size_t sizeOfString)
{
    char* resultChecksum = generateChecksum(input, sizeOfString); // Calculate the checksum
    int result = memcmp(resultChecksum, sendChecksum, sizeOfString); // Compare the checksums
    free(resultChecksum); // Free memory allocated by generateChecksum
    if (result == 0)
    {
        return true;
    }
    else
    {
        return false; // Return true if checksums are equal, false otherwise
    }
   
}

//char* packData(char* fileName, short packetTotal, short packetOrder, char* fileContent)
//{
//    char* packet;
//
//    strcpy(packet, fileName);
//
//    strcat(packet, kPacketSeparator);
//
//    sprintf(packet, "%d", packetTotal);
//
//    strcat(packet, kPacketSeparator);
//
//    sprintf(packet, "%d", packetOrder);
//
//    strcat(packet, kPacketSeparator);
//
//    strcat(packet, fileContent);
//
//    return packet;
//}
//
//void unpackData(char* packet, char* fileName, int packetTotal, int packetOrder, char* fileContent)
//{
//    char* token = NULL;
//    for (int i = 0; i < 4; i++)
//    {
//        token = strtok(packet, kPacketSeparator);
//        if (token != NULL)
//        {
//            switch (i)
//            {
//                case 0:
//                {
//                    strcpy(fileName, token);
//                }
//                case 1:
//                {
//                    packetTotal = atoi(token);
//                }
//                case 2:
//                {
//                    packetOrder = atoi(token);
//                }
//                case 3:
//                {
//                    strcpy(fileContent, token);
//                }
//            }
//        }
//    }
//}