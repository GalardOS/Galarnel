#include "common.hh"

#include "drivers/gdt/gdt.hh"

#include "pal/debug.hh"

#include "kernel/kernel.hh"

typedef void (*ctor)();
extern "C" ctor start_ctors;
extern "C" ctor end_ctors;
extern "C" void call_global_constructors() {
    for(ctor* constructor = &start_ctors; constructor != &end_ctors; constructor++) {
        (*constructor)();
    }
}

extern "C" void pre_configuration(void* mboot_header, uint32 magic) {
    // Calls the global constructors for all the global variables.
    call_global_constructors();

    // Initialize debug output
    pal::debug::initialize();
    pal::debug::write_line("[+] Pre configuring the kernel");

    // Setup the GDT for interrupts
    gdt::set_entry(0, 0, 0, GDT_FLAG_NULL);
    gdt::set_entry(1, 0, 0xFFFFF, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_CODESEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT);
    gdt::set_entry(2, 0, 0xFFFFF, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_DATASEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT);
    gdt::set_entry(3, 0, 0xFFFFF, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_CODESEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT | GDT_FLAG_RING3);
    gdt::set_entry(4, 0, 0xFFFFF, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_DATASEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT | GDT_FLAG_RING3);
    gdt::reload_table();

    // Jump to kernel code 
    kernel_main();
}