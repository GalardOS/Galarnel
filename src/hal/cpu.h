#ifndef HAL_CPU_H
#define HAL_CPU_H

extern "C" {

    int cpu_get_thread();

    int cpu_get_el();

    void cpu_switch_usermode(long pc);
}

#endif // HAL_CPU_H