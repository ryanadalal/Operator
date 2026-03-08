#include <stdio.h>
#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/interrupts.h>

void kernel_main() {
    terminal_init();
    printf("1. Starting kernel\n");
    
    gdt_install();
    printf("2. GDT installed\n");
    
    interrupts_init();
    printf("3. Interrupts initialized\n");

    printf("Hello, Kernel World!\n");

    while (1) {
        __asm__ __volatile__("hlt");
    }
}