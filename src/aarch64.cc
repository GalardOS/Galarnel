#include "aarch64.hh"

namespace aarch64 {
    uint64 spsr() {
        uint64 res;
        asm volatile("mrs %0, spsr_el1"
                      : "=r"(res));
        return res;
    }
}