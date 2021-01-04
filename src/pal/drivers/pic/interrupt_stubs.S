.global local_interrupt_ignore
local_interrupt_ignore:
    iret

.macro interrupt_request_handler irqnum
.endm

generic_interrupt_jumper:
    pusha
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs

