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
        inline uint8 in8(uint16 port)
        {
            uint8 value;
            asm volatile("inb %1, %0"
                         : "=a"(value)
                         : "Nd"(port));
            return value;
        }

        inline uint16 in16(uint16 port)
        {
            uint16 value;
            asm volatile("inw %1, %0"
                         : "=a"(value)
                         : "Nd"(port));
            return value;
        }

        inline uint32 in32(uint16 port)
        {
            uint32 value;
            asm volatile("inl %1, %0"
                         : "=a"(value)
                         : "Nd"(port));
            return value;
        }

        inline void repeated_in16(uint16 port, uint16* buffer, int buffer_size)
        {
            asm volatile("rep insw"
                         : "+D"(buffer), "+c"(buffer_size)
                         : "d"(port)
                         : "memory");
        }

        inline void out8(uint16 port, uint8 value)
        {
            asm volatile("outb %0, %1" ::"a"(value), "Nd"(port));
        }

        inline void out16(uint16 port, uint16 value)
        {
            asm volatile("outw %0, %1" ::"a"(value), "Nd"(port));
        }

        inline void out32(uint16 port, uint32 value)
        {
            asm volatile("outl %0, %1" ::"a"(value), "Nd"(port));
        }

        inline void repeated_out16(uint16 port, const uint16* data, int data_size)
        {
            asm volatile("rep outsw"
                         : "+S"(data), "+c"(data_size)
                         : "d"(port));
        }

        inline void delay(uint32 microseconds)
        {
            for (uint32 i = 0; i < microseconds; ++i)
                cpu::ports::in8(0x80);
        }
    }

} }