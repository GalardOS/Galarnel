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

.section ".text.boot"

.globl _start
_start:
	// Hang all non primary cpus
	mrs		x0, mpidr_el1		
	and		x0, x0,#0xFF
	cbnz	x0, proc_hang

	// Zero out the bss region
	adr	x0, bss_begin
	adr	x1, bss_end
	sub	x1, x1, x0
zero_bss:
	str xzr, [x0], #8
	subs x1, x1, #8
	bgt zero_bss

	// Jump to pre_kernel (First kernel initialization phase)
	bl	pre_kernel

proc_hang: 
	b 	proc_hang
