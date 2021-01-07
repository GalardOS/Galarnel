#pragma once

#include "common.hh"

namespace pal { namespace cpu {

    struct context;

    void initialize();

    uint8 get_el();

    uint8 get_cpuid();

    void switch_usermode(pal::cpu::context context);

    void wait_cycles(uint64 cycles);

    namespace ports {
        uint8 in8(uint16 port);

        uint16 in16(uint16 port);

        uint32 in32(uint16 port);

        void repeated_in16(uint16 port, uint16* buffer, int buffer_size);

        void out8(uint16 port, uint8 value);

        void out16(uint16 port, uint16 value);

        void out32(uint16 port, uint32 value);

        void repeated_out16(uint16 port, const uint16* data, int data_size);

        void delay(uint32 microseconds);
    }

} }