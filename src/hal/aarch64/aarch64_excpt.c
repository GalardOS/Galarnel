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

#include "aarch64_excpt.h"
#include "aarch64_sysregs.h"

struct {
    vect_func sync;
    vect_func irq;
    vect_func fiq;
    vect_func err;
} arch_vector_table;

void arch_setup_vector(vect_func sync, vect_func irq, vect_func fiq, vect_func err) {
    arch_vector_table.sync = sync;
    arch_vector_table.irq = irq;
    arch_vector_table.fiq = fiq;
    arch_vector_table.err = err;

    arch_setup_vector_regs();
}

void synchronous_exception(void) {
    long esr = arch_sysreg_esr_el1();
    arch_vector_table.sync(esr);
}

void irq_exception(void) {
    long esr = arch_sysreg_esr_el1();
    arch_vector_table.irq(esr);
}

void fiq_exception(void) {
    long esr = arch_sysreg_esr_el1();
    arch_vector_table.fiq(esr);
}

void error_exception(void) {
    long esr = arch_sysreg_esr_el1();
    arch_vector_table.err(esr);
}