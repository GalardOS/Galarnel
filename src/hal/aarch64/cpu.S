.globl cpu_get_thread_id
cpu_get_thread_id:
    mrs x0, mpidr_el1
    ret

.globl cpu_get_el
cpu_get_el:
    mrs x0, CurrentEL
    lsr x0, x0, #2
    ret

.globl cpu_switch_usermode
cpu_switch_usermode:
    ret