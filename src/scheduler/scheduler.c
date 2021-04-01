#include "scheduler.h"

#include "drivers/bcm2835intc.h"
#include "memory/heap.h"

#define TIMER_CS   ((volatile uint32*)(0x3F000000+0x00003000))
#define TIMER_CLO  ((volatile uint32*)(0x3F000000+0x00003004))
#define TIMER_CHI  ((volatile uint32*)(0x3F000000+0x00003008))
#define TIMER_C0   ((volatile uint32*)(0x3F000000+0x0000300C))
#define TIMER_C1   ((volatile uint32*)(0x3F000000+0x00003010))
#define TIMER_C2   ((volatile uint32*)(0x3F000000+0x00003014))
#define TIMER_C3   ((volatile uint32*)(0x3F000000+0x00003018))

static uint64 value;
static void timer_handler(struct cpu_status state) {
    value += 200000;
    *TIMER_C1 = value;

    // Send acknowledgment to timer
    uint32 acknowledgment = 1 << 1;
    *TIMER_CS = acknowledgment;

    eret_with_context(state);
}   

struct process_control_block pcbs[100];
uint32 num_pcbs;

void initialize_scheduler() {
    num_pcbs = 0;

    // Enable interrupt routing to the CPU
    asm volatile("msr daifclr, #2");

    // Enable interrupt for system timer
    /// TODO: general interrupt manager instead of global interrupt
    ///       handler only for scheduler
    bcm2835intc_enable(33);
    set_exception_handler(EXCEPTION_INTERRUPT, timer_handler);

    // Initialize the timer counter
    value = *TIMER_C0;
    value += 200000;
    *TIMER_C1 = value;
}

void add_kernel_proces(void(*function)(void* params)) {
    // Allocate a stack for the process
    void* new_stack = heap_alloc(4 * 1024);

    // Create the process control block
    struct process_control_block pcb;
    pcb.type = PROCESS_TYPE_KERNEL;
    pcb.status.spsr = 0;
    pcb.status.sp = (uint64)new_stack;
    // pcb.status.pc = berga;

    // Add the created PCB to the list
    pcbs[num_pcbs] = pcb;
    num_pcbs++;
}