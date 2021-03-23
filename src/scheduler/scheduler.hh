#pragma once

#include "libsteel/common.hh"

namespace scheduler {
    typedef void(*kernel_function)();

    using pid = uint64;
    
    enum class proc_type {
        kernel, 
        user
    };

    struct process {
        proc_type process_type;
        // cpu_context context;
    };


    void initialize();

    pid add_kernel_process(kernel_function exec);
}