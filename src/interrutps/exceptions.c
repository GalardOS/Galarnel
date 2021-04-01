#include "exceptions.h"

#include "drivers/bcm2835auxuart.h"

extern void set_cpu_status_and_eret(uint64 sp, uint64 pc, uint64 spsr);

static void(*synchronous_handler)(struct cpu_status);
static void(*interrupt_handler)(struct cpu_status);
static void(*finterrupt_handler)(struct cpu_status);
static void(*serror_handler)(struct cpu_status);

void exception_entry(uint64 type, uint64 esr, uint64 elr, uint64 sp, uint64 spsr) {
    // Create the cpu status from the data given by the 
    // exception entry
    struct cpu_status status;
    status.pc = elr;
    status.sp = sp;
    status.spsr = spsr;

    switch(type) {
        case EXCEPTION_SYNCHRONOUS:
            synchronous_handler(status);
            break;
        case EXCEPTION_INTERRUPT:
            interrupt_handler(status);
            break; 
        case EXCEPTION_FINTERRUPT: 
            finterrupt_handler(status);
            break;
        case EXCEPTION_SERROR:
            serror_handler(status);
            break;
        default:
            bcm2835auxuart_send_string("[E] Entered unknown exception type");
            break;
    }

    eret_with_context(status);
}

void set_exception_handler(enum exception_type type, void(*handler)(struct cpu_status)) {
    switch(type) {
        case EXCEPTION_SYNCHRONOUS:
            synchronous_handler = handler;
            break;
        case EXCEPTION_INTERRUPT: 
            interrupt_handler = handler;
            break;
        case EXCEPTION_FINTERRUPT: 
            finterrupt_handler = handler;
            break;
        case EXCEPTION_SERROR: 
            serror_handler = handler;
            break;
        default: 
            bcm2835auxuart_send_string("[E] Unknown exception type");
            break;
    }
}

void eret_with_context(struct cpu_status status) {
    set_cpu_status_and_eret(status.sp, status.pc, status.spsr);
}