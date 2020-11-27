#ifndef DRIVERS_BCM2835AUXUART_H
#define DRIVERS_BCM2835AUXUART_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Prepares the uart ports to start transmiting and
 * receiving data.
 * 
 * @param base_address: base address of gpio registers
 */
void bcm2835auxuart_initialize(void* base_address);

/*
 * Send a byte with the UART
 * 
 * @param data: byte to be sent
 */
void bcm2835auxuart_send_byte(byte data);

/*
 * Receive a byte from the UART
 * 
 * @return: received data from UART
 */
byte bcm2835auxuart_read_byte();

#ifdef __cplusplus
}
#endif

#endif // DRIVERS_BCM2835AUXUART_H