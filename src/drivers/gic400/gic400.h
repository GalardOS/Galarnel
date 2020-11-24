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

void gic400_enable_interrupt(uint32 id);

/*
 * Set the interrupt mode for a given processor
 */
void gic400_set_interrupt_mode(unsigned char mode);

/*
 * Sets the interrupt priority for peripheral.
 */
void gic400_set_priority();

/*
 * Sets the target of an interrupt. The target of an interrupt
 * is the processor or processors to be affected.
 */
void gic400_set_target();

/*
 * Forwards an SGI to another processor. An SGI is a software
 * generated interrupt that can affect other processors.
 * 
 * @param target: processor to be affected by SGI
 */
void gic400_forward_sgi(unsigned char target);

/*
 * 
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