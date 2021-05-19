#pragma once

#include "libsteel/common.hh"

namespace drv {
    namespace bcm2835timer {
        void initialize(uint64 cycles);
        
        void restart(uint64 cycles);
    }
}