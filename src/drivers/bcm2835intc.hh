#pragma once 

#include "../../lib/libsteel/lib/common.hh"

namespace drv {
    namespace bcm2835intc {
        void initialize();

        void enable_arm_irq(uint32 irq);
        void enable_peripheral_irq(uint32 irq);
    }
}