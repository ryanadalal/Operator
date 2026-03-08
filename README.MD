# Custom OS

- Boots into 32-bit protected with GRUB
- Global & interrupt descriptor table
- Interrupts working (handlers not fully implemented)
- Terminal - simple vga output working


# Next steps
1. Implement high priority interrupt handlers
2. Confirm paging is working fully (page tables, kernel heap, kmalloc, etc.)
3. Implement a timer
4. Scheduler - round robin to start
5. Shell loop - echo back whatever is typed
6. File system

# Testing
`./complete.sh`