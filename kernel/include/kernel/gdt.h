// gdt.h
#ifndef GDT_H
#define GDT_H

#include <stdint.h>

// Structure for a GDT entry
struct GDT {
    uint16_t limit;
    uint32_t base;
    uint8_t  access;
    uint8_t  granularity;
} __attribute__((packed));

// Our GDT array (3 entries: null, code, data)
extern struct GDT gdt[5];

// Function prototypes
void gdt_install(void);  // calls setGdt + reloadSegments in assembly

#endif
