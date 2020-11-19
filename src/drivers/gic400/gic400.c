#include "drivers/gic400/gic400.h"

// Distributor registers
#define GICD_CTLR       ((volatile unsigned int*)(distr_addr + 0x000))
#define GICD_TYPER      ((volatile unsigned int*)(distr_addr + 0x004))
#define GICD_IIDR       ((volatile unsigned int*)(distr_addr + 0x008))
#define GICD_ICGROUPR   ((volatile unsigned int*)(distr_addr + 0x080))
#define GICD_ISENABLER  ((volatile unsigned int*)(distr_addr + 0x100))
#define GICD_ICENABLER  ((volatile unsigned int*)(distr_addr + 0x180))
#define GICD_ISPENDR    ((volatile unsigned int*)(distr_addr + 0x200))
#define GICD_ICPENDR    ((volatile unsigned int*)(distr_addr + 0x280))
#define GICD_ISACTIVER  ((volatile unsigned int*)(distr_addr + 0x300)) 
#define GICD_ICACTIVER  ((volatile unsigned int*)(distr_addr + 0x380))
#define GICD_IPRIORITYR ((volatile unsigned int*)(distr_addr + 0x400))
#define GICD_ITARGETSR  ((volatile unsigned int*)(distr_addr + 0x800))
#define GICD_ITARGETSRW ((volatile unsigned int*)(distr_addr + 0x820))
#define GICD_ICFGR_SGI  ((volatile unsigned int*)(distr_addr + 0xC00))
#define GICD_ICFGR_PPI  ((volatile unsigned int*)(distr_addr + 0xC04))
#define GICD_ICFGR_SPI  ((volatile unsigned int*)(distr_addr + 0xC08))
#define GICD_PPISR      ((volatile unsigned int*)(distr_addr + 0xD00))
#define GICD_SPISR      ((volatile unsigned int*)(distr_addr + 0xD04))
#define GICD_SGIR       ((volatile unsigned int*)(distr_addr + 0xF00))
#define GICD_CPENDSGIR  ((volatile unsigned int*)(distr_addr + 0xF10))
#define GICD_SPENDSGIR  ((volatile unsigned int*)(distr_addr + 0xF20))
#define GICD_PIDR4      ((volatile unsigned int*)(distr_addr + 0xFD0))
#define GICD_PIDR5      ((volatile unsigned int*)(distr_addr + 0xFD4))
#define GICD_PIDR6      ((volatile unsigned int*)(distr_addr + 0xFD8))
#define GICD_PIDR7      ((volatile unsigned int*)(distr_addr + 0xFEC))
#define GICD_PIDR0      ((volatile unsigned int*)(distr_addr + 0xFE0))
#define GICD_PIDR1      ((volatile unsigned int*)(distr_addr + 0xFE4))
#define GICD_PIDR2      ((volatile unsigned int*)(distr_addr + 0xFE8))
#define GICD_PIDR3      ((volatile unsigned int*)(distr_addr + 0xFEC))

static unsigned long distr_addr;
static unsigned long icpu_addr;

void gic400_initialize(unsigned long base_addr) {
    // Setup the register addresses 
    distr_addr = base_addr + 0x1000;
    icpu_addr = base_addr + 0x2000; 


    // Disable irq controller 
    *GICD_CTLR = 0;

    // TODO: initialize

    // Enable irq controller 
    *GICD_CTLR = 1;
}