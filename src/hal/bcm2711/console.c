#include "hal/console.h"

#include "hal/bcm2711/constants.h"

#include "drivers/bcm2835auxuart/bcm2835auxuart.h"
#include "drivers/bcm2711gpio/bcm2711gpio.h"

void console_initialize() {
    bcm2711gpio_initialize(MMIO_GPIO);

    // Configure gpio to redirect uart to pins 14 and 15
    bcm2771gpio_set_pin_mode(14, GPIO_ALT_FUNC0);
    bcm2771gpio_set_pin_mode(15, GPIO_ALT_FUNC0);
    bcm2771gpio_set_resistor_mode(14, GPIO_NO_RESISTOR); 
    bcm2771gpio_set_resistor_mode(15, GPIO_NO_RESISTOR);

    bcm2835auxuart_initialize(MMIO_UART);
}

void console_writechar(char character) {
    bcm2835auxuart_send_byte(character);
}

void console_writestring(char* string) {
    for(uint16 i = 0; string[i] != '\0'; i++) {
        bcm2835auxuart_send_byte(string[i]);
    }
}
