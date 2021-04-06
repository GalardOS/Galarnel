#ifndef INTMAN_H
#define INTMAN_H

#include "common.h"
#include "exceptions.h"

enum error_type {
    ERROR_DATA_ABORT,
    ERROR_ILLEGAL_EXECUTION,
    ERROR_INSTRUCTION_ABORT,
    ERROR_FLOATING_POINT,
    ERROR_STACK_ALIGNMENT
};

void intman_initialize();

void intman_add_interrupt(uint32 irqid, void(*handler)(struct cpu_status));

void intman_add_synchronous(uint32 siid, void(*handler)(struct cpu_status));

#endif // INTMAN_H