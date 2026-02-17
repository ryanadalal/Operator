#include <stdio.h>

/*
* write a character to stdout
* @param ic the character to be written, passed as an int but converted to char
*/
#if defined(__is_libk)
#include <kernel/tty.h>
#endif
int putchar(int ic) {
#if defined(__is_libk)
	char c = (char) ic;
	terminal_write(&c, sizeof(c));
#else
	// TODO: Implement stdio and the write system call.
#endif
	return ic;
}