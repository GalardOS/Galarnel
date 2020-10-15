#pragma once



namespace cpu {
    
    enum class sysreg {
        esr_el1, esr_el0
    };

    int get_thread_id();

    int get_el();
    
    void switch_to_usermode();

    long get_sysreg(sysreg reg);
}