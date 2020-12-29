#include "common.hh"

#include "drivers/gdt/gdt.hh"

#include "pal/debug.hh"
#include "pal/intc.hh"

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

    pal::intc::initialize();

    // Jump to kernel code 
    kernel_main();
}