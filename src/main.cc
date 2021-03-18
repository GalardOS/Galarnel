#include "../lib/libsteel/lib/devices/mini_uart.hh"

#include "drivers/bcm2835intc.hh"

void main(int argc, char** argv) {
    steel::uart_send_string("Hello World from iquernel!\r\n");

    drv::bcm2835intc::initialize();

    while(true);
}