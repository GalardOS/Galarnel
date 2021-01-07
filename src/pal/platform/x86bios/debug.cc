/*
 * This project is provided under the GNU GPL v2 license, more informatpal::cpu::portsn can 
 * found on https://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *    - Iker Galardi
 */

#include "pal/debug.hh"
#include "pal/cpu.hh"
#include "common.hh"

#define VIDEO_MAP ((unsigned short*) 0xb8000)

static uint16 serial_ports[4] = { (uint16)0x3F8, (uint16)0x2F8, (uint16)0x3E8, (uint16)0x2E8 };

namespace pal { namespace debug {
    void initialize() {
        bool worked = false;
        for(uint8 i = 0; i < 1; i++){
            pal::cpu::ports::out8(serial_ports[i] + 1, (uint8)0x00);    // Disable all interrupts
            pal::cpu::ports::out8(serial_ports[i] + 3, (uint8)0x80);    // Enable DLAB (set baud rate divisor)
            pal::cpu::ports::out8(serial_ports[i] + 0, (uint8)0x03);    // Set divisor to 3 (lo byte) 38400 baud
            pal::cpu::ports::out8(serial_ports[i] + 1, (uint8)0x00);    //                  (hi byte)
            pal::cpu::ports::out8(serial_ports[i] + 3, (uint8)0x03);    // 8 bits, no parity, one stop bit
            pal::cpu::ports::out8(serial_ports[i] + 2, (uint8)0xC7);    // Enable FIFO, clear them, with 14-byte threshold
            pal::cpu::ports::out8(serial_ports[i] + 4, (uint8)0x0B);    // IRQs enabled, RTS/DSR set
            pal::cpu::ports::out8(serial_ports[i] + 4, (uint8)0x1E);    // Set in loopback mode, test the serial chip
            pal::cpu::ports::out8(serial_ports[i] + 0, (uint8)0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)
 
            // Check if serial is faulty (i.e: not same byte as sent)
            if(pal::cpu::ports::in8(serial_ports[i] + 0) == (uint8)0xAE) {
                worked = true;
            }
 
            // If serial is not faulty set it in normal operatpal::cpu::portsn mode
            // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
            pal::cpu::ports::out8(serial_ports[i] + 4, (uint8)0x0F);
        }

        // If no serial output device was found write an 'u' to the screen and waint until reboot
        while(!worked) VIDEO_MAP[0] = (VIDEO_MAP[0] & 0xFF00) | ('u');
    }

    void write(char ch) {
        // Wait until serial device is available to send data
        while(pal::cpu::ports::in8(serial_ports[0] + 5) & (uint8)0x20 == 0);

        // Send the character
        pal::cpu::ports::out8(serial_ports[0], ch);

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