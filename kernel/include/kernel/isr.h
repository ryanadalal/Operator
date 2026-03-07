#pragma once
#include <stdint.h>

struct regs;

typedef void (*isr_t)(struct regs *r);
extern isr_t interrupt_handlers[256];

void isr_handler(struct regs *r);
void irq_handler(struct regs *r);
void register_interrupt_handler(uint8_t n, isr_t handler);