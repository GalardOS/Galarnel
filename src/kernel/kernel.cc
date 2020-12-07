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

#include "hal/exc.h"
#include "hal/intc.h"
#include "hal/console.h"

#include "klib.hh"
#include "io.h"

extern "C" void kernel_main(void)
{
	// Initialize the mini uart for logging
	console_initialize();
	console_writestring("[+] Kernel preconfiguration complete.\r\n");

	// Initialize klib
	kstd::initialize();
	kstd::printf("[+] Standard library initialized\r\n");

	// Setting up the vector table
	kstd::printf("[+] Setting up vector table... \r\n");



	int i = 0;
	while (true) {
		kstd::printf("[+] Doing nothing %d\r\n", i);
		for(int i = 0; i < 0xFFFFF; i++);
		i++;
	}

	kstd::printf("[+] Should not be here wtf\r\n");
}