#ifndef DRIVERS_GIC400_H
#define DRIVERS_GIC400_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

/*
 * This driver is divided into two different set of functions:
 * the distributor (those with prefix gic400_) and the CPU 
 * interface (those with prefix gic400_iface). 
 * 
 * The distributor is able to create a global configuration of 
 * the controller and enabling and disabling global and peripheral
 * interrupts.
 * 
 * The CPU inteface is a per processor configuration in which lets
 * you disable interrupts on the processor itself and setup priority 
 * masks.
 */

#define GIC400_INT_MODEL_1N 1
#define GIC400_INT_MODEL_NN 0

#define GIC400_CPU0   BIT(0)
#define GIC400_CPU1   BIT(1)
#define GIC400_CPU2   BIT(2)
#define GIC400_CPU3   BIT(3)
#define GIC400_CPU4   BIT(4)
#define GIC400_CPU5   BIT(5)
#define GIC400_CPU6   BIT(6)
#define GIC400_CPU7   BIT(7)
#define GIC400_CPUALL 0b11111111

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
void gic400_iface_initialize();

/*
 * Enables the interrupt routing.
 */
void gic400_enable_interrupts();

/*
 * Disables the interrupt routing.
 */
void gic400_disable_interrupts();

/*
 * Enables interrupt routing of peripheral associated to 
 * specified id
 * 
 * @param id: id of the peripheral
 */
void gic400_enable_interrupt(uint32 id);

/*
 * Set the interrupt mode for a given processor.
 * 
 * @param mode: mode to set the interrupts
 *        options: 
 *            -GIC400_INT_MODEL_1N
 *            -GIC400_INT_MODEL_NN
 */
void gic400_set_interrupt_mode(unsigned char mode);

/*
 * Sets the interrupt priority for peripheral.
 */
void gic400_set_priority(uint32 id, byte priority);

/*
 * Sets the target of an interrupt. The target of an interrupt
 * is the processor or processors to be affected.
 * 
 * @param irq_id: id of the interrupt
 * @param cpu_id: id of the target cpu
 */
void gic400_set_target(uint32 irq_id, byte cpu_id);

/*
 * Forwards an SGI to another processor. An SGI is a software
 * generated interrupt that can affect other processors.
 * 
 * @param target: processor to be affected by SGI
 */
void gic400_forward_sgi(byte target);

/*
 * Enable signaling to this CPU.
 */
void gic400_iface_enable_signaling();

void gic400_iface_aknoledge_interrupt();

void gic400_iface_set_interrupt_priority_mask();

void gic400_iface_set_preemption_policy(unsigned int preemption_policy);

/*
 * Returns the number of available interrupts lines.
 * 
 * @return: number of available lines
 */
unsigned int gic400_available_line_count();

/*
 * Gets the cpuid of the processor accessing registers.
 * 
 * @return: cpuid of the processor
 */
int gic400_get_cpuid();

#ifdef __cplusplus
}
#endif

#endif // DRIVERS_GIC400_H