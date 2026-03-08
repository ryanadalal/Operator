#include <kernel/keyboard.h>
#include <kernel/isr.h>
#include <kernel/tty.h>
#include "port.h"

void keyboard_handler(struct regs *r) {
  uint8_t scancode = inb(KEYBOARD_DATA_PORT); // read scan code from keyboard data port
  terminal_putchar(scancode);
}

// register the keyboard handler
void keyboard_init() {
  // IRQ 1 corresponds to the keyboard
  register_interrupt_handler(33, keyboard_handler);
}