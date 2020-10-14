.globl arch_get_thread_id
arch_get_thread_id:
    mrs x0, mpidr_el1
    ret

.globl arch_get_el
arch_get_el:
    mrs x0, CurrentEL
    lsr x0, x0, #2
    ret

.globl arch_switch_to_usermode
arch_switch_to_usermode:
    ret