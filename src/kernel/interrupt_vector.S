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

.section ".text"
.globl move_exception_vector

.macro vector_entry label
.align 7
b   \label
.endm

/// TODO: save SIMD and floating point registers into stack 
.macro save_user_registers
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
	str	x30, [sp, #16 * 15] 
.endm

/// TODO: get SIMD and floating point registers information from stack
.macro get_user_registers
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
	add	sp, sp, #256
.endm

.align 11
.globl vector_table
vector_table:
    vector_entry unused_entry	//synchronous_el1t
    vector_entry unused_entry	//irq_el1t
    vector_entry unused_entry	//fiq_el1t
    vector_entry unused_entry	//error_el1t

    vector_entry unused_entry	//synchronous_el1h
    vector_entry unused_entry	//irq_el1h
    vector_entry unused_entry	//fiq_el1h
    vector_entry unused_entry	//error_el1h

    vector_entry unused_entry	//synchronous_el0_64
    vector_entry unused_entry	//irq_el0_64
    vector_entry unused_entry	//fiq_el0_64
    vector_entry unused_entry	//error_el0_64

    vector_entry unused_entry	//synchronous_el0_64
    vector_entry unused_entry	//irq_el0_64
    vector_entry unused_entry	//fiq_el0_64
    vector_entry unused_entry	//error_el0_64

unused_entry:
    eret

irq:
    bl irq_handler
    eret

.globl set_interrupt_table
set_interrupt_table: 
    adr x0, vector_table
    msr vbar_el1, x0
    ret
