#include "hal/intc.h"
#include "drivers/gic-400/gic400.h"

#define GIC400_BCM2711_BASEADDR 0x4C0040000

int interrupt_controller_initialized = false;

void intc_initialize() {
    if(!interrupt_controller_initialized) {
        // Enable the gic400 distributor
        gic400_initialize(GIC400_BCM2711_BASEADDR); 
        gic400_set_interrupt_mode(GIC400_INT_MODEL_1N);

        /// TODO: need atomic operations to ensure only one initialization 
        interrupt_controller_initialized = true;
    }

    // Enable the cpu interface
    gic400_iface_initialize();
    gic400_iface_enable_signaling();

    // Enable global interrupts and start receiving
    gic400_enable_interrupts();
}

void intc_add_handler(intc_id id, intc_handler handler, uint8 aff_cpu) {
    gic400_enable_interrupt(id);
    gic400_set_target(id, GIC400_CPUALL);
}

void intc_add_local_handler(intc_id id, intc_handler handler) {
    uint8 cpuid = gic400_get_cpuid();
    gic400_enable_interrupt(id);
    gic400_set_target(id, cpuid);
}