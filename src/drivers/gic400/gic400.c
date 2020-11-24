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

// CPU interface registers
#define GICC_CTLR       ((volatile unsigned int*)(icpu_addr + 0x0000))
#define GICC_PMR        ((volatile unsigned int*)(icpu_addr + 0x0004))
#define GICC_BPR        ((volatile unsigned int*)(icpu_addr + 0x0008))
#define GICC_IAR        ((volatile unsigned int*)(icpu_addr + 0x000C))
#define GICC_EOIR       ((volatile unsigned int*)(icpu_addr + 0x0010))
#define GICC_RPR        ((volatile unsigned int*)(icpu_addr + 0x0014))
#define GICC_HPPIR      ((volatile unsigned int*)(icpu_addr + 0x0018))
#define GICC_ABPR       ((volatile unsigned int*)(icpu_addr + 0x001C))
#define GICC_AIAR       ((volatile unsigned int*)(icpu_addr + 0x0020))
#define GICC_AEOIR      ((volatile unsigned int*)(icpu_addr + 0x0024))
#define GICC_AHPPIR     ((volatile unsigned int*)(icpu_addr + 0x0028))
#define GICC_APR0       ((volatile unsigned int*)(icpu_addr + 0x00D0))
#define GICC_NSAPR0     ((volatile unsigned int*)(icpu_addr + 0x00E0))
#define GICC_IIDR       ((volatile unsigned int*)(icpu_addr + 0x00FC))
#define GICC_DIR        ((volatile unsigned int*)(icpu_addr + 0x1000))

static unsigned long distr_addr = 0;
static unsigned long icpu_addr = 0;

void gic400_initialize(unsigned long base_addr) {
    // Setup the register addresses 
    distr_addr = base_addr + 0x1000;
    icpu_addr = base_addr + 0x2000; 

    // Disable irq controller 
    *GICD_CTLR = 0;

    // Disable and clear all pending interrupts
    unsigned int n_lines = gic400_available_line_count();
    for(int i = 0; i < n_lines / 32; i++) {
        GICD_ICENABLER[i] = 0xFFFFFFFF;
        GICD_ICPENDR[i] = 0xFFFFFFFF;
    }

    // The first 8 are reserved banks for the eight supported 
    // cpus. n_lines / 4 + 1 condition deduced from sel4 driver
    // implementation.
    for(int i = 8; i < n_lines / 4; i++) {
        GICD_IPRIORITYR[i] = 0;
    }
}

void gic400_initialize_cpu_iface() {

}

void gic400_enable_interrupts() {
    *GICD_CTLR = 1;
}

void gic400_disable_interrupts() {
    *GICD_CTLR = 0;
}

void gic400_set_interrupt_mode(unsigned char mode) {
    // Ends on 29 because the configuration addresses
    // start at 0xC08 to 0xC7C, range [0:116], dividing 
    // by 4 (size of uint in bytes) gives that 29 magic 
    // number.
    for(int i = 0; i < 29; i++)
        *GICD_ICFGR_SPI = mode;
}

void gic400_enable_interrupt(uint32 id) {
    uint16 bank = id / 32;
    uint32 peripheral = BIT(id % 32);

    GICD_ISENABLER[bank] |= peripheral;
}

void gic400_disable_interrupt(uint32 id) {
    uint16 bank = id / 32;
    uint32 peripheral = BIT(id % 32);

    GICD_ICENABLER[bank] |= peripheral;   
}

unsigned int gic400_available_line_count() {
    // Get the first 4 bits of the TYPER register
    return 32 * (*GICD_TYPER & 0x1f + 1);
}

int gic400_get_cpuid() {
    // CPUID saved on bits [5:7]
    int cpuid = *GICD_TYPER;
    cpuid = cpuid >> 4;
    cpuid = cpuid & 0x3;
    return cpuid;
}