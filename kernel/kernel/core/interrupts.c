#include <stdint.h>
#include <kernel/hardware/pic.h>
#include <kernel/core/idt.h>
#include <kernel/core/interrupts.h>
#include <kernel/hardware/keyboard.h>

void interrupts_init() {
    pic_remap(0x20, 0x28);
    idt_init();
    keyboard_init();
    __asm__ __volatile__("sti");
}