#include "pal/cpu.hh"

namespace pal { namespace cpu {

    void initialize() {

    }

    void wait_cycles(uint64 cycles) {
        int i = 0; 
        while(i < cycles) {
            int b = 1 + 1;
            i++;
        }
    }
} }