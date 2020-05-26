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

	while (true);
}
