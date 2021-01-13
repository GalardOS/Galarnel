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

#include "pal/drivers/pic/pic.hh"

#include "pal/drivers/gdt/gdt.hh"

#include "pal/cpu.hh"
#include "pal/debug.hh"

#define KERNEL_CODE_SEGMENT 1
#define KERNEL_DATA_SEGMENT 2
#define USER_CODE_SEGMENT   3
#define USER_DATA_SEGMENT   4

#define PIC_MASTER_COMMAND 0x20
#define PIC_MASTER_DATA 0x21
#define PIC_MASTER_IMR 0x21
#define PIC_SLAVE_COMMAND 0xA0
#define PIC_SLAVE_DATA 0xA1
#define PIC_SLAVE_IMR 0xA1
#define PIC_COMMAND_EOI 0x20

#define INT_DESCRIPTOR_PRESENT 0x80

#define MAX_IDT_ENTRIES 250

namespace pic {

    struct idt_structure {
        uint16 address_low_bits;
        uint16 code_segment_selector;
        uint8 reserved;
        uint8 access;
        uint16 address_high_bits;
    } __attribute__((packed));

    static pic::idt_structure descriptors[MAX_IDT_ENTRIES];
    
    void initialize() {
        pal::debug::write_line("[PIC] Setting up GDT... ");

        gdt::set_entry(0, 0, 0, GDT_ACCESS_NULL, GDT_FLAGS_NULL);
        
        // Kernel code segment
        gdt::set_entry(1,
                       0, 0xFFFFF, 
                       GDT_ACCESS_PRESENT | GDT_ACCESS_KERNEL | GDT_ACCESS_RDWR | GDT_ACCESS_EXEC, 
                       GDT_FLAGS_32BIT_MODE | GDT_FLAGS_GRANULARITY);
        
        // Kernel data segment
        gdt::set_entry(2,
                       0, 0xFFFFF, 
                       GDT_ACCESS_PRESENT | GDT_ACCESS_KERNEL | GDT_ACCESS_RDWR | GDT_ACCESS_DATA, 
                       GDT_FLAGS_32BIT_MODE | GDT_FLAGS_GRANULARITY);

        // User code segment
        gdt::set_entry(3,
                       0, 0xFFFFF, 
                       GDT_ACCESS_PRESENT | GDT_ACCESS_USER | GDT_ACCESS_RDWR | GDT_ACCESS_EXEC, 
                       GDT_FLAGS_32BIT_MODE | GDT_FLAGS_GRANULARITY);

        // User data segment
        gdt::set_entry(4,
                       0, 0xFFFFF, 
                       GDT_ACCESS_PRESENT | GDT_ACCESS_USER | GDT_ACCESS_RDWR | GDT_ACCESS_DATA, 
                       GDT_FLAGS_32BIT_MODE | GDT_FLAGS_GRANULARITY);
       
        gdt::reload_table();

        pal::debug::write_line("[PIC] Done!");

        pal::debug::write_line("[PIC] Configuring PICS... ");
        // Send initialization command to both PICs
        pal::cpu::ports::out8(PIC_MASTER_COMMAND, 0x11);
        pal::cpu::ports::out8(PIC_SLAVE_COMMAND, 0x11);

        // Map interrupts to certain IRQ numbers
        pal::cpu::ports::out8(PIC_MASTER_DATA, 0x20);
        pal::cpu::ports::out8(PIC_SLAVE_DATA, 0x20 + 8);
        
        // Specify how the master/slave pics will comunicate (IRQ2)
        // Master takes a bit mask with the relevant bit enabled and
        // slave takes the number directly (very strange)
        pal::cpu::ports::out8(PIC_MASTER_DATA, BIT(2 + 1));
        pal::cpu::ports::out8(PIC_SLAVE_DATA, 2);

        // Indicate PICs we are in 8086 (whatever that means)
        pal::cpu::ports::out8(PIC_MASTER_DATA, 0x01);
        pal::cpu::ports::out8(PIC_SLAVE_DATA, 0x01);

        pal::debug::write_line("[PIC] Done!");

        pal::debug::write_line("[PIC] Loading IDT... ");

        pic::reload_idt();

        pal::debug::write_line("[PIC] Done!");
    }

    void set_entry(pic::int_descriptor entry) {
        // Set handler address
        descriptors[entry.int_number].address_low_bits = ((uint32)entry.handler) & 0xFFFF;
        descriptors[entry.int_number].address_high_bits = ((uint32)entry.handler >> 16) & 0xFFFF;
        
        // Set the code segment selector
        descriptors[entry.int_number].code_segment_selector = KERNEL_CODE_SEGMENT;
        
        // Reserved byte NEEDS to be 0
        descriptors[entry.int_number].reserved = 0;

        // Sets the flags for entry access
        descriptors[entry.int_number].access = INT_DESCRIPTOR_PRESENT | (uint8)entry.descriptor_type | ((entry.priviledge_level & 3) << 5);
    }

    void reload_idt() {
        struct { 
            uint16 size;
            void* ptr;
        } __attribute__((packed)) idtptr;

        idtptr.size = sizeof(idt_structure) * 8 - 1;
        idtptr.ptr = descriptors;
        asm volatile("lidt %0" :: "m"(idtptr));
    }

    void enable() {
        asm volatile ("sti");
    }

    void disable() {
        asm volatile ("cli");
    }
}