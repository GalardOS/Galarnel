#include "pal/debug.hh"
#include "common.hh"

#include "pal/platform/x86bios/ports.hh"

#define VIDEO_MAP ((unsigned short*) 0xb8000)

static uint16 serial_ports[4] = { (uint16)0x3F8, (uint16)0x2F8, (uint16)0x3E8, (uint16)0x2E8 };

namespace pal { namespace debug {
    void initialize() {
        bool worked = false;
        for(uint8 i = 0; i < 1; i++){
            io::out8(serial_ports[i] + 1, (uint8)0x00);    // Disable all interrupts
            io::out8(serial_ports[i] + 3, (uint8)0x80);    // Enable DLAB (set baud rate divisor)
            io::out8(serial_ports[i] + 0, (uint8)0x03);    // Set divisor to 3 (lo byte) 38400 baud
            io::out8(serial_ports[i] + 1, (uint8)0x00);    //                  (hi byte)
            io::out8(serial_ports[i] + 3, (uint8)0x03);    // 8 bits, no parity, one stop bit
            io::out8(serial_ports[i] + 2, (uint8)0xC7);    // Enable FIFO, clear them, with 14-byte threshold
            io::out8(serial_ports[i] + 4, (uint8)0x0B);    // IRQs enabled, RTS/DSR set
            io::out8(serial_ports[i] + 4, (uint8)0x1E);    // Set in loopback mode, test the serial chip
            io::out8(serial_ports[i] + 0, (uint8)0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)
 
            // Check if serial is faulty (i.e: not same byte as sent)
            if(io::in8(serial_ports[i] + 0) == (uint8)0xAE) {
                worked = true;
            }
 
            // If serial is not faulty set it in normal operation mode
            // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
            io::out8(serial_ports[i] + 4, (uint8)0x0F);
        }

        // If no serial output device was found write an 'u' to the screen and waint until reboot
        while(!worked) VIDEO_MAP[0] = (VIDEO_MAP[0] & 0xFF00) | ('u');
    }

    void write(char ch) {
        // Wait until serial device is available to send data
        while(io::in8(serial_ports[0] + 5) & (uint8)0x20 == 0);

        // Send the character
        io::out8(serial_ports[0], ch);

    }

    void write(const char* message) {
        for(uint32 i = 0; message[i] != '\0'; i++) {
            write(message[i]);
        }
    }

    void write_line(const char* message) {
        pal::debug::write(message);
        pal::debug::write("\n");
    }
} }