#include "aarch64_excpt.h"
#include "aarch64_sysregs.h"

struct {
    vect_func sync;
    vect_func irq;
    vect_func fiq;
    vect_func err;
} arch_vector_table;

void arch_setup_vector(vect_func sync, vect_func irq, vect_func fiq, vect_func err) {
    arch_vector_table.sync = sync;
    arch_vector_table.irq = irq;
    arch_vector_table.fiq = fiq;
    arch_vector_table.err = err;

    arch_setup_vector_regs();
}

void synchronous_exception(void) {
    long esr = arch_sysreg_esr_el1();
    arch_vector_table.sync(esr);
}

void irq_exception(void) {
    long esr = arch_sysreg_esr_el1();
    arch_vector_table.irq(esr);
}

void fiq_exception(void) {
    long esr = arch_sysreg_esr_el1();
    arch_vector_table.fiq(esr);
}

void error_exception(void) {
    long esr = arch_sysreg_esr_el1();
    arch_vector_table.err(esr);
}