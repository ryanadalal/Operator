#include <kernel/hardware/tty.h>
#include <kernel/core/gdt.h>
#include <kernel/core/interrupts.h>

void kernel_main() {
    terminal_init();
    gdt_install();
    interrupts_init();

    terminal_writestring("Hello, Kernel World!\n");

    while (1) {
        __asm__ __volatile__("hlt");
    }
}