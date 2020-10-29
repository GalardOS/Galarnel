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

#include "interrupts.hh"

#include "klib/array.hh"

struct handler_pair {
    intc::id id;
    kstd::func<void(void)> handler;
    kstd::func<void(void)> cleaner;
};

int handler_count;
kstd::array<handler_pair, 70> interrupt_handlers;

namespace intc {
    bool initialize() {
        handler_count = 0;
        for(int i = 0; i < interrupt_handlers.size(); i++) {
            interrupt_handlers[i] = {};
        }

        /// TODO: get driver and add generic irq handler

        return true;
    }

    void add_handler(id id, kstd::func<void(void)> handler, kstd::func<void(void)> cleaner) {
        handler_pair pair;
        pair.id = id;
        pair.handler = handler;
        pair.cleaner = cleaner;


        interrupt_handlers[handler_count++] = pair;
    }

    void generic_irq_handler(long, long) {
        kstd::printf("[D] Entered generic irq handler\r\n");

        for(int i = 0; i < interrupt_handlers.size(); i++) {
            /// TODO: check what has interrupted 
        }
    }
}