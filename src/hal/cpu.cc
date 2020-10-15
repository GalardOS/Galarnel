#include "cpu.hh"

extern "C" {
    #include "hal/aarch64/aarch64_cpu.h"
    #include "hal/aarch64/aarch64_sysregs.h"
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

    long get_sysreg(sysreg reg) {
        if(reg == sysreg::esr_el1)
            return arch_sysreg_esr_el1();
        else if(reg == sysreg::esr_el0)
            return arch_sysreg_esr_el0();

        return 0;
    }
}