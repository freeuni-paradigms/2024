#include "compress.h"
#include <stdbool.h>

int getNumAtIndex(void *data, int index) {
	
}

int Compress(void* data, void* out) {
	int i = 0;
	int bytesWritten = 0;
	while (true) {
		int currentNum = getNumAtIndex(data, i);
		int currnetNumMaxIndex;
		for (currnetNumMaxIndex = i; getNumAtIndex(data, currnetNumMaxIndex) == currentNum; currnetNumMaxIndex++) {};
		
		int count = currnetNumMaxIndex - i;
		
		char byte = 0;
		byte |= (count << 4);
		byte |= currentNum;

	} 
}
