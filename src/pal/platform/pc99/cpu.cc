#include "pal/cpu.hh"

namespace pal { namespace cpu {

    void initialize() {

    }

    uint8 get_el() {

    }

    uint8 get_cpuid() {

    }

    void switch_usermode(long pc) {

    }

    void wait_cycles(uint64 cycles) {
        int i = 0; 
        while(i < cycles) {
            int b = 1 + 1;
            i++;
        }
    }

} }