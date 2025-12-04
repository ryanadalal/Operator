#include <kernel/tty.h>
#include <stdio.h>

void kernel_main() {
    terminal_initialize();
    terminal_write("Step 1\n", 7);
    printf("Hello, Kernel World!\n");
}