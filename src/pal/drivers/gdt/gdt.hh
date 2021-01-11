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

#pragma once

#include "common.hh"

#define GDT_ACCESS_PRESENT BIT(7)
#define GDT_ACCESS_KERNEL  BIT(5) | BIT(6)
#define GDT_ACCESS_SEGMENT 0x10
#define GDT_ACCESS_USER    0x00
#define GDT_ACCESS_EXEC    BIT(3)
#define GDT_ACCESS_DATA    0x00
#define GDT_ACCESS_RDWR    BIT(2)
#define GDT_ACCESS_NULL    0x00

#define GDT_FLAGS_GRANULARITY BIT(3)
#define GDT_FLAGS_32BIT_MODE  BIT(2)
#define GDT_FLAGS_NULL        0x00

namespace gdt {

    struct entry {
        uint16 limit0;
        uint16 base0;
        uint8  base1;
        uint8  access;
        uint8  limit_and_flags;
        uint8  base2;
    };

    typedef uint8 flags;
    typedef uint8 access;

    void reload_table();

    void set_entry(uint16 i, uint32 base, uint32 limit, gdt::access access, gdt::flags flags);
    gdt::entry get_entry(uint16 i);
    uint16 get_entry_offset(uint16 i);
};