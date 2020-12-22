#pragma once

#include "common.hh"

#define CPUID(x) (BIT(x))

namespace pal { namespace intc {
    typedef uint32 handler_id;
    typedef void(*intc_handler)(void);
    typedef uint16 cpuid;

    struct handler_descriptor {
        uint32 irqid;
        uint16 target;
        intc_handler handler;
    };

    void initialize();

    handler_id add_handler(const handler_descriptor& descriptor);

    void remove_handler(handler_id descriptor);
} }