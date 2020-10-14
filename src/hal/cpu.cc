#include "cpu.hh"

extern "C" {
    #include "hal/aarch64/aarch64_cpu.h"
}

namespace cpu {
    int get_thread_id() {
        return arch_get_thread_id();
    }

    int get_el() {
        return arch_get_el();
    }
    
    void switch_user_mode() {
        arch_switch_to_usermode();
    }
}