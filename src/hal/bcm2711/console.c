#include "hal/console.h"

#include "hal/bcm2711/constants.h"

#include "bcm2835auxuart/bcm2835auxuart.h"

#define UART_BASE_ADDRESS MMIO_BASE + 0x00215004

void console_initialize() {
    bcm2835auxuart_initialize(UART_BASE_ADDRESS);
}

void console_writechar(char character) {
    bcm2835auxuart_send_byte(character);
}

void console_writestring(char* string) {
    for(uint16 i = 0; string[i] != '\0'; i++) {
        bcm2835auxuart_send_byte(string[i]);
    }
}
