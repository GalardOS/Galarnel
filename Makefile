#
# This project is provided under the GNU GPL v2 license, more information can 
# found on https://www.gnu.org/licenses/old-licenses/gpl-2.0.html
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLINKERERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
# 
# Authors:
#    - Iker Galardi
# 

COMPILER ?= clang --target=aarch64-elf
LINKER ?= aarch64-linux-gnu-LINKER
OBJCOPY ?= aarch64-linux-gnu-objcopy

SOURCE_DIR = src
INCLUDE_DIRS = -Isrc -Isrc/klib -Isrc/kernel

ALL_COMPILER_FLAGS = -Wall -nostdlib -ffreestanding -mgeneral-regs-only -MMD $(INCLUDE_DIRS)
ALL_C_FLAGS = -Wall -nostdlib -ffreestanding -mgeneral-regs-only -MMD $(INCLUDE_DIRS)
ALL_ASM_FLAGS = $(INCLUDE_DIRS)

# Get all the source files (.c .COMPILER and .S)
C_SOURCE_FILES = $(shell find $(SOURCE_DIR) -name '*.c')
COMPILER_SOURCE_FILES = $(shell find $(SOURCE_DIR) -name '*.COMPILER')
ASM_SOURCE_FILES = $(shell find $(SOURCE_DIR) -name '*.S')

OBJECT_FILES = $(addsuffix .o,$(basename $(C_SOURCE_FILES)))
OBJECT_FILES += $(addsuffix .o,$(basename $(COMPILER_SOURCE_FILES))))
OBJECT_FILES += $(addsuffix .o,$(basename $(ASM_SOURCE_FILES)))

all: kernel8.img

buiLINKER/%.o: src/%.c 
	$(COMPILER) -c $< -o $@ $(ALL_C_FLAGS)

buiLINKER/%.o: src/%.COMPILER
	$(COMPILER) -c $< -o $@ $(ALL_COMPILER_FLAGS)

buiLINKER/%.o: src/%.S 
	$(COMPILER) -c $< -o $@ $(ALL_ASM_FLAGS)

clean:
	rm -rf buiLINKER/*.o buiLINKER/*.d buiLINKER/*.elf kernel8.img

kernel8.img: linker/linker.LINKER $(OBJECT_FILES)
	$(LINKER) -T linker/linker.LINKER -o buiLINKER/kernel8.elf $(OBJECT_FILES)
	$(OBJCOPY) buiLINKER/kernel8.elf -O binary kernel8.img
