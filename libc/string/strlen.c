#include <string.h>

/*
* compute the length of a null-terminated string
* @param str the string to compute the length of
* @returns the number of characters in the string before the null terminator
*/
size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}