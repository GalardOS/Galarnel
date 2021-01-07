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

#include "pal/debug.hh"
#include "pal/cpu.hh"
#include "pal/intc.hh"

void timer_interrupt() {
	pal::debug::write_line("Timer interrupt");
}

void kernel_main(void) {
	pal::debug::write_line("[+] Kernel entry reached");

	pal::intc::irq_handler_descriptor desc;
	desc.irqid = 20;
	desc.type = pal::intc::int_type::hardware;
	desc.handler = timer_interrupt;
	pal::intc::handler_id timer_id = pal::intc::add_handler(desc);

	int counter = 0;
	while(true) {
		pal::cpu::wait_cycles(0xFFFFF);
		counter++;

		pal::debug::write_line("[+] Inside the loop");
	}

	pal::debug::write_line("[+] This should not be printing ups");
}