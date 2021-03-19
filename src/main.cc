#include "libsteel/devices/mini_uart.hh"

#include "drivers/bcm2835intc.hh"
#include "drivers/bcm2835auxuart.hh"

void main(int argc, char** argv) {
    drv::bcm2835auxuart::init();
    drv::bcm2835auxuart::send_string("Jelou from iquernel!!\r\n");
    
    drv::bcm2835intc::initialize();

    while(true);
}