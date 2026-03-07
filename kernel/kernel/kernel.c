#include <kernel/tty.h>
#include <stdio.h>
#include <kernel/gdt.h>
#include <kernel/interrupts.h>

void kernel_main() {
    gdt_install();
    interrupts_init();

    terminal_initialize();
    terminal_write("Step 1\n", 7);
    printf("Hello, Kernel World1!\n");
    printf("Hello, Kernel World2!\n");
    printf("Hello, Kernel World3!\n");
    printf("Hello, Kernel World4!\n");
    printf("Hello, Kernel World5!\n");
    printf("Hello, Kernel World6!\n");
    printf("Hello, Kernel World7!\n");
    printf("Hello, Kernel World8!\n");
    printf("Hello, Kernel World9!\n");
    printf("Hello, Kernel World0!\n");


    while (1) {
        __asm__ __volatile__("hlt");
    }
}