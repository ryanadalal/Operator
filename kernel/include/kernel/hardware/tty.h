#pragma once

#include <stddef.h>

void terminal_init();
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
void kerror(const char *msg);