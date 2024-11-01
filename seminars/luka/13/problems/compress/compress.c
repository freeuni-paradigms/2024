#include "compress.h"
#include <stdbool.h>

// 0b01110011 0b01000100 0b00110110
int getNumAtIndex(void *data, int index) {
	int byteIndex = index / 2;

	char byte = ((char *)data)[byteIndex];

	if (index % 2 == 0) {

		// 0010 0000 >> 4 = 0000 0010 | 1010 0000 >> 4 = 1111 1010
		return (byte >> 4) & 0xF;
	} else {
		return byte & 0xF; // 0xF == 15 == 0b00001111 
	}
}

int Compress(void* data, void* out) {
	int i = 0;
	int bytesWritten = 0;
	while (true) {
		int currentNum = getNumAtIndex(data, i);

		if (currentNum == 0) {
			break;
		}

		int currnetNumMaxIndex;
		for (currnetNumMaxIndex = i; getNumAtIndex(data, currnetNumMaxIndex) == currentNum; currnetNumMaxIndex++) {};
		
		int count = currnetNumMaxIndex - i;
		
		char byte = 0; // 0b00000000
		// byte = byte | 5; byte |= 5;

		byte |= (count << 4); //  0b00100000
		byte |= currentNum; // 0b00100011

		*((char *)out + bytesWritten) = byte;
		bytesWritten++;

		i = currnetNumMaxIndex;
	} 

	return bytesWritten;
}
