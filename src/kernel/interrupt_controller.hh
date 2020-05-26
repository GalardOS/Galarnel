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

#pragma once

#include "klib/klib.hh"

namespace excpt 
{
    struct irq_desc {
        int bank;
        int hardware_num;
        int hardware_pending;
        kstd::func<void(void)> handler;
    };

    void initialize();

    // bool add_syncexcpt_handler                                                   NOT SUPPORTED YET
    bool add_irq_handler(irq_desc desc); //, kstd::func<void(void)> func_pointer);
    // bool add_serror_handler(kstd::func<void(int, int)> func_pointer);            NOT SUPPORTED YET
}
