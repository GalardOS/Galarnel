#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "common.h"

struct cpu_status {
    uint64 sp;
    uint64 pc;
    uint64 spsr;
};

enum exception_type {
    EXCEPTION_SYNCHRONOUS = 0,
    EXCEPTION_INTERRUPT = 1,
    EXCEPTION_FINTERRUPT = 2,
    EXCEPTION_SERROR = 3
};

/*
 * Setups the vector table of the ARM cpu so that we can have
 * entries for all the different exception types.
 */
void setup_exceptions();

/*
 * Sets up a handler for a specific exception type
 * 
 * @param type: exception type to set the handler for
 * @param handler: handler to be set
 */
void set_exception_handler(enum exception_type type, void(*handler)(struct cpu_status));

/*
 * Return from an exception with a given cpu status
 * 
 * @param status: cpu status to be set when returning
 */
void eret_with_context(struct cpu_status status);

#endif // EXCEPTIONS_H