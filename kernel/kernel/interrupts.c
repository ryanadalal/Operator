#include <stdint.h>
#include <kernel/pic.h>
#include <kernel/idt.h>
#include <kernel/interrupts.h>

void interrupts_init() {
    pic_remap(0x20, 0x28);

    idt_init();

    __asm__ __volatile__("sti");
}