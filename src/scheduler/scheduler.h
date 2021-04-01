#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "interrutps/exceptions.h"

enum process_type {
    PROCESS_TYPE_KERNEL,
    PROCESS_TYPE_USER
};

struct process_control_block {
    struct cpu_status status;
    enum process_type type;
};

void initialize_scheduler();

void add_kernel_proces(void(*function)(void* params));

#endif // SCHEDULER_H