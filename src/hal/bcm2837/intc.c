#include "hal/intc.h"
#include "hal/exc.h"
#include "hal/bcm2837/constants.h"

volatile int* IRQ_BASIC_PENDING  = (int*)(MMIO_BASE+0x0000B200);
volatile int* IRQ_PENDING_1      = (int*)(MMIO_BASE+0x0000B204);
volatile int* IRQ_PENDING_2      = (int*)(MMIO_BASE+0x0000B208);
volatile int* FIQ_CONTROL        = (int*)(MMIO_BASE+0x0000B20C);
volatile int* ENABLE_IRQS_1      = (int*)(MMIO_BASE+0x0000B210);
volatile int* ENABLE_IRQS_2      = (int*)(MMIO_BASE+0x0000B214);
volatile int* ENABLE_BASIC_IRQS  = (int*)(MMIO_BASE+0x0000B218);
volatile int* DISABLE_IRQS_1     = (int*)(MMIO_BASE+0x0000B21C);
volatile int* DISABLE_IRQS_2     = (int*)(MMIO_BASE+0x0000B220);
volatile int* DISABLE_BASIC_IRQS = (int*)(MMIO_BASE+0x0000B224);

typedef struct {
    intc_id id;
    intc_handler handler;
} id_handler_pair;

static id_handler_pair handlers[50];
static short handler_count;

void intc_initialize() {
    exc_enable_irq();

    handler_count = 0;
}

void add_handler(intc_id id, intc_handler handler) {
    id_handler_pair pair;
    pair.id = id;
    pair.handler = handler;

    handlers[handler_count] = pair;
    handler_count++;

    *((int*)id.domain) = id.device_id;
}