#include "scheduler.hh"

#include "drivers/bcm2835intc.hh"

#include "libsteel/events/event.hh"

#define TIMER_CS        ((volatile uint32*)(0x3F000000+0x00003000))
#define TIMER_CLO       ((volatile uint32*)(0x3F000000+0x00003004))
#define TIMER_CHI       ((volatile uint32*)(0x3F000000+0x00003008))
#define TIMER_C0        ((volatile uint32*)(0x3F000000+0x0000300C))
#define TIMER_C1        ((volatile uint32*)(0x3F000000+0x00003010))
#define TIMER_C2        ((volatile uint32*)(0x3F000000+0x00003014))
#define TIMER_C3        ((volatile uint32*)(0x3F000000+0x00003018))

static uint64 value;
static void timer_handler(uint64, uint64) {
    value += 200000;
    *TIMER_C1 = value;

    // Send acknowledgment to timer
    uint32 acknowledgment = 1 << 1;
    *TIMER_CS = acknowledgment;
}

namespace scheduler {
    constexpr uint32 MAX_PROCESSES = 100;
    process processes[MAX_PROCESSES];
    uint32 num_processes;

    void initialize() {
        num_processes = 0;

        asm volatile ("msr daifclr, #2");

        // Enable the system timer interrupts and set the timer_handler
        // as the generic interrupt handler
        /// TODO: use some kind of interrupt manager
        drv::bcm2835intc::enable_irq(33);
        steel::event(steel::exception_type::interrupt, timer_handler);

        // Initialize the timer counter
        value = *TIMER_C0;
        value += 200000;
        *TIMER_C1 = value;
    }

    pid add_kernel_process(kernel_function exec) {
        // Create the process
        process proc;
        proc.process_type = proc_type::kernel;

        // Add the process to the processes list
        processes[num_processes] = proc;
        num_processes++;

        return num_processes - 1;
    }
}