/*
 * This project is provided under the GNU GPL v2 license, more information can 
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

#include "pal/cpu.hh"

namespace pal { namespace cpu {

    struct context {
        int32 eax;
        int32 ebx;
        int32 ecx;
        int32 edx;
        int32 esi;
        int32 edi;
        int32 ebp;

        int32 ds;
        int32 es;
        int32 fs;
        int32 gs;
    };

    void initialize() {

    }

    void wait_cycles(uint64 cycles) {
        int i = 0; 
        while(i < cycles) {
            int b = 1 + 1;
            i++;
        }
    }

    namespace ports {
        uint8 in8(uint16 port)
        {
            uint8 value;
            asm volatile("inb %1, %0"
                         : "=a"(value)
                         : "Nd"(port));
            return value;
        }

        uint16 in16(uint16 port)
        {
            uint16 value;
            asm volatile("inw %1, %0"
                         : "=a"(value)
                         : "Nd"(port));
            return value;
        }

        uint32 in32(uint16 port)
        {
            uint32 value;
            asm volatile("inl %1, %0"
                         : "=a"(value)
                         : "Nd"(port));
            return value;
        }

        void repeated_in16(uint16 port, uint16* buffer, int buffer_size)
        {
            asm volatile("rep insw"
                         : "+D"(buffer), "+c"(buffer_size)
                         : "d"(port)
                         : "memory");
        }

        void out8(uint16 port, uint8 value)
        {
            asm volatile("outb %0, %1" ::"a"(value), "Nd"(port));
        }

        void out16(uint16 port, uint16 value)
        {
            asm volatile("outw %0, %1" ::"a"(value), "Nd"(port));
        }

        void out32(uint16 port, uint32 value)
        {
            asm volatile("outl %0, %1" ::"a"(value), "Nd"(port));
        }

        void repeated_out16(uint16 port, const uint16* data, int data_size)
        {
            asm volatile("rep outsw"
                         : "+S"(data), "+c"(data_size)
                         : "d"(port));
        }

        void delay(uint32 microseconds)
        {
            for (uint32 i = 0; i < microseconds; ++i)
                in8(0x80);
        }
    }
} }