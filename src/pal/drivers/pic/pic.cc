#include "drivers/pic/pic.hh"

#include "drivers/gdt/gdt.hh"

#define KERNEL_CODE_SEGMENT 1
#define KERNEL_DATA_SEGMENT 2
#define USER_CODE_SEGMENT   3
#define USER_DATA_SEGMENT   4

static void local_interrupt_ignore() {
    return;
}

namespace pic {
    pic::idt_structure descriptors[256];

    struct idt_structure {
        uint16 address_low_bits;
        uint16 code_segment_selector;
        uint8 reseved;
        uint8 access;
        uint16 address_high_bits;
    } __attribute__((packed));

    void initialize() {
        // Setup global descriptor table
        gdt::set_entry(0, 0, 0, GDT_FLAG_NULL);
        gdt::set_entry(1, 0, 0xFFFFF, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_CODESEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT); 
        gdt::set_entry(2, 0, 0xFFFFF, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_DATASEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT);
        gdt::set_entry(3, 0, 0xFFFFF, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_CODESEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT | GDT_FLAG_RING3);
        gdt::set_entry(4, 0, 0xFFFFF, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_DATASEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT | GDT_FLAG_RING3);
        gdt::reload_table();
        
        // Setup all the descriptors as ignore when not present
        for(uint16 i = 0; i < 256; i++) {
            // Setup the ignore descriptor
            pic::int_descriptor descriptor;
            descriptor.int_number = i;
            descriptor.code_segment_selector_offset = gdt::get_entry_offset(KERNEL_CODE_SEGMENT);
            descriptor.handler = &local_interrupt_ignore;
            descriptor.priviledge_level = 0;                                                // Priviledge level to kernel mode
            descriptor.descriptor_type = pic::desc_type::interrupt;

            // Add the descriptor to IDT
            pic::set_entry(descriptor);
        }

        // TODO: load the idt into PIC registers
    }


    void set_entry(pic::int_descriptor entry) {
        // Set handler address
        descriptors[entry.int_number].address_low_bits = ((uint32)entry.handler) & 0xFFFF;
        descriptors[entry.int_number].address_high_bits = ((uint32)entry.handler >> 16) & 0xFFFF;
        
        // Set the code segment selector
        descriptors[entry.int_number].code_segment_selector = entry.code_segment_selector_offset;
        
        // Reserved byte NEEDS to be 0
        descriptors[entry.int_number].reserved = 0;

        // Sets the flags for entry access (0x80 flag sets the descriptor as present)
        descriptors[entry.int_number].access = 0x80 | (uint8)entry.descriptor_type | ((entry.priviledge_level & 3) << 5);
    }
}