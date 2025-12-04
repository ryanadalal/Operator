/* declare constants to be used throughout the code */
.set ALIGN, 1<<0
.set MEMINFO, 1<<1
.set FLAGS, ALIGN | MEMINFO
.set MAGIC, 0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)


/*
writes a multi boot header
aligns them to 32 bit boundarys
magic allows the bootloader to find the kernel
*/
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM


/*
the bss .section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:section is zeroed at run time - this means that rather than containing
empty space in the kernel, the kernel knows to clear this space and then allow the 
stack to fill it when it starts up

stack_top and stack_bottom are labels and can be used in code to mark the stack end points

.skip allocates space in memory for this data


*/
.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:

/*
.text is for executable instructions
_start becomes a global label meaning other files can access it
.type function helps the linker and debugger know that this is a function
*/
.section .text
.global _start
.type _start, @function
_start: # marks a specific memory address for the label

    mov $stack_top, %esp # set the stack pointer to the top of the stack

    call kernel_main  # jumps to the address of the kernel_main function

    cli # disable interupts
1:  hlt # halt and wait for an interupt (since they are disabled the program will freeze)
    jmp 1b # if somehow it wakes up go back to halted state

.size _start, . - _start

