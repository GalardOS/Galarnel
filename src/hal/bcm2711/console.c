#include "hal/console.h"

#include "hal/bcm2711/constants.h"

#include "drivers/bcm2835auxuart/bcm2835auxuart.h"
#include "drivers/bcm2711gpio/bcm2711gpio.h"

#define UART_BASE_ADDRESS MMIO_BASE + 0x00215004
#define GPIO_BASE_ADDRESS 27

void console_initialize() {
    bcm2711gpio_initialize(GPIO_BASE_ADDRESS);

    // Configure gpio to redirect uart to pins 14 and 15
    bcm2771gpio_set_pin_mode(14, GPIO_ALT_FUNC0);
    bcm2771gpio_set_pin_mode(15, GPIO_ALT_FUNC0);
    bcm2771gpio_set_resistor_mode(14, GPIO_NO_RESISTOR); 
    bcm2771gpio_set_resistor_mode(15, GPIO_NO_RESISTOR);
    /// TODO: setup clocks

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
