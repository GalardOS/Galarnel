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

#include "arm/sysregs.h"

.globl pre_kernel
pre_kernel:
    // Get the current EL and jump to the appropiate ring switch function
    mrs x0, CurrentEL
    lsr x0, x0, #2
    cmp x0, #2
    beq el2

// Switch from el3 to el1
el3:
    ldr x0, =SCTLR_VALUE_MMU_DISABLED
    msr sctlr_el1, x0
    ldr x0, =HCR_VALUE
    msr hcr_el2, x0
    ldr x0, =SCR_VALUE
    msr scr_el3, x0
    ldr x0, =SPSR_VALUE
    msr spsr_el3, x0
    adr x0, el1    
    msr elr_el3, x0
    eret  

// Switch from el2 to el1
el2:
    msr sp_el1, x1
    // enable CNTP for EL1
    mrs x0, cnthctl_el2
    orr x0, x0, #3
    msr cnthctl_el2, x0
    msr cntvoff_el2, xzr
    // enable AArch64 in EL1
    mov x0, #(1 << 31)  // AArch64
    orr x0, x0, #(1 << 1)   // SWIO hardwired on Pi3
    msr hcr_el2, x0
    mrs x0, hcr_el2
    // change execution level to EL1
    mov x0, #0x3c4
    msr spsr_el2, x0
    adr x0, el1
    msr elr_el2, x0
    eret
// el1 entry point
el1:
    // Move the stack pointer to 0x16000 and jump to kernel_main
    mov	x0, #0x8000
	mov x1, #2
	mul x0, x0, x1
	mov sp, x0 
    bl kernel_main
