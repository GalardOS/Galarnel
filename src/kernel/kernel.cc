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

extern "C" {
	#include "utils.h"
}

#include "hal/cpu.hh"
#include "hal/excpt.hh"
#include "hal/interrupts.hh"

#include "mini_uart.hh"
#include "klib.hh"
#include "io.h"

extern "C" void kernel_main(void)
{
	// Initialize the mini uart for logging
	muart::initialize();
	muart::send_string("[+] Kernel preconfig completed.\r\n");
	
	// Initialize klib
	muart::send_string("[+] Initializing klib... \r\n");
	kstd::initialize();
	kstd::printf("[+] Done!\r\n");

	// Setting up the vector table
	kstd::printf("[+] Setting up vector table... \r\n");
	cpu::excp::vector_table table {
		.sync_excpt = kstd::func<void(long, long)>::null(),
		.irq_excpt = intc::generic_irq_handler,
		.fiq_excpt = kstd::func<void(long, long)>::null(),
		.err_excpt = kstd::func<void(long, long)>::null()
	};
	
	cpu::excp::setup_vector(table);
	kstd::printf("[+] Done!\r\n");

	while (true);
}