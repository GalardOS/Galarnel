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

#include "gdt.hh"

#define MAX_GDT_ENTRIES 64

namespace gdt {
    static gdt::entry gdt_entries[MAX_GDT_ENTRIES];

    void reload_table() {
        // Load the global descriptor table on the cpu register
        struct {
            uint16 limit;
            void* ptr;
        } __attribute__((packed)) gdt_register;
        gdt_register.limit = MAX_GDT_ENTRIES * sizeof(gdt::entry) - 1;
        gdt_register.ptr = gdt_entries;
        asm volatile("lgdt %0" :: "m"(gdt_register));
    }

    void set_entry(uint16 i, uint32 base, uint32 limit, gdt::access access, gdt::flags flags) {
        gdt::entry& entry = gdt_entries[i];

        // Setting the limit and flags
        entry.limit0 = limit & 0xFFFF;
        entry.limit_and_flags = (limit >> 12) & flags;

        // Setting the base 
        entry.base0 = (base >> 0 ) & 0xFFFF;
        entry.base1 = (base >> 16) & 0xFF;
        entry.base2 = (base >> 24) & 0xFF;

        // Setting the access
        entry.access = access;
    }
    

    gdt::entry get_entry(uint16 i) {
        return gdt_entries[i];
    }
}