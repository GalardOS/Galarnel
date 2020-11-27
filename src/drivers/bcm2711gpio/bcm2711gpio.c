#include "drivers/bcm2711gpio/bcm2711gpio.h"

#include "common.h"

#define GPFSEL0                 ((volatile uint32*)(gpio_base_addr + 0x00))
#define GPFSEL1                 ((volatile uint32*)(gpio_base_addr + 0x04))
#define GPFSEL2                 ((volatile uint32*)(gpio_base_addr + 0x08))
#define GPFSEL3                 ((volatile uint32*)(gpio_base_addr + 0x0C))
#define GPFSEL4                 ((volatile uint32*)(gpio_base_addr + 0x10))
#define GPFSEL5                 ((volatile uint32*)(gpio_base_addr + 0x14))

#define GPSET0                  ((volatile uint32*)(gpio_base_addr + 0x1C))
#define GPSET1                  ((volatile uint32*)(gpio_base_addr + 0x20))

#define GPCLR0                  ((volatile uint32*)(gpio_base_addr + 0x28))
#define GPCLR1                  ((volatile uint32*)(gpio_base_addr + 0x2C))

#define GPLEV0                  ((volatile uint32*)(gpio_base_addr + 0x34))
#define GPLEV1                  ((volatile uint32*)(gpio_base_addr + 0x38))

#define GPEDS0                  ((volatile uint32*)(gpio_base_addr + 0x40))
#define GPEDS1                  ((volatile uint32*)(gpio_base_addr + 0x44))

#define GPREN0                  ((volatile uint32*)(gpio_base_addr + 0x4C))
#define GPREN1                  ((volatile uint32*)(gpio_base_addr + 0x50))

#define GPFEN0                  ((volatile uint32*)(gpio_base_addr + 0x58))
#define GPFEN1                  ((volatile uint32*)(gpio_base_addr + 0x5C))

#define GPHEN0                  ((volatile uint32*)(gpio_base_addr + 0x64))
#define GPHEN1                  ((volatile uint32*)(gpio_base_addr + 0x68))

#define GPAREN0                 ((volatile uint32*)(gpio_base_addr + 0x7C))
#define GPAREN1                 ((volatile uint32*)(gpio_base_addr + 0x80))

#define GPAFEN0                 ((volatile uint32*)(gpio_base_addr + 0x88))
#define GPAFEN1                 ((volatile uint32*)(gpio_base_addr + 0x8C))

#define GPIO_PUP_PDN_CNTRL_REG0 ((volatile uint32*)(gpio_base_addr + 0xE4))
#define GPIO_PUP_PDN_CNTRL_REG1 ((volatile uint32*)(gpio_base_addr + 0xE8))
#define GPIO_PUP_PDN_CNTRL_REG2 ((volatile uint32*)(gpio_base_addr + 0xEC))
#define GPIO_PUP_PDN_CNTRL_REG3 ((volatile uint32*)(gpio_base_addr + 0xF0))

static uint64 gpio_base_addr;

void bcm2711gpio_initialize(long base_address) {
    gpio_base_addr = base_address;
}

void bcm277gpio_set_pin_mode(uint8 pin, uint32 mode) {
    // Selector to activate the mode of the pin
    int selector = mode << (pin % 10);

    // Set the mode on the specific bank
    if(ON_RANGE(pin, 50, 57)) {
        *GPFSEL5 |= selector;
    } else if(ON_RANGE(pin, 40, 49)) {
        *GPFSEL4 |= selector;
    } else if(ON_RANGE(pin, 30, 39)) {
        *GPFSEL3 |= selector;
    } else if(ON_RANGE(pin, 20, 29)) {
        *GPFSEL2 |= selector;
    } else if(ON_RANGE(pin, 10, 19)) {
        *GPFSEL1 |= selector;
    } else if(ON_RANGE(pin, 0, 9)) {
        *GPFSEL0 |= selector;
    }
}