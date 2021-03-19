#include "bcm2835auxuart.hh"

#define GPFSEL1         ((volatile uint32*)(PBASE+0x00200004))
#define GPSET0          ((volatile uint32*)(PBASE+0x0020001C))
#define GPCLR0          ((volatile uint32*)(PBASE+0x00200028))
#define GPPUD           ((volatile uint32*)(PBASE+0x00200094))
#define GPPUDCLK0       ((volatile uint32*)(PBASE+0x00200098))

#define AUX_ENABLES     ((volatile uint32*)(PBASE+0x00215004))
#define AUX_MU_IO_REG   ((volatile uint32*)(PBASE+0x00215040))
#define AUX_MU_IER_REG  ((volatile uint32*)(PBASE+0x00215044))
#define AUX_MU_IIR_REG  ((volatile uint32*)(PBASE+0x00215048))
#define AUX_MU_LCR_REG  ((volatile uint32*)(PBASE+0x0021504C))
#define AUX_MU_MCR_REG  ((volatile uint32*)(PBASE+0x00215050))
#define AUX_MU_LSR_REG  ((volatile uint32*)(PBASE+0x00215054))
#define AUX_MU_MSR_REG  ((volatile uint32*)(PBASE+0x00215058))
#define AUX_MU_SCRATCH  ((volatile uint32*)(PBASE+0x0021505C))
#define AUX_MU_CNTL_REG ((volatile uint32*)(PBASE+0x00215060))
#define AUX_MU_STAT_REG ((volatile uint32*)(PBASE+0x00215064))
#define AUX_MU_BAUD_REG ((volatile uint32*)(PBASE+0x00215068))

namespace drv {
    namespace bcm2835auxuart {

    }
}