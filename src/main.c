#include "drivers/bcm2835auxuart.h"
#include "drivers/bcm2835intc.h"

#include "interrutps/exceptions.h"

#define TIMER_CS        ((volatile uint32*)(0x3F000000+0x00003000))
#define TIMER_CLO       ((volatile uint32*)(0x3F000000+0x00003004))
#define TIMER_CHI       ((volatile uint32*)(0x3F000000+0x00003008))
#define TIMER_C0        ((volatile uint32*)(0x3F000000+0x0000300C))
#define TIMER_C1        ((volatile uint32*)(0x3F000000+0x00003010))
#define TIMER_C2        ((volatile uint32*)(0x3F000000+0x00003014))
#define TIMER_C3        ((volatile uint32*)(0x3F000000+0x00003018))


static uint64 value;
void timer_handler(struct cpu_status context) {
    bcm2835auxuart_send_string("Timer interrupt\r\n");
    while(1);

    value += 200000;
    *TIMER_C1 = value;
    uint32 acknowledgment = 1 << 1;
    *TIMER_CS = acknowledgment;

    eret_with_context(context);
}

void main() {
    bcm2835auxuart_send_string("[+] Jelou guorl!\r\n");

    set_exception_handler(EXCEPTION_INTERRUPT, timer_handler);
    
    asm volatile ("msr daifclr, #2");
   
    bcm2835intc_enable(33);

    value = *TIMER_C0;
    value += 200000;
    *TIMER_C1 = value;

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