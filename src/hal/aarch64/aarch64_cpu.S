.globl get_thread_id
get_thread_id: 
    msr x0, mpidr_el1
    ret

.globl get_el
get_el:
    mrs x0, CurrentEL
    lsr x0, x0, #2
    ret

.globl switch_to_usermode
switch_to_usermode: