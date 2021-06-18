#include "scheduler.hh"

#include "drivers/bcm2835intc.hh"
#include "drivers/bcm2835auxuart.hh"
#include "drivers/bcm2835timer.hh"

#include "memory/heap.hh"
#include "util/printf.hh"

#include "aarch64.hh"


constexpr uint32 MAX_PROCESSES = 100;
scheduler::process processes[MAX_PROCESSES];
volatile uint32 num_processes;

volatile uint32 running_process_index;


static void enable_preemption() {
    // Enable the interrupt routing from the system timer
    drv::bcm2835intc::enable_irq(33);

    drv::bcm2835timer::restart(20000);
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
    asm volatile("isb");
    printf("p%d process:\npc = %d\n\n", running_process_index, state.pc);

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
    disable_preemption();

    printf("Unexpected synchronous exception:\r\n");
    switch(aarch64::esr() >> 26) {
        case 0b000000: printf(" · Unknown"); break;
        case 0b000001: printf(" · Trapped WFI/WFE"); break;
        case 0b001110: printf(" · Illegal execution"); break;
        case 0b010101: printf(" · System call"); break;
        case 0b100000: printf(" · Instruction abort, lower EL"); break;
        case 0b100001: printf(" · Instruction abort, same EL"); break;
        case 0b100010: printf(" · Instruction alignment fault"); break;
        case 0b100100: printf(" · Data abort, lower EL"); break;
        case 0b100101: printf(" · Data abort, same EL"); break;
        case 0b100110: printf(" · Stack alignment fault"); break;
        case 0b101100: printf(" · Floating point"); break;
        default: printf(" · Unknown"); break;
    }
    printf("\r\n");
    if(aarch64::esr() >> 26 == 0b100100 || aarch64::esr() >> 26 == 0b100101) {
        switch((aarch64::esr() >> 2)&0x3) {
            case 0: printf("   · Address size fault"); break;
            case 1: printf("   · Translation fault"); break;
            case 2: printf("   · Access flag fault"); break;
            case 3: printf("   · Permission fault"); break;
        }
        switch(aarch64::esr() & 0x3) {
            case 0: printf(" at level 0"); break;
            case 1: printf(" at level 1"); break;
            case 2: printf(" at level 2"); break;
            case 3: printf(" at level 3"); break;
        }
    }
    while(true);

    // Execute the process switching
    timer_handler(state);
}

namespace scheduler {
    void initialize() {
        // Disable interrupt routing to the CPU while initializing
        // the scheduler
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

        drv::bcm2835timer::initialize(20000);
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

        printf("process added:\npc = %d\r\n", proc.context.pc);

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