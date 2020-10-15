.globl arch_sysreg_esr_el1
arch_sysreg_esr_el1:
    mrs x0, esr_el1
    ret

.globl arch_sysreg_esr_el0
arch_sysreg_esr_el0:
    mrs x0, esr_el0
    ret