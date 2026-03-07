#include <stdint.h>
#include <stdio.h>
#include <kernel/isr.h>
#include <kernel/pic.h>
#include <kernel/tty.h>

isr_t interrupt_handlers[256] = {0};

struct regs {
    uint32_t ds;                  // Data segment selector
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // pusha
    uint32_t int_no, err_code;    // interrupt number + error code
    uint32_t eip, cs, eflags, useresp, ss; // pushed by CPU automatically
};

// Called by assembly stubs for CPU exceptions
void isr_handler(struct regs *r) {
    if (interrupt_handlers[r->int_no]) {
        interrupt_handlers[r->int_no](r);  // call custom handler
    } else {
        // Default: print exception info and halt
        printf("Unhandled exception: %d\n", r->int_no);
        while (1) { __asm__ __volatile__("hlt"); } // halt CPU
    }
}

// Called by assembly stubs for hardware IRQs
void irq_handler(struct regs *r) {
    // Send End Of Interrupt (EOI) to PIC
    if (r->int_no >= 40) {
      pic_send_eoi(r->int_no - 40); // slave PIC
      pic_send_eoi(0); // also notify master
    } else {
        pic_send_eoi(r->int_no); // master PIC
    }

    // Call custom handler if registered
    if (interrupt_handlers[r->int_no]) {
        interrupt_handlers[r->int_no](r);
    }
}

// Allows kernel modules or drivers to register their own handlers
void register_interrupt_handler(uint8_t n, isr_t handler) {
    interrupt_handlers[n] = handler;
}