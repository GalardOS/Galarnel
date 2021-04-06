#include "intman.h"

#include "aarch64.h"
#include "drivers/bcm2835auxuart.h"

void(*synchronous_handlers[256])(struct cpu_status);
void(*interrupt_handlers[256])(struct cpu_status);

static void synchronous_handler(struct cpu_status status) {
    uint64 syndrome = esr_el1();
   
    uint64 reason = syndrome >> 26;
    switch(reason) {
        case 0b000000: bcm2835auxuart_send_string("Unknown\r\n"); break;
        case 0b000001: bcm2835auxuart_send_string("Trapped WFI/WFE\r\n"); break;
        case 0b001110: bcm2835auxuart_send_string("Illegal execution\r\n"); break;
        case 0b010101: 
            bcm2835auxuart_send_string("System call\r\n");
            if(synchronous_handlers[0] != NULL) synchronous_handlers[0](status);
            break;
        case 0b100000: bcm2835auxuart_send_string("Instruction abort, lower EL\r\n"); break;
        case 0b100001: bcm2835auxuart_send_string("Instruction abort, same EL\r\n"); break;
        case 0b100010: bcm2835auxuart_send_string("Instruction alignment fault\r\n"); break;
        case 0b100100: bcm2835auxuart_send_string("Data abort, lower EL\r\n"); break;
        case 0b100101: bcm2835auxuart_send_string("Data abort, same EL\r\n"); break;
        case 0b100110: bcm2835auxuart_send_string("Stack alignment fault\r\n"); break;
        case 0b101100: bcm2835auxuart_send_string("Floating point\r\n"); break;
        
        // We will threat this as a system call, as svc instruction jumps to el2
        // and that would be painful to handle.
        default:
            bcm2835auxuart_send_string("System call\r\n");
            if(synchronous_handlers[0] != NULL) synchronous_handlers[0](status);
            break;
    }
}

static void interrupt_handler(struct cpu_status status) {
    bcm2835auxuart_send_string("Interrupt!\r\n");
    bcm2835auxuart_send_string("Defaulting to interrupt 33...\r\n");
}

void intman_initialize() {
    // Setup the exception handlers
    set_exception_handler(EXCEPTION_SYNCHRONOUS, synchronous_handler);
    set_exception_handler(EXCEPTION_INTERRUPT, interrupt_handler);
}

void intman_add_interrupt(uint32 irqid, void(*handler)(struct cpu_status)) {

}

void intman_add_synchronous(uint32 siid, void(*handler)(struct cpu_status)) {
    if(synchronous_handlers[siid] != NULL) {
        bcm2835auxuart_send_string("Warning: ovewritting already added handler\r\n");
    }

    synchronous_handlers[siid] = handler;
}