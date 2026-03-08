#pragma once

#include "../core/isr.h"

#define KEYBOARD_DATA_PORT 0x60

void keyboard_init();
void keyboard_handler(struct regs *r);