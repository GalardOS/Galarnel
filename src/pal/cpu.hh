#pragma once

#include "common.hh"

namespace pal { namespace cpu {

    void initialize();

    uint8 get_el();

    uint8 get_cpuid();

    void switch_usermode(long pc);

} }