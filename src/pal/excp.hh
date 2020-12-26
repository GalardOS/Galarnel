#pragma once

#include "common.hh"

namespace pal { namespace excp {

    struct table {
        void(*synchronized)(uint32);
        void(*interrupts)(uint32);
        void(*fast_interrupts)(uint32);
    };

    void setup_handlers(const table& table);

    void(*set_context_pointer)(long ptr);

} }