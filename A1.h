enum ERROR {
	FILENAME_INVALIDCHARACTERS,
	FILENAME_TOOLONG
};

char* packData(char* fileName, short packetTotal, short packetOrder, char* fileContent, size_t fileContentSize);
void unpackData(char* packet, char* fileName, int packetTotal, int packetOrder, char* fileContent);
int validateFilename(char* fileName);
char* generateChecksum(char* input, size_t sizeOfString);
bool checkChecksum(char* input, char* sendChecksum, size_t sizeOfString);