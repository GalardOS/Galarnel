#include "scheduler.hh"

#include "drivers/bcm2835intc.hh"
#include "drivers/bcm2835auxuart.hh"

#include "memory/heap.hh"

#define TIMER_CS        ((volatile uint32*)(0x3F000000+0x00003000))
#define TIMER_CLO       ((volatile uint32*)(0x3F000000+0x00003004))
#define TIMER_CHI       ((volatile uint32*)(0x3F000000+0x00003008))
#define TIMER_C0        ((volatile uint32*)(0x3F000000+0x0000300C))
#define TIMER_C1        ((volatile uint32*)(0x3F000000+0x00003010))
#define TIMER_C2        ((volatile uint32*)(0x3F000000+0x00003014))
#define TIMER_C3        ((volatile uint32*)(0x3F000000+0x00003018))

constexpr uint32 MAX_PROCESSES = 100;
scheduler::process processes[MAX_PROCESSES];
uint32 num_processes;

uint32 running_process_index;

static uint64 value;
static void timer_handler(steel::cpu_status state) {
    drv::bcm2835auxuart::send_string("taimer\r\n");

    // Save the current running program status
    processes[running_process_index].context = state;

    // Change to the next process
    running_process_index = (running_process_index + 1) % num_processes;
    steel::cpu_status next_status = processes[running_process_index].context;

    value += 100000;
    *TIMER_C1 = value;

    // Send acknowledgment to timer
    uint32 acknowledgment = 1 << 1;
    *TIMER_CS = acknowledgment;

    steel::return_from_event(next_status);
}

static void enable_preemption() {
    drv::bcm2835intc::enable_irq(33);

    // Initialize the timer counter
    value = *TIMER_C0;
    value += 100000;
    *TIMER_C1 = value;
}

static void disable_preemption() {
    drv::bcm2835intc::disable_irq(33);
}

namespace scheduler {


    void initialize() {
        asm volatile ("msr daifclr, #2");

        // Enable the system timer interrupts and set the timer_handler
        // as the generic interrupt handler
        /// TODO: use some kind of interrupt manager
        drv::bcm2835intc::enable_irq(33);
        steel::event(steel::exception_type::interrupt, timer_handler);

        // Add the main process to the list, so it is not lost
        process main_process;
        main_process.process_type = proc_type::kernel;
        processes[0] = main_process;
        num_processes = 1;

        // Set the first process as the running process
        running_process_index = 0;

        // Initialize the timer counter
        value = *TIMER_C0;
        value += 100000;
        *TIMER_C1 = value;
    }

    pid add_kernel_process(kernel_function exec) {
        // Imporant for not interrupting the creation
        // process
        disable_preemption();

        process proc;
        proc.process_type = proc_type::kernel;

        // Allocate the stack for the new process. The stack pointer
        // is moved 256 bytes beacouse all the registers are stored in the
        // stack.
        proc.context.sp = (uint64)heap::allocate(4 * 1024);
        proc.context.sp += 256;

        proc.context.pc = (uint64)exec;

        // Add the process to the processes list
        processes[num_processes] = proc;
        num_processes++;
        enable_preemption();
        return num_processes - 1;
    }

    bool has_finalized() {
        return num_processes == 0;
    }
}