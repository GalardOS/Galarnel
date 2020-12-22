#ifndef HAL_BCM2711_H
#define HAL_BCM2711_H

// Base MMIO base address
#define MMIO_BASE 0xFE000000

// UART registers address
#define MMIO_UART MMIO_BASE + 0x00215000

// GPIO registers address
#define MMIO_GPIO MMIO_BASE + 0x00200000

#endif // HAL_BC2711_H