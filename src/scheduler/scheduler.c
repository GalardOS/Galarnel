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

struct process_control_block pcbs[100];
uint32 num_pcbs;

void initialize_scheduler() {
    num_pcbs = 0;
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