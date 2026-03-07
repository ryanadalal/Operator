.section .text
  .globl idt_load
  .extern idtp

idt_load:
    lidt [idtp]
    ret