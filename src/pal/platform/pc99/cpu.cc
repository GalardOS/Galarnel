#include "pal/cpu.hh"

namespace pal { namespace cpu {
    uint8(*get_el)() = nullptr;

    uint8(*get_cpuid)() = nullptr;

    void(*switch_usermode)(long pc) = nullptr;
    
    void(*wait_cycles)(uint64 cycles) = nullptr;

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