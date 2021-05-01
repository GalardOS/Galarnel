#include "scheduler.hh"

#include "drivers/bcm2835intc.hh"
#include "drivers/bcm2835auxuart.hh"

#include "memory/heap.hh"
#include "util/printf.hh"

#include "aarch64.hh"

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

static void enable_preemption() {
    // Enable the interrupt routing from the system timer
    drv::bcm2835intc::enable_irq(33);

    // Initialize the timer value to a random number (not gonna lie)
    value += 200000;
    *TIMER_C1 = value;
    
    // Send an acknowledgment in case a previous interrupt
    // was not handled properly or not handled at all
    uint32 acknowledgment = 1 << 1;
    *TIMER_CS = acknowledgment;
}

static void disable_preemption() {
    // Disable routing of the interrupt
    drv::bcm2835intc::disable_irq(33);
}

static void timer_handler(steel::cpu_status state) {
    // Disable preemption so that process switch does not 
    // occur while a process switch is happening
    disable_preemption();

    // Save the current running program status
    processes[running_process_index].context = state;

    printf("\r\nCHANGING FROM PID %d TO PID %d\r\n", running_process_index, (running_process_index + 1) % num_processes);

    // Change to the next process
    running_process_index = (running_process_index + 1) % num_processes;

    // Reenable the timer
    enable_preemption();
    
    // Return with the new context
    steel::return_from_event(processes[running_process_index].context);
}

static void synch_handler(steel::cpu_status state) {
    // The program counter advances one instruction not to repeat
    // the instruction that caused the exception
    state.pc += 4;

    // Execute the process switching
    timer_handler(state);
}

namespace scheduler {
    void initialize() {
        asm volatile ("msr daifclr, #2");

        // Enable the system timer interrupts and set the timer_handler
        // as the generic interrupt handler
        /// TODO: use some kind of interrupt manager
        drv::bcm2835intc::enable_irq(33);
        steel::event(steel::exception_type::interrupt, timer_handler);
        steel::event(steel::exception_type::synchronous, synch_handler);

        // Add the main process to the list, so it is not lost
        process main_process;
        main_process.process_type = proc_type::kernel;
        main_process.context.spsr = aarch64::spsr();
        processes[0] = main_process;
        num_processes = 1;

        // Set the first process as the running process
        running_process_index = 0;

        // Initialize the timer with a random value (not gonna lie)
        value = *TIMER_CLO;
        value += 200000;
        *TIMER_C1 = value;
    }

    pid add_kernel_process(kernel_function exec) {
        // Set the process type to a kernel process
        process proc;
        proc.process_type = proc_type::kernel;

        // Allocate the stack for the new process. The stack pointer
        // is moved 256 bytes beacouse all the registers are stored in the
        // stack.
        // IMPORTANT: the stack pointer should point to the top of the buffer
        //            and not the start (stack grows down!!!!)
        proc.stack_buffer = heap::allocate(4 * 1024);
        proc.context.sp = (uint64)(proc.stack_buffer) + 4 * 1024 - 1;
        proc.context.pc = (uint64)exec;
        proc.context.spsr = 0b0101;

        // Important that this addition process is not interrupted 
        disable_preemption();

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