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

.set MAGIC, 0x1badb002
.set FLAGS, (1 << 0 | 1 << 1)
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
.long MAGIC
.long FLAGS
.long CHECKSUM 

.section .text

.extern pre_configuration
.extern call_global_constructors

# Entry point of the program
.global _start
_start:
    cli
    mov $kernel_stack, %esp

    # Getting the multiboot structure inside kernel_main
    push %eax
    push %ebx
    call pre_configuration

# In case kernel exits infinite loop
_stop:
    cli
    hlt
    jmp _stop

.section .bss
.space 2 * 1024 * 1024 #2 MB
kernel_stack: 
