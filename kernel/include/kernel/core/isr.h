#pragma once
#include <stdint.h>

struct regs {
    // Pushed LAST by our stubs (so first in memory)
    uint32_t int_no, err_code;
    // Segment registers 
    uint32_t gs, fs, es, ds;
    // General purpose registers (from pushal - EDI pushed last, EAX first)
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    // CPU-pushed context (EIP pushed last by CPU)
    uint32_t eip, cs, eflags, useresp, ss;
};

typedef void (*isr_t)(struct regs *r);
extern isr_t interrupt_handlers[256];

void isr_handler(struct regs *r);
void irq_handler(struct regs *r);
void register_interrupt_handler(uint8_t n, isr_t handler);