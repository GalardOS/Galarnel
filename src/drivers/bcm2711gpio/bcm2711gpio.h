#ifndef DRIVERS_BCM2711GPIO_H
#define DRIVERS_BCM2711GPIO_H 
 
#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define GPIO_PIN_INPUT  0b000
#define GPIO_PIN_OUTPUT 0b001
#define GPIO_ALT_FUNC0  0b100
#define GPIO_ALT_FUNC1  0b101
#define GPIO_ALT_FUNC2  0b110
#define GPIO_ALT_FUNC3  0b111
#define GPIO_ALT_FUNC4  0b011
#define GPIO_ALT_FUNC5  0b010

void bcm2711gpio_initialize(long base_address);

void bcm2771gpio_set_pin_mode(uint8 pin, uint32 mode);

#ifdef __cplusplus
}
#endif

#endif // DRIVERS_BCM2711GPIO_H