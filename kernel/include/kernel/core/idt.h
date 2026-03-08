// idt.h
#pragma once
#include <stdint.h>

struct idt_entry {
    uint16_t offset_1;
    uint16_t selector;
    uint8_t  zero;
    uint8_t  type_attributes;
    uint16_t offset_2;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

extern struct idt_entry idt[256];
extern struct idt_ptr idtp;

extern void* isr_stub_table[];
extern void* irq_stub_table[];
extern void idt_load(uint32_t);

void idt_init(void);
void idt_set_gate(int n, uint32_t handler);