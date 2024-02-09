const char kInvalidFilenameChars[] = { '\\', '/', ':', '*', '?', '"', '<', '>', '|' };
const int kUdpHeaderSize = 12;
const int kFileNameSize = 51; // 50 characters
const int kPacketTotalSize = sizeof(short);
const int kPacketOrderSize = sizeof(short);
const int kFileContentSize = 384 - kFileNameSize - kPacketTotalSize - kPacketOrderSize;
const int kPacketSize = kUdpHeaderSize + kFileNameSize + kPacketTotalSize + kPacketOrderSize + kFileContentSize;
const int kChecksumSize = 33; // 32 characters

enum ERROR {
	FILENAME_INVALIDCHARACTERS,
	FILENAME_TOOLONG
};

void packData(unsigned char packet[kPacketSize], char fileName[kFileNameSize], short packetTotal, short packetOrder, unsigned char fileContent[kFileContentSize]);
void unpackData(unsigned char packet[kPacketSize], char fileName[kFileNameSize], short packetTotal, short packetOrder, unsigned char fileContent[kFileContentSize]);
int validateFilename(char* fileName);
void generateChecksum(char checksum[kChecksumSize], unsigned char packet[kPacketSize]);
int checkChecksum(char* input, char* sendChecksum, size_t sizeOfString);