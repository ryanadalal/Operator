# Declare constants for the multiboot header.
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

# Declare a header as in the Multiboot Standard.
.section .multiboot, "a"
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Reserve a stack for the initial thread.
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.align 4096
boot_page_directory:
	.skip 4096
boot_page_table1:
	.skip 4096

# The kernel entry point.
.section .multiboot.text, "ax"
.global _start
.type _start, @function
_start:
  # edi points to boot_page_table1
	movl $(boot_page_table1 - 0xC0000000), %edi
	# virtual address to map starting at 0
	movl $0, %esi
	# the number of pages to map (1023 since 1024 is for VGA text memory)
	movl $1023, %ecx

# 1 and 2 are used to map the kernel in both the lower half and higher half of the virtual address space.
1:
	# map the kernel into the page table
	cmpl $_kernel_start, %esi
	jl 2f
	cmpl $(_kernel_end - 0xC0000000), %esi
	jge 3f

	movl %esi, %edx
  # set the present and writable flags to true
	orl $0x003, %edx
	movl %edx, (%edi)
2:
	# each page is 4096 bytes, so to get next addr add 4096 to esi
	addl $4096, %esi
	# each entry is 4 bytes
	addl $4, %edi
	# loop until all pages are mapped
	loop 1b
3:
  # maps the vga text buffer and sets present and writable flags (0x003)
  movl $(0x000B8000 | 0x003), boot_page_table1 - 0xC0000000 + 1023 * 4

	# page directory has 1024 entries, each pointing to a page table
  # entry 0 maps to boot_page_table1, and entry 768 (0x300) also maps to boot_page_table1 to create the higher half mapping.
  # the first is identity mapping, and the second is the higher half mapping.

	# Map the page table to both virtual addresses 0x00000000 and 0xC0000000.
	movl $(boot_page_table1 - 0xC0000000 + 0x003), boot_page_directory - 0xC0000000 + 0
	movl $(boot_page_table1 - 0xC0000000 + 0x003), boot_page_directory - 0xC0000000 + 768 * 4

	# Set cr3 to the address of the boot_page_directory.
	movl $(boot_page_directory - 0xC0000000), %ecx
	movl %ecx, %cr3

	# Enable paging and the write-protect bit.
	movl %cr0, %ecx
  # overwrite cr0s paging enabled bit to 1
  # and set the write-protect bit to 1 as well (0x80010000) to avoid kernel overwriting read-only pages in user space.
	orl $0x80010000, %ecx
	movl %ecx, %cr0

	# Jump to higher half with an absolute jump. 
	lea 4f, %ecx
	jmp *%ecx

.section .text

4:
	cli

  # Unmap the identity mapping as it is now unnecessary. 
	movl $0, boot_page_directory + 0

  # Reload crc3 to force a TLB flush so the changes to take effect.
	movl %cr3, %ecx
	movl %ecx, %cr3

  # set up the stack
	movl $stack_top, %esp

	# Transfer control to the main kernel.
	call kernel_main

	# Hang if kernel_main unexpectedly returns.
	cli
1:	hlt
	jmp 1b