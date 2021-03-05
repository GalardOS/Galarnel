#include "../lib/libsteel/lib/devices/mini_uart.hh"

void main(int argc, char** argv) {
    steel::uart_send_string("Hello World from iquernel!\r\n");

    while(true);
}