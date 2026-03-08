#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>

#include <kernel/hardware/tty.h>

#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xC03FF000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

/*
* initial the terminal: clear screen & set cursor to (0, 0)
*/
void terminal_init(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

/*
* set the terminal color
* @param - color: the color to be set
*/
void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

/*
* put a character with color at (x, y)
* @param c the character to be put
* @param color the color of the character
* @param x the column of the character
* @param y the row of the character
*/
void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

/*
* scroll the terminal up by one line
* @param line the line to be scrolled up
*/
void terminal_scroll(int line) {
    uint16_t* vga = VGA_MEMORY;
    int start = line * VGA_WIDTH;

    for (size_t i = start; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga[i - VGA_WIDTH] = vga[i];
    }
}

/*
* clear the last line of the terminal
*/
void terminal_delete_last_line() {
	uint16_t* vga = VGA_MEMORY;

	for(size_t x = 0; x < VGA_WIDTH; x++) {
		vga[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = 0;
	}
}

/*
* put a character on the terminal
* @param c the character to be put
*/
void terminal_putchar(char c) {
	size_t line;
	unsigned char uc = c;

	if (c == '\n') {
		terminal_column = 0;
		terminal_row++;
	} else {
		terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		terminal_row++;
	}
	}
	if (terminal_row == VGA_HEIGHT)
	{
		for(line = 1; line <= VGA_HEIGHT - 1; line++)
		{
			terminal_scroll(line);
		}
		terminal_delete_last_line();
		terminal_row = VGA_HEIGHT - 1;
	}
}

/*
* write a string of given size to the terminal
* @param data the string to be written
* @param size the size of the string to be written
*/
void terminal_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

/* 
* write a null-terminated string to the terminal
* @param data the string to be written
*/
void terminal_writestring(const char* data) {
	terminal_write(data, strlen(data));
}

/*
* print an integer in hexadecimal format to the terminal
* @param n the integer to be printed
*/
static void print_uint32_hex(uint32_t n) {
    char hex[9];
    hex[8] = 0;
    for(int i = 7; i >= 0; i--) {
        uint8_t digit = n & 0xF;
        if(digit < 10) hex[i] = '0' + digit;
        else hex[i] = 'A' + (digit - 10);
        n >>= 4;
    }
    terminal_writestring(hex);
}

/*
* Print a formatted string to the terminal (supports %c, %s, %x)
* @param fmt the format string
* @param ... the arguments to be formatted
*/
void kprintf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    for(const char* p = fmt; *p; p++) {
        if(*p == '%') {
            p++;
            if(*p == 'c') {
                char c = (char) va_arg(args, int);
                terminal_putchar(c);
            } else if(*p == 's') {
                const char* s = va_arg(args, const char*);
                terminal_writestring(s);
            } else if(*p == 'x') {
                uint32_t val = va_arg(args, uint32_t);
                print_uint32_hex(val);
            } else if(*p == '%') {
                terminal_putchar('%');
            }
        } else {
            terminal_putchar(*p);
        }
    }
    va_end(args);
}

/*
* Print a kernel error message
* @param msg the error message to display
*/
void kerror(const char *msg) {
	kprintf("KERNEL ERROR: %s\n", msg);
}