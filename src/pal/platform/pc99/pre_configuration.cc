#include "common.hh"

#include "pal/debug.hh"
#include "pal/cpu.hh"

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

    pal::debug::initialize();
    pal::debug::write_line("[+] Pre configuring the kernel\r\n");
    
    pal::cpu::initialize();
}