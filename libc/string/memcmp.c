#include <string.h>

/*
* Compare the first [size] bytes of memory at [aptsr] and [bptr]
* @param aptr the first memory area to compare
* @param bptr the second memory area to compare
* @param size the number of bytes to compare
* @returns an integer less than 0 if a < b, 0 if a == b, and greater than 0 if a > b
*/
int memcmp(const void* aptr, const void* bptr, size_t size) {
	const unsigned char* a = (const unsigned char*) aptr;
	const unsigned char* b = (const unsigned char*) bptr;
	for (size_t i = 0; i < size; i++) {
		if (a[i] < b[i])
			return -1;
		else if (b[i] < a[i])
			return 1;
	}
	return 0;
}