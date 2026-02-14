
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "gdt.h"

extern void setGdt(uint16_t limit, uint32_t base);
extern void reloadSegments(void);

void gdt_install() {
    gdt[0] = (struct GDT){0};          // Null segment
    gdt[1] = (struct GDT){.base = 0, .limit = 0xFFFFF, .access = 0x9A, .granularity = 0xC}; // Code segment
    gdt[2] = (struct GDT){.base = 0, .limit = 0xFFFFF, .access = 0x92, .granularity = 0xC}; // Data segment
    gdt[3] = (struct GDT){.base = 0, .limit = 0xFFFFF, .access = 0xFA, .granularity = 0xC}; // User mode code segment
    gdt[4] = (struct GDT){.base = 0, .limit = 0xFFFFF, .access = 0xF2, .granularity = 0xC}; // User mode data segment
    // gdt[5] = (struct GDT){.base = 0, .limit = 0xFFFFF, .access = 0x89, .granularity = 0x0}; // TSS segment

    uint8_t gdt_entries[5][8]; // raw entries sent to CPU

    for(int i = 0; i < 5; i++) {
        encodeGdtEntry(gdt_entries[i], gdt[i]);
    }

    setGdt(sizeof(gdt_entries)-1, (uint32_t)&gdt_entries);
    reloadSegments();
}

void encodeGdtEntry(uint8_t *target, struct GDT source)
{
    // Check the limit to make sure that it can be encoded
    if (source.limit > 0xFFFFF) {kerror("GDT cannot encode limits larger than 0xFFFFF");}
    
    // Encode the limit
    target[0] = source.limit & 0xFF;
    target[1] = (source.limit >> 8) & 0xFF;
    target[6] = (source.limit >> 16) & 0x0F;
    
    // Encode the base
    target[2] = source.base & 0xFF;
    target[3] = (source.base >> 8) & 0xFF;
    target[4] = (source.base >> 16) & 0xFF;
    target[7] = (source.base >> 24) & 0xFF;
    
    // Encode the access byte
    target[5] = source.access;
    
    // Encode the flags
    target[6] |= (source.granularity << 4);
}