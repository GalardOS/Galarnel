#ifndef DRIVERS_GIC400_H
#define DRIVERS_GIC400_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Initializes the gic-400 interrupt controller by 
 * setting up all the register addresses and cleaning 
 * up all the interrupts and priorities.
 * 
 * @param base_addr: base address of the gic400 registers
 */
void gic400_initialize(unsigned long base_addr);

/*
 * Sets up the CPU interface of the interrupt controller
 * This must be executed on all the CPU cores of the system which 
 * want to receive interrupts.
 * 
 * @constraint: must be executed after gic400_initialize function
 */
void gic400_initialize_cpu_iface();

/*
 * Enables the interrupt routing.
 */
void gic400_enable_interrupts();

/*
 * Disables the interrupt routing.
 */
void gic400_disable_interrupts();

/*
 * Returns the number of available interrupts lines.
 * 
 * @return: number of available lines
 */
unsigned int gic400_available_line_count();

/*
 * Gets the cpuid of the core accessing registers.
 * 
 * @return: cpuid of the core
 */
int gic400_get_cpuid();

#ifdef __cplusplus
}
#endif

#endif // DRIVERS_GIC400_H