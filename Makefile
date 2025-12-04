# Compiler and flags
CC = i686-elf-gcc
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -ffreestanding -nostdlib

# Files
KERNEL = myos.bin
ISO = myos.iso
LINKER = linker.ld

# Directories
ISO_DIR = isodir
BOOT_DIR = $(ISO_DIR)/boot
GRUB_DIR = $(BOOT_DIR)/grub

# Default target
all: iso

kernel.o: kernel.c
	$(CC) -c kernel.c -o kernel.o $(CFLAGS)

boot.o: boot.s
	$(CC) -c boot.s -o boot.o

$(KERNEL): boot.o kernel.o
	$(CC) -T $(LINKER) -o $(KERNEL) boot.o kernel.o $(LDFLAGS) -lgcc

iso: $(KERNEL)
	mkdir -p $(GRUB_DIR)
	cp $(KERNEL) $(BOOT_DIR)/$(KERNEL)
	cp grub.cfg $(GRUB_DIR)/grub.cfg
	grub2-mkrescue -o $(ISO) $(ISO_DIR)

clean:
	rm -f *.o $(KERNEL) $(ISO)

run: iso
	qemu-system-i386 -cdrom $(ISO)
