// copy a block of memory, handling overlapping regions correctly


#include <string.h>


/*
* copy [size] bytes from memory area [srcptr] to memory area [dstptr]
* notes - source and destination regions may overlap
* @param dstptr the destination memory area to copy to
* @param srcptr the source memory area to copy from
* @param size the number of bytes to copy
* @returns a pointer to the destination memory area [dstptr]
*/
void* memmove(void* dstptr, const void* srcptr, size_t size) {
	unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;
	if (dst < src) {
		for (size_t i = 0; i < size; i++) // forward copy
			dst[i] = src[i];
	} else {
		for (size_t i = size; i != 0; i--) // backward copy
			dst[i-1] = src[i-1];
	}
	return dstptr;
}