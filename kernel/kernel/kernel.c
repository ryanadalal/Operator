#include <stdio.h>
#include <kernel/hardware/tty.h>
#include <kernel/core/gdt.h>
#include <kernel/core/interrupts.h>

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