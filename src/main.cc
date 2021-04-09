#include "libsteel/devices/mini_uart.hh"
#include "libsteel/events/event.hh"

#include "drivers/bcm2835intc.hh"
#include "drivers/bcm2835auxuart.hh"

#include "util/printf.hh"

#include "scheduler/scheduler.hh"

#define TIMER_CS        ((volatile uint32*)(0x3F000000+0x00003000))
#define TIMER_CLO       ((volatile uint32*)(0x3F000000+0x00003004))
#define TIMER_CHI       ((volatile uint32*)(0x3F000000+0x00003008))
#define TIMER_C0        ((volatile uint32*)(0x3F000000+0x0000300C))
#define TIMER_C1        ((volatile uint32*)(0x3F000000+0x00003010))
#define TIMER_C2        ((volatile uint32*)(0x3F000000+0x00003014))
#define TIMER_C3        ((volatile uint32*)(0x3F000000+0x00003018))

void inline_delay(uint64 count);

void async_process() {
    while(true) {
        drv::bcm2835auxuart::send('b');

        inline_delay(0xFFF);
        //asm volatile("brk 7");
    }
}

void async_process2() {
    while(true) {
        drv::bcm2835auxuart::send('c');

        inline_delay(0xFFF);
        //asm volatile("brk 7");
    }
}

void main(int argc, char** argv) {
    drv::bcm2835auxuart::init();
    drv::bcm2835auxuart::send_string("Jelou from iquernel!!\r\n");

    // Initialize the printf library
    __init_printf(nullptr, [](void* p, char c){ drv::bcm2835auxuart::send(c); });

    drv::bcm2835intc::initialize();

    scheduler::initialize();

    scheduler::add_kernel_process(async_process2);
    scheduler::add_kernel_process(async_process);


    while(true) {
        drv::bcm2835auxuart::send('a');
        inline_delay(0xFFFF);
        //asm volatile("brk 7");
    }
}