#pragma once

#include "libsteel/common.hh"
#include "libsteel/events/event.hh"

namespace scheduler {
    typedef void(*kernel_function)();

    using pid = uint64;
    
    enum class proc_type {
        kernel, 
        user
    };

    struct process {
        proc_type process_type;
        steel::cpu_status status;
    };

    void initialize();

    pid add_kernel_process(kernel_function exec);

    bool has_finalized();
}