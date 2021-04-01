#include "drivers/bcm2835auxuart.h"
#include "drivers/bcm2835intc.h"

#include "interrutps/exceptions.h"

void synchronous_handler(struct cpu_status context) {
    bcm2835auxuart_send_string("Synchronous interrupt!!\r\n");

    context.pc += 4;
    eret_with_context(context);
}

void main() {
    bcm2835auxuart_send_string("[+] Jelou guorl!\r\n");
    // Enable the interrupt controller and unmask 
    // interrupts from the cpu
    bcm2835intc_initialize();
    asm volatile ("msr daifclr, #2");

    set_exception_handler(EXCEPTION_SYNCHRONOUS, synchronous_handler);

    asm volatile("brk #7");

    while(1) {
        // Wait whatever seconds
        int i = 0;
        while(i < 0xFFFF) {
            i++;
            asm volatile("nop");
        }

        bcm2835auxuart_send_char('a');
    }
}