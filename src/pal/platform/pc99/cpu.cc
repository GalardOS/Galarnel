#include "pal/cpu.hh"

namespace pal { namespace cpu {

    static void wait_cycles_impl(uint64 cycles) {
        int i = 0; 
        while(i < cycles) {
            int b = 1 + 1;
            i++;
        }
    }

    void initialize() {
        get_el = nullptr;
        get_cpuid = nullptr;
        switch_usermode = nullptr;
        wait_cycles = wait_cycles_impl;
    }
} }