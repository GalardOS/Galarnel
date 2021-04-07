.global cltimer_get_freq
cltimer_get_freq:
    // Ensure correct memory access ordering
    isb

    // Get the value from the register and return
    mrs x0, cntfrq_el0
    ret

.global cltimer_set_compare
cltimer_set_compare:
    // Ensure correct memory access ordering
    isb

    // Set the value of the register and return
    msr cntp_cval_el0, x0
    ret

.global cltimer_get_value
cltimer_get_value:
    // Ensure correct memory access ordering
    isb

    // Get the value from the register and return
    mrs x0, cntp_tval_el0
    ret