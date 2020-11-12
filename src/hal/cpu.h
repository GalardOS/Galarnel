#ifndef HAL_CPU_H
#define HAL_CPU_H

#ifdef __cplusplus
extern "C" {
#endif

int cpu_get_thread_id();

int cpu_get_el();

void cpu_switch_usermode(long pc);

#ifdef __cplusplus
}
#endif

#endif // HAL_CPU_H