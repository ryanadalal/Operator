#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#if defined(__linux__)
#error "This code is not intended to be compiled on Linux systems."
#endif

#if !defined(__i386__)
#error "This code is intended to be compiled only for 32 bit architecture."
#endif

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

/*
vga represents text with foreground and background colors in a byte
the upper four bits are fg and the lower four bits are bg
the whole entry is 2 bytes
1. lower byte for the ascii character
2. upper byte for the color byte
*/
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

/* loop until null character to find length */
size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

#define VGA_WIDTH   80
#define VGA_HEIGHT  25
#define VGA_MEMORY  0xB8000 


size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;

void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK);
	
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_scroll(void) {
    for (size_t y = 0; y < VGA_HEIGHT - 1; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            terminal_buffer[y * VGA_WIDTH + x] = terminal_buffer[(y + 1)* VGA_WIDTH + x];
        }
    }
    for (size_t x = 0; x < VGA_WIDTH; x++) {
        terminal_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = vga_entry(' ', terminal_color);
    }
    terminal_row = VGA_HEIGHT - 1;
}

void terminal_putchar(char c) 
{
    if (c == '\n') {
        terminal_column = 0;
        terminal_row++;
    } else {
	    terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
        if (++terminal_column == VGA_WIDTH) {
		    terminal_column = 0;
            terminal_row++;
        }
    }
    if (terminal_row == VGA_HEIGHT){
        terminal_row = 0;
        terminal_scroll();
    }
}

void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();

	terminal_writestring("Hello, kernel World!1\n");
	terminal_writestring("Hello, kernel World!2\n");
	terminal_writestring("Hello, kernel World!3\n");
	terminal_writestring("Hello, kernel World!4\n");
	terminal_writestring("Hello, kernel World!5\n");
	terminal_writestring("Hello, kernel World!6\n");
	terminal_writestring("Hello, kernel World!7\n");
	terminal_writestring("Hello, kernel World!8\n");
	terminal_writestring("Hello, kernel World!9\n");
	terminal_writestring("Hello, kernel World!10\n");
    terminal_writestring("Hello, kernel World!11\n");
    terminal_writestring("Hello, kernel World!12\n");
    terminal_writestring("Hello, kernel World!13\n");
	terminal_writestring("Hello, kernel World!14\n");
	terminal_writestring("Hello, kernel World!15\n");
	terminal_writestring("Hello, kernel World!16\n");
	terminal_writestring("Hello, kernel World!17\n");
	terminal_writestring("Hello, kernel World!18\n");
	terminal_writestring("Hello, kernel World!19\n");
	terminal_writestring("Hello, kernel World!20\n");
	terminal_writestring("Hello, kernel World!21\n");
	terminal_writestring("Hello, kernel World!22\n");
	terminal_writestring("Hello, kernel World!23\n");
	terminal_writestring("Hello, kernel World!24\n");
	terminal_writestring("Hello, kernel World!25\n");
    terminal_writestring("Hello, kernel World!26\n");
	terminal_writestring("Hello, kernel World!27\n");
	terminal_writestring("Hello, kernel World!28\n");
	terminal_writestring("Hello, kernel World!29\n");
	terminal_writestring("Hello, kernel World!30\n");
	terminal_writestring("Hello, kernel World!31\n");
	terminal_writestring("Hello, kernel World!32\n");
	terminal_writestring("Hello, kernel World!33\n");
	terminal_writestring("Hello, kernel World!34\n");
	terminal_writestring("Hello, kernel World!35\n");
	terminal_writestring("Hello, kernel World!36\n");
	terminal_writestring("Hello, kernel World!37\n");
	terminal_writestring("Hello, kernel World!38\n");
	terminal_writestring("Hello, kernel World!39\n");
	terminal_writestring("Hello, kernel World!40\n");
    
}