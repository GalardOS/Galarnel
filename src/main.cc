#include "libsteel/events/event.hh"

#include "drivers/bcm2835intc.hh"
#include "drivers/bcm2835auxuart.hh"

#include "util/printf.hh"

#include "scheduler/scheduler.hh"

#include "aarch64.hh"

#define TIMER_CS        ((volatile uint32*)(0x3F000000+0x00003000))
#define TIMER_CLO       ((volatile uint32*)(0x3F000000+0x00003004))
#define TIMER_CHI       ((volatile uint32*)(0x3F000000+0x00003008))
#define TIMER_C0        ((volatile uint32*)(0x3F000000+0x0000300C))
#define TIMER_C1        ((volatile uint32*)(0x3F000000+0x00003010))
#define TIMER_C2        ((volatile uint32*)(0x3F000000+0x00003014))
#define TIMER_C3        ((volatile uint32*)(0x3F000000+0x00003018))

void inline_delay(uint64 count);

constexpr int TIME_TO_WAIT = 0xFFFF;

void async_process() {
    int i = 0;
    while(true) {
        i++;

        inline_delay(TIME_TO_WAIT);
//        printf("async_process1: %d\r\n", i);
    }

    printf("process1 finished\r\n");
}

void async_process2() {
    int i = 0;
    while(true) {
        i++;

        inline_delay(TIME_TO_WAIT);
//        printf("async_process2: %d\r\n", i);
    }
    printf("process2 finished\r\n");
}

void main(int argc, char** argv) {
    drv::bcm2835auxuart::init();
    drv::bcm2835auxuart::send_string("Kernel entry point reached\r\n");

    // Initialize the printf library
    __init_printf(nullptr, [](void* p, char c){ drv::bcm2835auxuart::send(c); });

    printf("Processor state:\r\n");
    printf("  · EL   = %d\r\n", aarch64::el());

    drv::bcm2835intc::initialize();

    scheduler::initialize();

    // Add two random processes for testing purposes
    scheduler::add_kernel_process(async_process);
    scheduler::add_kernel_process(async_process2);
    scheduler::add_kernel_process(async_process2);
    scheduler::add_kernel_process(async_process2);
    scheduler::add_kernel_process(async_process2);
    scheduler::add_kernel_process(async_process2);
    scheduler::add_kernel_process(async_process2);
    scheduler::add_kernel_process(async_process2);
    scheduler::add_kernel_process(async_process2);

    int i = 0;
    while(true) {
        i++;

        inline_delay(TIME_TO_WAIT);
//        printf("main: %d\r\n", i);
    }
    printf("main finished\r\n");
}