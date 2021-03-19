#include "libsteel/devices/mini_uart.hh"
#include "libsteel/events/event.hh"

#include "drivers/bcm2835intc.hh"
#include "drivers/bcm2835auxuart.hh"

#define TIMER_CS        ((volatile uint32*)(0x3F000000+0x00003000))
#define TIMER_CLO       ((volatile uint32*)(0x3F000000+0x00003004))
#define TIMER_CHI       ((volatile uint32*)(0x3F000000+0x00003008))
#define TIMER_C0        ((volatile uint32*)(0x3F000000+0x0000300C))
#define TIMER_C1        ((volatile uint32*)(0x3F000000+0x00003010))
#define TIMER_C2        ((volatile uint32*)(0x3F000000+0x00003014))
#define TIMER_C3        ((volatile uint32*)(0x3F000000+0x00003018))

uint32 value;

void timer_handler(uint64, uint64) {
    value += 200000;
    *TIMER_C1 = value;

    // Send acknowledgment to timer
    uint32 acknowledgment = 1 << 1;
    *TIMER_CS = acknowledgment;
}

void main(int argc, char** argv) {
    drv::bcm2835auxuart::init();
    drv::bcm2835auxuart::send_string("Jelou from iquernel!!\r\n");
    
    drv::bcm2835intc::initialize();

    {
        asm volatile ("msr daifclr, #2");

        // Enable the arm timer interrupts
        drv::bcm2835intc::enable_irq(33);
        steel::event(steel::exception_type::interrupt, timer_handler);

        // Initialize the timer counter
        value = *TIMER_C0;
        value += 200000;
        *TIMER_C1 = value;
    }

    while(true);
}