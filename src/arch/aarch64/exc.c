#include "exc.h"

static exc_vector_table current_table;

// Function prototype from exc.S
void setup_vector_reg();

void exc_setup_vector(exc_vector_table handlers) {
    // Copy the vector table
    current_table.syn_handler = handlers.syn_handler;
    current_table.irq_handler = handlers.irq_handler;
    current_table.fiq_handler = handlers.fiq_handler;
    current_table.err_handler = handlers.err_handler;

    // Setup arm vector table
    setup_vector_reg();
}

void synchronous_exception(long esr, long elr) {
    if(current_table.syn_handler != 0)
        current_table.syn_handler(esr, elr);
}

void irq_exception(long esr, long elr) {
    if(current_table.irq_handler != 0)
        current_table.irq_handler(esr, elr);
}

void fiq_exception(long esr, long elr) {
    if(current_table.fiq_handler != 0)
        current_table.fiq_handler(esr, elr);
}

void error_exception(long esr, long elr) {
    if(current_table.err_handler != 0)
        current_table.err_handler(esr, elr);
}