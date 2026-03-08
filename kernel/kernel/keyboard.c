#include <kernel/keyboard.h>
#include <kernel/isr.h>
#include <kernel/tty.h>
#include "port.h"

#define KEY_RELEASE_CODE 0x80

static char scancode_ascii[128] = {
    0,  27, '1','2','3','4','5','6','7','8','9','0','-','=','\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n', 0,
    'a','s','d','f','g','h','j','k','l',';','\'','`', 0,'\\',
    'z','x','c','v','b','n','m',',','.','/', 0, '*', 0, ' ',
    // remaining scancodes are not mapped to ASCII characters
};

void keyboard_handler(struct regs *r) {
  // read scan code from keyboard data port
  uint8_t scancode = inb(KEYBOARD_DATA_PORT);

  if (scancode & KEY_RELEASE_CODE) {
    return;
  }

  if (scancode < 128) {
    char c = scancode_ascii[scancode];
    if (c) {
      terminal_putchar(c);
    }
  }
}

// register the keyboard handler
void keyboard_init() {
  // IRQ 1 corresponds to the keyboard
  register_interrupt_handler(33, keyboard_handler);
}