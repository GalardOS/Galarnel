#include "bcm2835intc.hh" 
 
#include "common.hh"

#define BCM2835_BASE_REGISTER 0x7E00B000
#define PENDING0       ((volatile uint32*)(BCM2835_BASE_REGISTER + 0x200))
#define PENDING1       ((volatile uint32*)(BCM2835_BASE_REGISTER + 0x204))
#define PENDING2       ((volatile uint32*)(BCM2835_BASE_REGISTER + 0x208))
#define FIQ_CONTROL    ((volatile uint32*)(BCM2835_BASE_REGISTER + 0x20C))
#define ENABLE1        ((volatile uint32*)(BCM2835_BASE_REGISTER + 0x210))
#define ENABLE2        ((volatile uint32*)(BCM2835_BASE_REGISTER + 0x214))
#define ENABLE0        ((volatile uint32*)(BCM2835_BASE_REGISTER + 0x218))
#define DISABLE1       ((volatile uint32*)(BCM2835_BASE_REGISTER + 0x21C))
#define DISABLE2       ((volatile uint32*)(BCM2835_BASE_REGISTER + 0x220))
#define DISABLE0       ((volatile uint32*)(BCM2835_BASE_REGISTER + 0x224))

namespace drv {
    namespace bcm2835intc {
        void initialize() {
            // Set all the pendings to 0, not to interfere with 
            // future interrupts
            *PENDING0 = 0;
            *PENDING1 = 0;
            *PENDING2 = 0;

            // By default, all the interrupts will be disabled
            *DISABLE0 = 0xFFFFFFFF;
            *DISABLE1 = 0xFFFFFFFF;
            *DISABLE2 = 0xFFFFFFFF;
        }
    }
}