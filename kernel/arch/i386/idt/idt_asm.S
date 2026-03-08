.section .text
.global idt_load
.type idt_load, @function
idt_load:
    movl 4(%esp), %eax    # load the pointer to idtp from the stack argument
    lidt (%eax)           # load IDT - %eax points to the idt_ptr structure
    ret