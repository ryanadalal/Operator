// fill a block of memory with a particular value

#include <string.h>

/*
* fills [size] bytes starting at [bufptr] with the byte value [value]
* @param bufptr the memory area to fill
* @param value the byte value to fill with (converted to unsigned char)
* @param size the number of bytes to fill
* @returns a pointer to the memory area [bufptr]
*/
void* memset(void* bufptr, int value, size_t size) {
	unsigned char* buf = (unsigned char*) bufptr;
	for (size_t i = 0; i < size; i++)
		buf[i] = (unsigned char) value;
	return bufptr;
}