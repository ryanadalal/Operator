.section .data
gdtr:
	.word 0		# For limit storage
	.long 0		# For base storage

.section .text
.global setGdt
.type setGdt, @function
setGdt:
	movw 4(%esp), %ax
	movw %ax, gdtr
	movl 8(%esp), %eax
	movl %eax, gdtr + 2
	lgdt gdtr
	ret

.global reloadSegments
.type reloadSegments, @function
reloadSegments:
	# Reload CS register containing code selector:
	ljmp $0x08, $.reload_CS	# 0x08 is a stand-in for your code segment
.reload_CS:
	# Reload data segment registers:
	movw $0x10, %ax	# 0x10 is a stand-in for your data segment
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movw %ax, %ss
	ret
