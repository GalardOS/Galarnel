#ifndef AARCH64_EXCPT_H
#define AARCH64_EXCPT_H

typedef void(*vect_func)(long);

void arch_setup_vector(vect_func sync, vect_func irq, vect_func fiq, vect_func err);

void arch_setup_vector_regs();

#endif // AARCH64_EXCPT_H