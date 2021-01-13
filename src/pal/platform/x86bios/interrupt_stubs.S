#
# This project is provided under the GNU GPL v2 license, more information can 
# found on https://www.gnu.org/licenses/old-licenses/gpl-2.0.html
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
#
# Authors:
#    - Iker Galardi
#

.extern generic_interrupt_handler

.set HIRQ_BASE, 0x20

.global local_interrupt_ignore
local_interrupt_ignore:
    iret

# Macro for generating exception handlers
.macro exception_interrupt_request_handler irqnum
.global global_irq_handler\irqnum\()
global_irq_handler\irqnum\():
    movb $\irqnum, (irqnum)
    jmp generic_interrupt_jumper
.endm

# Macro for generating interrupt handlers
.macro hardware_interrupt_request_handler irqnum
.global global_hirq_handler\irqnum\()
global_hirq_handler\irqnum\():
    movb $\irqnum + HIRQ_BASE, (irqnum)
    jmp generic_interrupt_jumper
.endm

# assembly handlers
exception_interrupt_request_handler 0x00
exception_interrupt_request_handler 0x01
exception_interrupt_request_handler 0x02
exception_interrupt_request_handler 0x03
exception_interrupt_request_handler 0x04
exception_interrupt_request_handler 0x05
exception_interrupt_request_handler 0x06
exception_interrupt_request_handler 0x07
exception_interrupt_request_handler 0x08
exception_interrupt_request_handler 0x09
exception_interrupt_request_handler 0x0A
exception_interrupt_request_handler 0x0B
exception_interrupt_request_handler 0x0C
exception_interrupt_request_handler 0x0D
exception_interrupt_request_handler 0x0E
exception_interrupt_request_handler 0x0F
exception_interrupt_request_handler 0x10
exception_interrupt_request_handler 0x11
exception_interrupt_request_handler 0x12
exception_interrupt_request_handler 0x13

hardware_interrupt_request_handler 0x00
hardware_interrupt_request_handler 0x01
hardware_interrupt_request_handler 0x02
hardware_interrupt_request_handler 0x03
hardware_interrupt_request_handler 0x04
hardware_interrupt_request_handler 0x05
hardware_interrupt_request_handler 0x06
hardware_interrupt_request_handler 0x07
hardware_interrupt_request_handler 0x08
hardware_interrupt_request_handler 0x09
hardware_interrupt_request_handler 0x0A
hardware_interrupt_request_handler 0x0B
hardware_interrupt_request_handler 0x0C
hardware_interrupt_request_handler 0x0D
hardware_interrupt_request_handler 0x0E
hardware_interrupt_request_handler 0x0F
hardware_interrupt_request_handler 0x31

generic_interrupt_jumper:
    # Save the cpu context registers
    pushl %ebp
    pushl %edi
    pushl %esi
    pushl %edx
    pushl %ecx
    pushl %ebx
    pushl %eax 
    pushl %esp

    push (irqnum)
    call generic_interrupt_handler

    # Get the cpu context back
    popl %esp
    popl %eax
    popl %ebx
    popl %ecx
    popl %edx

    popl %esi
    popl %edi
    popl %ebp 
    iret

.data
    irqnum: .byte 0
    