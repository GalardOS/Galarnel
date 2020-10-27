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

#include "excpt.hh"

extern "C" {
    #include "aarch64/aarch64_excpt.h"
}

namespace cpu {
    namespace excp {

        void setup_vector(const vector_table& vt) {
            auto sync_func = &vt.sync_excpt;
            auto irq_func = &vt.irq_excpt;
            auto fiq_func = &vt.fiq_excpt;
            auto err_func = &vt.err_excpt;

            arch_setup_vector(sync_func, irq_func, fiq_func, err_func);
        }
    }
}