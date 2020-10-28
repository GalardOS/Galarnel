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

.macro save_registers
	sub	sp, sp, #256
	stp	x0, x1, [sp, #16 * 0]
	stp	x2, x3, [sp, #16 * 1]
	stp	x4, x5, [sp, #16 * 2]
	stp	x6, x7, [sp, #16 * 3]
	stp	x8, x9, [sp, #16 * 4]
	stp	x10, x11, [sp, #16 * 5]
	stp	x12, x13, [sp, #16 * 6]
	stp	x14, x15, [sp, #16 * 7]
	stp	x16, x17, [sp, #16 * 8]
	stp	x18, x19, [sp, #16 * 9]
	stp	x20, x21, [sp, #16 * 10]
	stp	x22, x23, [sp, #16 * 11]
	stp	x24, x25, [sp, #16 * 12]
	stp	x26, x27, [sp, #16 * 13]
	stp	x28, x29, [sp, #16 * 14]
	str	x30, [sp, #16 * 15]                 // All registers size
.endm

.macro recover_registers
	ldp	x0, x1, [sp, #16 * 0]
	ldp	x2, x3, [sp, #16 * 1]
	ldp	x4, x5, [sp, #16 * 2]
	ldp	x6, x7, [sp, #16 * 3]
	ldp	x8, x9, [sp, #16 * 4]
	ldp	x10, x11, [sp, #16 * 5]
	ldp	x12, x13, [sp, #16 * 6]
	ldp	x14, x15, [sp, #16 * 7]
	ldp	x16, x17, [sp, #16 * 8]
	ldp	x18, x19, [sp, #16 * 9]
	ldp	x20, x21, [sp, #16 * 10]
	ldp	x22, x23, [sp, #16 * 11]
	ldp	x24, x25, [sp, #16 * 12]
	ldp	x26, x27, [sp, #16 * 13]
	ldp	x28, x29, [sp, #16 * 14]
	ldr	x30, [sp, #16 * 15] 
	add	sp, sp, #256                // All registers size
.endm

.macro vector_entry label
    .align 7 
    b \label
.endm

.globl arch_setup_vector_regs
arch_setup_vector_regs:
	adr x0, vectors
	msr vbar_el1, x0
	ret

.align	11
.globl vectors 
vectors:
	vector_entry invalid_entry			// Synchronous EL1t
	vector_entry invalid_entry			// IRQ EL1t
	vector_entry invalid_entry			// FIQ EL1t
	vector_entry invalid_entry			// Error EL1t

	vector_entry sync_asm			    // Synchronous EL1h
	vector_entry irq_asm				// IRQ EL1h
	vector_entry fiq_asm			    // FIQ EL1h
	vector_entry err_asm			    // Error EL1h

	vector_entry invalid_entry			// Synchronous 64-bit EL0
	vector_entry invalid_entry			// IRQ 64-bit EL0
	vector_entry invalid_entry			// FIQ 64-bit EL0
	vector_entry invalid_entry		    // Error 64-bit EL0

	vector_entry invalid_entry			// Synchronous 32-bit EL0
	vector_entry invalid_entry			// IRQ 32-bit EL0
	vector_entry invalid_entry			// FIQ 32-bit EL0
	vector_entry invalid_entry			// Error 32-bit EL0

invalid_entry:
    eret

sync_asm:
    save_registers
    bl synchronous_exception
    recover_registers
    eret

irq_asm:
    save_registers
    bl irq_exception
    recover_registers
    eret

fiq_asm:
    save_registers
    bl fiq_exception
    recover_registers
    eret

err_asm:
    save_registers
    bl error_exception
    recover_registers
    eret       

.globl arch_enable_irq
arch_enable_irq:
    msr daifclr, #2
    ret
.globl arch_disable_irq
arch_disable_irq:
    msr daifset, #2
    ret