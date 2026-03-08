#include <stdint.h>
#include <kernel/core/isr.h>
#include <kernel/hardware/pic.h>
#include <kernel/hardware/tty.h>

isr_t interrupt_handlers[256] = {0};

// Called by assembly stubs for CPU exceptions
void isr_handler(struct regs *r) {
    if (interrupt_handlers[r->int_no]) {
        interrupt_handlers[r->int_no](r);  // call custom handler
    } else {
        // Default: print exception info and halt
        kprintf("Unhandled exception: %d\n", r->int_no);
        while (1) { __asm__ __volatile__("hlt"); } // halt CPU
    }
}

// Called by assembly stubs for hardware IRQs
void irq_handler(struct regs *r) {
    if (interrupt_handlers[r->int_no]) {
        interrupt_handlers[r->int_no](r);
    }

    // Send End Of Interrupt (EOI) to PIC
    // r->int_no is 32-47, convert to IRQ 0-15
    uint8_t irq = r->int_no - 32;
    pic_send_eoi(irq);
}

// Allows kernel modules or drivers to register their own handlers
void register_interrupt_handler(uint8_t n, isr_t handler) {
    interrupt_handlers[n] = handler;
}