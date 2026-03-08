#include <stddef.h>
#include <stdint.h>

extern void* isr_stub_table[];
extern void* irq_stub_table[];
extern void idt_load(uint32_t);

void idt_set_gate(int n, uint32_t handler);

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

struct idt_entry idt[256];
struct idt_ptr idtp;

void idt_init()
{
    idtp.limit = sizeof(idt) - 1;
    idtp.base  = (uint32_t)&idt;

    for(int i = 0; i < 256; i++)
        idt_set_gate(i, 0);

    // CPU exceptions (0-31)
    for(int i = 0; i < 32; i++)
        idt_set_gate(i, (uint32_t)isr_stub_table[i]);

    // Hardware IRQs (32-47)
    for(int i = 0; i < 16; i++)
        idt_set_gate(32 + i, (uint32_t)irq_stub_table[i]);

    idt_load((uint32_t)&idtp);
}

void idt_set_gate(int n, uint32_t handler)
{
    idt[n].offset_1  = handler & 0xFFFF;
    idt[n].selector  = 0x08;
    idt[n].zero      = 0;
    idt[n].type_attributes = 0x8E;
    idt[n].offset_2  = (handler >> 16) & 0xFFFF;
}