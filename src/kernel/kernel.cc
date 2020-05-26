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

extern "C" 
{
	#include "cpu.h"
	#include "utils.h"
}

#include "mini_uart.hh"
#include "interrupt_controller.hh"
#include "klib.hh"
#include "io.h"

namespace kstd_test {
	int func_test(int gg) {
		return gg;
	}
	
	void kstd_func() {
		kstd::func<int(int)> fntest(func_test);
		int r = fntest.execute(7);
		kstd::printf("function result value: %d\r\n", r);
	}

	void all() {
		kstd::printf("-- kstd::func test\r\n");
		kstd_func();
		kstd::printf("-- kstd::func test ended\r\n");
	}
}

namespace kernel_test {
	const unsigned int interval = 200000;
	volatile unsigned int curVal = 0;

	void timer_handler();

	void timer_init() {
		curVal = mem_get32(TIMER_CLO);
		curVal += interval;
		mem_put32(TIMER_C1, curVal); 
		mem_put32(TIMER_CS, TIMER_CS_M1);


		excpt::irq_desc timer;
		timer.bank = ENABLE_IRQS_1;
		timer.hardware_num = SYSTEM_TIMER_IRQ_1;
		timer.handler = timer_handler;
		excpt::add_irq_handler(timer);
	}

	void timer_handler() {
		curVal += interval;
		mem_put32(TIMER_C1, curVal);
		mem_put32(TIMER_CS, TIMER_CS_M1);

		kstd::printf("Received timer interrupt!!\r\n");
	}

	void all() {
		kstd::printf("-- kernel::timer test\r\n");
		timer_init();
		kstd::printf("-- kernel::timer test ended\r\n");
	}
}

extern "C" void kernel_main(void)
{
	// Initialize the mini uart for logging
	muart::initialize();
	muart::send_string("[+] Kernel preconfig completed.\r\n");
	
	// Initialize klib
	muart::send_string("[+] Initializing klib... \r\n");
	kstd::initialize();
	kstd::printf("[+] Done!\r\n");

	/// TODO: make able to dissable the tests at compile time
	kstd::printf("[+] Starting klib tests...\r\n");
	kstd_test::all();
	kstd::printf("[+] Done!\r\n");

	kstd::printf("[+] Initializing and configuring exceptions...\r\n");
	excpt::initialize();
	/// TODO: configure system error exception handler
	kstd::printf("[+] Done!\r\n");

	/// TODO: make able to dissable the tests at compile time
	kstd::printf("[+] Starting kernel tests...\r\n");
	kernel_test::all();
	kstd::printf("[+] Done\r\n");

	while (true) {
		kstd::printf("While (true)\r\n");

		int i = 0;
		while(i < 100000)
			i++;
	}
}
