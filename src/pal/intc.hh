#pragma once

#include "common.hh"

#define CPUID(x) (BIT(x))

namespace pal { namespace intc {
    typedef uint32 handler_id;
    typedef void(*intc_handler)(void);
    typedef uint16 cpuid;

    typedef uint16 reason;

    enum class int_type {
        syscall,
        error,
        hardware
    };

    struct irq_handler_descriptor {
        uint32 irqid;
        uint16 target;
        intc_handler handler;
        int_type type;
    };

    void initialize();

    handler_id add_handler(const irq_handler_descriptor& descriptor);

    void remove_handler(const irq_handler_descriptor& descriptor);

    void add_error_handler(void(*error_handler)(reason));

    void enable();

    void disable();
} }