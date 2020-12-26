#pragma once

#include "common.hh"

namespace pal { namespace cpu {

    void initialize();

    extern uint8(*get_el)();

    extern uint8(*get_cpuid)();

    extern void(*switch_usermode)(long pc);

    extern void(*wait_cycles)(uint64 cycles);

} }