#pragma once

#include "../common.hh"

namespace steel {
    struct cpu_status {
        uint64 sp;
        uint64 pc;
        uint64 spsr;
    };

    enum class exception_type : uint64 {
        synchronous = 0,
        interrupt = 1,
        finterrupt = 2,
        serror = 3
    };

    typedef void(*event_handler)(cpu_status status);

    void event(exception_type type, event_handler handler);

    void return_from_event(const cpu_status& status);
}