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

#include "interrupt_controller.hh"

#include "klib/klib.hh"
extern "C" {
    #include "utils.h"
}

static excpt::irq_desc irq_description;

// Declarations from interrupt_vector.S
extern "C" {
    void set_interrupt_table();
    void enable_irq();
    void disable_irq();
}

// This handler is going to be called from an exception state
extern "C" __attribute__((interrupt("IRQ"))) void irq_handler() {
    kstd::printf("[EXCP] Generic interrupt handler\r\n");
    irq_description.handler.execute();
}

namespace excpt {
    void initialize() {
        set_interrupt_table();
        enable_irq();
    }

    bool add_irq_handler(irq_desc description) {
        mem_put32(description.bank, description.hardware_num);
        irq_description = description;
        return true;
    }
}

