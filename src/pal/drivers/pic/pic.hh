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

namespace pic {
    enum class desc_type : uint8 {
        interrupt   = 0b110,
        trap        = 0b111,
        task        = 0b101
    };

    struct int_descriptor {
        uint8 int_number;
        void(*handler)();
        uint8 priviledge_level;
        desc_type descriptor_type;
    };

    void initialize();

    void set_entry(pic::int_descriptor entry);

    void set_ignore_entry(uint8 int_number);

    void set_interrupt_mask(uint16 mask);

    void reload_idt();
    
    void enable();

    void disable();
}