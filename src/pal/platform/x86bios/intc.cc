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

#include "pal/intc.hh"

#include "pal/debug.hh"

#include "pal/drivers/pic/pic.hh"

constexpr uint8 HIRQ_BASE = 0x20;

pal::intc::intc_handler handlers[255];

extern "C" void generic_interrupt_handler(uint8 irqid) {
    pal::debug::write_line("CPU interrupted");
}

#pragma region llhandlers
extern "C" void global_irq_handler0x00();
extern "C" void global_irq_handler0x01();
extern "C" void global_irq_handler0x02();
extern "C" void global_irq_handler0x03();
extern "C" void global_irq_handler0x04();
extern "C" void global_irq_handler0x05();
extern "C" void global_irq_handler0x06();
extern "C" void global_irq_handler0x07();
extern "C" void global_irq_handler0x08();
extern "C" void global_irq_handler0x09();
extern "C" void global_irq_handler0x0A();
extern "C" void global_irq_handler0x0B();
extern "C" void global_irq_handler0x0C();
extern "C" void global_irq_handler0x0D();
extern "C" void global_irq_handler0x0E();
extern "C" void global_irq_handler0x0F();
extern "C" void global_irq_handler0x10();
extern "C" void global_irq_handler0x11();
extern "C" void global_irq_handler0x12();
extern "C" void global_irq_handler0x13();

extern "C" void global_hirq_handler0x00();
extern "C" void global_hirq_handler0x01();
extern "C" void global_hirq_handler0x02();
extern "C" void global_hirq_handler0x03();
extern "C" void global_hirq_handler0x04();
extern "C" void global_hirq_handler0x05();
extern "C" void global_hirq_handler0x06();
extern "C" void global_hirq_handler0x07();
extern "C" void global_hirq_handler0x08();
extern "C" void global_hirq_handler0x09();
extern "C" void global_hirq_handler0x0A();
extern "C" void global_hirq_handler0x0B();
extern "C" void global_hirq_handler0x0C();
extern "C" void global_hirq_handler0x0D();
extern "C" void global_hirq_handler0x0E();
extern "C" void global_hirq_handler0x0F();
extern "C" void global_hirq_handler0x31();
#pragma endregion llhandlers

#define SET_ELLHANDLER(num) descriptor.int_number = num; descriptor.handler = global_irq_handler##num; pic::set_entry(descriptor)
#define SET_HLLHANDLER(num) descriptor.int_number = num + HIRQ_BASE; descriptor.handler = global_hirq_handler##num; pic::set_entry(descriptor)

namespace pal { namespace intc {

    void initialize() {
        pic::initialize();

        pic::int_descriptor descriptor;
        descriptor.descriptor_type = pic::desc_type::interrupt;
        descriptor.priviledge_level = 0;

        // Set the low level exception handlers
        SET_ELLHANDLER(0x00);
        SET_ELLHANDLER(0x01);
        SET_ELLHANDLER(0x02);
        SET_ELLHANDLER(0x03);
        SET_ELLHANDLER(0x04);
        SET_ELLHANDLER(0x05);
        SET_ELLHANDLER(0x06);
        SET_ELLHANDLER(0x07);
        SET_ELLHANDLER(0x08);
        SET_ELLHANDLER(0x09);
        SET_ELLHANDLER(0x0A);
        SET_ELLHANDLER(0x0B);
        SET_ELLHANDLER(0x0C);
        SET_ELLHANDLER(0x0D);
        SET_ELLHANDLER(0x0E);
        SET_ELLHANDLER(0x0F);
        SET_ELLHANDLER(0x10);
        SET_ELLHANDLER(0x11);
        SET_ELLHANDLER(0x12);
        SET_ELLHANDLER(0x13);

        // Set the low level hardware interrupt handlers
        SET_HLLHANDLER(0x00);
        SET_HLLHANDLER(0x01);
        SET_HLLHANDLER(0x02);
        SET_HLLHANDLER(0x03);
        SET_HLLHANDLER(0x04);
        SET_HLLHANDLER(0x05);
        SET_HLLHANDLER(0x06);
        SET_HLLHANDLER(0x07);
        SET_HLLHANDLER(0x08);
        SET_HLLHANDLER(0x09);
        SET_HLLHANDLER(0x0A);
        SET_HLLHANDLER(0x0B);
        SET_HLLHANDLER(0x0C);
        SET_HLLHANDLER(0x0D);
        SET_HLLHANDLER(0x0E);
        SET_HLLHANDLER(0x0F);
        SET_HLLHANDLER(0x31);

        pic::reload_idt();
        pic::enable();
    }

    handler_id add_handler(const irq_handler_descriptor& descriptor) {
        handlers[descriptor.irqid] = descriptor.handler;

        return descriptor.irqid;
    }

    void remove_handler(irq_handler_descriptor descriptor) {
        pic::set_ignore_entry(descriptor.irqid);
    }

    void add_error_handler(void(*error_handler)(reason)) {


    }

    void enable() {
        pic::enable();
    }

    void disable() {
        pic::disable();
    }

} }