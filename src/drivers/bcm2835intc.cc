#include "bcm2835intc.hh" 
 
#define BCM2835_BASE_REGISTER 0x7E00B000
#define PENDING_ARM    ((volatile uint32*)(BCM2835_BASE_REGISTER + 0x200))
#define PENDING1       ((volatile uint32*)(BCM2835_BASE_REGISTER + 0x204))
#define PENDING2       ((volatile uint32*)(BCM2835_BASE_REGISTER + 0x208))
#define FIQ_CONTROL    ((volatile uint32*)(BCM2835_BASE_REGISTER + 0x20C))
#define ENABLE1        ((volatile uint32*)(BCM2835_BASE_REGISTER + 0x210))
#define ENABLE2        ((volatile uint32*)(BCM2835_BASE_REGISTER + 0x214))
#define ENABLE_ARM     ((volatile uint32*)(BCM2835_BASE_REGISTER + 0x218))
#define DISABLE1       ((volatile uint32*)(BCM2835_BASE_REGISTER + 0x21C))
#define DISABLE2       ((volatile uint32*)(BCM2835_BASE_REGISTER + 0x220))
#define DISABLE_ARM    ((volatile uint32*)(BCM2835_BASE_REGISTER + 0x224))

namespace drv {
    namespace bcm2835intc {
        void initialize() {
            // Set all the pendings to 0, not to interfere with 
            // future interrupts
            *PENDING_ARM = 0;
            *PENDING1 = 0;
            *PENDING2 = 0;

            // By default, all the interrupts will be disabled
            *DISABLE_ARM = 0xFFFFFFFF;
            *DISABLE1 = 0xFFFFFFFF;
            *DISABLE2 = 0xFFFFFFFF;
        }

        void enable_irq(uint32 irq_num) {
            uint32 bit_of_register = irq_num % 32;
            uint32 register_of_irq = irq_num / 32;

            switch(register_of_irq) {
                case 0: {
                    *ENABLE_ARM = bit_of_register;
                } break;
                
                case 1: {
                    *ENABLE1 = bit_of_register;
                } break;

                case 2: {
                    *ENABLE2 = bit_of_register;
                } break;
            }
        }

        void disable_irq(uint32 irq_num) {
            uint32 bit_of_register = irq_num % 32;
            uint32 register_of_irq = irq_num / 32;

            switch(register_of_irq) {
                case 0: {
                    *DISABLE_ARM = bit_of_register;
                } break;
                
                case 1: {
                    *DISABLE1 = bit_of_register;
                } break;

                case 2: {
                    *DISABLE2 = bit_of_register;
                } break;
            }

        }
    }
}