#pragma warning(disable : 4996)

#include <iostream>
#include "A1.h"

int main()
{
    char iFileName[kFileNameSize + 1] = "catVid.mp4";
    /*printf("File Name: ");
    scanf("%s", iFileName);*/

    //unsigned short iPacketTotal;
    //printf("Packet Total: ");
    //scanf("%hd", &iPacketTotal);

    //printf("Packet Order: ");
    //scanf("%hd", &iPacketOrder);

    unsigned char iFileContent[kFileContentSize];
    //printf("File Content: ");
    //scanf("%s", iFileContent);
    FILE* file = fopen(iFileName, "rb");
    if (file == NULL)
    {
        printf("Cannot open file: %s", iFileName);
        return -1;
    }
    FILE* ofile = fopen("newFile", "wb");
    if (ofile == NULL)
    {
        return -1;
    }
    fseek(file, 0L, SEEK_END);
    int fileSize = ftell(file);
    rewind(file);
    unsigned short iPacketTotal = (fileSize / kPacketSize) + 1;
    unsigned short iPacketOrder = 0;

    char oFileName[kFileNameSize + 1];
    unsigned short oPacketTotal = 0;
    unsigned short oPacketOrder = 0;
    unsigned char oFileContent[kFileContentSize];
    char oChecksum[kChecksumSize + 1];

    // Load the file contents into a buffer
    size_t bytesRead;
    while (!feof(file))
    {
        if ((bytesRead = fread(iFileContent, sizeof(unsigned char), kFileContentSize, file)) != 0)
        {
            unsigned char iPacket[kPacketSize];
            packData(iPacket, iFileName, iPacketTotal, iPacketOrder, iFileContent);

            unpackData(iPacket, oFileName, &oPacketTotal, &oPacketOrder, oFileContent, oChecksum);
            printf("\nFile Name: %s", oFileName);
            printf("\nPacket Total: %d", oPacketTotal);
            printf("\nPacket Order: %d", oPacketOrder);
            printf("\nFile Content: %s", oFileContent);
            printf("\nChecksum: %s", oChecksum);
            int status = compareChecksum(oChecksum, iPacket);
            printf("\nOK: %d", status);
            if (status == 1)
            {
                fwrite(oFileContent, kFileContentSize, sizeof(unsigned char), ofile);
                iPacketOrder++;
            }
          
        }
    }
    fclose(file);
    fclose(ofile);
   


   

   

    return 0;
}