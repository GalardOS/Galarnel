#include "drivers/bcm2835-aux-uart/bcm2835auxuart.h"

/// TODO: base_addr be relative to base of uart and not to base MMIO address
#define AUX_ENABLES     ((volatile uint32*)(base_addr + 0x00215004))
#define AUX_MU_IO_REG   ((volatile uint32*)(base_addr + 0x00215040))
#define AUX_MU_IER_REG  ((volatile uint32*)(base_addr + 0x00215044))
#define AUX_MU_IIR_REG  ((volatile uint32*)(base_addr + 0x00215048))
#define AUX_MU_LCR_REG  ((volatile uint32*)(base_addr + 0x0021504C))
#define AUX_MU_MCR_REG  ((volatile uint32*)(base_addr + 0x00215050))
#define AUX_MU_LSR_REG  ((volatile uint32*)(base_addr + 0x00215054))
#define AUX_MU_MSR_REG  ((volatile uint32*)(base_addr + 0x00215058))
#define AUX_MU_SCRATCH  ((volatile uint32*)(base_addr + 0x0021505C))
#define AUX_MU_CNTL_REG ((volatile uint32*)(base_addr + 0x00215060))
#define AUX_MU_STAT_REG ((volatile uint32*)(base_addr + 0x00215064))
#define AUX_MU_BAUD_REG ((volatile uint32*)(base_addr + 0x00215068))

static unsigned long base_addr = 0;

void bcm2835auxuart_initialize(void* base_address) {
    base_addr = base_address;


}

void bcm2835auxuart_send_byte(byte data) {

}

byte bcm2835auxuart_read_byte() {

}