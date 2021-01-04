#include "pal/cpu.hh"

namespace pal { namespace cpu {

    struct context {
        int32 eax;
        int32 ebx;
        int32 ecx;
        int32 edx;
        int32 esi;
        int32 edi;
        int32 ebp;

        int32 ds;
        int32 es;
        int32 fs;
        int32 gs;
    };

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