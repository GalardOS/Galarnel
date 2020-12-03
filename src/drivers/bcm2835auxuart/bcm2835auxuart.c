#include "drivers/bcm2835auxuart/bcm2835auxuart.h"

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

    // Enable the UART
    *AUX_ENABLES = 1;

    // Disable the interrupts (and other things)
    *AUX_MU_IER_REG = 0; 

    // Disable Receiver and transmitter, flow control etc
    *AUX_MU_CNTL_REG = 0;

    // Enable 8 bit mode
    *AUX_MU_LCR_REG = BIT(0);

    // Set RTS line to always high
    *AUX_MU_MCR_REG = 0;

    // Enable baud rate access bit 7 is set to 1
    *AUX_MU_IER_REG = BIT(7);

    // Set baud rate to 115200
    *AUX_MU_BAUD_REG = 270;

    // Enable transmitter and receiver
    *AUX_MU_CNTL_REG = BIT(0) | BIT(1);
}

void bcm2835auxuart_send_byte(byte data) {
    // Wait until data can be sent 
    while(!(*AUX_MU_LSR_REG & BIT(0)));
    
    // Send data
    *AUX_MU_IO_REG = data;
}

byte bcm2835auxuart_read_byte() {

}