#pragma once

#include "common.hh"

#define GDT_FLAG_NULL 0
#define GDT_FLAG_DATASEG 0x02
#define GDT_FLAG_CODESEG 0x0a
#define GDT_FLAG_TSS 0x09

#define GDT_FLAG_SEGMENT 0x10
#define GDT_FLAG_RING0 0x00
#define GDT_FLAG_RING3 0x60
#define GDT_FLAG_PRESENT 0x80

#define GDT_FLAG_4K_GRAN 0x800
#define GDT_FLAG_32_BIT 0x400

namespace gdt {

    typedef uint64 segment;
    typedef uint16 flags;

    void reload_table();

    void set_entry(uint16 i, uint32 base, uint32 limit, gdt::flags flags);
    gdt::segment get_entry(uint16 i);
    uint16 get_entry_offset(uint16 i);
};