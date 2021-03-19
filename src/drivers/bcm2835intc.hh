#pragma once 

#include "libsteel/common.hh"

namespace drv {
    namespace bcm2835intc {
        void initialize();

        void enable_irq(uint32 irq_num);
        void disable_irq(uint32 irq_num);
    }
}