.section .text
.extern isr_handler    # C handler for CPU exceptions
.extern irq_handler    # C handler for IRQs

.macro ISR_NOERR num
    .globl isr\num
isr\num:
    pushal                  # save eax, ecx, edx, ebx, esp, ebp, esi, edi
    push %ds
    push %es
    push %fs
    push %gs

    mov $0x10, %ax          # kernel data segment
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    push $0                  # fake error code
    push $\num               # interrupt number
    mov %esp, %eax          # eax = pointer to regs structure on stack
    push %eax               # push as first argument to isr_handler
    call isr_handler
    add $12, %esp           # pop: argument (4) + int_no (4) + err_code (4)

    pop %gs
    pop %fs
    pop %es
    pop %ds
    popal
    iret
.endm

/* -----------------------------
   Macro: ISR with error code
   ----------------------------- */
.macro ISR_ERR num
    .globl isr\num
isr\num:
    pushal
    push %ds
    push %es
    push %fs
    push %gs

    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    push $\num               # interrupt number
    mov %esp, %eax          # eax = pointer to regs structure
    push %eax               # push as first argument
    call isr_handler
    add $8, %esp            # pop argument and int_no (error code left on stack by CPU)

    pop %gs
    pop %fs
    pop %es
    pop %ds
    popal
    add $4, %esp            # skip error code on stack
    iret
.endm

/* -----------------------------
   Macro: IRQ handler
   ----------------------------- */
.macro IRQ num
    .globl irq\num
irq\num:
    pushal
    push %ds
    push %es
    push %fs
    push %gs

    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    push $0                 # fake error code (for consistency with struct regs)
    push $(32 + \num)       # interrupt number (IRQ0 = INT 32, etc.)
    mov %esp, %eax          # eax = pointer to regs structure
    push %eax               # push as first argument
    call irq_handler
    add $12, %esp           # pop argument (4) + int_no (4) + err_code (4)

    pop %gs
    pop %fs
    pop %es
    pop %ds
    popal
    iret
.endm

/* -----------------------------
   Define CPU exceptions
   ----------------------------- */
ISR_NOERR 0
ISR_NOERR 1
ISR_NOERR 2
ISR_NOERR 3
ISR_NOERR 4
ISR_NOERR 5
ISR_NOERR 6
ISR_NOERR 7
ISR_ERR 8
ISR_NOERR 9
ISR_ERR 10
ISR_ERR 11
ISR_NOERR 12
ISR_ERR 13
ISR_NOERR 14
ISR_NOERR 15
ISR_NOERR 16
ISR_NOERR 17
ISR_NOERR 18
ISR_NOERR 19
ISR_NOERR 20
ISR_NOERR 21
ISR_NOERR 22
ISR_NOERR 23
ISR_NOERR 24
ISR_NOERR 25
ISR_NOERR 26
ISR_NOERR 27
ISR_NOERR 28
ISR_NOERR 29
ISR_NOERR 30
ISR_NOERR 31

/* -----------------------------
   Define IRQs 0-15
   ----------------------------- */
IRQ 0
IRQ 1
IRQ 2
IRQ 3
IRQ 4
IRQ 5
IRQ 6
IRQ 7
IRQ 8
IRQ 9
IRQ 10
IRQ 11
IRQ 12
IRQ 13
IRQ 14
IRQ 15

/* -----------------------------
   Table of ISR addresses for C
   ----------------------------- */
.section .rodata
.global isr_stub_table
isr_stub_table:
    .long isr0
    .long isr1
    .long isr2
    .long isr3
    .long isr4
    .long isr5
    .long isr6
    .long isr7
    .long isr8
    .long isr9
    .long isr10
    .long isr11
    .long isr12
    .long isr13
    .long isr14
    .long isr15
    .long isr16
    .long isr17
    .long isr18
    .long isr19
    .long isr20
    .long isr21
    .long isr22
    .long isr23
    .long isr24
    .long isr25
    .long isr26
    .long isr27
    .long isr28
    .long isr29
    .long isr30
    .long isr31

.global irq_stub_table
irq_stub_table:
    .long irq0
    .long irq1
    .long irq2
    .long irq3
    .long irq4
    .long irq5
    .long irq6
    .long irq7
    .long irq8
    .long irq9
    .long irq10
    .long irq11
    .long irq12
    .long irq13
    .long irq14
    .long irq15