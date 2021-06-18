#include "aarch64.hh"

namespace aarch64 {
    uint64 spsr() {
        uint64 res;
        asm volatile("mrs %0, spsr_el1"
                      : "=r"(res));
        return res;
    }

    uint64 el() {
        uint64 res;
        asm volatile("mrs %0, CurrentEL"
                      : "=r"(res));
        res = res >> 2;
        return res;
    }

    uint64 esr() {
        uint64 res;
        asm volatile("mrs %0, esr_el1"
                      : "=r"(res));
        return res;
    }
}