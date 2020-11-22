#include "hal/intc.h"
#include "drivers/gic400/gic400.h"

#define GIC400_BCM2711_BASEADDR 0x4C0040000

int interrupt_controller_initialized = 0;

void intc_initialize() {
    if(!interrupt_controller_initialized) {
        gic400_initialize(GIC400_BCM2711_BASEADDR); 
        gic400_set_interrupt_mode(GIC400_INT_MODEL_1N);
    }

    gic400_enable_interrupts();
}

void intc_add_handler(intc_id id, intc_handler handler, int aff_cpu) {
    gic400_enable_interrupt(id.domain, id.device_id);
    gic400_set_target();            // Set all CPU as targets
}

void intc_add_local_handler(intc_id id, intc_handler handler) {
    unsigned char cpuid = gic400_get_cpuid();
    gic400_enable_interrupt(id.domain, id.device_id);
    gic400_set_target();            // Set this cpu as target
}