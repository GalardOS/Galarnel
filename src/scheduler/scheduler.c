#include "scheduler.h"

#include "drivers/bcm2835auxuart.h"
#include "memory/heap.h"

#include "interrutps/intman.h"

struct process_control_block pcbs[100];
uint32 num_pcbs;
uint32 running_pcb_index;

static void sys_yield(struct cpu_status status) {
    // Necesary for system calls, as returning to the same
    // pc would enter into a loop of syscall return to syscall
    status.pc += 4;

    // Save the currently running process' cpu_status to the
    // pcbs list
    pcbs[running_pcb_index].status = status;

    // Select the next process to run and start running it
    /// TODO: check if is a user process, and handle it how it should
    running_pcb_index = (running_pcb_index + 1) % 100;
    eret_with_context(pcbs[running_pcb_index].status);
}

void initialize_scheduler() {

    // Add the yield system call to the list
    intman_add_synchronous(0, sys_yield);

    // Add the main thread as a kernel process so it is not lost
    struct process_control_block main;
    main.type = PROCESS_TYPE_KERNEL;
    pcbs[0] = main;
    num_pcbs = 1;
    
    // Set the added main thread as the currently running process
    running_pcb_index = 0;
}

void add_kernel_proces(void(*function)(void* params)) {
    // Allocate a stack for the process
    void* new_stack = heap_alloc(4 * 1024);

    // Create the process control block
    struct process_control_block pcb;
    pcb.type = PROCESS_TYPE_KERNEL;
    pcb.status.spsr = 0;
    pcb.status.sp = (uint64)new_stack;
    pcb.status.pc = (uint64)function;

    // Add the created PCB to the list
    pcbs[num_pcbs] = pcb;
    num_pcbs++;
}