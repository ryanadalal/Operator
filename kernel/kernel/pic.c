#include <stdint.h>
#include <kernel/pic.h>
#include "port.h"

#define PIC1_COMMAND 0x20
#define PIC1_DATA    0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA    0xA1
#define ICW1_INIT    0x11
#define ICW4_8086    0x01

void pic_remap(int offset1, int offset2) {
    uint8_t a1, a2;

    a1 = inb(PIC1_DATA); // save masks
    a2 = inb(PIC2_DATA);

    outb(PIC1_COMMAND, ICW1_INIT); // initializes configuration
    outb(PIC2_COMMAND, ICW1_INIT);
    outb(PIC1_DATA, offset1); // remap IRQ 0-7 to offset1
    outb(PIC2_DATA, offset2); // remap IRQ 8-15 to offset2
    outb(PIC1_DATA, 4); // tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
    outb(PIC2_DATA, 2); 
    outb(PIC1_DATA, ICW4_8086); // set master to x86 mode
    outb(PIC2_DATA, ICW4_8086);

    outb(PIC1_DATA, a1); // restore masks
    outb(PIC2_DATA, a2);
}

void pic_send_eoi(uint8_t irq) {
    if (irq >= 8)
        outb(PIC2_COMMAND, 0x20);  // send EOI to slave PIC
    outb(PIC1_COMMAND, 0x20);      // send EOI to master PIC
}