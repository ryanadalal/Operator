// write a string to stdout followed by a newline

#include <stdio.h>

/*
* write a string to stdout followed by a newline
* @param string the string to write
* @returns a non-negative number on success, EOF on error
*/
int puts(const char* string) {
	return printf("%s\n", string);
}