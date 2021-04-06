.global esr_el1
esr_el1:
    mrs x0, esr_el1
    ret

.global syscall
syscall:
    mov x8, x0
    brk 0x0