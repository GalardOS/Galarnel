#ifndef AARCH64_CPU_H
#define AARCH64_CPU_H

int arch_get_thread_id();

int arch_get_el();

void arch_switch_to_usermode();

#endif // AARCH64_CPU_H