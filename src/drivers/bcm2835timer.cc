#include "bcm2835timer.hh"

#define TIMER_CS        ((volatile uint32*)(0x3F000000+0x00003000))
#define TIMER_CLO       ((volatile uint32*)(0x3F000000+0x00003004))
#define TIMER_CHI       ((volatile uint32*)(0x3F000000+0x00003008))
#define TIMER_C0        ((volatile uint32*)(0x3F000000+0x0000300C))
#define TIMER_C1        ((volatile uint32*)(0x3F000000+0x00003010))
#define TIMER_C2        ((volatile uint32*)(0x3F000000+0x00003014))
#define TIMER_C3        ((volatile uint32*)(0x3F000000+0x00003018))

static uint64 value;

namespace drv {
    namespace bcm2835timer {
        void initialize(uint64 cycles) {
            // Initialize the timer with a random value (not gonna lie)
            value = *TIMER_CLO;
            value += cycles;
            *TIMER_C1 = value;
        }
        
        void restart(uint64 cycles) {
            // Initialize the timer value to the given value
            value += cycles;
            *TIMER_C1 = value;
    
            // Send an acknowledgment in case a previous interrupt
            // was not handled properly or not handled at all
            uint32 acknowledgment = 1 << 1;
            *TIMER_CS = acknowledgment;
        }
    }
}