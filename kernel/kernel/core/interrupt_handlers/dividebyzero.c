#include <kernel/core/interrupt_handlers/dividebyzero.h>
#include <kernel/core/isr.h>
#include <kernel/hardware/tty.h>
#include "port.h"

void divide_by_zero_handler(struct regs *r) {
    kprintf("Divide by zero exception!\n");
    kprintf("EAX: %x, EBX: %x, ECX: %x, EDX: %x\n",
               r->eax, r->ebx, r->ecx, r->edx);
    kprintf("EIP: %x, CS: %x\n", r->eip, r->cs);
    while (1) {
        __asm__ __volatile__("hlt");
    }
}

// register the divide by zero handler
void divide_by_zero_init() {
  // IRQ 0 corresponds to the divide by zero exception
  register_interrupt_handler(0, divide_by_zero_handler);
}