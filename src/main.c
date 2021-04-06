#include "drivers/bcm2835auxuart.h"
#include "drivers/bcm2835intc.h"

#include "interrutps/exceptions.h"
#include "interrutps/intman.h"

#include "scheduler/scheduler.h"

#include "aarch64.h"

void async_job(void* params) {
    while(1) {
        // Wait whatever seconds
        int i = 0;
        while(i < 0xFFFF) {
            i++;
            asm volatile("nop");
        }

        bcm2835auxuart_send_char('c');
        
        // Yield system call
        syscall(0);
    }
}

void main() {
    bcm2835auxuart_send_string("[+] Jelou guorl!\r\n");
    // Enable the interrupt controller and unmask 
    // interrupts from the cpu
    bcm2835intc_initialize();
    asm volatile ("msr daifclr, #2");

    intman_initialize();

    initialize_scheduler();

    while(1) {
        // Wait whatever seconds
        int i = 0;
        while(i < 0xFFFF) {
            i++;
            asm volatile("nop");
        }

        bcm2835auxuart_send_char('a');
        
        // Yield system call
        syscall(0);
    }
}